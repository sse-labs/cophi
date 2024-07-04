#ifndef DELPHICPP_PACKAGE_HPP_
#define DELPHICPP_PACKAGE_HPP_

#include "core/binary.hpp"

#include <string>
#include <vector>

namespace Core {
class Package {
  public:
    Package(const std::string name, const std::string version) : 
                        _name(name),         _version(version) {  }

  private:
    const std::string _name,
                      _version;
    std::vector<Binary> _bins;

    std::unordered_map<std::string, std::string> _settings,
                                                 _options;
    std::vector<std::string> _requires;
};
}

#endif  // DELPHICPP_PACKAGE_HPP_