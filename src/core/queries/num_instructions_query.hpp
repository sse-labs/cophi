#ifndef DELPHICPP_NUMINSTRUCTIONSQUERY_HPP_
#define DELPHICPP_NUMINSTRUCTIONSQUERY_HPP_

#include <core/package.hpp>
#include <core/feature_query.hpp>

#include <string>
#include <vector>

namespace Core::Queries {
  class NumInstructionsQuery : public Query {
    public:
      NumInstructionsQuery(std::string name) : Query(name) {  }
      ~NumInstructionsQuery() = default;

      static inline std::vector<std::string> types{"unit"};
      enum Type { 
        UNIT = 0
      };

      std::vector<std::string> &getTypes() const override { return types; }
      bool runOn(Package const * const pkg,
                 Query::Result * const res,
                 const std::shared_ptr<std::atomic_bool> &terminate) const override;
  };
}

#endif  // DELPHICPP_NUMINSTRUCTIONSQUERY_HPP_