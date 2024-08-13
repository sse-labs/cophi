#include <core/feature_query.hpp>
#include <core/bin_attr_map.hpp>
#include <core/feature_data.hpp>
#include <core/queries/num_instructions_query.hpp>
#include <core/query_registry.hpp>

#include <iostream>
#include <vector>

REGISTER_QUERY(NumInstructionsQuery)

namespace Core::Queries {

void NumInstructionsQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  const FeatureID fid(*static_cast<Query const *>(this), Type::UNIT, Attribute::Type::U_INT, FeatureData::Type::BINMAP);
  BinAttrMap num_instrs_map(Attribute::Type::U_INT);

  for (const auto &bin : pkg->bins()) {
    size_t num_instrs = 0;
    for (const auto &F : bin->getModuleRef()) {
      for (const auto &BB : F) {
        num_instrs += std::distance(BB.begin(), BB.end());
      }
    }
    num_instrs_map.insert(bin->getID(), Attribute(num_instrs));
  }

  res->emplace(fid, FeatureData(num_instrs_map));
}

}