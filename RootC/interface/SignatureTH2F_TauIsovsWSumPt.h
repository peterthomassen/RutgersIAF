#ifndef SignatureTH2F_TauIsovsWSumPt_H
#define SignatureTH2F_TauIsovsWSumPt_H

#include <TH2F.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureRecoVertex.h"

class SignatureTH2F_TauIsovsWSumPt : public SignatureTH2F {
 public:
  SignatureTH2F_TauIsovsWSumPt(const char* name, const char * productname, const char* title = "TauIso vs WSumPt Distribution", Int_t nbinsX = 60, Double_t minX = 0, Double_t maxX = 30, Int_t nbinsY = 200, Double_t minY = 0, Double_t maxY = 2500):SignatureTH2F(name,title,nbinsX,minX,maxX,nbinsY,minY,maxY){ m_productname = productname; }

    SignatureTH2F_TauIsovsWSumPt(TH2F h):SignatureTH2F(h) {}
    SignatureTH2F_TauIsovsWSumPt():SignatureTH2F() {}
	
    Int_t Fill(BaseHandler*);

    ClassDef(SignatureTH2F_TauIsovsWSumPt,1);

 protected:
  TString m_productname;

};

inline Int_t SignatureTH2F_TauIsovsWSumPt::Fill(BaseHandler* handler)
{
  Int_t dummy = -1;
  
	double WSumPt = (handler->getGoodRecoVertices().size() > 0)
		? std::max(handler->getGoodRecoVertices()[0]->getWSumPt(), 0.0)
		: -1000;
	
  std::vector<SignatureObject*> v = handler->getProduct(m_productname);

  for(std::vector<SignatureObject*>::iterator it = v.begin(); it != v.end(); ++it){
    SignatureObjectTau* tau = (SignatureObjectTau*)(*it);
    dummy = TH2F::Fill(tau->getTotalIso(), WSumPt, handler->getPhysicsWeight());
  }
  
  return dummy;
}




#endif
