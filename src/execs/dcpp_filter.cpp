#include <core/package.hpp>
#include <core/feature_map.hpp>
#include <core/filter.hpp>
#include <utils/exec_utils.hpp>
#include <utils/json_utils.hpp>
#include <utils/logging.hpp>

#include <llvm/Support/CommandLine.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

using namespace llvm;
using namespace Core;
using namespace Utils;

// Command Line Args
cl::opt<std::string> FeatureMapFile("m", cl::Required, cl::desc("Path to feature map file"), cl::value_desc("path"));
cl::opt<std::string> FiltersFile("f", cl::Required, cl::desc("Path to filter config file"), cl::value_desc("path"));
cl::opt<std::string> OutputFile("o", cl::Required, cl::desc("Path to output file"), cl::value_desc("path"));

int main(int argc, char* argv[]) {
  // setup
  cl::ParseCommandLineOptions(argc, argv);
  initializeLogger();

  // get filters
  std::vector<Filter> filters;
  if (!parseJSONArray(FiltersFile, &filters)) {
    errAndExit("unable to parse filters file");
  }
  spdlog::info("filters parsed");

  // verify we can write out results
  std::ofstream of(OutputFile);
  if (!of) {
    errAndExit("cannot write to output file");
  }

  // get feature map
  std::unique_ptr<FeatureMap> fm = deserializeFeatureMap(FeatureMapFile);
  if (fm == nullptr) {
    errAndExit("unable to parse feature map file");
  }
  spdlog::info("feature map parsed");

  // filtering
  FilteredFM results = fm->filter(filters);

  // write out the filtered results
  of << results.json().dump(1, '\t');
  of.close();
  spdlog::info("results written out");

  return EXIT_SUCCESS;
}