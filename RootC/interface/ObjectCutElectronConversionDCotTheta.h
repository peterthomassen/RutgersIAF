#ifndef ObjectCutElectronConversionDCotTheta_h
#define ObjectCutElectronConversionDCotTheta_h

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

class ObjectCutElectronConversionDCotTheta : public ObjectCut {
 public:
  ObjectCutElectronConversionDCotTheta(double conversionDCotThetamin = 0.02, double conversionDCotThetamax = -1.0,const char* name="electronConversionDCotThetacut" ) : ObjectCut(name),m_conversionDCotThetamin(conversionDCotThetamin),m_conversionDCotThetamax(conversionDCotThetamax){ /*no-op*/}
    //ObjectCutElectronConversionDCotTheta(double conversionDCotThetamax = 0.02 ) : ObjectCutElectronConversionDCotTheta("electronConversionDCotThetacut",conversionDCotThetamax) { /* no-op */ }
    
  virtual ~ObjectCutElectronConversionDCotTheta(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if( m_conversionDCotThetamin > 0 && fabs(sigObj->getConversionDCotTheta()) < m_conversionDCotThetamin) return false;
    if( m_conversionDCotThetamax > 0 && fabs(sigObj->getConversionDCotTheta()) > m_conversionDCotThetamax) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_conversionDCotThetamin;
  double m_conversionDCotThetamax;

  ClassDef(ObjectCutElectronConversionDCotTheta,1);

};

inline bool ObjectCutElectronConversionDCotTheta::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
