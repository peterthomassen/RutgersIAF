#ifndef EventVariableOS_h
#define EventVariableOS_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableOS : public EventVariable{
 public:
  EventVariableOS(TString name, TString productname, TString prefix="") : EventVariable(name),m_prefix(prefix) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableOS,1);

 private:
  TString m_prefix;
  std::vector<TString> m_productnames;


};

#endif
