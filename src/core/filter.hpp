#ifndef DELPHICPP_FILTER_HPP_
#define DELPHICPP_FILTER_HPP_

#include <core/feature_query.hpp>

#include <nlohmann/json.hpp>

namespace Core {

// we could get much fancier with how to represent filters, but I think this is good enough
// this is applied to a feature map filter it
struct Filter {
// the feature has to appear with [min_locs, max_locs] appearances
Filter(const std::string &query_name, const std::string &query_type, const size_t min, const size_t max) :
       fid(query_name, query_type), min_locs(min), max_locs(max) { }

// the feature has to appear with [min_locs, inf) appearances
Filter(const std::string &query_name, const std::string &query_type, const size_t min) :
       Filter(query_name, query_type, min, std::numeric_limits<size_t>::max()) { }

Filter(const std::string &query_name, const std::string &query_type) :
       Filter(query_name, query_type, 0, std::numeric_limits<size_t>::max()) { }

Filter(const nlohmann::json jfil) : fid(jfil["ftr_id"]) {
  min_locs = jfil.contains("min_locs") ? size_t(jfil["min_locs"])
                                       : 0;
  max_locs = jfil.contains("max_locs") ? size_t(jfil["max_locs"])
                                       : std::numeric_limits<size_t>::max();
}

// the feature that has to appear
FeatureID fid;
// the minimum/maximum number of appearances of the feature the package has to have
size_t min_locs, max_locs;
};
}

#endif  // DELPHICPP_FILTER_HPP_