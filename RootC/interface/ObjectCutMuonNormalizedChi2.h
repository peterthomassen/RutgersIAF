#ifndef ObjectCutMuonNormalizedChi2_h
#define ObjectCutMuonNormalizedChi2_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"

class ObjectCutMuonNormalizedChi2 : public ObjectCut {
 public:
  ObjectCutMuonNormalizedChi2(float minmatches=0,float maxmatches=10,const char* name="muonnormalizedch2cut") : ObjectCut(name),m_minMuonNormalizedChi2(minmatches),m_maxMuonNormalizedChi2(maxmatches){ /*no-op*/}
    //ObjectCutMuonNormalizedChi2(bool isPromptTight=true) : ObjectCutMuonNormalizedChi2("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutMuonNormalizedChi2(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(sigObj->getNormalizedChi2() < 0) return false;
    if(m_minMuonNormalizedChi2 > 0 && sigObj->getNormalizedChi2() < m_minMuonNormalizedChi2)return false;
    if(m_maxMuonNormalizedChi2 > 0 && sigObj->getNormalizedChi2() > m_maxMuonNormalizedChi2)return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  float m_minMuonNormalizedChi2;
  int m_maxMuonNormalizedChi2;

  ClassDef(ObjectCutMuonNormalizedChi2,1);

};

inline bool ObjectCutMuonNormalizedChi2::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
