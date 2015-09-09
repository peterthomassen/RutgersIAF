#include "RutgersIAF/EventAnalyzer/interface/EventVariableDRvector.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

#include <vector>

ClassImp(EventVariableDRvector)

using namespace std;

bool EventVariableDRvector::calculate(BaseHandler *handler) {
	vector<SignatureObject*> v = handler->getProduct(m_productname1);
	vector<SignatureObject*> w = handler->getProduct(m_productname2);
	
	std::vector<double> vector;
	
	for(auto const &sigObj : v) {
		double dR = 100;
		for(auto const &compObj : w) {
			dR = min(dR, TLorentzVector(*sigObj).DeltaR(TLorentzVector(*compObj)));
		}
		vector.push_back(dR);
	}
	
	handler->setVector(getName(), vector);
	
	return w.size();
}
