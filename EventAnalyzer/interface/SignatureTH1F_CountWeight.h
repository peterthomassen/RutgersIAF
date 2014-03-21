#ifndef SignatureTH1F_CountWeight_h
#define SignatureTH1F_CountWeight_h

#include <TH1F.h>
#include <TString.h>
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F.h"

class SignatureTH1F_CountWeight : public SignatureTH1F {
public:
  
  SignatureTH1F_CountWeight(const char* name):SignatureTH1F(name,"Event Count",1,0,1){ }
    
  SignatureTH1F_CountWeight(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_CountWeight():SignatureTH1F() {}
	
  Int_t Fill(BaseHandler* handler)
  {    
    return TH1F::Fill(0.5,handler->getPhysicsWeight());
  }

  ClassDef(SignatureTH1F_CountWeight,1);

 protected:
};

#endif
