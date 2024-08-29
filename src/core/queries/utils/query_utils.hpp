#ifndef DELPHICPP_QUERYUTILS_HPP_
#define DELPHICPP_QUERYUTILS_HPP_

#include <core/package.hpp>

#include <llvm/IR/Module.h>

namespace Core::Queries::Utils {

bool isExecutable(const llvm::Module &mod);

// whether this package is for sure is written in C++
bool forSureCpp(Package const * const pkg);

}

#endif  // DELPHICPP_QUERYUTILS_HPP_