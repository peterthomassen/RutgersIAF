#ifndef ObjectCutElectronHadOverEm_h
#define ObjectCutElectronHadOverEm_h

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
#include "RutgersIAF/RootC/interface/SignatureObjectPhoton.h"

class ObjectCutElectronHadOverEm : public ObjectCut {
 public:
  ObjectCutElectronHadOverEm(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5,const char* name="electronHoEcut") : ObjectCut(name),m_barrelHoEmax(barrelHoEmax),m_endcapHoEmax(endcapHoEmax),m_etaseparator(etaseparator){ /*no-op*/}
    //ObjectCutElectronHadOverEm(double barrelHoEmax = 0.12, double endcapHoEmax=0.05, double etaseparator=1.5) : ObjectCutElectronHadOverEm("electronHoEcut",barrelHoEmax,endcapHoEmax,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutElectronHadOverEm(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelHoEmax > 0 && sigObj->getHadOverEm() > m_barrelHoEmax) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapHoEmax > 0 && sigObj->getHadOverEm() > m_endcapHoEmax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;
  bool passCut(SignatureObjectPhoton* sigObj) const
  {
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelHoEmax > 0 && sigObj->getHadOverEm() > m_barrelHoEmax) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapHoEmax > 0 && sigObj->getHadOverEm() > m_endcapHoEmax) return false;
    return true;
  }
  bool operator()(SignatureObjectPhoton*) const;

 private:
  double m_barrelHoEmax;
  double m_endcapHoEmax;
  double m_etaseparator;

  ClassDef(ObjectCutElectronHadOverEm,1);

};

inline bool ObjectCutElectronHadOverEm::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
inline bool ObjectCutElectronHadOverEm::operator()(SignatureObjectPhoton* sigobj) const
{
  return passCut(sigobj);
}
#endif
