#ifndef DELPHICPP_FEATUREMAP_HPP_
#define DELPHICPP_FEATUREMAP_HPP_

#include <core/feature_query.hpp>
#include <core/package.hpp>
#include <core/filter.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Core {

// need to forward declare class
class FilteredFM;

class FeatureMap {
  typedef std::unordered_map<PackageID, std::unordered_set<Feature>> InternalMap;
  public:
    FeatureMap() = default;
    //FeatureMap(csv file); // implement sometime

    // method to write to json
    bool writeToJSON(const std::string &path) const;
    

    // if kv mapping doesn't exist, creates it, otherwise adds ftr to _M[pkgid]
    void insert(const PackageID pkgid, const Feature &ftr);
    //void insert(const std::string &key, const Location &loc);

    bool containsPackage(const PackageID &id) const noexcept;

    // apply filters to this feature map, this affects the iterator it produces
    FilteredFM filter(std::vector<Filter> filters);

  private:
    // map from packages to the features found in those packages
    InternalMap _M;
    friend class FilteredFM;
};

// produced by feature map after giving it filters - provides an
// iterator to go over the filtered results
class FilteredFM {
  public:

    FilteredFM(FeatureMap &fm, std::vector<Filter> filters) :
              _fm(fm), _filters(std::move(filters)) { }

    // iterator stuff
    class iterator {
      public:
        iterator(const FeatureMap &fm, const FeatureMap::InternalMap::iterator it, const std::vector<Filter> &filters) :
                       _fm(fm), _it(it), _filters(filters) {
          while (!currentSatisfies()) _it++;
        }

        // the value type of the iterator
        typedef std::pair<const PackageID&, std::vector<const Feature *>> package_features;

        package_features operator*();
        iterator &operator++();

        bool operator!=(const iterator& other) { return other._it != _it; }

      private:
        // returns whether _it is pointing to a valid element (in terms of _filters)
        bool currentSatisfies() const;

        const FeatureMap &_fm;
        FeatureMap::InternalMap::iterator _it;
        const std::vector<Filter> &_filters;
    };

    iterator begin() const;
    iterator end() const;

  private:
    FeatureMap &_fm;
    std::vector<Filter> _filters;
};

}

#endif  // DELPHICPP_FEATUREMAP_HPP_