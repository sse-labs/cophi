#ifndef DELPHICPP_FEATUREQUERY_HPP_
#define DELPHICPP_FEATUREQUERY_HPP_

#include <core/attribute.hpp>
#include <core/binary.hpp>
#include <core/package.hpp>
#include <core/feature_data.hpp>

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
    FeatureID(const Query &query, const size_t type,
              const Attribute::Type attr_type,
              const FeatureData::Type data_type) {
      // if this is false, then `type` is not referring to a valid feature of `query`
      assert(type < query.getTypes().size());

      _query_name = query.getName();
      _query_type = query.getTypes()[type];
      _attr_type = attr_type;
      _data_type = data_type;
    }

    FeatureID(const std::string &query, const std::string type,
              const Attribute::Type attr_type,
              const FeatureData::Type data_type) : 
        _query_name(query), _query_type(type),
        _attr_type(attr_type), _data_type(data_type) { }
    
    FeatureID(const nlohmann::json &jfid);

    const std::string &name() const {return _query_name; }
    const std::string &type() const {return _query_type; }
    const Attribute::Type attr_type() const {return _attr_type; }
    const FeatureData::Type data_type() const {return _data_type; }
    std::string toString() const { return _query_name + "/" + _query_type; }

    nlohmann::json json() const;

    bool operator==(const FeatureID &other) const {
      return _query_name == other._query_name &&
             _query_type == other._query_type &&
             _attr_type  == other._attr_type &&
             _data_type  == other._data_type;
    }

    bool operator!=(const FeatureID &other) const {
      return !(*this == other);
    }
 
  private:
    // these two fields basically form the name of the feature
    std::string _query_name;
    std::string _query_type;

    // this is the type of data that is being stored (int, double, string, bool, unit, ...)
    Attribute::Type _attr_type;
    // this is like in what form the data is (one attribute for the whole binary, map from bin -> attribute)
    FeatureData::Type _data_type;
};

// a feature consists of query + type. the query tells you the general scope of
// what information the feature will tell you, and the specific type is the specific information
//
// example: a feature with query "BinTypeQuery" is about the binary types of the binaries in a
//          package. it then either has the type "exe" or "lib", telling you the specific binary type
class Feature {
  public: 
    Feature(const FeatureID fid, const FeatureData &data) :
                       _fid(fid),   _data(std::move(data)) {
      // making sure the fid actually matches the feature data
      assert(_fid.data_type() == _data.getDataType());
      switch (_fid.data_type()) {
        case FeatureData::UNIT:
          assert(_fid.attr_type() == Attribute::Type::UNIT);
          break;
        case FeatureData::ATTR:
          assert(_fid.attr_type() == _data.getAttr().type());
          break;
        case FeatureData::BINMAP:
          assert(_fid.attr_type() == _data.getBinMap().attrType());
          break;
      }
    }
    
    Feature(const FeatureID fid) : _fid(fid) {  }

    // json ctor, can throw
    Feature(const nlohmann::json &jftr);

    const FeatureID &getUniqueId() const { return _fid; }
    const FeatureData &getData() const { return _data; }

    bool operator==(const Feature &other) const {
      return _fid == other._fid; // &&
             // TODO: add == to FeatureData _data == other._data;
    }

    bool operator!=(const Feature &other) const {
      return !(*this == other);
    }

    nlohmann::json json() const;

  private:
    // holds the query+type info
    const FeatureID   _fid;
    const FeatureData _data;
};
}

template<>
struct std::hash<Core::FeatureID> {
  std::size_t operator()(const Core::FeatureID &fid) const {
    return std::hash<std::string>()(fid.name())
         ^ std::hash<std::string>()(fid.type())
         ^ std::hash<int>()(static_cast<int>(fid.attr_type()))
         ^ std::hash<int>()(static_cast<int>(fid.data_type()));
  }
};

// provide hash for feature so we can put it in a set
template<>
struct std::hash<Core::Feature> {
  std::size_t operator()(const Core::Feature &ftr) const {
    return std::hash<Core::FeatureID>()(ftr.getUniqueId());
  }
};

#endif  // DELPHICPP_FEATUREQUERY_HPP_