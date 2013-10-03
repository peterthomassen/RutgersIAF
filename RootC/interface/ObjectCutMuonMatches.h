#ifndef ObjectCutMuonMatches_h
#define ObjectCutMuonMatches_h

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

class ObjectCutMuonMatches : public ObjectCut {
 public:
  ObjectCutMuonMatches(int minmatches=2,int maxmatches=-1,const char* name="trackermuoncut") : ObjectCut(name),m_minMuonMatches(minmatches),m_maxMuonMatches(maxmatches){ /*no-op*/}
    //ObjectCutMuonMatches(bool isPromptTight=true) : ObjectCutMuonMatches("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutMuonMatches(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(m_minMuonMatches > 0 && sigObj->getNumberOfMatches() < m_minMuonMatches)return false;
    if(m_maxMuonMatches > 0 && sigObj->getNumberOfMatches() > m_maxMuonMatches)return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  int m_minMuonMatches;
  int m_maxMuonMatches;

  ClassDef(ObjectCutMuonMatches,1);

};

inline bool ObjectCutMuonMatches::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
