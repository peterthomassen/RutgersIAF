#ifndef ObjectCutEcalIso_h
#define ObjectCutEcalIso_h

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

class ObjectCutEcalIso : public ObjectCut {
 public:
  ObjectCutEcalIso(double relmin=-1.0,double relmax=10.0, const char* name="ecalisocut") : ObjectCut(name),m_relmin(relmin),m_relmax(relmax){ /*no-op*/}
    //ObjectCutEcalIso(double irelmax=0.15) : ObjectCutEcalIso("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutEcalIso(){}

  virtual double calcEcalIso(SignatureObjectWithIso* sigObj) const;
  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*) sigObj); }
  virtual bool passCut(SignatureObjectWithIso* sigObj) const
  {
    double rel = calcEcalIso(sigObj);
    if(m_relmin > 0 && rel < m_relmin) return false;
    if(m_relmax > 0 && rel > m_relmax) return false;
    return true;
  }
  virtual bool operator()(SignatureObjectWithIso*) const;

 protected:
  double m_relmin;
  double m_relmax;

  ClassDef(ObjectCutEcalIso,1);

};
inline double ObjectCutEcalIso::calcEcalIso(SignatureObjectWithIso* sigobj) const
{
  return sigobj->getEcaloIso();
}

inline bool ObjectCutEcalIso::operator()(SignatureObjectWithIso* sigobj) const
{
  return passCut(sigobj);
}
#endif
