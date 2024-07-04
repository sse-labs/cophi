#ifndef DELPHICPP_BINARY_HPP_
#define DELPHICPP_BINARY_HPP_

#include <string>

namespace Core {
class Binary {
  public:
    Binary(std::string path) : 
                 _path(path) {  }

  private:
    const std::string _path;
    // llvm::IRModule _module;
};
}

#endif  // DELPHICPP_BINARY_HPP_