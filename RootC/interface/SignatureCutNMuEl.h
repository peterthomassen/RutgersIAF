#ifndef SignatureCutNMuEl_h
#define SignatureCutNMuEl_h

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

class SignatureCutNMuEl : public SignatureCutN {
 public:
  SignatureCutNMuEl(double nmuellow = 0, double nmuelhigh=-1,const char* name="sigcutnmuel") : SignatureCutN("goodMuons",nmuellow,nmuelhigh,name){ addProduct("goodElectrons");}
    //SignatureCutNMuel(double nmuellow = 0, double nmuelhigh=-1):SignatureCutNMuel("sigcutnmuel",nmuellow,nmuelhigh) { /*no-op */ }
  virtual ~SignatureCutNMuEl(){ /* no-op */ }

 private:

  ClassDef(SignatureCutNMuEl,1);

};

#endif
