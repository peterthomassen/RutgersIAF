#ifndef EventVariableAllPairsMass_h
#define EventVariableAllPairsMass_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableAllPairsMass : public EventVariable{
 public:
  EventVariableAllPairsMass(TString name, TString productname) : EventVariable(name) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableAllPairsMass,1);

 private:
  std::vector<TString> m_productnames;


};

#endif
