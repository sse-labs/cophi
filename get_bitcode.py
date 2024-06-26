import argparse, sqlite3, subprocess, os, yaml

parser = argparse.ArgumentParser(prog='get_bitcode.py',
                                 description='Extract LLVM bitcode from a Conan recipe.')

# Command Line Args
parser.add_argument('--conan-index', '-ci', default='/conan-center-index/', dest='index',
                    help='path to local conan center index')

parser.add_argument('--output', '-o', required=True, dest='output',
                    help='which directory to output the metadata/bitcode to')

parser.add_argument('--recipe', '-r', required=True, dest='recipe',
                    help='the recipe in the conan-center-index to build')

parser.add_argument('--version', '-v', required=True, dest='version',
                    help='the specific version of the recipe')

class BitcodeExtractor:
  """
  A class which builds desired conan packages from a local conan-center clone 
  and extracts the LLVM bitcode from their binaries, as well as their .h files

  TODO:
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

  def __init__(self, conan_index, output_folder):
    self.__index_dir = conan_index
    self.__out_dir = output_folder
    self.__cache = BitcodeExtractor.__get_cache_path()
  
  def extract_bitcode(self, recipe, version, cascade=True):
    conf_path = self.__get_conf_file_path(recipe)
    if not BitcodeExtractor.__version_exists(conf_path, version):
      raise IOError(f'version {version} does not exist for recipe {recipe}')
    if self.__run_install(recipe, version) != 0:
      raise RuntimeError(f'failed to install {recipe}/{version}')
    self.__write_bitcode(recipe, version)
  
  def __get_conf_file_path(self, recipe):
    conf_path = os.path.join(self.__index_dir, 'recipes', recipe, 'config.yml')
    if not os.path.isfile(conf_path):
      raise IOError(f'recipe {recipe} does not exist in conan-center-index')
    return conf_path
  
  def __version_exists(conf_path, version):
    conf_file = open(conf_path, 'r')
    conf_parsed = yaml.safe_load(conf_file)
    conf_file.close()

    versions = conf_parsed['versions'].keys()
    return version in versions

  def __run_install(self, recipe, version):
    run_info = subprocess.run(['conan', 'install',
                              f'--requires={recipe}/{version}',
                              '--build=*',
                              '--settings:all=build_type=Debug',
                              f'--conf:all=tools.build:compiler_executables={self.__compiler_executables}',
                              '--remote=conan-index',
                              f'--output-folder={os.path.join(self.__index_dir, recipe, 'all/build/')}'])
    return run_info.returncode
  
  # TODO: some recipes may have stuff in their metadata folder, check for that
  # to get it: `conan cache path --folder=metadata <recipe>/<version>`
  def __write_bitcode(self, recipe, version):
    package_folder = self.__get_package_dir(recipe, version)

    for outtype in ['bin', 'lib', 'include']:
      curr_folder = os.path.join(package_folder, outtype)
      if not os.path.isdir(curr_folder):
        continue

      suboutdir = os.path.join(self.__out_dir, recipe, version, outtype)
      subprocess.run(['mkdir', '-p', suboutdir])

      match outtype:
        case 'bin':
          for executable in os.listdir(curr_folder):
            binfile = os.path.join(curr_folder, executable)
            outfile = os.path.join(suboutdir, executable + '.bc')
            subprocess.run(['get-bc', '-S', '-o', outfile, binfile])
        case 'lib':
          for library in os.listdir(curr_folder):
            libfile = os.path.join(curr_folder, library)
            outfile = os.path.join(suboutdir, library + '.bc')
            subprocess.run(['get-bc', '-S', '-b', '-o', outfile, libfile])
        case 'include':
          subprocess.run(['cp', '-r', curr_folder, os.path.join(self.__out_dir, f'{recipe}_{version}')])
  
  def __get_package_dir(self, recipe, version):
    if not os.path.isfile(self.__cache):
      raise IOError('cannot find `cache.sqlite3` in local conan cache')
    
    con = sqlite3.connect(self.__cache)
    cur = con.cursor()

    recipe_ref = f'{recipe}/{version}'
    res = cur.execute("""SELECT path FROM packages 
                            WHERE reference=?
                            ORDER BY timestamp DESC""", (recipe_ref,)).fetchone()
    con.close()

    if res is None:
      raise RuntimeError(f'cannot find `{recipe_ref}` in local conan cache database')
    (rel_path,) = res
    return os.path.join(os.path.split(self.__cache)[0], rel_path, 'p')
  
  def __get_cache_path():
    runinfo = subprocess.run(['conan', 'config', 'home'], capture_output=True, text=True)
    return os.path.join(runinfo.stdout.strip(), 'p', 'cache.sqlite3')


def main():
  try:
    args = parser.parse_args()
    be = BitcodeExtractor(args.index, args.output)
    be.extract_bitcode(args.recipe, args.version)
  except Exception as exp:
    print(f'ERROR: {exp}')

main()