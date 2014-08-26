#ifndef EventVariableTH1_h
#define EventVariableTH1_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include <TH1.h>

template <typename T>
class EventVariableTH1 : public EventVariable{
 public:
  EventVariableTH1(TString name, TString varname, TH1* f) : EventVariable(name), m_varname(varname) { m_histo = f;}


  bool calculate(BaseHandler* handler){
    T value;
    bool isSet = handler->getVariable(m_varname, value);
    if(!isSet){
      return false;
    }else{
      int bin = m_histo->FindBin((double)value);
      double rv = m_histo->GetBinContent(bin);
      handler->setVariable(getName(),rv);
      return true;
    }
  }

  ClassDef(EventVariableTH1,1);

 private:
  TString m_varname;
  TH1* m_histo;

};

#endif
