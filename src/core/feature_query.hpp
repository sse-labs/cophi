#ifndef DELPHICPP_FEATUREQUERY_HPP_
#define DELPHICPP_FEATUREQUERY_HPP_

#include <core/package.hpp>

#include <cassert>
#include <string>
#include <vector>


namespace Core {
// need to forward declare it
struct Feature;

// TODO: move inside Query and rename to Result
typedef std::vector<struct Feature> QueryResult;

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

struct FeatureID {
  public:
    FeatureID(const Query &query, const size_t type) {
      // if this is false, then `type` is not referring to a valid feature of `query`
      assert(type < query.getTypes().size());

      _query_name = query.getName();
      _query_type = query.getTypes()[type];
    }

    const std::string &name() const {return _query_name; }
    const std::string &type() const {return _query_type; }
    std::string toString() const { return _query_name + "/" + _query_type; }

    bool operator==(const FeatureID &other) const {
      return _query_name == other._query_name
          && _query_type == other._query_type;
    }
 
  private:
    std::string _query_name;
    std::string _query_type;
};

struct Feature {
  Feature(const Query &query, const size_t type, const std::vector<Location> &_locs)
        : fid(query, type), locs(std::move(_locs)) {
    spdlog::trace("successfully constructed Feature `{}`", this->getUniqueId().toString()); 
  }

  const FeatureID &getUniqueId() const { return fid; }

  const FeatureID fid;
  const std::vector<Location> locs;
};
}

// for hashing FeatureID
template<>
struct std::hash<Core::FeatureID> {
  std::size_t operator()(const Core::FeatureID &fid) const {
    return (std::hash<std::string>()(fid.name())
        ^ ((std::hash<std::string>()(fid.type()) << 1) >> 1));
  }
};

#endif  // DELPHICPP_FEATUREQUERY_HPP_