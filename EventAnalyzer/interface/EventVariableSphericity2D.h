#ifndef EventVariableSphericity2D_h
#define EventVariableSphericity2D_h
#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableSphericity2D : public EventVariable{
 public:
 EventVariableSphericity2D(TString name, TString productname, int maxNoOfObjects=9999) : EventVariable(name), m_maxNoOfObjects(maxNoOfObjects) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableSphericity2D,1);

 private:
  std::vector<TString> m_productnames;
  int m_maxNoOfObjects;

};

#endif