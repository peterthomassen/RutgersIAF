#ifndef ObjectCutTauCharge_h
#define ObjectCutTauCharge_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutTauCharge : public ObjectCut {
 public:
  ObjectCutTauCharge(double minc = -99.0,double maxc=99.0,const char* name="tauChargecut") : ObjectCut(name),m_min(minc),m_max(maxc){ /*no-op*/}
    //ObjectCutTauCharge(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5) : ObjectCutTauCharge("tauHoEcut",barrelHoEmax,endcapHoEmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutTauCharge(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(sigObj->getPF_signalCharge() < m_min)return false;
    if(sigObj->getPF_signalCharge() > m_max)return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  double m_min;
  double m_max;

  ClassDef(ObjectCutTauCharge,1);

};

inline bool ObjectCutTauCharge::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
