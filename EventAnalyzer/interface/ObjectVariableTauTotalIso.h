#ifndef ObjectVariableTauTotalIso_h
#define ObjectVariableTauTotalIso_h

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

class ObjectVariableTauTotalIso : public ObjectVariable {
 public:
  ObjectVariableTauTotalIso(TString name):ObjectVariable(name){}
  virtual ~ObjectVariableTauTotalIso() {}

  virtual bool calculate(SignatureObject*);

 private:


  ClassDef(ObjectVariableTauTotalIso,1);

};

#endif
