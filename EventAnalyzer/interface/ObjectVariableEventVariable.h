#ifndef ObjectVariableEventVariable_h
#define ObjectVariableEventVariable_h

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
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

template <typename T> 
class ObjectVariableEventVariable : public ObjectVariable {
 public:
  ObjectVariableEventVariable(TString variable,BaseHandler* handler, TString name="variablevaluecut") : ObjectVariable(name),m_variable(variable),m_handler(handler){ /*no-op*/}
    
  virtual ~ObjectVariableEventVariable(){}

  bool calculate(SignatureObject* sigObj)
  {
    T value;
    if(!m_handler->getVariable(m_variable,value))return false;
    sigObj->setVariable(getName(),value);
    return true;
  }

 private:
  TString m_variable;
  BaseHandler* m_handler;

  ClassDef(ObjectVariableEventVariable,1);

};


#endif
