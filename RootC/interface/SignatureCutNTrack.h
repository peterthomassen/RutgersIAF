#ifndef SignatureCutNTrack_h
#define SignatureCutNTrack_h

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

class SignatureCutNTrack : public SignatureCutN {
 public:
  SignatureCutNTrack(double ntracklow = 0, double ntrackhigh=-1,const char* name="sigcutntrack") : SignatureCutN("goodIsoTracks",ntracklow,ntrackhigh,name){ /* no-op */}
    //SignatureCutNTrack(double ntracklow = 0, double ntrackhigh=-1):SignatureCutNTrack("sigcutntrack",ntracklow,ntrackhigh) { /*no-op */ }
  virtual ~SignatureCutNTrack(){ /* no-op */ }

 private:

  ClassDef(SignatureCutNTrack,1);

};

#endif
