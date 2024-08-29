#ifndef DELPHICPP_LONGESTINHERITANCECHAINQUERY_HPP_
#define DELPHICPP_LONGESTINHERITANCECHAINQUERY_HPP_

#include <core/package.hpp>
#include <core/feature_query.hpp>

#include <string>
#include <vector>

namespace Core::Queries {

class LongestInheritanceChainQuery : public Query {
  public:
    LongestInheritanceChainQuery(std::string name) : Query(name) {  }
    ~LongestInheritanceChainQuery() = default;

    static inline std::vector<std::string> types{"notcpp", "cpp"};
    enum Type { 
      NOTCPP = 0,
      CPP = 1,
    };

    std::vector<std::string> &getTypes() const override { return types; }
    bool runOn(Package const * const pkg,
                Query::Result * const res,
                const std::shared_ptr<std::atomic_bool> &terminate) const override;
};

}

#endif  // DELPHICPP_LONGESTINHERITANCECHAINQUERY_HPP_