#ifndef EventVariableDRvector_h
#define EventVariableDRvector_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

class EventVariableDRvector : public EventVariable{
public:
	EventVariableDRvector(TString productname1, TString productname2, TString name="evdrvector") : EventVariable(name),m_productname1(productname1),m_productname2(productname2) { }

	bool calculate(BaseHandler* handler);

	ClassDef(EventVariableDRvector, 1);

private:
	TString m_productname1;
	TString m_productname2;
};

#endif
