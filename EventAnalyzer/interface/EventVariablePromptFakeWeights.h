#ifndef EventVariablePromptFakeWeights_h
#define EventVariablePromptFakeWeights_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariablePromptFakeWeights : public EventVariable{
 public:
 EventVariablePromptFakeWeights(TString productname, TString promptname="promptrate", TString fakename="fakerate", TString tightname="isTight",  TString prefix="",TString name="promptFakeWeights") : EventVariable(name),m_productname(productname),m_prefix(prefix),m_promptname(promptname),m_fakename(fakename),m_tightname(tightname) {m_n = 3;}

  bool calculate(BaseHandler*);

  ClassDef(EventVariablePromptFakeWeights,1);

 private:
  TString m_productname;
  TString m_prefix;
  TString m_promptname;
  TString m_fakename;
  TString m_tightname;
  int m_n;
};

#endif
