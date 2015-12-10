#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableDescendantOf.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableDescendantOf)

  using namespace std;

bool ObjectVariableDescendantOf::calculate(SignatureObject* sigObj)
{

  vector<SignatureObject*> product = m_handler->getProduct(m_productname);
  if(product.size() < 1) return false;
  int motherpdgid = 0;
  int stepCount = 0;
  int motherIndex = 0;
  bool hasMother = sigObj->getVariable(m_motherIndexVariable,motherIndex);
  if(!hasMother)return false;
  while(abs(motherpdgid) != abs(m_value) && stepCount < m_maxSteps){
    bool hasVariable = product[motherIndex]->getVariable(m_variable,motherpdgid);
    hasMother = product[motherIndex]->getVariable(m_motherIndexVariable,motherIndex);
    if(!hasVariable)motherpdgid=0;
    if(!hasMother)break;
    stepCount++;
  }
  if(abs(motherpdgid) == abs(m_value)){
    sigObj->setVariable(getName(),true);
    return true;
  }else{
    sigObj->setVariable(getName(),false);
    return false;
  }
  return false;
}
