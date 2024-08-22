#include <core/corpus_analyzer.hpp>
#include <core/feature_map.hpp>
#include <core/query_registry.hpp>
#include <core/globals/globals.hpp>
#include <utils/multithreading_utils.hpp>

#include <spdlog/spdlog.h>

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
                                const std::chrono::minutes timeout)
{
  // spdlog::info("running query `{}` on package `{}`",
  //               query->getName(), pkg->getID().str());

  Query::Result results;

  //query->runOn(pkg, &results);
  if (!Utils::run_queries_with_timeout(runQueriesWrapper, timeout, pkg, queries, &results,
                                                    std::make_shared<std::atomic_bool>(false))) {
    spdlog::error("failed on package `{}`", pkg->getID().str());
    return false;
  }

 
  // spdlog::info("finished running query `{}` on package `{}`",
  //               query->getName(), pkg->getID().str());

  // spdlog::debug("got {} features from running query `{}` on package `{}`",
  //               results.size(), query->getName(), pkg->getID().str());

  for (const Feature &res : results) {
    const auto id = res.getUniqueId();
    spdlog::debug("extracted feature `{}`", id.toString());
    
    // FeatureMap is thread-safe for insert
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

void CorpusAnalyzer::evaluate(std::vector<Package> &pkgs, FeatureMap &fm,
                              const std::chrono::minutes timeout) const {
  size_t total_pkgs = pkgs.size();
  size_t num_done = 0;
  size_t num_failed = 0;

  auto raw_queries = this->getRawQueryPtrs();

  for (Package &pkg : pkgs) {
    const std::string pkg_name = pkg.getID().str();
    spdlog::info("attempting to reify package `{}`", pkg_name);

    bool not_failed_eval = true;

    if (!pkg.reify()) {
      spdlog::warn("unable to reify package `{}`, skipping", pkg_name);
      num_failed += 1;
    } else {
      spdlog::info("reified package `{}`", pkg_name);
      not_failed_eval = extractFeaturesFromPackage(&pkg, raw_queries, &fm, timeout);
      // for (const auto &qry : _queries) {
      //   // if (failed) {
      //   //   num_failed++;
      //   //   break;
      //   // }
      //   not_failed &= extractFeatures(&pkg, qry.get(), &fm);
      // }
      if (not_failed_eval) num_done += 1;
      else num_failed += 1;
    }
    if (not_failed_eval) { pkg.unreify(); }
    spdlog::info("successfully evaluated {:d}/{:d} packages, failed on {:d}", num_done, total_pkgs, num_failed);
  }
}

std::vector<Query*> CorpusAnalyzer::getRawQueryPtrs() const {
  std::vector<Query*> ret;
  
  std::cerr << "here\n";
  // std::transform(_queries.begin(), _queries.end(), ret.begin(), [](auto &q) {
  //   return q.get();
  // });

  for (auto &q : _queries) {
    ret.emplace_back(q.get());
  }
  std::cerr << "here2\n";

  return ret;
}

} // namespace Core