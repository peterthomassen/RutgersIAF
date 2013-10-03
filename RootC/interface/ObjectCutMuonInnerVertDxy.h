#ifndef ObjectCutMuonInnerVertDxy_h
#define ObjectCutMuonInnerVertDxy_h

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

class ObjectCutMuonInnerVertDxy : public ObjectCut {
 public:
  ObjectCutMuonInnerVertDxy(float minmatches=0,float maxmatches=0.02,const char* name="muoninnervertdzcut") : ObjectCut(name),m_minMuonInnerVertDxy(minmatches),m_maxMuonInnerVertDxy(maxmatches){ /*no-op*/}
    //ObjectCutMuonInnerVertDxy(bool isPromptTight=true) : ObjectCutMuonInnerVertDxy("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutMuonInnerVertDxy(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(m_minMuonInnerVertDxy > 0 && fabs(sigObj->getInnerVertDxy()) < m_minMuonInnerVertDxy)return false;
    if(m_maxMuonInnerVertDxy > 0 && fabs(sigObj->getInnerVertDxy()) > m_maxMuonInnerVertDxy)return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  float m_minMuonInnerVertDxy;
  float m_maxMuonInnerVertDxy;

  ClassDef(ObjectCutMuonInnerVertDxy,1);

};

inline bool ObjectCutMuonInnerVertDxy::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
