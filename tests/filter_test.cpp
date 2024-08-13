// #include <core/feature_map.hpp>
// #include <core/feature_query.hpp>
// #include <core/package.hpp>
// #include <core/filter.hpp>

// #include <gtest/gtest.h>

// #include <string>
// #include <vector>

// namespace testing {

// class FeatureMapTest : public testing::Test {
//   protected:
//     void insert(std::string pkg, std::string ftr, size_t num_locs) {
//       fm.insert(Core::PackageID(std::make_shared<std::string>(""), std::make_shared<std::string>(pkg)),
//                 Core::Feature(Core::FeatureID("", ftr)));
//     }

//     // sets up feature map with `num_mappings` mappings. for package i in
//     // the feature map, it will have i+1 features ([0, i]), and for each
//     // feature j, it has i locations
//     void SetUp() override {
//      for (int i = 0; i < num_mappings; i++) { // "packages"
//         for (int j = 0; j <= i; j++) { // features + how many times they appear
//           insert(std::to_string(i), std::to_string(j), i);
//         }
//       }
//     }

//     // thing we're testing
//     Core::FeatureMap fm;
//     // controls how many mapping we put into the map
//     const int num_mappings = 1000;
// };

// TEST_F(FeatureMapTest, NoFilters) {
//   std::vector<bool> pkgs_seen(num_mappings, false);

//   for (const auto &[pkgid, ftr_set] : fm.filter({})) {
//     int pkg_num = std::stoi(*pkgid.version);
//     bool in_bounds = pkg_num >= 0 && pkg_num < num_mappings;
//     EXPECT_TRUE(in_bounds);
//     EXPECT_EQ(0, ftr_set.size());
//     if (in_bounds) pkgs_seen[pkg_num] = true;
//   }

//   for (const bool seen : pkgs_seen)
//     EXPECT_TRUE(seen);
// }

// TEST_F(FeatureMapTest, OneFilter) {
//   std::vector<bool> pkgs_seen(num_mappings, false);

//   for (const auto &[pkgid, ftr_set] : fm.filter({Core::Filter("", "0", 0)})) {
//     int pkg_num = std::stoi(*pkgid.version);
//     bool in_bounds = pkg_num >= 0 && pkg_num < num_mappings;
//     EXPECT_TRUE(in_bounds);
//     EXPECT_EQ(1, ftr_set.size());
//     if (in_bounds) pkgs_seen[pkg_num] = true;
//   }

//   for (const bool seen : pkgs_seen)
//     EXPECT_TRUE(seen);
// }

// TEST_F(FeatureMapTest, FilterHalf) {
//   std::vector<bool> pkgs_seen(num_mappings, false);

//   int half = num_mappings / 2;

//   for (const auto &[pkgid, ftr_set] : fm.filter({Core::Filter("", std::to_string(half), half)})) {
//     int pkg_num = std::stoi(*pkgid.version);
//     bool in_bounds = pkg_num >= 0 && pkg_num < num_mappings;
//     EXPECT_TRUE(in_bounds);
//     EXPECT_EQ(1, ftr_set.size());
//     if (in_bounds) pkgs_seen[pkg_num] = true;
//   }

//   for (int i = 0; i < num_mappings; i++) {
//     if (i < half) {
//       EXPECT_FALSE(pkgs_seen[i]);
//     } else {
//       EXPECT_TRUE(pkgs_seen[i]);
//     }
//   }
// }

// TEST_F(FeatureMapTest, FilterInterval) {
//   std::vector<bool> pkgs_seen(num_mappings, false);

//   int one_fourth = num_mappings / 4;
//   int three_fourths = 3 * (num_mappings / 4);

//   for (const auto &[pkgid, ftr_set] : fm.filter({Core::Filter("", std::to_string(one_fourth), one_fourth, three_fourths)})) {
//     int pkg_num = std::stoi(*pkgid.version);
//     bool in_bounds = pkg_num >= 0 && pkg_num < num_mappings;
//     EXPECT_TRUE(in_bounds);
//     EXPECT_EQ(1, ftr_set.size());
//     if (in_bounds) pkgs_seen[pkg_num] = true;
//   }

//   for (int i = 0; i < num_mappings; i++) {
//     if (i >= one_fourth && i <= three_fourths) {
//       EXPECT_TRUE(pkgs_seen[i]);
//     } else {
//       EXPECT_FALSE(pkgs_seen[i]);
//     }
//   }
// }

// TEST_F(FeatureMapTest, FilterTwoIntervals) {
//   std::vector<bool> pkgs_seen(num_mappings, false);

//   int one_fourth = num_mappings / 4;
//   int half = num_mappings / 2;
//   int three_fourths = 3 * (num_mappings / 4);

//   for (const auto &[pkgid, ftr_set] : fm.filter({Core::Filter("", std::to_string(one_fourth), one_fourth, three_fourths),
//                                                  Core::Filter("", std::to_string(half), half)})) {
//     int pkg_num = std::stoi(*pkgid.version);
//     bool in_bounds = pkg_num >= 0 && pkg_num < num_mappings;
//     EXPECT_TRUE(in_bounds);
//     EXPECT_EQ(2, ftr_set.size());
//     if (in_bounds) pkgs_seen[pkg_num] = true;
//   }

//   for (int i = 0; i < num_mappings; i++) {
//     if (i >= half && i <= three_fourths) {
//       EXPECT_TRUE(pkgs_seen[i]);
//     } else {
//       EXPECT_FALSE(pkgs_seen[i]);
//     }
//   }
// }

// }