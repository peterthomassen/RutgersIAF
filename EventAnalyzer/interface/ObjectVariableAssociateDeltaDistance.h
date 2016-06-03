#ifndef ObjectVariableAssociateDeltaDistance_h
#define ObjectVariableAssociateDeltaDistance_h

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

class ObjectVariableAssociateDeltaDistance : public ObjectVariable {
 public:
 ObjectVariableAssociateDeltaDistance(TString associate, TString vxName="vx", TString vyName="vy", TString vzName="vz",TString name="variablevaluecut") : ObjectVariable(name),m_associate(associate),m_vxName(vxName),m_vyName(vyName),m_vzName(vzName){ /*no-op*/}
    
  virtual ~ObjectVariableAssociateDeltaDistance(){}

  bool calculate(SignatureObject* sigObj)
  {
    SignatureObject* assoc = sigObj->getAssociate(m_associate);
    if(!assoc)return false;
    double this_vx=0,this_vy=0,this_vz=0;
    double that_vx=0,that_vy=0,that_vz=0;
    bool isSet_thisvx = sigObj->getVariable(m_vxName,this_vx);
    bool isSet_thisvy = sigObj->getVariable(m_vyName,this_vy);
    bool isSet_thisvz = sigObj->getVariable(m_vzName,this_vz);
    bool isSet_thatvx = assoc->getVariable(m_vxName,that_vx);
    bool isSet_thatvy = assoc->getVariable(m_vyName,that_vy);
    bool isSet_thatvz = assoc->getVariable(m_vzName,that_vz);
    if(!isSet_thisvx || !isSet_thisvy || !isSet_thisvz || !isSet_thatvx || !isSet_thatvy || !isSet_thatvz)return false;
    double deltaD = sqrt(pow(this_vx-that_vx,2)+pow(this_vy-that_vy,2)+pow(this_vz-that_vz,2));
    double deltaR = sqrt(pow(this_vx-that_vx,2)+pow(this_vy-that_vy,2));
    double deltaZ = this_vz-that_vz;
    sigObj->setVariable(getName(),deltaD);
    sigObj->setVariable(TString::Format("%s_RHO",getName().Data()),deltaR);
    sigObj->setVariable(TString::Format("%s_Z",getName().Data()),deltaZ);
    return true;
  }

 private:
  TString m_associate;
  TString m_vxName;
  TString m_vyName;
  TString m_vzName;

  ClassDef(ObjectVariableAssociateDeltaDistance,1);

};


#endif
