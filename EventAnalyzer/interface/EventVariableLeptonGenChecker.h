#ifndef EventVariableLeptonGenChecker_h
#define EventVariableLeptonGenChecker_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableLeptonGenChecker : public EventVariable{
 public:
 EventVariableLeptonGenChecker(TString name, TString productname, TString suffix="") : EventVariable(name), m_suffix(suffix) {m_productnames.push_back(productname);}


  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableLeptonGenChecker,1);

 private:
  TString m_suffix;
  std::vector<TString> m_productnames;

};

#endif
