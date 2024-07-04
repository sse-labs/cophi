#ifndef DELPHICPP_FEATUREQUERY_HPP_
#define DELPHICPP_FEATUREQUERY_HPP_

#include "core/package.hpp"

#include <cassert>
#include <string>
#include <vector>

namespace Core {
  // need to forward declare it
  class Feature;

  typedef std::vector<const Feature> QueryResult;

  class Query {
    public:
      virtual ~Query() = default;
      virtual std::vector<std::string> &getTypes() const = 0;

      // append to end of queryresult
      virtual void runOn(const Package &pkg, QueryResult * const res) const = 0;

    protected:
      Query() = default;
  };

  class Feature {
    public:
      Feature(const Query &query, const size_t type, const size_t count) :
                    _query(query),       _type(type),      _count(count) {
        // if this is false, then `type` is not referring to a valid feature of `query`
        assert(type < query.getTypes().size());
      }

      std::string getUniqueId() const; // query.name + "/" + query.types[_type]

    private:
      const Query &_query;
      const size_t _type;
      const size_t _count;
    // TODO: add Locations
  };
}

#endif  // DELPHICPP_FEATUREQUERY_HPP_