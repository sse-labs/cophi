#ifndef DELPHICPP_BINARY_HPP_
#define DELPHICPP_BINARY_HPP_

#include <llvm/IR/Module.h>

#include <memory>
#include <string>

namespace Core {
class Binary {
  public:
    Binary(std::string *name, std::string path) : 
          name(std::shared_ptr<std::string>(name)),       path(path) {  }

    // cache the internal llvm module, basically
    bool reifySelf();
    // hand out copy of the module
    std::unique_ptr<llvm::Module> getModuleCopy() const;

    const std::shared_ptr<std::string> name;
    const std::string path;

  private:
    std::unique_ptr<llvm::Module> _module = nullptr;
};
}

#endif  // DELPHICPP_BINARY_HPP_