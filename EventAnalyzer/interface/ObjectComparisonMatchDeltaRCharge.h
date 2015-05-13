#ifndef ObjectComparisonMatchDeltaRCharge_h
#define ObjectComparisonMatchDeltaRCharge_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonMatchDeltaRCharge : public ObjectComparison {
 public:
 ObjectComparisonMatchDeltaRCharge(double deltar,TString associateName="associate",TString name="objectcomparisonmatchdeltarcharge"): ObjectComparison(name),m_deltar(deltar),m_associateName(associateName){}
  virtual ~ObjectComparisonMatchDeltaRCharge() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    int a_charge = 0;
    int b_charge = 0;
    bool a_isSet = a->getVariable("charge",a_charge);
    bool b_isSet = a->getVariable("charge",b_charge);
    if(!a_isSet || !b_isSet)return false;
    if(a_charge == b_charge && TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar){
      a->setAssociate(m_associateName,b);
      a->setVariable(TString::Format("hasAssociate_%s",m_associateName.Data()),true);
      return true;
    }
    return false;
  }
  virtual bool operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;
  TString m_associateName;

  ClassDef(ObjectComparisonMatchDeltaRCharge,1);
};

#endif
