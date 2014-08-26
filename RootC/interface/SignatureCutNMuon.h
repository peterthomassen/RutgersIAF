#ifndef SignatureCutNMuon_h
#define SignatureCutNMuon_h

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

class SignatureCutNMuon : public SignatureCutN {
 public:
  SignatureCutNMuon(double nmuonlow = 0, double nmuonhigh=-1,const char* name="sigcutnmuon") : SignatureCutN("goodMuons",nmuonlow,nmuonhigh,name){ /* no-op */}
    //SignatureCutNMuon(double muonlow = 0, double muonhigh=-1):SignatureCutNMuon("sigcutnmuon",nmuonlow,nmuonhigh) { /*no-op */ }
  virtual ~SignatureCutNMuon(){ /* no-op */ }

 private:

  ClassDef(SignatureCutNMuon,1);

};

#endif
