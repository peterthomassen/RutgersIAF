#ifndef SignatureTH1F_TCMET_h
#define SignatureTH1F_TCMET_h
#include <TH1F.h>
#include <string.h>
#include "RutgersIAF/RootC/interface/SignatureObjectMET.h"
#include "RutgersIAF/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_TCMET : public SignatureTH1F {

public:
	SignatureTH1F_TCMET(const char* name, const char* title = "\\ensuremath{\\not\\!\\!E_T}\\xspace Distribution", int nbins = 70, double xmin 
= 0, double xmax = 700):SignatureTH1F(strcat((char*)name,"_TCMET"),title,nbins,xmin,xmax){}

	SignatureTH1F_TCMET(TH1F h):SignatureTH1F(h) {/**/}
	SignatureTH1F_TCMET():SignatureTH1F() {/**/}

	Int_t Fill(BaseHandler*);

	ClassDef(SignatureTH1F_TCMET,1);
};

inline Int_t SignatureTH1F_TCMET::Fill(BaseHandler* handler)
{
  return TH1F::Fill(handler->getMET()->getTc_sumEt(),handler->getPhysicsWeight());	
}


#endif
