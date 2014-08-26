#ifndef EventVariableMixedPairMass_h
#define EventVariableMixedPairMass_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"

class EventVariableMixedPairMass : public EventVariable{
 public:
  EventVariableMixedPairMass(TString name, TString productname, TString prefix="", double peak = 0, double width = 10) : EventVariable(name),m_prefix(prefix),m_peak(peak),m_width(width) {m_productnames.push_back(productname);}

  void addProduct(TString);

  bool calculate(BaseHandler*);

  ClassDef(EventVariableMixedPairMass,1);

 private:
  TString m_prefix;
  double m_peak;
  double m_width;
  std::vector<TString> m_productnames;


};

#endif
