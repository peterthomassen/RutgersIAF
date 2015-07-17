#ifndef ObjectVariableDeltaBetaCorrectedTotalIso_h
#define ObjectVariableDeltaBetaCorrectedTotalIso_h

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

class ObjectVariableDeltaBetaCorrectedTotalIso : public ObjectVariable {
 public:
  ObjectVariableDeltaBetaCorrectedTotalIso(TString charged, TString neutral, TString photon, TString beta, TString name="TOTALISO",TString flagname=""):ObjectVariable(name),m_chargedHadronName(charged),m_neutralHadronName(neutral),m_photonName(photon),m_betaName(beta),m_flagName(flagname){}
  virtual ~ObjectVariableDeltaBetaCorrectedTotalIso() {}

  virtual bool calculate(SignatureObject*);

 private:
  TString m_chargedHadronName;
  TString m_neutralHadronName;
  TString m_photonName;
  TString m_betaName;
  TString m_flagName;

  ClassDef(ObjectVariableDeltaBetaCorrectedTotalIso,1);

};

#endif
