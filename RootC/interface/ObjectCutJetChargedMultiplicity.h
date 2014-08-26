#ifndef ObjectCutJetChargedMultiplicity_h
#define ObjectCutJetChargedMultiplicity_h

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

class ObjectCutJetChargedMultiplicity : public ObjectCut {
 public:
  ObjectCutJetChargedMultiplicity(int mincut=1, float maxcut=-1,const char* name="nConstituentscut") : ObjectCut(name),m_minCut(mincut),m_maxCut(maxcut){ /*no-op*/}
    //ObjectCutJetChargedMultiplicity(bool isPromptTight=true) : ObjectCutJetChargedMultiplicity("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutJetChargedMultiplicity(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectJet*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectJet*) sigObj); }
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_minCut > 0 && sigObj->getChargedHadronMultiplicity() < m_minCut)return false;
    if(m_maxCut > 0 && sigObj->getChargedHadronMultiplicity() > m_maxCut)return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;

 private:
  int m_minCut;
  int m_maxCut;

  ClassDef(ObjectCutJetChargedMultiplicity,1);

};

inline bool ObjectCutJetChargedMultiplicity::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
#endif
