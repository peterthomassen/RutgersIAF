#ifndef ObjectCutIrelNeutralHadron_h
#define ObjectCutIrelNeutralHadron_h

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

class ObjectCutIrelNeutralHadron : public ObjectCut {
 public:
  ObjectCutIrelNeutralHadron(double irelmin=0.0,double irelmax=0.15, const char* name="irelcut") : ObjectCut(name),m_irelmin(irelmin),m_irelmax(irelmax){ /*no-op*/}
    //ObjectCutIrelNeutralHadron(double irelmax=0.15) : ObjectCutIrelNeutralHadron("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrelNeutralHadron(){}

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

  ClassDef(ObjectCutIrelNeutralHadron,1);

};
inline double ObjectCutIrelNeutralHadron::calcIrel(SignatureObjectWithIso* sigobj) const
{
  return sigobj->getRhoCorrectedPFNeutralHadronIsolation()/sigobj->Pt();
}

inline bool ObjectCutIrelNeutralHadron::operator()(SignatureObjectWithIso* sigobj) const
{
  return passCut(sigobj);
}
#endif
