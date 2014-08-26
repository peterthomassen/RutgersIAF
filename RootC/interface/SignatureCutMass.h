#ifndef SignatureCutMass_h
#define SignatureCutMass_h

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
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureCutMass : public SignatureCut {
 public:
  SignatureCutMass(const char* pname, double ZmassCutLow = 75, double ZmassCutHigh=105,bool cutInRange = true, const char* name="sigcut3bodyZ") : SignatureCut(name),m_massCutLow(ZmassCutLow), m_massCutHigh(ZmassCutHigh),m_cutInRange(cutInRange){ m_products.push_back(pname);}
    //SignatureCutMass(double dypairlow = 0, double dypairhigh=-1):SignatureCutMass("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
  virtual ~SignatureCutMass(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const;
  virtual bool operator()(BaseHandler*) const;
  void addProduct(TString c);

 private:
  std::vector<TString> m_products;
  double m_massCutLow;
  double m_massCutHigh;
  bool m_cutInRange;

  ClassDef(SignatureCutMass,1);

};

inline bool SignatureCutMass::operator()(BaseHandler* handler) const
{
  return passCut(handler);
}
#endif
