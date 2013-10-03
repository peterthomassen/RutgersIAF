#ifndef ObjectCutChi2Ndof_h
#define ObjectCutChi2Ndof_h

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

class ObjectCutChi2Ndof : public ObjectCut {
 public:
  ObjectCutChi2Ndof( double chi2ndofmax=10, const char* name="chi2ndofcut") : ObjectCut(name),m_chi2ndofmax(chi2ndofmax){ /*no-op*/}
    //ObjectCutChi2Ndof(double chi2ndofmax=10) : ObjectCutChi2Ndof("chi2ndofcut",chi2ndofmax) { /* no-op */}
    
  virtual ~ObjectCutChi2Ndof(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(sigObj->getNdof() > 0 && sigObj->getChi2()/sigObj->getNdof() > m_chi2ndofmax) return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_chi2ndofmax;


  ClassDef(ObjectCutChi2Ndof,1);

};

inline bool ObjectCutChi2Ndof::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
