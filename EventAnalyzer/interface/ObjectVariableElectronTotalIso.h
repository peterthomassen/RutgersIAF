#ifndef ObjectVariableElectronTotalIso_h
#define ObjectVariableElectronTotalIso_h

#include <string>
#include <iostream>
#include <sstream>
#include <TObject.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"

class SignatureObject;

class ObjectVariableElectronTotalIso : public ObjectVariable {
 public:
  ObjectVariableElectronTotalIso(TString name):ObjectVariable(name){}
  virtual ~ObjectVariableElectronTotalIso() {}

  virtual bool calculate(SignatureObject*);

 private:


  ClassDef(ObjectVariableElectronTotalIso,1);

};

#endif
