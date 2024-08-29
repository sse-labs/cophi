import argparse, subprocess, json

'''
Command Line Args
cl::opt<std::string> PackagesIndex("p", cl::Required, cl::desc("Path to packages index file"), cl::value_desc("path"));
cl::opt<std::string> AnalysisConfig("c", cl::Required, cl::desc("Path to query config file"), cl::value_desc("path"));
cl::opt<std::string> PrevFeatureMap("fm", cl::Required, cl::desc("Path to feature map file"), cl::value_desc("path"));
cl::opt<std::string> StatsFile("s", cl::Required, cl::desc("Path to stats file"), cl::value_desc("path"));

cl::opt<size_t> ChunkSize("cs", cl::Required, cl::desc(""),
                                             cl::value_desc(""));
cl::opt<size_t> PkgIndex("pi", cl::Required, cl::desc(""),
                                            cl::value_desc(""));

cl::opt<size_t> Timeout("t", cl::Required, cl::desc("How long to try to evaluate a package for"),
                                           cl::value_desc("duration in minutes"));
'''
parser = argparse.ArgumentParser(prog='partial_extract.py',
                                 description='extract features in chunks')

parser.add_argument('--pkgs-index', '-pi', dest='pkgs_index', type=str)
parser.add_argument('--config', '-c', dest='config', type=str)
parser.add_argument('--prev-fm', '-fm', dest='prev_fm', type=str)
parser.add_argument('--stats', '-s', dest='stats', type=str)

parser.add_argument('--chunk-size', '-cs', dest='chunk_size', type=int)
parser.add_argument('--pkg-start', '-ps', dest='pkg_start', type=int)
parser.add_argument('--timeout', '-t', dest='timeout', type=int)

def get_num_pkgs(pkgs_index):
  f = open(pkgs_index)
  arr = json.load(f)
  size = len(arr)
  f.close()
  return size

def init_fm(fm_file):
  f = open(fm_file, 'w+')
  f.write('[]')
  f.close()

def main():
  args = parser.parse_args()
  num_pkgs = get_num_pkgs(args.pkgs_index)

  init_fm(args.prev_fm)
  
  pkg_ind = args.pkg_start
  chunk_ind = 1
  while pkg_ind < num_pkgs:
    print(f'[info] starting chunk {str(chunk_ind)}')
    run_info = subprocess.run(['/workspaces/DelphiCpp/build/dcpp_partial_extract',
                               '-p', args.pkgs_index,
                               '-c', args.config,
                               '-fm', args.prev_fm,
                               '-s', args.stats + str(pkg_ind) + '.json',
                               '-cs', str(args.chunk_size),
                               '-pi', str(pkg_ind),
                               '-t', str(args.timeout)])
    if run_info.returncode != 0:
      print('[info] failed on chunk ' + str(chunk_ind))
    else:
      print(f'[info] finished chunk {str(chunk_ind)}')
    pkg_ind += args.chunk_size
    chunk_ind += 1

main()
