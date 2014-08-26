#ifndef SignatureCutNBjetTrack_h
#define SignatureCutNBjetTrack_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureCutN.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureObjectJet.h"

class SignatureCutNBjetTrack : public SignatureCutN{
 public:
  SignatureCutNBjetTrack(double nbjetlow = 0, double nbjethigh=-1, double trackcut = 0.0,const char* name="sigcutnbjet") : SignatureCutN("goodJets",nbjetlow,nbjethigh,name), m_trackcut(trackcut){ /* no-op */}
    //SignatureCutNBjetTrack(double nbjetlow = 0, double nbjethigh=-1, double trackcut = 0.0):SignatureCutNBjetTrack("sigcutnbjet",nbjetlow,nbjethigh,trackcut) { /*no-op */ }
  virtual ~SignatureCutNBjetTrack(){ /* no-op */ }

  int getN(BaseHandler*) const;

 private:
  double m_trackcut;

  ClassDef(SignatureCutNBjetTrack,1);

};

inline int SignatureCutNBjetTrack::getN(BaseHandler* handler) const
{
  int nbjets = 0;
  for(int i = 0; i < (int)m_products.size(); i++){
    std::vector<SignatureObject*> v = handler->getProduct(m_products[i]);
    for(int j = 0; j < (int)v.size(); j++){
      SignatureObjectJet* jet = dynamic_cast<SignatureObjectJet*>(v[j]);
      if(jet == NULL)break;
      if(jet->getBDiscriminator_trackCount() > m_trackcut)nbjets++;
    }
  }
  return nbjets;
}
#endif
