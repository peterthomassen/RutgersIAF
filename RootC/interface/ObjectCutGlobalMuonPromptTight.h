#ifndef ObjectCutGlobalMuonPromptTight_h
#define ObjectCutGlobalMuonPromptTight_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMuon.h"

class ObjectCutGlobalMuonPromptTight : public ObjectCut {
 public:
  ObjectCutGlobalMuonPromptTight(bool isPromptTight=true,const char* name="globalmuonprompttightcut") : ObjectCut(name),m_isGlobalMuonPromptTight(isPromptTight){ /*no-op*/}
    //ObjectCutGlobalMuonPromptTight(bool isPromptTight=true) : ObjectCutGlobalMuonPromptTight("globalmuonprompttight",isPromptTight) { /* no-op */ }
    
  virtual ~ObjectCutGlobalMuonPromptTight(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(m_isGlobalMuonPromptTight != (bool)sigObj->getIsGlobalMuonPromptTight()) return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  bool m_isGlobalMuonPromptTight;

  ClassDef(ObjectCutGlobalMuonPromptTight,1);

};

inline bool ObjectCutGlobalMuonPromptTight::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
