#ifndef ObjectCutElectronMissingHits_h
#define ObjectCutElectronMissingHits_h

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

class ObjectCutElectronMissingHits : public ObjectCut {
 public:
  ObjectCutElectronMissingHits(int nMissingHitsmax = 1,const char* name="electronMissingHitscut" ) : ObjectCut(name),m_nMissingHitsmax(nMissingHitsmax){ /*no-op*/}
    //ObjectCutElectronMissingHits(int nMissingHitsmax = 1) : ObjectCutElectronMissingHits("electronMissingHitscut",nMissingHitsmax) { /* no-op */ }
    
  virtual ~ObjectCutElectronMissingHits(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if( m_nMissingHitsmax >= 0 && sigObj->getNumberOfExpectedInnerHits() > m_nMissingHitsmax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  int m_nMissingHitsmax;

  ClassDef(ObjectCutElectronMissingHits,1);

};

inline bool ObjectCutElectronMissingHits::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
