#ifndef ObjectCutCharge_h
#define ObjectCutCharge_h

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

class ObjectCutCharge : public ObjectCut {
 public:
  ObjectCutCharge(double dymin=-1.0,double dxymax=1.0, const char* name="chargecut") : ObjectCut(name),m_chargeMin(dymin),m_chargeMax(dxymax){ /*no-op*/}
    //ObjectCutCharge(double dzmax = 1.0) : ObjectCutCharge("dzcut",dzmax) {/* no-op */ }
    
  virtual ~ObjectCutCharge(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(sigObj->getCharge() < m_chargeMin) return false;
    if(sigObj->getCharge() > m_chargeMax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_chargeMin,m_chargeMax;

  ClassDef(ObjectCutCharge,1);

};

inline bool ObjectCutCharge::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
