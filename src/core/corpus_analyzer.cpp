#include <core/corpus_analyzer.hpp>
#include <core/feature_map.hpp>
#include <core/query_registry.hpp>

namespace Core {

CorpusAnalyzer::CorpusAnalyzer(const CorpusAnalyzerConfig &conf) : _conf(conf) {
  _queries = std::vector<std::unique_ptr<Query>>();
  const QueryRegistry &registry = QueryRegistry::singleton();

  for (const auto &query_name : conf.query_subset) {
    auto reified_query = registry.getInstanceOf(query_name);
    if (!reified_query) {
      // log
      // TODO: fail?
      continue;
    }
    _queries.push_back(std::move(reified_query));
  }
}

std::unique_ptr<FeatureMap> CorpusAnalyzer::evaluate(const std::vector<Package> &pkgs) const {
  // add concurrency here
  auto ret = std::unique_ptr<FeatureMap>(new FeatureMap());

  for (const auto &pkg : pkgs) {
    for (const auto &query: _queries) {
      QueryResult results;
      query->runOn(pkg, &results);

      for (const auto &res : results)
        ret->insert(res.getUniqueId(), std::move(res.locs));
    }
  }

  return ret;
}

}