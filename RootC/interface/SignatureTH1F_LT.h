#ifndef SignatureTH1F_LT_h
#define SignatureTH1F_LT_h
#include <TH1F.h>
#include <string.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_LT : public SignatureTH1F {

public:
	SignatureTH1F_LT(const char* name, const char* title = "L_{T} Distribution", int nbins = 200, double xmin = 0, double xmax = 2500):SignatureTH1F(name,title,nbins,xmin,xmax){}

	SignatureTH1F_LT(TH1F h):SignatureTH1F(h) {/**/}
	SignatureTH1F_LT():SignatureTH1F() {/**/}

	Int_t Fill(BaseHandler*);

	ClassDef(SignatureTH1F_LT,1);
};

inline Int_t SignatureTH1F_LT::Fill(BaseHandler* handler)
{
	return TH1F::Fill(handler->getLT(),handler->getPhysicsWeight());	
}

#endif
