#ifndef ObjectCutIrelChargedHadron_h
#define ObjectCutIrelChargedHadron_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectWithIso.h"

class ObjectCutIrelChargedHadron : public ObjectCut {
 public:
  ObjectCutIrelChargedHadron(double irelmin=0.0,double irelmax=0.15, const char* name="irelcut") : ObjectCut(name),m_irelmin(irelmin),m_irelmax(irelmax){ /*no-op*/}
    //ObjectCutIrelChargedHadron(double irelmax=0.15) : ObjectCutIrelChargedHadron("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrelChargedHadron(){}

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

  ClassDef(ObjectCutIrelChargedHadron,1);

};
inline double ObjectCutIrelChargedHadron::calcIrel(SignatureObjectWithIso* sigobj) const
{
  return sigobj->getRhoCorrectedPFChargedHadronIsolation()/sigobj->Pt();
}

inline bool ObjectCutIrelChargedHadron::operator()(SignatureObjectWithIso* sigobj) const
{
  return passCut(sigobj);
}
#endif
