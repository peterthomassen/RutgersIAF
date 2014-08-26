#ifndef ObjectCutBeamDz_h
#define ObjectCutBeamDz_h

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

class ObjectCutBeamDz : public ObjectCut {
 public:
  ObjectCutBeamDz(double dzmax=1.0, const char* name="dzcut") : ObjectCut(name),m_dzmax(dzmax){ /*no-op*/}
    //ObjectCutBeamDz(double dzmax = 1.0) : ObjectCutBeamDz("dzcut",dzmax) {/* no-op */ }
    
  virtual ~ObjectCutBeamDz(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_dzmax > 0 && fabs(sigObj->getBeam_dz()) > m_dzmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_dzmax;

  ClassDef(ObjectCutBeamDz,1);

};

inline bool ObjectCutBeamDz::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
