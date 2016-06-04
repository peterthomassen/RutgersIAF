#ifndef EventVariableLinearRadialMoment_h
#define EventVariableLinearRadialMoment_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableLinearRadialMoment : public EventVariable{
 public:
 EventVariableLinearRadialMoment(TString name, TString productname) : EventVariable(name) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableLinearRadialMoment,1);

 private:
  std::vector<TString> m_productnames;

};

#endif
