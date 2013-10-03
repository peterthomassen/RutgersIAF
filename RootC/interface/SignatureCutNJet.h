#ifndef SignatureCutNJet_h
#define SignatureCutNJet_h

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
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"

class SignatureCutNJet : public SignatureCutN {
 public:
  SignatureCutNJet(double njetlow = 0, double njethigh=-1,const char* name="sigcutnjet") : SignatureCutN("goodJets",njetlow,njethigh,name){ /* no-op */}
    //SignatureCutNJet(double njetlow = 0, double njethigh=-1):SignatureCutNJet("sigcutnjet",njetlow,njethigh) { /*no-op */ }
  virtual ~SignatureCutNJet(){ /* no-op */ }

 private:

  ClassDef(SignatureCutNJet,1);

};

#endif
