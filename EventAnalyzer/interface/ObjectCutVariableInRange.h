#ifndef ObjectCutVariableInRange_h
#define ObjectCutVariableInRange_h

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
class ObjectCutVariableInRange : public ObjectCut {
 public:
  ObjectCutVariableInRange(TString variable,T low=0, T high=100000,TString name="variableinrangecut") : ObjectCut(name),m_variable(variable),m_low(low),m_high(high){ /*no-op*/}
    
  virtual ~ObjectCutVariableInRange(){}

  bool passCut(SignatureObject* sigObj) const
  {
    T value;
    if(!sigObj->getVariable(m_variable,value))return false;
    if(value < m_low) return false;
    if(value > m_high) return false;
    return true;
  }
  bool operator()(SignatureObject* sigObj) const
  {
    return passCut(sigObj);
  }

 private:
  TString m_variable;
  T m_low;
  T m_high;

  ClassDef(ObjectCutVariableInRange,1);

};

#endif
