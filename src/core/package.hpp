#ifndef DELPHICPP_PACKAGE_HPP_
#define DELPHICPP_PACKAGE_HPP_

#include <core/binary.hpp>

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

namespace Core {

// unique identifier for a package
struct PackageID {
  PackageID(std::shared_ptr<std::string> _name, std::shared_ptr<std::string> _version) :
                                    name(_name),                     version(_version)  { }
  
  PackageID(const PackageID &other) = default;
  
  // can throw error on malformed json
  PackageID(const nlohmann::json &jid);

  std::shared_ptr<std::string> name,
                               version;

  std::string str() const { return *name + "/" + *version; }

  nlohmann::json json() const;

  // need this so we can use PackageID as the key type in FeatureMap
  bool operator==(const PackageID &other) const {
    return *name == *other.name &&
           *version == *other.version;
  }
};

// a container for unreified (llvm bitcode) binaries + metadata about them
class Package {
  public:
    Package(std::shared_ptr<std::string> name, std::shared_ptr<std::string> version) :
            _pid(name, version) {
      spdlog::debug("successfully constructed Package `{}/{}`", *name, *version);
    }

    // will throw if json is malformed
    Package(const nlohmann::json &jpkg);

    // takes ownership
    void setBins(std::vector<Binary> bins) { _bins = std::move(bins); }

    // attempt to reify this specific package, return whether *all* of the binaries were able
    // to be reified
    bool reify();

    void unreify();

    // returns id used to identify package
    const PackageID &getID() const { return _pid; }
    const std::vector<std::unique_ptr<ReifiedBinary>> &bins() const { return _rbins; }

    // this is all just metadata that conan hands out
    std::unordered_map<std::string, std::string> settings,
                                                 options;
    std::vector<std::string> requires;

  private:
    PackageID _pid;
    std::vector<Binary> _bins;
    std::vector<std::unique_ptr<ReifiedBinary>> _rbins; // the binaries we were able to reify
};
}

// for hashing PackageID so we can use it as a key in FeatureMap
template<>
struct std::hash<Core::PackageID> {
  std::size_t operator()(const Core::PackageID &pid) const {
    return std::hash<std::string>()(*pid.name)
         ^ std::hash<std::string>()(*pid.version);
  }
};

#endif  // DELPHICPP_PACKAGE_HPP_