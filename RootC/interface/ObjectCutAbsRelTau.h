#ifndef ObjectCutAbsRelTau_h
#define ObjectCutAbsRelTau_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <algorithm>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCutAbsRel.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectWithIso.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"

class ObjectCutAbsRelTau : public ObjectCutAbsRel {
 public:
  ObjectCutAbsRelTau(double irelmin=0.0,double irelmax=0.15, const char* name="ireltaucut") : ObjectCutAbsRel(irelmin,irelmax,name){ /*no-op*/}
    //ObjectCutAbsRelTau(double irelmax=0.15) : ObjectCutAbsRelTau("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutAbsRelTau(){}

  double calcAbsRel(SignatureObjectTau*) const;
  bool passCut(SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    //if(sigObj->getLeadTrack_ntID() < 0)return false;
    double irel = calcAbsRel(sigObj);
    if(m_relmin > 0 && irel < m_relmin) return false;
    if(m_relmax > 0 && irel > m_relmax) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;


 private:

  ClassDef(ObjectCutAbsRelTau,1);

};

inline bool ObjectCutAbsRelTau::operator()(SignatureObjectTau* sigObj) const
{
  return passCut(sigObj);
}
#endif
