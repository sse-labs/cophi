#include "core/binary.hpp"
#include "core/package.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace Core {
Package::Package(const std::string name, const std::string version, std::vector<std::string> bin_paths) : 
                              name(name),          version(version) {
  
  bins = std::vector<Binary>();
  bins.reserve(bin_paths.size());
  for (auto &path : bin_paths) bins.emplace_back(path);
}
}