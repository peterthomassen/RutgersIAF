#include "RutgersIAF2012/RootC/interface/SignatureCutTTZSelection.h"

ClassImp(SignatureCutTTZSelection)

using namespace std;

bool SignatureCutTTZSelection::passCut(BaseHandler* handler)const
{
  vector<SignatureObject*> goodElectrons = handler->getProduct("tightElectrons");
  vector<SignatureObject*> goodMuons = handler->getProduct("tightMuons");

  vector<SignatureObject*> tightElectrons = handler->getProduct("tightElectrons");
  vector<SignatureObject*> tightMuons = handler->getProduct("tightMuons");

  if(goodElectrons.size() < 2 && goodMuons.size() < 2)return false;
  if(goodElectrons.size() + goodMuons.size() != 3)return false;
  if(tightElectrons.size() < 1 && tightMuons.size() < 1)return false;

  std::vector< std::pair<SignatureObject*,SignatureObject*> > m_dyCandidates;

  for(int i = 0; i < (int)goodElectrons.size(); i++){
    SignatureObjectElectron* electron1 = (SignatureObjectElectron*)goodElectrons[i];
    for(int j = i+1; j < (int)goodElectrons.size(); j++){
      SignatureObjectElectron* electron2 = (SignatureObjectElectron*)goodElectrons[j];
      if(fabs(electron1->getCharge() + electron2->getCharge()) > 0.01)continue;
      TLorentzVector v1(*electron1);
      TLorentzVector v2(*electron2);
      if(m_removeLowM && (v1+v2).M() < m_lowMassCutOff)return false;
      if((v1+v2).M() < m_ZMassCutOffLow)continue;
      if((v1+v2).M() > m_ZMassCutOffHigh)continue;
      pair<SignatureObject*,SignatureObject*> newCand (electron1,electron2);
      m_dyCandidates.push_back(newCand);
    }
  }
  for(int i = 0; i < (int)goodMuons.size(); i++){
    SignatureObjectMuon* muon1 = (SignatureObjectMuon*)goodMuons[i];
    for(int j = i+1; j < (int)goodMuons.size(); j++){
      SignatureObjectMuon* muon2 = (SignatureObjectMuon*)goodMuons[j];
      if(fabs(muon1->getCharge() + muon2->getCharge()) > 0.01)continue;
      TLorentzVector v1(*muon1);
      TLorentzVector v2(*muon2);
      if(m_removeLowM && (v1+v2).M() < m_lowMassCutOff)return false;
      if((v1+v2).M() < m_ZMassCutOffLow)continue;
      if((v1+v2).M() > m_ZMassCutOffHigh)continue;
      pair<SignatureObject*,SignatureObject*> newCand (muon1,muon2);
      m_dyCandidates.push_back(newCand);
    }
  }

  if(m_dyCandidates.size() < 1)return false;
  int selection = 0;
  double bestMassDiff = 9999;
  for(int i = 0; i < (int)m_dyCandidates.size(); i++){
    TLorentzVector v1(*((m_dyCandidates[i]).first));
    TLorentzVector v2(*((m_dyCandidates[i]).second));
    double mass = (v1+v2).M();
    if(fabs(91.0-mass) < bestMassDiff){
      bestMassDiff = fabs(91.0-mass);
      selection = i;
    }
  }
  int nTightGood = 0;
  int foundElectron = -99;
  int foundMuon = -99;
  for(int i = 0; i < (int)tightElectrons.size(); i++){
    if(tightElectrons[i] == (m_dyCandidates[selection]).first)continue;
    if(tightElectrons[i] == (m_dyCandidates[selection]).second)continue;
    nTightGood++;
    foundElectron = i;
  }
  for(int i = 0; i < (int)tightMuons.size(); i++){
    if(tightMuons[i] == (m_dyCandidates[selection]).first)continue;
    if(tightMuons[i] == (m_dyCandidates[selection]).second)continue;
    nTightGood++;
    foundMuon = i;
  }

  if(nTightGood != 1)return false;

  //print out ttV sync line

  TString outline;
  SignatureObject* ll;
  SignatureObject* sl;
  SignatureObject* tl = 0;
  if((m_dyCandidates[selection]).first->Pt() > (m_dyCandidates[selection]).second->Pt()){
    ll = (m_dyCandidates[selection]).first;
    sl = (m_dyCandidates[selection]).second;
  }else{
    sl = (m_dyCandidates[selection]).first;
    ll = (m_dyCandidates[selection]).second;
  }
  if(foundElectron >= 0){
    tl = tightElectrons[foundElectron];
  }else if(foundMuon >= 0){
    tl = tightMuons[foundMuon];
  }

  outline = TString::Format("lkjhg%i:%li:%i:%0.3f:%0.3f:%i:%0.3f:%0.3f:%i:%0.3f:%0.3f",handler->getRun(),handler->getEvent(),ll->getPDGid(),ll->Pt(),ll->Eta(),sl->getPDGid(),sl->Pt(),sl->Eta(),tl->getPDGid(),tl->Pt(),tl->Eta());

  cout<<outline<<endl;

  return true;

}
