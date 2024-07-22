#include <core/corpus_analyzer.hpp>
#include <core/package.hpp>
#include <core/feature_map.hpp>
#include <core/filter.hpp>
#include <utils/json_utils.hpp>
#include <utils/logging.hpp>

#include <llvm/Support/CommandLine.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

using namespace llvm;

// Command Line Args
cl::opt<std::string> PackagesIndex("p", cl::Required, cl::desc("Path to packages index"), cl::value_desc("path"));
cl::opt<std::string> AnalysisConfig("c", cl::Required, cl::desc("Path to query config"), cl::value_desc("path"));
cl::opt<std::string> OutputPath("o", cl::Required, cl::desc("Path to output file"), cl::value_desc("path"));

// Helpers


int main(int argc, char* argv[]) {
  cl::ParseCommandLineOptions(argc, argv);

  Utils::initializeLogger();
  spdlog::info("logger initialized");

  Core::CorpusAnalyzerConfig conf = {{"BinTypeQuery"}};
  spdlog::info("initilizing CorpusAnalyzer...");
  Core::CorpusAnalyzer ca(conf);
  spdlog::info("CorpusAnalyzer initialized.");

  std::vector<Core::Package> pkgs;
  spdlog::info("parsing packages...");
  std::ifstream ifs("../bitcode/packages.json");
  Utils::parsePackages(ifs, &pkgs);
  ifs.close();
  spdlog::info("packages parsed.");

  spdlog::info("evaluating packages...");
  auto fm = ca.evaluate(pkgs);
  spdlog::info("packages evaluated.");

  auto filters = { Core::Filter("BinTypeQuery", "exe") };

  for (const auto &[pkg, ftrs] : fm->filter(filters)) {
    const auto name = *pkg.name;
    const auto version = *pkg.version;
    std::cout << "\tPackage: " << name << "/" << version << "\n"
              << "\t\tExecutables:\n";
    for (const auto &loc : ftrs[0]->locs) {
      std::cout << "\t\t\t" << *loc.bin_name << "\n";
    }
    std::cout << std::endl;
  }

  //feature_map->writeToJSON(OutputPath);

  return EXIT_SUCCESS;
}