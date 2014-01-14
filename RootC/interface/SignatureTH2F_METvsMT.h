#ifndef SignatureTH2F_METvsMT_H
#define SignatureTH2F_METvsMT_H

#include <TH2F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"

class SignatureTH2F_METvsMT : public SignatureTH2F {
 public:
  SignatureTH2F_METvsMT(const char* name, const char* title = "MET vs MT Distribution ; MT (GeV) ; MET (GeV)", Int_t nbinsx = 250, Double_t xmin = 0, Double_t xmax = 500, Int_t nbinsy = 250, Double_t ymin = 0, Double_t ymax = 500):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax){}
    
  SignatureTH2F_METvsMT(TH2F h):SignatureTH2F(h) {}
  SignatureTH2F_METvsMT():SignatureTH2F() {}

  virtual Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH2F_METvsMT,1);

 protected:

};

#endif
