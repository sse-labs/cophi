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

bool IsExecQuery::runOn(Package const * const pkg,
                        Query::Result * const res,
                        const std::shared_ptr<std::atomic_bool> &terminate) const {
  const FeatureID fid(*static_cast<Query const *>(this), Type::UNIT, Attribute::Type::BOOL, FeatureData::Type::BINMAP);
  BinAttrMap exec_map(Attribute::Type::BOOL);

  const auto pkg_name = pkg->getID().str();
  size_t i = 0;
  const size_t num_bins = pkg->bins().size(); 

  spdlog::debug("started running IsExecQuery on `{}`", pkg_name);

  for (auto &bin : pkg->bins()) {
    if (*terminate) {
      spdlog::debug("IsExecQuery timed out on `{}`, not writing out results", pkg_name);
      return false;
    }

    i++;
    spdlog::trace("running IsExecQuery on binary `{}` in `{}`", bin->getID().name(), pkg_name);
    bool is_exec = Utils::isExecutable(bin->getModuleRef());
    exec_map.insert(bin->getID(), Attribute(is_exec));
    spdlog::trace("IsExecQuery has been run on {:d}/{:d} binaries in `{}`", i, num_bins, pkg_name);
  }
  spdlog::debug("finished running IsExecQuery on `{}`", pkg_name);

  if (*terminate) {
    spdlog::debug("IsExecQuery timed out on `{}`, not writing out results", pkg_name);
    return false;
  } else {
    res->emplace(fid, FeatureData(exec_map));
    return true;
  }
}

}