#ifndef EventVariableLeptonLTChecker_h
#define EventVariableLeptonLTChecker_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableLeptonLTChecker : public EventVariable{
 public:
 EventVariableLeptonLTChecker(TString name, TString productname, TString prefix="") : EventVariable(name), m_prefix(prefix) {m_productnames.push_back(productname);}


  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableLeptonLTChecker,1);

 private:
  TString m_prefix;
  std::vector<TString> m_productnames;
  bool m_includeFakes;


};

#endif
