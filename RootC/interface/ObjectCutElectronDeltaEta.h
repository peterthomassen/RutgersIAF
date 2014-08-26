#ifndef ObjectCutElectronDeltaEta_h
#define ObjectCutElectronDeltaEta_h

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

class ObjectCutElectronDeltaEta : public ObjectCut {
 public:
  ObjectCutElectronDeltaEta(double barrelDeltaEtamax = 0.007, double endcapDeltaEtamax=0.009, double etaseparator=1.5,const char* name="electronDeltaEtacut") : ObjectCut(name),m_barrelDeltaEtamax(barrelDeltaEtamax),m_endcapDeltaEtamax(endcapDeltaEtamax),m_etaseparator(etaseparator){ /*no-op*/}
    //ObjectCutElectronDeltaEta(double barrelDeltaEtamax = 0.007, double endcapDeltaEtamax=0.009, double etaseparator=1.5) : ObjectCutElectronDeltaEta("electronDeltaEtacut", barrelDeltaEtamax,endcapDeltaEtamax,etaseparator) { /* no-op */ }
    
  virtual ~ObjectCutElectronDeltaEta(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelDeltaEtamax > 0 && fabs(sigObj->getDeltaEta()) > m_barrelDeltaEtamax) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapDeltaEtamax > 0 && fabs(sigObj->getDeltaEta()) > m_endcapDeltaEtamax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_barrelDeltaEtamax;
  double m_endcapDeltaEtamax;
  double m_etaseparator;

  ClassDef(ObjectCutElectronDeltaEta,1);

};

inline bool ObjectCutElectronDeltaEta::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
