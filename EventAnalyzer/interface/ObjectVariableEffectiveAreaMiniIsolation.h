#ifndef ObjectVariableEffectiveAreaMiniIsolation_h
#define ObjectVariableEffectiveAreaMiniIsolation_h

#include <string>
#include <iostream>
#include <sstream>
#include <TObject.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableEffectiveArea.h"

class SignatureObject;

class ObjectVariableEffectiveAreaMiniIsolation : public ObjectVariableEffectiveArea {
 public:
 ObjectVariableEffectiveAreaMiniIsolation(TString coneName,double scale, double power,TString name):ObjectVariableEffectiveArea(name),m_coneName(coneName),m_scale(scale),m_power(power){}
  virtual ~ObjectVariableEffectiveAreaMiniIsolation() {}

  virtual bool calculate(SignatureObject*);

 private:
  TString m_coneName;
  double m_scale;
  double m_power;

  ClassDef(ObjectVariableEffectiveAreaMiniIsolation,1);

};

#endif
