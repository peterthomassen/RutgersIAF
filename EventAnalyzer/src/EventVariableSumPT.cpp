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
  // Store input objects for clear pt ordering
  vector<double> ptVector;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    for(int j = 0; j < (int)v.size(); j++){
      ptVector.push_back( v[j]->Pt() );
    }
  }

  // Sort, highest pt first
  std::sort(ptVector.begin(), ptVector.end(), std::greater<int>());

  // Calculate SumPT
  double ptsum = 0;
  for(int i = 0; i < (int)ptVector.size(); i++) {
    if(i>=m_maxNoOfObjects) break;//max number of allowed objects in the sum.
    ptsum += (double)(ptVector.at(i));
  }

  handler->setVariable(getName(),ptsum);
  return true;
}
