#include <core/feature_query.hpp>
#include <core/queries/call_graph_size_query.hpp>
#include <core/query_registry.hpp>

#include <phasar.h>

#include <iostream>
#include <vector>

REGISTER_QUERY(CallGraphSizeQuery)

namespace Core::Queries {

void CallGraphSizeQuery::runOn(Package const * const pkg, Query::Result * const res) const {
  size_t num_bins = pkg->bins().size();
  
  // vector<(num_nodes, num_edges)>
  std::vector<std::pair<size_t, size_t>> cg_sizes(num_bins, std::make_pair(0, 0));

  for (size_t i = 0; i < num_bins; i++) {
    auto mod = pkg->bins()[i]->getModuleCopy();

    psr::HelperAnalyses HA(std::move(mod), {"main"}); // what should the entry points be??????????

    const auto &cg = HA.getICFG().getCallGraph();

    // this is what's in the call graph:

    // llvm::DenseMap<N, InstructionVertexTy *> CalleesAt{};
    // llvm::DenseMap<F, FunctionVertexTy *> CallersOf{};

    // setting num nodes
    cg_sizes[i].first = cg.getNumVertexFunctions(); // is this right? i dunno

    // finding out num edges
    size_t num_edges = 0;
    for (const auto &site : cg.getAllVertexCallSites()) {
      const auto it = cg.getCalleesOfCallAt(site);
      num_edges += std::distance(it.begin(), it.end());
    }
    cg_sizes[i].second = num_edges; // change
  }

  for (size_t i = 0; i < num_bins; i++) {
    const auto &bin = pkg->bins()[i];
    std::vector<Location> locs{Location(bin->sharedName(), bin->sharedPath())};

    res->emplace(*static_cast<Query const *>(this), Type::NODE, cg_sizes[i].first, locs);
    res->emplace(*static_cast<Query const *>(this), Type::EDGE, cg_sizes[i].second, locs);
  }
}

}