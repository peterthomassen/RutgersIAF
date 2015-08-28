#ifndef ObjectAssociationDisplacedDeltaRPtFrac_h
#define ObjectAssociationDisplacedDeltaRPtFrac_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include <TVector3.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociation.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectAssociationDisplacedDeltaRPtFrac : public ObjectAssociation {
 public:
 ObjectAssociationDisplacedDeltaRPtFrac(double deltar, double ptfrac, TString name="objectcomparisonmatchdisplacedr",bool giveDeltaR=true): ObjectAssociation(name),m_deltar(deltar),m_ptfrac(ptfrac),m_giveDeltaR(giveDeltaR){}
  virtual ~ObjectAssociationDisplacedDeltaRPtFrac() {}

  virtual std::pair<bool,double> passCut(SignatureObject* a,SignatureObject* b) const {
    if(a->Pt() == 0)return std::make_pair(false,1e6);
    double a_etaOnECAL = 0;
    double a_phiOnECAL = 0;
    double b_etaOnECAL = 0;
    double b_phiOnECAL = 0;
    bool a_e_isSet = a->getVariable("etaOnECAL",a_etaOnECAL);
    bool a_p_isSet = a->getVariable("phiOnECAL",a_phiOnECAL);
    bool b_e_isSet = b->getVariable("etaOnECAL",b_etaOnECAL);
    bool b_p_isSet = b->getVariable("phiOnECAL",b_phiOnECAL);
    if(!((a_e_isSet && a_p_isSet) || (b_e_isSet && b_p_isSet)))return std::make_pair(false,1e6);
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
    if(a_vec.DeltaR(b_vec) < m_deltar && fabs((a->Pt()-b->Pt())/a->Pt()) < m_ptfrac){
      double retval = a_vec.DeltaR(b_vec);
      if(!m_giveDeltaR)retval = fabs((a->Pt()-b->Pt())/a->Pt());
      return std::make_pair(true,retval);
    }
    return std::make_pair(false,1e6);
  }
  virtual std::pair<bool,double> operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;
  double m_ptfrac;
  bool m_giveDeltaR;

  ClassDef(ObjectAssociationDisplacedDeltaRPtFrac,1);
};

#endif
