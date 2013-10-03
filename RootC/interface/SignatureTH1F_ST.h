#ifndef SignatureTH1F_ST_h
#define SignatureTH1F_ST_h
#include <TH1F.h>
#include <string.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_ST : public SignatureTH1F {

public:
	SignatureTH1F_ST(const char* name, const char* title = "S_{T} Distribution", int nbins = 300, double xmin = 0, double xmax = 3000):SignatureTH1F(name,title,nbins,xmin,xmax){}

	SignatureTH1F_ST(TH1F h):SignatureTH1F(h) {/**/}
	SignatureTH1F_ST():SignatureTH1F() {/**/}

	Int_t Fill(BaseHandler*);

	ClassDef(SignatureTH1F_ST,1);
};

inline Int_t SignatureTH1F_ST::Fill(BaseHandler* handler)
{
	return TH1F::Fill(handler->getST(),handler->getPhysicsWeight());	
}

#endif
