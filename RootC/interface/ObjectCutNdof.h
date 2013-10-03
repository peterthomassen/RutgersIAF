#ifndef ObjectCutNdof_h
#define ObjectCutNdof_h

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

class ObjectCutNdof : public ObjectCut {
 public:
  ObjectCutNdof( double ndofmin=1, double ndofmax=-1,const char* name="ndofcut") : ObjectCut(name),m_ndofmin(ndofmin),m_ndofmax(ndofmax){ /*no-op*/}
    //ObjectCutNdof(double chi2ndofmax=10) : ObjectCutNdof("chi2ndofcut",chi2ndofmax) { /* no-op */}
    
  virtual ~ObjectCutNdof(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectRecoTrack*) sigObj); }
  bool passCut(SignatureObjectRecoTrack* sigObj) const
  {
    if(m_ndofmin > 0 && sigObj->getNdof() < m_ndofmin)return false;
    if(m_ndofmax > 0 && sigObj->getNdof() > m_ndofmax)return false;
    return true;
  }
  bool operator()(SignatureObjectRecoTrack*) const;

 private:
  double m_ndofmin;
  double m_ndofmax;


  ClassDef(ObjectCutNdof,1);

};

inline bool ObjectCutNdof::operator()(SignatureObjectRecoTrack* sigobj) const
{
  return passCut(sigobj);
}
#endif
