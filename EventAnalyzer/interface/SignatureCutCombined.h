#ifndef SignatureCutCombined_h
#define SignatureCutCombined_h

#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include <vector>
#include <algorithm>

class SignatureCutCombined: public SignatureCut
{
 public:
  SignatureCutCombined(TString cut1,TString cut2, bool doAnd = false, const char* name = "combinedsignaturecut") : SignatureCut(name),m_and(doAnd){
    m_cuts.push_back(cut1);
    m_cuts.push_back(cut2);
  }

  virtual ~SignatureCutCombined() {m_cuts.clear();}

  void addCut(TString cut);
  bool passCut(BaseHandler* handler) const
  {
    bool retval = m_and;
    for(int i = 0; i < (int)m_cuts.size(); i++){
      bool passVal = false;
      bool isSet = handler->getVariable(m_cuts[i],passVal);
      if(m_and) retval = retval && passVal && isSet;
      else retval = retval || (passVal && isSet);
    }
    return retval;
  }
  bool operator()(BaseHandler* handler) const
  {
    return passCut(handler);
  }

 private:
  std::vector<TString> m_cuts;
  bool m_and; //true = satsify and, false = satisfy or

  ClassDef(SignatureCutCombined,1);
};

inline void SignatureCutCombined::addCut(TString cut)
{
  if(find(m_cuts.begin(),m_cuts.end(),cut)==m_cuts.end())m_cuts.push_back(cut);
}


#endif
