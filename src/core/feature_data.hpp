#ifndef DELPHICPP_FEATUREDATA_HPP_
#define DELPHICPP_FEATUREDATA_HPP_

#include <core/attribute.hpp>
#include <core/bin_attr_map.hpp>
#include <core/binary.hpp>
#include <core/package.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <variant>

namespace Core {

class FeatureData {
  public:
    using ftr_data_t = std::variant<std::monostate,
                                    Attribute,
                                    BinAttrMap>;
    enum Type {
      UNIT,
      ATTR,
      BINMAP,
    };

    FeatureData() : _data_type(Type::UNIT), _data(std::monostate()) { }
    FeatureData(Attribute &attr) : _data_type(Type::ATTR),
      _data(std::move(attr)) { }
    FeatureData(BinAttrMap &battr_map) : _data_type(Type::BINMAP),
      _data(std::move(battr_map)) { }

    // json stuff:
    // this ctor can throw
    FeatureData (const jsonf &jfd);
    jsonf json() const;
    static jsonf typeToJSON(Type type);
    // can throw
    static Type JSONToType(const jsonf &type);

    // accessors
    Type getDataType() const { return _data_type; }
    const Attribute &getAttr() const { return std::get<Attribute>(_data); }
    const BinAttrMap &getBinMap() const { return std::get<BinAttrMap>(_data); }

  private:
    Type _data_type;
    ftr_data_t _data;
};

}

#endif  // DELPHICPP_FEATUREDATA_HPP_