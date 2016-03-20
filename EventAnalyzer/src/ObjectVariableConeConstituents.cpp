#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableConeConstituents.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

ClassImp(ObjectVariableConeConstituents)

using namespace std;


bool ObjectVariableConeConstituents::calculate(SignatureObject* sigObj)
{
  bool isdebug      = true;
  //
  int    coneConstN    = 0;
  float coneConstSumEt = 0;
  
  if(m_useMatchedPFJet){
    double dRmin = 9999.0;//dummy large value
    vector<SignatureObject*> jets = m_handler->getProduct("ALL");
    // SlimmedJets are general purpose collection of AK4 jets, made from ak4PFJetsCHS, with a pT cut at 10 GeV.
    //
    for(auto const &ijet : jets){
      TString inputType;
      bool hasInputType = ijet->getVariable("INPUTTYPE",inputType);
      if( !hasInputType || inputType!="jet" ) continue;
      if( m_maxEta < fabs(ijet->Eta())   ) continue;
      if( m_minPt  > ijet->Pt()          ) continue;
      //
      if(isdebug) cout<<"ijet->Pt(): "<<ijet->Pt()<<endl;
      //
      TLorentzVector LepSubtractedJet = TLorentzVector(*ijet)-TLorentzVector(*sigObj);
      double dRJet = TLorentzVector(*sigObj).DeltaR(TLorentzVector(*ijet));
      if(isdebug) cout<<"dRmin/dRJet/m_coneVetoSize/m_coneSize: "<<dRmin<<"/"<<dRJet<<"/"<<m_coneVetoSize<<"/"<<m_coneSize<<endl;
      //find jetDRmin within the specified DR range
      if( dRJet < dRmin && dRJet > m_coneVetoSize && dRJet < m_coneSize ){
	dRmin = dRJet;
	bool hasMultiplicityName = ijet->getVariable(m_multiplicityName, coneConstN);
	if( !hasMultiplicityName ) return false;
	coneConstSumEt=ijet->Pt();
	if( m_coneVetoSize<0.4 ) coneConstSumEt=LepSubtractedJet.Pt();//correction assuming DR=0.4 jets
	// ------------------------------------------------------------------
	// Allowed multiplicityName parameters:
	//   electronMultiplicity
	//   muonMultiplicity
	//   photonMultiplicity
	//   chargedMultiplicity
	//   neutralMultiplicity
	//   chargedHadronMultiplicity
	//   neutralHadronMultiplicity
	//   numberOfConstituents (=chargedMultiplicity+neutralMultiplicity)
	// ------------------------------------------------------------------
      }
    }
  } else{
    vector<SignatureObject*> pfcands = m_handler->getProduct("ALL");
    // All candidates reconstructed by the ParticleFlow algorithm are saved in MiniAOD in the packedPFCandidates collection.
    for(auto const &ipf : pfcands){
      TString inputType;
      bool hasInputType = ipf->getVariable("INPUTTYPE",inputType);
      if( !hasInputType || inputType!="pfcand" ) continue;
      //if( !hasInputType || inputType!="pftrack" ) continue;
      if( m_minPt  > ipf->Pt()          ) continue;
      if( m_maxEta < fabs(ipf->Eta())   ) continue;
      //
      double dRpf = TLorentzVector(*sigObj).DeltaR(TLorentzVector(*ipf));
      if( dRpf > m_coneVetoSize && dRpf < m_coneSize ){//count pfcands within  the specified DR range
	coneConstN++;
	coneConstSumEt = coneConstSumEt + (float)ipf->Pt();
      }
    }
  }
  //
  if(isdebug) cout<<"    coneConstN: "<<coneConstN<<endl;
  if(isdebug) cout<<"coneConstSumEt: "<<coneConstSumEt<<endl;
  sigObj->setVariable(TString::Format("%sN",    getName().Data()),coneConstN);
  sigObj->setVariable(TString::Format("%sSUMET",getName().Data()),coneConstSumEt);
  return true;
}
