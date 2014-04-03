#ifndef SignatureTH1F_N_h
#define SignatureTH1F_N_h

#include <TH1F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F.h"

class SignatureTH1F_N : public SignatureTH1F {
public:
  
  SignatureTH1F_N(const char* name, const char * productname, const char* title = "N Distribution", int nbins = 20, double xmin = -0.5, double xmax = 19.5):SignatureTH1F(name,title,nbins,xmin,xmax){m_productnames.push_back(productname);}
    
    SignatureTH1F_N(TH1F h):SignatureTH1F(h) {}
    SignatureTH1F_N():SignatureTH1F() {}
	
	using TH1F::Fill;
    Int_t Fill(BaseHandler*);

    void addProduct(TString);

    ClassDef(SignatureTH1F_N,1);

 protected:
    std::vector<TString> m_productnames;
};

inline Int_t SignatureTH1F_N::Fill(BaseHandler* handler)
{
   int count = 0;
   for(int i = 0; i < (int)m_productnames.size(); i++){
     std::vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
     count += (int)v.size();
   }
   
   return TH1F::Fill(count,handler->getPhysicsWeight());
}

inline void SignatureTH1F_N::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}
#endif
