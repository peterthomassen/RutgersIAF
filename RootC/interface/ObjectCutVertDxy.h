#ifndef ObjectCutVertDxy_h
#define ObjectCutVertDxy_h

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

class ObjectCutVertDxy : public ObjectCut {
 public:
  ObjectCutVertDxy(double dxymax=1.0, const char* name="dzcut") : ObjectCut(name),m_dxymax(dxymax){ /*no-op*/}
    //ObjectCutVertDxy(double dzmax = 1.0) : ObjectCutVertDxy("dzcut",dzmax) {/* no-op */ }
    
  virtual ~ObjectCutVertDxy(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_dxymax > 0 && fabs(sigObj->getVert_dxy()) > m_dxymax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_dxymax;

  ClassDef(ObjectCutVertDxy,1);

};

inline bool ObjectCutVertDxy::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
