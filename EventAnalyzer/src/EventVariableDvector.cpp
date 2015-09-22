#include "RutgersIAF/EventAnalyzer/interface/EventVariableDvector.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

#include <vector>

ClassImp(EventVariableDvector)

using namespace std;

bool EventVariableDvector::addProduct(TString productName) {
	if(find(m_productNames2.begin(), m_productNames2.end(), productName) != m_productNames2.end()) {
		return false;
	}
	
	m_productNames2.push_back(productName);
	
	return true;
}

bool EventVariableDvector::calculate(BaseHandler *handler) {
	vector<SignatureObject*> v = handler->getProduct(m_productName1);
	
	std::vector<double> dRvector;
	std::vector<double> dPhivector;
	
	for(auto const &sigObj : v) {
		double dR = 100;
		double dPhi = 100;
		for(auto const &productName2 : m_productNames2) {
			for(auto const &compObj : handler->getProduct(productName2)) {
				if(sigObj == compObj) {
					continue;
				}
				double dRnew = TLorentzVector(*sigObj).DeltaR(TLorentzVector(*compObj));
				if(dRnew < dR) {
					dR = dRnew;
					dPhi = TLorentzVector(*sigObj).DeltaPhi(TLorentzVector(*compObj));
				}
			}
		}
		dRvector.push_back(dR);
		dPhivector.push_back(dPhi);
	}
	
	handler->setVector(m_productName1 + "DR" + m_suffix, dRvector);
	handler->setVector(m_productName1 + "DPhi" + m_suffix, dPhivector);
	
	return true;
}
