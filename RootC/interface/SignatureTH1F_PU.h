#ifndef SignatureTH1F_PU_h
#define SignatureTH1F_PU_h
#include <TH1F.h>
#include <string.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_PU : public SignatureTH1F {

public:
  SignatureTH1F_PU(const char* name, bool doWeight=false, const char* title = "S_{T} Distribution", int nbins = 100, double xmin = -0.5, double xmax = 99.5):SignatureTH1F(name,title,nbins,xmin,xmax),m_doWeight(doWeight){}

	SignatureTH1F_PU(TH1F h):SignatureTH1F(h) {/**/}
	SignatureTH1F_PU():SignatureTH1F() {/**/}

	Int_t Fill(BaseHandler*);

 private:
	bool m_doWeight;

	ClassDef(SignatureTH1F_PU,1);
};

inline Int_t SignatureTH1F_PU::Fill(BaseHandler* handler)
{
  return TH1F::Fill(handler->getPU(),m_doWeight ? handler->getPhysicsWeight(): 1.0);	
}

#endif
