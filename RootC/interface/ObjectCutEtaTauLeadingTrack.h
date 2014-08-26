#ifndef ObjectCutEtaTauLeadingTrack_h
#define ObjectCutEtaTauLeadingTrack_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectTau.h"

class ObjectCutEtaTauLeadingTrack : public ObjectCut {
 public:
  ObjectCutEtaTauLeadingTrack(double etamax=2.4, const char* name="etacut") : ObjectCut(name),m_etamax(etamax){ /*no-op*/}
    //ObjectCutEtaTauLeadingTrack(double etamax) : ObjectCutEtaTauLeadingTrack("etacut",etamax){ /* no-op */ }
    
  virtual ~ObjectCutEtaTauLeadingTrack(){}

  bool passCut(SignatureObject* sigObj)const {return passCut((SignatureObjectTau*)sigObj);}
  bool operator()(SignatureObject* sigObj)const {return passCut((SignatureObjectTau*)sigObj);}
  bool passCut(SignatureObjectTau* sigObj) const
  {
    if(fabs(sigObj->Eta()) > m_etamax) return false;
    return true;
  }
  bool operator()(SignatureObjectTau*) const;

 private:
  double m_etamax;


  ClassDef(ObjectCutEtaTauLeadingTrack,1);

};

inline bool ObjectCutEtaTauLeadingTrack::operator()(SignatureObjectTau* sigobj) const
{
  return passCut(sigobj);
}
#endif
