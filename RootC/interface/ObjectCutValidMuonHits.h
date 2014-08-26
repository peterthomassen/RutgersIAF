#ifndef ObjectCutValidMuonHits_h
#define ObjectCutValidMuonHits_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutValidMuonHits : public ObjectCut {
 public:
  ObjectCutValidMuonHits(int validmuonhitsmin=1,int validmuonhitsmax=-1,const char* name="validmuoncut") : ObjectCut(name),m_validmuonhitsmin(validmuonhitsmin),m_validmuonhitsmax(validmuonhitsmax){ /*no-op*/}
    //ObjectCutValidMuonHits(int validmuonhitsmin=10,int validmuonhitsmax=-1) : ObjectValidMuonHits("validmuoncut",validmuonhitsmin,validmuonhitsmax){ /* no-op */ }
    
  virtual ~ObjectCutValidMuonHits(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_validmuonhitsmin > 0 && sigObj->getNValidMuonHits() < m_validmuonhitsmin) return false;
    if(m_validmuonhitsmax > 0 && sigObj->getNValidMuonHits() > m_validmuonhitsmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  int m_validmuonhitsmin;
  int m_validmuonhitsmax;


  ClassDef(ObjectCutValidMuonHits,1);

};

inline bool ObjectCutValidMuonHits::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
