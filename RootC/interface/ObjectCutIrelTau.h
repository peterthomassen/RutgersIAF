#ifndef ObjectCutIrelTau_h
#define ObjectCutIrelTau_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <algorithm>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCutIrel.h"
#include "RutgersIAF/RootC/interface/SignatureObjectWithIso.h"
#include "RutgersIAF/RootC/interface/SignatureObjectTau.h"

class ObjectCutIrelTau : public ObjectCutIrel {
 public:
  ObjectCutIrelTau(double irelmin=0.0,double irelmax=0.15, const char* name="ireltaucut") : ObjectCutIrel(irelmin,irelmax,name){ /*no-op*/}
    //ObjectCutIrelTau(double irelmax=0.15) : ObjectCutIrelTau("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrelTau(){}

  bool passCut(SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*)sigObj); }
  bool operator() (SignatureObjectWithIso* sigObj) const { return passCut((SignatureObjectTau*) sigObj); }
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(sigObj->getLeadTrack_ntID() < 0)return false;
    if(!sigObj->getLeadingTrack())return false;
    double irel = calcIrel((SignatureObjectWithIso*)sigObj->getLeadingTrack());
    if(m_irelmin > 0 && irel < m_irelmin) return false;
    if(m_irelmax > 0 && irel > m_irelmax) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;


 private:

  ClassDef(ObjectCutIrelTau,1);

};

inline bool ObjectCutIrelTau::operator()(SignatureObjectTau* sigObj) const
{
  return passCut(sigObj);
}
#endif
