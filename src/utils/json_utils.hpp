#ifndef DELPHICPP_PACKAGESPARSER_HPP_
#define DELPHICPP_PACKAGESPARSER_HPP_

#include <core/package.hpp>
#include <core/feature_map.hpp>

#include <fstream>
#include <string>
#include <vector>

namespace Utils {

bool parseCorpusAnalyzerConfig(std::ifstream &in, std::vector<std::string> * const queries);
bool parsePackages(std::ifstream &in, std::vector<Core::Package> * const ret);
std::string serializeFeatureMap(const Core::FeatureMap &fm);

}

#endif  // DELPHICPP_PACKAGESPARSER_HPP_

