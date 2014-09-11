#ifndef EventVariableObjectVariableExtreme_h
#define EventVariableObjectVariableExtreme_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class EventVariableObjectVariableExtreme : public EventVariable{
 public:
  EventVariableObjectVariableExtreme(TString varname, TString productname, TString name="evobjectvariableextreme", int which = 1) : EventVariable(name),m_varname(varname),m_which(which) {
	  m_productnames.push_back(productname);
  }

  void addProduct(TString pname){
    if(std::find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
  }

  bool calculate(BaseHandler* handler){
    T extremum = -1e6;
    bool any=false;
    for(int i = 0; i < (int)m_productnames.size(); i++){
      std::vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
      for(int j = 0; j < (int)v.size(); j++){
	T value;
	if(v[j]->getVariable(m_varname,value)) {
		if(!any) {
			extremum = value;
			any = true;
			continue;
		}
		switch(m_which) {
			case 1:
				if(value > extremum) {
					extremum = value;
				}
				break;
			case -1:
				if(value < extremum) {
					extremum = value;
				}
				break;
			default:
				return false;
		}
	}
      }
    }
    if(!any)return false;
    handler->setVariable(getName(),extremum);
    return true;
  }

  ClassDef(EventVariableObjectVariableExtreme,1);

 private:
  TString m_varname;
  std::vector<TString> m_productnames;
  int m_which;


};

#endif
