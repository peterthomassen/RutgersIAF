#ifndef EventVariableRename_h
#define EventVariableRename_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

template <typename T>
class EventVariableRename : public EventVariable
{
 public:
  EventVariableRename(TString othername, TString name = "variablevaluecut") : EventVariable(name),m_cut1(othername) { /* no-op */ }
  virtual ~EventVariableRename(){}

  bool calculate(BaseHandler* handler) {
    T retval;
    bool isSet = handler->getVariable(m_cut1,retval);
    if(isSet){
      handler->setVariable(getName(), retval);
      return true;
    }else{
      return false;
    }
  }

 private:
  TString m_cut1;

 ClassDef(EventVariableRename,1);

};

#endif
