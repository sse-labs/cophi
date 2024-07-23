#ifndef DELPHICPP_BINTYPEQUERY_HPP_
#define DELPHICPP_BINTYPEQUERY_HPP_

#include <core/package.hpp>
#include <core/feature_query.hpp>

#include <string>
#include <vector>

namespace Core::Queries {
  class BinTypeQuery : public Query {
    public:
      BinTypeQuery(std::string name) : Query(name) {  }
      ~BinTypeQuery() = default;

      static inline std::vector<std::string> types{"exe", "lib"};
      enum Type { 
        EXE = 0,
        LIB = 1,
      };

      std::vector<std::string> &getTypes() const override { return types; }
      void runOn(Package const * const pkg, Query::Result * const res) const override;
  };
}

#endif  // DELPHICPP_BINTYPEQUERY_HPP_