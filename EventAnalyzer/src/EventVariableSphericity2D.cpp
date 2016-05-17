#include "RutgersIAF/EventAnalyzer/interface/EventVariableSphericity2D.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableSphericity2D)

void EventVariableSphericity2D::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableSphericity2D::calculate(BaseHandler* handler)
{
	// Represent sphericity matrix as {{a,b},{b,c}}
	double a=0;
	double b=0;
	double c=0;
	
	// Compute Sphericity Matrix
	for(int i = 0; i < (int)m_productnames.size(); i++) {
		vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
		for(int j = 0; j < (int)v.size(); j++){
			double px = TLorentzVector(*v[j]).Px();
			double py = TLorentzVector(*v[j]).Py();
			double pt = v[j]->Pt();

			a+=px*px/pt;
			b+=px*py/pt;
			c+=py*py/pt;
		}
	}
	
	double lambdaMin = (a + c - sqrt((a-c)*(a-c) + 4*b*b))/2.;

	if(a+c == 0){
		return false;
	}else{
		handler->setVariable(getName(),(2*lambdaMin)/(a+c));
	}
  return true;
}