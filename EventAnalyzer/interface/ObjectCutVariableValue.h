#ifndef ObjectCutVariableValue_h
#define ObjectCutVariableValue_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

template <typename T> 
class ObjectCutVariableValue : public ObjectCut {
 public:
  ObjectCutVariableValue(TString variable,T val, TString name="variablevaluecut") : ObjectCut(name),m_variable(variable),m_value(val){ /*no-op*/}
    
  virtual ~ObjectCutVariableValue(){}

  bool passCut(SignatureObject* sigObj)
  {
    T value;
    if(!sigObj->getVariable(m_variable,value))return false;
    if(value != m_value){
      sigObj->setVariable(getName(),false);
      return false;
    }
    sigObj->setVariable(getName(),true);
    return true;
  }
  bool operator()(SignatureObject* sigobj)
  {
    return passCut(sigobj);
  }

 private:
  TString m_variable;
  T m_value;

  ClassDef(ObjectCutVariableValue,1);

};


#endif
