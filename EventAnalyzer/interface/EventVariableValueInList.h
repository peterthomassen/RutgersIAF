#ifndef EventVariableValueInList_h
#define EventVariableValueInList_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

template <typename T>
class EventVariableValueInList : public EventVariable
{
 public:

  EventVariableValueInList(TString variable, T value, TString name = "variablevaluecut") : EventVariable(name),m_variable(variable) { m_values.push_back(value);}
  virtual ~EventVariableValueInList(){}

  void addValue(T value){m_values.push_back(value);}

  bool calculate(BaseHandler* handler) {
    T value;
    if(!handler->getVariable(m_variable,value))return false;
    bool retval = false;
    for(int i = 0; i < (int)m_values.size() && !retval; i++){
      if(value == m_values[i])retval = true;
    }
    handler->setVariable(getName(),retval);
    return retval;
  }

 private:
  TString m_variable;
  std::vector<T> m_values;

 ClassDef(EventVariableValueInList,1);

};

#endif
