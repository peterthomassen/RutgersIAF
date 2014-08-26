#ifndef EventVariableObjectVariableMax_h
#define EventVariableObjectVariableMax_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class EventVariableObjectVariableMax : public EventVariable{
 public:
  EventVariableObjectVariableMax(TString varname, TString productname, TString name="evobjectvariablemax") : EventVariable(name),m_varname(varname){m_productnames.push_back(productname);}

  void addProduct(TString pname){
    if(std::find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
  }

  bool calculate(BaseHandler* handler){
    T max = -1e6;
    bool any=false;
    for(int i = 0; i < (int)m_productnames.size(); i++){
      std::vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
      for(int j = 0; j < (int)v.size(); j++){
	any=true;
	T value;
	if(v[j]->getVariable(m_varname,value) && value > max)max = value;
      }
    }
    if(!any)return false;
    handler->setVariable(getName(),max);
    return true;
  }

  ClassDef(EventVariableObjectVariableMax,1);

 private:
  TString m_varname;
  std::vector<TString> m_productnames;


};

#endif
