#ifndef EventVariableSumPT_h
#define EventVariableSumPT_h

#include <vector>
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"

class EventVariableSumPT : public EventVariable{

  EventVariableSumPT(TString name, TString productname) : EventVariable(name) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableSumPT,1);

 private:
  std::vector<TString> m_productnames;


};

#endif