#include <core/feature_query.hpp>
#include <core/queries/bintype_query.hpp>
#include <core/query_registry.hpp>
#include <core/queries/utils/query_utils.hpp>

#include <phasar.h>

#include <iostream>
#include <vector>

REGISTER_QUERY(BinTypeQuery)

namespace Core::Queries {

void BinTypeQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  std::vector<Location> execs;
  std::vector<Location> libs;

  for (auto &bin : pkg->bins()) {
    if (Utils::isExecutable(bin->getModuleRef())) {
      execs.emplace_back(bin->sharedName(), bin->sharedPath());
    } else {
      libs.emplace_back(bin->sharedName(), bin->sharedPath());
    }
  }

  if (execs.size() > 0) res->emplace(*static_cast<Query const *>(this), Type::EXE, execs.size(), execs);
  if (libs.size() > 0) res->emplace(*static_cast<Query const *>(this), Type::LIB, libs.size(), libs);
}

}