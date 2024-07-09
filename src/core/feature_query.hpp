#ifndef DELPHICPP_FEATUREQUERY_HPP_
#define DELPHICPP_FEATUREQUERY_HPP_

#include <core/package.hpp>

#include <cassert>
#include <string>
#include <vector>

namespace Core {
  // need to forward declare it
  class Feature;

  typedef std::vector<Feature> QueryResult;

  class Query {
    public:
      virtual ~Query() = default;

      virtual std::string getName() const { return _name; }
      virtual std::vector<std::string> &getTypes() const = 0;

      // append to end of queryresult
      virtual void runOn(const Package &pkg, QueryResult * const res) const = 0;

    protected:
      Query(std::string &name) : _name(name) {  }

    private:
      const std::string _name;
  };

  struct Feature {
      Feature(const Query &query, const size_t type, const size_t count) :
                     query(query),        type(type),       count(count) {
        // if this is false, then `type` is not referring to a valid feature of `query`
        assert(type < query.getTypes().size());
      }

      std::string getUniqueId() const { return query.getName() + "/" + query.getTypes()[type]; }

      const Query &query;
      const size_t type;
      const size_t count;
    // TODO: add Locations
  };
}

#endif  // DELPHICPP_FEATUREQUERY_HPP_