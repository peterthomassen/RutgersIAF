#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMethod.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

ClassImp(ObjectVariableMethod)

using namespace std;

bool ObjectVariableMethod::calculate(SignatureObject* sigObj)
{
  double value = (sigObj->*m_function)();
  sigObj->setVariable(getName(),value);
  return true;
}
