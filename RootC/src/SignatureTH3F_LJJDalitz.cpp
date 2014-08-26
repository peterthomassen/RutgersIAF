#include "RutgersIAF/RootC/interface/SignatureTH3F_LJJDalitz.h"

ClassImp(SignatureTH3F_LJJDalitz)

using namespace std;

Int_t SignatureTH3F_LJJDalitz::Fill(BaseHandler* handler)
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
	  TLorentzVector lj1Vec;
	  TLorentzVector lj2Vec;
	  TLorentzVector jjVec;
	  lj1Vec += TLorentzVector(*(leptons[i]));
	  lj2Vec += TLorentzVector(*(leptons[i]));
	  jjVec += TLorentzVector(*(jets[j]));
	  jjVec += TLorentzVector(*(bJets[k]));
	  if(jets[j]->Pt() > bJets[k]->Pt()){
	    lj1Vec += TLorentzVector(*(jets[j]));
	    lj2Vec += TLorentzVector(*(bJets[k]));
	  }else{
	    lj1Vec += TLorentzVector(*(bJets[k]));
	    lj2Vec += TLorentzVector(*(jets[j]));
	  }
	  dummy = TH3F::Fill(lj1Vec.M(),lj2Vec.M(),jjVec.M());
	}
      }else{
	for(int k = j+1; k < (int)jets.size(); k++){
	  TLorentzVector lj1Vec;
	  TLorentzVector lj2Vec;
	  TLorentzVector jjVec;
	  lj1Vec += TLorentzVector(*(leptons[i]));
	  lj1Vec += TLorentzVector(*(jets[j]));
	  lj2Vec += TLorentzVector(*(leptons[i]));
	  lj2Vec += TLorentzVector(*(jets[k]));
	  jjVec += TLorentzVector(*(jets[j]));
	  jjVec += TLorentzVector(*(jets[k]));
	  dummy = TH3F::Fill(lj1Vec.M(),lj2Vec.M(),jjVec.M());
	}
      }
    }
  }

  return dummy;
}
