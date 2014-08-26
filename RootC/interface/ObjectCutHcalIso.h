#ifndef ObjectCutHcalIso_h
#define ObjectCutHcalIso_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include <algorithm>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectWithIso.h"

class ObjectCutHcalIso : public ObjectCut {
 public:
  ObjectCutHcalIso(double relmin=-1.0,double relmax=10.0, const char* name="hcalisocut") : ObjectCut(name),m_relmin(relmin),m_relmax(relmax){ /*no-op*/}
    //ObjectCutHcalIso(double irelmax=0.15) : ObjectCutHcalIso("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutHcalIso(){}

  virtual double calcHcalIso(SignatureObjectWithIso* sigObj) const;
  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*) sigObj); }
  virtual bool passCut(SignatureObjectWithIso* sigObj) const
  {
    double rel = calcHcalIso(sigObj);
    if(m_relmin > 0 && rel < m_relmin) return false;
    if(m_relmax > 0 && rel > m_relmax) return false;
    return true;
  }
  virtual bool operator()(SignatureObjectWithIso*) const;

 protected:
  double m_relmin;
  double m_relmax;

  ClassDef(ObjectCutHcalIso,1);

};
inline double ObjectCutHcalIso::calcHcalIso(SignatureObjectWithIso* sigobj) const
{
  return sigobj->getHcaloIso();
}

inline bool ObjectCutHcalIso::operator()(SignatureObjectWithIso* sigobj) const
{
  return passCut(sigobj);
}
#endif
