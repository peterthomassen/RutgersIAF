#ifndef ObjectCutElectronVertDxy_h
#define ObjectCutElectronVertDxy_h

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

class ObjectCutElectronVertDxy : public ObjectCut {
 public:
  ObjectCutElectronVertDxy(double dxymax=1.0, const char* name="dzcut") : ObjectCut(name),m_dxymax(dxymax){ /*no-op*/}
    //ObjectCutElectronVertDxy(double dzmax = 1.0) : ObjectCutElectronVertDxy("dzcut",dzmax) {/* no-op */ }
    
  virtual ~ObjectCutElectronVertDxy(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(m_dxymax > 0 && fabs(sigObj->getFMVAVar_d0()) > m_dxymax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_dxymax;

  ClassDef(ObjectCutElectronVertDxy,1);

};

inline bool ObjectCutElectronVertDxy::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
