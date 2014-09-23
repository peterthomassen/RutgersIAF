#ifndef EventVariableProductAngle_h
#define EventVariableProductAngle_h

#include "RutgersIAF/EventAnalyzer/interface/EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class EventVariableProductAngle : public EventVariable {

public:
	EventVariableProductAngle(TString product1, TString product2, const char* name="productAngle") : EventVariable(name),m_product2(product2) {
		addProduct(product1);
	}
	virtual ~EventVariableProductAngle(){}
	
	void addProduct(TString name) {
		m_product1names.push_back(name);
	}
	
	bool calculate(BaseHandler* handler)  {
		std::vector<SignatureObject*> v2 = handler->getProduct(m_product2);
		if(!v2.size()) {
			return false;
		}
		
		for(size_t i = 0; i < m_product1names.size(); ++i) {
			std::vector<SignatureObject*> v1 = handler->getProduct(m_product1names[i]);
			if(!v1.size()) {
				return false;
			}
			double angle = v1[0]->Angle(v2[0]->Vect());
			handler->setVariable(getName(), angle);
			return true;
		}
		
		return false;
	}

private:
	std::vector<TString> m_product1names;
	TString m_product2;

	ClassDef(EventVariableProductAngle,1);
};


#endif
