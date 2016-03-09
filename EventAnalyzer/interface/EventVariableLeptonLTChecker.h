#ifndef EventVariableLeptonLTChecker_h
#define EventVariableLeptonLTChecker_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableLeptonLTChecker : public EventVariable{
 public:
 EventVariableLeptonLTChecker(TString name,  TString productname,  TString prefix,  TString loosename,  TString tightname) :  EventVariable(name),  m_prefix(prefix),  m_loosename(loosename), m_tightname(tightname) {m_productnames.push_back(productname);}
			     
  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableLeptonLTChecker,1);

 private:
  TString m_prefix;
  TString m_loosename;
  TString m_tightname;
  std::vector<TString> m_productnames;


};

#endif
