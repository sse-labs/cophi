#include <core/attribute.hpp>
#include <core/attr_mapping.hpp>
#include <core/feature_query.hpp>
#include <core/filter.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <cstdlib>
#include <variant>

namespace Core {

Range::Range(const jsonf &jrange) {
  _type = typeFromJSON(jrange["attr_type"]);
  
  switch (_type) {
    case Attribute::Type::UNIT:
      _range = std::monostate();
      break;
    case Attribute::Type::BOOL:
      _range = static_cast<bool>(jrange["bool_val"]);
      break;
    case Attribute::Type::U_INT:
      _range = static_cast<std::pair<size_t, size_t>>(jrange["uint_lower_bound"],
                                                     jrange["uint_upper_bound"]);
      break;
    case Attribute::Type::FLOAT:
      _range = static_cast<std::pair<double, double>>(jrange["uint_lower_bound"],
                                                     jrange["uint_upper_bound"]);
      break;
    case Attribute::Type::STRING:
      _range = static_cast<std::string>(jrange["string_val"]);
      break;
    default:
      throw jsonf::other_error::create(501, "unknown Attribute::Type value", nullptr);
  }
}

jsonf Range::json() const {
  jsonf ret = jsonf::object();
  ret["attr_type"] = this->type();
  switch (this->type()) {
    case Attribute::Type::UNIT: {
      break;
    }
    case Attribute::Type::BOOL: {
      ret["bool_val"] = std::get<bool>(_range);
      break;
    }
    case Attribute::Type::U_INT: {
      const auto [ul, uu] = std::get<std::pair<size_t, size_t>>(_range);
      ret["uint_lower_bound"] = ul;
      ret["uint_upper_bound"] = uu;
      break;
    }
    case Attribute::Type::FLOAT: {
      const auto [fl, fu] = std::get<std::pair<double, double>>(_range);
      ret["float_lower_bound"] = fl;
      ret["float_upper_bound"] = fu;
      break;
    }
    case Attribute::Type::STRING: {
      ret["string_val"] = std::get<std::string>(_range);
      break;
    }
    default: {
      spdlog::critical("unknown Attribute::Type value, exiting...");
      exit(1);
    }
  }
  return ret;
}

// checks if attribute is in the range.
// precond: attr.type() == this->type()
bool Range::inRange(const Attribute &attr) const {
  if (attr.type() != this->type()) {
    spdlog::critical("attempting to filter attribite of type {} with range of type {}. exiting...",
                      typeToString(attr.type()), typeToString(this->type()));
    exit(1);
  }

  switch (attr.type()) {
    case Attribute::Type::UNIT: {
      return true;
    }
    case Attribute::Type::BOOL: {
      return std::get<bool>(_range) == attr.getBool();
    }
    case Attribute::Type::U_INT: {
      const size_t num = attr.getUInt();
      const auto [nl, nu] = std::get<std::pair<size_t, size_t>>(_range);
      return nl <= num && num < nu;
    }
    case Attribute::Type::FLOAT: {
      const double flt = attr.getFloat();
      const auto [fl, fu] = std::get<std::pair<double, double>>(_range);
      return fl <= flt && flt < fu;
    }
    case Attribute::Type::STRING: {
      return std::get<std::string>(_range) == attr.getString();
    }
    default: {
      spdlog::critical("unknown Attribute::Type value, exiting...");
      exit(1);
    }
  }
}

// precond: fid.attr_type() == range.type()
Filter::Filter(const FeatureID &fid, const Type type, const Range &range) :
  _fid(fid), _type(type), _range(range)
{
  if (fid.attr_type() != range.type()) {
    spdlog::error("Filter constructed with FeatureID of type {} with range of type {}.",
                  typeToString(fid.attr_type()), typeToString(range.type()));
  }
}

bool Filter::test(const Feature &ftr) const {
  if (_type == Type::FORALL) {
    return testFeatureForAll(ftr);
  } else {
    return testFeatureExists(ftr);
  }
}

bool Filter::testFeatureForAll(const Feature &ftr) const {
  for (const AttrMapping &attr_map : ftr) {
    if (!_range.inRange(attr_map.getAttr())) {
      return false;
    }
  }
  return true;
}

bool Filter::testFeatureExists(const Feature &ftr) const {
  for (const AttrMapping &attr_map : ftr) {
    if (_range.inRange(attr_map.getAttr())) {
      return true;
    }
  }
  return false;
}

// throws on malformed json
Filter::Filter(const jsonf &jfilter) :
  _fid(jfilter["fid"]), _range(jfilter["range"])
{
  std::string type = jfilter["filter_type"];

  if (type == "forall") {
    _type = Type::FORALL;
  } else if (type == "exists") {
    _type = Type::EXISTS;
  } else {
    throw jsonf::other_error::create(501, "filter type " + type + " not valid", nullptr);
  }
}

}