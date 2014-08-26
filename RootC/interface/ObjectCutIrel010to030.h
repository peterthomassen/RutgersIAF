#ifndef ObjectCutIrel010to030_h
#define ObjectCutIrel010to030_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCutIrel.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutIrel010to030 : public ObjectCutIrel {
 public:
  ObjectCutIrel010to030(double irelmin=0.0,double irelmax=0.15, const char* name="irel010to030cut") : ObjectCutIrel(irelmin,irelmax,name){ /*no-op*/}
    //ObjectCutIrel010to030(double irelmax=0.15) : ObjectCutIrel010to030("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrel010to030(){}
  double calcIrel(SignatureObjectWithIso* sigObj) const { return calcIrel((SignatureObjectRecoTrack*)sigObj); }
  double calcIrel(SignatureObjectRecoTrack* sigObj) const{
    return (sigObj->getCaloIso() + sigObj->getTrackIso() - sigObj->getTrackIso1() - sigObj->getCaloIso1())/sigObj->Pt();
  }


  bool passCut(SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    double irel = calcIrel(sigObj);
    if(m_irelmin > 0 && irel < m_irelmin) return false;
    if(m_irelmax > 0 && irel > m_irelmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:

  ClassDef(ObjectCutIrel010to030,1);

};


inline bool ObjectCutIrel010to030::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
