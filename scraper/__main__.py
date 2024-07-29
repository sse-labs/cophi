import argparse, logging, os, random, yaml
from scraper.bitcode_extractor import BitcodeExtractor

##############################
# Setting Command Line Flags #
##############################
parser = argparse.ArgumentParser(prog='test_extract.py',
                                 description='test get_bitcode.py')

parser.add_argument('--conan-index', '-i', default='/conan-center-index/', dest='index',
                    help='path to local conan center index')

# TODO: change default to docker volume
parser.add_argument('--output', '-o', default='./bitcode/', dest='output',
                    help='which directory to output the metadata/bitcode to')

parser.add_argument('--num-packages', '-n', required=True, dest='total', type=int,
                    help='how many packages to install (with no errors and >0 bitcode files)')

#####################
# Setting Up Logger #
##################### TODO: you can just put all this in a config file, do that
logger = logging.getLogger('bitcode_scraper')
logger.setLevel(logging.DEBUG)

# configure handler for console output
ch = logging.StreamHandler()
ch.setLevel(logging.INFO)
ch.setFormatter(logging.Formatter('%(levelname)s: %(message)s'))
logger.addHandler(ch)

# configure handler for file output
fh = logging.FileHandler('./scraper/logs/scraper.log', 'w', 'utf-8')
fh.setLevel(logging.DEBUG)
fh.setFormatter(logging.Formatter('%(levelname)s: %(message)s'))
logger.addHandler(fh)

def get_packages_already_scraped(bitcode_dir: str) -> set[str]:
  if not os.path.isdir(bitcode_dir):
    return set()

  ret = set()
  for package in os.listdir(bitcode_dir):
    package_dir = os.path.join(bitcode_dir, package)
    if os.path.isdir(package_dir):
      for version in os.listdir(package_dir):
        ret.add(package + '/' + version)
  return ret

def get_first_version(conf):
  """Given a `config.yml` file for a recipe, extract the first version listed in it.
  Raise an error if it has no versions.
  """
  conf_file = open(conf, 'r')
  conf_parsed = yaml.safe_load(conf_file)
  conf_file.close()

  versions = conf_parsed['versions'].keys()
  if not versions:
    raise RuntimeError('recipe has no versions')
  return next(iter(versions))

def main():
  args = parser.parse_args()
  recipes = os.path.join(args.index, 'recipes')
  already_scraped = get_packages_already_scraped(args.output)

  num_errored = 0
  num_scraped = len(already_scraped)

  be = BitcodeExtractor(args.index, args.output, already_scraped, logger)

  # go through recipes in a random order
  recipe_dirs = os.listdir(recipes)
  random.shuffle(recipe_dirs)
  for recipe in recipe_dirs:
    exit = False

    try:
      version = get_first_version(os.path.join(recipes, recipe, 'config.yml'))
      if be.have_tried_extracting(recipe, version):
        logger.info(f"skipping {recipe}/{version}, already tried to extract")
        continue
      elif be.extract_bitcode(recipe, version, check_version=False):
        num_scraped += 1
        logger.info(f'{recipe}/{version} installed successfully')
      else:
        logger.warning(f'{recipe}/{version} failed to install')
        num_errored += 1
    except Exception as exp:
      logger.error(f'unexpected error trying to extract bitcode from `{recipe}/{version}`: {exp}')
      num_errored += 1
    except KeyboardInterrupt:
      exit = True

    logger.info('going though dependencies')
    n = be.extract_from_deps()
    logger.info(f'{n} packages gotten from deps')
    num_scraped += n

    logger.info(f'{num_scraped} packages successful, {num_errored} packages errored')
    
    # get rid of everything in the local cache
    be.destroy_local_cache()
    if num_scraped >= args.total or exit:
      break
  
  be.dump_output_json()

if __name__ == '__main__':
  main()