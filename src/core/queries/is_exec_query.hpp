#ifndef DELPHICPP_ISEXECQUERY_HPP_
#define DELPHICPP_ISEXECQUERY_HPP_

#include <core/package.hpp>
#include <core/feature_query.hpp>

#include <string>
#include <vector>

namespace Core::Queries {
  class IsExecQuery : public Query {
    public:
      IsExecQuery(std::string name) : Query(name) {  }
      ~IsExecQuery() = default;

      static inline std::vector<std::string> types{"unit"};
      enum Type { 
        UNIT = 0,
      };

      std::vector<std::string> &getTypes() const override { return types; }
      bool runOn(Package const * const pkg,
                 Query::Result * const res,
                 const std::shared_ptr<std::atomic_bool> &terminate) const override;
  };
}

#endif  // DELPHICPP_ISEXECQUERY_HPP_