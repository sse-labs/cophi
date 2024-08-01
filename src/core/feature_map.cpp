#include <core/feature_map.hpp>
#include <core/feature_query.hpp>
#include <utils/json_utils.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <fstream>
#include <memory>
#include <vector>

namespace Core {

FeatureMap::FeatureMap(const jsonf &jfm) {
  for (const auto &elem : jfm) {
    Core::PackageID pid(elem["pkg_id"]);
    auto ftr_set = Utils::parseFeatureSet(elem["ftr_set"]);

    _M.insert(std::make_pair(pid, std::move(ftr_set)));
  }
}

void FeatureMap::insert(const PackageID pkgid, const Feature &ftr) {
  _insertMutex.lock();
  if (this->containsPackage(pkgid)) { // key exists
    _M[pkgid].insert(std::move(ftr));
  } else {
    spdlog::trace("inserting feature `{}` into FeatureMap for the first time", ftr.getUniqueId().toString());
    _M[pkgid] = std::unordered_set<Feature> {ftr};
  }
  _insertMutex.unlock();
}

bool FeatureMap::containsPackage(const PackageID &id) const noexcept {
  return _M.find(id) != _M.end();
}

FilteredFM FeatureMap::filter(std::vector<Filter> filters) {
  return FilteredFM(*this, std::move(filters));
}

jsonf FeatureMap::json() const {  
  jsonf ret = jsonf::array();
  for (const auto &[key, val] : _M) {
    jsonf mapping = jsonf::object();

    mapping["pkg_id"] = key.json();

    jsonf ftr_set = jsonf::array();
    for (const auto &ftr : val) {
      ftr_set.push_back(ftr.json());
    }
    mapping["ftr_set"] = ftr_set;

    ret.push_back(mapping);
  }
  return ret;
}

jsonf FilteredFM::json() const {  
  jsonf ret = jsonf::array();

  for (const auto [key, val] : *this) {
    jsonf mapping = jsonf::object();
  
    mapping["pkg_id"] = key.json();

    jsonf ftr_set = jsonf::array();
    for (const auto &ftr : val) {
      ftr_set.push_back(ftr->json());
    }
    mapping["ftr_set"] = ftr_set;

    ret.push_back(mapping);
  }
  return ret;
}

/******************
 * Iterator Stuff *
 ******************/
using FMIterator = FilteredFM::iterator;

bool FMIterator::currentSatisfies() const {
  if (_it == _fm._M.end()) {
    return true;
  }

  const auto ftrs = _it->second;

  for (const auto &filter : _filters) {
    const auto it = ftrs.find(filter.fid);
    
    if (it != ftrs.end()) {
      const int num_locs = it->numLocs();
      if (num_locs < filter.min_locs || num_locs > filter.max_locs) {
        return false;
      }
    } else {
      return false;
    }
  }

  return true;
}

FMIterator &FMIterator::operator++() {
  if (_it == _fm._M.end()) {
    return *this;
  }
  _it++;
  while (!currentSatisfies()) _it++;
  return *this;
}

FMIterator::package_features FMIterator::operator*() {
  if (_it == _fm._M.end()) {
    
  }

  const PackageID &pkgid = _it->first;
  auto &ftr_set = _it->second;

  // getting the features in the filter
  std::vector<const Feature *> ftrs;
  for (const auto &fltr : _filters) {
    auto *ftr_ref = &*ftr_set.find(fltr.fid);
    ftrs.push_back(ftr_ref);
  }

  return std::make_pair<PackageID, std::vector<const Feature *>>(PackageID(pkgid), std::move(ftrs));
}

FMIterator FilteredFM::begin() const {
  return FMIterator(_fm, _fm._M.begin(), _filters);
}

FMIterator FilteredFM::end() const {
  return FMIterator(_fm, _fm._M.end(), _filters);
}

}