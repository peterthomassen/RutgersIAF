#ifndef ObjectCutMuonGlobal_h
#define ObjectCutMuonGlobal_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"

class ObjectCutMuonGlobal : public ObjectCut {
 public:
  ObjectCutMuonGlobal(bool isPromptTight=true,const char* name="globalmuonprompttightcut") : ObjectCut(name),m_isMuonGlobal(isPromptTight){ /*no-op*/}
    //ObjectCutMuonGlobal(bool isPromptTight=true) : ObjectCutMuonGlobal("globalmuonprompttight",isPromptTight) { /* no-op */ }
    
  virtual ~ObjectCutMuonGlobal(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(m_isMuonGlobal != (bool)sigObj->getIsGlobalMuon()) return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  bool m_isMuonGlobal;

  ClassDef(ObjectCutMuonGlobal,1);

};

inline bool ObjectCutMuonGlobal::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
