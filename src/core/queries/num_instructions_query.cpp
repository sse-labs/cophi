#include <core/feature_query.hpp>
#include <core/bin_attr_map.hpp>
#include <core/feature_data.hpp>
#include <core/queries/num_instructions_query.hpp>
#include <core/query_registry.hpp>

#include <iostream>
#include <vector>

REGISTER_QUERY(NumInstructionsQuery)

namespace Core::Queries {

bool NumInstructionsQuery::runOn(Package const * const pkg,
                                 Query::Result * const res,
                                 const std::shared_ptr<std::atomic_bool> &terminate) const {
  const FeatureID fid(*static_cast<Query const *>(this), Type::UNIT, Attribute::Type::U_INT, FeatureData::Type::BINMAP);
  BinAttrMap num_instrs_map(Attribute::Type::U_INT);

  const auto pkg_name = pkg->getID().str();
  size_t i = 0;
  const size_t num_bins = pkg->bins().size(); 

  spdlog::debug("started running NumInstructionsQuery on `{}`", pkg_name);

  for (const auto &bin : pkg->bins()) {
    if (*terminate) {
      spdlog::debug("NumInstructionsQuery timed out on `{}`, not writing out results", pkg_name);
      return false;
    }

    i++;
    spdlog::trace("running NumInstructionsQuery on binary `{}` in `{}`", bin->getID().name(), pkg_name);

    size_t num_instrs = 0;
    for (const auto &F : bin->getModuleRef()) {
      for (const auto &BB : F) {
        num_instrs += std::distance(BB.begin(), BB.end());
      }
    }
    num_instrs_map.insert(bin->getID(), Attribute(num_instrs));

    spdlog::trace("NumInstructionsQuery has been run on {:d}/{:d} binaries in `{}`", i, num_bins, pkg_name);
  }

  spdlog::debug("finished running NumInstructionsQuery on `{}`", pkg_name);

  if (*terminate) {
    spdlog::debug("NumInstructionsQuery timed out on `{}`, not writing out results", pkg_name);
    return false;
  }

  res->emplace(fid, FeatureData(num_instrs_map));
  return true;
}

}