#include "RutgersIAF/EventAnalyzer/interface/EventVariableLeptonGenChecker.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableLeptonGenChecker)

void EventVariableLeptonGenChecker::addProduct(TString pname) {
	if(find(m_productnames.begin(), m_productnames.end(), pname) == m_productnames.end()) {
		m_productnames.push_back(pname);
	}
}

bool EventVariableLeptonGenChecker::calculate(BaseHandler* handler) {

  bool isdebug  = false;
  bool isdebug2 = false;

  // ----------------------------------------------------------------------------
  // This calculates the DRmin between a reco lepton and a gen lepton from a boson.
  // A match is declared if "recoGenDRmin<0.3".
  // ----------------------------------------------------------------------------


  // Input "BOSONS" is used for debugging only! 
  if(isdebug){
    for(int i = 0; i < (int)m_productnames.size(); i++) {
      vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
      string prodname = (string)(m_productnames[i]);
      if( prodname.find("BOSONS") == std::string::npos ) continue;
      for(int j = 0; j < (int)v.size(); j++){
	cout<<"BOSON Pt/Eta/Phi: "<<v[j]->Pt()<<"/"<<v[j]->Eta()<<"/"<<v[j]->Phi()<<endl;
      }
    }
  }


  // Store Reco Leptons
  vector<SignatureObject*> RecoLeptons;
  string RecoLeptonProductName;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find("MC") != std::string::npos ) continue;
    if( prodname.find("BOSONS") != std::string::npos ) continue;
    RecoLeptonProductName=prodname;
    for(int j = 0; j < (int)v.size(); j++){
      RecoLeptons.push_back( v[j] );
    }
  }

  // Store Gen Leptons
  vector<SignatureObject*> GenLeptons;
  vector<string> GenLeptonProductName;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find("MC") == std::string::npos ) continue;
    for(int j = 0; j < (int)v.size(); j++){
      GenLeptons.push_back( v[j] );
      if(isdebug) GenLeptonProductName.push_back(prodname);
      if(isdebug) cout<<prodname<<" Gen Pt/Eta/Phi: "<<v[j]->Pt()<<"/"<<v[j]->Eta()<<"/"<<v[j]->Phi()<<endl;
    }
  }


  // Check if Reco Leptons are Gen-matched
  vector<int> isRecoGenMatchedVector;
  TVector3 vecR, vecG;
  for(auto itR=begin(RecoLeptons); itR!=end(RecoLeptons); ++itR){
    int isMatched=0;
    double recoGenDRmin=99999;
    if(isdebug) cout<<RecoLeptonProductName<<" Reco Pt/Eta/Phi/DR: "<<(*itR)->Pt()<<"/"<<(*itR)->Eta()<<"/"<<(*itR)->Phi()<<endl;
    int prodNameIndex=0;
    for(auto itG=begin(GenLeptons); itG!=end(GenLeptons); ++itG){
      vecR.SetPtEtaPhi((*itR)->Pt(),(*itR)->Eta(),(*itR)->Phi());
      vecG.SetPtEtaPhi((*itG)->Pt(),(*itG)->Eta(),(*itG)->Phi());
      double recoGenDR=fabs(vecR.DeltaR(vecG));
      if(isdebug) cout<<"  "<<GenLeptonProductName.at(prodNameIndex)<<" Gen Pt/Eta/Phi/DR: "<<(*itG)->Pt()<<"/"<<(*itG)->Eta()<<"/"<<(*itG)->Phi()<<"/"<<recoGenDR<<endl;
      if(recoGenDR<recoGenDRmin) recoGenDRmin=recoGenDR;
      prodNameIndex++;
    }
    if(recoGenDRmin<0.3) isMatched=1;
    if(isdebug) cout<<"Reco recoGenDRmin: "<<recoGenDRmin<<endl;
    isRecoGenMatchedVector.push_back(isMatched);
  }

  TString IsGenMatched = TString::Format("IsGenMatched%s",m_suffix.Data());

  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find("MC") != std::string::npos ) continue;// only use reco lepton collection for the final tagging
    if( prodname.find("BOSONS") != std::string::npos ) continue;// only use reco lepton collection for the final tagging
    for(int j = 0; j < (int)v.size(); j++){
      v[j]->setVariable(IsGenMatched, (int)(isRecoGenMatchedVector.at(j)));
    }
  }

  GenLeptonProductName.clear();

  if(isdebug2){//check mothers of gen leptons here:
    vector<SignatureObject*> M = handler->getProduct("allmc");
    //
    for(int i = 0; i < (int)m_productnames.size(); i++) {
      vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
      string prodname = (string)(m_productnames[i]);
      if( prodname.find("MC") == std::string::npos ) continue;
      for(int j = 0; j < (int)v.size(); j++){
	int lepPdgID = 0;
	v[j]->getVariable("pdgId",lepPdgID);
	cout<<"GenLepPdgID: "<<lepPdgID<<"   Pt/Eta/Phi: "<<v[j]->Pt()<<"/"<<v[j]->Eta()<<"/"<<v[j]->Phi()<<endl;
	//
	int motherIndex = 0;
	int motherPdgID = 0;
	int stepCtr = 0;
	bool hasMother = v[j]->getVariable("motherIndex",motherIndex);//get motherIndex of gen lepton
	if(!hasMother) continue;
	M[motherIndex]->getVariable("pdgId",motherPdgID);//get motherPdgID
	cout<<"GenMotherPdgID: "<<motherPdgID<<endl;
	while( abs(motherPdgID)!=23 && abs(motherPdgID)!=24 && abs(motherPdgID)!=25 && stepCtr<30 && motherPdgID!=2212 ){
	  M[motherIndex]->getVariable("motherIndex",motherIndex);//renew motherIndex
	  M[motherIndex]->getVariable("pdgId",motherPdgID);//get new motherPdgID
	  cout<<"GenMotherPdgID: "<<motherPdgID<<endl;
	  stepCtr++;
	}
	//
      }
    }
  }


  return true;

}
