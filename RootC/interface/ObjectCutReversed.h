#ifndef ObjectCutReversed_h
#define ObjectCutReversed_h

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

class ObjectCutReversed : public ObjectCut {
 public:
  ObjectCutReversed(ObjectCut* cut1, const char* name="reversedcut") : ObjectCut(name),m_cut1(cut1){ /*no-op*/}
    //ObjectCutReversed(double ptlow = 8.,double pthigh = -1):ObjectCutReversed("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectCutReversed(){}

  bool passCut(SignatureObject* sigObj) const
  {
    return !(m_cut1->passCut(sigObj));
  }
  bool operator()(SignatureObject*) const;

 private:
  ObjectCut* m_cut1;

  ClassDef(ObjectCutReversed,1);

};

inline bool ObjectCutReversed::operator()(SignatureObject* sigobj) const
{
  return passCut(sigobj);
}
#endif
