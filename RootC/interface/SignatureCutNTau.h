#ifndef SignatureCutNTau_h
#define SignatureCutNTau_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureCutN.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureCutNTau : public SignatureCutN {
 public:
  SignatureCutNTau(double ntaulow = 0, double ntauhigh=-1,const char* name="sigcutntau") : SignatureCutN("goodTaus",ntaulow,ntauhigh,name){/* no-op */}
    //SignatureCutNTau(double taulow = 0, double tauhigh=-1):SignatureCutNTau("sigcutntau",ntaulow,ntauhigh) { /*no-op */ }
  virtual ~SignatureCutNTau(){ /* no-op */ }

  //int getN(BaseHandler* handler) const;

 private:

  ClassDef(SignatureCutNTau,1);

};

#endif
