#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableOSSF.h"
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableOSSF)

void EventVariableOSSF::addProduct(TString pname)
{
  if(find(m_productnames.begin(),m_productnames.end(),pname) == m_productnames.end())m_productnames.push_back(pname);
}

bool EventVariableOSSF::calculate(BaseHandler* handler)
{
  double minMass = 1e6;
  double maxMass = 0;
  int nOSSF = 0;
  double bestMass = 0;
  for(int i = 0; i < (int)m_productnames.size(); i++){
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    int nPlus = 0;
    int nMinus = 0;
    for(int j = 0; j < (int)v.size(); j++){
      double charge1 = 0;
      bool charge1set = (v[j])->getVariable("CHARGE",charge1);
      if(!charge1set)continue;
      charge1 > 0 ? nPlus++ : nMinus++;
      for(int k = j+1; k < (int)v.size(); k++){
	double charge2 = 0;
	bool charge2set = (v[k])->getVariable("CHARGE",charge2);
	if(!charge2set)continue;
	if(charge1*charge2 < 0){
	  double mass = (TLorentzVector(*v[k])+TLorentzVector(*v[j])).M();
	  if(mass < minMass)minMass = mass;
	  if(mass > maxMass)maxMass = mass;
	  if(fabs(m_zmass - mass) < fabs(m_zmass - bestMass)) bestMass = mass;
	}
      }
    }
    nOSSF += min(nPlus,nMinus);
  }
  bool onZ = (fabs(bestMass - m_zmass) < m_zwidth);

  handler->setVariable(TString::Format("%sOSSFMINMLL",m_prefix.Data()),minMass);
  handler->setVariable(TString::Format("%sOSSFMAXMLL",m_prefix.Data()),maxMass);
  handler->setVariable(TString::Format("%sMOSSF",m_prefix.Data()),bestMass);
  handler->setVariable(TString::Format("%sNOSSF",m_prefix.Data()),nOSSF);
  handler->setVariable(TString::Format("%sONZ",m_prefix.Data()),onZ);
  return true;
}
