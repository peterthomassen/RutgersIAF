#include "RutgersIAF2012/EventAnalyzer/interface/EventVariablePairMass.h"
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariablePairMass)

void EventVariablePairMass::addProduct(TString pname) {
	if(find(m_productnames.begin(), m_productnames.end(),pname) == m_productnames.end()) {
		m_productnames.push_back(pname);
	}
}

bool EventVariablePairMass::calculate(BaseHandler* handler) {
	double minMass = 1e6;
	double maxMass = 0;
	double bestMass = 0;
	for(size_t i = 0; i < m_productnames.size(); i++){
		vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
		for(size_t j = 0; j < v.size(); j++){
			for(size_t k = j+1; k < v.size(); k++){
				double mass = (*v[k]+*v[j]).M();
				minMass = min(minMass, mass);
				maxMass = max(maxMass, mass);
				if(m_peak && fabs(m_peak - mass) < fabs(m_peak - bestMass)) bestMass = mass;
			}
		}
	}
	bool onPeak = (fabs(bestMass - m_peak) < m_width);

	handler->setVariable(TString::Format("%sMPAIRMIN",m_prefix.Data()),minMass);
	handler->setVariable(TString::Format("%sMPAIRMAX",m_prefix.Data()),maxMass);
	if(m_peak) {
		handler->setVariable(TString::Format("%sMPAIR",m_prefix.Data()),bestMass);
		handler->setVariable(TString::Format("%sPAIRPEAK",m_prefix.Data()),onPeak);
	}
	return true;
}
