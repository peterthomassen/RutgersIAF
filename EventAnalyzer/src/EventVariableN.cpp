#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableN)

void EventVariableN::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableN::calculate(BaseHandler* handler)
{
  int count = 0;
  for(int i = 0; i < (int)m_productnames.size(); i++){
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    count += (int)v.size();
  }
  handler->setVariable(getName(),count);
  return true;
}
