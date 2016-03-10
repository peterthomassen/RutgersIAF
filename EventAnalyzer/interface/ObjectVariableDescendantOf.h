#ifndef ObjectVariableDescendantOf_h
#define ObjectVariableDescendantOf_h

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
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

class SignatureObject;

class ObjectVariableDescendantOf : public ObjectVariable {
 public:
 ObjectVariableDescendantOf(TString pname, int value, BaseHandler* handler, TString variable="pdgId", TString motherIndexVariable="motherIndex", int maxSteps = 30, TString name="DescendantOf"):ObjectVariable(name),m_productname(pname),m_value(value),m_handler(handler),m_variable(variable),m_motherIndexVariable(motherIndexVariable),m_maxSteps(maxSteps){}
  virtual ~ObjectVariableDescendantOf() {}

  virtual bool calculate(SignatureObject*);

 private:
  TString m_productname;
  int m_value;
  BaseHandler* m_handler;
  TString m_variable;
  TString m_motherIndexVariable;
  int m_maxSteps;

  ClassDef(ObjectVariableDescendantOf,1);

};

#endif
