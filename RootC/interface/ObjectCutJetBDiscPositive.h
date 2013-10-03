#ifndef ObjectCutJetBDiscPositive_h
#define ObjectCutJetBDiscPositive_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"

class ObjectCutJetBDiscPositive : public ObjectCut {
 public:
  ObjectCutJetBDiscPositive(int whichdisc=10,float mincutdisc=0.679, float maxcutdisc=999.0,const char* name="bdisccut") : ObjectCut(name),m_whichBDisc(whichdisc),m_minCutBDisc(mincutdisc),m_maxCutBDisc(maxcutdisc){ /*no-op*/}
    //ObjectCutJetBDiscPositive(bool isPromptTight=true) : ObjectCutJetBDiscPositive("trackermuoncut",isPromptTight){ /* no-op */ }
    
  virtual ~ObjectCutJetBDiscPositive(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectJet*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectJet*) sigObj); }
  bool passCut(SignatureObjectJet* sigObj) const
  {
    if(m_whichBDisc >= 50)return false;
    if(sigObj->getBDiscPositiveAt(m_whichBDisc) < m_minCutBDisc)return false;
    if(sigObj->getBDiscPositiveAt(m_whichBDisc) > m_maxCutBDisc)return false;
    return true;
  }
  bool operator()(SignatureObjectJet*) const;

 private:
  int m_whichBDisc;
  float m_minCutBDisc;
  float m_maxCutBDisc;

  ClassDef(ObjectCutJetBDiscPositive,1);

};

inline bool ObjectCutJetBDiscPositive::operator()(SignatureObjectJet* sigobj) const
{
  return passCut(sigobj);
}
#endif
