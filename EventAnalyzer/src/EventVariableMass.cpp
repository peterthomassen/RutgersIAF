#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableMass.h"
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableMass)

void EventVariableMass::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableMass::calculate(BaseHandler* handler)
{
  TLorentzVector sum;
  for(int i = 0; i < (int)m_productnames.size(); i++){
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    for(size_t i = 0; i < v.size(); ++i) {
		sum += *v[i];
	}
  }
  handler->setVariable(getName(),sum.M());
  return true;
}
