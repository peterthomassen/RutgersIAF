#ifndef EventVariableLeptonBjetMass_h
#define EventVariableLeptonBjetMass_h


#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableLeptonBjetMass : public EventVariable{
 public:
  EventVariableLeptonBjetMass(TString name) : EventVariable(name) {}

  //  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableLeptonBjetMass,1);

 private:
  //  TString m_prefix;
  //  double m_peak;
  //  double m_width;
  //  std::vector<TString> m_productnames;


};

#endif
