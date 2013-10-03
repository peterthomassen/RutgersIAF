#ifndef ObjectCutElectronDeltaPhi_h
#define ObjectCutElectronDeltaPhi_h

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

class ObjectCutElectronDeltaPhi : public ObjectCut {
 public:
  ObjectCutElectronDeltaPhi(double barrelDeltaPhimax = 0.007, double endcapDeltaPhimax=0.009, double etaseparator=1.5,const char* name="electronDeltaPhicut") : ObjectCut(name),m_barrelDeltaPhimax(barrelDeltaPhimax),m_endcapDeltaPhimax(endcapDeltaPhimax),m_etaseparator(etaseparator){ /*no-op*/}
    //ObjectCutElectronDeltaPhi(double barrelDeltaPhimax = 0.007, double endcapDeltaPhimax=0.009, double etaseparator=1.5) : ObjectCutElectronDeltaPhi("electronDeltaPhicut",barrelDeltaPhimax,endcapDeltaPhimax,etaseparator) { /* no-op */ }
    
  virtual ~ObjectCutElectronDeltaPhi(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelDeltaPhimax > 0 && fabs(sigObj->getDeltaPhi()) > m_barrelDeltaPhimax) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapDeltaPhimax > 0 && fabs(sigObj->getDeltaPhi()) > m_endcapDeltaPhimax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_barrelDeltaPhimax;
  double m_endcapDeltaPhimax;
  double m_etaseparator;

  ClassDef(ObjectCutElectronDeltaPhi,1);

};

inline bool ObjectCutElectronDeltaPhi::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
