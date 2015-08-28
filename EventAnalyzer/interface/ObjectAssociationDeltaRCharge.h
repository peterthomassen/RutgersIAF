#ifndef ObjectAssociationDeltaRCharge_h
#define ObjectAssociationDeltaRCharge_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociation.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectAssociationDeltaRCharge : public ObjectAssociation {
 public:
 ObjectAssociationDeltaRCharge(double deltar,TString name="objectcomparisonmatchdeltarcharge"): ObjectAssociation(name),m_deltar(deltar){}
  virtual ~ObjectAssociationDeltaRCharge() {}

  virtual std::pair<bool,double> passCut(SignatureObject* a,SignatureObject* b) const {
    int a_charge = 0;
    int b_charge = 0;
    bool a_isSet = a->getVariable("charge",a_charge);
    bool b_isSet = a->getVariable("charge",b_charge);
    if(!a_isSet) a_isSet = a->getVariable("CHARGE",a_charge);
    if(!b_isSet) b_isSet = b->getVariable("CHARGE",b_charge);
    if(!a_isSet || !b_isSet)return std::make_pair(false,1e6);
    if(a_charge == b_charge && TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar){
      return std::make_pair(true, TLorentzVector(*a).DeltaR(TLorentzVector(*b)));
    }
    return std::make_pair(false,1e6);
  }
  virtual std::pair<bool,double> operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;

  ClassDef(ObjectAssociationDeltaRCharge,1);
};

#endif
