#ifndef ObjectComparisonSkimRecoTracks_h
#define ObjectComparisonSkimRecoTracks_h

#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparison.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

class ObjectComparisonSkimRecoTracks : public ObjectComparison {
 public:
  ObjectComparisonSkimRecoTracks(double deltar,TString name="objectcomparisondeltar"): ObjectComparison(name),m_deltar(deltar){}
  virtual ~ObjectComparisonSkimRecoTracks() {}

  virtual bool passCut(SignatureObject* a,SignatureObject* b) const {
    int a_nvth=99,a_nvph=99;
    int b_nvth=100,b_nvph=100;
    bool isSeta_nvth = a->getVariable("NVALIDTRACKERHITS",a_nvth);
    bool isSeta_nvph = a->getVariable("NVALIDPIXELHITS",a_nvph);
    bool isSetb_nvth = b->getVariable("NVALIDTRACKERHITS",b_nvth);
    bool isSetb_nvph = b->getVariable("NVALIDPIXELHITS",b_nvph);
    if(!isSeta_nvth || !isSetb_nvth)return true;
    bool match_nvth = a_nvth == b_nvth;
    if(!isSeta_nvph || !isSetb_nvph)return true;
    bool match_nvph = a_nvph == b_nvph;
    if(match_nvth && match_nvph && TLorentzVector(*a).DeltaR(TLorentzVector(*b)) < m_deltar)return false;
    return true;
  }
  virtual bool operator()(SignatureObject* a,SignatureObject* b) const {
    return passCut(a,b);
  }

 private:
  double m_deltar;

  ClassDef(ObjectComparisonSkimRecoTracks,1);
};

#endif
