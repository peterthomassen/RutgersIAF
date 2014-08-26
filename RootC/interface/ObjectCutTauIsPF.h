#ifndef ObjectCutTauIsPF_h
#define ObjectCutTauIsPF_h

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

class ObjectCutTauIsPF : public ObjectCut {
 public:
  ObjectCutTauIsPF(bool isPF=true,const char* name="tauIsPFcut") : ObjectCut(name),m_isPF(isPF){ /*no-op*/}
    //ObjectCutTauIsPF(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5) : ObjectCutTauIsPF("tauHoEcut",barrelHoEmax,endcapHoEmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutTauIsPF(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(m_isPF != (bool)sigObj->getIsPF())return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  bool m_isPF;

  ClassDef(ObjectCutTauIsPF,1);

};

inline bool ObjectCutTauIsPF::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
