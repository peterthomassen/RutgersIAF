#ifndef ObjectCutMT_h
#define ObjectCutMT_h

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
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMET.h"

class ObjectCutMT : public ObjectCut {
 public:
  ObjectCutMT(BaseHandler* handler,double ptlow=8., double pthigh=-1,const char* name="ptcut") : ObjectCut(name),m_handler(handler),m_ptlow(ptlow),m_pthigh(pthigh){ /*no-op*/}
    //ObjectCutMT(double ptlow = 8.,double pthigh = -1):ObjectCutMT("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectCutMT(){}

  bool passCut(SignatureObject* sigObj) const
  {
    SignatureObjectMET* met = m_handler->getMET();
    float mt = sqrt(2 * sigObj->Pt() * met->getPf_pt() * (1 - cos(sigObj->Phi() - met->getPf_phi()))); 
    if(m_ptlow > 0 && mt < m_ptlow) return false;
    if(m_pthigh > 0 && mt > m_pthigh) return false;
    return true;
  }
  bool operator()(SignatureObject*) const;

 private:
  BaseHandler* m_handler;
  double m_ptlow;
  double m_pthigh;

  ClassDef(ObjectCutMT,1);

};

inline bool ObjectCutMT::operator()(SignatureObject* sigobj) const
{
  return passCut(sigobj);
}
#endif
