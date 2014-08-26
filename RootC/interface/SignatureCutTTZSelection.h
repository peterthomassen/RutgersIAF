#ifndef SignatureCutTTZSelection_h
#define SignatureCutTTZSelection_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <algorithm>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureObject.h"
#include "RutgersIAF/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureCutTTZSelection : public SignatureCut {
 public:
  SignatureCutTTZSelection(double ZmassCutLow = 75, double ZmassCutHigh=105, bool removeLowM = true, double lowMassCut = 12, const char* name="sigcutttzselection") : SignatureCut(name),m_ZMassCutOffLow(ZmassCutLow), m_ZMassCutOffHigh(ZmassCutHigh),m_removeLowM(removeLowM),m_lowMassCutOff(lowMassCut){ /* no-op */}
    //SignatureCutTTZSelection(double dypairlow = 0, double dypairhigh=-1):SignatureCutTTZSelection("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
  virtual ~SignatureCutTTZSelection(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const;
  virtual bool operator()(BaseHandler*) const;

 private:
  double m_ZMassCutOffLow;
  double m_ZMassCutOffHigh;
  bool m_removeLowM;
  double m_lowMassCutOff;

  ClassDef(SignatureCutTTZSelection,1);

};

inline bool SignatureCutTTZSelection::operator()(BaseHandler* handler) const
{
  return passCut(handler);
}
#endif
