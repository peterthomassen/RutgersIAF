#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableEffectiveAreaMiniIsolation.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableEffectiveAreaMiniIsolation)

using namespace std;

bool ObjectVariableEffectiveAreaMiniIsolation::calculate(SignatureObject* obj)
{
  if(obj->Pt() == 0)return false;
  double cone = 0;
  if(!obj->getVariable(m_coneName,cone)) return false;
  if(cone == 0)return false;
  double eta = fabs(obj->Eta());
  double area = -1;
  for(map<double,double>::reverse_iterator iter = m_eta_area_map.rbegin(); iter != m_eta_area_map.rend(); iter++){
    if(eta < (*iter).first) area = (*iter).second;
  }
  if(area < 0)return false;
  area *= pow(m_scale/cone,m_power);

  obj->setVariable(getName(),area);
  return true;
}
