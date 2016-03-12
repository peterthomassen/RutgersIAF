#ifndef ObjectVariableMotherOf_h
#define ObjectVariableMotherOf_h

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

class ObjectVariableMotherOf : public ObjectVariable {
 public:
 ObjectVariableMotherOf(TString pname, int value, BaseHandler* handler, int maxSteps = 30, TString name="MotherOf" ):
  ObjectVariable(name), m_productname(pname), m_value(value), m_handler(handler), m_maxSteps(maxSteps){}
  
  virtual ~ObjectVariableMotherOf() {}
  
  virtual bool calculate(SignatureObject*);
  
 private:
  TString      m_productname;
  int          m_value;
  BaseHandler* m_handler;
  int          m_maxSteps;
  
  ClassDef(ObjectVariableMotherOf,1);

};

#endif
