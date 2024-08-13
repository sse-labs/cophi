#include <core/attribute.hpp>
#include <core/bin_attr_map.hpp>
#include <core/feature_query.hpp>
#include <core/feature_data.hpp>
#include <core/queries/is_exec_query.hpp>
#include <core/query_registry.hpp>
#include <core/queries/utils/query_utils.hpp>

#include <phasar.h>

#include <iostream>
#include <vector>

REGISTER_QUERY(IsExecQuery)

namespace Core::Queries {

void IsExecQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  const FeatureID fid(*static_cast<Query const *>(this), Type::UNIT, Attribute::Type::BOOL, FeatureData::Type::BINMAP);
  BinAttrMap exec_map(Attribute::Type::BOOL);

  for (auto &bin : pkg->bins()) {
    bool is_exec = Utils::isExecutable(bin->getModuleRef());
    exec_map.insert(bin->getID(), Attribute(is_exec));
  }
  res->emplace(fid, FeatureData(exec_map));
}

}