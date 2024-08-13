#include <core/attribute.hpp>

#include <spdlog/spdlog.h>

#include <string>
#include <variant>

namespace Core {

Attribute::Attribute(const jsonf &jattr) :
          _type(typeFromJSON(jattr["type"]))
{
  switch (_type) {
    case Type::UNIT:
      _attr = std::monostate();
      break;
    case Type::BOOL:
      _attr = static_cast<bool>(jattr["val"]);
      break;
    case Type::U_INT:
      _attr = static_cast<size_t>(jattr["val"]);
      break;
    case Type::FLOAT:
      _attr = static_cast<double>(jattr["val"]);
      break;
    case Type::STRING:
      _attr = static_cast<std::string>(jattr["val"]);
      break;
  }
}

jsonf Attribute::json() const {
  jsonf ret = jsonf::object();
  ret["type"] = typeToString(_type);

  switch (_type) {
    case Type::UNIT:
      ret["val"] = nullptr;
      break;
    case Type::BOOL:
      ret["val"] = getBool();
      break;
    case Type::U_INT:
      ret["val"] = getUInt();
      break;
    case Type::FLOAT:
      ret["val"] = getFloat();
      break;
    case Type::STRING:
      ret["val"] = getString ();
      break;
  }
  return ret;
}

std::string Attribute::typeToString(const Attribute::Type type) {
  switch (type) {
    case Attribute::Type::UNIT:
      return "unit";
    case Attribute::Type::BOOL:
      return "bool";
    case Attribute::Type::U_INT:
      return "uint";
    case Attribute::Type::FLOAT:
      return "float";
    case Attribute::Type::STRING:
      return "string";
    default:
      spdlog::error("recieved unknown Attribute::Type");
      return "unknown_type";
  }
}
// can throw
Attribute::Type Attribute::typeFromJSON(const jsonf &jtype) {
  const auto type = static_cast<std::string>(jtype);
  if (type == "unit") {
    return Attribute::Type::UNIT;
  } else if (type == "bool") {
    return Attribute::Type::BOOL;
  } else if (type == "uint") {
    return Attribute::Type::U_INT;
  } else if (type == "float") {
    return Attribute::Type::FLOAT;
  } else if (type == "string") {
    return Attribute::Type::STRING;
  } else {
    throw jsonf::other_error::create(501, type + " is not an Attribute::Type", nullptr);
  }
}

}