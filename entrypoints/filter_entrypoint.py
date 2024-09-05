import argparse, subprocess, os
from vol_paths import paths

# CL Args
# parser = argparse.ArgumentParser()

# parser.add_argument('--map-file-name', '-m', dest='fm_name', help='name of the feature map file',
#                     type=str, required=True)
# parser.add_argument('--filter-file-name', '-f', dest='ff_name', help='name of the filter file',
#                     type=str, required=True)
# parser.add_argument('--output-name', '-o', dest='output_name', help='name of output file',
#                     type=str, required=True)
# parser.add_argument('--log_file_name', '-l', dest='log_name', help='name of log file',
#                     type=str, required=True)

def main():
  res = subprocess.run(['/DelphiCpp/build/dcpp_filter',
                        '-m', paths['ftr_map'],
                        '-f', paths['filters'],
                        '-o', paths['filtered_map'],
                        '-l', paths['log_file']])

  return res.returncode

main()