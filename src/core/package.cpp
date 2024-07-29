#include <core/binary.hpp>
#include <core/package.hpp>

#include <nlohmann/json.hpp>
using jsonf = nlohmann::json;
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace Core {
PackageID::PackageID(const nlohmann::json &jid) :
  name(std::make_shared<std::string>(jid["name"])),
  version(std::make_shared<std::string>(jid["version"]))
{  }

jsonf PackageID::json() const {
  jsonf ret = jsonf::object();
  ret["name"] = *name;
  ret["version"] = *version;
  return ret;
}  

Package::Package(const nlohmann::json &jpkg) :
_pid(std::make_shared<std::string>(jpkg["pkg_name"]),
     std::make_shared<std::string>(jpkg["pkg_version"]))
{
  // getting the binaries
  std::vector<Core::Binary> bins;
  for (const jsonf &e : jpkg["bins"]) {
    const std::string bin_name = e["bin_name"];
    const std::string bin_path = e["bin_path"];
    bins.emplace_back(std::make_shared<std::string>(bin_name), std::make_shared<std::string>(bin_path));
  }
  this->setBins(std::move(bins));

  // getting the metadata
  const jsonf &metadata = jpkg["metadata"];

  if (metadata.contains("settings")) {
    for (const auto &[k, v] : metadata["settings"].items()) {
      if (v.is_string()) {
        settings[k] = v;
      }
    }
  }

  if (metadata.contains("options")) {
    for (const auto &[k, v] : metadata["options"].items()) {
      if (v.is_string()) {
        options[k] = v;
      }
    }
  }

  if (metadata.contains("requires")) {
    for (const auto &elem : metadata["requires"]) {
      if (elem.is_string()) {
        requires.push_back(elem);
      }
    }
  }
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

void Package::unreify() {
  _rbins.clear();
}

}