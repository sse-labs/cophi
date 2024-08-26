#include <core/corpus_analyzer.hpp>
#include <core/package.hpp>
#include <core/feature_map.hpp>

#include <core/attribute.hpp>

#include <utils/exec_utils.hpp>
#include <utils/json_utils.hpp>
#include <utils/logging.hpp>

#include <llvm/Support/CommandLine.h>
#include <spdlog/spdlog.h>

#include <chrono>
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
cl::opt<std::string> StatsFile("s", cl::Required, cl::desc("Path to stats file"), cl::value_desc("path"));
cl::opt<size_t> Timeout("t", cl::Required, cl::desc("How long to try to evaluate a package for"),
                                           cl::value_desc("duration in minutes"));

int main(int argc, char* argv[]) {
  // setup
  cl::ParseCommandLineOptions(argc, argv);
  initializeLogger();

  // get config
  CorpusAnalyzerConfig conf;
  if (!parseJSONArray<std::string>(AnalysisConfig, &conf.query_subset)) {
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
  std::ofstream of_res(OutputFile);
  if (!of_res) {
    errAndExit("cannot write to output file");
  }

  // verify we can write out stats
  std::ofstream of_stats(StatsFile);
  if (!of_stats) {
    errAndExit("cannot write to stats file");
  }

  // get the queries
  CorpusAnalyzer ca(conf);
  FeatureMap fm;

  spdlog::info("evaluating packages...");
  // max time we should take on a single package
  auto timeout = std::chrono::minutes(Timeout);
  // run queries on the packages
  auto stats = ca.evaluate(pkgs, fm, timeout);
  spdlog::info("done evaluating packages");

  // write out FeatureMap
  of_res << fm.json().dump(1, '\t');
  of_res.close();
  spdlog::info("feature map written out");

  // write out Stats
  of_stats << CorpusAnalyzer::serializeStats(stats).dump(1, '\t');
  of_stats.close();
  spdlog::info("stats written out");

  return EXIT_SUCCESS;
}