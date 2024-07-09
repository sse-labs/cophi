#ifndef DELPHICPP_PACKAGE_HPP_
#define DELPHICPP_PACKAGE_HPP_

#include <core/binary.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace Core {
class Package {
  public:
    Package(const std::string name, const std::string version, std::vector<std::string> bin_paths);

    const std::string name,
                      version;
    std::vector<Binary> bins;

    std::unordered_map<std::string, std::string> settings,
                                                 options;
    std::vector<std::string> requires;
};
}

#endif  // DELPHICPP_PACKAGE_HPP_