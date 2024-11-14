#include <core/corpus_analyzer.hpp>
#include <core/feature_map.hpp>
#include <core/query_registry.hpp>
#include <core/globals/globals.hpp>
#include <utils/multithreading_utils.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <chrono>
#include <algorithm>
#include <mutex>
#include <thread>

#include <iostream>

namespace Core {

// Helpers

// need this because Utils::run_with_timeout() doesn't play well with member functions
bool runQueriesWrapper(Package const * const pkg,
                       Query* query,
                       Query::Result * const results,
                       std::shared_ptr<std::atomic_bool> terminate)
{
  return query->runOn(pkg, results, terminate);
}

void extractFeaturesFromPackage(Package const * const pkg,
                                std::vector<Query*> &queries,
                                FeatureMap * const ret,
                                const std::chrono::minutes timeout,
                                PackageStats *stats)
{
  stats->successful = true;
  Query::Result results;

  for (auto *query : queries) {
    Query::Result partial_res;

    auto begin = std::chrono::steady_clock::now();
    const bool res = Utils::run_query_with_timeout(runQueriesWrapper, timeout, pkg, query, &partial_res,
                                                   std::make_shared<std::atomic_bool>(false));
    auto end = std::chrono::steady_clock::now();

    if (!res) {  
      stats->successful = false;                                              
      spdlog::error("query {} timed out on package `{}`", query->getName(), pkg->getID().str());
      break;
    } else {
      PackageStats::dur_t time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

      stats->timings[query->getName()] = time;
      results.insert(partial_res.begin(), partial_res.end());
    }
  }
  

  //*time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  for (const Feature &res : results) {
    const auto id = res.getUniqueId();
    spdlog::debug("extracted feature `{}`", id.toString());
    
    ret->insert(pkg->getID(), res);
  }
}

// End Helpers

CorpusAnalyzer::CorpusAnalyzer(const CorpusAnalyzerConfig &conf) : _config(conf) {
  _queries = std::vector<std::unique_ptr<Query>>();
  const QueryRegistry &registry = QueryRegistry::singleton();

  for (const auto &query_name : _config.query_subset) {
    spdlog::trace("reifying query `{}`", query_name);
    auto reified_query = registry.getInstanceOf(query_name);
    if (!reified_query) {
      spdlog::warn("query `{}` does not exist, skipping", query_name);
      continue;
    }
    spdlog::trace("reified query `{}`", query_name);
    _queries.push_back(std::move(reified_query));
  }
  spdlog::info("queries reified");
}

CorpusAnalyzer::EvalStats CorpusAnalyzer::evaluate(std::vector<Package> &pkgs, FeatureMap &fm,
                                                    const std::chrono::minutes timeout) const {
  EvalStats ret;
  size_t total_pkgs = pkgs.size();
  size_t num_done = 0;
  size_t num_failed = 0;

  auto raw_queries = this->getRawQueryPtrs();

  for (Package &pkg : pkgs) {
    const std::string pkg_name = pkg.getID().str();
    spdlog::info("attempting to reify package `{}`", pkg_name);

    bool did_not_detach_thread = true;

    if (pkg.numBins() > _config.max_bins) {
      spdlog::warn("package `{}` exceeds maximum number of bins, skipping", pkg_name);
      num_failed += 1;
    } else if (!pkg.reify()) {
      spdlog::warn("unable to reify package `{}`, skipping", pkg_name);
      num_failed += 1;
    } else {
      spdlog::info("reified package `{}`", pkg_name);

      PackageStats stats;
      extractFeaturesFromPackage(&pkg, raw_queries, &fm, timeout, &stats);

      did_not_detach_thread = stats.successful;

      // put stats in
      ret.insert({pkg.getID(), stats}); //PackageStats(did_not_detach_thread, elapsed_time)});

      if (did_not_detach_thread) num_done += 1;
      else num_failed += 1;
    }
    if (did_not_detach_thread) { pkg.unreify(); }
    spdlog::info("successfully evaluated {:d}/{:d} packages, failed on {:d}", num_done, total_pkgs, num_failed);
  }
  return ret;
}

std::vector<Query*> CorpusAnalyzer::getRawQueryPtrs() const {
  std::vector<Query*> ret;
  for (auto &q : _queries) {
    ret.emplace_back(q.get());
  }
  return ret;
}

jsonf CorpusAnalyzer::serializeStats(jsonf &prev, EvalStats &stats) {
  jsonf ret = prev;
  for (const auto &[k, v] : stats) {
    jsonf elem = jsonf::object();
    jsonf pkg_stats = jsonf::object();

    pkg_stats["successful"] = v.successful;

    jsonf timings = jsonf::object();
    for (const auto &[k, v] : v.timings) {
      timings[k] = v.count();
    }
    pkg_stats["timings"] = timings;

    elem[k.str()] = pkg_stats;

    ret.emplace_back(elem);
  }
  return ret;
}

} // namespace Core