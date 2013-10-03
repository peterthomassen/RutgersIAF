#ifndef SignatureCutThreshold_h
#define SignatureCutThreshold_h

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

class SignatureCutThreshold : public SignatureCut {
 public:
  SignatureCutThreshold(const char* productname="",const char* name="sigcutthresh") : SignatureCut(name),m_productname(productname){ /* no-op */}
    //SignatureCutThreshold(double nlow = 0, double nhigh=-1):SignatureCutThreshold("sigcutn",nlow,nhigh) { /*no-op */ }
  virtual ~SignatureCutThreshold(){ /* no-op */ }

  virtual std::vector<double> getETs(BaseHandler*) const;
  virtual void addThreshold(double c){m_thresholds.push_back(c);}
  virtual bool passCut(BaseHandler* handler) const 
  {
    std::vector<double> ets = getETs(handler);
    for(int i = 0; i < (int)m_thresholds.size(); i++){
      if(i >= (int)ets.size()) return false;
      if(m_thresholds[i] > 0 && ets[i] < m_thresholds[i])return false;
    }
    return true;
  }
  virtual bool operator()(BaseHandler*) const;

 private:
  TString m_productname;
  std::vector<double> m_thresholds;

  ClassDef(SignatureCutThreshold,1);

};
inline std::vector<double> SignatureCutThreshold::getETs(BaseHandler* handler) const
{
  std::vector<double> retval;
  std::vector<SignatureObject*> product = handler->getProduct(m_productname);
  for(int i = 0; i < (int)product.size(); i++)retval.push_back(product[i]->Pt());
  sort(retval.begin(),retval.end());
  reverse(retval.begin(),retval.end());
  return retval;
}

inline bool SignatureCutThreshold::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}
#endif
