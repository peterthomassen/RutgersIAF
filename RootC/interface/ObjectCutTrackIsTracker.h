#ifndef ObjectCutTrackIsTracker_h
#define ObjectCutTrackIsTracker_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"

class ObjectCutTrackIsTracker : public ObjectCut {
 public:
  ObjectCutTrackIsTracker(bool isPromptTight=true,const char* name="istrackercut") : ObjectCut(name),m_isTrackIsTracker(isPromptTight){ /*no-op*/}
    //ObjectCutTrackIsTracker(bool isPromptTight=true) : ObjectCutTrackIsTracker("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutTrackIsTracker(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_isTrackIsTracker != (bool)sigObj->getIsTracker()) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  bool m_isTrackIsTracker;

  ClassDef(ObjectCutTrackIsTracker,1);

};

inline bool ObjectCutTrackIsTracker::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
