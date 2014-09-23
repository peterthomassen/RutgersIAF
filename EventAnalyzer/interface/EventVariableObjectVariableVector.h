#ifndef EventVariableObjectVariableVector_h
#define EventVariableObjectVariableVector_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

template <typename T>
class EventVariableObjectVariableVector : public EventVariable{
 public:
  EventVariableObjectVariableVector(TString varname, TString productname, TString name="evobjectvariablevector") : EventVariable(name),m_varname(varname),m_productname(productname) {
  }

  bool calculate(BaseHandler* handler){
    std::vector<T> vector;
    T value;
    for(SignatureObject* object : handler->getProduct(m_productname)) {
      if(object->getVariable(m_varname, value)) {
        vector.push_back(value);
      }
    }
    handler->setVector(getName(), vector);
    return vector.size();
  }

  ClassDef(EventVariableObjectVariableVector,1);

 private:
  TString m_varname;
  TString m_productname;


};

#endif
