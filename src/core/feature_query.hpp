#ifndef DELPHICPP_FEATUREQUERY_HPP_
#define DELPHICPP_FEATUREQUERY_HPP_

#include <core/attribute.hpp>
#include <core/attr_mapping.hpp>
#include <core/binary.hpp>
#include <core/package.hpp>

#include <nlohmann/json.hpp>

#include <cassert>
#include <string>
#include <vector>
#include <unordered_set>


namespace Core {
// need to forward declare it
class Feature;

// Interface
// represents an operation which takes a package and produces
// a set of features regarding that package
class Query {
  public:
    typedef std::unordered_set<Feature> Result;

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

// unique id for a feature
struct FeatureID {
  public:
    FeatureID(const Query &query, const size_t type, const Attribute::Type attr_type) {
      // if this is false, then `type` is not referring to a valid feature of `query`
      assert(type < query.getTypes().size());

      _query_name = query.getName();
      _query_type = query.getTypes()[type];
      _attr_type = attr_type;
    }

    FeatureID(const std::string &query, const std::string type, const Attribute::Type attr_type) : 
             _query_name(query), _query_type(type), _attr_type(attr_type) { }
    
    FeatureID(const nlohmann::json &jfid);

    const std::string &name() const {return _query_name; }
    const std::string &type() const {return _query_type; }
    const Attribute::Type attr_type() const {return _attr_type; }
    std::string toString() const { return _query_name + "/" + _query_type; }

    nlohmann::json json() const;
 
  private:
    std::string _query_name;
    std::string _query_type;
    Attribute::Type _attr_type;
};

// a feature consists of query + type. the query tells you the general scope of
// what information the feature will tell you, and the specific type is the specific information
//
// example: a feature with query "BinTypeQuery" is about the binary types of the binaries in a
//          package. it then either has the type "exe" or "lib", telling you the specific binary type
class Feature {
  public:
    Feature(const FeatureID fid, std::vector<AttrMapping> data) :
                       _fid(fid),        _data(std::move(data)) {  }
    
    Feature(const FeatureID fid) : Feature(fid, {}) {  }

    // json ctor, can throw
    Feature(const nlohmann::json &jftr);

    const FeatureID &getUniqueId() const { return _fid; }

    size_t numLocs() const { return _data.size(); }

    bool operator==(const Feature &other) const {
      return _fid.name() == other._fid.name() &&
             _fid.type() == other._fid.type() &&
             _fid.attr_type() == other._fid.attr_type();
    }

    nlohmann::json json() const;

    // iter stuff
    using const_iterator = std::vector<AttrMapping>::const_iterator;
    const_iterator begin() const noexcept { return _data.cbegin(); }
    const_iterator end() const noexcept { return _data.cend(); }

    // only for testing
    const std::vector<AttrMapping> &getData() const { return _data; }
  private:
    // holds the query+type info
    const FeatureID _fid;
    std::vector<AttrMapping> _data;

    // IMPORTANT inv
    // forall d in _data. _fid._type == d.getAttr().type()
};
}

// provide hash for feature so we can put it in a set
template<>
struct std::hash<Core::Feature> {
  std::size_t operator()(const Core::Feature &ftr) const {
    const auto fid = ftr.getUniqueId();
    return std::hash<std::string>()(fid.name())
         ^ std::hash<std::string>()(fid.type())
         ^ std::hash<int>()(static_cast<int>(fid.attr_type()));
  }
};

#endif  // DELPHICPP_FEATUREQUERY_HPP_