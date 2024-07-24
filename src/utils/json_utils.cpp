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

static Core::Package parsePackage(const json &jpkg) {
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


// END HELPERS

bool parseCorpusAnalyzerConfig(const std::string &file, std::vector<std::string> queries) {
  std::ifstream ifs(file);
  if (!ifs) {
    return false;
  }

  try {
    json arr = json::parse(ifs);

    for (auto &elem : arr) {
      queries.push_back(elem);
    }

    return true;
  } catch (const json::exception &e) {
    spdlog::error("failed to parse packages from file {}. error: id={:d}, what=`{}`", file, e.id, e.what());
    return false;
  }
}

bool parsePackages(const std::string &file, std::vector<Core::Package> * const ret) {
  std::ifstream ifs(file);
  if (!ifs) {
    return false;
  }
  
  try {
    json arr = json::parse(ifs);

    for (const auto &elem : arr) {
      ret->push_back(parsePackage(elem));
    }

    return true;
  } catch (const json::exception &e) {
    spdlog::error("failed to parse packages from file {}. error: id={:d}, what=`{}`", file, e.id, e.what());
    return false;
  }
}

bool parseFilters(const std::string &file, std::vector<Core::Filter> * const filters) {
  std::ifstream ifs(file);
  if (!ifs) {
    return false;
  }

  try {
    json arr = json::parse(ifs);

    for (const auto &elem : arr) {
      filters->emplace_back(elem);
    }

    return true;
  } catch (const json::exception &e) {
    spdlog::error("failed to parse filters from file {}. error: id={:d}, what=`{}`", file, e.id, e.what());
    return false;
  }
}

std::unordered_set<Core::Feature> parseFeatureSet(const nlohmann::json &jftr_set) {
  return std::unordered_set<Core::Feature>(jftr_set.begin(), jftr_set.end());
}

std::unique_ptr<Core::FeatureMap> deserializeFeatureMap(const std::string &file) {
  std::ifstream ifs(file);
  if (!ifs) {
    return nullptr;
  }
  
  try {
    json jfm = json::parse(ifs);
    return std::make_unique<Core::FeatureMap>(jfm);
  } catch (const json::exception &e) {
    spdlog::error("failed to parse FeatureMap from file {}: id={:d}, what=`{}`", file, e.id, e.what());
    return nullptr;
  }
}

}