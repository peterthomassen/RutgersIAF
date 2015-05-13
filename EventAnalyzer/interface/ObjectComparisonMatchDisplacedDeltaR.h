#ifndef ObjectComparisonMatchDisplacedDeltaR_h
#define ObjectComparisonMatchDisplacedDeltaR_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include <TVector3.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonMatchDisplacedDeltaR : public ObjectComparison {
 public:
 ObjectComparisonMatchDisplacedDeltaR(double deltar,TString associateName="associate",TString name="objectcomparisonmatchdisplacedr"): ObjectComparison(name),m_deltar(deltar),m_associateName(associateName){}
  virtual ~ObjectComparisonMatchDisplacedDeltaR() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    double a_etaOnECAL = 0;
    double a_phiOnECAL = 0;
    double b_etaOnECAL = 0;
    double b_phiOnECAL = 0;
    bool a_e_isSet = a->getVariable("etaOnECAL",a_etaOnECAL);
    bool a_p_isSet = a->getVariable("phiOnECAL",a_phiOnECAL);
    bool b_e_isSet = b->getVariable("etaOnECAL",b_etaOnECAL);
    bool b_p_isSet = b->getVariable("phiOnECAL",b_phiOnECAL);
    if(!((a_e_isSet && a_p_isSet) || (b_e_isSet && b_p_isSet)))return false;
    TVector3 a_vec,b_vec;
    if(a_e_isSet && a_p_isSet){
      a_vec.SetPtEtaPhi(10.0,a_etaOnECAL,a_phiOnECAL);
    }else{
      a_vec.SetPtEtaPhi(10.0,a->Eta(),a->Phi());
    }
    if(b_e_isSet && b_p_isSet){
      b_vec.SetPtEtaPhi(10.0,b_etaOnECAL,b_phiOnECAL);
    }else{
      b_vec.SetPtEtaPhi(10.0,b->Eta(),b->Phi());
    }
    if(a_vec.DeltaR(b_vec) < m_deltar){
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

  ClassDef(ObjectComparisonMatchDisplacedDeltaR,1);
};

#endif
