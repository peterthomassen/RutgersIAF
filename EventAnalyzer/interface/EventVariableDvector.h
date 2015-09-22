#ifndef EventVariableDvector_h
#define EventVariableDvector_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

#include <vector>

class EventVariableDvector : public EventVariable {
public:
	EventVariableDvector(TString productName1, TString productName2, TString name="evdrvector") : EventVariableDvector(productName1, std::vector<TString>(1, productName2), productName2, name) { }

	EventVariableDvector(TString productName1, std::vector<TString> productNames2, TString suffix, TString name="evdrvector") : EventVariable(name), m_productName1(productName1), m_productNames2(productNames2), m_suffix(suffix) { }

	bool addProduct(TString productName);
	bool calculate(BaseHandler* handler);

	ClassDef(EventVariableDvector, 1);

private:
	TString m_productName1;
	std::vector<TString> m_productNames2;
	TString m_suffix;
};

#endif
