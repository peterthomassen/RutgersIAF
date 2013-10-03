#ifndef ObjectCutJetChargedHadronFraction_h
#define ObjectCutJetChargedHadronFraction_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"

class ObjectCutJetChargedHadronFraction : public ObjectCut {
 public:
  ObjectCutJetChargedHadronFraction(float mincut=0.00001, float maxcut=1.0,const char* name="neutralhadronfractioncut") : ObjectCut(name),m_minCut(mincut),m_maxCut(maxcut){ /*no-op*/}
    //ObjectCutJetChargedHadronFraction(bool isPromptTight=true) : ObjectCutJetChargedHadronFraction("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutJetChargedHadronFraction(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectJet*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectJet*) sigObj); }
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_minCut > 0 && sigObj->getChargedHadronFraction() < m_minCut)return false;
    if(m_maxCut > 0 && sigObj->getChargedHadronFraction() > m_maxCut)return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;

 private:
  float m_minCut;
  float m_maxCut;

  ClassDef(ObjectCutJetChargedHadronFraction,1);

};

inline bool ObjectCutJetChargedHadronFraction::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
#endif
