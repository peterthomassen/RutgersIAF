#ifndef SignatureTH2F_LeadPtVsM_H
#define SignatureTH2F_LeadPtVsM_H

#include <TH2F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "RutgersIAF/RootC/interface/SignatureTH2F.h"

class SignatureTH2F_LeadPtVsM : public SignatureTH2F {
 public:
  SignatureTH2F_LeadPtVsM(const char* name, const char * productname, bool samesign=false, const char* title = "Leading p_{T} vs M Distribution ; M (GeV/c^{2}) ; p_{T} (GeV/c)", Int_t nbinsx = 80, Double_t xmin = 0, Double_t xmax = 400, Int_t nbinsy = 50, Double_t ymin = 0, Double_t ymax = 200):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax),m_samesign(samesign){m_productname = productname;}
    
  SignatureTH2F_LeadPtVsM(TH2F h):SignatureTH2F(h) {}
  SignatureTH2F_LeadPtVsM():SignatureTH2F() {}

  virtual Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH2F_LeadPtVsM,1);

 protected:
  bool m_samesign;  
  TString m_productname;

};

#endif
