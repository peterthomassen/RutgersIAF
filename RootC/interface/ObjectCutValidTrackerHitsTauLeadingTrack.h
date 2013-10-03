#ifndef ObjectCutValidTrackerHitsTauLeadingTrack_h
#define ObjectCutValidTrackerHitsTauLeadingTrack_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"

class ObjectCutValidTrackerHitsTauLeadingTrack : public ObjectCut {
 public:
  ObjectCutValidTrackerHitsTauLeadingTrack(int validtrackerhitsmin=11,int validtrackerhitsmax=-1,const char* name="validtrackercut") : ObjectCut(name),m_validtrackerhitsmin(validtrackerhitsmin),m_validtrackerhitsmax(validtrackerhitsmax){ /*no-op*/}
    //ObjectCutValidTrackerHitsTauLeadingTrack(int validtrackerhitsmin=10,int validtrackerhitsmax=-1) : ObjectValidTrackerHitsTauLeadingTrack("validtrackercut",validtrackerhitsmin,validtrackerhitsmax){ /* no-op */ }
    
  virtual ~ObjectCutValidTrackerHitsTauLeadingTrack(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(!sigObj->getLeadingTrack())return false;
    if(m_validtrackerhitsmin > 0 && sigObj->getLeadingTrack()->getNValidTrackerHits() < m_validtrackerhitsmin) return false;
    if(m_validtrackerhitsmax > 0 && sigObj->getLeadingTrack()->getNValidTrackerHits() > m_validtrackerhitsmax) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  int m_validtrackerhitsmin;
  int m_validtrackerhitsmax;


  ClassDef(ObjectCutValidTrackerHitsTauLeadingTrack,1);

};

inline bool ObjectCutValidTrackerHitsTauLeadingTrack::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
