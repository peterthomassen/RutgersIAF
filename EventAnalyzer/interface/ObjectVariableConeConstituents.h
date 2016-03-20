#ifndef ObjectVariableConeConstituents_h
#define ObjectVariableConeConstituents_h

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

class ObjectVariableConeConstituents : public ObjectVariable {
 public:
  ObjectVariableConeConstituents(double coneSize,
				  double coneVetoSize,
				  double minPt,
				  double maxEta,
				  BaseHandler* handler,
				  bool useMatchedPFJet,
				  TString multiplicityName="",
				  TString name="CONECONST"
				  ):
  ObjectVariable(name),
    m_coneSize(coneSize),
    m_coneVetoSize(coneVetoSize),
    m_minPt(minPt),
    m_maxEta(maxEta),
    m_handler(handler),
    m_useMatchedPFJet(useMatchedPFJet),
    m_multiplicityName(multiplicityName){}
  
  virtual ~ObjectVariableConeConstituents() {}
  
  virtual bool calculate(SignatureObject*);
  
 private:
  double       m_coneSize;
  double       m_coneVetoSize;
  double       m_minPt;
  double       m_maxEta;
  BaseHandler* m_handler;
  bool         m_useMatchedPFJet;
  TString      m_multiplicityName;
 
  ClassDef(ObjectVariableConeConstituents,1);

};

#endif
