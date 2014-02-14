#ifndef ObjectCutReversed_h
#define ObjectCutReversed_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

class ObjectCutReversed : public ObjectCut {
 public:
  ObjectCutReversed(TString cut1, const char* name="reversedcut") : ObjectCut(name),m_cut1(cut1){ /*no-op*/}
    //ObjectCutReversed(double ptlow = 8.,double pthigh = -1):ObjectCutReversed("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectCutReversed(){}

  bool passCut(SignatureObject* sigObj) const
  {
    bool retval;
    bool isSet = sigObj->getVariable(m_cut1,retval);
    if(isSet)return !retval;
    else return false;
  }
  bool operator()(SignatureObject*) const;

 private:
  TString m_cut1;

  ClassDef(ObjectCutReversed,1);

};

inline bool ObjectCutReversed::operator()(SignatureObject* sigobj) const
{
  return passCut(sigobj);
}
#endif
