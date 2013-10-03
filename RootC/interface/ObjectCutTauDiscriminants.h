#ifndef ObjectCutTauDiscriminants_h
#define ObjectCutTauDiscriminants_h

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

class ObjectCutTauDiscriminants : public ObjectCut {
 public:
  ObjectCutTauDiscriminants(int whichdisc, bool pass=true,const char* name="tauDiscriminantscut") : ObjectCut(name),m_whichDisc(whichdisc),m_pass(pass){ /*no-op*/}
    //ObjectCutTauDiscriminants(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5) : ObjectCutTauDiscriminants("tauHoEcut",barrelHoEmax,endcapHoEmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutTauDiscriminants(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(m_whichDisc > 49)return false;
    double discval = sigObj->getPF_DiscriminantsAt(m_whichDisc);
    if(discval < 0) return false;
    if(m_pass != (bool)discval)return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  int m_whichDisc;
  bool m_pass;

  ClassDef(ObjectCutTauDiscriminants,1);

};

inline bool ObjectCutTauDiscriminants::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
