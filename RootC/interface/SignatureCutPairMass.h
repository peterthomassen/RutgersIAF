#ifndef SignatureCutPairMass_h
#define SignatureCutPairMass_h

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

class SignatureCutPairMass : public SignatureCut {
 public:
  SignatureCutPairMass(const char* pname, double ZmassCutLow = 75, double ZmassCutHigh=105,bool acceptInRange = true, int chargeMode=0, int mixMode=0, const char* name="sigcutpairmass") : SignatureCut(name),m_massCutLow(ZmassCutLow), m_massCutHigh(ZmassCutHigh),m_acceptInRange(acceptInRange),m_chargeMode(chargeMode),m_mixMode(mixMode){ m_products.push_back(pname);}
    //SignatureCutPairMass(double dypairlow = 0, double dypairhigh=-1):SignatureCutPairMass("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
  virtual ~SignatureCutPairMass(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const;
  virtual bool operator()(BaseHandler*) const;
  void addProduct(TString c);

 private:
  std::vector<TString> m_products;
  double m_massCutLow;
  double m_massCutHigh;
  bool m_acceptInRange;
  int m_chargeMode;
  int m_mixMode;

  ClassDef(SignatureCutPairMass,1);

};

inline bool SignatureCutPairMass::operator()(BaseHandler* handler) const
{
  return passCut(handler);
}
#endif
