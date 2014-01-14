#ifndef SignatureTH2F_METvsAllMass_H
#define SignatureTH2F_METvsAllMass_H

#include <TH2F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"

class SignatureTH2F_METvsAllMass : public SignatureTH2F {
 public:
  SignatureTH2F_METvsAllMass(const char* name, const char* title = "MET vs AllMass Distribution ; AllMass (GeV) ; MET (GeV)", Int_t nbinsx = 250, Double_t xmin = 0, Double_t xmax = 500, Int_t nbinsy = 250, Double_t ymin = 0, Double_t ymax = 500):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax){}
    
  SignatureTH2F_METvsAllMass(TH2F h):SignatureTH2F(h) {}
  SignatureTH2F_METvsAllMass():SignatureTH2F() {}

  virtual Int_t Fill(BaseHandler*);
  void addProduct(TString c);

  ClassDef(SignatureTH2F_METvsAllMass,1);

 private:
  std::vector<TString> m_products;

 protected:

};

#endif
