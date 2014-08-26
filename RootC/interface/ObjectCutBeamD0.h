#ifndef ObjectCutBeamD0_h
#define ObjectCutBeamD0_h

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

class ObjectCutBeamD0 : public ObjectCut {
 public:
  ObjectCutBeamD0(double dxymax=0.02, const char* name="dxycut") : ObjectCut(name),m_dxymax(dxymax){ /*no-op*/}
    //ObjectCutBeamD0(double dxymax=0.02) : ObjectCutBeamD0("dxycut",dxymax) { /* no-op */ }
    
  virtual ~ObjectCutBeamD0(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_dxymax > 0 && fabs(sigObj->getBeam_d0()) > m_dxymax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_dxymax;

  ClassDef(ObjectCutBeamD0,1);

};

inline bool ObjectCutBeamD0::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
