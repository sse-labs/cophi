#ifndef DELPHICPP_PACKAGESPARSER_HPP_
#define DELPHICPP_PACKAGESPARSER_HPP_

#include <core/binary.hpp>
#include <core/package.hpp>

#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using json = nlohmann::json;
namespace Utils {

Core::Package parsePackage(json &jpkg) {
  const std::string name = jpkg["pkg_name"];
  const std::string version = jpkg["pkg_version"];

  Core::Package pkg(std::make_shared<std::string>(name), 
                    std::make_shared<std::string>(version));

  // getting the binaries
  for (const json &e : jpkg["bins"]) {
    const std::string bin_name = e["bin_name"];
    const std::string bin_path = e["bin_path"];
    pkg.bins.emplace_back(std::make_shared<std::string>(bin_name), std::make_shared<std::string>(bin_path));
  }

  // TODO: grab the settings and stuff (ok to fail here)
  const json &metadata = jpkg["metadata"];

  // ADD ERROR CHECKING

  if (metadata.contains("settings")) {
    for (const auto &[k, v] : metadata["settings"].items()) {
      if (v.is_string()) {
        pkg.settings[k] = v;
      }
    }
  }

  if (metadata.contains("options")) {
    for (const auto &[k, v] : metadata["options"].items()) {
      if (v.is_string()) {
        pkg.settings[k] = v;
      }
    }
  }

  if (metadata.contains("requires")) {
    for (const auto &elem : metadata["requires"]) {
      if (elem.is_string()) {
        pkg.requires.push_back(elem);
      }
    }
  }

  return pkg;
}

bool parsePackages(const std::string &pkgs_file, std::vector<Core::Package> * const ret) {
  std::ifstream ifs(pkgs_file);

  if (!ifs.is_open()) {
    // log
    return false;
  }

  try {
    json arr = json::parse(ifs);

    //std::vector<Core::Package> res;
    for (auto &elem : arr) {
      ret->push_back(parsePackage(elem));
    }

    return true;
  } catch (const json::exception &e) {
    // log
    return false;
  }
}

}

#endif  // DELPHICPP_PACKAGESPARSER_HPP_
