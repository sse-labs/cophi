import argparse, shutil, sqlite3, subprocess, os, yaml

# parser = argparse.ArgumentParser(prog='get_bitcode.py',
#                                  description='Extract LLVM bitcode from a Conan recipe.')

# # Command Line Args
# parser.add_argument('--conan-index', '-ci', default='/conan-center-index/', dest='index',
#                     help='path to local conan center index')

# parser.add_argument('--output', '-o', required=True, dest='output',
#                     help='which directory to output the metadata/bitcode to')

# parser.add_argument('--recipe', '-r', required=True, dest='recipe',
#                     help='the recipe in the conan-center-index to build')

# parser.add_argument('--version', '-v', required=True, dest='version',
#                     help='the specific version of the recipe')

class BitcodeExtractor:
  """
  A class which builds desired conan packages from a local conan-center clone 
  and extracts the LLVM bitcode from their binaries, as well as their .h files

  TODO:
    * first priority: test on a bunch of recipes
    * add option dependencies get their bitcode extracted as well
    * extract more metadata (like what though?)
    * keep the connection to the database open the whole time?
      - it doesn't exist at first though, and it's updated with each new package
    * make good comments on the methods and stuff
    * add more robust error checking
    * see if you can change flags on conan install to not install binaries if already there
      - might be slightly tricky with dependency stuff
  """

  # a record we pass into a `conan install` flag so it compiles using gllvm
  __compiler_executables = {
            "c": "gclang",
            "cpp": "gclang++",
        }

  def __init__(self, conan_index, output_folder, logger):
    self.__index_dir = conan_index
    self.__out_dir = output_folder
    self.__logger = logger
    self.__cache = BitcodeExtractor.__get_cache_path()
  
  def extract_bitcode(self, recipe, version, cascade=True, check_version=True):
    conf_path = self.__get_conf_file_path(recipe)
    if check_version and not BitcodeExtractor.__version_exists(conf_path, version):
      self.__logger.debug(f'could not find version {version} for {recipe}')
      raise IOError(f'version {version} does not exist for recipe {recipe}')
    self.__run_install(recipe, version)
    return self.__write_bitcode(recipe, version)
  
  def __get_conf_file_path(self, recipe):
    conf_path = os.path.join(self.__index_dir, 'recipes', recipe, 'config.yml')
    if not os.path.isfile(conf_path):
      self.__logger.debug(f'conf file for package not found: {conf_path}')
      raise IOError(f'recipe {recipe} does not exist in conan-center-index')
    return conf_path
  
  def __version_exists(conf_path, version):
    conf_file = open(conf_path, 'r')
    conf_parsed = yaml.safe_load(conf_file)
    conf_file.close()

    versions = conf_parsed['versions'].keys()
    return version in versions

  def __run_install(self, recipe, version):
    self.__logger.info(f'started conan install for {recipe}/{version}')
    run_info = subprocess.run(['conan', 'install',
                               # specify which package/version to install (we use this instead of the path to conanfile.py because that doesn't always work)
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
  
  # TODO: some recipes may have stuff in their metadata folder, check for that
  # to get it: `conan cache path --folder=metadata <recipe>/<version>`
  def __write_bitcode(self, recipe, version):
    package_folder = self.__get_package_dir(recipe, version)
    out_folder = self.__gen_out_dir(recipe, version)

    num_written = 0

    for root, _, files in os.walk(package_folder):
      for file in files:
        file = os.path.join(root, file)
        out_file = os.path.join(out_folder, file + '.bc')
        if self.__invoke_get_bc(file, out_file):
          num_written += 1
    
    return num_written
  
  def __get_package_dir(self, recipe, version):
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
      self.__logger.debug(f'contents of table packages in `cache.sqlite3`: \n{'\n'.join(cur.execute('SELECT * FROM packages').fetchall())}'.replace('\n', '\n\t\t'))
      con.close()
      raise RuntimeError(f'cannot find `{recipe_ref}` in local conan cache database')
    con.close()
    (rel_path,) = res
    return os.path.join(os.path.split(self.__cache)[0], rel_path, 'p')
  
  def __gen_out_dir(self, recipe, version):
    path = os.path.join(self.__out_dir, recipe, version)
    if 0 != subprocess.run(['mkdir', '-p', path]).returncode:
      raise RuntimeError(f'failed to generate output directory: {path}')
    return path

  def __invoke_get_bc(self, file, dest):
    run = subprocess.run(['get-bc', '-S', '-b', '-o', dest, file], capture_output=True, text=True)
    if run.returncode != 0:
      self.__logger.log(2, f'get-bc failed on file `{file}`')
    return run.returncode == 0
  
  def __get_cache_path():
    runinfo = subprocess.run(['conan', 'config', 'home'], capture_output=True, text=True)
    return os.path.join(runinfo.stdout.strip(), 'p', 'cache.sqlite3')


# def main():
#   try:
#     args = parser.parse_args()
#     be = BitcodeExtractor(args.index, args.output)
#     be.extract_bitcode(args.recipe, args.version)
#   except Exception as exp:
#     print(f'ERROR: {exp}')

# main()