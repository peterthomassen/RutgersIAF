#ifndef ObjectCutMCMotherPdgID_h
#define ObjectCutMCMotherPdgID_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class ObjectCutMCMotherPdgID : public ObjectCut {
 public:
  ObjectCutMCMotherPdgID(int pdgid, bool keepAntiParticles=false, const char* name="mcmotherpdgidcut") : ObjectCut(name),m_pdgid(pdgid),m_keepAntiParticles(keepAntiParticles){ /*no-op*/}
    //ObjectCutMCMotherPdgID(double etamax) : ObjectCutMCMotherPdgID("etacut",etamax){ /* no-op */ }
    
  virtual ~ObjectCutMCMotherPdgID(){}
  bool passCut(SignatureObject* sigObj) const {return passCut((SignatureObjectMCPart*)sigObj);}
  bool operator()(SignatureObject* sigObj)const {return passCut((SignatureObjectMCPart*)sigObj);}

  bool passCut(SignatureObjectMCPart* sigObj) const
  {
    if(!m_keepAntiParticles && sigObj->getMother_pdgID() != m_pdgid) return false;
    if(fabs(sigObj->getMother_pdgID()) != m_pdgid) return false;
    return true;
  }
  bool operator()(SignatureObjectMCPart*) const;

 private:
  double m_pdgid;
  bool m_keepAntiParticles;


  ClassDef(ObjectCutMCMotherPdgID,1);

};

inline bool ObjectCutMCMotherPdgID::operator()(SignatureObjectMCPart* sigobj) const
{
  return passCut(sigobj);
}
#endif
