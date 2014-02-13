#ifndef SignatureCutReversed_h
#define SignatureCutReversed_h

#include "RutgersIAF2012/EventAnalyzer/interface/SignatureCut.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"

class SignatureCutReversed : public SignatureCut {
 public:
  SignatureCutReversed(TString cutname, const char* name="reversedsignaturecut") : SignatureCut(name),m_cutname(cutname){ /* no-op */}
  virtual ~SignatureCutReversed(){}

  bool passCut(BaseHandler* handler) const
  {
    bool retval;
    bool isSet = handler->getVariable(m_cutname,retval);
    if(!isSet)return false;
    return !retval;
  }
  bool operator()(BaseHandler* handler) const
  {
    return passCut(handler);
  }

 private:
  TString m_cutname;

  ClassDef(SignatureCutReversed,1);
};


#endif
