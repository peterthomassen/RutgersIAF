#ifndef ObjectCutIrelPhoton_h
#define ObjectCutIrelPhoton_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectWithIso.h"

class ObjectCutIrelPhoton : public ObjectCut {
 public:
  ObjectCutIrelPhoton(double irelmin=0.0,double irelmax=0.15, const char* name="irelcut") : ObjectCut(name),m_irelmin(irelmin),m_irelmax(irelmax){ /*no-op*/}
    //ObjectCutIrelPhoton(double irelmax=0.15) : ObjectCutIrelPhoton("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrelPhoton(){}

  virtual double calcIrel(SignatureObjectWithIso* sigObj) const;
  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*) sigObj); }
  virtual bool passCut(SignatureObjectWithIso* sigObj) const
  {
    double irel = calcIrel(sigObj);
    if(m_irelmin > 0 && irel < m_irelmin) return false;
    if(m_irelmax > 0 && irel > m_irelmax) return false;
    return true;
  }
  virtual bool operator()(SignatureObjectWithIso*) const;

 protected:
  double m_irelmin;
  double m_irelmax;

  ClassDef(ObjectCutIrelPhoton,1);

};
inline double ObjectCutIrelPhoton::calcIrel(SignatureObjectWithIso* sigobj) const
{
  return sigobj->getRhoCorrectedPFPhotonIsolation()/sigobj->Pt();
}

inline bool ObjectCutIrelPhoton::operator()(SignatureObjectWithIso* sigobj) const
{
  return passCut(sigobj);
}
#endif
