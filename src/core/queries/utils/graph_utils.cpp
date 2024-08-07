#include <core/queries/utils/graph_utils.hpp>

#include <spdlog/spdlog.h>

#include <algorithm>
#include <queue>
#include <vector>
#include <cstdlib>

#include <iostream>

namespace Core::Queries::Utils {

size_t UnweightedDAG::longestPath() const {
  spdlog::trace("UnweightedDAG::longestPath() started");

  // if there are no types, return zero (cause there aren't any edges)
  if (numNodes() == 0) {
    return 0;
  }

  std::vector<size_t> length_to(numNodes(), 0);

  const auto ordering = topoSort();
  for (const size_t v : ordering) {
    assert(v < numNodes());
    for (const size_t w : _adj_list[v].adj) {
      assert(w < numNodes());

      if (length_to[w] <= length_to[v] + 1) {
        length_to[w] = length_to[v] + 1;
      }
    }
  }

  auto ret = *std::max_element(length_to.begin(), 
                               length_to.end());
  
  spdlog::trace("UnweightedDAG::longestPath() finished");
  return ret;
}

std::vector<size_t> UnweightedDAG::topoSort() const {
  spdlog::trace("UnweightedDAG::topoSort() started");

  std::vector<size_t> ret;
  ret.reserve(numNodes());

  labelInDegrees();
  std::queue<size_t> zero_deg_nodes;

  // putting all the zero degree nodes in
  for (size_t i = 0; i < _adj_list.size(); i++) {
    if (_adj_list[i].in_deg == 0)
      zero_deg_nodes.emplace(i);
  }

  while (!zero_deg_nodes.empty()) {
    // add next node to sorted list
    const size_t next = zero_deg_nodes.front();
    ret.emplace_back(next);
    zero_deg_nodes.pop();

    // decreasing in-degrees of nodes adjacent to `next`
    for (const size_t node : _adj_list[next].adj) {
      // if decreasing the in-degree makes this node zero, add to queue
      if (_adj_list[node].in_deg == 1) {
        zero_deg_nodes.emplace(node);
      }

      _adj_list[node].in_deg -= 1;
    }
  }

  spdlog::trace("UnweightedDAG::topoSort() finished");

  return ret;
}

void UnweightedDAG::labelInDegrees() const {
  spdlog::trace("UnweightedDAG::labelInDegrees() started");
  for (const Node &node : _adj_list) {
    node.in_deg = 0;
  }

  for (const Node &node : _adj_list) {
    for (const size_t adj: node.adj) {
      _adj_list[adj].in_deg += 1;
    }
  }
  spdlog::trace("UnweightedDAG::labelInDegrees() finished");
}

}