#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableDeltaBetaCorrectedTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableDeltaBetaCorrectedTotalIso)

using namespace std;


bool ObjectVariableDeltaBetaCorrectedTotalIso::calculate(SignatureObject* sigObj)
{
  if(m_flagName != ""){
    bool goodFlag = false;
    bool isSet_flag = sigObj->getVariable(m_flagName, goodFlag);
    if(!(isSet_flag && goodFlag))return false;
  }
  double chargedHadronIso = 0;
  bool isSet_chargedHadronIso = sigObj->getVariable(m_chargedHadronName,chargedHadronIso);
  double neutralHadronIso = 0;
  bool isSet_neutralHadronIso = m_neutralHadronName.Length()
    ? sigObj->getVariable(m_neutralHadronName,neutralHadronIso)
    : true;
  double photonIso = 0;
  bool isSet_photonIso = sigObj->getVariable(m_photonName,photonIso);
  double beta = 0;
  bool isSet_beta = sigObj->getVariable(m_betaName,beta);

  if(!(isSet_chargedHadronIso && isSet_neutralHadronIso && isSet_photonIso && isSet_beta))return false;

  double totalIso = chargedHadronIso + max(0.0,neutralHadronIso + photonIso - 0.5 * beta);
  sigObj->setVariable(getName(),totalIso);
  return true;
}
