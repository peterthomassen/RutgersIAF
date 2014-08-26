#ifndef EventVariableN_h
#define EventVariableN_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableN : public EventVariable{
 public:
  EventVariableN(TString name, TString productname) : EventVariable(name) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableN,1);

 private:
  std::vector<TString> m_productnames;


};

#endif
