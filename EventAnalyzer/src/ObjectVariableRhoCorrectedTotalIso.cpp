#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRhoCorrectedTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableRhoCorrectedTotalIso)

using namespace std;


bool ObjectVariableRhoCorrectedTotalIso::calculate(SignatureObject* sigObj)
{
  double chargedHadronIso = 0;
  bool isSet_chargedHadronIso = sigObj->getVariable(m_chargedHadronName,chargedHadronIso);
  double neutralHadronIso = 0;
  bool isSet_neutralHadronIso = sigObj->getVariable(m_neutralHadronName,neutralHadronIso);
  double photonIso = 0;
  bool isSet_photonIso = sigObj->getVariable(m_photonName,photonIso);
  double rho = 0;
  bool isSet_rho = sigObj->getVariable(m_rhoName,rho);
  double area = 0;
  bool isSet_area = sigObj->getVariable(m_areaName,area);

  if(!(isSet_chargedHadronIso && isSet_neutralHadronIso && isSet_photonIso && isSet_rho && isSet_area))return false;

  double totalIso = chargedHadronIso + max(0.0,neutralHadronIso + photonIso - rho*area);
  sigObj->setVariable(getName(),totalIso);
  return true;
}
