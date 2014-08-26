#ifndef SignatureTH1F_MT_h
#define SignatureTH1F_MT_h
#include <TH1F.h>
#include <string.h>
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_MT : public SignatureTH1F {

public:
	SignatureTH1F_MT(const char* name, const char* title = "MT Distribution", int nbins = 150, double xmin = 0, double xmax = 1500):SignatureTH1F(name,title,nbins,xmin,xmax){}

	SignatureTH1F_MT(TH1F h):SignatureTH1F(h) {/**/}
	SignatureTH1F_MT():SignatureTH1F() {/**/}

	Int_t Fill(BaseHandler*);

	ClassDef(SignatureTH1F_MT,1);
};

inline Int_t SignatureTH1F_MT::Fill(BaseHandler* handler)
{
	return TH1F::Fill(handler->getMT(),handler->getPhysicsWeight());	
}

#endif
