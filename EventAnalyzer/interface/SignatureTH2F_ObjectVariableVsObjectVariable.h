#ifndef SignatureTH2F_ObjectVariableVsObjectVariable_h
#define SignatureTH2F_ObjectVariableVsObjectVariable_h

#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include <TString.h>
#include <algorithm>

template <typename T1, typename T2>
class SignatureTH2F_ObjectVariableVsObjectVariable : public SignatureTH2F 
{
 public:
  SignatureTH2F_ObjectVariableVsObjectVariable(TString var1, TString var2, TString productname, const char* name, const char* title="", Int_t nbinsx=100,Double_t xmin=0,Double_t xmax=1000, Int_t nbinsy=100, Double_t ymin=0, Double_t ymax=1000):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax),m_var1(var1),m_var2(var2) {m_productnames.push_back(productname);}

  SignatureTH2F_ObjectVariableVsObjectVariable(TH2F h):SignatureTH2F(h){}
  SignatureTH2F_ObjectVariableVsObjectVariable():SignatureTH2F(){}

  void addProduct(TString pname){
    if(std::find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
  }

  using TH2F::Fill;
  Int_t Fill(BaseHandler* handler){
    int dummy = -1;
    for(int i = 0; i < (int)m_productnames.size(); i++){
      std::vector<SignatureObject*> v= handler->getProduct(m_productnames[i]);
      for(int j = 0; j < (int)v.size(); j++){
	T1 val1;
	T2 val2;
	if(!v[j]->getVariable(m_var2,val2) || !v[j]->getVariable(m_var1,val1)){
	  dummy = -1;
	}else{
	  dummy = TH2F::Fill(val1,val2,handler->getPhysicsWeight());
	}
      }
    }
    return dummy;
  }

 private:
  TString m_var1;
  TString m_var2;
  std::vector<TString> m_productnames;

  ClassDef(SignatureTH2F_ObjectVariableVsObjectVariable,1);
};
#endif
