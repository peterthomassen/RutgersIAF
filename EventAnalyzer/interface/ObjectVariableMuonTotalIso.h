#ifndef ObjectVariableMuonTotalIso_h
#define ObjectVariableMuonTotalIso_h

#include <string>
#include <iostream>
#include <sstream>
#include <TObject.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariable.h"

class SignatureObject;

class ObjectVariableMuonTotalIso : public ObjectVariable {
 public:
  ObjectVariableMuonTotalIso(TString name):ObjectVariable(name){}
  virtual ~ObjectVariableMuonTotalIso() {}

  virtual bool calculate(SignatureObject*);

 private:


  ClassDef(ObjectVariableMuonTotalIso,1);

};

#endif
