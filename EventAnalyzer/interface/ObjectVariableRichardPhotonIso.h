#ifndef ObjectVariableRichardPhotonIso_h
#define ObjectVariableRichardPhotonIso_h

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

class ObjectVariableRichardPhotonIso : public ObjectVariable {
 public:
  ObjectVariableRichardPhotonIso(TString name, TString totalname1, TString totalname2):ObjectVariable(name),m_totalisoname1(totalname1),m_totalisoname2(totalname2){}
  virtual ~ObjectVariableRichardPhotonIso() {}

  virtual bool calculate(SignatureObject* sigObj)
  {
    double value1;
    bool isSet1 = sigObj->getVariable(m_totalisoname1,value1);
    if(!isSet1)return false;
    double value2;
    bool isSet2 = sigObj->getVariable(m_totalisoname2,value2);
    if(!isSet2)return false;
    sigObj->setVariable(getName(),(value1+value2)/sigObj->Pt());
    return true;
  }

 private:
  TString m_totalisoname1;
  TString m_totalisoname2;

  ClassDef(ObjectVariableRichardPhotonIso,1);

};

#endif
