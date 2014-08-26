#ifndef ObjectCutValidTrackerHits_h
#define ObjectCutValidTrackerHits_h

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

class ObjectCutValidTrackerHits : public ObjectCut {
 public:
  ObjectCutValidTrackerHits(int validtrackerhitsmin=10,int validtrackerhitsmax=-1,const char* name="validtrackercut") : ObjectCut(name),m_validtrackerhitsmin(validtrackerhitsmin),m_validtrackerhitsmax(validtrackerhitsmax){ /*no-op*/}
    //ObjectCutValidTrackerHits(int validtrackerhitsmin=10,int validtrackerhitsmax=-1) : ObjectValidTrackerHits("validtrackercut",validtrackerhitsmin,validtrackerhitsmax){ /* no-op */ }
    
  virtual ~ObjectCutValidTrackerHits(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_validtrackerhitsmin > 0 && sigObj->getNValidTrackerHits() < m_validtrackerhitsmin) return false;
    if(m_validtrackerhitsmax > 0 && sigObj->getNValidTrackerHits() > m_validtrackerhitsmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  int m_validtrackerhitsmin;
  int m_validtrackerhitsmax;


  ClassDef(ObjectCutValidTrackerHits,1);

};

inline bool ObjectCutValidTrackerHits::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
