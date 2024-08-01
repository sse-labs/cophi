#ifndef DELPHICPP_ATTRIBUTE_HPP_
#define DELPHICPP_ATTRIBUTE_HPP_

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <string>
#include <variant>

namespace Core {

class Attribute {
  public:
    using var_t = std::variant<std::monostate, bool, size_t, double, std::string>;
    enum Type {
      UNIT,
      BOOL,
      U_INT,
      FLOAT,
      STRING,
    };

    explicit Attribute() noexcept : // unit ctor
             Attribute(Type::UNIT, std::monostate()) { }
    
    explicit Attribute(const bool b) noexcept : // bool ctor
             Attribute(Type::BOOL, b) { }
    
    explicit Attribute(const size_t i) noexcept : // u_int ctor
             Attribute(Type::U_INT, i) { }
    
    explicit Attribute(const double d) noexcept : // float ctor
             Attribute(Type::FLOAT, d) { }
    
    explicit Attribute(const std::string &s) noexcept : // string ctor
             Attribute(Type::STRING, std::string(s)) { }
    
    Attribute(const jsonf &jattr);
    jsonf json() const;

    // which type is this attribute
    Type type() const { return _type; }

    // getters (throws bad_variant_access if type doesn't match)
    bool        getBool()   const { return std::get<bool>(_attr); }
    size_t      getUInt()   const { return std::get<size_t>(_attr); }
    double      getFloat()  const { return std::get<double>(_attr); }
    std::string getString() const { return std::get<std::string>(_attr); }

  private:
    Attribute(Type t, var_t v) noexcept : 
    _type(t), _attr(std::move(v)) {  }

    Type _type;
    var_t _attr;
};

// helpers for converting Attribute::Type to/from json

std::string typeToString(const Attribute::Type type);
// can throw
Attribute::Type typeFromJSON(const jsonf &jtype);

}

#endif  // DELPHICPP_ATTRIBUTE_HPP_