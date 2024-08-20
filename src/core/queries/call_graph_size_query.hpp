#ifndef DELPHICPP_CALLGRAPHSIZEQUERY_HPP_
#define DELPHICPP_CALLGRAPHSIZEQUERY_HPP_

#include <core/package.hpp>
#include <core/feature_query.hpp>

#include <atomic>
#include <string>
#include <vector>

namespace Core::Queries {
  class CallGraphSizeQuery : public Query {
    public:
      CallGraphSizeQuery(std::string name) : Query(name) {  }
      ~CallGraphSizeQuery() = default;

      static inline std::vector<std::string> types{"node", "edge"};
      enum Type { 
        NODE = 0,
        EDGE = 1,
      };

      std::vector<std::string> &getTypes() const override { return types; }
      bool runOn(Package const * const pkg,
                 Query::Result * const res,
                 const std::shared_ptr<std::atomic_bool> &terminate) const override;
  };
}

#endif  // DELPHICPP_CALLGRAPHSIZEQUERY_HPP_