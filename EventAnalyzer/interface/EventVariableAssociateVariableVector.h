#ifndef EventVariableAssociateVariableVector_h
#define EventVariableAssociateVariableVector_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class EventVariableAssociateVariableVector : public EventVariable{
 public:
 EventVariableAssociateVariableVector(TString varname, TString productname, TString associatename, bool doSort = false, TString name="evobjectvariablevector") : EventVariable(name),m_varname(varname),m_assocname(associatename),m_doSort(doSort){ m_productnames.push_back(productname);}

  void addProduct(TString name){
    if(find(m_productnames.begin(),m_productnames.end(),name) == m_productnames.end())m_productnames.push_back(name);
  }

  bool calculate(BaseHandler* handler){
    std::vector<T> vector;
    T value;
    for( TString m_productname : m_productnames){
      for(SignatureObject* object : handler->getProduct(m_productname)) {
	SignatureObject* associate = object->getAssociate(m_assocname);
	if(associate && associate->getVariable(m_varname, value)) {
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

  ClassDef(EventVariableAssociateVariableVector,1);

 private:
  TString m_varname;
  TString m_assocname;
  bool m_doSort;
  std::vector<TString> m_productnames;


};

#endif
