#ifndef ObjectComparisonDeltaR_h
#define ObjectComparisonDeltaR_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonDeltaR : public ObjectComparison {
 public:
  ObjectComparisonDeltaR(double deltar,TString name="objectcomparisondeltar"): ObjectComparison(name),m_deltar(deltar){}
  virtual ~ObjectComparisonDeltaR() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    if(TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar)return false;
    return true;
  }
  virtual bool operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;

  ClassDef(ObjectComparisonDeltaR,1);
};

#endif
