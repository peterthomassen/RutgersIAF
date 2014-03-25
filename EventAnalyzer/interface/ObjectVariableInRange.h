#ifndef ObjectVariableInRange_h
#define ObjectVariableInRange_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

template <typename T> 
class ObjectVariableInRange : public ObjectVariable {
 public:
  ObjectVariableInRange(TString variable,T low=0, T high=100000,TString name="variableinrangecut") : ObjectVariable(name),m_variable(variable),m_low(low),m_high(high){ /*no-op*/}
    
  virtual ~ObjectVariableInRange(){}

  bool calculate(SignatureObject* sigObj)
  {
    T value;
    if(!sigObj->getVariable(m_variable,value))return false;
    if(value < m_low){
      sigObj->setVariable(getName(),false);
      return false;
    }
    if(value > m_high){
      sigObj->setVariable(getName(),false);
      return false;
    }
    sigObj->setVariable(getName(),true);
    return true;
  }

 private:
  TString m_variable;
  T m_low;
  T m_high;

  ClassDef(ObjectVariableInRange,1);

};

#endif
