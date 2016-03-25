#ifndef ObjectVariableConeCorrectedPt_h
#define ObjectVariableConeCorrectedPt_h

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

class ObjectVariableConeCorrectedPt : public ObjectVariableEffectiveArea {
 public:
 ObjectVariableConeCorrectedPt(TString ptName, TString miniIsoName, TString ptRatioName, TString ptRelName, double miniIsoVal, double ptRatioVal, double ptRelVal,TString name="conecorrectedPt"):ObjectVariableEffectiveArea(name),m_ptName(ptName),m_miniIsoName(miniIsoName),m_ptRatioName(ptRatioName),m_ptRelName(ptRelName),m_miniIsoVal(miniIsoVal),m_ptRatioVal(ptRatioVal),m_ptRelVal(ptRelVal){}
  virtual ~ObjectVariableConeCorrectedPt() {}

  virtual bool calculate(SignatureObject*);

 private:
  TString m_ptName;
  TString m_miniIsoName;
  TString m_ptRatioName;
  TString m_ptRelName;
  double m_miniIsoVal;
  double m_ptRatioVal;
  double m_ptRelVal;

  ClassDef(ObjectVariableConeCorrectedPt,1);

};

#endif
