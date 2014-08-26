#ifndef ObjectCutJetBDiscNegative_h
#define ObjectCutJetBDiscNegative_h

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

class ObjectCutJetBDiscNegative : public ObjectCut {
 public:
  ObjectCutJetBDiscNegative(int whichdisc=2,float mincutdisc=0.679, float maxcutdisc=999.0,const char* name="bdisccut") : ObjectCut(name),m_whichBDisc(whichdisc),m_minCutBDisc(mincutdisc),m_maxCutBDisc(maxcutdisc){ /*no-op*/}
    //ObjectCutJetBDiscNegative(bool isPromptTight=true) : ObjectCutJetBDiscNegative("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutJetBDiscNegative(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectJet*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectJet*) sigObj); }
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_whichBDisc >= 4)return false;
    if(sigObj->getBDiscPositiveAt(m_whichBDisc) < m_minCutBDisc)return false;
    if(sigObj->getBDiscPositiveAt(m_whichBDisc) > m_maxCutBDisc)return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;

 private:
  int m_whichBDisc;
  float m_minCutBDisc;
  float m_maxCutBDisc;

  ClassDef(ObjectCutJetBDiscNegative,1);

};

inline bool ObjectCutJetBDiscNegative::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
#endif
