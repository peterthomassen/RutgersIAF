#ifndef ObjectCutMuonInnerVertDz_h
#define ObjectCutMuonInnerVertDz_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMuon.h"

class ObjectCutMuonInnerVertDz : public ObjectCut {
 public:
  ObjectCutMuonInnerVertDz(float minmatches=0,float maxmatches=0.02,const char* name="muoninnervertdzcut") : ObjectCut(name),m_minMuonInnerVertDz(minmatches),m_maxMuonInnerVertDz(maxmatches){ /*no-op*/}
    //ObjectCutMuonInnerVertDz(bool isPromptTight=true) : ObjectCutMuonInnerVertDz("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutMuonInnerVertDz(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(sigObj->getInnerVertDz() < -900)return false;
    if(m_minMuonInnerVertDz >= 0 && fabs(sigObj->getInnerVertDz()) < m_minMuonInnerVertDz)return false;
    if(m_maxMuonInnerVertDz > 0 && fabs(sigObj->getInnerVertDz()) > m_maxMuonInnerVertDz)return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  float m_minMuonInnerVertDz;
  float m_maxMuonInnerVertDz;

  ClassDef(ObjectCutMuonInnerVertDz,1);

};

inline bool ObjectCutMuonInnerVertDz::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
