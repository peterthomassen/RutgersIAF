#ifndef ObjectVariableAssociateAngles_h
#define ObjectVariableAssociateAngles_h

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

class ObjectVariableAssociateAngles : public ObjectVariable {
 public:
  ObjectVariableAssociateAngles(TString associate, TString name="variablevaluecut") : ObjectVariable(name),m_associate(associate){ /*no-op*/}
    
  virtual ~ObjectVariableAssociateAngles(){}

  bool calculate(SignatureObject* sigObj)
  {
    SignatureObject* assoc = sigObj->getAssociate(m_associate);
    if(!assoc)return false;
    sigObj->setVariable(TString::Format("%s_dPHI",getName().Data()),sigObj->DeltaPhi((*(TLorentzVector*)assoc)));
    sigObj->setVariable(TString::Format("%s_dETA",getName().Data()),sigObj->Eta() - assoc->Eta());
    sigObj->setVariable(TString::Format("%s_dANGLE",getName().Data()),sigObj->Angle(assoc->Vect()));
    return true;
  }

 private:
  TString m_associate;

  ClassDef(ObjectVariableAssociateAngles,1);

};


#endif
