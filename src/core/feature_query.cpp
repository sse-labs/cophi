#include <core/attribute.hpp>
#include <core/feature_query.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <memory>

namespace Core {

FeatureID::FeatureID(const nlohmann::json &jfid) {
  _query_name = jfid["name"];
  _query_type = jfid["type"];
  _attr_type = typeFromJSON(jfid["attr_type"]);
}

jsonf FeatureID::json() const {
  jsonf ret = jsonf::object();
  ret["name"] = _query_name;
  ret["type"] = _query_type;
  ret["attr_type"] = typeToString(_attr_type);
  return ret;
}

Feature::Feature(const nlohmann::json &jftr) :
  _fid(FeatureID(jftr["ftr_id"])),
  _data(jftr["attr_map"].begin(), jftr["attr_map"].end())
{ }

jsonf Feature::json() const {
  jsonf ret = jsonf::object();

  ret["ftr_id"] = _fid.json();

  ret["num_locations"] = numLocs();

  jsonf jlocs = jsonf::array();
  for (const auto &am: _data) {
    jlocs.push_back(am.json());
  }
  ret["attr_map"] = jlocs;

  return ret;
}

}