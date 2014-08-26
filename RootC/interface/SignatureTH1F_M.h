#ifndef SignatureTH1F_M_H
#define SignatureTH1F_M_H

#include <TH1F.h>
#include <string.h>
#include <vector>
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_M : public SignatureTH1F {

 public:
      
  SignatureTH1F_M(const char* name, const char * productname, int chargeMode=0, int mixMode=0, const char* title = "M Distribution ; M (GeV) ; ", int nbins = 50, double xmin = 0, double xmax = 400):SignatureTH1F(name,title,nbins,xmin,xmax),m_chargeMode(chargeMode),m_mixMode(mixMode){ m_products.push_back(productname);}

  SignatureTH1F_M(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_M():SignatureTH1F() {}
    
  void addProduct(TString c);
  Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH1F_M,1)


 protected:
  int m_chargeMode;
  int m_mixMode;
  std::vector<TString> m_products;

};

#endif
