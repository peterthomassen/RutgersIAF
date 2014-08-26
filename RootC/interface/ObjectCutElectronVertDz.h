#ifndef ObjectCutElectronVertDz_h
#define ObjectCutElectronVertDz_h

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

class ObjectCutElectronVertDz : public ObjectCut {
 public:
  ObjectCutElectronVertDz(double dzmax=1.0, const char* name="dzcut") : ObjectCut(name),m_dzmax(dzmax){ /*no-op*/}
    //ObjectCutElectronVertDz(double dzmax = 1.0) : ObjectCutElectronVertDz("dzcut",dzmax) {/* no-op */ }
    
  virtual ~ObjectCutElectronVertDz(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
	//std::cout<<m_dzmax<<" "<<sigObj->getVert_dz()<<" "<<(int)(fabs(sigObj->getVert_dz()) > m_dzmax)<<std::endl;
    if(m_dzmax > 0 && fabs(sigObj->getFMVAVar_dz()) > m_dzmax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_dzmax;

  ClassDef(ObjectCutElectronVertDz,1);

};

inline bool ObjectCutElectronVertDz::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
