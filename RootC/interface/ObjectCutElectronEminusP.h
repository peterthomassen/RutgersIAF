#ifndef ObjectCutElectronEminusP_h
#define ObjectCutElectronEminusP_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"

class ObjectCutElectronEminusP : public ObjectCut {
 public:
  ObjectCutElectronEminusP(double barrelEmPmax = 0.05, double endcapEmPmax=0.05, double etaseparator=1.5,const char* name="electronEmPcut") : ObjectCut(name),m_barrelEmPmax(barrelEmPmax),m_endcapEmPmax(endcapEmPmax),m_etaseparator(etaseparator){ /*no-op*/}
    //ObjectCutElectronEminusP(double barrelEmPmax = 0.12, double endcapEmPmax=0.05, double etaseparator=1.5) : ObjectCutElectronEminusP("electronEmPcut",barrelEmPmax,endcapEmPmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutElectronEminusP(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    float EmP = fabs(sigObj->getFMVAVar_IoEmIoP());
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelEmPmax > 0 && EmP > m_barrelEmPmax) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapEmPmax > 0 && EmP > m_endcapEmPmax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_barrelEmPmax;
  double m_endcapEmPmax;
  double m_etaseparator;

  ClassDef(ObjectCutElectronEminusP,1);

};

inline bool ObjectCutElectronEminusP::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
