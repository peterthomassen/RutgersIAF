#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableMixedPairMass.h"
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

ClassImp(EventVariableMixedPairMass)

using namespace std;

void EventVariableMixedPairMass::addProduct(TString pname) {
        if(find(m_productnames.begin(), m_productnames.end(),pname) == m_productnames.end()) {
                m_productnames.push_back(pname);
        }
}

bool EventVariableMixedPairMass::calculate(BaseHandler* handler) {
  double minMass = 1e6;
  double maxMass = 0;
  double bestMass = 1e6;
  
  bool enoughObjects = false;
        
  for(size_t i = 0; i < m_productnames.size(); i++){
    vector<SignatureObject*> v1 = handler->getProduct(m_productnames[i]);
    for(size_t h = i+1; h < m_productnames.size(); h++){
      vector<SignatureObject*> v2 = handler->getProduct(m_productnames[h]);
      if(v1.size() > 0 && v2.size() > 0) {
	enoughObjects = true;
      }
      for(size_t j = 0; j < v1.size(); j++){
	for(size_t k = 0; k < v2.size(); k++){
	  double mass = (*v1[j] + *v2[k]).M();
	  minMass = min(minMass, mass);
	  maxMass = max(maxMass, mass);
	  if(m_peak && fabs(m_peak - mass) < fabs(m_peak - bestMass)) {
	    bestMass = mass;
	  }
	}
      }
    }
  }
  if(!enoughObjects) {
    return false;
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
