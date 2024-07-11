#include <core/binary.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/Utils/Cloning.h>

namespace Core {

bool Binary::reifySelf() {
  if (_module) { // module already loaded
    return true;
  }

  llvm::LLVMContext context;
  llvm::SMDiagnostic err;

  _module = llvm::parseIRFile(path, err, context);

  // log if failed

  return _module != nullptr;
}

std::unique_ptr<llvm::Module> Binary::getModuleCopy() const {
  if (!_module) {
    // log
    return nullptr;
  }
  return llvm::CloneModule(*_module);
}

}