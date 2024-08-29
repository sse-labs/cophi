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
#include <filesystem>
namespace fs = std::filesystem;

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

bool parsePackages(const std::string &file, std::vector<Core::Package> * const pkgs, const size_t chunkSize, const size_t ind) {
  std::ifstream ifs(file);
  if (!ifs) {
    return false;
  }

  fs::path index_path(file);

  try {
    jsonf arr = jsonf::parse(ifs);

    size_t end = std::min(ind + chunkSize, arr.size());
    for (size_t i = ind; i < end; i++) { 
      pkgs->emplace_back(index_path, arr[i]);
    }

    return true;
  } catch (const jsonf::exception &e) {
      spdlog::error("failed to parse array of Packages from file {}. error: id={:d}, what()=`{}`",
                    file, e.id, e.what());
    return false;
  }
}

}