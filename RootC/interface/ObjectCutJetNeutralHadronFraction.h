#ifndef ObjectCutJetNeutralHadronFraction_h
#define ObjectCutJetNeutralHadronFraction_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectJet.h"

class ObjectCutJetNeutralHadronFraction : public ObjectCut {
 public:
  ObjectCutJetNeutralHadronFraction(float mincut=0.0, float maxcut=0.99,const char* name="neutralhadronfractioncut") : ObjectCut(name),m_minCut(mincut),m_maxCut(maxcut){ /*no-op*/}
    //ObjectCutJetNeutralHadronFraction(bool isPromptTight=true) : ObjectCutJetNeutralHadronFraction("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutJetNeutralHadronFraction(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectJet*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectJet*) sigObj); }
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_minCut > 0 && sigObj->getNeutralHadronFraction() < m_minCut)return false;
    if(m_maxCut > 0 && sigObj->getNeutralHadronFraction() > m_maxCut)return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;

 private:
  float m_minCut;
  float m_maxCut;

  ClassDef(ObjectCutJetNeutralHadronFraction,1);

};

inline bool ObjectCutJetNeutralHadronFraction::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
#endif
