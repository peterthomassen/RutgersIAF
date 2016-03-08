#ifndef EventVariableSumPT_h
#define EventVariableSumPT_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableSumPT : public EventVariable{
 public:
 EventVariableSumPT(TString name, TString productname, int maxNoOfObjects=9999) : EventVariable(name), m_maxNoOfObjects(maxNoOfObjects) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableSumPT,1);

 private:
  std::vector<TString> m_productnames;
  int m_maxNoOfObjects;

};

#endif
