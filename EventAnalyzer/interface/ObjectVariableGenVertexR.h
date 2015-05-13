#ifndef ObjectVariableGenVertexR_h
#define ObjectVariableGenVertexR_h

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

class ObjectVariableGenVertexR : public ObjectVariable {
 public:
  ObjectVariableGenVertexR(TString name):ObjectVariable(name){}
  virtual ~ObjectVariableGenVertexR() {}

  virtual bool calculate(SignatureObject*);

 private:


  ClassDef(ObjectVariableGenVertexR,1);

};

#endif
