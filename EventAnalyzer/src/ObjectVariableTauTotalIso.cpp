#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableTauTotalIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableTauTotalIso)

  using namespace std;

bool ObjectVariableTauTotalIso::calculate(SignatureObject* sigObj)
{
  double pdgid = 0;
  bool hasPdgid = sigObj->getVariable("PDGID", pdgid);
  if(!hasPdgid || fabs(fabs(pdgid) - 15) > 1E-6) {
	  return false;
  }

  int tauIsoDisc = 0;
  if(!sigObj->getVariable("DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR",tauIsoDisc))
    return false;

  if(tauIsoDisc){
    sigObj->setVariable(getName(),0);
    return true;
  }else{
    double photonIso = 0;
    double chargedIso = 0;
    if(!sigObj->getVariable("PF_PHOTONISO05",photonIso))return false;
    if(!sigObj->getVariable("PF_CHARGEDHADRONISO05",chargedIso))return false;
    sigObj->setVariable(getName(),std::max(photonIso,0.0)+std::max(chargedIso,0.0));
    return true;
  }


  return false;
}
