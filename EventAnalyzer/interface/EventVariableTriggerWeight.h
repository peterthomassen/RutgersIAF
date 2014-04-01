#ifndef EventVariableTriggerWeight_h
#define EventVariableTriggerWeight_h

#include <vector>
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"

class EventVariableTriggerWeight : public EventVariable{
 public:
  EventVariableTriggerWeight(TString name = "TRIGGERWEIGHT") : EventVariable(name) { }

  bool calculate(BaseHandler* handler);

  ClassDef(EventVariableTriggerWeight,1);

 private:

};

#endif
