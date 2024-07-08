#include "core/feature_query.hpp"
#include "core/queries/bintype_query.hpp"
#include "core/query_registry.hpp"

#include "phasar.h"

#include <iostream>

REGISTER_QUERY(BinTypeQuery)

namespace Core::Queries {
  BinTypeQuery::BinTypeQuery(std::string name) : Query(name) {
    std::cout << "hello i am bin type query. nice to meet you." << std::endl;
  }

  void BinTypeQuery::runOn(const Package &pkg, QueryResult * const res) const {
    size_t num_bin = 0;
    size_t num_lib = 0;

    for (auto &bin : pkg.bins) {
      std::vector<std::string> entries {"main"};
      psr::HelperAnalyses HA(bin.path, entries);

      const auto *test = HA.getProjectIRDB().getFunctionDefinition("main");

      if (test) num_bin++;
      else      num_lib++;
    }

    if (num_bin > 0) res->emplace_back(*static_cast<Query const *>(this) , 0, num_bin);
    if (num_lib > 0) res->emplace_back(*static_cast<Query const *>(this) , 1, num_lib);
  }
}