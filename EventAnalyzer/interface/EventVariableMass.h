#ifndef EventVariableMass_h
#define EventVariableMass_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableMass : public EventVariable{
 public:
  EventVariableMass(TString name, TString productname) : EventVariable(name) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableMass,1);

 private:
  std::vector<TString> m_productnames;


};

#endif
