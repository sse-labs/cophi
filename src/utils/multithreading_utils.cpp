#include <utils/multithreading_utils.hpp>

#include <core/package.hpp>

#include <spdlog/spdlog.h>

#include <condition_variable>
#include <mutex>
#include <queue>

namespace Utils {

PackageQueue::PackageQueue(const size_t max_capacity) :
                          _max_capacity(max_capacity) { }

void PackageQueue::addPackage(pkg_t pkg) {
  std::unique_lock<std::mutex> unique_lock(_mtx);

  _not_full.wait(unique_lock, [this]() {
    return this->_pkg_queue.size() < this->_max_capacity;
  });

  const std::string name = pkg->getID().str();

  // if we can't reify the package, don't add it
  spdlog::info("reifing `{}`...", name);
  if (!pkg->reify()) {
    spdlog::warn("failed to reify `{}`!", name);
    pkg->unreify();
    return;
  }
  spdlog::info("successfully reified `{}`!", name);

  _pkg_queue.emplace(pkg);

  spdlog::debug("added `{}` to work queue", pkg->getID().str());

  _not_empty.notify_one();
}

PackageQueue::pkg_t PackageQueue::getPackage() {
  std::unique_lock<std::mutex> unique_lock(_mtx);

  _not_empty.wait(unique_lock, [this]() {
    return _pkg_queue.size() > 0;
  });

  pkg_t ret = _pkg_queue.front();
  _pkg_queue.pop();

  spdlog::debug("popped `{}` off work queue", ret->getID().str());

  _not_full.notify_one();

  return ret;
}

}
