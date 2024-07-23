#include <core/binary.hpp>

#include <spdlog/spdlog.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/Utils/Cloning.h>

namespace Core {

std::unique_ptr<ReifiedBinary> Binary::reify() {
  std::unique_ptr<ReifiedBinary> ret = nullptr;

  llvm::SMDiagnostic err;
  auto context = std::make_unique<llvm::LLVMContext>();
  auto module = llvm::parseIRFile(*_path, err, *context);

  if (module == nullptr) {
    spdlog::warn("`llvm::parseIRFile()` failed on: `{}`", *_path);
  } else {
    ret = std::unique_ptr<ReifiedBinary>(new ReifiedBinary(_name, _path, std::move(context), std::move(module)));
    spdlog::debug("reified Binary `{}`", *_name);
  }
  return ret;
}

std::unique_ptr<llvm::Module> ReifiedBinary::getModuleCopy() const {
  if (!_module.get()) {
    spdlog::warn("`getModuleCopy()` from Binary `{}` handed out nullptr", *_name);
    return nullptr;
  }
  spdlog::debug("cloning module for Binary `{}`...", *_name);
  return llvm::CloneModule(*_module);
}

}