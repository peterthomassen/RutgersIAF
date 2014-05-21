#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableOS.h"
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableOS)

void EventVariableOS::addProduct(TString pname) {
	if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableOS::calculate(BaseHandler* handler) {
	double minMass = 1e6;
	double maxMass = 0;

	vector<SignatureObject*> v = handler->getProduct(m_productnames[0]);
	for(int i = 1; i < (int)m_productnames.size(); ++i){
	  vector<SignatureObject*> w = handler->getProduct(m_productnames[i]);
	  v.insert(v.end(), w.begin(), w.end());
	}

	for(int j = 0; j < (int)v.size(); j++){
		double charge1 = 0;
		bool charge1set = (v[j])->getVariable("CHARGE",charge1);
		if(!charge1set)continue;
		for(int k = j+1; k < (int)v.size(); k++){
			double charge2 = 0;
			bool charge2set = (v[k])->getVariable("CHARGE",charge2);
			if(!charge2set) {
				continue;
			}
			if(charge1*charge2 < 0){
				double mass = (TLorentzVector(*v[k])+TLorentzVector(*v[j])).M();
				if(mass < minMass)minMass = mass;
				if(mass > maxMass)maxMass = mass;
			}
		}
	}
	
	handler->setVariable(TString::Format("%sOSMINMLL",m_prefix.Data()),minMass);
	handler->setVariable(TString::Format("%sOSMAXMLL",m_prefix.Data()),maxMass);
	return true;
}
