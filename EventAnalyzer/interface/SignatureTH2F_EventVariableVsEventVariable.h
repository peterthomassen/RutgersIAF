#ifndef SignatureTH2F_EventVariableVsEventVariable_h
#define SignatureTH2F_EventVariableVsEventVariable_h

#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH2F.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include <TString.h>

template <typename T1, typename T2>
class SignatureTH2F_EventVariableVsEventVariable : public SignatureTH2F 
{
 public:
  SignatureTH2F_EventVariableVsEventVariable(TString var1, TString var2, const char* name, const char* title="", Int_t nbinsx=100,Double_t xmin=0,Double_t xmax=1000, Int_t nbinsy=100, Double_t ymin=0, Double_t ymax=1000):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax),m_var1(var1),m_var2(var2) {}

  SignatureTH2F_EventVariableVsEventVariable(TH2F h):SignatureTH2F(h){}
  SignatureTH2F_EventVariableVsEventVariable():SignatureTH2F(){}

  Int_t Fill(BaseHandler* handler){
    T1 val1;
    T2 val2;
    if(!handler->getVariable(m_var1,val1))return -1;
    if(!handler->getVariable(m_var2,val2))return -1;
    return TH2F::Fill(val1,val2,handler->getPhysicsWeight());
  }

 private:
  TString m_var1;
  TString m_var2;

  ClassDef(SignatureTH2F_EventVariableVsEventVariable,1);
};
#endif
