#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableMethod.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableMethod)

using namespace std;

bool ObjectVariableMethod::calculate(SignatureObject* sigObj)
{
  double value = (sigObj->*m_function)();
  sigObj->setVariable(getName(),value);
  return true;
}
