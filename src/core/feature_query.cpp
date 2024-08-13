#include <core/attribute.hpp>
#include <core/feature_query.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <memory>

namespace Core {

FeatureID::FeatureID(const nlohmann::json &jfid) {
  _query_name = jfid["name"];
  _query_type = jfid["type"];
  _attr_type = Attribute::typeFromJSON(jfid["attr_type"]);
  _data_type = FeatureData::JSONToType(jfid["data_type"]);
}

jsonf FeatureID::json() const {
  jsonf ret = jsonf::object();
  ret["name"] = _query_name;
  ret["type"] = _query_type;
  ret["attr_type"] = Attribute::typeToString(_attr_type);
  ret["data_type"] = FeatureData::typeToJSON(_data_type);
  return ret;
}

Feature::Feature(const nlohmann::json &jftr) :
  Feature(FeatureID(jftr["ftr_id"]), FeatureData(jftr["data"]))
{ }

jsonf Feature::json() const {
  jsonf ret = jsonf::object();
  ret["ftr_id"] = _fid.json();
  ret["data"] = _data.json();
  return ret;
}

}