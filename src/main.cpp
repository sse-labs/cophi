#include <core/corpus_analyzer.hpp>
#include <core/package.hpp>
#include <core/query_registry.hpp>
#include <core/feature_query.hpp>
#include <utils/json_parsers.hpp>

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Welcome to DelphiCpp!\n" << std::endl;

  Core::CorpusAnalyzerConfig conf = {{"BinTypeQuery"}};
  Core::CorpusAnalyzer ca(conf);

  //auto bintype = std::unique_ptr<Core::Query>(Core::QueryRegistry::singleton().getInstanceOf("BinTypeQuery"));

  std::vector<Core::Package> pkgs;
  Utils::parsePackages("../bitcode/packages.json", &pkgs);

  //std::vector<Core::QueryResult> results(pkgs.size());

  ca.evaluate(pkgs)->testPrint();

  // for (int i = 0; i < pkgs.size(); i++) {
  //   bintype->runOn(pkgs[i], &results[i]); 
  // }

  // for (auto &res : results) {
  //   for (auto &feature : res) {
  //     std::cout << feature.getUniqueId() << ": " << feature.count << std::endl;
  //   }
  //   std::cout << std::endl;
  // }

  return EXIT_SUCCESS;
}