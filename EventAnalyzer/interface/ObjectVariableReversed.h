#ifndef ObjectVariableReversed_h
#define ObjectVariableReversed_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

class ObjectVariableReversed : public ObjectVariable {
 public:
  ObjectVariableReversed(TString cut1, const char* name="reversedcut") : ObjectVariable(name),m_cut1(cut1){ /*no-op*/}
    //ObjectVariableReversed(double ptlow = 8.,double pthigh = -1):ObjectVariableReversed("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectVariableReversed(){}

  bool calculate(SignatureObject* sigObj)
  {
    bool retval;
    bool isSet = sigObj->getVariable(m_cut1,retval);
    if(isSet){
      sigObj->setVariable(getName(),!retval);
      return !retval;
    }else{
      return false;
    }
  }

 private:
  TString m_cut1;

  ClassDef(ObjectVariableReversed,1);

};

#endif
