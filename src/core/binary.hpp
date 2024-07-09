#ifndef DELPHICPP_BINARY_HPP_
#define DELPHICPP_BINARY_HPP_

#include <llvm/IR/Module.h>

#include <string>

namespace Core {
class Binary {
  public:
    Binary(std::string name, std::string path) : 
                  name(name),       path(path) {  }

    const std::string name;
    const std::string path;
    // llvm::IRModule _module;
};
}

#endif  // DELPHICPP_BINARY_HPP_