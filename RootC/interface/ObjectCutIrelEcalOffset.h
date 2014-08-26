#ifndef ObjectCutIrelEcalOffset_h
#define ObjectCutIrelEcalOffset_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <algorithm>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/ObjectCutIrel.h"
#include "RutgersIAF/RootC/interface/SignatureObjectWithIso.h"

class ObjectCutIrelEcalOffset : public ObjectCutIrel {
 public:
  ObjectCutIrelEcalOffset(double offset=1.0,double irelmin=0.0,double irelmax=0.15, const char* name="irelecaloffsetcut") : ObjectCutIrel(irelmin,irelmax,name),m_offset(offset){ /*no-op*/}
    //ObjectCutIrelEcalOffset(double irelmax=0.15) : ObjectCutIrelEcalOffset("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutIrelEcalOffset(){}

  double calcIrel(SignatureObjectWithIso* sigObj) const;

 private:
  double m_offset;
  ClassDef(ObjectCutIrelEcalOffset,1);

};
inline double ObjectCutIrelEcalOffset::calcIrel(SignatureObjectWithIso* sigobj) const
{
  return (std::max(0.0,sigobj->getEcaloIso()-m_offset) + sigobj->getHcaloIso() + sigobj->getTrackIso())/sigobj->Pt();
}

#endif
