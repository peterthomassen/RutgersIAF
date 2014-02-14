#ifndef SignatureTH2F_METxy_H
#define SignatureTH2F_METxy_H

#include <TH2F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"

class SignatureTH2F_METxy : public SignatureTH2F {
 public:
  SignatureTH2F_METxy(const char* name, const char* title = "MET_{y} vs MET_{x} Distribution ; M (GeV) ; MET (GeV)", Int_t nbinsx = 250, Double_t xmin = -250, Double_t xmax = 250, Int_t nbinsy = 250, Double_t ymin = -250, Double_t ymax = 250):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax){}
    
  SignatureTH2F_METxy(TH2F h):SignatureTH2F(h) {}
  SignatureTH2F_METxy():SignatureTH2F() {}

  virtual Int_t Fill(BaseHandler*);
  Int_t Fill(SignatureHandler*);

  ClassDef(SignatureTH2F_METxy,1);

 protected:

};

#endif
