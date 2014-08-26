#ifndef EventVariableOSSF_h
#define EventVariableOSSF_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableOSSF : public EventVariable{
 public:
  EventVariableOSSF(TString name, TString productname, TString prefix="", double zmass = 91, double width = 15) : EventVariable(name),m_prefix(prefix),m_zmass(zmass),m_zwidth(width) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableOSSF,1);

 private:
  TString m_prefix;
  double m_zmass;
  double m_zwidth;
  std::vector<TString> m_productnames;


};

#endif
