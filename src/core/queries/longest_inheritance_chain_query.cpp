#include <core/attribute.hpp>
#include <core/attr_mapping.hpp>
#include <core/feature_query.hpp>
#include <core/queries/longest_inheritance_chain_query.hpp>
#include <core/queries/utils/graph_utils.hpp>
#include <core/query_registry.hpp>

#include <phasar.h>

#include <iostream>
#include <vector>

REGISTER_QUERY(LongestInheritanceChainQuery)

namespace Core::Queries {

static Utils::UnweightedDAG extractTypeGraph(const psr::LLVMTypeHierarchy &lth) {
  std::vector<const llvm::StructType*> types = lth.getAllTypes();
  Utils::UnweightedDAG ret(types.size());

  // make map from struct type to its index
  std::unordered_map<const llvm::StructType*, size_t> type_to_ind;
  for (size_t i = 0; i < types.size(); i++) {
    type_to_ind[types[i]] = i;
  }

  // insert edges into DAG
  for (size_t i = 0; i < types.size(); i++) {
    const auto *type = types[i];
    for (const auto *sub : lth.getSubTypes(type)) {
      // a type is included in the set of its subtypes, but we need
      // to avoid self edges because we're making a DAG, hence this check
      if (sub != type) {
        ret.addEdge(i, type_to_ind[sub]);
      }
    }
  }
  return ret;
}

void LongestInheritanceChainQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  size_t num_bins = pkg->bins().size();

  std::vector<AttrMapping> mappings;
  mappings.reserve(num_bins);
  
  for (size_t i = 0; i < num_bins; i++) {
    auto &bin = pkg->bins()[i];
    auto mod = bin->getModuleCopy();
    psr::HelperAnalyses HA(std::move(mod), {});
    
    const auto th = HA.getTypeHierarchy();
    const auto typeGraph = extractTypeGraph(th);
    
    size_t longest = typeGraph.longestPath();
    mappings.emplace_back(bin->getID(), Attribute(longest));
  }

  FeatureID fid(*static_cast<Query const *>(this), Type::UNIT, Attribute::Type::U_INT);
  res->emplace(fid, mappings);
}

}