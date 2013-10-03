#ifndef ObjectCutPt_h
#define ObjectCutPt_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"

class ObjectCutPt : public ObjectCut {
 public:
  ObjectCutPt(double ptlow=8., double pthigh=-1,const char* name="ptcut") : ObjectCut(name),m_ptlow(ptlow),m_pthigh(pthigh){ /*no-op*/}
    //ObjectCutPt(double ptlow = 8.,double pthigh = -1):ObjectCutPt("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectCutPt(){}

  bool passCut(SignatureObject* sigObj) const
  {
    if(m_ptlow > 0 && sigObj->Pt() < m_ptlow) return false;
    if(m_pthigh > 0 && sigObj->Pt() > m_pthigh) return false;
    return true;
  }
  bool operator()(SignatureObject*) const;

 private:
  double m_ptlow;
  double m_pthigh;

  ClassDef(ObjectCutPt,1);

};

inline bool ObjectCutPt::operator()(SignatureObject* sigobj) const
{
  return passCut(sigobj);
}
#endif
