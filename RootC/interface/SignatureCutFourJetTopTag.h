#ifndef SignatureCutFourJetTopTag_h
#define SignatureCutFourJetTopTag_h

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
#include "RutgersIAF/RootC/interface/SignatureObjectJet.h"
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureCutFourJetTopTag : public SignatureCut {
 public:
  SignatureCutFourJetTopTag(const char* pname, double chi2cut=50, double refMass=80.4, const char* name="sigcut4jettoptags") : SignatureCut(name),m_chi2cut(chi2cut), m_refMass(refMass){ m_product  = pname;}
    //SignatureCutFourJetTopTag(double dypairlow = 0, double dypairhigh=-1):SignatureCutFourJetTopTag("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
  virtual ~SignatureCutFourJetTopTag(){ /* no-op */ }

  virtual bool passCut(BaseHandler* handler) const;
  virtual bool operator()(BaseHandler*) const;

 private:
  TString m_product;
  double m_chi2cut;
  double m_refMass;

  ClassDef(SignatureCutFourJetTopTag,1);

};

inline bool SignatureCutFourJetTopTag::operator()(BaseHandler* handler) const
{
  return passCut(handler);
}
#endif
