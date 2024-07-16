#include <core/feature_map.hpp>
#include <core/feature_query.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <vector>

namespace Core {

void FeatureMap::insert(const Feature &ftr) {
  if (this->containsFeature(ftr.fid)) { // key exists


    auto &val = _M[ftr.fid];
    val.insert(val.end(), ftr.locs.begin(), ftr.locs.end());
  } else {
    spdlog::trace("inserting feature `{}` into FeatureMap for the first time", ftr.fid.toString());
    _M[ftr.fid] = ftr.locs;
  }
}

// const std::vector<Location> &FeatureMap::get(const std::string &key) const {
//   if (!this->containsFeature(key)) {
//     spdlog::warn("attempted to get nonexistant feature `{}` from FeatureMap", key);
//     // throw something maybe...?
//   }

//   return _M.at(key);
// }

bool FeatureMap::containsFeature(const FeatureID &id) const noexcept {
  return _M.find(id) != _M.end();
}

bool FeatureMap::writeToJSON(const std::string &path) const {

  return true;
}

}