#ifndef ObjectCutElectronVertexFitProbability_h
#define ObjectCutElectronVertexFitProbability_h

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
#include "RutgersIAF/RootC/interface/SignatureObjectPhoton.h"

class ObjectCutElectronVertexFitProbability : public ObjectCut {
 public:
  ObjectCutElectronVertexFitProbability(double barrelVtxProbMin = 1e-6, double endcapVtxProbMin=1e-6, double etaseparator=1.5,const char* name="electronVtcProbcut") : ObjectCut(name),m_barrelVtxProbMin(barrelVtxProbMin),m_endcapVtxProbMin(endcapVtxProbMin),m_etaseparator(etaseparator){ /*no-op*/}
    //ObjectCutElectronVertexFitProbability(double barrelVtxProbmax = 0.12, double endcapVtxProbMin=0.05, double etaseparator=1.5) : ObjectCutElectronVertexFitProbability("electronHoEcut",barrelVtxProbmax,endcapVtxProbMin,etaseparator){ /* no-op */ }

    
  virtual ~ObjectCutElectronVertexFitProbability(){}

  bool passCut(SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*)sigObj); }
  bool operator() (SignatureObject* sigObj) const { return passCut((SignatureObjectElectron*) sigObj); }
  bool passCut(SignatureObjectElectron* sigObj) const
  {
    if(fabs(sigObj->Eta()) < m_etaseparator && m_barrelVtxProbMin > 0 && sigObj->getHadOverEm() < m_barrelVtxProbMin) return false;
    if(fabs(sigObj->Eta()) > m_etaseparator && m_endcapVtxProbMin > 0 && sigObj->getHadOverEm() < m_endcapVtxProbMin) return false;
    return true;
  }
  bool operator()(SignatureObjectElectron*) const;

 private:
  double m_barrelVtxProbMin;
  double m_endcapVtxProbMin;
  double m_etaseparator;

  ClassDef(ObjectCutElectronVertexFitProbability,1);

};

inline bool ObjectCutElectronVertexFitProbability::operator()(SignatureObjectElectron* sigobj) const
{
  return passCut(sigobj);
}
#endif
