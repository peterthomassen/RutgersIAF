#ifndef SignatureTH1F_EventVariable_h
#define SignatureTH1F_EventVariable_h

#include <TH1F.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"

template <typename T>
class SignatureTH1F_EventVariable : public SignatureTH1F {
public:
  
  SignatureTH1F_EventVariable(const char* name, TString varname, const char* title = "N Distribution", int nbins = 20, double xmin = -0.5, double xmax = 19.5, TString weightName = ""):SignatureTH1F(name,title,nbins,xmin,xmax),m_varname(varname),m_weightName(weightName){ }
    
  SignatureTH1F_EventVariable(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_EventVariable():SignatureTH1F() {}
  
  using TH1F::Fill;
  Int_t Fill(BaseHandler* handler);

  virtual void Copy(TObject& hnew) const
  {
    TH1F::Copy(hnew);
    ((SignatureTH1F_EventVariable<T>&)hnew).m_varname = m_varname;
    ((SignatureTH1F_EventVariable<T>&)hnew).m_weightName = m_weightName;
  }

  ClassDef(SignatureTH1F_EventVariable,1);

 protected:
  TString m_varname;
  TString m_weightName;
};

#endif
