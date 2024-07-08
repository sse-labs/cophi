#include "core/package.hpp"
#include "core/query_registry.hpp"
#include "core/feature_query.hpp"

#include <filesystem>
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
  std::cout << "DelphiCpp!\n" << std::endl;
  auto bintype = std::unique_ptr<Core::Query>(Core::QueryRegistry::singleton().getInstanceOf("BinTypeQuery"));

  std::string prefix("../bitcode/libiconv/1.17/");
  std::vector<std::string> bins {prefix + "iconv.bc", prefix + "libcharset.a.bc", prefix + "libiconv.a.bc"};
  Core::Package pkg("libiconv", "1.17", bins);

  Core::QueryResult results;
  bintype->runOn(pkg, &results);

  for (auto &res : results)
    std::cout << res.getUniqueId() << ": " << res.count << std::endl;

  return EXIT_SUCCESS;
}