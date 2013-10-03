#ifndef ObjectCutPhotonIsTight_h
#define ObjectCutPhotonIsTight_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectPhoton.h"

class ObjectCutPhotonIsTight : public ObjectCut {
 public:
  ObjectCutPhotonIsTight(bool isTight=true,const char* name="photonIsTightcut") : ObjectCut(name),m_isTight(isTight){ /*no-op*/}
    //ObjectCutPhotonIsTight(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5) : ObjectCutPhotonIsTight("photonHoEcut",barrelHoEmax,endcapHoEmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutPhotonIsTight(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectPhoton*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectPhoton*) sigObj); }
  bool passCut(SignatureObjectPhoton* sigObj) const
  {
    if(m_isTight != (bool)sigObj->getIsTight())return false;
    return true;
  }
  bool operator()(SignatureObjectPhoton*) const;

 private:
  bool m_isTight;

  ClassDef(ObjectCutPhotonIsTight,1);

};

inline bool ObjectCutPhotonIsTight::operator()(SignatureObjectPhoton* sigobj) const
{
  return passCut(sigobj);
}
#endif
