#ifndef SignatureTH1F_EventVariable_h
#define SignatureTH1F_EventVariable_h

#include <TH1F.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"

template <typename T>
class SignatureTH1F_EventVariable : public SignatureTH1F {
public:
  
  SignatureTH1F_EventVariable(const char* name, TString varname, const char* title = "N Distribution", int nbins = 20, double xmin = -0.5, double xmax = 19.5):SignatureTH1F(name,title,nbins,xmin,xmax),m_varname(varname){ }
    
  SignatureTH1F_EventVariable(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_EventVariable():SignatureTH1F() {}
  
  using TH1F::Fill;
  Int_t Fill(BaseHandler* handler)
  {
    T value;
    bool isSet = handler->getVariable(m_varname,value);
    if(!isSet)return -1;
    
    return TH1F::Fill(value,handler->getPhysicsWeight());
  }

  ClassDef(SignatureTH1F_EventVariable,1);

 protected:
  TString m_varname;
};

#endif
