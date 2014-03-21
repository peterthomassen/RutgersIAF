#ifndef EventVariableTF1_h
#define EventVariableTF1_h

#include <vector>
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include <TF1.h>

template <typename T>
class EventVariableTF1 : public EventVariable{
 public:
  EventVariableTF1(TString name, TString varname, TF1* f) : EventVariable(name), m_varname(varname) { m_function = f;}


  bool calculate(BaseHandler* handler){
    T value;
    bool isSet = handler->getVariable(m_varname, value);
    if(!isSet){
      return false;
    }else{
      double rv = m_function->Eval((double)value);
      handler->setVariable(getName(),rv);
      return true;
    }
  }

  ClassDef(EventVariableTF1,1);

 private:
  TString m_varname;
  TF1* m_function;

};

#endif
