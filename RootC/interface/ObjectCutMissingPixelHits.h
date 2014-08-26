#ifndef ObjectCutMissingPixelHits_h
#define ObjectCutMissingPixelHits_h

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

class ObjectCutMissingPixelHits : public ObjectCut {
 public:
  ObjectCutMissingPixelHits(int missingpixelhitsmin=0,int missingpixelhitsmax=1,const char* name="missingpixelcut") : ObjectCut(name),m_missingpixelhitsmin(missingpixelhitsmin),m_missingpixelhitsmax(missingpixelhitsmax){ /*no-op*/}
    //ObjectCutMissingPixelHits(int missingpixelhitsmin=10,int missingpixelhitsmax=-1) : ObjectMissingPixelHits("missingpixelcut",missingpixelhitsmin,missingpixelhitsmax){ /* no-op */ }
    
  virtual ~ObjectCutMissingPixelHits(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_missingpixelhitsmin >= 0 && sigObj->getNLostPixelHits() < m_missingpixelhitsmin) return false;
    if(m_missingpixelhitsmax >= 0 && sigObj->getNLostPixelHits() > m_missingpixelhitsmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  int m_missingpixelhitsmin;
  int m_missingpixelhitsmax;


  ClassDef(ObjectCutMissingPixelHits,1);

};

inline bool ObjectCutMissingPixelHits::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
