#ifndef ObjectCutPtTauLeadingTrack_h
#define ObjectCutPtTauLeadingTrack_h

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

class ObjectCutPtTauLeadingTrack : public ObjectCut {
 public:
  ObjectCutPtTauLeadingTrack(double ptlow=8., double pthigh=-1,const char* name="ptcut") : ObjectCut(name),m_ptlow(ptlow),m_pthigh(pthigh){ /*no-op*/}
    //ObjectCutPtTauLeadingTrack(double ptlow = 8.,double pthigh = -1):ObjectCutPtTauLeadingTrack("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectCutPtTauLeadingTrack(){}

  bool passCut(SignatureObject* sigObj)const {return passCut((SignatureObjectTau*)sigObj);}
  bool operator()(SignatureObject* sigObj)const {return passCut((SignatureObjectTau*)sigObj);}
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(m_ptlow > 0 && sigObj->getLeadingTrack()->Pt() < m_ptlow) return false;
    if(m_pthigh > 0 && sigObj->getLeadingTrack()->Pt() > m_pthigh) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  double m_ptlow;
  double m_pthigh;

  ClassDef(ObjectCutPtTauLeadingTrack,1);

};

inline bool ObjectCutPtTauLeadingTrack::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
