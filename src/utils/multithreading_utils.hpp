#ifndef DELPHICPP_MULTITHREADINGUTILS_HPP_
#define DELPHICPP_MULTITHREADINGUTILS_HPP_

#include <core/package.hpp>
#include <core/feature_query.hpp>
#include <core/globals/globals.hpp>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <type_traits>

namespace Utils {

// https://stackoverflow.com/a/56268886
template <typename TF, typename TDuration, class... TArgs>
std::result_of_t<TF&&(TArgs&&...)> run_with_timeout(TF&& f, TDuration timeout, TArgs&&... args)
{
    using R = std::result_of_t<TF&&(TArgs&&...)>;
    std::packaged_task<R(TArgs...)> task(f);
    auto future = task.get_future();
    std::thread thr(std::move(task), std::forward<TArgs>(args)...);
    if (future.wait_for(timeout) != std::future_status::timeout)
    {
      thr.join();
      return future.get(); // this will propagate exception from f() if any
    }
    else
    {
      Core::Globals::timeout = true;
      thr.detach();
      throw std::runtime_error("timeout");
    }
}


// using run_on_f_t = bool (&)(std::decay_t<Core::Package const * const>,
//                           std::decay_t<Core::Query::Result * const>,
//                           std::decay_t<std::shared_ptr<std::atomic_bool>>);


using run_on_f_t = bool (Core::Package const * const,
                         Core::Query const * const,
                         Core::Query::Result * const,
                         std::shared_ptr<std::atomic_bool>);

// https://stackoverflow.com/a/56268886
template <typename TDuration>
bool runOn_with_timeout(run_on_f_t f,
                        TDuration timeout,
                        Core::Package const * const pkg,
                        Core::Query const * const query,
                        Core::Query::Result * const res,
                        std::shared_ptr<std::atomic_bool> terminate_flag)
{
  //std::packaged_task<bool(Core::Package const * const, Core::Query::Result * const, std::atomic_bool&)> task(f);
  std::packaged_task<run_on_f_t> task(*f);
  auto future = task.get_future();

  std::thread thr(std::move(task), pkg, query, res, terminate_flag);
  if (future.wait_for(timeout) != std::future_status::timeout)
  {
    thr.join();
    return future.get(); // this will propagate exception from f() if any
  }
  else
  {
    *terminate_flag = true;
    thr.detach();
    return false;
  }
}


using run_on_mul_f_t = bool (Core::Package const * const,
                             std::vector<Core::Query*>&,
                             Core::Query::Result * const,
                             std::shared_ptr<std::atomic_bool>);

template <typename TDuration>
bool run_queries_with_timeout(run_on_mul_f_t f,
                        TDuration timeout,
                        Core::Package const * const pkg,
                        std::vector<Core::Query*> &queries,
                        Core::Query::Result * const res,
                        std::shared_ptr<std::atomic_bool> terminate_flag)
{
  //std::packaged_task<bool(Core::Package const * const, Core::Query::Result * const, std::atomic_bool&)> task(f);
  std::packaged_task<run_on_mul_f_t> task(*f);
  auto future = task.get_future();

  std::thread thr(std::move(task), pkg, std::ref(queries), res, terminate_flag);
  if (future.wait_for(timeout) != std::future_status::timeout)
  {
    thr.join();
    return future.get(); // this will propagate exception from f() if any
  }
  else
  {
    *terminate_flag = true;
    thr.detach();
    return false;
  }
}

// thread safe, intended for 1 producer, many consumers
class PackageQueue {
  public:
    using pkg_t = Core::Package*;

    PackageQueue(const size_t max_capacity);

    void  addPackage(pkg_t pkg);
    pkg_t getPackage();

  private:
    const size_t _max_capacity;
    std::queue<pkg_t> _pkg_queue;

    std::mutex _mtx;
    std::condition_variable _not_empty;
    std::condition_variable _not_full;
};

}

#endif  // DELPHICPP_MULTITHREADINGUTILS_HPP_