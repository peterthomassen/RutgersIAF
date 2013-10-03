#ifndef ObjectCutDz_h
#define ObjectCutDz_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutDz : public ObjectCut {
 public:
  ObjectCutDz(double dzmax=1.0, const char* name="dzcut") : ObjectCut(name),m_dzmax(dzmax){ /*no-op*/}
    //ObjectCutDz(double dzmax = 1.0) : ObjectCutDz("dzcut",dzmax) {/* no-op */ }
    
  virtual ~ObjectCutDz(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_dzmax > 0 && fabs(sigObj->getDz()) > m_dzmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_dzmax;

  ClassDef(ObjectCutDz,1);

};

inline bool ObjectCutDz::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
