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
    bool thisVariable = false;
    bool hasThisVariable = product[motherIndex]->getVariable(getName(),thisVariable);
    if(hasThisVariable && thisVariable){
      sigObj->setVariable(getName(),thisVariable);
      return thisVariable;
    }
    bool hasVariable = product[motherIndex]->getVariable(m_variable,motherpdgid);
    if(!hasVariable)motherpdgid=0;
    hasMother = product[motherIndex]->getVariable(m_motherIndexVariable,motherIndex);
    if(!hasMother)break;
    if(motherIndex >= (int)product.size()) break;
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
