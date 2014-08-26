#include "RutgersIAF/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include <algorithm>

ClassImp(EventVariableThreshold)

using namespace std;

void EventVariableThreshold::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableThreshold::calculate(BaseHandler* handler)
{
  vector<double> pts;
  for(int i = 0; i < (int)m_productnames.size(); i++){
    vector<SignatureObject*>v = handler->getProduct(m_productnames[i]);
    for(int j = 0; j < (int)v.size();j++){
      pts.push_back(v[j]->Pt());
    }
  }
  sort(pts.begin(),pts.end());
  reverse(pts.begin(),pts.end());

  bool retval = true;
  if(m_thresholds.size() > pts.size()){
    retval = false;
  }else{
    for(int i = 0; i < (int)m_thresholds.size() && retval; i++){
      if(pts[i] < m_thresholds[i])retval = false;
    }
  }
  handler->setVariable(getName(),retval);
  return retval;

}
