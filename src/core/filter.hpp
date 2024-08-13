#ifndef DELPHICPP_FILTER_HPP_
#define DELPHICPP_FILTER_HPP_

#include <core/attribute.hpp>
#include <core/feature_query.hpp>
#include <core/feature_data.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <cstdlib>
#include <utility>
#include <variant>

namespace Core {

class Range {
  public:
    using range_t = std::variant<std::monostate,
                                 bool,
                                 std::pair<size_t, size_t>,
                                 std::pair<double, double>,
                                 std::string>;
    Range() :
      _type(Attribute::Type::UNIT), _range(std::monostate()) { }

    Range(const bool b) :
      _type(Attribute::Type::BOOL), _range(b) { }
    
    Range(size_t l, size_t u) :
      _type(Attribute::Type::U_INT), _range(std::make_pair<size_t, size_t>(std::move(l), std::move(u))) { }
    
    Range(double l, double u) :
      _type(Attribute::Type::FLOAT), _range(std::make_pair<double, double>(std::move(l), std::move(u))) { }
    
    Range(const std::string &s) :
      _type(Attribute::Type::STRING), _range(std::string(s)) { }

    Range(const jsonf &jrange);

    jsonf json() const;

    // checks if attribute is in the range.
    // precond: attr.type() == this->type()
    bool inRange(const Attribute &attr) const;
    
    Attribute::Type type() const { return _type; }
  private:
    Attribute::Type _type;
    range_t _range;
};

class Filter {
  public:
    enum FilterType {
      // no attribute to check, test() returns true iff this->_fid matches the fid of the Feature
      // (i.e. when the feature is of type FeatureData::Type::UNIT)
      NOATTR,
      // used when the feature just has one attribute
      // (i.e. when the feature is of type FeatureData::Type::ATTR)
      ONEATTR,
      // these two meant to be used when the feature has a bin-attr map
      // (i.e. when the feature is of type FeatureData::Type::BINMAP)
      FORALL,
      EXISTS,
    };

    // precond: fid.attr_type() == range.type()
    //
    // precond: fid.data_type() == UNIT   <--> type == NOATTR
    //          fid.data_type() == ATTR   <--> type == ONEATTR
    //          fid.data_type() == BINMAP <--> type == FORALL | EXISTS
    Filter(const FeatureID &fid, const FilterType type, const Range &range);

    // bit of a hack so we can use FeatureID to search a set of Features
    // not a ctor meant to be used in any other circumstance
    Filter(const FeatureID &fid) : _fid(fid) {
      _type = FilterType::NOATTR;
      _range = Range();
    }

    // throws on malformed json
    Filter(const jsonf &jfilter);

    // evaluates the feature to see if it passes the filter.
    // if `ftr.getUniqueId().type() == this->_fid.type()`, then returns false
    //
    // otherwise, there are two cases in which this method returns true
    //    1. this->_type == FORALL
    //        - all attributes attached to binaries in this feature have to pass the check by _range
    //    2. this->_type == EXISTS
    //        - only one attribute attached to a binary in this feature has to pass the check by _range
    bool test(const Feature &ftr) const;

    FeatureID getFID() const { return _fid; }
    
  private:

    // precond: ftr_data.getDataType() == FeatureData::Type::BINMAP;
    bool testFeatureForAll(const Feature &ftr) const;
    // precond: ftr_data.getDataType() == FeatureData::Type::BINMAP;
    bool testFeatureExists(const Feature &ftr) const;

    FeatureID  _fid;
    FilterType _type;
    Range      _range;
};

}

#endif  // DELPHICPP_FILTER_HPP_