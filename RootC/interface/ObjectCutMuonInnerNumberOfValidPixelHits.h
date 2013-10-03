#ifndef ObjectCutMuonInnerNumberOfValidPixelHits_h
#define ObjectCutMuonInnerNumberOfValidPixelHits_h

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

class ObjectCutMuonInnerNumberOfValidPixelHits : public ObjectCut {
 public:
  ObjectCutMuonInnerNumberOfValidPixelHits(int minmatches=1,int maxmatches=-1,const char* name="muoninnervertdzcut") : ObjectCut(name),m_minMuonInnerNumberOfValidPixelHits(minmatches),m_maxMuonInnerNumberOfValidPixelHits(maxmatches){ /*no-op*/}
    //ObjectCutMuonInnerNumberOfValidPixelHits(bool isPromptTight=true) : ObjectCutMuonInnerNumberOfValidPixelHits("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutMuonInnerNumberOfValidPixelHits(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(m_minMuonInnerNumberOfValidPixelHits >= 0 && sigObj->getInnerNumberOfValidPixelHits() < m_minMuonInnerNumberOfValidPixelHits)return false;
    if(m_maxMuonInnerNumberOfValidPixelHits > 0 && sigObj->getInnerNumberOfValidPixelHits() > m_maxMuonInnerNumberOfValidPixelHits)return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  int m_minMuonInnerNumberOfValidPixelHits;
  int m_maxMuonInnerNumberOfValidPixelHits;

  ClassDef(ObjectCutMuonInnerNumberOfValidPixelHits,1);

};

inline bool ObjectCutMuonInnerNumberOfValidPixelHits::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
