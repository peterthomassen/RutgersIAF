#ifndef EventVariableValue_h
#define EventVariableValue_h

#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"

template <typename T>
class EventVariableValue : public EventVariable
{
 public:

  EventVariableValue(TString variable, T value, TString name = "variablevaluecut") : EventVariable(name),m_variable(variable),m_value(value) { /* no-op */ }
  virtual ~EventVariableValue(){}

  bool calculate(BaseHandler* handler) {
    T value;
    if(!handler->getVariable(m_variable,value))return false;
    handler->setVariable(getName(),value == m_value);
    return value == m_value;
  }

 private:
  TString m_variable;
  T m_value;

 ClassDef(EventVariableValue,1);

};

#endif
