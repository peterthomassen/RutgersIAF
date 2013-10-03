#ifndef ObjectCutIrel010to030Tau_h
#define ObjectCutIrel010to030Tau_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCutIrel010to030.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"

class ObjectCutIrel010to030Tau : public ObjectCutIrel010to030 {
 public:
  ObjectCutIrel010to030Tau(double irelmin=0.0,double irelmax=0.15, const char* name="irel010to030Taucut") : ObjectCutIrel010to030(irelmin,irelmax,name){ /*no-op*/}
    //ObjectCutIrel010to030Tau(double irelmax=0.15) : ObjectCutIrel010to030Tau("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrel010to030Tau(){}

  bool passCut(SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(sigObj->getLeadTrack_ntID() < 0)return false;
    double irel = calcIrel((SignatureObjectRecoTrack*)sigObj->getLeadingTrack());
    if(m_irelmin > 0 && irel < m_irelmin) return false;
    if(m_irelmax > 0 && irel > m_irelmax) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:

  ClassDef(ObjectCutIrel010to030Tau,1);

};


inline bool ObjectCutIrel010to030Tau::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
