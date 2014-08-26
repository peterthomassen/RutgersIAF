#ifndef ObjectCutElectronIsConversion_h
#define ObjectCutElectronIsConversion_h

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

class ObjectCutElectronIsConversion : public ObjectCut {
 public:
  ObjectCutElectronIsConversion(bool isConversion=false,const char* name="electronIsConversioncut" ) : ObjectCut(name),m_isConversion(isConversion){ /*no-op*/}
    //ObjectCutElectronIsConversion(double conversionDistancemax = 0.02 ) : ObjectCutElectronIsConversion("electronIsConversioncut",converstionDistancemax) { /* no-op */ }
    
  virtual ~ObjectCutElectronIsConversion(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(m_isConversion != (bool)sigObj->getIsConversion())return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  bool m_isConversion;

  ClassDef(ObjectCutElectronIsConversion,1);

};

inline bool ObjectCutElectronIsConversion::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
