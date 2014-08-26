#ifndef ObjectCutValidPixelHits_h
#define ObjectCutValidPixelHits_h

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

class ObjectCutValidPixelHits : public ObjectCut {
 public:
  ObjectCutValidPixelHits(int validpixelhitsmin=1,int validpixelhitsmax=-1,const char* name="validpixelcut") : ObjectCut(name),m_validpixelhitsmin(validpixelhitsmin),m_validpixelhitsmax(validpixelhitsmax){ /*no-op*/}
    //ObjectCutValidPixelHits(int validpixelhitsmin=10,int validpixelhitsmax=-1) : ObjectValidPixelHits("validpixelcut",validpixelhitsmin,validpixelhitsmax){ /* no-op */ }
    
  virtual ~ObjectCutValidPixelHits(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_validpixelhitsmin > 0 && sigObj->getNValidPixelHits() < m_validpixelhitsmin) return false;
    if(m_validpixelhitsmax > 0 && sigObj->getNValidPixelHits() > m_validpixelhitsmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  int m_validpixelhitsmin;
  int m_validpixelhitsmax;


  ClassDef(ObjectCutValidPixelHits,1);

};

inline bool ObjectCutValidPixelHits::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
