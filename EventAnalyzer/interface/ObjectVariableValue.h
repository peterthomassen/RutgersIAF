#ifndef ObjectVariableValue_h
#define ObjectVariableValue_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T> 
class ObjectVariableValue : public ObjectVariable {
 public:
  ObjectVariableValue(TString variable,T val, TString name="variablevaluecut") : ObjectVariable(name),m_variable(variable),m_value(val){ /*no-op*/}
    
  virtual ~ObjectVariableValue(){}

  bool calculate(SignatureObject* sigObj)
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

 private:
  TString m_variable;
  T m_value;

  ClassDef(ObjectVariableValue,1);

};


#endif
