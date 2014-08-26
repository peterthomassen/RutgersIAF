#ifndef ObjectCutJetChargedEMFraction_h
#define ObjectCutJetChargedEMFraction_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectJet.h"

class ObjectCutJetChargedEMFraction : public ObjectCut {
 public:
  ObjectCutJetChargedEMFraction(float mincut=0.0, float maxcut=0.99,const char* name="neutralemfractioncut") : ObjectCut(name),m_minCut(mincut),m_maxCut(maxcut){ /*no-op*/}
    //ObjectCutJetChargedEMFraction(bool isPromptTight=true) : ObjectCutJetChargedEMFraction("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutJetChargedEMFraction(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectJet*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectJet*) sigObj); }
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_minCut > 0 && sigObj->getChargedEMFraction() < m_minCut)return false;
    if(m_maxCut > 0 && sigObj->getChargedEMFraction() > m_maxCut)return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;

 private:
  float m_minCut;
  float m_maxCut;

  ClassDef(ObjectCutJetChargedEMFraction,1);

};

inline bool ObjectCutJetChargedEMFraction::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
#endif
