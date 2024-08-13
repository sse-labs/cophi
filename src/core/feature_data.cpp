#include <core/feature_data.hpp>
#include <core/attribute.hpp>
#include <core/bin_attr_map.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <variant>

namespace Core {

FeatureData::FeatureData (const jsonf &jfd) :
  _data_type(JSONToType(jfd["ftr_data_type"])) {
  
  switch (_data_type) {
    case Type::UNIT:
      _data = std::monostate();
      break;
    case Type::ATTR:
      _data = Attribute(jfd["ftr_data"]);
      break;
    case Type::BINMAP:
      _data = BinAttrMap(jfd["ftr_data"]);
      break;
  }
}

jsonf FeatureData::json() const {
  jsonf ret = jsonf::object();
  ret["ftr_data_type"] = typeToJSON(_data_type);

  switch (_data_type) {
    case Type::UNIT:
      // no data to store
      break;
    case Type::ATTR:
      ret["ftr_data"] = std::get<Attribute>(_data).json();
      break;
    case Type::BINMAP:
      ret["ftr_data"] = std::get<BinAttrMap>(_data).json();
      break;
  }
  return ret;
}

jsonf FeatureData::typeToJSON(FeatureData::Type type) {
  switch (type) {
    case Type::UNIT:
      return "unit";
    case Type::ATTR:
      return "attr";
    case Type::BINMAP:
      return "binmap";
    default:
      throw std::runtime_error("unrecognized FeatureData::Type");
  }
}

FeatureData::Type FeatureData::JSONToType(const jsonf &type) {
  // why is shadowing not a thing >:(
  const std::string stype = static_cast<std::string>(type);

  if (stype == "unit") {
    return Type::UNIT;
  } else if (stype == "attr") {
    return Type::ATTR;
  } else if (stype == "binmap") {
    return Type::BINMAP;
  } else {
    throw jsonf::other_error::create(501, "unrecognized type for FeatureData::Type", nullptr);
  }
}

}