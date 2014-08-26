#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableGenVertexR.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableGenVertexR)

bool ObjectVariableGenVertexR::calculate(SignatureObject* sigObj)
{
  double vx = -99999;
  double vy = -99999;
  double vz = -999999;
  if(!sigObj->getVariable("vx",vx) || !sigObj->getVariable("vy",vy) || !sigObj->getVariable("vz",vz)) return false;
  sigObj->setVariable(getName(),sqrt(pow(vx,2)+pow(vy,2)));
  return true;

}
