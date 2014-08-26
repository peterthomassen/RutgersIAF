#ifndef ObjectCutElectronSuperClusterEta_h
#define ObjectCutElectronSuperClusterEta_h

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

class ObjectCutElectronSuperClusterEta : public ObjectCut {
 public:
  ObjectCutElectronSuperClusterEta(float nSuperClusterEtamin = 1.4442, float nSuperClusterEtamax = 1.566,const char* name="electronSuperClusterEtacut" ) : ObjectCut(name),m_nSuperClusterEtamin(nSuperClusterEtamin),m_nSuperClusterEtamax(nSuperClusterEtamax){ /*no-op*/}
    //ObjectCutElectronSuperClusterEta(int nSuperClusterEtamax = 1) : ObjectCutElectronSuperClusterEta("electronSuperClusterEtacut",nSuperClusterEtamax) { /* no-op */ }
    
  virtual ~ObjectCutElectronSuperClusterEta(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(m_nSuperClusterEtamin > 0 && fabs(sigObj->getFMVAVar_eta()) < m_nSuperClusterEtamin) return false;
    if(m_nSuperClusterEtamax > 0 && fabs(sigObj->getFMVAVar_eta()) > m_nSuperClusterEtamax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  float m_nSuperClusterEtamin;
  float m_nSuperClusterEtamax;

  ClassDef(ObjectCutElectronSuperClusterEta,1);

};

inline bool ObjectCutElectronSuperClusterEta::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
