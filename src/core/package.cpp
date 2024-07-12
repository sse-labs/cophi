#include <core/binary.hpp>
#include <core/package.hpp>

#include <string>
#include <vector>

namespace Core {
  bool Package::reifySelf() {
    spdlog::debug("attempting to reify Package `{}/{}`", *name, *version);
    _reified = true;
    for (auto &bin : bins) {

      bool ret = bin.reifySelf();

      if (!ret) {
        spdlog::warn("failed to reify Binary `{}` in Package `{}/{}`", *bin.name, *name, *version);
      }

      _reified &= ret;
    }

    if (_reified) {
      spdlog::debug("successfully reified Package `{}/{}`", *name, *version);
    } else {
      spdlog::warn("failed to reify Package `{}/{}`", *name, *version);
    }

    return _reified;
  }
}