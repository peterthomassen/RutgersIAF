#ifndef SignatureTH1F_ZpT_H
#define SignatureTH1F_ZpT_H

#include <TH1F.h>
#include <string.h>
#include <vector>
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_ZpT : public SignatureTH1F {

 public:
      
  SignatureTH1F_ZpT(const char* name, const char * productname, const char* title = "p_{T} Distribution ; p_{T} (GeV) ; ", int nbins = 50, double xmin = 0, double xmax = 500):SignatureTH1F(name,title,nbins,xmin,xmax){ m_products.push_back(productname);}

  SignatureTH1F_ZpT(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_ZpT():SignatureTH1F() {}
    
  void addProduct(TString c);
  Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH1F_ZpT,1)


 protected:
  std::vector<TString> m_products;

};

#endif
