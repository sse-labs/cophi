#include <core/binary.hpp>

#include <spdlog/spdlog.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/Utils/Cloning.h>

namespace Core {

bool Binary::reifySelf() {
  if (_module) { // module already loaded
    spdlog::warn("called `reifySelf()` on already reified Binary {}", *name);
    return true;
  }

  llvm::LLVMContext context;
  llvm::SMDiagnostic err;

  _module = llvm::parseIRFile(*path, err, context);

  bool ret = _module != nullptr;
  if (!ret) {
    spdlog::warn("`llvm::parseIRFile()` failed on: `{}`", *path);
  }
  spdlog::debug("reified Binary `{}`", *name);
  return ret;
}

std::unique_ptr<llvm::Module> Binary::getModuleCopy() const {
  if (!_module.get()) {
    spdlog::warn("`getModuleCopy()` from Binary `{}` handed out nullptr", *name);
    return nullptr;
  }
  spdlog::debug("cloning module for Binary {}...", *name);
  return llvm::CloneModule(*_module);
}

}