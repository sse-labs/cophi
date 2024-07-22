#include <core/corpus_analyzer.hpp>
#include <core/feature_map.hpp>
#include <core/query_registry.hpp>

#include <spdlog/spdlog.h>


namespace Core {

CorpusAnalyzer::CorpusAnalyzer(const CorpusAnalyzerConfig &conf) {
  _queries = std::vector<std::unique_ptr<Query>>();
  const QueryRegistry &registry = QueryRegistry::singleton();

  spdlog::info("reifying queries...");
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
  spdlog::info("queries reified.");
}

std::unique_ptr<FeatureMap> CorpusAnalyzer::evaluate(std::vector<Package> &pkgs) const {
  // might wanna add concurrency here
  spdlog::info("start reifying packages...");
  // store ptrs to sucessfully reified packages in here
  std::vector<Package*> reified_pkgs;
  for (auto &pkg : pkgs) {
    if (!pkg.isReified() && !pkg.reifySelf()) {
      spdlog::warn("unable to reify package `{}`", *pkg.name);
    } else {
      reified_pkgs.emplace_back(&pkg);
    }
  }
  spdlog::info("done reifying packages.");

  // add concurrency here
  auto ret = std::make_unique<FeatureMap>();

  spdlog::info("starting to run queries...");
  for (const auto &query: _queries) {
    for (const auto *pkg_ptr : reified_pkgs) {
      const auto pkg = *pkg_ptr;
      spdlog::trace("running query `{}` on package `{}/{}`", query->getName(), *pkg.name, *pkg.version);

      Query::Result results;
      query->runOn(pkg, &results);

      spdlog::debug("got {} features from running query `{}` on package `{}/{}`", results.size(), query->getName(), *pkg.name, *pkg.version);

      for (const Feature &res : results) {
        const auto id = res.getUniqueId();
        spdlog::debug("extracted {} locations from feature `{}`", res.locs.size(), id.toString());
        ret->insert(pkg.getID(), res);
      }
    }
  }
  spdlog::info("finished running queries.");
  return ret;
}
} // namespace Core