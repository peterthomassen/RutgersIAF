#ifndef EventVariableObjectVariableVector_h
#define EventVariableObjectVariableVector_h

#include <iostream>
#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class EventVariableObjectVariableVector : public EventVariable{
 public:
  EventVariableObjectVariableVector(TString varname, TString productname, bool doSort = false, TString name="evobjectvariablevector") : EventVariable(name),m_varname(varname),m_doSort(doSort){ m_productnames.push_back(productname);}

  void addProduct(TString name){
    if(find(m_productnames.begin(),m_productnames.end(),name) == m_productnames.end())m_productnames.push_back(name);
  }

  bool calculate(BaseHandler* handler){
    std::vector<T> vector;
    T value;
    for( TString m_productname : m_productnames){
      for(SignatureObject* object : handler->getProduct(m_productname)) {
	if(object->getVariable(m_varname, value)) {
	  vector.push_back(value);
	}else if (handler->getDefaultObjectVariable(m_productname,m_varname,value)){
	  vector.push_back(value);
	}
      }
    }
    if(m_doSort){
      std::sort(vector.begin(),vector.end());
      std::reverse(vector.begin(),vector.end());
    }
    handler->setVector(getName(), vector);
    return vector.size();
  }

  ClassDef(EventVariableObjectVariableVector,1);

 private:
  TString m_varname;
  bool m_doSort;
  std::vector<TString> m_productnames;


};

#endif
