#ifndef EventVariableObjectWeightPtTF1_h
#define EventVariableObjectWeightPtTF1_h

#include <vector>
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include <TF1.h>

class EventVariableObjectWeightPtTF1 : public EventVariable{
 public:
  EventVariableObjectWeightPtTF1(TString name, TString productname, TF1* f) : EventVariable(name) { m_productnames.push_back(productname);m_function = f;}

  void addProduct(TString);

  bool calculate(BaseHandler* handler);

  ClassDef(EventVariableObjectWeightPtTF1,1);

 private:
  std::vector<TString> m_productnames;
  TF1* m_function;

};

#endif
