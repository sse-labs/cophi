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
      // TODO: fail?
      continue;
    }
    spdlog::trace("reified query `{}`", query_name);
    _queries.push_back(std::move(reified_query));
  }
  spdlog::info("queries reified.");
}

std::unique_ptr<FeatureMap> CorpusAnalyzer::evaluate(std::vector<Package> &pkgs) const {
  // reify packages 
  //
  // TODO: MOVE LOGIC BELOW OUT OF THIS FUNCTION AND INTO A WRAPPER CLASS AROUND VECTOR<PACKAGE>
  //
  // for (auto it = pkgs.begin(); it != pkgs.end(); it++) {
  //   auto pkg = *it;

  //   if (!pkg.isReified() && !pkg.reifySelf()) {
  //     // log?
  //     // uhh, fail? ig? no don't fail, just remove from vector
  //     //pkgs.erase(it);
  //   }
  // }

  spdlog::info("start reifying packages...");
  for (auto &pkg : pkgs) {
    if (!pkg.isReified() && !pkg.reifySelf()) {

      spdlog::warn("unable to reify package `{}`", *pkg.name);


      // TODO: figure out what to do in this situation
            // idea: separate types for query & reified query?
            // yeah i think that's good: query = {name, path}
            //                          rquery = {name, module}
      // uhh, fail? ig? no don't fail, just remove from vector
      // pkgs.erase(it);
    }
  }
  spdlog::info("done reifying packages.");




  // add concurrency here
  auto ret = std::make_unique<FeatureMap>();

  spdlog::info("starting to run queries...");
  for (const auto &query: _queries) {
    for (const auto &pkg : pkgs) {
      spdlog::trace("running query `{}` on package `{}{}`", query->getName(), *pkg.name, *pkg.version);

      QueryResult results;
      query->runOn(pkg, &results);

      spdlog::debug("got {} features from running query `{}` on package `{}/{}`", results.size(), query->getName(), *pkg.name, *pkg.version);

      for (const auto &res : results) {
        const auto id = res.getUniqueId();
        spdlog::debug("extracted {} locations from feature `{}`", res.locs.size(), id.toString());
        ret->insert(std::move(res));
      }
    }
  }
  spdlog::info("finished running queries.");
  return ret;
}
} // namespace Core