#ifndef ObjectAssociationDeltaR_h
#define ObjectAssociationDeltaR_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/ObjectAssociation.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectAssociationDeltaR : public ObjectAssociation {
 public:
 ObjectAssociationDeltaR(double deltar,TString name="objectcomparisonmatchdeltar"): ObjectAssociation(name),m_deltar(deltar){}
  virtual ~ObjectAssociationDeltaR() {}

  virtual std::pair<bool,double> passCut(SignatureObject* a,SignatureObject* b) const {
    if(TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar){
      return std::make_pair(true,TLorentzVector(*a).DeltaR(TLorentzVector(*b)));
    }
    return std::make_pair(false,1e6);
  }
  virtual std::pair<bool,double> operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;

  ClassDef(ObjectAssociationDeltaR,1);
};

#endif
