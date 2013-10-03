#ifndef SignatureCutTauZ_h
#define SignatureCutTauZ_h

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
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"

class SignatureCutTauZ : public SignatureCut {
 public:
  SignatureCutTauZ(double ZmassCutLow = 75, double ZmassCutHigh=105,bool acceptInRange = true, const char* name="tauZcut") : SignatureCut(name),m_massCutLow(ZmassCutLow), m_massCutHigh(ZmassCutHigh),m_acceptInRange(acceptInRange){
    m_tauProduct = "goodTaus";
    m_electronProduct = "goodElectrons";
    m_muonProduct = "goodMuons";
  }
    //SignatureCutTauZ(double dypairlow = 0, double dypairhigh=-1):SignatureCutTauZ("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
  virtual ~SignatureCutTauZ(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const;
  virtual bool operator()(BaseHandler*) const;
  void setTauProduct(TString c){m_tauProduct = c;}
  void setElectronProduct(TString c){m_electronProduct = c;}
  void setMuonProduct(TString c){m_muonProduct = c;}

 private:
  double m_massCutLow;
  double m_massCutHigh;
  bool m_acceptInRange;
  TString m_tauProduct;
  TString m_electronProduct;
  TString m_muonProduct;

  ClassDef(SignatureCutTauZ,1);

};

inline bool SignatureCutTauZ::operator()(BaseHandler* handler) const
{
  return passCut(handler);
}
#endif
