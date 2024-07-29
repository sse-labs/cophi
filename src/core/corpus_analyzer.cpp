#include <core/corpus_analyzer.hpp>
#include <core/feature_map.hpp>
#include <core/query_registry.hpp>

#include <spdlog/spdlog.h>

#include <algorithm>
#include <mutex>
#include <thread>

namespace Core {

// Helpers

std::mutex reifyEmplace;
void attemptReify(Package &pkg, std::vector<Package*> &reified_pkgs) {
  if (!pkg.reify()) {
    spdlog::warn("unable to reify package `{}`", pkg.getID().str());
  } else {
    reifyEmplace.lock();
    reified_pkgs.emplace_back(&pkg);
    reifyEmplace.unlock();
  }
}

void extractFeatures(Package const * const pkg,
                     Query const * const query,
                     FeatureMap * const ret)
{
  spdlog::trace("running query `{}` on package `{}`",
                query->getName(), pkg->getID().str());

  Query::Result results;
  query->runOn(pkg, &results);

  spdlog::debug("got {} features from running query `{}` on package `{}`",
                results.size(), query->getName(), pkg->getID().str());

  for (const Feature &res : results) {
    const auto id = res.getUniqueId();
    spdlog::debug("extracted {} locations from feature `{}`",
                  res.locs.size(), id.toString());
    
    // FeatureMap is thread-safe for insert
    ret->insert(pkg->getID(), res);
  }
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

void CorpusAnalyzer::evaluate(std::vector<Package> &pkgs, FeatureMap &fm, const size_t chunkSize) const {
  for (int i = 0; i < pkgs.size(); i += chunkSize) {
    const size_t end_ind = std::min(pkgs.size(), size_t(i + chunkSize));

    spdlog::info("reifing packages...");
    // store ptrs to sucessfully reified packages in here
    std::vector<Package*> reified_pkgs;
    //for (auto &pkg : pkgs) {
    for (int j = i; j < end_ind; j++) {
      attemptReify(pkgs[j], reified_pkgs);
    }
    spdlog::info("packages reified");

    for (const auto &query: _queries) {
      const std::string queryName = query->getName();
      spdlog::info("running {} on packages...", queryName);

      for (auto const * const pkg : reified_pkgs) {
        extractFeatures(pkg, query.get(), &fm);
      }
      spdlog::info("done running {} on packages", queryName);
    }

    for (int j = i; j < end_ind; j++) {
      pkgs[j].unreify();
    }
    spdlog::info("all queries done");
  }
}

void CorpusAnalyzer::parallelEvaluate(std::vector<Package> &pkgs, FeatureMap &fm, const size_t chunkSize) const {
  spdlog::info("reifing packages...");

  // store ptrs to sucessfully reified packages in here
  std::vector<Package*> reified_pkgs;
  std::vector<std::thread> pkgReifyThreads;
  for (auto &pkg : pkgs) {
    pkgReifyThreads.emplace_back(attemptReify, std::ref(pkg), std::ref(reified_pkgs));
  }
  for (auto &thrd : pkgReifyThreads) thrd.join();

  spdlog::info("packages reified");

  for (const auto &query: _queries) {
    const std::string queryName = query->getName();
    spdlog::info("running {} on packages...", queryName);

    std::vector<std::thread> extractFeaturesThreads;
    for (auto const * const pkg : reified_pkgs) {
      extractFeaturesThreads.emplace_back(extractFeatures, pkg, query.get(), &fm);
    }
    for (auto &thrd : extractFeaturesThreads) thrd.join();
    spdlog::info("done running {} on packages", queryName);
  }
  spdlog::info("all queries done");
}

} // namespace Core