#ifndef SignatureCutNPhoton_h
#define SignatureCutNPhoton_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/SignatureCutN.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"

class SignatureCutNPhoton : public SignatureCutN {
 public:
  SignatureCutNPhoton(double nphotonlow = 0, double nphotonhigh=-1,const char* name="sigcutnphoton") : SignatureCutN("goodPhotons",nphotonlow,nphotonhigh,name){ /* no-op */}
    //SignatureCutNPhoton(double photonlow = 0, double photonhigh=-1):SignatureCutNPhoton("sigcutnphoton",nphotonlow,nphotonhigh) { /*no-op */ }
  virtual ~SignatureCutNPhoton(){ /* no-op */ }

 private:

  ClassDef(SignatureCutNPhoton,1);

};

#endif
