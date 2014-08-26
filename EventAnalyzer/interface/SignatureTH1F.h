#ifndef SignatureTH1F_h
#define SignatureTH1F_h
#include <TH1F.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

class SignatureTH1F : public TH1F  {
 public:
  SignatureTH1F(const char* name, const char* title, int nbins, double xmin, double xmax);
  SignatureTH1F(TH1F h);
  SignatureTH1F():TH1F(){/*no-op*/}
  virtual ~SignatureTH1F(){/* no-op*/}
  using TH1F::Fill;
  virtual Int_t Fill(BaseHandler*) = 0;
  //virtual Int_t Fill(double);

 protected:

  ClassDef(SignatureTH1F,1);

};

inline SignatureTH1F::SignatureTH1F(const char* name, const char* title, int nbins, double xmin, double xmax):TH1F(name,title,nbins,xmin,xmax){
}


inline SignatureTH1F::SignatureTH1F(TH1F v):TH1F(v){
}
#endif
