#ifndef ObjectVariableAssociateRecoil_h
#define ObjectVariableAssociateRecoil_h

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

class ObjectVariableAssociateRecoil : public ObjectVariable {
 public:
  ObjectVariableAssociateRecoil(TString associate, TString name="variablevaluecut") : ObjectVariable(name),m_associate(associate){ /*no-op*/}
    
  virtual ~ObjectVariableAssociateRecoil(){}

  bool calculate(SignatureObject* sigObj)
  {
    SignatureObject* assoc = sigObj->getAssociate(m_associate);
    if(!assoc)return false;
    TVector3 product = ((TLorentzVector*)sigObj)->Vect();
    TVector3 associate = ((TLorentzVector*)assoc)->Vect();
    sigObj->setVariable(getName(),(associate - product*((product*associate)/(product*product))).Mag());
    return true;
  }

 private:
  TString m_associate;

  ClassDef(ObjectVariableAssociateRecoil,1);

};


#endif
