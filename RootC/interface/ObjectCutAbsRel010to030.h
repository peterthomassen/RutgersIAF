#ifndef ObjectCutAbsRel010to030_h
#define ObjectCutAbsRel010to030_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCutAbsRel.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutAbsRel010to030 : public ObjectCutAbsRel {
 public:
  ObjectCutAbsRel010to030(double irelmin=-1.0,double irelmax=10.0, const char* name="absrel010to030cut") : ObjectCutAbsRel(irelmin,irelmax,name){ /*no-op*/}
    //ObjectCutAbsRel010to030(double irelmax=0.15) : ObjectCutAbsRel010to030("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutAbsRel010to030(){}
  double calcAbsRel(SignatureObjectWithIso* sigObj) const { return calcAbsRel((SignatureObjectRecoTrack*)sigObj); }
  double calcAbsRel(SignatureObjectRecoTrack* sigObj) const{
    return fabs(sigObj->getCaloIso() + sigObj->getTrackIso() - sigObj->getTrackIso1() - sigObj->getCaloIso1());
  }


  bool passCut(SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    double irel = calcAbsRel(sigObj);
    if(m_relmin > 0 && irel < m_relmin) return false;
    if(m_relmax > 0 && irel > m_relmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:

  ClassDef(ObjectCutAbsRel010to030,1);

};


inline bool ObjectCutAbsRel010to030::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
