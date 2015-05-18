#include "RutgersIAF/EventAnalyzer/interface/EventVariableOSSF.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableOSSF)

void EventVariableOSSF::addProduct(TString pname) {
	if(find(m_productnames.begin(), m_productnames.end(), pname) == m_productnames.end()) {
		m_productnames.push_back(pname);
	}
}

bool EventVariableOSSF::calculate(BaseHandler* handler) {
	double minMass = 1e6;
	double maxMass = 0;
	int nOSSF = 0;
	double bestMass = 1e6;
	double bestMassLow = 1e6;
	int fakeRole = 0;
	for(int i = 0; i < (int)m_productnames.size(); i++) {
		vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
		int nPlus = 0;
		int nMinus = 0;
		for(int j = 0; j < (int)v.size(); j++){
			if(!m_includeFakes && v[j]->getVariable("fakeRole", fakeRole) && fakeRole > 0) {
				continue;
			}
			int charge1 = 0;
			bool charge1set = (v[j])->getVariable("CHARGE",charge1);
			if(!charge1set) {
				continue;
			}
			charge1 > 0 ? nPlus++ : nMinus++;
			for(int k = j+1; k < (int)v.size(); k++) {
				if(!m_includeFakes && v[k]->getVariable("fakeRole", fakeRole) && fakeRole > 0) {
					continue;
				}
				int charge2 = 0;
				bool charge2set = (v[k])->getVariable("CHARGE",charge2);
				if(!charge2set) {
					continue;
				}
				if(charge1 * charge2 < 0) {
					double mass = (TLorentzVector(*v[k])+TLorentzVector(*v[j])).M();
					if(mass < minMass) minMass = mass;
					if(mass > maxMass) maxMass = mass;
					if(fabs(m_zmass - mass) < fabs(m_zmass - bestMass)) bestMass = mass;
					if(mass < m_zmass && fabs(m_zmass - mass) < fabs(m_zmass - bestMassLow)) bestMassLow = mass;
				}
			}
		}
		nOSSF += min(nPlus,nMinus);
	}
	bool onZ = (fabs(bestMass - m_zmass) < m_zwidth);
	double closeMass = bestMass;
	if(!onZ && bestMassLow < bestMass) {
		bestMass = bestMassLow;
	}
	
	handler->setVariable(TString::Format("%sNOSSF",m_prefix.Data()),nOSSF);
	handler->setVariable(TString::Format("%sONZ",m_prefix.Data()),onZ);
	
	// Always set these variables to avoid skipping of NOSSF == 0 events, 
	// e.g. when selecting from the ntuple with MOSSF dimension
	handler->setVariable(TString::Format("%sOSSFMINMLL",m_prefix.Data()),minMass);
	handler->setVariable(TString::Format("%sOSSFCLOSEMLL",m_prefix.Data()),closeMass);
	handler->setVariable(TString::Format("%sOSSFMAXMLL",m_prefix.Data()),maxMass);
	handler->setVariable(TString::Format("%sMOSSF",m_prefix.Data()),bestMass);
	
	// TODO add vector of all OSSF pair masses
	
	return true;
}
