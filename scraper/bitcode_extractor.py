import os, subprocess, yaml
from logging import Logger
from scraper.package_cache import ConanCache

class BitcodeExtractor:
  """Builds desired conan2 packages from a local conan-center clone 
  and extracts the LLVM bitcode from their binaries.

  TODO:
    * add methods for clearing the local cache and pulling from the repo
    * extract more metadata (like what though?)
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
    db_path = BitcodeExtractor.__get_cache_path()
    # wrapper around db in local conan cache
    self.__cache: ConanCache = ConanCache(db_path, logger)

    # set of packages we've tried to install (strings should be `recipe/version`)
    self.__set_tried: set[str] = set()
  
  def extract_bitcode(self, recipe: str, version: str, check_version: bool = True) -> bool:
    """Attempts to install a a given package/version, and returns how many 
    packages were scraped for >0 bitcode files. Raises exeptions on failure.
    
    Args:
      recipe: The recipe to try and install.
      version: The specific version of the recipe.
      check_version: whether to check if the version exists before trying to install.
    
    Returns:
      The number of packages successfully scraped for >0 bitcode files.

    Raises:
      IOError: If a necessary file wasn't found, or failure to make a file.
    """
    if check_version:
      # get the config.yml path which contains all versions for a package
      conf_path = self.__get_conf_file_path(recipe)

      # error if version not found
      if not BitcodeExtractor.__version_exists(conf_path, version):
        raise IOError(f'version {version} does not exist for recipe {recipe}')
      
    # run 'conan install ...' on the package. This function takes the lion's share of the time
    if not self.__run_install(recipe, version):
      return False

    # if run_install() didn't fail, we get the directory where the binaries were installed and write them out
    package_folder = self.__cache.get_package_dir(recipe, version)
    if package_folder is None:
      raise RuntimeError(f'could not find {recipe}/{version} in database even after successful installation')
    return self.__write_bitcode(package_folder, recipe, version)
  
  def extract_from_deps(self) -> int:
    all_packages = self.__cache.get_package_set()

    if all_packages is None:
      self.__logger.warning('failed to get set of packages from cache')
      return 0
    
    not_tried = all_packages.difference(self.__set_tried)

    num_successful = 0
    for package in not_tried:
      (recipe, _, version) = package.partition('/')
      package_folder = self.__cache.get_package_dir(recipe, version)
      if self.__write_bitcode(package_folder, recipe, version):
        num_successful += 1
    
    return num_successful

  
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

  def __run_install(self, recipe: str, version: str) -> bool:
    """Attempt to install the given recipe/version. Return whether successful

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
                              # set the cpp standard at 17, as that's the highest standard llvm 14 fully supports
                              '--settings:all=compiler.cppstd=gnu17',
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
      self.__logger.warning(f'conan install failed for {recipe}/{version}')
      self.__logger.debug('conan install output: \n\t\t' + run_info.stderr.replace('\n', '\n\t\t'))
      return False
    self.__logger.info('conan install successful')
    return True
  
  def __write_bitcode(self, package_folder: str, recipe: str, version: str) -> bool:
    """Given the build folder for a package, extract all possible bitcode files and 
    write them out to the output folder. Return how many bitcode files extracted.

    Args:
      package_folder: The folder with all the binaries for this package version.
      recipe: The name of the recipe we installed.
      version: the version of the package we installed.
    
    Returns:
      Whether or not >0 bitcode files were written out.

    TODO:
      some recipes may have stuff in their metadata folder, check for that
      to get it: `conan cache path --folder=metadata <recipe>/<version>`
    """
    out_folder = self.__gen_out_dir(recipe, version)
    num_written = 0

    self.__set_tried.add(f'{recipe}/{version}')

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
    
    if num_written == 0:
      self.__remove_out_dir(recipe, version)
    
    return num_written > 0
  
  def __gen_out_dir(self, recipe: str, version: str) -> str:
    """Make out output directory for this specific package/version and return the path to it."""
    path = os.path.join(self.__out_dir, recipe, version)
    if 0 != subprocess.run(['mkdir', '-p', path]).returncode:
      raise IOError(f'failed to generate output directory: {path}')
    return path
  
  def __remove_out_dir(self, recipe: str, version: str):
    recipe_dir = os.path.join(self.__out_dir, recipe)
    version_dir = os.path.join(self.__out_dir, recipe, version)
    if 0 != subprocess.run(['rmdir', version_dir, recipe_dir]).returncode:
      self.__logger.warning(f'failed to delete empty directory: {version_dir}')

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