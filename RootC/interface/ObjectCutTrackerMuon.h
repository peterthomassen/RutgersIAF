#ifndef ObjectCutTrackerMuon_h
#define ObjectCutTrackerMuon_h

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

class ObjectCutTrackerMuon : public ObjectCut {
 public:
  ObjectCutTrackerMuon(bool isPromptTight=true,const char* name="trackermuoncut") : ObjectCut(name),m_isTrackerMuon(isPromptTight){ /*no-op*/}
    //ObjectCutTrackerMuon(bool isPromptTight=true) : ObjectCutTrackerMuon("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutTrackerMuon(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectMuon*) sigObj); }
  bool passCut(SignatureObjectMuon* sigObj) const
  {
    if(m_isTrackerMuon != (bool)sigObj->getIsTrackerMuon()) return false;
    return true;
  }
  bool operator()(SignatureObjectMuon*) const;

 private:
  bool m_isTrackerMuon;

  ClassDef(ObjectCutTrackerMuon,1);

};

inline bool ObjectCutTrackerMuon::operator()(SignatureObjectMuon* sigobj) const
{
  return passCut(sigobj);
}
#endif
