#ifndef DELPHICPP_FEATUREMAP_HPP_
#define DELPHICPP_FEATUREMAP_HPP_

#include <core/feature_query.hpp>
#include <core/package.hpp>
#include <core/filter.hpp>

#include <nlohmann/json.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Core {

// need to forward declare class
class FilteredFM;

// map from packages to the features it contains
class FeatureMap {
  typedef std::unordered_map<PackageID, std::unordered_set<Feature>> InternalMap;
  public:
    FeatureMap() = default;

    // parse from json, can throw if malformed
    FeatureMap(const nlohmann::json &jfm);

    // method to write to json
    bool writeToJSON(const std::string &path) const;
    

    // if kv mapping doesn't exist, creates it, otherwise adds ftr to _M[pkgid]
    void insert(const PackageID pkgid, const Feature &ftr);
    //void insert(const std::string &key, const Location &loc);

    // does the map contain a package with this id?
    bool containsPackage(const PackageID &id) const noexcept;

    // apply filters to this feature map, give back an object, which when
    // iterated over, only shows the packages with the desired features
    FilteredFM filter(std::vector<Filter> filters);

    // serialize FeatureMap to json
    nlohmann::json json() const;

    // for testing
    bool operator==(const FeatureMap &rhs) const { return _M == rhs._M; }
  private:
    // map from packages to the features found in those packages
    InternalMap _M;
    // FilteredFM need to have access to _M to iterate over it
    friend class FilteredFM;
};

// produced by feature map after giving it filters - the only thing it does 
// is provide an iterator over the feature map with filters applied
class FilteredFM {
  public:

    FilteredFM(FeatureMap &fm, std::vector<Filter> filters) :
              _fm(fm), _filters(std::move(filters)) { }

    // the iterator over the filtered results
    class iterator {
      public:
        iterator(const FeatureMap &fm, const FeatureMap::InternalMap::iterator it, const std::vector<Filter> &filters) :
                       _fm(fm), _it(it), _filters(filters) {
          while (!currentSatisfies()) _it++;
        }

        // the value type of the iterator
        typedef std::pair<const PackageID&, std::vector<const Feature *>> package_features;

        // the methods needed for an iterator
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