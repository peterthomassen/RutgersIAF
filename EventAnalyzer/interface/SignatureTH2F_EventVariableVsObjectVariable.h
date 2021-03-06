#ifndef SignatureTH2F_EventVariableVsObjectVariable_h
#define SignatureTH2F_EventVariableVsObjectVariable_h

#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include <TString.h>
#include <algorithm>

template <typename T1, typename T2>
class SignatureTH2F_EventVariableVsObjectVariable : public SignatureTH2F 
{
 public:
  SignatureTH2F_EventVariableVsObjectVariable(TString eventvar, TString objectvar, TString productname, const char* name, const char* title="", Int_t nbinsx=100,Double_t xmin=0,Double_t xmax=1000, Int_t nbinsy=100, Double_t ymin=0, Double_t ymax=1000):SignatureTH2F(name,title,nbinsx,xmin,xmax,nbinsy,ymin,ymax),m_eventvar(eventvar),m_objectvar(objectvar) {m_productnames.push_back(productname);}

  SignatureTH2F_EventVariableVsObjectVariable(TH2F h):SignatureTH2F(h){}
  SignatureTH2F_EventVariableVsObjectVariable():SignatureTH2F(){}

  void addProduct(TString pname){
    if(std::find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
  }

  using TH2F::Fill;
  Int_t Fill(BaseHandler* handler){
    T1 eventval;
    T2 objectval;
    if(!handler->getVariable(m_eventvar,eventval))return -1;
    int dummy = -1;
    for(int i = 0; i < (int)m_productnames.size(); i++){
      std::vector<SignatureObject*> v= handler->getProduct(m_productnames[i]);
      for(int j = 0; j < (int)v.size(); j++){
	if(!v[j]->getVariable(m_objectvar,objectval)){
	  dummy = -1;
	}else{
	  dummy = TH2F::Fill(eventval,objectval,handler->getPhysicsWeight());
	}
      }
    }
    return dummy;
  }
  virtual void Copy(TObject& hnew) const
  {
    TH2F::Copy(hnew);
    ((SignatureTH2F_EventVariableVsObjectVariable<T1,T2>&)hnew).m_eventvar = m_eventvar;
    ((SignatureTH2F_EventVariableVsObjectVariable<T1,T2>&)hnew).m_objectvar = m_objectvar;
    ((SignatureTH2F_EventVariableVsObjectVariable<T1,T2>&)hnew).m_productnames = m_productnames;
  }

 private:
  TString m_eventvar;
  TString m_objectvar;
  std::vector<TString> m_productnames;

  ClassDef(SignatureTH2F_EventVariableVsObjectVariable,1);
};
#endif
