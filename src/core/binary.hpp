#ifndef DELPHICPP_BINARY_HPP_
#define DELPHICPP_BINARY_HPP_

#include <llvm/IR/Module.h>

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

namespace Core {

// forward declaration
class ReifiedBinary;

// wrapper around the name/path to a llvm bitcode module
class Binary {
  public:
    // initialize with name / path to bitcode
    Binary(std::shared_ptr<std::string> name, std::shared_ptr<std::string> path) : 
           _name(name), _path(path) {  }

    // try to load the llvm module from the file.
    // return nullptr if unsuccessful
    std::unique_ptr<ReifiedBinary> reify();

    std::string name() const { return *_name; }
    std::string path() const { return *_path; }

  private:
    std::shared_ptr<std::string> _name;
    std::shared_ptr<std::string> _path;
};

// llvm bitcode module which has been loaded into memory from a file
class ReifiedBinary {
  public:
    // hand out copy of the module
    std::unique_ptr<llvm::Module> getModuleCopy() const;
    
    // hand out const ref to module
    const llvm::Module &getModuleRef() const { return *_module; }

    std::string name() const { return *_name; }
    std::string path() const { return *_path; }

    std::shared_ptr<std::string> sharedName() const { return _name; }
    std::shared_ptr<std::string> sharedPath() const { return _path; }

  protected:
    friend class Binary;
    ReifiedBinary(std::shared_ptr<std::string> name,
                  std::shared_ptr<std::string> path,
                  std::unique_ptr<llvm::LLVMContext> context,
                  std::unique_ptr<llvm::Module> module) : 
    _name(name), _path(path), _context(std::move(context)), _module(std::move(module)) {
      spdlog::trace("Binary `{}` succesfully reified", *name);
    }

  private:
    std::shared_ptr<std::string> _name;
    std::shared_ptr<std::string> _path;
    // we need the context because it owns the module
    std::unique_ptr<llvm::LLVMContext> _context;
    std::unique_ptr<llvm::Module> _module;
};
}

#endif  // DELPHICPP_BINARY_HPP_