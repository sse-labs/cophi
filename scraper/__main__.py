import argparse, logging, os, yaml
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

parser.add_argument('--num-packages', '-n', required=True, dest='total',
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

def get_first_version(conf):
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

  num_tried = 0
  num_errored = 0
  num_more_zero = 0

  be = BitcodeExtractor(args.index, args.output, logger)
  for recipe in os.listdir(recipes):
    num_tried += 1
    try:
      version = get_first_version(os.path.join(recipes, recipe, 'config.yml'))
      num_more_zero += be.extract_bitcode(recipe, version, check_version=False)
      logger.info(f'{recipe}/{version} installed successfully with {num_more_zero} packages extracted')
    except Exception as exp:
      logger.warning(f'failure to extract bitcode from `{recipe}`: {exp}')
      num_errored += 1

    logger.info(f'{num_tried} packages attempted, {num_errored} errored, {num_more_zero}/{args.total} successful with >0 binaries')
    
    if num_more_zero == args.total:
      break

if __name__ == '__main__':
  main()