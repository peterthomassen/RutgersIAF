#ifndef SignatureTH1F_N_h
#define SignatureTH1F_N_h

#include <TH1F.h>
#include <TString.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_N : public SignatureTH1F {

	public:

		SignatureTH1F_N(const char* name, const char * productname, const char * productname2 = "", const char* title = "N Distribution", int nbins = 20, double xmin = -0.5, double xmax = 19.5):SignatureTH1F(name,title,nbins,xmin,xmax){m_productname = productname; m_productname2 = productname2;}

		SignatureTH1F_N(TH1F h):SignatureTH1F(h) {}
		SignatureTH1F_N():SignatureTH1F() {}

		Int_t Fill(BaseHandler*);

		//virtual Int_t GetN(BaseHandler*) = 0;

		ClassDef(SignatureTH1F_N,1);

	protected:

		TString m_productname, m_productname2;
};

inline Int_t SignatureTH1F_N::Fill(BaseHandler* handler)
{
   std::vector<SignatureObject*> v = handler->getProduct(m_productname);
   
   Int_t dummy = v.size();

   if(!(m_productname2 == ""))
   {
      v = handler->getProduct(m_productname2);
      dummy += v.size();
   }
   
   return TH1F::Fill(dummy,handler->getPhysicsWeight());
}


#endif
