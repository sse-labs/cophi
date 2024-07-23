#include <core/feature_query.hpp>
#include <core/queries/bintype_query.hpp>
#include <core/query_registry.hpp>

#include <phasar.h>

#include <iostream>
#include <vector>

REGISTER_QUERY(BinTypeQuery)

namespace Core::Queries {

void BinTypeQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  std::vector<Location> execs;
  std::vector<Location> libs;

  for (auto &bin : pkg->bins()) {
    std::vector<std::string> entries {"main"};
    
    auto ptr = bin->getModuleCopy();
    psr::HelperAnalyses HA(std::move(ptr), entries);

    const auto *test = HA.getProjectIRDB().getFunctionDefinition("main");

    if (test) {
      execs.emplace_back(pkg->getID().name, pkg->getID().version, bin->sharedName());
    } else {
      libs.emplace_back(pkg->getID().name, pkg->getID().version, bin->sharedName());
    }
  }

  if (execs.size() > 0) res->emplace(*static_cast<Query const *>(this), 0, execs);
  if (libs.size() > 0) res->emplace(*static_cast<Query const *>(this), 1, libs);
}

}