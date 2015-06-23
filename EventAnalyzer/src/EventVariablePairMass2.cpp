#include "RutgersIAF/EventAnalyzer/interface/EventVariablePairMass2.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariablePairMass2)

void EventVariablePairMass2::addProduct(TString pname) {
	if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariablePairMass2::calculate(BaseHandler* handler) {
	double minMass = 1e6;
	double maxMass = 0;

	if(m_productnames.size() < 1) {
	  return false;
	}

	vector<SignatureObject*> v0 = handler->getProduct(m_productnames[0]);
	//	cout << "m_productnames[0]=" << m_productnames[0] << endl;

	if(m_productnames.size() < 2) {
	  return false;
	}
	vector<SignatureObject*> v1 = handler->getProduct(m_productnames[1]);
	//	cout << "m_productnames[1]=" << m_productnames[1] << endl;

	for(int i = 0; i < (int)v0.size(); ++i) {
	  for(int j = 0; j < (int)v1.size(); ++j) {
	    double mass = (TLorentzVector(*v0[i]) + TLorentzVector(*v1[j])).M();
				if(mass < minMass)minMass = mass;
				if(mass > maxMass)maxMass = mass;
	  }
	}


	/*
	  cout << "i,m_productnames[i]=" << endl;
	  cout << i << endl;
	  cout << m_productnames[i] << endl;
	//	cout << "v[0] Pt" << endl;
	//        double mypt;
	//	(v[0])->getVariable("PAT_PT",mypt);
	//	cout << mypt << endl;
	cout << "step1" << endl;
	cout << charge1 << endl;
	cout << charge2 << endl;
	cout << "j,k" << endl;
	int j1 = j; int k1 = k;
	cout << j << endl;
	cout << k << endl;
	cout << "mass=" << endl;
	cout << mass << endl;
	*/

	handler->setVariable(TString::Format("%sMIN",m_prefix.Data()),minMass);
	handler->setVariable(TString::Format("%sMAX",m_prefix.Data()),maxMass);
	return true;
}
