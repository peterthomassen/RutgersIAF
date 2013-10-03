#ifndef ObjectCutAbsRel_h
#define ObjectCutAbsRel_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include <algorithm>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectWithIso.h"

class ObjectCutAbsRel : public ObjectCut {
 public:
  ObjectCutAbsRel(double relmin=-1.0,double relmax=10.0, const char* name="absrelcut") : ObjectCut(name),m_relmin(relmin),m_relmax(relmax){ /*no-op*/}
    //ObjectCutAbsRel(double irelmax=0.15) : ObjectCutAbsRel("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutAbsRel(){}

  virtual double calcAbsRel(SignatureObjectWithIso* sigObj) const;
  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*) sigObj); }
  virtual bool passCut(SignatureObjectWithIso* sigObj) const
  {
    double rel = calcAbsRel(sigObj);
    if(m_relmin > 0 && rel < m_relmin) return false;
    if(m_relmax > 0 && rel > m_relmax) return false;
    return true;
  }
  virtual bool operator()(SignatureObjectWithIso*) const;

 protected:
  double m_relmin;
  double m_relmax;

  ClassDef(ObjectCutAbsRel,1);

};
inline double ObjectCutAbsRel::calcAbsRel(SignatureObjectWithIso* sigobj) const
{
  return sigobj->getTotalIso();
}

inline bool ObjectCutAbsRel::operator()(SignatureObjectWithIso* sigobj) const
{
  return passCut(sigobj);
}
#endif
