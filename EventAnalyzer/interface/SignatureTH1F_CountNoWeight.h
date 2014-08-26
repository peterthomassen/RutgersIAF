#ifndef SignatureTH1F_CountNoWeight_h
#define SignatureTH1F_CountNoWeight_h

#include <TH1F.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"

class SignatureTH1F_CountNoWeight : public SignatureTH1F {
public:
  
  SignatureTH1F_CountNoWeight(const char* name):SignatureTH1F(name,"Event Count",1,0,1){ }
    
  SignatureTH1F_CountNoWeight(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_CountNoWeight():SignatureTH1F() {}
	
  Int_t Fill(BaseHandler* handler)
  {    
    return TH1F::Fill(0.5,1);
  }

  ClassDef(SignatureTH1F_CountNoWeight,1);

 protected:
};

#endif
