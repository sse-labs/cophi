#include <core/feature_query.hpp>
#include <core/queries/num_instructions_query.hpp>
#include <core/query_registry.hpp>

#include <iostream>
#include <vector>

REGISTER_QUERY(NumInstructionsQuery)

namespace Core::Queries {

void NumInstructionsQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  std::vector<AttrMapping> mappings;
  for (const auto &bin : pkg->bins()) {
    size_t num_instrs = 0;
    for (const auto &F : bin->getModuleRef()) {
      for (const auto &BB : F) {
        num_instrs += std::distance(BB.begin(), BB.end());
      }
    }
    mappings.emplace_back(bin->getID(), Attribute(num_instrs));
  }
  FeatureID fid(*static_cast<Query const *>(this), Type::UNIT, Attribute::Type::U_INT);
  res->emplace(fid, mappings);
}

}