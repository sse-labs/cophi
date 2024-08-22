#include <core/attribute.hpp>
#include <core/feature_data.hpp>
#include <core/feature_query.hpp>
#include <core/filter.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <cstdlib>
#include <variant>

namespace Core {

Range::Range(const jsonf &jrange) {
  _type = Attribute::typeFromJSON(jrange["attr_type"]);
  
  switch (_type) {
    case Attribute::Type::UNIT:
      _range = std::monostate();
      break;
    case Attribute::Type::BOOL:
      _range = static_cast<bool>(jrange["val"]);
      break;
    case Attribute::Type::U_INT:
      _range = std::pair<size_t, size_t>(static_cast<size_t>(jrange["lower_bound"]),
                                         static_cast<size_t>(jrange["upper_bound"]));
      break;
    case Attribute::Type::FLOAT:
      _range = std::pair<double, double>(static_cast<double>(jrange["lower_bound"]),
                                         static_cast<double>(jrange["upper_bound"]));
      break;
    case Attribute::Type::STRING:
      _range = static_cast<std::string>(jrange["val"]);
      break;
    default:
      throw jsonf::other_error::create(501, "unknown Attribute::Type value", nullptr);
  }
}

jsonf Range::json() const {
  jsonf ret = jsonf::object();
  ret["attr_type"] = Attribute::typeToString(_type);
  switch (this->type()) {
    case Attribute::Type::UNIT: {
      break;
    }
    case Attribute::Type::BOOL: {
      ret["val"] = std::get<bool>(_range);
      break;
    }
    case Attribute::Type::U_INT: {
      const auto [ul, uu] = std::get<std::pair<size_t, size_t>>(_range);
      ret["lower_bound"] = ul;
      ret["upper_bound"] = uu;
      break;
    }
    case Attribute::Type::FLOAT: {
      const auto [fl, fu] = std::get<std::pair<double, double>>(_range);
      ret["lower_bound"] = fl;
      ret["upper_bound"] = fu;
      break;
    }
    case Attribute::Type::STRING: {
      ret["val"] = std::get<std::string>(_range);
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
                      Attribute::typeToString(attr.type()), Attribute::typeToString(this->type()));
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
Filter::Filter(const FeatureID &fid, const FilterType type, const Range &range) :
  _fid(fid), _type(type), _use_range(true), _range(range)
{
  if (_fid.attr_type() != _range.type()) {
    spdlog::error("Filter constructed with FeatureID of type {} with range of type {}.",
                  Attribute::typeToString(_fid.attr_type()), Attribute::typeToString(_range.type()));
  }

  const auto fid_dt = _fid.data_type();

  // checking that data_type and filter type match up
  if ((fid_dt == FeatureData::Type::UNIT && _type != FilterType::NOATTR) ||
      (fid_dt == FeatureData::Type::ATTR && _type != FilterType::ONEATTR) ||
      (fid_dt == FeatureData::Type::BINMAP && _type != FilterType::FORALL
                                           && _type != FilterType::EXISTS)) {
      spdlog::error("");
  }
}

Filter::Filter(const FeatureID &fid, const FilterType type) :
  Filter(fid, type, Range())
{
  _use_range = false;
}

bool Filter::test(const Feature &ftr) const {
  if (ftr.getUniqueId() != _fid) {
    return false;
  } else if (!_use_range) { // we only care if the ftr_id matches in this case
    return true;
  }

  switch (_type) {
    case FilterType::NOATTR:
      return true;
    case FilterType::ONEATTR:
      return _range.inRange(ftr.getData().getAttr());
    case FilterType::FORALL:
      return testFeatureForAll(ftr);
    case FilterType::EXISTS:
      return testFeatureExists(ftr);
  }
}

bool Filter::testFeatureForAll(const Feature &ftr) const {
  for (const auto &[_, attr] : ftr.getData().getBinMap()) {
    if (!_range.inRange(attr)) {
      return false;
    }
  }
  return true;
}

bool Filter::testFeatureExists(const Feature &ftr) const {
  for (const auto &[_, attr] : ftr.getData().getBinMap()) {
    if (_range.inRange(attr)) {
      return true;
    }
  }
  return false;
}

// throws on malformed json
Filter::Filter(const jsonf &jfilter) :
  _fid(jfilter["feature_id"]), _use_range(static_cast<bool>(jfilter["use_range"])) //, _range(jfilter["range"])
{
  if (!_use_range) {
    _range = Range();
    _type = FilterType::NOATTR;
    return;
  }

  _range = Range(jfilter["range"]);

  std::string type = jfilter["filter_type"];

  if (type == "no_attr") {
    _type = FilterType::NOATTR;
  } else if (type == "one_attr") {
    _type = FilterType::ONEATTR;
  } else if (type == "forall") {
    _type = FilterType::FORALL;
  } else if (type == "exists") {
    _type = FilterType::EXISTS;
  } else {
    throw jsonf::other_error::create(501, "filter type " + type + " not valid", nullptr);
  }
}

}