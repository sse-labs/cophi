#ifndef DELPHICPP_PACKAGE_HPP_
#define DELPHICPP_PACKAGE_HPP_

#include <core/binary.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

namespace Core {

struct PackageID {
  PackageID(std::shared_ptr<std::string> _name, std::shared_ptr<std::string> _version) :
                                    name(_name),                     version(_version)  { }
  std::shared_ptr<std::string> name,
                               version;

  bool operator==(const PackageID &other) const {
    return *name == *other.name &&
           *version == *other.version;
  }
};

// a container for (llvm bitcode) binaries + metadata about them
class Package {
  public:
    Package(std::shared_ptr<std::string> _name, std::shared_ptr<std::string> _version) :
                                    name(_name),                     version(_version) {
      spdlog::debug("successfully constructed Package `{}/{}`", *name, *version);
    }

    // attempt to reify this specific package, return whether successful
    // reification is said to be successful if *all* of the binaries are able
    // to be reified
    bool reifySelf();
    bool isReified() const { return _reified; }

    // returns id used to identify package
    PackageID getID() const { return PackageID(name, version); }

    std::shared_ptr<std::string> name,
                                 version;
    std::vector<Binary> bins;

    // this is all just metadata that conan hands out
    std::unordered_map<std::string, std::string> settings,
                                                 options;
    std::vector<std::string> requires;

  private:
    bool _reified = false;
};

}

// for hashing PackageID so we can use it as a key in a map
template<>
struct std::hash<Core::PackageID> {
  std::size_t operator()(const Core::PackageID &pid) const {
    return (std::hash<std::string>()(*pid.name)
         ^ (std::hash<std::string>()(*pid.version) << 1));
  }
};

#endif  // DELPHICPP_PACKAGE_HPP_