#ifndef EventVariableConst_h
#define EventVariableConst_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

template <typename T>
class EventVariableConst : public EventVariable
{
 public:

  EventVariableConst(T value, TString name = "variablevaluecut") : EventVariable(name),m_value(value) { /* no-op */ }
  virtual ~EventVariableConst(){}

  bool calculate(BaseHandler* handler) {
    handler->setVariable(getName(), m_value);
    return true;
  }

 private:
  T m_value;

 ClassDef(EventVariableConst,1);

};

#endif
