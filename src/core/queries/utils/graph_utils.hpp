#ifndef DELPHICPP_GRAPHUTILS_HPP_
#define DELPHICPP_GRAPHUTILS_HPP_

#include <cassert>
#include <cstdlib>
#include <vector>

namespace Core::Queries::Utils {

// used for representing the type hierarchy
// (it's a graph because C++ has multiple inheritance)
class UnweightedDAG {
  public:
    UnweightedDAG(size_t num_nodes) : _adj_list(num_nodes) {  }

    void addEdge(size_t from, size_t to) {
      assert(from < numNodes());
      assert(to < numNodes());

      _adj_list[from].adj.emplace_back(to);
    }

    size_t longestPath() const;

  private:
    struct Node {
      mutable size_t in_deg;
      std::vector<size_t> adj;
    };

    std::vector<size_t> topoSort() const;
    size_t numNodes() const { return _adj_list.size(); }
    void labelInDegrees() const;

    std::vector<Node> _adj_list;
};

}

#endif  // DELPHICPP_GRAPHUTILS_HPP_