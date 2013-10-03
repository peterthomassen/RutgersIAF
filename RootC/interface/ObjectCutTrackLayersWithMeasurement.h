#ifndef ObjectCutTrackLayersWithMeasurement_h
#define ObjectCutTrackLayersWithMeasurement_h

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

class ObjectCutTrackLayersWithMeasurement : public ObjectCut {
 public:
  ObjectCutTrackLayersWithMeasurement(int ntrackerlayersmin=6,int ntrackerlayersmax=-1,const char* name="validtrackercut") : ObjectCut(name),m_ntrackerlayersmin(ntrackerlayersmin),m_ntrackerlayersmax(ntrackerlayersmax){ /*no-op*/}
    //ObjectCutTrackLayersWithMeasurement(int ntrackerlayersmin=10,int ntrackerlayersmax=-1) : ObjectTrackLayersWithMeasurement("validtrackercut",ntrackerlayersmin,ntrackerlayersmax){ /* no-op */ }
    
  virtual ~ObjectCutTrackLayersWithMeasurement(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_ntrackerlayersmin > 0 && sigObj->getNtrackerLayersWM() < m_ntrackerlayersmin) return false;
    if(m_ntrackerlayersmax > 0 && sigObj->getNtrackerLayersWM() > m_ntrackerlayersmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  int m_ntrackerlayersmin;
  int m_ntrackerlayersmax;


  ClassDef(ObjectCutTrackLayersWithMeasurement,1);

};

inline bool ObjectCutTrackLayersWithMeasurement::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
