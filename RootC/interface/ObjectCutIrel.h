#ifndef ObjectCutIrel_h
#define ObjectCutIrel_h

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

class ObjectCutIrel : public ObjectCut {
 public:
  ObjectCutIrel(double irelmin=0.0,double irelmax=0.15, const char* name="irelcut") : ObjectCut(name),m_irelmin(irelmin),m_irelmax(irelmax){ /*no-op*/}
    //ObjectCutIrel(double irelmax=0.15) : ObjectCutIrel("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrel(){}

  virtual double calcIrel(SignatureObjectWithIso* sigObj) const;
  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectWithIso*) sigObj); }
  virtual bool passCut(SignatureObjectWithIso* sigObj) const
  {
    double irel = calcIrel(sigObj);
    //std::cout<<irel<<std::endl;
    if(m_irelmin > 0 && irel < m_irelmin) return false;
    if(m_irelmax > 0 && irel > m_irelmax) return false;
    return true;
  }
  virtual bool operator()(SignatureObjectWithIso*) const;

 protected:
  double m_irelmin;
  double m_irelmax;

  ClassDef(ObjectCutIrel,1);

};
inline double ObjectCutIrel::calcIrel(SignatureObjectWithIso* sigobj) const
{
  return sigobj->getRelIso();
}

inline bool ObjectCutIrel::operator()(SignatureObjectWithIso* sigobj) const
{
  return passCut(sigobj);
}
#endif
