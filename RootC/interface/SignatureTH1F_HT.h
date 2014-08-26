#ifndef SignatureTH1F_HT_h
#define SignatureTH1F_HT_h
#include <TH1F.h>
#include <string.h>
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_HT : public SignatureTH1F {

public:
	SignatureTH1F_HT(const char* name, const char* title = "H_{T} Distribution", int nbins = 200, double xmin = 0, double xmax = 2500):SignatureTH1F(name,title,nbins,xmin,xmax){}

	SignatureTH1F_HT(TH1F h):SignatureTH1F(h) {/**/}
	SignatureTH1F_HT():SignatureTH1F() {/**/}

	Int_t Fill(BaseHandler*);

	ClassDef(SignatureTH1F_HT,1);
};

inline Int_t SignatureTH1F_HT::Fill(BaseHandler* handler)
{
	return TH1F::Fill(handler->getHT(),handler->getPhysicsWeight());	
}

#endif
