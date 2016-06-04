#include "RutgersIAF/EventAnalyzer/interface/EventVariableLinearRadialMoment.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableLinearRadialMoment)

void EventVariableLinearRadialMoment::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableLinearRadialMoment::calculate(BaseHandler* handler)
{
  // Store input objects for clear pt ordering
  TLorentzVector sumVector(0,0,0,0);
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    for(int j = 0; j < (int)v.size(); j++){
      sumVector += TLorentzVector((*v[j]));
    }
  }

  // Sort, highest pt first

  // Calculate LinearRadialMoment
  double lrm = 0;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    for(int j = 0; j < (int)v.size(); j++){
      lrm += sumVector.DeltaR(TLorentzVector((*v[j]))) * v[j]->Pt() / sumVector.Pt();
    }
  }

  handler->setVariable(getName(),lrm);
  return true;
}
