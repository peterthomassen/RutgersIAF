#ifndef EventVariableTriggerWeight_h
#define EventVariableTriggerWeight_h

#include <vector>
#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

class EventVariableTriggerWeight : public EventVariable{
 public:
  EventVariableTriggerWeight(TString name = "TRIGGERWEIGHT") : EventVariable(name) { }

  bool calculate(BaseHandler* handler);

  ClassDef(EventVariableTriggerWeight,1);

 private:

};

#endif
