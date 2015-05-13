#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableEffectiveArea.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableEffectiveArea)

  using namespace std;

bool ObjectVariableEffectiveArea::calculate(SignatureObject* obj)
{
  if(obj->Pt() == 0)return false;
  double eta = fabs(obj->Eta());
  double area = -1;
  for(map<double,double>::reverse_iterator iter = m_eta_area_map.rbegin(); iter != m_eta_area_map.rend(); iter++){
    if(eta < (*iter).first) area = (*iter).second;
  }
  if(area < 0)return false;
  obj->setVariable(getName(),area);
  return true;
}

void ObjectVariableEffectiveArea::addArea(double maxEta, double area)
{
  m_eta_area_map[maxEta] = area;
}
