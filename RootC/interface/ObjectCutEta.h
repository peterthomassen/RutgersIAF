#ifndef ObjectCutEta_h
#define ObjectCutEta_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"

class ObjectCutEta : public ObjectCut {
 public:
  ObjectCutEta(double etamax=2.4, const char* name="etacut") : ObjectCut(name),m_etamax(etamax){ /*no-op*/}
    //ObjectCutEta(double etamax) : ObjectCutEta("etacut",etamax){ /* no-op */ }
    
  virtual ~ObjectCutEta(){}

  bool passCut(SignatureObject* sigObj) const
  {
    if(fabs(sigObj->Eta()) > m_etamax) return false;
    return true;
  }
  bool operator()(SignatureObject*) const;

 private:
  double m_etamax;


  ClassDef(ObjectCutEta,1);

};

inline bool ObjectCutEta::operator()(SignatureObject* sigobj) const
{
  return passCut(sigobj);
}
#endif
