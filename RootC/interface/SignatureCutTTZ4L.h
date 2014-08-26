#ifndef SignatureCutTTZ4L_h
#define SignatureCutTTZ4L_h

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

class SignatureCutTTZ4L : public SignatureCut {
 public:
  SignatureCutTTZ4L(TString product = "goodElectrons",double ZmassCutLow = 75, double ZmassCutHigh=105, const char* name="sigcutttzselection") : SignatureCut(name),m_ZMassCutOffLow(ZmassCutLow), m_ZMassCutOffHigh(ZmassCutHigh){ m_products.push_back(product);}
    //SignatureCutTTZ4L(double dypairlow = 0, double dypairhigh=-1):SignatureCutTTZ4L("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
  virtual ~SignatureCutTTZ4L(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const;
  virtual bool operator()(BaseHandler*) const;

  void addProduct(TString);

 private:
  double m_ZMassCutOffLow;
  double m_ZMassCutOffHigh;

  std::vector<TString> m_products;

  ClassDef(SignatureCutTTZ4L,1);

};

inline bool SignatureCutTTZ4L::operator()(BaseHandler* handler) const
{
  return passCut(handler);
}
#endif
