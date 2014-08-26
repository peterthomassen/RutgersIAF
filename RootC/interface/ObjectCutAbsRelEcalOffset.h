#ifndef ObjectCutAbsRelEcalOffset_h
#define ObjectCutAbsRelEcalOffset_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include <algorithm>
#include "RutgersIAF/RootC/interface/ObjectCutAbsRel.h"
#include "RutgersIAF/RootC/interface/SignatureObjectWithIso.h"

class ObjectCutAbsRelEcalOffset : public ObjectCutAbsRel {
 public:
  ObjectCutAbsRelEcalOffset(double offset=1.0,double relmin=-1.0,double relmax=10.0, const char* name="absrelecaloffcut") : ObjectCutAbsRel(relmin,relmax,name),m_offset(offset){ /*no-op*/}
    //ObjectCutAbsRelEcalOffset(double irelmax=0.15) : ObjectCutAbsRelEcalOffset("irelcut",irelmax){ /* no-op */ }
    
  virtual ~ObjectCutAbsRelEcalOffset(){}

  double calcAbsRel(SignatureObjectWithIso* sigObj) const;

 protected:
  double m_offset;

  ClassDef(ObjectCutAbsRelEcalOffset,1);

};
inline double ObjectCutAbsRelEcalOffset::calcAbsRel(SignatureObjectWithIso* sigobj) const
{
  return fabs(std::max(0.0,sigobj->getEcaloIso() - m_offset) + sigobj->getHcaloIso() + sigobj->getTrackIso());
}

#endif
