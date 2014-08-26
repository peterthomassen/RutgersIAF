#include "RutgersIAF/EventAnalyzer/interface/EventVariableSumPT.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableSumPT)

void EventVariableSumPT::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableSumPT::calculate(BaseHandler* handler)
{
  double ptsum = 0;
  for(int i = 0; i < (int)m_productnames.size(); i++){
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    for(int j = 0; j < (int)v.size(); j++){
      ptsum += v[j]->Pt();
    }
  }
  handler->setVariable(getName(),ptsum);
  return true;
}
