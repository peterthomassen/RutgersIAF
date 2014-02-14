#ifndef SignatureTH2F_H
#define SignatureTH2F_H

#include <TH2F.h>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"

class SignatureTH2F : public TH2F  {
   public:

      SignatureTH2F(const char* name, const char* title, Int_t nbinsx, Double_t xmin, Double_t xmax, Int_t nbinsy, Double_t ymin, Double_t ymax):TH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax) {}

      SignatureTH2F(TH2F h):TH2F(h) {}

      SignatureTH2F():TH2F(){/*no-op*/}

      virtual ~SignatureTH2F(){}

      using TH2F::Fill;
      virtual Int_t Fill(BaseHandler*) = 0;

   protected:

      ClassDef(SignatureTH2F,1);

};

//inline Int_t SignatureTH2F::Fill(BaseHandler * handler)
//{
//   return TH2F::Fill();
//}


#endif
