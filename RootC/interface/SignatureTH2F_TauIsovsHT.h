#ifndef SignatureTH2F_TauIsovsHT_H
#define SignatureTH2F_TauIsovsHT_H

#include <TH2F.h>
#include "RutgersIAF/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF/RootC/interface/SignatureObjectTau.h"

class SignatureTH2F_TauIsovsHT : public SignatureTH2F {
 public:
  SignatureTH2F_TauIsovsHT(const char* name, const char * productname, const char* title = "TauIso vs HT Distribution", Int_t nbinsX = 60, Double_t minX = 0, Double_t maxX = 30, Int_t nbinsY = 200, Double_t minY = 0, Double_t maxY = 2500):SignatureTH2F(name,title,nbinsX,minX,maxX,nbinsY,minY,maxY){ m_productname = productname; }

    SignatureTH2F_TauIsovsHT(TH2F h):SignatureTH2F(h) {}
    SignatureTH2F_TauIsovsHT():SignatureTH2F() {}
	
    Int_t Fill(BaseHandler*);

    ClassDef(SignatureTH2F_TauIsovsHT,1);

 protected:
  TString m_productname;

};

inline Int_t SignatureTH2F_TauIsovsHT::Fill(BaseHandler* handler)
{
  Int_t dummy = -1;
  
  std::vector<SignatureObject*> v = handler->getProduct(m_productname);

  for(std::vector<SignatureObject*>::iterator it = v.begin(); it != v.end(); ++it){
    SignatureObjectTau* tau = (SignatureObjectTau*)(*it);
    dummy = TH2F::Fill(tau->getTotalIso(), handler->getHT(), handler->getPhysicsWeight());
  }
  
  return dummy;
}




#endif
