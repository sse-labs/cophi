#include <core/queries/utils/query_utils.hpp>

namespace Core::Queries::Utils {

bool isExecutable(const llvm::Module &mod) {
  for (const auto &F : mod) {
    if (F.getName() == "main")
      return true;
  }
  return false;
}

}