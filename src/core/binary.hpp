#ifndef DELPHICPP_BINARY_HPP_
#define DELPHICPP_BINARY_HPP_

#include <llvm/IR/Module.h>

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

namespace Core {
class Binary {
  public:
    Binary(std::shared_ptr<std::string> name, std::shared_ptr<std::string> path) : 
                                   name(name),                        path(path) {
      spdlog::trace("Binary `{}` succesfully constructed", *name);
    }

    // cache the internal llvm module, basically
    bool reifySelf();

    bool isReified() const { return _module != nullptr; }
    // hand out copy of the module
    std::unique_ptr<llvm::Module> getModuleCopy() const;

    std::shared_ptr<std::string> name;
    std::shared_ptr<std::string> path;

  private:
    std::unique_ptr<llvm::LLVMContext> _context;
    std::unique_ptr<llvm::Module> _module = nullptr;
};
}

#endif  // DELPHICPP_BINARY_HPP_