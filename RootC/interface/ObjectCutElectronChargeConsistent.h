#ifndef ObjectCutElectronChargeConsistent_h
#define ObjectCutElectronChargeConsistent_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectElectron.h"

class ObjectCutElectronChargeConsistent : public ObjectCut {
 public:
  ObjectCutElectronChargeConsistent(bool isConsistent=true, const char* name="electronsigmaIetaIetacut") : ObjectCut(name),m_isConsistent(isConsistent){ /*no-op*/}
    //ObjectCutElectronChargeConsistent(double barrelsigmaIetaIetamax = 0.01, double endcapsigmaIetaIetamax = 0.03, double etaseparator=1.5) : ObjectCutElectronChargeConsistent(barrelsigmaIetaIetamax,endcapsigmaIetaIetamax,etaseparator) { /* no-op */ }
    
  virtual ~ObjectCutElectronChargeConsistent(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(m_isConsistent != (bool)sigObj->getGsfScPixChargeConsistent())return false;
    if(m_isConsistent != (bool)sigObj->getGsfCtfChargeConsistent())return false;
    if(m_isConsistent != (bool)sigObj->getGsfCtfScPixChargeConsistent())return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_isConsistent;

  ClassDef(ObjectCutElectronChargeConsistent,1);

};

inline bool ObjectCutElectronChargeConsistent::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
