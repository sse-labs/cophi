#ifndef DELPHICPP_PACKAGESPARSER_HPP_
#define DELPHICPP_PACKAGESPARSER_HPP_

#include <core/package.hpp>
#include <core/feature_map.hpp>
#include <core/filter.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <fstream>
#include <string>
#include <memory>
#include <vector>

namespace Utils {

// throws on malformed json
std::unordered_set<Core::Feature> parseFeatureSet(const jsonf &jftr_set);

// attempt to parse FeatureMap from JSON from the ifstream, returns nullptr on error
std::unique_ptr<Core::FeatureMap> deserializeFeatureMap(const std::string &file);

// parses a json file containing an array of some type.
// T must have a ctor of the form `T(const nlohmann::json&)`
//
// emplaces parsed elements on the back of queries
// returns false if the entire array was not able to be parsed or the file
// not able to be opened
template<class T>
bool parseJSONArray(const std::string &file, std::vector<T> * const queries) {
  std::ifstream ifs(file);
  if (!ifs) {
    return false;
  }

  try {
    jsonf arr = jsonf::parse(ifs);

    for (auto &elem : arr) {
      queries->emplace_back(elem);
    }

    return true;
  } catch (const jsonf::exception &e) {
      char const * type = typeid(T).name();
      spdlog::error("failed to parse array of {} from file {}. error: id={:d}, what()=`{}`",
                    type, file, e.id, e.what());
    return false;
  }
}

}

#endif  // DELPHICPP_PACKAGESPARSER_HPP_

