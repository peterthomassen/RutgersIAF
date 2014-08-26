#ifndef SignatureCutThresholdMuon_h
#define SignatureCutThresholdMuon_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <algorithm>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureCutThreshold.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"

class SignatureCutThresholdMuon : public SignatureCutThreshold {
 public:
  SignatureCutThresholdMuon(const char* name="sigcutthreshMuon") : SignatureCutThreshold("goodMuons",name){ /* no-op */}
    //SignatureCutThreshold(double nlow = 0, double nhigh=-1):SignatureCutThreshold("sigcutn",nlow,nhigh) { /*no-op */ }
  virtual ~SignatureCutThresholdMuon(){ /* no-op */ }

 private:

  ClassDef(SignatureCutThresholdMuon,1);

};
#endif
