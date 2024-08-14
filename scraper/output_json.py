import json

class OutputJSON:
  def __init__(self, logger, prev_pkgs_file: None|str=None):
    self.packages = []
    self.__logger = logger

    if prev_pkgs_file is not None:
      self.__parse_existing_packages(prev_pkgs_file)
  
  def add_package(self, name: str, version: str, bin_paths: list[str], metadata):
    package = {
      "pkg_name": name,
      "pkg_version": version,
      "bins": bin_paths,
      "metadata": metadata,
    }

    self.packages.append(package)

  def __parse_existing_packages(self, pkgs_file: str):
    f = open(pkgs_file)

    try:
      pkgs = json.load(f)

      # check everything is there
      for pkg in pkgs:
        if ('pkg_name' not in pkg or
            'pkg_version' not in pkg or
            'bins' not in pkg or
            'metadata' not in pkg):
            raise Exception('malformed packages file')

      self.packages = pkgs
    except Exception:
      self.packages = []
      self.__logger.warning(f'packages file unable to be parsed')
    
    f.close()
  
def get_metadata(conan_metadata_file):
  try:
    infos = find_values('info', conan_metadata_file)
    return infos[0]
  except Exception as _:
    return {}

# copied from: https://stackoverflow.com/a/14059645/26033272
def find_values(id, json_repr):
    results = []

    def _decode_dict(a_dict):
        try:
            results.append(a_dict[id])
        except KeyError:
            pass
        return a_dict

    json.loads(json_repr, object_hook=_decode_dict) # Return value ignored.
    return results