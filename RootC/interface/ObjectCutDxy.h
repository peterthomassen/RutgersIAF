#ifndef ObjectCutDxy_h
#define ObjectCutDxy_h

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

class ObjectCutDxy : public ObjectCut {
 public:
  ObjectCutDxy(double dxymax=0.02, const char* name="dxycut") : ObjectCut(name),m_dxymax(dxymax){ /*no-op*/}
    //ObjectCutDxy(double dxymax=0.02) : ObjectCutDxy("dxycut",dxymax) { /* no-op */ }
    
  virtual ~ObjectCutDxy(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_dxymax > 0 && fabs(sigObj->getDxy()) > m_dxymax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_dxymax;

  ClassDef(ObjectCutDxy,1);

};

inline bool ObjectCutDxy::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
