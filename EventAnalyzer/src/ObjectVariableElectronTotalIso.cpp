#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableElectronTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableElectronTotalIso)

using namespace std;


bool ObjectVariableElectronTotalIso::calculate(SignatureObject* sigObj)
{
  double pdgid = 0;
  bool hasPdgid = sigObj->getVariable("PDGID", pdgid);
  // Do not enforce electron PDGID here -- also allow unset PDGID (for tracks)
  if(hasPdgid && fabs(fabs(pdgid) - 11) > 1E-6) {
	  return false;
  }

  double chargedHadronIso = 0;
  bool isSet_chargedHadronIso = sigObj->getVariable("CHARGEDHADRONISO",chargedHadronIso);
  double neutralHadronIso = 0;
  bool isSet_neutralHadronIso = sigObj->getVariable("NEUTRALHADRONISO",neutralHadronIso);
  double photonIso = 0;
  bool isSet_photonIso = sigObj->getVariable("PHOTONISO",photonIso);
  double rho = 0;
  bool isSet_rho = sigObj->getVariable("RHO",rho);

  if(!(isSet_chargedHadronIso && isSet_neutralHadronIso && isSet_photonIso && isSet_rho))return false;

  double area = 0;
  double eta = fabs(sigObj->Eta());
  if (eta < 1.0) area = 0.13;
  else if(eta < 1.479) area = 0.14;
  else if(eta < 2.0) area = 0.07;
  else if(eta < 2.2) area = 0.09;
  else if(eta < 2.4) area = 0.11;
  else area = 0.14;

  double totalIso = chargedHadronIso + max(0.0,neutralHadronIso + photonIso - rho*area);
  sigObj->setVariable(getName(),totalIso);
  return true;
}
