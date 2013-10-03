#ifndef ObjectCutBeamD0TauLeadingTrack_h
#define ObjectCutBeamD0TauLeadingTrack_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"

class ObjectCutBeamD0TauLeadingTrack : public ObjectCut {
 public:
  ObjectCutBeamD0TauLeadingTrack(double dxymax=0.02, const char* name="dxycut") : ObjectCut(name),m_dxymax(dxymax){ /*no-op*/}
    //ObjectCutBeamD0TauLeadingTrack(double dxymax=0.02) : ObjectCutBeamD0TauLeadingTrack("dxycut",dxymax) { /* no-op */ }
    
  virtual ~ObjectCutBeamD0TauLeadingTrack(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(m_dxymax > 0 && fabs(sigObj->getLeadingTrack()->getBeam_d0()) > m_dxymax) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  double m_dxymax;

  ClassDef(ObjectCutBeamD0TauLeadingTrack,1);

};

inline bool ObjectCutBeamD0TauLeadingTrack::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
