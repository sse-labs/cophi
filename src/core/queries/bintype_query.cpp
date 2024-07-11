#include <core/feature_query.hpp>
#include <core/queries/bintype_query.hpp>
#include <core/query_registry.hpp>

#include <phasar.h>

#include <iostream>
#include <vector>

REGISTER_QUERY(BinTypeQuery)

namespace Core::Queries {

void BinTypeQuery::runOn(const Package &pkg, QueryResult * const res) const {
  size_t num_bin = 0;
  size_t num_lib = 0;

  std::vector<Location> execs;
  std::vector<Location> libs;

  for (auto &bin : pkg.bins) {
    std::vector<std::string> entries {"main"};

    psr::HelperAnalyses HA(bin.getModuleCopy(), entries);

    const auto *test = HA.getProjectIRDB().getFunctionDefinition("main");

    if (test) {
      execs.emplace_back(pkg.name, pkg.version, bin.name);
    } else {
      libs.emplace_back(pkg.name, pkg.version, bin.name);
    }
  }

  if (execs.size() > 0) res->emplace_back(*static_cast<Query const *>(this), 0, execs.size(), execs);
  if (libs.size() > 0) res->emplace_back(*static_cast<Query const *>(this), 1, libs.size(), libs);
}

}