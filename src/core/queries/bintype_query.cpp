#include "core/queries/bintype_query.hpp"
#include "core/query_registry.hpp"

#include <iostream>

REGISTER_QUERY(BinTypeQuery)

namespace Core::Queries {
    BinTypeQuery::BinTypeQuery() {
      std::cout << "hello i am bin type query. nice to meet you." << std::endl;
    }

    void BinTypeQuery::runOn(const Package &pkg, QueryResult * const res) const {
      std::cout << "does this fix things?" << std::endl;
    }
}