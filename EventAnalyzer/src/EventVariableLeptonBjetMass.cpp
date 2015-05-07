#include "RutgersIAF/EventAnalyzer/interface/EventVariableLeptonBjetMass.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableLeptonBjetMass)


bool EventVariableLeptonBjetMass::calculate(BaseHandler* handler) {
  double value = 100.;
	handler->setVariable("LEPBJETMASS",value);
	return true;
}
