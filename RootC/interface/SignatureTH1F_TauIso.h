#ifndef SignatureTH1F_TauIso_H
#define SignatureTH1F_TauIso_H

#include <TH1F.h>
#include <string.h>
#include <vector>
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_TauIso : public SignatureTH1F {

   public:
      
  SignatureTH1F_TauIso(const char* name, const char * productname, double jetcutmin = -1, double jetcutmax = -1, TString jetsource = "LEAD", const char* title = "I_{abs} Distribution ; I_{abs} (GeV) ; ", int nbins = 60, double xmin = 0, double xmax = 30):SignatureTH1F(name,title,nbins,xmin,xmax),m_jetmin(jetcutmin),m_jetmax(jetcutmax),m_jetsource(jetsource){ m_productname = productname;}

  SignatureTH1F_TauIso(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_TauIso():SignatureTH1F() {}

  Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH1F_TauIso,1)


 protected:

  TString m_productname;
  double m_jetmin,m_jetmax;
  TString m_jetsource;

};

#endif
