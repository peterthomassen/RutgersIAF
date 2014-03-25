#ifndef ObjectCutVariableValueInList_h
#define ObjectCutVariableValueInList_h

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
class ObjectVariableValueInList : public ObjectVariable {
 public:
  ObjectVariableValueInList(TString variable,T val, TString name="variablevaluecut") : ObjectVariable(name),m_variable(variable){ m_values.push_back(val);}
    
  virtual ~ObjectVariableValueInList(){}

  void addValue(T c){m_values.push_back(c);}

  bool calculate(SignatureObject* sigObj)
  {
    T value;
    if(!sigObj->getVariable(m_variable,value))return false;
    bool retval = false;

    for(int i = 0; i < (int)m_values.size() && !retval; i++){
      if(value == m_values[i])retval = true;
    }

    sigObj->setVariable(getName(),retval);
    return retval;
  }

 private:
  TString m_variable;
  std::vector<T> m_values;

  ClassDef(ObjectVariableValueInList,1);

};


#endif
