#ifndef EventVariableMT_h
#define EventVariableMT_h

#include <vector>
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"

class EventVariableMT : public EventVariable{
 public:
  EventVariableMT(TString name, double mZ, TString prefix="", TString productEl = "goodElectrons", TString productMu = "goodMuons", TString productTau = "goodTaus", TString productMET = "MET") : EventVariable(name),m_mZ(mZ),m_prefix(prefix),m_productEl(productEl),m_productMu(productMu),m_productTau(productTau),m_productMET(productMET) {}

  bool calculate(BaseHandler*);

  ClassDef(EventVariableMT,1);

 private:
  double m_mZ;
  TString m_prefix;
  TString m_productEl;
  TString m_productMu;
  TString m_productTau;
  TString m_productMET;


};

#endif
