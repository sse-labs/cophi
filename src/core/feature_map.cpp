#include <core/feature_map.hpp>
#include <core/feature_query.hpp>

#include <spdlog/spdlog.h>
#include <utils/json_utils.hpp>

#include <fstream>
#include <memory>
#include <vector>

namespace Core {

void FeatureMap::insert(const PackageID pkgid, const Feature &ftr) {
  if (this->containsPackage(pkgid)) { // key exists
    _M[pkgid].insert(std::move(ftr));
  } else {
    spdlog::trace("inserting feature `{}` into FeatureMap for the first time", ftr.fid.toString());
    _M[pkgid] = std::unordered_set<Feature> {ftr};
  }
}

bool FeatureMap::containsPackage(const PackageID &id) const noexcept {
  return _M.find(id) != _M.end();
}

bool FeatureMap::writeToJSON(const std::string &path) const {
  // TODO
  return true;
}

FilteredFM FeatureMap::filter(std::vector<Filter> filters) {
  return FilteredFM(*this, std::move(filters));
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
      const int num_locs = it->locs.size();
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

  return std::make_pair<const PackageID&, std::vector<const Feature *>>(pkgid, std::move(ftrs));
}

FMIterator FilteredFM::begin() const {
  return FMIterator(_fm, _fm._M.begin(), _filters);
}

FMIterator FilteredFM::end() const {
  return FMIterator(_fm, _fm._M.end(), _filters);
}

}