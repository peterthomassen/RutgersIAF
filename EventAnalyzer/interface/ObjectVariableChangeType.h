#ifndef ObjectVariableChangeType_h
#define ObjectVariableChangeType_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T1, typename T2>
class ObjectVariableChangeType : public ObjectVariable {
 public:
  ObjectVariableChangeType(TString cut1, const char* name="renamevar") : ObjectVariable(name),m_cut1(cut1){ /*no-op*/}
    //ObjectVariableChangeType(double ptlow = 8.,double pthigh = -1):ObjectVariableChangeType("ptcut",ptlow,pthigh) { /* no-op */ }
    
  virtual ~ObjectVariableChangeType(){}

  bool calculate(SignatureObject* sigObj)
  {
    T1 retval;
    bool isSet = sigObj->getVariable(m_cut1,retval);
    if(isSet){
      sigObj->setVariable(m_cut1,T2(retval));
      return true;
    }else{
      return false;
    }
  }

 private:
  TString m_cut1;

  ClassDef(ObjectVariableChangeType,1);

};

#endif
