#include <utils/json_utils.hpp>
#include <core/binary.hpp>
#include <core/package.hpp>
#include <core/feature_query.hpp>
#include <core/feature_map.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using json = nlohmann::json;
namespace Utils {

// HELPERS

static Core::Package parsePackage(json &jpkg) {
  const std::string name = jpkg["pkg_name"];
  const std::string version = jpkg["pkg_version"];

  Core::Package pkg(std::make_shared<std::string>(name), 
                    std::make_shared<std::string>(version));

  // getting the binaries
  std::vector<Core::Binary> bins;
  for (const json &e : jpkg["bins"]) {
    const std::string bin_name = e["bin_name"];
    const std::string bin_path = e["bin_path"];
    bins.emplace_back(std::make_shared<std::string>(bin_name), std::make_shared<std::string>(bin_path));
  }
  pkg.setBins(std::move(bins));

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

static json convertLocs(const std::vector<Core::Location> &locs) {
  json arr = json::array();
  for (const auto &loc : locs) {
    json jloc = json::object();
    jloc["package_name"] = *loc.pkg_name;
    jloc["package_version"] = *loc.pkg_version;
    jloc["binary_name"] = *loc.bin_name;

    arr.push_back(jloc);
  }
  return arr;
}


// END HELPERS

bool parseCorpusAnalyzerConfig(std::ifstream &ifs, std::vector<std::string> queries) {
  try {
    json arr = json::parse(ifs);

    for (auto &elem : arr) {
      queries.push_back(elem);
    }

    return true;
  } catch (const json::exception &e) {
    spdlog::error("failed to parse packages from json: id={:d}, what=`{}`", e.id, e.what());
    return false;
  }
}

bool parsePackages(std::ifstream &ifs, std::vector<Core::Package> * const ret) {
  try {
    json arr = json::parse(ifs);

    for (auto &elem : arr) {
      ret->push_back(parsePackage(elem));
    }

    return true;
  } catch (const json::exception &e) {
    spdlog::error("failed to parse packages from json: id={:d}, what=`{}`", e.id, e.what());
    return false;
  }
}

std::string serializeFeatureMap(const Core::FeatureMap &fm) {
  // json arr = json::array();
  // // iterating through the feature id / locations pairs
  // for (const auto &[k, v] : fm) {
  //   json fid = json::object();
  //   fid["query_name"] = k.name();
  //   fid["feature_type"] = k.type();
  //   fid["locations"] = convertLocs(v);

  //   arr.push_back(fid);
  // }

  return "TODO"; //arr.dump(1, '\t');
}

}