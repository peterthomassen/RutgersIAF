#ifndef ObjectVariableAssociateDeltaR_h
#define ObjectVariableAssociateDeltaR_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class ObjectVariableAssociateDeltaR : public ObjectVariable {
 public:
  ObjectVariableAssociateDeltaR(TString associate, TString name="variablevaluecut") : ObjectVariable(name),m_associate(associate){ /*no-op*/}
    
  virtual ~ObjectVariableAssociateDeltaR(){}

  bool calculate(SignatureObject* sigObj)
  {
    SignatureObject* assoc = sigObj->getAssociate(m_associate);
    if(!assoc)return false;
    sigObj->setVariable(getName(),sigObj->DeltaR((*(TLorentzVector*)assoc)));
    return true;
  }

 private:
  TString m_associate;

  ClassDef(ObjectVariableAssociateDeltaR,1);

};


#endif
