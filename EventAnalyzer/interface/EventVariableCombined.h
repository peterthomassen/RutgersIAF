#ifndef EventVariableCombined_h
#define EventVariableCombined_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include <vector>
#include <algorithm>

class EventVariableCombined: public EventVariable
{
 public:
  EventVariableCombined(TString cut1,TString cut2, bool doAnd = false, const char* name = "combinedsignaturecut") : EventVariable(name),m_and(doAnd){
    m_cuts.push_back(cut1);
    m_cuts.push_back(cut2);
  }

  virtual ~EventVariableCombined() {m_cuts.clear();}

  void addVariable(TString cut);
  bool calculate(BaseHandler* handler)
  {
    bool retval = m_and;
    for(int i = 0; i < (int)m_cuts.size(); i++){
      bool passVal = false;
      bool isSet = handler->getVariable(m_cuts[i],passVal);
      if(m_and) retval = retval && passVal && isSet;
      else retval = retval || (passVal && isSet);
    }
    handler->setVariable(getName(),retval);
    return retval;
  }

 private:
  std::vector<TString> m_cuts;
  bool m_and; //true = satsify and, false = satisfy or

  ClassDef(EventVariableCombined,1);
};

inline void EventVariableCombined::addVariable(TString cut)
{
  if(find(m_cuts.begin(),m_cuts.end(),cut)==m_cuts.end())m_cuts.push_back(cut);
}


#endif
