#ifndef EventVariableThreshold_h
#define EventVariableThreshold_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableThreshold : public EventVariable{
 public:
  EventVariableThreshold(TString name, TString productname) : EventVariable(name) {m_productnames.push_back(productname);}

  void addProduct(TString);
  void addThreshold(double c){m_thresholds.push_back(c);}

  bool calculate(BaseHandler*);

  ClassDef(EventVariableThreshold,1);

 private:
  std::vector<TString> m_productnames;
  std::vector<double> m_thresholds;

};

#endif
