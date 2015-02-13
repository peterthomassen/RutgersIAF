#ifndef ObjectVariableEffectiveArea_h
#define ObjectVariableEffectiveArea_h

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

class ObjectVariableEffectiveArea : public ObjectVariable {
 public:
  ObjectVariableEffectiveArea(TString name):ObjectVariable(name){}
  virtual ~ObjectVariableEffectiveArea() {}

  void addArea(double maxEta, double area);

  virtual bool calculate(SignatureObject*);

 private:
  std::map<double,double> m_eta_area_map;

  ClassDef(ObjectVariableEffectiveArea,1);

};

#endif
