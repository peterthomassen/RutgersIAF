#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableMuonTotalIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableMuonTotalIso)

using namespace std;

bool ObjectVariableMuonTotalIso::calculate(SignatureObject* sigObj)
{
  double pdgid = 0;
  bool hasPdgid = sigObj->getVariable("PDGID", pdgid);
  if(!hasPdgid || fabs(fabs(pdgid) - 13) > 1E-6) {
	  return false;
  }

  double chargedHadronIso = 0;
  bool isSet_chargedHadronIso = sigObj->getVariable("PF_CHARGEDHADRONISO",chargedHadronIso);
  double neutralHadronIso = 0;
  bool isSet_neutralHadronIso = sigObj->getVariable("PF_NEUTRALHADRONISO",neutralHadronIso);
  double photonIso = 0;
  bool isSet_photonIso = sigObj->getVariable("PF_PHOTONISO",photonIso);
  double beta = 0;
  bool isSet_beta = sigObj->getVariable("BETA",beta);

  if(!(isSet_chargedHadronIso && isSet_neutralHadronIso && isSet_photonIso && isSet_beta))return false;

  double totalIso = chargedHadronIso + max(0.0,neutralHadronIso + photonIso -0.5*beta);
  sigObj->setVariable(getName(),totalIso);
  return true;
}
