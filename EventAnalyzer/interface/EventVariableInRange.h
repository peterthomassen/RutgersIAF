#ifndef EventVariableInRange_h
#define EventVariableInRange_h

#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"

template <typename T>
class EventVariableInRange : public EventVariable
{
 public:

  EventVariableInRange(TString variable, T low = 0, T high = 100000, TString name = "variableinrangecut") : EventVariable(name),m_variable(variable),m_low(low),m_high(high) { /* no-op */ }
  virtual ~EventVariableInRange(){}

  bool calculate(BaseHandler* handler) {
    T value;
    if(!handler->getVariable(m_variable,value))return false;
    if(value < m_low){
      handler->setVariable(getName(),false);
      return false;
    }
    if(value > m_high){
      handler->setVariable(getName(),false);
      return false;
    }
    handler->setVariable(getName(),true);
    return true;
  }

 private:
 TString m_variable;
 T m_low;
 T m_high;

 ClassDef(EventVariableInRange,1);

};

#endif
