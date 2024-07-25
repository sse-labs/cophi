#include <core/corpus_analyzer.hpp>
#include <core/package.hpp>
#include <core/feature_map.hpp>
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
cl::opt<std::string> PackagesIndex("p", cl::Required, cl::desc("Path to packages index"), cl::value_desc("path"));
cl::opt<std::string> AnalysisConfig("c", cl::Required, cl::desc("Path to query config"), cl::value_desc("path"));
cl::opt<std::string> OutputFile("o", cl::Required, cl::desc("Path to output file"), cl::value_desc("path"));

int main(int argc, char* argv[]) {
  // setup
  cl::ParseCommandLineOptions(argc, argv);
  initializeLogger();

  // get config
  CorpusAnalyzerConfig conf;
  if (!parseCorpusAnalyzerConfig(AnalysisConfig, &conf.query_subset)) {
    errAndExit("unable to parse query config file");
  }
  spdlog::info("query list parsed");

  // get packages
  std::vector<Package> pkgs;
  if (!parsePackages(PackagesIndex, &pkgs)) {
    errAndExit("unable to parse packages file");
  }
  spdlog::info("packages parsed");

  // verify we can write out results
  std::ofstream of(OutputFile);
  if (!of) {
    errAndExit("cannot write to output file");
  }

  // get the queries
  CorpusAnalyzer ca(conf);
  // run queries on the packages
  std::unique_ptr<FeatureMap> fm = ca.evaluate(pkgs);

  // write out FeatureMap
  of << fm->json().dump(1, '\t');
  of.close();
  spdlog::info("feature map written out");

  return EXIT_SUCCESS;
}