import os, sqlite3, subprocess, yaml
from logging import Logger

class BitcodeExtractor:
  """Builds desired conan2 packages from a local conan-center clone 
  and extracts the LLVM bitcode from their binaries.

  TODO:
    * first priority: test on a bunch of recipes
    * add option dependencies get their bitcode extracted as well
    * extract more metadata (like what though?)
    * make good comments on the methods and stuff
  """

  # a record we pass into `conan install` so it compiles packages using gllvm
  __compiler_executables: dict[str, str] = {
            "c": "gclang",
            "cpp": "gclang++",
        }

  def __init__(self, conan_index: str, output_folder: str, logger: Logger):
    """Initializes BitcodeExtractor.

    Args:
      conan_index: Path to copy of conan-center-index's repo.
      output_folder: Path to folder to output the bitcode.
      logger: A logger (mostly for debug info).
    """
    self.__index_dir = conan_index
    self.__out_dir = output_folder
    self.__logger = logger
    # path to the sqlite3 database which holds the locations 
    # of all installed packages in the local cache
    self.__cache = BitcodeExtractor.__get_cache_path()
  
  def extract_bitcode(self, recipe: str, version: str, cascade: bool = True, check_version: bool = True) -> int:
    """Attempt to install a a given package/version, and returns how many bitcode files we got. 
    Raises exeptions on failure.
    
    Args:
      recipe: The recipe to try and install.
      version: The specific version of the recipe.
      cascade: whether to try and get bitcode from installed dependencies of the package.
      check_version: whether to check if the version exists before trying to install.
    
    Returns:
      The number of bitcode files successfully extracted.

    Raises:
      IOError: If a necessary file wasn't found, or failure to make a file.
      RuntimeError: If a necessary command failed, or something unexpected happened.
    """
    if check_version:
      # get the config.yml path which contains all versions for a package
      conf_path = self.__get_conf_file_path(recipe)

      # error if version not found
      if not BitcodeExtractor.__version_exists(conf_path, version):
        raise IOError(f'version {version} does not exist for recipe {recipe}')
      
    # run 'conan install ...' on the package. This function takes the lion's share of the time
    self.__run_install(recipe, version)

    # if run_install() didn't throw, we get the directory where the binaries were installed and write them out
    package_folder = self.__get_package_dir(recipe, version)
    return self.__write_bitcode(package_folder, recipe, version)
  
  def __get_conf_file_path(self, recipe: str) -> str:
    """Given a recipe name, return the path to its `config.yml` file (contains all its versions)."""
    conf_path = os.path.join(self.__index_dir, 'recipes', recipe, 'config.yml')
    if not os.path.isfile(conf_path):
      self.__logger.debug(f'conf file for package not found: {conf_path}')
      raise IOError(f'recipe {recipe} does not exist in conan-center-index')
    return conf_path
  
  def __version_exists(conf_path: str, version: str) -> bool:
    """Return whether a certain version exists in `config.yml` file."""
    conf_file = open(conf_path, 'r')
    conf_parsed = yaml.safe_load(conf_file)
    conf_file.close()

    return version in conf_parsed['versions'].keys()

  def __run_install(self, recipe: str, version: str):
    """Attempt to install the given recipe/version.

    Note:
      This function takes the *most* amount of time compared to anything else in this class.
    """
    self.__logger.info(f'started conan install for {recipe}/{version}')
    run_info = subprocess.run(['conan', 'install',
                               # specify which package/version to install
                               # (we use this instead of the path to conanfile.py because that doesn't always work)
                              f'--requires={recipe}/{version}',
                              # if prebuilt binaries are not available, build from scratch
                              '--build=missing',
                              # build in Debug mode (needed for PhASAR)
                              '--settings:all=build_type=Debug',
                              # set the cpp standard at 20 to build as many packages as possible
                              '--settings:all=compiler.cppstd=gnu20',
                              # specify the gllvm binaries so clang saves the llvm bitcode
                              f'--conf:all=tools.build:compiler_executables={self.__compiler_executables}',
                              # allow recipes to install needed packages so less package installations fail
                              '--conf:all=tools.system.package_manager:mode=install',
                              # install from our local copy of conan index
                              '--remote=conan-index',
                              # conan install writes some output files that we don't seem to need,
                              # just put them in the place they would go if we used the path to the conanfile.py
                              # instead of --requires. TODO: look into this more?
                              f'--output-folder={os.path.join(self.__index_dir, recipe, 'all/build/')}'],
                              # capture output for debug info on install failure
                              capture_output=True, text=True)
    if run_info.returncode != 0:
      self.__logger.debug('conan install output: \n\t\t' + run_info.stderr.replace('\n', '\n\t\t'))
      raise RuntimeError('conan install failed')
    self.__logger.info('conan install successful')
  
  def __write_bitcode(self, package_folder: str, recipe: str, version: str) -> int:
    """Given the build folder for a package, extract all possible bitcode files and 
    write them out to the output folder. Return how many bitcode files extracted.

    Args:
      package_folder: The folder with all the binaries for this package version.
      recipe: The name of the recipe we installed.
      version: the version of the package we installed.
    
    Returns:
      The number of bitcode files successfully extracted.

    TODO:
      some recipes may have stuff in their metadata folder, check for that
      to get it: `conan cache path --folder=metadata <recipe>/<version>`
    """
    out_folder = self.__gen_out_dir(recipe, version)
    num_written = 0

    # for all files in this directory (recursive)
    for root, _, files in os.walk(package_folder):
      for file in files:

        # get absolute path to file
        potential_bin = os.path.join(root, file)
        # construct path to output file
        out_file = os.path.join(out_folder, file + '.bc')
        # if `get-bc` succeeds, increment num_written
        if self.__invoke_get_bc(potential_bin, out_file):
          num_written += 1
    
    return num_written
  
  def __get_package_dir(self, recipe: str, version: str) -> str:
    """Gets the directory where all of the binaries are stored."""
    if not os.path.isfile(self.__cache):
      self.__logger.error(f'`cache.sqlite3` not found at: {self.__cache}')
      raise IOError('cannot find `cache.sqlite3` in local conan cache')
    
    con = sqlite3.connect(self.__cache)
    cur = con.cursor()

    recipe_ref = f'{recipe}/{version}'
    res = cur.execute("""SELECT path FROM packages 
                            WHERE reference=?
                            ORDER BY timestamp DESC""", (recipe_ref,)).fetchone()
    
    if res is None:
      # dump database if we can't find recipe_ref
      self.__logger.debug(f'contents of table packages in `cache.sqlite3`: \n{'\n'.join(cur.execute('SELECT * FROM packages').fetchall())}'.replace('\n', '\n\t\t'))
      con.close()
      raise RuntimeError(f'cannot find `{recipe_ref}` in local conan cache database')
    con.close()

    (rel_path,) = res
    bin_dir = os.path.join(os.path.split(self.__cache)[0], rel_path, 'p')

    if not os.path.isdir(bin_dir):
      raise IOError(f'cannot find installation directory for {recipe}/{version}: `{bin_dir}`')
    return bin_dir
  
  def __gen_out_dir(self, recipe: str, version: str) -> str:
    """Make out output directory for this specific package/version and return the path to it."""
    path = os.path.join(self.__out_dir, recipe, version)
    if 0 != subprocess.run(['mkdir', '-p', path]).returncode:
      raise IOError(f'failed to generate output directory: {path}')
    return path

  def __invoke_get_bc(self, file: str, dest: str) -> bool:
    """Run get-bc on file and send it to dest. Return whether successful"""
    run = subprocess.run(['get-bc', '-S', '-b', '-o', dest, file], capture_output=True, text=True)
    if run.returncode != 0:
      # We set this at level 2 because this should fail on most of the files in the directory
      self.__logger.log(2, f'get-bc failed on file `{file}`')
    return run.returncode == 0
  
  def __get_cache_path() -> str:
    """Return where the sqlite3 cache should be."""
    runinfo = subprocess.run(['conan', 'config', 'home'], capture_output=True, text=True)
    return os.path.join(runinfo.stdout.strip(), 'p', 'cache.sqlite3')