#ifndef SignatureCutNTauTrack_h
#define SignatureCutNTauTrack_h

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

class SignatureCutNTauTrack : public SignatureCutN {
 public:
  SignatureCutNTauTrack(double nmuellow = 0, double nmuelhigh=-1,const char* name="sigcutnmuel") : SignatureCutN("goodTaus",nmuellow,nmuelhigh,name){ addProduct("goodIsoTracks");}
    //SignatureCutNMuel(double nmuellow = 0, double nmuelhigh=-1):SignatureCutNMuel("sigcutnmuel",nmuellow,nmuelhigh) { /*no-op */ }
  virtual ~SignatureCutNTauTrack(){ /* no-op */ }

 private:

  ClassDef(SignatureCutNTauTrack,1);

};

#endif
