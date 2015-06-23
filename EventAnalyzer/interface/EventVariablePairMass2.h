#ifndef EventVariablePairMass2_h
#define EventVariablePairMass2_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariablePairMass2: public EventVariable{
 public:
  EventVariablePairMass2(TString name, TString productname, TString prefix="") : EventVariable(name),m_prefix(prefix) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariablePairMass2,1);

 private:
  TString m_prefix;
  std::vector<TString> m_productnames;


};

#endif
