#ifndef DELPHICPP_ATTRMAPPING_HPP_
#define DELPHICPP_ATTRMAPPING_HPP_

#include <core/attribute.hpp>
#include <core/binary.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <unordered_map>

namespace Core {

class BinAttrMap {
  public:
    BinAttrMap(Attribute::Type type) : _attr_type(type), _bin_mapping({}) {  }

    // throws if attr.type() != this->_attr_type
    void insert(const Binary &bin, const Attribute &attr);
    
    // can throw
    BinAttrMap(const jsonf &jattr_map);
    jsonf json() const;

    // accessors
    Attribute::Type attrType() const { return _attr_type; }

    const std::unordered_map<Binary, Attribute> &getMapping() const {
      return _bin_mapping;
    }

    // iter stuff
    using const_iterator = std::unordered_map<Binary, Attribute>::const_iterator;

    const_iterator begin() const { return _bin_mapping.cbegin(); }
    const_iterator end() const { return _bin_mapping.cend(); }

  private:
    Attribute::Type _attr_type;
    std::unordered_map<Binary, Attribute> _bin_mapping;
};

}

#endif  // DELPHICPP_ATTRMAPPING_HPP_