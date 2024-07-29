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
    void evaluate(std::vector<Package> &pkgs, FeatureMap &fm, const size_t chunkSize) const;

    // same as above, but with multithreading
    //std::unique_ptr<FeatureMap> parallelEvaluate(std::vector<Package> &pkgs) const;

    void parallelEvaluate(std::vector<Package> &pkgs, FeatureMap &fm, const size_t chunkSize) const;
  private:
    // all the reified queries
    std::vector<std::unique_ptr<Query>> _queries;
};
}

#endif  // DELPHICPP_PACKAGEANALYZER_HPP_