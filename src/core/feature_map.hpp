#ifndef DELPHICPP_FEATUREMAP_HPP_
#define DELPHICPP_FEATUREMAP_HPP_

#include <core/feature_query.hpp>

#include <string>
#include <unordered_map>
#include <vector>


#include <iostream> // remove
#include <iomanip>  // remove

namespace Core {

// add struct/class that represents a Filter

class FeatureMap {
  public:
    FeatureMap() = default;
    //FeatureMap(csv file); // implement sometime

    // method to write to csv
    bool writeToJSON(const std::string &path) const;
    

    // if kv mapping doesn't exist, creates it, otherwise appends locs
    // to _M[key]
    void insert(const Feature &ftr);
    //void insert(const std::string &key, const Location &loc);

    bool containsFeature(const FeatureID &id) const noexcept;

    // // add exception to throw if key not there
    // const std::vector<Location> &get(const std::string &key) const;

    // add method for filtering


    // need iterator


  
    void testPrint() {
      // for (const auto &[k, v] : _M) {
      //   std::cout << "Query: " << k << "\n";
      //   for (const auto &e : v) {
      //     std::cout << "\tFeature Type: " << e.first << "\n";

      //     for (const auto &loc : e.second) {
      //       const auto pkg = *loc.pkg_name + "/" + *loc.pkg_version;
      //       std::cout << "\t\t" << std::setw(20) << "Package:" << " Binary:\n"
      //                 << "\t\t" << std::setw(20) << pkg        << *loc.bin_name << "\n";
      //     }
      //   }
      //   std::cout << std::endl;
      // }
    }


  private:
    // map from features to where those features have been located
    std::unordered_map<FeatureID, std::vector<Location>> _M;
};

}

#endif  // DELPHICPP_FEATUREMAP_HPP_