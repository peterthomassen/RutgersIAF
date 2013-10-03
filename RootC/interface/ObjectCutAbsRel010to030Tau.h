#ifndef ObjectCutAbsRel010to030Tau_h
#define ObjectCutAbsRel010to030Tau_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRel010to030.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"

class ObjectCutAbsRel010to030Tau : public ObjectCutAbsRel010to030 {
 public:
  ObjectCutAbsRel010to030Tau(double irelmin=-1.0,double irelmax=10.0, const char* name="absrel010to030Taucut") : ObjectCutAbsRel010to030(irelmin,irelmax,name){ /*no-op*/}
    //ObjectCutAbsRel010to030Tau(double irelmax=0.15) : ObjectCutAbsRel010to030Tau("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutAbsRel010to030Tau(){}

  bool passCut(SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    double irel = calcAbsRel((SignatureObjectRecoTrack*)sigObj->getLeadingTrack());
    if(m_relmin > 0 && irel < m_relmin) return false;
    if(m_relmax > 0 && irel > m_relmax) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:

  ClassDef(ObjectCutAbsRel010to030Tau,1);

};


inline bool ObjectCutAbsRel010to030Tau::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
