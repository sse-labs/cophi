#include <filesystem>
#include <iostream>

#include "core/query_registry.hpp"

int main(int argc, char* argv[]) {
  std::cout << "DelphiCpp!" << std::endl;
  auto throwaway = Core::QueryRegistry::instance().getInstance("BinTypeQuery");
  return EXIT_SUCCESS;
}