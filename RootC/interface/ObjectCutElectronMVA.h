#ifndef ObjectCutElectronMVA_h
#define ObjectCutElectronMVA_h

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

class ObjectCutElectronMVA : public ObjectCut {
 public:
  ObjectCutElectronMVA(float nMVAmin = -1.0, float nMVAmax = 10.0,bool useTrig=true,const char* name="electronMVAcut" );
    //ObjectCutElectronMVA(int nMVAmax = 1) : ObjectCutElectronMVA("electronMVAcut",nMVAmax) { /* no-op */ }
    
  virtual ~ObjectCutElectronMVA(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const;
  bool operator()(SignatureObjectElectron*) const;

 private:
  float m_nMVAmin;
  float m_nMVAmax;
  bool m_useTrig;

  ClassDef(ObjectCutElectronMVA,1);

};

inline bool ObjectCutElectronMVA::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
