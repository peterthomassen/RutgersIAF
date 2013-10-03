#ifndef SignatureTH1F_LJMET_h
#define SignatureTH1F_LJMET_h
#include <TH1F.h>
#include <string.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_LJMET : public SignatureTH1F {

public:
	SignatureTH1F_LJMET(const char* name, const char* title = "LJMET Distribution", int nbins = 70, double xmin = 0, double xmax = 700):SignatureTH1F(name,title,nbins,xmin,xmax){}

	SignatureTH1F_LJMET(TH1F h):SignatureTH1F(h) {/**/}
	SignatureTH1F_LJMET():SignatureTH1F() {/**/}

	Int_t Fill(BaseHandler*);

	ClassDef(SignatureTH1F_LJMET,1);
};

inline Int_t SignatureTH1F_LJMET::Fill(BaseHandler* handler)
{
	return TH1F::Fill(handler->getLJMET(),handler->getPhysicsWeight());	
}

#endif
