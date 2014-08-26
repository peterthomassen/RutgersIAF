#ifndef SignatureTH3F_H
#define SignatureTH3F_H

#include <TH3F.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

class SignatureTH3F : public TH3F  {
   public:

  SignatureTH3F(const char* name, const char* title, Int_t nbinsx, Double_t xmin, Double_t xmax, Int_t nbinsy, Double_t ymin, Double_t ymax, Int_t nbinsz, Double_t zmin, Double_t zmax):TH3F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax) {}

      SignatureTH3F(TH3F h):TH3F(h) {}

      SignatureTH3F():TH3F(){/*no-op*/}

      virtual ~SignatureTH3F(){}

      using TH3F::Fill;
      virtual Int_t Fill(BaseHandler*) = 0;

   protected:

      ClassDef(SignatureTH3F,1);

};

//inline Int_t SignatureTH3F::Fill(BaseHandler * handler)
//{
//   return TH3F::Fill();
//}


#endif
