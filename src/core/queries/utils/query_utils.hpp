#ifndef DELPHICPP_QUERYUTILS_HPP_
#define DELPHICPP_QUERYUTILS_HPP_

#include <llvm/IR/Module.h>

namespace Core::Queries::Utils {

bool isExecutable(const llvm::Module &mod);

}

#endif  // DELPHICPP_QUERYUTILS_HPP_