#ifndef SignatureCutBDiscriminant_h
#define SignatureCutBDiscriminant_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"

class SignatureCutBDiscriminant : public SignatureCut {
 public:
  SignatureCutBDiscriminant(const char* productname="", const char* discType = "trackcount", const char* name="sigcutthresh") : SignatureCut(name),m_productname(productname),m_discType(discType){ m_discType.ToLower();}
    //SignatureCutBDiscriminant(double nlow = 0, double nhigh=-1):SignatureCutBDiscriminant("sigcutn",nlow,nhigh) { /*no-op */ }
  virtual ~SignatureCutBDiscriminant(){ /* no-op */ }

  virtual std::vector<double> getBDs(BaseHandler*) const;
  virtual void addThreshold(double c){m_thresholds.push_back(c);}
  virtual bool passCut(BaseHandler* handler) const 
  {
    std::vector<double> ets = getBDs(handler);
    for(int i = 0; i < (int)m_thresholds.size(); i++){
      if(i >= (int)ets.size()) return false;
      if(m_thresholds[i] > 0 && ets[i] < m_thresholds[i])return false;
    }
    return true;
  }
  virtual bool operator()(BaseHandler*) const;

 private:
  TString m_productname,m_discType;
  std::vector<double> m_thresholds;

  ClassDef(SignatureCutBDiscriminant,1);

};
inline std::vector<double> SignatureCutBDiscriminant::getBDs(BaseHandler* handler) const
{
  std::vector<double> retval;
  std::vector<SignatureObject*> product = handler->getProduct(m_productname);
  sort(product.begin(),product.end());
  reverse(product.begin(),product.end());
  for(int i = 0; i < (int)product.size(); i++){
    SignatureObjectJet* jet = dynamic_cast<SignatureObjectJet*>(product[i]);
    if(jet == NULL)break;
    if(m_discType == ""){
      retval.push_back(jet->getBDiscriminator());
    }else if(m_discType == "ssvertex"){
      retval.push_back(jet->getBDiscriminator_ssVertex());
    }else if(m_discType == "ssvertexpure"){
      retval.push_back(jet->getBDiscriminator_ssVertexPure());
    }else if(m_discType == "combined"){
      retval.push_back(jet->getBDiscriminator_combined());
    }else if(m_discType == "trackcount"){
      retval.push_back(jet->getBDiscriminator_trackCount());
    }else if(m_discType == "trackcountpure"){
      retval.push_back(jet->getBDiscriminator_trackCountPure());
    }
  }
  return retval;
}

inline bool SignatureCutBDiscriminant::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
