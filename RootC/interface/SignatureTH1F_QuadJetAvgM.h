#ifndef SignatureTH1F_QuadJetAvgM_H
#define SignatureTH1F_QuadJetAvgM_H

#include <TH1F.h>
#include <string.h>
#include <vector>
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_QuadJetAvgM : public SignatureTH1F {

 public:
      
  SignatureTH1F_QuadJetAvgM(const char* name, const char * productname, double maxMassRes = 0.5, double minDelta = 60, const char* title = "Average dijet mass ; avg M_{jj} (GeV) ; ", int nbins = 1000, double xmin = 0, double xmax = 1000):SignatureTH1F(name,title,nbins,xmin,xmax),m_maxMassRes(maxMassRes),m_minDelta(minDelta){ m_product = productname;}

  SignatureTH1F_QuadJetAvgM(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_QuadJetAvgM():SignatureTH1F() {}
    
  Int_t Fill(BaseHandler*);

  ClassDef(SignatureTH1F_QuadJetAvgM,1)


 protected:
  double m_maxMassRes;
  double m_minDelta;
  TString m_product;

};

#endif
