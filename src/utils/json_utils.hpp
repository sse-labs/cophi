#ifndef DELPHICPP_PACKAGESPARSER_HPP_
#define DELPHICPP_PACKAGESPARSER_HPP_

#include <core/package.hpp>
#include <core/feature_map.hpp>
#include <core/filter.hpp>

#include <nlohmann/json.hpp>

#include <string>
#include <memory>
#include <vector>

namespace Utils {


bool parseCorpusAnalyzerConfig(const std::string &file,
                               std::vector<std::string> * const queries);
bool parseFilters(const std::string &file, 
                  std::vector<Core::Filter> * const filters);
bool parsePackages(const std::string &file,
                   std::vector<Core::Package> * const ret);

// throws on malformed json
std::unordered_set<Core::Feature> parseFeatureSet(const nlohmann::json &jftr_set);

// attempt to parse FeatureMap from JSON from the ifstream, returns nullptr on error
std::unique_ptr<Core::FeatureMap> deserializeFeatureMap(const std::string &file);

}

#endif  // DELPHICPP_PACKAGESPARSER_HPP_

