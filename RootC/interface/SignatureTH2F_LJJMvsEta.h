#ifndef SignatureTH2F_LJJMvsEta_H
#define SignatureTH2F_LJJMvsEta_H

#include <TH2F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "RutgersIAF/RootC/interface/SignatureTH2F.h"

class SignatureTH2F_LJJMvsEta : public SignatureTH2F {
 public:
  SignatureTH2F_LJJMvsEta(const char* leptonProductName, const char* jetProductName, const char* bJetProductName, const char* name, const char* title = "|#eta| vs M Distribution ; M (GeV) ; |#eta|", Int_t nbinsx = 100, Double_t xmin = 0, Double_t xmax = 1000, Int_t nbinsy = 100, Double_t ymin = 0, Double_t ymax = 3):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax),m_leptonProductName(leptonProductName),m_jetProductName(jetProductName),m_bJetProductName(bJetProductName){}
    
  SignatureTH2F_LJJMvsEta(TH2F h):SignatureTH2F(h) {}
  SignatureTH2F_LJJMvsEta():SignatureTH2F() {}

  virtual Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH2F_LJJMvsEta,1);

 protected:
  TString m_leptonProductName;
  TString m_jetProductName;
  TString m_bJetProductName;

};

#endif
