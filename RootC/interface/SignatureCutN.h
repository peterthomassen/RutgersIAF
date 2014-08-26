#ifndef SignatureCutN_h
#define SignatureCutN_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"

class SignatureCutN : public SignatureCut {
 public:
  SignatureCutN(const char* productname, double nlow = 0, double nhigh=-1,const char* name="sigcutn") : SignatureCut(name),m_nlow(nlow),m_nhigh(nhigh){ m_products.push_back(productname);}
    //SignatureCutN(double nlow = 0, double nhigh=-1):SignatureCutN("sigcutn",nlow,nhigh) { /*no-op */ }
  virtual ~SignatureCutN(){ /* no-op */ }

  virtual int getN(BaseHandler* handler) const;
  virtual void addProduct(TString);
  virtual bool passCut(BaseHandler* handler) const 
  {
    int n = getN(handler);
    if(m_nlow >= 0 && n < m_nlow) return false;
    if(m_nhigh >= 0 && n > m_nhigh) return false;
    return true;
  }
  virtual bool operator()(BaseHandler*) const;

 protected:
  std::vector<TString> m_products;
 private:
  double m_nlow;
  double m_nhigh;

  ClassDef(SignatureCutN,1);

};

inline void SignatureCutN::addProduct(TString product)
{
  if(std::find(m_products.begin(),m_products.end(),product) == m_products.end())m_products.push_back(product);
}

inline bool SignatureCutN::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}

inline int SignatureCutN::getN(BaseHandler* handler) const
{
  int n = 0;
  for(int i = 0; i < (int)m_products.size(); i++){
    std::vector<SignatureObject*> v = handler->getProduct(m_products[i]);
    n += (int)v.size();
  }
  return n;
}
#endif
