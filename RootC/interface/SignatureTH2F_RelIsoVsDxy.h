#ifndef SignatureTH2F_RelIsoVsDxy_H
#define SignatureTH2F_RelIsoVsDxy_H

#include <TH2F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "RutgersIAF/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF/RootC/interface/SignatureRecoVertex.h"

class SignatureTH2F_RelIsoVsDxy : public SignatureTH2F {
 public:
  SignatureTH2F_RelIsoVsDxy(const char* name, const char * productname, double jetcutmin = -1, double jetcutmax = -1, TString jetsource = "HT", const char* title = "I_{rel} vs d_{xy} Distribution ; d_{xy} (cm) ; I_{rel}", Int_t nbinsx = 80, Double_t xmin = -0.2, Double_t xmax = 0.2, Int_t nbinsy = 200, Double_t ymin = 0, Double_t ymax = 10):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax){m_productname = productname; m_jetsource = jetsource; m_jetsource.ToUpper(); m_jetmin = jetcutmin; m_jetmax = jetcutmax;}
    
  SignatureTH2F_RelIsoVsDxy(TH2F h):SignatureTH2F(h) {}
  SignatureTH2F_RelIsoVsDxy():SignatureTH2F() {}

  void addSubtractProduct(TString c);

  virtual Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH2F_RelIsoVsDxy,1);

 protected:
  
  TString m_productname;
  TString m_jetsource;
  double m_jetmin,m_jetmax;
  std::vector<TString> m_subtractproducts;

};



#endif
