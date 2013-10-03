#ifndef SignatureTH1F_NVertex_h
#define SignatureTH1F_NVertex_h

#include <TH1F.h>
#include <TString.h>
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"

class SignatureTH1F_NVertex : public SignatureTH1F {

 public:
  
  SignatureTH1F_NVertex(const char* name, const char* title = "NVertex Distribution ; Number of Vertices", int nbins = 50, double xmin = -0.5, double xmax = 49.5):SignatureTH1F(name,title,nbins,xmin,xmax){ }
    
  SignatureTH1F_NVertex(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_NVertex():SignatureTH1F() {}
	
  Int_t Fill(BaseHandler*);

  //virtual Int_t GetN(BaseHandler*) = 0;

  ClassDef(SignatureTH1F_NVertex,1);
  
 protected:

};

inline Int_t SignatureTH1F_NVertex::Fill(BaseHandler* handler)
{
   std::vector<SignatureRecoVertex*> v = handler->getGoodRecoVertices();
   
   Int_t dummy = v.size();
   
   return TH1F::Fill(dummy,handler->getPhysicsWeight());
}


#endif
