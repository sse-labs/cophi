#ifndef DELPHICPP_FEATUREQUERY_HPP_
#define DELPHICPP_FEATUREQUERY_HPP_

#include <core/package.hpp>

#include <cassert>
#include <string>
#include <vector>
#include <unordered_set>


namespace Core {
// need to forward declare it
struct Feature;

// Interface
// represents an operation which takes a package and produces
// a set of features regarding that package
class Query {
  public:
    typedef std::unordered_set<struct Feature> Result;

    virtual ~Query() = default;

    // returns name of concrete class
    virtual std::string getName() const { return _name; }
    virtual std::vector<std::string> &getTypes() const = 0;

    // takes the package and adds any features found to the set of features (res)
    virtual void runOn(Package const * const pkg, Result * const res) const = 0;

  protected:
    Query(std::string name) : _name(name) {  }

  private:
    const std::string _name;
};

// represents where a feature was found
// right now, just holds info on which binary the feature was found in
// might be good to add more specific info in the future (like specific method, instruction)
struct Location {
  Location(const std::shared_ptr<std::string> &name,
           const std::shared_ptr<std::string> &vers,
           const std::shared_ptr<std::string> &bname,
           const std::shared_ptr<std::string> &bpath) :
  pkg_name(name), pkg_version(vers), bin_name(bname), bin_path(bpath) {  }
  
  Location &operator=(const Location&) = default;

  std::shared_ptr<std::string> pkg_name;
  std::shared_ptr<std::string> pkg_version;
  std::shared_ptr<std::string> bin_name;
  std::shared_ptr<std::string> bin_path;
};

// unique id for a feature
struct FeatureID {
  public:
    FeatureID(const Query &query, const size_t type) {
      // if this is false, then `type` is not referring to a valid feature of `query`
      assert(type < query.getTypes().size());

      _query_name = query.getName();
      _query_type = query.getTypes()[type];
    }

    FeatureID(const std::string &query, const std::string type) : 
             _query_name(query), _query_type(type) { }

    const std::string &name() const {return _query_name; }
    const std::string &type() const {return _query_type; }
    std::string toString() const { return _query_name + "/" + _query_type; }
 
  private:
    std::string _query_name;
    std::string _query_type;
};

// a feature consists of query + type. the query tells you the general scope of
// what information the feature will tell you, and the specific type is the specific information
//
// example: a feature with query "BinTypeQuery" is about the binary types of the binaries in a
//          package. it then either has the type "exe" or "lib", telling you the specific binary type
struct Feature {
  Feature(const Query &query, const size_t type, const std::vector<Location> &_locs)
        : fid(query, type), locs(std::move(_locs)) {
    spdlog::trace("successfully constructed Feature `{}`", this->getUniqueId().toString()); 
  }

  Feature(const FeatureID fid, const std::vector<Location> &_locs)
        : fid(fid), locs(std::move(_locs)) {
    spdlog::trace("successfully constructed Feature `{}`", this->getUniqueId().toString()); 
  }

  Feature(const FeatureID fid)
        : fid(fid), locs({}) {
    spdlog::trace("successfully constructed Feature `{}`", this->getUniqueId().toString()); 
  }

  const FeatureID &getUniqueId() const { return fid; }

  bool operator==(const Feature &other) const {
    return fid.name() == other.fid.name() &&
           fid.type() == other.fid.type();
  }

  // holds the query+type info
  const FeatureID fid;

  // all the locations where this feature was found in a specific package
  const std::vector<Location> locs;
};
}

// so we can put features in a set
template<>
struct std::hash<Core::Feature> {
  std::size_t operator()(const Core::Feature &ftr) const {
    const auto fid = ftr.fid;
    return (std::hash<std::string>()(fid.name())
         ^ (std::hash<std::string>()(fid.type()) << 1));
  }
};

#endif  // DELPHICPP_FEATUREQUERY_HPP_