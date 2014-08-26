#ifndef ObjectCutBeamDxy_h
#define ObjectCutBeamDxy_h

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

class ObjectCutBeamDxy : public ObjectCut {
 public:
  ObjectCutBeamDxy(double dxymax=0.02, const char* name="dxycut") : ObjectCut(name),m_dxymax(dxymax){ /*no-op*/}
    //ObjectCutBeamDxy(double dxymax=0.02) : ObjectCutBeamDxy("dxycut",dxymax) { /* no-op */ }
    
  virtual ~ObjectCutBeamDxy(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_dxymax > 0 && fabs(sigObj->getBeam_dxy()) > m_dxymax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_dxymax;

  ClassDef(ObjectCutBeamDxy,1);

};

inline bool ObjectCutBeamDxy::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
