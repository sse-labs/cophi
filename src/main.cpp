#include <core/corpus_analyzer.hpp>
#include <core/package.hpp>
#include <utils/json_parsers.hpp>
#include <utils/logging.hpp>

#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Welcome to DelphiCpp!\n" << std::endl;

  Utils::initializeLogger();
  spdlog::info("Logger Initialized");

  Core::CorpusAnalyzerConfig conf = {{"BinTypeQuery"}};
  spdlog::info("Initilizing CorpusAnalyzer");
  Core::CorpusAnalyzer ca(conf);
  spdlog::info("CorpusAnalyzer Initialized");

  std::vector<Core::Package> pkgs;
  spdlog::info("Parsing Packages");
  Utils::parsePackages("../bitcode/packages.json", &pkgs);
  spdlog::info("Packages Parsed");

  spdlog::info("Evaluating Packages");
  ca.evaluate(pkgs)->testPrint();
  spdlog::info("Packages Evaluated");

  return EXIT_SUCCESS;
}