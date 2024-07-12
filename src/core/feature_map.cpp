#include <core/feature_map.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <vector>

namespace Core {

void FeatureMap::insert(const std::string &key, const std::vector<Location> &locs) {
  if (this->containsFeature(key)) { // key exists


    auto &val = _M[key];
    val.insert(val.end(), locs.begin(), locs.end());
  } else {
    spdlog::trace("inserting feature `{}` into FeatureMap for the first time", key);
    _M[key] = locs;
  }
}

const std::vector<Location> &FeatureMap::get(const std::string &key) const {
  if (!this->containsFeature(key)) {
    spdlog::warn("attempted to get nonexistant feature `{}` from FeatureMap", key);
    // throw something maybe...?
  }

  return _M.at(key);
}

}