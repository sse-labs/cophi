#include <core/queries/utils/query_utils.hpp>

#include <core/package.hpp>

namespace Core::Queries::Utils {

bool isExecutable(const llvm::Module &mod) {
  for (const auto &F : mod) {
    if (F.getName() == "main")
      return true;
  }
  return false;
}

bool forSureCpp(Package const * const pkg) {
  for (const auto &[k, v] : pkg->settings) {
    if (k == "compiler.cppstd" || k == "compiler.libcxx") {
      return true;
    }
  }
  return false;
}

}