#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(EventVariableObjectWeightPtTF1)

using namespace std;

void EventVariableObjectWeightPtTF1::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableObjectWeightPtTF1::calculate(BaseHandler* handler)
{
  double weight = 1.0;
  for(int i = 0; i < (int)m_productnames.size(); i++){
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    for(int j = 0; j < (int)v.size(); j++){
      weight *= m_function->Eval(v[j]->Pt());
    }
  }
  handler->setVariable(getName(),weight);
  return true;
}
