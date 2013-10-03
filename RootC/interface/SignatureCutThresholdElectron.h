#ifndef SignatureCutThresholdElectron_h
#define SignatureCutThresholdElectron_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <algorithm>
#include <map>
#include "RutgersIAF2012/RootC/interface/SignatureCutThreshold.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"

class SignatureCutThresholdElectron : public SignatureCutThreshold {
 public:
  SignatureCutThresholdElectron(const char* name="sigcutthreshElectron") : SignatureCutThreshold("goodElectrons",name){ /* no-op */}
    //SignatureCutThreshold(double nlow = 0, double nhigh=-1):SignatureCutThreshold("sigcutn",nlow,nhigh) { /*no-op */ }
  virtual ~SignatureCutThresholdElectron(){ /* no-op */ }


 private:

  ClassDef(SignatureCutThresholdElectron,1);

};
#endif
