#include "RutgersIAF2012/RootC/interface/SignatureCutNDYPairs.h"

using namespace std;

ClassImp(SignatureCutNDYPairs)

int SignatureCutNDYPairs::getCandidates(BaseHandler* handler) const
{
  m_dyCandidates.clear();
  /////////////////////////////////
  //only count electons and muons//
  /////////////////////////////////
  vector<SignatureObject*> goodElectrons = handler->getGoodElectrons();
  vector<SignatureObject*> goodMuons = handler->getGoodMuons();

  int nElp = 0;
  int nElm = 0;
  int nMup = 0;
  int nMum = 0;

  for(int i = 0; i < (int)goodElectrons.size(); i++){
    SignatureObjectElectron* electron1 = (SignatureObjectElectron*)goodElectrons[i];
    electron1->getCharge() > 0 ? nElp++ : nElm++;
    for(int j = i+1; j < (int)goodElectrons.size(); j++){
      SignatureObjectElectron* electron2 = (SignatureObjectElectron*)goodElectrons[j];
      if(fabs(electron1->getCharge() + electron2->getCharge()) > 0.01)continue;
      TLorentzVector v1(*electron1);
      TLorentzVector v2(*electron2);
      pair<SignatureObject*,SignatureObject*> newCand (electron1,electron2);
      m_dyCandidates.push_back(newCand);
    }
  }
  for(int i = 0; i < (int)goodMuons.size(); i++){
    SignatureObjectMuon* muon1 = (SignatureObjectMuon*)goodMuons[i];
    muon1->getCharge() > 0 ? nMup++ : nMum++;
    for(int j = i+1; j < (int)goodMuons.size(); j++){
      SignatureObjectMuon* muon2 = (SignatureObjectMuon*)goodMuons[j];
      if(fabs(muon1->getCharge() + muon2->getCharge()) > 0.01)continue;
      TLorentzVector v1(*muon1);
      TLorentzVector v2(*muon2);
      pair<SignatureObject*,SignatureObject*> newCand (muon1,muon2);
      m_dyCandidates.push_back(newCand);
    }
  }
  return min(nElp,nElm) + min(nMup,nMum);
}
