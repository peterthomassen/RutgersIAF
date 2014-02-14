#ifndef SignatureCutVariableInRange_h
#define SignatureCutVariableInRange_h

#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"

template <typename T>
class SignatureCutVariableInRange : public SignatureCut
{
 public:

  SignatureCutVariableInRange(TString variable, T low = 0, T high = 100000, TString name = "variableinrangecut") : SignatureCut(name),m_variable(variable),m_low(low),m_high(high) { /* no-op */ }
  virtual ~SignatureCutVariableInRange(){}

  bool passCut(BaseHandler* handler) const{
    T value;
    if(!handler->getVariable(m_variable,value))return false;
    if(value < m_low)return false;
    if(value > m_high)return false;
    return true;
  }
  bool operator()(BaseHandler* handler) const{
    return passCut(handler);
  }

 private:
 TString m_variable;
 T m_low;
 T m_high;

 ClassDef(SignatureCutVariableInRange,1);

};

#endif
