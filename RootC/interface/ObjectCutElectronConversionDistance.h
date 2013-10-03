#ifndef ObjectCutElectronConversionDistance_h
#define ObjectCutElectronConversionDistance_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"

class ObjectCutElectronConversionDistance : public ObjectCut {
 public:
  ObjectCutElectronConversionDistance(double conversionDistancemin = 0.02,double conversionDistancemax = -1.0,const char* name="electronConversionDistancecut" ) : ObjectCut(name),m_conversionDistancemin(conversionDistancemin),m_conversionDistancemax(conversionDistancemax){ /*no-op*/}
    //ObjectCutElectronConversionDistance(double conversionDistancemax = 0.02 ) : ObjectCutElectronConversionDistance("electronConversionDistancecut",converstionDistancemax) { /* no-op */ }
    
  virtual ~ObjectCutElectronConversionDistance(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if( m_conversionDistancemin > 0 && fabs(sigObj->getConversionDist()) < m_conversionDistancemin) return false;
    if( m_conversionDistancemax > 0 && fabs(sigObj->getConversionDist()) > m_conversionDistancemax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_conversionDistancemin;
  double m_conversionDistancemax;

  ClassDef(ObjectCutElectronConversionDistance,1);

};

inline bool ObjectCutElectronConversionDistance::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
