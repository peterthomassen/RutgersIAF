#ifndef ObjectCutMCPdgID_h
#define ObjectCutMCPdgID_h

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

class ObjectCutMCPdgID : public ObjectCut {
 public:
  ObjectCutMCPdgID(int pdgid, bool keepAntiParticles=false, const char* name="mcpdgidcut") : ObjectCut(name),m_pdgid(pdgid),m_keepAntiParticles(keepAntiParticles){ /*no-op*/}
    //ObjectCutMCPdgID(double etamax) : ObjectCutMCPdgID("etacut",etamax){ /* no-op */ }
    
  virtual ~ObjectCutMCPdgID(){}
  bool passCut(SignatureObject* sigObj) const {return passCut((SignatureObjectMCPart*)sigObj);}
  bool operator()(SignatureObject* sigObj) const {return passCut((SignatureObjectMCPart*)sigObj);}

  bool passCut(SignatureObjectMCPart* sigObj) const
  {
    if(!m_keepAntiParticles && sigObj->getPdgID() != m_pdgid) return false;
    if(fabs(sigObj->getPdgID()) != m_pdgid) return false;
    return true;
  }
  bool operator()(SignatureObjectMCPart*) const;

 private:
  double m_pdgid;
  bool m_keepAntiParticles;


  ClassDef(ObjectCutMCPdgID,1);

};

inline bool ObjectCutMCPdgID::operator()(SignatureObjectMCPart* sigobj) const
{
  return passCut(sigobj);
}
#endif
