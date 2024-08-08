#ifndef DELPHICPP_ATTRMAPPING_HPP_
#define DELPHICPP_ATTRMAPPING_HPP_

#include <core/attribute.hpp>
#include <core/binary.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <string>
#include <variant>
#include <unordered_map>

namespace Core {

class AttrMapping {
  public:
    AttrMapping(const Binary &bin, Attribute attr) :
                 _bin(bin), _attr(std::move(attr)) {  }
    
    // can throw
    AttrMapping(const jsonf &jattr_map) :
      _bin(jattr_map["bin"]), _attr(jattr_map["attr"]) {  }
    
    jsonf json() const {
      jsonf ret = jsonf::object();
      ret["bin"] = _bin.json();
      ret["attr"] = _attr.json();
      return ret;
    }

    const Binary &getBin() const { return _bin; }
    const Attribute &getAttr() const { return _attr; }
  private:
    Binary _bin;
    Attribute _attr;
};

}

#endif  // DELPHICPP_ATTRMAPPING_HPP_