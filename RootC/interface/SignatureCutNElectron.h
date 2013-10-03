#ifndef SignatureCutNElectron_h
#define SignatureCutNElectron_h

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

class SignatureCutNElectron : public SignatureCutN {
 public:
  SignatureCutNElectron(double nelectronlow = 0, double nelectronhigh=-1,const char* name="sigcutnelectron") : SignatureCutN("goodElectrons",nelectronlow,nelectronhigh,name){ /* no-op */}
    //SignatureCutNElectron(double nelectronlow = 0, double nelectronhigh=-1):SignatureCutNElectron("sigcutnelectron",nelectronlow,nelectronhigh) { /*no-op */ }
  virtual ~SignatureCutNElectron(){ /* no-op */ }


 private:

  ClassDef(SignatureCutNElectron,1);

};
#endif
