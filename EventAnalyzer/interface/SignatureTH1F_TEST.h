#ifndef SignatureTH1F_TEST_h
#define SignatureTH1F_TEST_h

#include <TH1F.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class SignatureTH1F_TEST : public SignatureTH1F {
public:
  
  SignatureTH1F_TEST(const char* name, TString varname, TString productname, const char* title = "N Distribution", int nbins = 20, double xmin = -0.5, double xmax = 19.5):SignatureTH1F(name,title,nbins,xmin,xmax),m_varname(varname){ m_productnames.push_back(productname);}
    
  SignatureTH1F_TEST(TH1F h):SignatureTH1F(h) {}
  SignatureTH1F_TEST():SignatureTH1F() {}
	
  void addProduct(TString pname)
  {
    if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
  }


  using TH1F::Fill;
  Int_t Fill(BaseHandler* handler)
  {
    Int_t dummy = -1;
    
    for(int i = 0; i < (int)m_productnames.size(); i++){
      std::vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
      for(int j = 0; j < (int)v.size(); j++){
	T value;
	bool isSet = v[i]->getVariable(m_varname,value);
	if(isSet) dummy = TH1F::Fill(value,handler->getPhysicsWeight());
      }
    }
    return dummy;
  }

  virtual void Copy(TObject& hnew) const
  {
    TH1F::Copy(hnew);
    ((SignatureTH1F_TEST<T>&)hnew).m_varname = m_varname;
    ((SignatureTH1F_TEST<T>&)hnew).m_productnames = m_productnames;
  }

  ClassDef(SignatureTH1F_TEST,1);

  TString m_varname;
  std::vector<TString> m_productnames;
};

#endif