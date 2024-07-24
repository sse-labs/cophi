#include <core/binary.hpp>
#include <core/package.hpp>

#include <nlohmann/json.hpp>

#include <string>
#include <memory>
#include <vector>

namespace Core {
  PackageID::PackageID(const nlohmann::json &jid) {
    name = std::make_shared<std::string>(jid["name"]);
    version = std::make_shared<std::string>(jid["version"]);
  }

  bool Package::reify() {
    _rbins.clear();

    spdlog::debug("attempting to reify Package `{}`", _pid.str());
    bool success = true;
    for (auto &bin : _bins) {

      auto rbin = bin.reify();

      if (!rbin) {
        success = false;
        spdlog::warn("failed to reify Binary `{}` in Package `{}`", bin.name(), _pid.str());
      } else {
        _rbins.emplace_back(std::move(rbin));
      }
    }

    if (success) {
      spdlog::debug("successfully reified Package `{}`", _pid.str());
    } else {
      spdlog::warn("failed to reify Package `{}`", _pid.str());
    }

    return success;
  }
}