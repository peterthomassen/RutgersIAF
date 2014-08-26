#ifndef ObjectCutJetBeta_h
#define ObjectCutJetBeta_h

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

class ObjectCutJetBeta : public ObjectCut {
 public:
  ObjectCutJetBeta(float mincut=0.0, float maxcut=0.1,const char* name="neutralemfractioncut") : ObjectCut(name),m_minCut(mincut),m_maxCut(maxcut){ /*no-op*/}
    //ObjectCutJetBeta(bool isPromptTight=true) : ObjectCutJetBeta("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutJetBeta(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectJet*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectJet*) sigObj); }
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_minCut > 0 && sigObj->getBeta() < m_minCut)return false;
    if(m_maxCut > 0 && sigObj->getBeta() > m_maxCut)return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;

 private:
  float m_minCut;
  float m_maxCut;

  ClassDef(ObjectCutJetBeta,1);

};

inline bool ObjectCutJetBeta::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
#endif
