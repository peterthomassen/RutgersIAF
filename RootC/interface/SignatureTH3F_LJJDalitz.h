#ifndef SignatureTH3F_LJJDalitz_H
#define SignatureTH3F_LJJDalitz_H

#include <TH3F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "RutgersIAF/RootC/interface/SignatureTH3F.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"

class SignatureTH3F_LJJDalitz : public SignatureTH3F {
 public:
  SignatureTH3F_LJJDalitz(const char* leptonProductName, const char* jetProductName, const char* bJetProductName, const char* name, const char* title = "M_{lj} vs M_{lj'} vs M_{jj'}; M_{lj} (GeV) ; M_{lj'} (GeV); M_{jj'} (GEV)", Int_t nbinsx = 100, Double_t xmin = 0, Double_t xmax = 1000, Int_t nbinsy = 100, Double_t ymin = 0, Double_t ymax = 1000, Int_t nbinsz = 100, Double_t zmin = 0, Double_t zmax = 1000):SignatureTH3F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax),m_leptonProductName(leptonProductName),m_jetProductName(jetProductName),m_bJetProductName(bJetProductName){}
    
  SignatureTH3F_LJJDalitz(TH3F h):SignatureTH3F(h) {}
  SignatureTH3F_LJJDalitz():SignatureTH3F() {}

  virtual Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH3F_LJJDalitz,1);

 protected:
  TString m_leptonProductName;
  TString m_jetProductName;
  TString m_bJetProductName;

};

#endif
