#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableConeCorrectedPt.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableConeCorrectedPt)

using namespace std;

bool ObjectVariableConeCorrectedPt::calculate(SignatureObject* obj)
{
  double pt = 0;
  if(!obj->getVariable(m_ptName,pt))return false;
  double miniIso = 0;
  if(!obj->getVariable(m_miniIsoName,miniIso))return false;
  double ptRatio = 0;
  if(!obj->getVariable(m_ptRatioName,ptRatio))return false;
  double ptRel = 0;
  if(!obj->getVariable(m_ptRelName,ptRel))return false;
  double corrPt = pt;
  if(ptRel > m_ptRelVal){
    corrPt = pt * (1 + max(0.0,miniIso - m_miniIsoVal));
  }else{
    corrPt = max(pt,pt / ptRatio * m_ptRatioVal);
  }
  obj->setVariable(getName(),corrPt);
  return true;
}
