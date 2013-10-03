#ifndef SignatureTH2F_NvN_H
#define SignatureTH2F_NvN_H

#include <TH2F.h>
#include <TString.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"

class SignatureTH2F_NvN : public SignatureTH2F {
 public:
  SignatureTH2F_NvN(const char* name, const char * productnameX, const char* productnameY, const char* title = "N vs N Distribution", Int_t nbinseta = 50, Double_t etamin = -0.5, Double_t etamax = 49.5, Int_t nbinsphi = 50, Double_t phimin = -0.5, Double_t phimax = 49.5):SignatureTH2F(name,title,nbinseta,etamin,etamax,nbinsphi,phimin,phimax){m_productnameX = productnameX; m_productnameY = productnameY;}

	SignatureTH2F_NvN(TH2F h):SignatureTH2F(h) {}
	SignatureTH2F_NvN():SignatureTH2F() {}

	Int_t Fill(BaseHandler*);

	ClassDef(SignatureTH2F_NvN,1);

	protected:

		TString m_productnameX;
		TString m_productnameY;

};

inline Int_t SignatureTH2F_NvN::Fill(BaseHandler* handler)
{
	Int_t dummy = 0;

	std::vector<SignatureObject*> vx = handler->getProduct(m_productnameX);
	std::vector<SignatureObject*> vy = handler->getProduct(m_productnameY);
	
	dummy = TH2F::Fill(vx.size(),vy.size(),handler->getPhysicsWeight());

	return dummy;
}




#endif
