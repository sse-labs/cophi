// #include <core/queries/call_graph_size_query.hpp>
// #include <core/queries/is_exec_query.hpp>
// #include <core/queries/longest_inheritance_chain_query.hpp>

// #include <core/binary.hpp>
// #include <core/package.hpp>

// #include <gtest/gtest.h>

// #include <cassert>
// #include <string>
// #include <vector>

// namespace Core::Queries::Tests {

// const std::vector<std::string> bins {
//   "an_exec",
//   "buncha_calls",
//   "buncha_classes",
//   "just_main_basically",
//   "not_an_exec",
// }

// const std::vector<Binary> bins {
//   Binary(std::make_shared<std::string>(bins[0]), std::make_shared<std::string>("../test_bitcode/an_exec.ll")),
//   Binary(std::make_shared<std::string>(bins[1]), std::make_shared<std::string>("../test_bitcode/buncha_calls.ll")),
//   Binary(std::make_shared<std::string>(bins[2]), std::make_shared<std::string>("../test_bitcode/buncha_classes.ll")),
//   Binary(std::make_shared<std::string>(bins[3]), std::make_shared<std::string>("../test_bitcode/just_main_basically.ll")),
//   Binary(std::make_shared<std::string>(bins[4]), std::make_shared<std::string>("../test_bitcode/not_an_exec.ll")),
// };

// class QueryTests : public testing::Test {
//   protected:
//     // sets up package with all binaries from directory `test_bitcode`
//     QueryTests() : pkg(std::make_shared<std::string>("pkg"),
//                        std::make_shared<std::string>("version"))
//     {
//       pkg.setBins(bins);
//     }

//     void SetUp() override {
//       assert(pkg.reify());
//     }

//     // package we put through the queries
//     Package pkg;
// };

// // macro to test binary for attribute

// TEST_F(QueryTests, CallGraphSizeQuery) {
//   const auto cg_query = CallGraphSizeQuery("CallGraphSizeQuery");
//   Query::Result res;

//   cg_query.runOn(&pkg, &res);

//   auto it = res.find(Feature(FeatureID(cg_query,
//                              CallGraphSizeQuery::Type::NODE,
//                              Attribute::Type::U_INT)));
  
//   EXPECT_TRUE(it != res.end());

//   // still unsure about call graph query, come back to later TODO
// }

// TEST_F(QueryTests, IsExecQuery) {
//   const auto is_exec_query = IsExecQuery("IsExecQuery");
//   Query::Result res;

//   is_exec_query.runOn(&pkg, &res);

//   auto it = res.find(Feature(FeatureID(is_exec_query,
//                              IsExecQuery::Type::UNIT,
//                              Attribute::Type::BOOL)));
  
//   EXPECT_TRUE(it != res.end());

//   const auto &data = it->getData;

// } 

// }