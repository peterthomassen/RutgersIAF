#ifndef SignatureTH1F_TopTagChi2_H
#define SignatureTH1F_TopTagChi2_H

#include <TH1F.h>
#include <string.h>
#include <vector>
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_TopTagChi2 : public SignatureTH1F {

 public:
      
  SignatureTH1F_TopTagChi2(const char* name, const char * productname, double refMass = 80.4, const char* title = "Top Tag Chi2 ; avg sqrt(Chi2) (GeV) ; ", int nbins = 100, double xmin = 0, double xmax = 100):SignatureTH1F(name,title,nbins,xmin,xmax),m_refMass(refMass){ m_product = productname;}

  SignatureTH1F_TopTagChi2(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_TopTagChi2():SignatureTH1F() {}
    
  Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH1F_TopTagChi2,1)


 protected:
  double m_refMass;
  TString m_product;

};

#endif
