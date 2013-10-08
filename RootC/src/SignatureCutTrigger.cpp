#include "RutgersIAF2012/RootC/interface/SignatureCutTrigger.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(SignatureCutTrigger)

bool SignatureCutTrigger::passCut(BaseHandler* handler) const
{
  vector<SignatureTrigger*> triggers = handler->getTriggers();
  bool pass=false;
  for(int i = 0; i < (int)triggers.size(); i++){
    if(!m_usePrescaled && triggers[i]->getPrescale() != 1)continue;
    map<TString,vector<int> >::const_iterator iter;
    //DEBUG("Checking vetos");
    for(iter = m_veto_int.begin(); iter != m_veto_int.end(); iter++){
      TString name = (*iter).first;
      vector<int> vec = (*iter).second;
      SignatureCut* cut = (*(m_map_cuts.find(name))).second;
      if(find(vec.begin(),vec.end(),triggers[i]->getId()) != vec.end() && cut->passCut(handler)) {
		  if(handler->getDebugMode()) {
			  cout << "Failed trigger " << triggers[i]->getId() << endl;
		  }
		  return false;
	  }
    }
    //DEBUG("Checking accept");
    for(iter = m_accept_int.begin(); iter != m_accept_int.end(); iter++){
      TString name = (*iter).first;
      vector<int> vec = (*iter).second;
      SignatureCut* cut = (*(m_map_cuts.find(name))).second;
      if(find(vec.begin(),vec.end(),triggers[i]->getId()) != vec.end() && cut->passCut(handler))pass = true;
	  if(handler->getDebugMode()) {
		  cout<<i<<" "<<triggers[i]->getId()<<" "<<pass<<endl;
	  }
    }
  }
  //DEBUG("almost through trigger cut code");
  //cout << m_accept_int.size() << endl;
  if(m_accept_int.size() == 0){
    map<TString,SignatureCut*>::const_iterator cut_iter;
    for(cut_iter = m_map_cuts.begin(); cut_iter != m_map_cuts.end(); cut_iter++){
      SignatureCut* cut = (*cut_iter).second;
      if(cut->passCut(handler))pass = true;
    }
  }
  return pass;
}
//--------
void SignatureCutTrigger::addCut(TString name,SignatureCut* cut)
{
  m_map_cuts[name] = cut;
}
//--------
void SignatureCutTrigger::addVetoTrigger(TString name, int c)
{
  if(m_veto_int.find(name) == m_veto_int.end()){
    vector<int> vec;
    m_veto_int[name] = vec;
  }
  m_veto_int[name].push_back(c);
}
//--------
void SignatureCutTrigger::addAcceptTrigger(TString name, int c)
{
  if(m_accept_int.find(name) == m_accept_int.end()){
    vector<int> vec;
    m_accept_int[name] = vec;
  }
  m_accept_int[name].push_back(c);
}
void SignatureCutTrigger::addVetoTrigger(TString name, TString c)
{
  if(m_veto_TString.find(name) == m_veto_TString.end()){
    vector<TString> vec;
    m_veto_TString[name] = vec;
  }
  m_veto_TString[name].push_back(c);
}
//--------
void SignatureCutTrigger::addAcceptTrigger(TString name, TString c)
{
  if(m_accept_TString.find(name) == m_accept_TString.end()){
    vector<TString> vec;
    m_accept_TString[name] = vec;
  }
  m_accept_TString[name].push_back(c);
}
