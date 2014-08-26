#ifndef EventVariableReversed_h
#define EventVariableReversed_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

class EventVariableReversed : public EventVariable {
 public:
  EventVariableReversed(TString cutname, const char* name="reversedsignaturecut") : EventVariable(name),m_cutname(cutname){ /* no-op */}
  virtual ~EventVariableReversed(){}

  bool calculate(BaseHandler* handler) 
  {
    bool retval;
    bool isSet = handler->getVariable(m_cutname,retval);
    if(!isSet)return false;
    handler->setVariable(getName(),!retval);
    return !retval;
  }

 private:
  TString m_cutname;

  ClassDef(EventVariableReversed,1);
};


#endif
