#include <core/attribute.hpp>
#include <core/attr_mapping.hpp>
#include <core/feature_query.hpp>
#include <core/queries/is_exec_query.hpp>
#include <core/query_registry.hpp>
#include <core/queries/utils/query_utils.hpp>

#include <phasar.h>

#include <iostream>
#include <vector>

REGISTER_QUERY(IsExecQuery)

namespace Core::Queries {

void IsExecQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  std::vector<AttrMapping> mappings;

  for (auto &bin : pkg->bins()) {
    bool is_exec = Utils::isExecutable(bin->getModuleRef());
    mappings.emplace_back(bin->getID(), Attribute(is_exec));
  }
  const FeatureID fid(*static_cast<Query const *>(this), Type::UNIT, Attribute::Type::BOOL);
  res->emplace(fid, mappings);
}

}