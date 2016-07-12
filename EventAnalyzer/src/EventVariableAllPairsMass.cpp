#include "RutgersIAF/EventAnalyzer/interface/EventVariableAllPairsMass.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableAllPairsMass)

void EventVariableAllPairsMass::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableAllPairsMass::calculate(BaseHandler* handler)
{
  for(int ip = 0; ip < (int)m_productnames.size(); ip++){
    vector<SignatureObject*> v = handler->getProduct(m_productnames[ip]);
    //
    for(size_t i = 0; i < v.size(); ++i){//loop over all pairs in a given product collection
      for(size_t j = i+1; j < v.size(); ++j){
	//	TString::Format("%dmPT2",i)
	handler->setVariable( TString::Format("%d_%d_%s",(int)i,(int)j,getName().Data()),((*v[i])+(*v[j])).M());
      }
    }
  }
  //
  return true;
}
