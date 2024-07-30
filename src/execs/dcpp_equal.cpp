#include <core/feature_map.hpp>
#include <utils/exec_utils.hpp>
#include <utils/json_utils.hpp>
#include <utils/logging.hpp>

#include <llvm/Support/CommandLine.h>
#include <spdlog/spdlog.h>


#include <iostream>
#include <memory>

using namespace llvm;
using namespace Core;
using namespace Utils;

// Command Line Args
cl::opt<std::string> FirstFM(cl::Positional, cl::desc("<input feature map>"), cl::Required);
cl::opt<std::string> SecondFM(cl::Positional, cl::desc("<input feature map>"), cl::Required);

int main(int argc, char* argv[]) {
  // setup
  cl::ParseCommandLineOptions(argc, argv);
  initializeLogger();

  std::unique_ptr<FeatureMap> fm1 = deserializeFeatureMap(FirstFM);
  std::unique_ptr<FeatureMap> fm2 = deserializeFeatureMap(SecondFM);

  if (!fm1 && !fm2) {
    errAndExit("could not extract Feature Map from " + FirstFM + " and " + SecondFM);
  } else if (!fm1) {
    errAndExit("could not extract Feature Map from " + FirstFM);
  } else if (!fm2) {
    errAndExit("could not extract Feature Map from " + SecondFM);
  }

  if (*fm1 == *fm2) {
    std::cout << "The two feature maps are equal." << std::endl;
  } else {
    std::cout << "The two feature maps are not equal." << std::endl;
  }
  return EXIT_SUCCESS;
}