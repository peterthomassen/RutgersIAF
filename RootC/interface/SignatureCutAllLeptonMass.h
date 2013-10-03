#ifndef SignatureCutAllLeptonMass_h
#define SignatureCutAllLeptonMass_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <algorithm>
#include <map>
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"

class SignatureCutAllLeptonMass : public SignatureCut {
 public:
  SignatureCutAllLeptonMass(double ZmassCutLow = 75, double ZmassCutHigh=105,bool cutInRange = true, const char* name="sigcut3bodyZ") : SignatureCut(name),m_massCutLow(ZmassCutLow), m_massCutHigh(ZmassCutHigh),m_cutInRange(cutInRange){ /* no-op */}
    //SignatureCutAllLeptonMass(double dypairlow = 0, double dypairhigh=-1):SignatureCutAllLeptonMass("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
  virtual ~SignatureCutAllLeptonMass(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const;
  virtual bool operator()(BaseHandler*) const;

 private:
  double m_massCutLow;
  double m_massCutHigh;
  bool m_cutInRange;

  ClassDef(SignatureCutAllLeptonMass,1);

};

inline bool SignatureCutAllLeptonMass::operator()(BaseHandler* handler) const
{
  return passCut(handler);
}
#endif
