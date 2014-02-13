#ifndef SignatureCutVariableValue_h
#define SignatureCutVariableValue_h

#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"

template <typename T>
class SignatureCutVariableValue : public SignatureCut
{
 public:

  SignatureCutVariableValue(TString variable, T value, TString name = "variablevaluecut") : SignatureCut(name),m_variable(variable),m_value(value) { /* no-op */ }
  virtual ~SignatureCutVariableValue(){}

  bool passCut(BaseHandler* handler) const{
    T value;
    if(!handler->getVariable(m_variable,value))return false;
    return value == m_value;
  }
  bool operator()(BaseHandler* handler) const{
    return passCut(handler);
  }

 private:
 TString m_variable;
 T m_value;

 ClassDef(SignatureCutVariableValue,1);

};

#endif
