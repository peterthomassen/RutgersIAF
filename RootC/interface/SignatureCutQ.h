#ifndef SignatureCutQ_h
#define SignatureCutQ_h

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
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class SignatureCutQ : public SignatureCut {
 public:
   SignatureCutQ(TString product, double nlow = -9999, double nhigh=9999,const char* name="sigcutq") : SignatureCut(name),m_nlow(nlow),m_nhigh(nhigh){ m_products.push_back(product);}
  virtual ~SignatureCutQ(){ /* no-op */ }

  virtual double getQ(BaseHandler* handler) const;
  virtual bool passCut(BaseHandler* handler) const 
  {
    double n = getQ(handler);
    if(n < m_nlow) return false;
    if(n > m_nhigh) return false;
    return true;
  }
  virtual bool operator()(BaseHandler*) const;

  void addProduct(TString product) {m_products.push_back(product);}
  std::vector<TString> getProducts() {return m_products;}

private:
  double m_nlow;
  double m_nhigh;
  
  std::vector<TString> m_products;

  ClassDef(SignatureCutQ,1);

};

inline bool SignatureCutQ::operator()(BaseHandler* handler)const
{
  return passCut(handler);
}

inline double SignatureCutQ::getQ(BaseHandler* handler)const
{
  double dummy = 0;
  for(std::vector<TString>::const_iterator it = m_products.begin(); it < m_products.end(); it++)
  {
      std::vector<SignatureObject*> v = handler->getProduct((*it));
      for(std::vector<SignatureObject*>::iterator it2 = v.begin(); it2 < v.end(); it2++)
      {
         SignatureObjectRecoTrack * so = dynamic_cast<SignatureObjectRecoTrack*>(*it2);
	 SignatureObjectMCPart * mcso = dynamic_cast<SignatureObjectMCPart*> (*it2);
         if (so == NULL && mcso == NULL) break;
      
         if (so != NULL )dummy += so->getCharge();
	 else if(mcso != NULL)dummy += mcso->getCharge();
      }
  }
  return dummy;
}



#endif
