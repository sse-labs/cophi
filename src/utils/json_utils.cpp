#include <utils/json_utils.hpp>
#include <core/binary.hpp>
#include <core/package.hpp>
#include <core/feature_query.hpp>
#include <core/feature_map.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <fstream>
#include <memory>
#include <string>

namespace Utils {

std::unordered_set<Core::Feature> parseFeatureSet(const nlohmann::json &jftr_set) {
  return std::unordered_set<Core::Feature>(jftr_set.begin(), jftr_set.end());
}

std::unique_ptr<Core::FeatureMap> deserializeFeatureMap(const std::string &file) {
  std::ifstream ifs(file);
  if (!ifs) {
    return nullptr;
  }
  
  try {
    jsonf jfm = jsonf::parse(ifs);
    return std::make_unique<Core::FeatureMap>(jfm);
  } catch (const jsonf::exception &e) {
    spdlog::error("failed to parse FeatureMap from file {}: id={:d}, what=`{}`", file, e.id, e.what());
    return nullptr;
  }
}

}