#ifndef ObjectCutTauChargeMatch_h
#define ObjectCutTauChargeMatch_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutTauChargeMatch : public ObjectCut {
 public:
  ObjectCutTauChargeMatch(bool isPF=true,const char* name="tauChargeMatchcut") : ObjectCut(name),m_chargeMatch(isPF){ /*no-op*/}
    //ObjectCutTauChargeMatch(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5) : ObjectCutTauChargeMatch("tauHoEcut",barrelHoEmax,endcapHoEmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutTauChargeMatch(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(!sigObj->getLeadingTrack())return false;
    if(m_chargeMatch && fabs(sigObj->getPF_signalCharge() - sigObj->getLeadingTrack()->getCharge())> 0.5)return false;
    if(!m_chargeMatch && fabs(sigObj->getPF_signalCharge() - sigObj->getLeadingTrack()->getCharge()) < 0.5)return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  bool m_chargeMatch;

  ClassDef(ObjectCutTauChargeMatch,1);

};

inline bool ObjectCutTauChargeMatch::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
