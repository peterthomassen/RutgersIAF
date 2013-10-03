#include "RutgersIAF2012/RootC/interface/SignatureTH2F_LJJMvsPiT.h"

ClassImp(SignatureTH2F_LJJMvsPiT)

using namespace std;

Int_t SignatureTH2F_LJJMvsPiT::Fill(BaseHandler* handler)
{
  int dummy = -1;

  vector<SignatureObject*> leptons = handler->getProduct(m_leptonProductName);
  vector<SignatureObject*> jets = handler->getProduct(m_jetProductName);
  vector<SignatureObject*> bJets;
  bool useBjets = false;
  if(m_bJetProductName != ""){
    bJets = handler->getProduct(m_bJetProductName);
    useBjets = true;
  }

  if(leptons.size() < 1)return dummy;
  if(useBjets && bJets.size() < 1)return dummy;
  if(useBjets && jets.size() < 1)return dummy;
  if(!useBjets && jets.size() < 2)return dummy;

  for(int i = 0; i < (int)leptons.size(); i++){
    for(int j = 0; j < (int)jets.size(); j++){
      if(useBjets){
	for(int k = 0; k < (int)bJets.size(); k++){
	  //float scalarPt = 0;
	  TLorentzVector totalVec;
	  totalVec += TLorentzVector(*(leptons[i]));
	  //scalarPt += leptons[i]->Pt();
	  totalVec += TLorentzVector(*(jets[j]));
	  //scalarPt += jets[j]->Pt();
	  totalVec += TLorentzVector(*(bJets[k]));
	  //scalarPt += bJets[k]->Pt();
	  //if(leptons[i]->Pt()/totalVec.M() < 0.3)continue;
	  //if(jets[j]->Pt()/totalVec.M() < 0.3)continue;
	  //if(bJets[k]->Pt()/totalVec.M() < 0.3)continue;
	  dummy = TH2F::Fill(totalVec.M(),totalVec.Pt()/totalVec.M());
	}
      }else{
	for(int k = j+1; k < (int)jets.size(); k++){
	  //float scalarPt = 0;
	  TLorentzVector totalVec;
	  totalVec += TLorentzVector(*(leptons[i]));
	  //scalarPt += leptons[i]->Pt();
	  totalVec += TLorentzVector(*(jets[j]));
	  //scalarPt += jets[j]->Pt();
	  totalVec += TLorentzVector(*(jets[k]));
	  //scalarPt += jets[k]->Pt();
	  //if(leptons[i]->Pt()/totalVec.M() < 0.3)continue;
	  //if(jets[j]->Pt()/totalVec.M() < 0.3)continue;
	  //if(jets[k]->Pt()/totalVec.M() < 0.3)continue;
	  dummy = TH2F::Fill(totalVec.M(),totalVec.Pt()/totalVec.M());
	}
      }
    }
  }

  return dummy;
}
