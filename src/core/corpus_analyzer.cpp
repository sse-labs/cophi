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
                       std::vector<Query*> &queries,
                       Query::Result * const results,
                       std::shared_ptr<std::atomic_bool> terminate)
{
  bool ret = true;
  for (auto q : queries) {
    ret &= q->runOn(pkg, results, terminate);
  }
  return ret;
}

bool extractFeaturesFromPackage(Package const * const pkg,
                                std::vector<Query*> &queries,
                                FeatureMap * const ret,
                                const std::chrono::minutes timeout,
                                PackageStats::dur_t *time)
{
  Query::Result results;

  auto begin = std::chrono::steady_clock::now();
  bool success = Utils::run_queries_with_timeout(runQueriesWrapper, timeout, pkg, queries, &results,
                                                                    std::make_shared<std::atomic_bool>(false));
  auto end = std::chrono::steady_clock::now();

  *time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  if (!success) {
    spdlog::error("failed on package `{}`", pkg->getID().str());
    return false;
  }

  for (const Feature &res : results) {
    const auto id = res.getUniqueId();
    spdlog::debug("extracted feature `{}`", id.toString());
    
    ret->insert(pkg->getID(), res);
  }
  return true;
}

// End Helpers

CorpusAnalyzer::CorpusAnalyzer(const CorpusAnalyzerConfig &conf) {
  _queries = std::vector<std::unique_ptr<Query>>();
  const QueryRegistry &registry = QueryRegistry::singleton();

  for (const auto &query_name : conf.query_subset) {
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

    if (pkg.numBins() > _max_bins) {
      spdlog::warn("package `{}` exceeds maximum number of bins, skipping", pkg_name);
      num_failed += 1;
    } else if (!pkg.reify()) {
      spdlog::warn("unable to reify package `{}`, skipping", pkg_name);
      num_failed += 1;
    } else {
      spdlog::info("reified package `{}`", pkg_name);

      PackageStats::dur_t elapsed_time;
      did_not_detach_thread = extractFeaturesFromPackage(&pkg, raw_queries, &fm, timeout, &elapsed_time);

      // put stats in
      ret.insert({pkg.getID(), PackageStats(did_not_detach_thread, elapsed_time)});

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

jsonf CorpusAnalyzer::serializeStats(EvalStats &stats) {
  jsonf ret = jsonf::array();
  for (const auto &[k, v] : stats) {
    jsonf elem = jsonf::object();
    jsonf pkg_stats = jsonf::object();

    pkg_stats["successful"] = v.successful;
    pkg_stats["time_ns"] = v.time.count();

    elem[k.str()] = pkg_stats;

    ret.emplace_back(elem);
  }
  return ret;
}

} // namespace Core