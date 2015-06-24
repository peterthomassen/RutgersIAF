#ifndef ObjectVariableRhoCorrectedTotalIso_h
#define ObjectVariableRhoCorrectedTotalIso_h

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

class ObjectVariableRhoCorrectedTotalIso : public ObjectVariable {
 public:
  ObjectVariableRhoCorrectedTotalIso(TString charged, TString neutral, TString photon, TString rho, TString area, TString name="TOTALISO",TString flagname=""):ObjectVariable(name),m_chargedHadronName(charged),m_neutralHadronName(neutral),m_photonName(photon),m_rhoName(rho),m_areaName(area),m_flagName(flagname){}
  virtual ~ObjectVariableRhoCorrectedTotalIso() {}

  virtual bool calculate(SignatureObject*);

 private:
  TString m_chargedHadronName;
  TString m_neutralHadronName;
  TString m_photonName;
  TString m_rhoName;
  TString m_areaName;
  TString m_flagName;

  ClassDef(ObjectVariableRhoCorrectedTotalIso,1);

};

#endif
