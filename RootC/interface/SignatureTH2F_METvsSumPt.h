#ifndef SignatureTH2F_METvsSumPt_H
#define SignatureTH2F_METvsSumPt_H

#include <TH2F.h>
#include <TString.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"

class SignatureTH2F_METvsSumPt : public SignatureTH2F {
 public:
  SignatureTH2F_METvsSumPt(const char* name, const char * productname, const char* title = "#phi vs #eta Distribution", Int_t nbinseta = 50, Double_t etamin = -3, Double_t etamax = 3, Int_t nbinsphi = 50, Double_t phimin = (-1.0 * TMath::Pi()), Double_t phimax = TMath::Pi()):SignatureTH2F(name,title,nbinseta,etamin,etamax,nbinsphi,phimin,phimax){m_productname = productname;}

    SignatureTH2F_METvsSumPt(TH2F h):SignatureTH2F(h) {}
    SignatureTH2F_METvsSumPt():SignatureTH2F() {}
	
    Int_t Fill(BaseHandler*);

    ClassDef(SignatureTH2F_METvsSumPt,1);

 protected:

    TString m_productname;

};

inline Int_t SignatureTH2F_METvsSumPt::Fill(BaseHandler* handler)
{
	Int_t dummy = 0;

	std::vector<SignatureObject*> v = handler->getProduct(m_productname);

	for(std::vector<SignatureObject*>::iterator it = v.begin(); it != v.end(); ++it)
	{
		dummy = TH2F::Fill((*it)->Eta(),(*it)->Phi(),handler->getPhysicsWeight());
	}

	return dummy;
}




#endif
