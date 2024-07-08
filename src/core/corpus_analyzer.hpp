#ifndef DELPHICPP_PACKAGEANALYZER_HPP_
#define DELPHICPP_PACKAGEANALYZER_HPP_

#include "core/package.hpp"
#include "core/feature_query.hpp"

namespace Core {
class CorpusAnalyzer {
  public:
    CorpusAnalyzer(Package &pkg) : _pkg(pkg) { }
    void evaluateOn(Query &qry) const; // add result
  private:
    Package &_pkg;
};
}

#endif  // DELPHICPP_PACKAGEANALYZER_HPP_