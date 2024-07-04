#ifndef DELPHICPP_QUERYREGISTRY_HPP_
#define DELPHICPP_QUERYREGISTRY_HPP_

#include "core/feature_query.hpp"

#include <cassert>
#include <functional>
#include <map>
// #include <optional>

// helper
#define STRING(a) #a

// macro to register classes which implement query
// Q must be the name of the class which implements Query
#define REGISTER_QUERY(A) \
namespace { \
  bool dummy = Core::QueryRegistry::instance().registerImpl(STRING(A), [](){ return new Core::Queries::A(); }); \
} \


namespace Core {
class QueryRegistry {
  typedef std::function<Query *()> Producer;

  public:
    static QueryRegistry &instance() {
      static QueryRegistry qr;
      return qr;
    }

    bool registerImpl(const std::string &name, Producer p) {
      assert(_registry.find(name) == _registry.end()); // we want the query names to be unique
      _registry[name] = p;
      return true; // dummy
    }

    // std::optional<Query*> getInstance(const std::string &name) const {
    //   const auto it = _registry.find(name);

    //   if (it != _registry.end() && it->second)
    //     return std::make_optional((it->second)());
    //   else
    //     return std::nullopt;
    // }
    Query *getInstance(const std::string &name) const {
      const auto it = _registry.find(name);

      if (it != _registry.end() && it->second)
        return (it->second)();
      else
        return nullptr;
    }

  private:
    std::map<std::string, Producer> _registry;
};
}

#endif  // DELPHICPP_QUERYREGISTRY_HPP_