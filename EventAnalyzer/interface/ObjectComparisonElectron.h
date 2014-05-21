#ifndef ObjectComparisonElectron_h
#define ObjectComparisonElectron_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonElectron : public ObjectComparison {
 public:
  ObjectComparisonElectron(double deltar,TString name="objectcomparisonelectron"): ObjectComparison(name),m_deltar(deltar){}
  virtual ~ObjectComparisonElectron() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    double a_sceta=99,a_deta=99,a_dz=99,a_sieta=99;
    double b_sceta=96,b_deta=96,b_dz=96,b_sieta=96;
    bool isSeta_sceta = a->getVariable("FMVAVAR_ETA",a_sceta);
    bool isSeta_deta = a->getVariable("FMVAVAR_DETA",a_deta);
    bool isSeta_dz = a->getVariable("FMVAVAR_DZ",a_dz);
    bool isSeta_sieta = a->getVariable("SIGMAIETAIETA",a_sieta);
    bool isSetb_sceta = b->getVariable("FMVAVAR_ETA",b_sceta);
    bool isSetb_deta = b->getVariable("FMVAVAR_DETA",b_deta);
    bool isSetb_dz = a->getVariable("FMVAVAR_DZ",b_dz);
    bool isSetb_sieta = a->getVariable("SIGMAIETAIETA",b_sieta);
    if(!isSeta_sceta || !isSetb_sceta)return true;
    bool match_sceta = fabs(a_sceta - b_sceta) < 1e-3;
    if(!isSeta_deta || !isSetb_deta)return true;
    bool match_deta = fabs(a_deta - b_deta) < 1e-3;
    if(!isSeta_dz || !isSetb_dz)return true;
    bool match_dz = fabs(a_dz - b_dz) < 1e-3;
    if(!isSeta_sieta || !isSetb_sieta)return true;
    bool match_sieta = fabs(a_sieta - b_sieta) < 1e-3;
    if(match_sceta && match_deta && match_dz && match_sieta)return false;
    if(TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar)return false;
    return true;
  }
  virtual bool operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;

  ClassDef(ObjectComparisonElectron,1);
};

#endif
