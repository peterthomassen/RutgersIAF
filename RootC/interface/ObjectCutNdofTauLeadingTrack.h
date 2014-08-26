#ifndef ObjectCutNdofTauLeadingTrack_h
#define ObjectCutNdofTauLeadingTrack_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectTau.h"

class ObjectCutNdofTauLeadingTrack : public ObjectCut {
 public:
  ObjectCutNdofTauLeadingTrack( double ndofmin=1, double ndofmax = -1, const char* name="ndofcut") : ObjectCut(name),m_ndofmin(ndofmin),m_ndofmax(ndofmax){ /*no-op*/}
    //ObjectCutNdofTauLeadingTrack(double chi2ndofmax=10) : ObjectCutChi2NdofTauLeadingTrack("chi2ndofcut",chi2ndofmax) { /* no-op */}
    
  virtual ~ObjectCutNdofTauLeadingTrack(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(!sigObj->getLeadingTrack())return false;
    if(m_ndofmin > 0 && sigObj->getLeadingTrack()->getNdof() < m_ndofmin)return false;
    if(m_ndofmax > 0 && sigObj->getLeadingTrack()->getNdof() > m_ndofmax)return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  double m_ndofmin;
  double m_ndofmax;


  ClassDef(ObjectCutNdofTauLeadingTrack,1);

};

inline bool ObjectCutNdofTauLeadingTrack::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
