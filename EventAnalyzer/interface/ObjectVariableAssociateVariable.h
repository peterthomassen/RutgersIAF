#ifndef ObjectVariableAssociateVariable_h
#define ObjectVariableAssociateVariable_h

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
class ObjectVariableAssociateVariable : public ObjectVariable {
 public:
  ObjectVariableAssociateVariable(TString associate,TString variable, TString name="variablevaluecut") : ObjectVariable(name),m_associate(associate),m_variable(variable){ /*no-op*/}
    
  virtual ~ObjectVariableAssociateVariable(){}

  bool calculate(SignatureObject* sigObj)
  {
    SignatureObject* assoc = sigObj->getAssociate(m_associate);
    if(!assoc)return false;
    T value;
    if(!assoc->getVariable(m_variable,value))return false;
    sigObj->setVariable(getName(),value);
    return true;
  }

 private:
  TString m_associate;
  TString m_variable;

  ClassDef(ObjectVariableAssociateVariable,1);

};


#endif
