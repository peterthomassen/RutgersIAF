#ifndef ObjectComparisonMatchDeltaR_h
#define ObjectComparisonMatchDeltaR_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonMatchDeltaR : public ObjectComparison {
 public:
 ObjectComparisonMatchDeltaR(double deltar,TString associateName="associate",TString name="objectcomparisonmatchdeltar"): ObjectComparison(name),m_deltar(deltar),m_associateName(associateName){}
  virtual ~ObjectComparisonMatchDeltaR() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    if(TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar){
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

  ClassDef(ObjectComparisonMatchDeltaR,1);
};

#endif
