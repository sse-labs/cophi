#include <core/feature_map.hpp>

#include <memory>
#include <vector>

namespace Core {

void FeatureMap::insert(const std::string &key, const std::vector<Location> &locs) {
  if (this->containsFeature(key)) { // key exists
    auto &val = _M[key];
    val.insert(val.end(), locs.begin(), locs.end());
  } else {
    _M[key] = std::vector<Location>();
    _M[key] = locs;
  }
}

const std::vector<Location> &FeatureMap::get(const std::string &key) const {
  if (!this->containsFeature(key)) {
    // throw something...?
  }

  return _M.at(key);
}

}