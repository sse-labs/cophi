#ifndef DELPHICPP_PACKAGEANALYZER_HPP_
#define DELPHICPP_PACKAGEANALYZER_HPP_

#include <core/package.hpp>
#include <core/feature_map.hpp>
#include <core/feature_query.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <chrono>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Core {

// names of queries 
struct CorpusAnalyzerConfig {
  // the number of packages to process at a time before saving
  size_t chunk_size;
  // how long to spend evaluating a package before timing out
  size_t timeout_mins;
  // the max number of bins a package can have (we skip over it otherwise)
  size_t max_bins;
  // the queries we run on the packages
  std::vector<std::string> query_subset;
};

struct PackageStats {
  using dur_t = std::chrono::nanoseconds;
  PackageStats(bool s, dur_t t) : successful(s), time(t) { }

  bool successful;
  dur_t time;
};

// holds a set of queries to run on given packages and produce a FeatureMap
class CorpusAnalyzer {
  public:
    using EvalStats = std::unordered_map<PackageID, PackageStats>;

    // given the config, will try to reify all the queries in it
    CorpusAnalyzer(const CorpusAnalyzerConfig &conf);

    // takes in packages and produces feature map
    //std::unique_ptr<FeatureMap> evaluate(std::vector<Package> &pkgs) const;
    EvalStats evaluate(std::vector<Package> &pkgs, FeatureMap &fm,
                       const std::chrono::minutes timeout) const;
    
    static jsonf serializeStats(EvalStats &stats);

  private:
    std::vector<Query*> getRawQueryPtrs() const;

    // all the reified queries
    std::vector<std::unique_ptr<Query>> _queries;
    const CorpusAnalyzerConfig _config;
};

}

#endif  // DELPHICPP_PACKAGEANALYZER_HPP_