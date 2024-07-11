#ifndef DELPHICPP_PACKAGEANALYZER_HPP_
#define DELPHICPP_PACKAGEANALYZER_HPP_

#include <core/package.hpp>
#include <core/feature_map.hpp>
#include <core/feature_query.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

namespace Core {

struct CorpusAnalyzerConfig {
  std::vector<std::string> query_subset;
};

class CorpusAnalyzer {
  public:
    CorpusAnalyzer(const CorpusAnalyzerConfig &conf);
    std::unique_ptr<FeatureMap> evaluate(const std::vector<Package> &pkgs) const;
  private:
    const CorpusAnalyzerConfig &_conf;
    std::vector<std::unique_ptr<Query>> _queries;
};
}

#endif  // DELPHICPP_PACKAGEANALYZER_HPP_