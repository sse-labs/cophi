#ifndef DELPHICPP_BINARY_HPP_
#define DELPHICPP_BINARY_HPP_

#include <llvm/IR/Module.h>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

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

    // can throw
    Binary(const jsonf &jbin);
    jsonf json() const;

    // try to load the llvm module from the file.
    // return nullptr if unsuccessful
    std::unique_ptr<ReifiedBinary> reify();

    std::string name() const { return *_name; }
    std::string path() const { return *_path; }

    std::shared_ptr<std::string> sharedName() const { return _name; }
    std::shared_ptr<std::string> sharedPath() const { return _path; }

    bool operator==(const Binary &other) const {
      return name() == other.name() &&
             path() == other.path();
    }

  private:
    std::shared_ptr<std::string> _name;
    std::shared_ptr<std::string> _path;
};

// wrapper around llvm bitcode module
// owned by a binary
class ReifiedBinary {
  public:
    // hand out copy of the module
    std::unique_ptr<llvm::Module> getModuleCopy() const;
    
    // hand out const ref to module
    const llvm::Module &getModuleRef() const { return *_module; }

    const Binary &getID() const { return _id; }

  protected:
    friend class Binary;
    ReifiedBinary(const Binary id,
                  std::unique_ptr<llvm::LLVMContext> context,
                  std::unique_ptr<llvm::Module> module) : 
    _id(id), _context(std::move(context)), _module(std::move(module)) {
      spdlog::trace("Binary `{}` succesfully reified", _id.name());
    }

  private:
    Binary _id;
    // we need the context because it owns the module
    std::unique_ptr<llvm::LLVMContext> _context;
    std::unique_ptr<llvm::Module> _module;
};
}

// provide hash for binary so we can use it as a key in a map
template<>
struct std::hash<Core::Binary> {
  std::size_t operator()(const Core::Binary &bin) const {
    return std::hash<std::string>()(bin.name())
         ^ std::hash<std::string>()(bin.path());
  }
};

#endif  // DELPHICPP_BINARY_HPP_