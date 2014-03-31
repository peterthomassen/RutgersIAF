#ifndef ObjectVariableMethod_h
#define ObjectVariableMethod_h

#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariable.h"

class SignatureObject;

typedef double (SignatureObject::*SOfunction)() const;

class ObjectVariableMethod : public ObjectVariable {
 public:
  ObjectVariableMethod(TString name, SOfunction func):ObjectVariable(name),m_function(func){}
  virtual ~ObjectVariableMethod() {}

  virtual bool calculate(SignatureObject*);

 private:
  SOfunction m_function;

  ClassDef(ObjectVariableMethod,1);

};

#endif
