import json

class OutputJSON:
  def __init__(self):
    self.packages = []
  
  def add_package(self, name: str, version: str, bin_paths: list[str], metadata):
    package = {
      "pkg_name": name,
      "pkg_version": version,
      "bins": bin_paths,
      "metadata": metadata,
    }

    self.packages.append(package)
  
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