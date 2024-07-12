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
  spdlog::info("logger initialized");

  Core::CorpusAnalyzerConfig conf = {{"BinTypeQuery"}};
  spdlog::info("initilizing CorpusAnalyzer...");
  Core::CorpusAnalyzer ca(conf);
  spdlog::info("CorpusAnalyzer initialized.");

  std::vector<Core::Package> pkgs;
  spdlog::info("parsing packages...");
  Utils::parsePackages("../bitcode/packages.json", &pkgs);
  spdlog::info("packages parsed.");

  spdlog::info("evaluating packages...");
  ca.evaluate(pkgs)->testPrint();
  spdlog::info("packages evaluated.");

  return EXIT_SUCCESS;
}