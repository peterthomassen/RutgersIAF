#ifndef EventVariableMassDisplaced_h
#define EventVariableMassDisplaced_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableMassDisplaced : public EventVariable{
 public:
 EventVariableMassDisplaced(TString productname,TString px,TString py, TString pz, TString en, TString name="massdisplaced") : EventVariable(name),m_pxName(px),m_pyName(py),m_pzName(pz),m_eName(en) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableMassDisplaced,1);

 private:
  std::vector<TString> m_productnames;
  TString m_pxName;
  TString m_pyName;
  TString m_pzName;
  TString m_eName;

};

#endif
