#ifndef DELPHICPP_PACKAGEANALYZER_HPP_
#define DELPHICPP_PACKAGEANALYZER_HPP_

#include <core/package.hpp>
#include <core/feature_map.hpp>
#include <core/feature_query.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

namespace Core {

// names of queries 
struct CorpusAnalyzerConfig {
  std::vector<std::string> query_subset;
};

// holds a set of queries to run on given packages and produce a FeatureMap
class CorpusAnalyzer {
  public:
    // given the config, will try to reify all the queries in it
    CorpusAnalyzer(const CorpusAnalyzerConfig &conf);

    // takes in packages and produces feature map
    //std::unique_ptr<FeatureMap> evaluate(std::vector<Package> &pkgs) const;
    void evaluate(std::vector<Package> &pkgs, FeatureMap &fm,
                  const std::chrono::minutes timeout) const;

  private:
    std::vector<Query*> getRawQueryPtrs() const;

    // all the reified queries
    std::vector<std::unique_ptr<Query>> _queries;
};

}

#endif  // DELPHICPP_PACKAGEANALYZER_HPP_