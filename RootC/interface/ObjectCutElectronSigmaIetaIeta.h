#ifndef ObjectCutElectronSigmaIetaIeta_h
#define ObjectCutElectronSigmaIetaIeta_h

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
#include "RutgersIAF2012/RootC/interface/SignatureObjectPhoton.h"

class ObjectCutElectronSigmaIetaIeta : public ObjectCut {
 public:
  ObjectCutElectronSigmaIetaIeta(double barrelsigmaIetaIetamax = 0.01, double endcapsigmaIetaIetamax=0.03, double etaseparator=1.5, const char* name="electronsigmaIetaIetacut") : ObjectCut(name),m_barrelsigmaIetaIetamax(barrelsigmaIetaIetamax),m_endcapsigmaIetaIetamax(endcapsigmaIetaIetamax),m_etaseparator(etaseparator){ /*no-op*/}
    //ObjectCutElectronSigmaIetaIeta(double barrelsigmaIetaIetamax = 0.01, double endcapsigmaIetaIetamax = 0.03, double etaseparator=1.5) : ObjectCutElectronSigmaIetaIeta(barrelsigmaIetaIetamax,endcapsigmaIetaIetamax,etaseparator) { /* no-op */ }
    
  virtual ~ObjectCutElectronSigmaIetaIeta(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelsigmaIetaIetamax > 0 && fabs(sigObj->getSigmaIetaIeta()) > m_barrelsigmaIetaIetamax) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapsigmaIetaIetamax > 0 && fabs(sigObj->getSigmaIetaIeta()) > m_endcapsigmaIetaIetamax) return false;
    return true;
  }
  bool passCut(SignatureObjectPhoton* sigObj) const
  {
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelsigmaIetaIetamax > 0 && fabs(sigObj->getSigmaIetaIeta()) > m_barrelsigmaIetaIetamax) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapsigmaIetaIetamax > 0 && fabs(sigObj->getSigmaIetaIeta()) > m_endcapsigmaIetaIetamax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;
  bool operator()(SignatureObjectPhoton*) const;

 private:
  double m_barrelsigmaIetaIetamax;
  double m_endcapsigmaIetaIetamax;
  double m_etaseparator;

  ClassDef(ObjectCutElectronSigmaIetaIeta,1);

};

inline bool ObjectCutElectronSigmaIetaIeta::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
inline bool ObjectCutElectronSigmaIetaIeta::operator()(SignatureObjectPhoton* sigobj) const
{
  return passCut(sigobj);
}
#endif
