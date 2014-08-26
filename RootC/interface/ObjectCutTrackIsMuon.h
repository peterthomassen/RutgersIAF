#ifndef ObjectCutTrackIsMuon_h
#define ObjectCutTrackIsMuon_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutTrackIsMuon : public ObjectCut {
 public:
  ObjectCutTrackIsMuon(bool isPromptTight=true,const char* name="istrackercut") : ObjectCut(name),m_isTrackIsMuon(isPromptTight){ /*no-op*/}
    //ObjectCutTrackIsMuon(bool isPromptTight=true) : ObjectCutTrackIsMuon("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutTrackIsMuon(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_isTrackIsMuon != (bool)sigObj->getIsMuon()) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  bool m_isTrackIsMuon;

  ClassDef(ObjectCutTrackIsMuon,1);

};

inline bool ObjectCutTrackIsMuon::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
