#include <core/binary.hpp>
#include <core/package.hpp>

#include <string>
#include <vector>

namespace Core {
  bool Package::reifySelf() {
    bool successful = true;
    for (auto &bin : bins) {
      successful &= bin.reifySelf();
    }
    _reified = successful;
    return _reified;
  }
}