#ifndef ObjectCutIsPF_h
#define ObjectCutIsPF_h

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
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"

class ObjectCutIsPF : public ObjectCut {
 public:
  ObjectCutIsPF(bool isPF=true,const char* name="IsPFcut") : ObjectCut(name),m_isPF(isPF){ /*no-op*/}
    //ObjectCutIsPF(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5) : ObjectCutIsPF("tauHoEcut",barrelHoEmax,endcapHoEmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutIsPF(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(m_isPF != (bool)sigObj->getIsPF())return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_isPF != (bool)sigObj->getIsPF())return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(m_isPF != (bool)sigObj->getIsPF())return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(m_isPF != (bool)sigObj->getIsPF())return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  bool m_isPF;

  ClassDef(ObjectCutIsPF,1);

};

inline bool ObjectCutIsPF::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
inline bool ObjectCutIsPF::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
inline bool ObjectCutIsPF::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
inline bool ObjectCutIsPF::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
