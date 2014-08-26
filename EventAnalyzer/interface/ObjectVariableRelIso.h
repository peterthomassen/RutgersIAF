#ifndef ObjectVariableRelIso_h
#define ObjectVariableRelIso_h

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
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectVariableRelIso : public ObjectVariable {
 public:
  ObjectVariableRelIso(TString name, TString totalname="TOTALISO"):ObjectVariable(name),m_totalisoname(totalname){}
  virtual ~ObjectVariableRelIso() {}

  virtual bool calculate(SignatureObject* sigObj)
  {
    double value = 99*sigObj->Pt();
    bool isSet = sigObj->getVariable(m_totalisoname,value);
    if(!isSet)return false;
    sigObj->setVariable(getName(),value/sigObj->Pt());
    return true;
  }

 private:
  TString m_totalisoname;

  ClassDef(ObjectVariableRelIso,1);

};

#endif
