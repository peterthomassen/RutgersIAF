#ifndef SignatureTH2F_HTvsWSumPt_H
#define SignatureTH2F_HTvsWSumPt_H

#include <TH2F.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF2012/RootC/interface/SignatureRecoVertex.h"

class SignatureTH2F_HTvsWSumPt : public SignatureTH2F {
 public:
  SignatureTH2F_HTvsWSumPt(const char* name, const char * productname, const char* title = "HT vs WSumPt Distribution", Int_t nbinsX = 200, Double_t minX = 0, Double_t maxX = 2500, Int_t nbinsY = 200, Double_t minY = 0, Double_t maxY = 2500):SignatureTH2F(name,title,nbinsX,minX,maxX,nbinsY,minY,maxY){ }

    SignatureTH2F_HTvsWSumPt(TH2F h):SignatureTH2F(h) {}
    SignatureTH2F_HTvsWSumPt():SignatureTH2F() {}
	
    Int_t Fill(BaseHandler*);

    ClassDef(SignatureTH2F_HTvsWSumPt,1);

 protected:

};

inline Int_t SignatureTH2F_HTvsWSumPt::Fill(BaseHandler* handler)
{
	double WSumPt = (handler->getGoodRecoVertices().size() > 0)
		? std::max(handler->getGoodRecoVertices()[0]->getWSumPt(), 0.0)
		: -1000;
	return TH2F::Fill(handler->getHT(), WSumPt, handler->getPhysicsWeight());
}




#endif
