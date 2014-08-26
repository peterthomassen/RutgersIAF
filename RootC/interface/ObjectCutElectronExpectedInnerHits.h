#ifndef ObjectCutElectronExpectedInnerHits_h
#define ObjectCutElectronExpectedInnerHits_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCut.h"
#include "RutgersIAF/RootC/interface/SignatureObjectElectron.h"

class ObjectCutElectronExpectedInnerHits : public ObjectCut {
 public:
  ObjectCutElectronExpectedInnerHits(int nExpectedInnerHitsmax = 1,const char* name="electronExpectedInnerHitscut" ) : ObjectCut(name),m_nExpectedInnerHitsmax(nExpectedInnerHitsmax){ /*no-op*/}
    //ObjectCutElectronExpectedInnerHits(int nExpectedInnerHitsmax = 1) : ObjectCutElectronExpectedInnerHits("electronExpectedInnerHitscut",nExpectedInnerHitsmax) { /* no-op */ }
    
  virtual ~ObjectCutElectronExpectedInnerHits(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if( m_nExpectedInnerHitsmax > 0 && sigObj->getNumberOfExpectedInnerHits() > m_nExpectedInnerHitsmax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  int m_nExpectedInnerHitsmax;

  ClassDef(ObjectCutElectronExpectedInnerHits,1);

};

inline bool ObjectCutElectronExpectedInnerHits::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
