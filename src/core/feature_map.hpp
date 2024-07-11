#ifndef DELPHICPP_FEATUREMAP_HPP_
#define DELPHICPP_FEATUREMAP_HPP_

#include <core/feature_query.hpp>

#include <string>
#include <unordered_map>
#include <vector>


#include <iostream> // remove

namespace Core {

// add struct/class that represents a Filter

class FeatureMap {
  public:
    FeatureMap() = default;
    //FeatureMap(csv file); // implement sometime

    // method to write to csv
    

    // if kv mapping doesn't exist, creates it, otherwise appends locs
    // to _M[key]
    void insert(const std::string &key, const std::vector<Location> &locs);
    //void insert(const std::string &key, const Location &loc);

    bool containsFeature(const std::string &featureID) const noexcept { return _M.find(featureID) != _M.end(); }

    // add exception to throw if key not there
    const std::vector<Location> &get(const std::string &key) const;

    // add method for filtering


    // need iterator


  
    void testPrint() {
      for (const auto &[k, v] : _M) {
        std::cout << k << "\n";
        for (const auto &e : v) {
          std::cout << "\t\tPackage " << e.pkg_name << "/" << e.pkg_version << ", Binary: " << e.bin_name << "\n";
        }
        std::cout << std::endl;
      }
    }


  private:
    // featureID -> Vec<Location>
    std::unordered_map<std::string, std::vector<Location>> _M;
};

}

#endif  // DELPHICPP_FEATUREMAP_HPP_