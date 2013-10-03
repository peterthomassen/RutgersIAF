#ifndef ObjectCutTrackIsGlobal_h
#define ObjectCutTrackIsGlobal_h

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

class ObjectCutTrackIsGlobal : public ObjectCut {
 public:
  ObjectCutTrackIsGlobal(bool isPromptTight=true,const char* name="istrackercut") : ObjectCut(name),m_isTrackIsGlobal(isPromptTight){ /*no-op*/}
    //ObjectCutTrackIsGlobal(bool isPromptTight=true) : ObjectCutTrackIsGlobal("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutTrackIsGlobal(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_isTrackIsGlobal != (bool)sigObj->getIsGlobal()) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  bool m_isTrackIsGlobal;

  ClassDef(ObjectCutTrackIsGlobal,1);

};

inline bool ObjectCutTrackIsGlobal::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
