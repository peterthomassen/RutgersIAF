#ifndef SignatureTH1F_PT_H
#define SignatureTH1F_PT_H

#include <TH1F.h>
#include <string.h>
#include <vector>
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_PT : public SignatureTH1F {

   public:
      
  SignatureTH1F_PT(const char* name, const char * productname, double jetcutmin = -1, double jetcutmax = -1, TString jetsource = "", const char* title = "P_{T} Distribution ; p_{T} (GeV/c) ; ", int nbins = 50, double xmin = 0, double xmax = 200):SignatureTH1F(name,title,nbins,xmin,xmax),m_jetmin(jetcutmin),m_jetmax(jetcutmax),m_jetsource(jetsource){ m_productname = productname;}

  SignatureTH1F_PT(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_PT():SignatureTH1F() {}

  void addSubtractProduct(TString c);
  Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH1F_PT,1)


 protected:

  TString m_productname;
  double m_jetmin,m_jetmax;
  TString m_jetsource;
  std::vector<TString> m_subtractproducts;

};

#endif
