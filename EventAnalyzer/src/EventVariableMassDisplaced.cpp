#include "RutgersIAF/EventAnalyzer/interface/EventVariableMassDisplaced.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableMassDisplaced)

void EventVariableMassDisplaced::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableMassDisplaced::calculate(BaseHandler* handler)
{
  TLorentzVector sum;
  for(int i = 0; i < (int)m_productnames.size(); i++){
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    for(size_t i = 0; i < v.size(); ++i) {
      double px=0,py=0,pz=0,en=0;
      bool isSet_px = v[i]->getVariable(m_pxName,px);
      bool isSet_py = v[i]->getVariable(m_pyName,py);
      bool isSet_pz = v[i]->getVariable(m_pzName,pz);
      bool isSet_en = v[i]->getVariable(m_eName,en);
      if(!isSet_px || !isSet_py || !isSet_pz || !isSet_en)return false;
      TLorentzVector vect(px,py,pz,en);
      sum += vect;
    }
  }
  handler->setVariable(getName(),sum.M());
  return true;
}
