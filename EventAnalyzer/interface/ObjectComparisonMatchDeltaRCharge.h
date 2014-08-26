#ifndef ObjectComparisonMatchDeltaRCharge_h
#define ObjectComparisonMatchDeltaRCharge_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonMatchDeltaRCharge : public ObjectComparison {
 public:
  ObjectComparisonMatchDeltaRCharge(double deltar,TString name="objectcomparisonmatchdeltarcharge"): ObjectComparison(name),m_deltar(deltar){}
  virtual ~ObjectComparisonMatchDeltaRCharge() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    double a_charge = 0;
    double b_charge = 0;
    bool a_isSet = a->getVariable("CHARGE",a_charge);
    bool b_isSet = a->getVariable("CHARGE",b_charge);
    if(!a_isSet || !b_isSet)return false;
    if(fabs(a_charge - b_charge) < 1e-3 && TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar)return true;
    return false;
  }
  virtual bool operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;

  ClassDef(ObjectComparisonMatchDeltaRCharge,1);
};

#endif
