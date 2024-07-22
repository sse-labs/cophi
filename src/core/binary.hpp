#ifndef DELPHICPP_BINARY_HPP_
#define DELPHICPP_BINARY_HPP_

#include <llvm/IR/Module.h>

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

namespace Core {

// wrapper around a llvm bitcode module
class Binary {
  public:
    // initialize with name / path to bitcode
    Binary(std::shared_ptr<std::string> name, std::shared_ptr<std::string> path) : 
                                   name(name),                        path(path) {
      spdlog::trace("Binary `{}` succesfully constructed", *name);
    }

    // try to load the llvm module from the file. return whether successful
    bool reifySelf();

    // is the binary reified?
    bool isReified() const { return _module != nullptr; }

    // hand out copy of the module, returns nullptr if not reified
    std::unique_ptr<llvm::Module> getModuleCopy() const;

    // public for convenience
    std::shared_ptr<std::string> name;
    std::shared_ptr<std::string> path;

  private:
    std::unique_ptr<llvm::LLVMContext> _context;
    std::unique_ptr<llvm::Module> _module = nullptr;
};
}

#endif  // DELPHICPP_BINARY_HPP_