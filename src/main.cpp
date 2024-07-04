#include "core/package.hpp"
#include "core/query_registry.hpp"
#include "core/feature_query.hpp"

#include <filesystem>
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
  std::cout << "DelphiCpp!" << std::endl;
  Core::Query *throwaway = Core::QueryRegistry::singleton().getInstanceOf("BinTypeQuery");

  Core::Package pkg("wow", "version me");

  delete throwaway;
  return EXIT_SUCCESS;
}