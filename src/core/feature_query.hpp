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
    Query(std::string name) : _name(name) {  }

  private:
    const std::string _name;
};

struct Location {
  Location(const std::shared_ptr<std::string> &name,
           const std::shared_ptr<std::string> &vers,
           const std::shared_ptr<std::string> &bin) :
               pkg_name(name), pkg_version(vers),    bin_name(bin) {  }
  
  Location &operator=(const Location&) = default;

  std::shared_ptr<std::string> pkg_name;
  std::shared_ptr<std::string> pkg_version;
  std::shared_ptr<std::string> bin_name;
};

struct Feature {
    Feature(const Query &_query, const size_t type, const size_t count, const std::vector<Location> &_locs) :
                   query(_query),        type(type),       count(count),              locs(std::move(_locs)) {
      // if this is false, then `type` is not referring to a valid feature of `query`
      assert(type < query.getTypes().size());
      spdlog::trace("successfully constructed Feature `{}`", this->getUniqueId()); 
    }

    std::string getUniqueId() const { return query.getName() + "/" + query.getTypes()[type]; }

    const Query &query;
    const size_t type;
    const size_t count;
    const std::vector<Location> locs;
};
}

#endif  // DELPHICPP_FEATUREQUERY_HPP_