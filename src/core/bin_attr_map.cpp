#include <core/bin_attr_map.hpp>
#include <core/attribute.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <exception>

namespace Core {

// can throw
BinAttrMap::BinAttrMap(const jsonf &jattr_map) :
  BinAttrMap(Attribute::typeFromJSON(jattr_map["attr_type"])) {
  
  for (const auto &pair : jattr_map["mapping"]) {
    insert(std::move(Binary(pair["binary"])),
           std::move(Attribute(pair["attribute"])));
  }
}

// throws if attr.type() != this->_attr_type
void BinAttrMap::insert(const Binary &bin, const Attribute &attr) {
  if (attr.type() != _attr_type) {
    throw std::runtime_error("attempted to insert Attribute of wrong type into BinAttrMap");
  }
  _bin_mapping[bin] = attr;
}

jsonf BinAttrMap::json() const {
  jsonf ret = jsonf::object();
  ret["attr_type"] = Attribute::typeToString(_attr_type);

  jsonf mapping = jsonf::array();
  for (const auto &[k, v] : _bin_mapping) {
    jsonf pair = jsonf::object();
    pair["binary"] = k.json();
    pair["attribute"] = v.json();
    mapping.push_back(pair);
  }

  ret["mapping"] = mapping;
  return ret;
}

}