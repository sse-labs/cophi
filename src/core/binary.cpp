#include <core/binary.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/IR/Verifier.h>

#include <iostream>
#include <cassert>
#include <memory>

namespace Core {

Binary::Binary(const jsonf &jbin) :
  _name(std::make_shared<std::string>(jbin["name"])),
  _path(std::make_shared<std::string>(jbin["path"]))
{ }

jsonf Binary::json() const {
  jsonf ret;
  ret["name"] = *_name;
  ret["path"] = *_path;
  return ret;
}

std::unique_ptr<ReifiedBinary> Binary::reify() {
  std::unique_ptr<ReifiedBinary> ret = nullptr;

  llvm::SMDiagnostic err;
  auto context = std::make_unique<llvm::LLVMContext>();
  auto module = llvm::parseIRFile(*_path, err, *context);

  if (module == nullptr) {
    spdlog::warn("`llvm::parseIRFile()` failed on: `{}`", *_path);
  } else if (llvm::verifyModule(*module)) { // returns true if module is bad
    spdlog::warn("module for `{}` is malformed", *_name);
  } else {
    ret = std::unique_ptr<ReifiedBinary>(new ReifiedBinary(*this, std::move(context), std::move(module)));
    spdlog::debug("reified Binary `{}`", *_name);
  }
  return ret;
}

std::unique_ptr<llvm::Module> ReifiedBinary::getModuleCopy() const {
  if (!_module.get()) {
    spdlog::warn("`getModuleCopy()` from Binary `{}` handed out nullptr", _id.name());
    return nullptr;
  }

  spdlog::debug("cloning module for Binary `{}`...", _id.name());
  auto ret = llvm::CloneModule(*_module);
  spdlog::debug("done cloning module for Binary `{}`.", _id.name());

  return ret;
}

}