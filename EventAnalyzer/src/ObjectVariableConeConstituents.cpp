#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableConeConstituents.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"

ClassImp(ObjectVariableConeConstituents)
using namespace std;

bool ObjectVariableConeConstituents::calculate(SignatureObject* sigObj)
{
  bool isdebug  = false;
  //
  // For PFJet matching
  int   numberOfConstituents_Jet      = 0;
  int   chargedMultiplicity_Jet       = 0;
  int   chargedHadronMultiplicity_Jet = 0;
  float corrPt_Jet                    = 0;
  double CSVbtagvalue_Jet              = 0;
  double  JPbtagvalue_Jet              = 0;
  double MVAbtagvalue_Jet              = 0;
  //
  // For PFCand matching
  int   coneConstNDR03         = 0;
  float coneConstSumEtDR03     = 0;
  int   coneConstNDR03to07     = 0;
  float coneConstSumEtDR03to07 = 0;
  int   coneConstNDR04         = 0;
  float coneConstSumEtDR04     = 0;
  int   coneConstNDR04to08     = 0;
  float coneConstSumEtDR04to08 = 0;
  int   coneConstNDR01to08     = 0;
  float coneConstSumEtDR01to08 = 0;
  int   coneConstNDR02to08     = 0;
  float coneConstSumEtDR02to08 = 0;
  //
  if(sigObj->Pt()<10) return false; //To save time - since we only care about objects with pt>10 GeV (lowest lepton pt cut)
  //
  if(m_useMatchedPFJet){
    double dRmin = 9999.0;//dummy large value
    vector<SignatureObject*> jets = m_handler->getProduct("ALL");
    // SlimmedJets are general purpose collection of AK4 jets, made from ak4PFJetsCHS, with a pT cut at 10 GeV.
    //
    for(auto const &ijet : jets){
      TString inputType;
      bool hasInputType = ijet->getVariable("INPUTTYPE",inputType);
      if( !hasInputType || inputType!="jet" ) continue;
      if( ijet->Pt() < m_minPt    ) continue;
      if( ijet->Pt() < 0.01       ) continue;//redundant protection
      if( fabs(ijet->Eta()) > 2.5 ) continue;
      //
      if(isdebug) cout<<"sigObj->Pt() / ijet->Pt() :: "<<sigObj->Pt()<<" / "<<ijet->Pt()<<endl;
      if(isdebug) cout<<"ijet->Pt(): "<<ijet->Pt()<<endl;
      //
      double dRJet=TLorentzVector(*sigObj).DeltaR(TLorentzVector(*ijet));
      //
      if(isdebug) cout<<"dRmin/dRJet: "<<dRmin<<"/"<<dRJet<<endl;
      //
      if( dRJet < dRmin ){ //find nearest jet
	dRmin = dRJet;
	bool hasMultiplicity1 = ijet->getVariable( "numberOfConstituents",      numberOfConstituents_Jet      );
	bool hasMultiplicity2 = ijet->getVariable( "chargedMultiplicity",       chargedMultiplicity_Jet       );
	bool hasMultiplicity3 = ijet->getVariable( "chargedHadronMultiplicity", chargedHadronMultiplicity_Jet );
	bool hasBtagValue1    = ijet->getVariable( "pfCombinedInclusiveSecondaryVertexV2BJetTags", CSVbtagvalue_Jet );
	bool hasBtagValue2    = ijet->getVariable( "pfJetProbabilityBJetTags",                      JPbtagvalue_Jet );
	bool hasBtagValue3    = ijet->getVariable( "pfCombinedMVAV2BJetTags",                      MVAbtagvalue_Jet );
	if( !hasBtagValue1 ) CSVbtagvalue_Jet = -1;//reduntant protection, but not sure if low pt jets have btag info
	if( !hasBtagValue2 )  JPbtagvalue_Jet = -1;//reduntant protection, but not sure if low pt jets have btag info
	if( !hasBtagValue3 ) MVAbtagvalue_Jet = -1;//reduntant protection, but not sure if low pt jets have btag info
	//
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
	if( !hasMultiplicity1 || !hasMultiplicity2 || !hasMultiplicity3 ) return false;
	//
	corrPt_Jet=ijet->Pt();
	if( dRJet<0.4 ){//jet-lep subtraction if lepton is within the jet cone.
	  TLorentzVector LepSubtractedJet = TLorentzVector(*ijet)-TLorentzVector(*sigObj);
	  if( LepSubtractedJet.Pt() <= 0  ) corrPt_Jet=0;
	  else corrPt_Jet=LepSubtractedJet.Pt();//correction assuming DR=0.4 jets
	}
      }
    }
    sigObj->setVariable(TString::Format("%sCSVBTAG",  getName().Data()), CSVbtagvalue_Jet ); 
    sigObj->setVariable(TString::Format("%sJPBTAG",   getName().Data()),  JPbtagvalue_Jet ); 
    sigObj->setVariable(TString::Format("%sMVABTAG",  getName().Data()), MVAbtagvalue_Jet ); 
    //
    sigObj->setVariable(TString::Format("%sNOOFCONST",  getName().Data()), numberOfConstituents_Jet      );
    sigObj->setVariable(TString::Format("%sCHMULT",     getName().Data()), chargedMultiplicity_Jet       );
    sigObj->setVariable(TString::Format("%sCHHADMULT",  getName().Data()), chargedHadronMultiplicity_Jet );
    sigObj->setVariable(TString::Format("%sCORRJETPT",  getName().Data()), corrPt_Jet                    );
    //
    if(isdebug) cout<<"     numberOfConstituents_Jet: "<< numberOfConstituents_Jet      <<endl;
    if(isdebug) cout<<"      chargedMultiplicity_Jet: "<< chargedMultiplicity_Jet       <<endl;
    if(isdebug) cout<<"chargedHadronMultiplicity_Jet: "<< chargedHadronMultiplicity_Jet <<endl;
    if(isdebug) cout<<"                   corrPt_Jet: "<< corrPt_Jet                    <<endl;
    if(isdebug) cout<<"             CSVbtagvalue_Jet: "<< CSVbtagvalue_Jet              <<endl;
    if(isdebug) cout<<"              JPbtagvalue_Jet: "<<  JPbtagvalue_Jet              <<endl;
    if(isdebug) cout<<"             MVAbtagvalue_Jet: "<< MVAbtagvalue_Jet              <<endl;
    // ------------------------------------------------------------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------------------------------------------------------------
  } else{
    vector<SignatureObject*> pfcands = m_handler->getProduct("ALL");
    // All candidates reconstructed by the ParticleFlow algorithm are saved in MiniAOD in the packedPFCandidates collection.
    for(auto const &ipf : pfcands){
      TString inputType;
      int     PFcharge=0;
      bool    hasInputType = ipf->getVariable("INPUTTYPE", inputType );
      bool    hasCharge    = ipf->getVariable("charge",    PFcharge  );
      if( !hasInputType || inputType!="pfcand" ) continue;
      if( ipf->Pt() < m_minPt    ) continue;
      if( m_useChargedPFOnly && hasCharge && PFcharge==0 ) continue; //skip neutral PFcands if  "m_useChargedPFOnly=true"
      if( ipf->Pt() < 0.01       ) continue;//redundant protection
      if( fabs(ipf->Eta()) > 2.5 ) continue;
      // 
     double dRpf = TLorentzVector(*sigObj).DeltaR(TLorentzVector(*ipf));
      //
      //count pfcands within the specified DR range
      if(               dRpf < 0.3 ){ coneConstNDR03++;     coneConstSumEtDR03 +=  (float)ipf->Pt(); }
      if(               dRpf < 0.4 ){ coneConstNDR04++;     coneConstSumEtDR04 +=  (float)ipf->Pt(); }
      if( dRpf > 0.3 && dRpf < 0.7 ){ coneConstNDR03to07++; coneConstSumEtDR03to07 +=  (float)ipf->Pt(); }
      if( dRpf > 0.4 && dRpf < 0.8 ){ coneConstNDR04to08++; coneConstSumEtDR04to08 +=  (float)ipf->Pt(); }
      if( dRpf > 0.1 && dRpf < 0.8 ){ coneConstNDR01to08++; coneConstSumEtDR01to08 +=  (float)ipf->Pt(); }
      if( dRpf > 0.2 && dRpf < 0.8 ){ coneConstNDR02to08++; coneConstSumEtDR02to08 +=  (float)ipf->Pt(); }
      //   
    }
    sigObj->setVariable(TString::Format("%sNDR03",         getName().Data()), coneConstNDR03          );
    sigObj->setVariable(TString::Format("%sSUMETDR03",     getName().Data()), coneConstSumEtDR03      );
    sigObj->setVariable(TString::Format("%sNDR04",         getName().Data()), coneConstNDR04          );
    sigObj->setVariable(TString::Format("%sSUMETDR04",     getName().Data()), coneConstSumEtDR04      );
    sigObj->setVariable(TString::Format("%sNDR03to07",     getName().Data()), coneConstNDR03to07      );
    sigObj->setVariable(TString::Format("%sSUMETDR03to07", getName().Data()), coneConstSumEtDR03to07  );
    sigObj->setVariable(TString::Format("%sNDR04to08",     getName().Data()), coneConstNDR04to08      );
    sigObj->setVariable(TString::Format("%sSUMETDR04to08", getName().Data()), coneConstSumEtDR04to08  );
    sigObj->setVariable(TString::Format("%sNDR01to08",     getName().Data()), coneConstNDR01to08      );
    sigObj->setVariable(TString::Format("%sSUMETDR01to08", getName().Data()), coneConstSumEtDR01to08  );
    sigObj->setVariable(TString::Format("%sNDR02to08",     getName().Data()), coneConstNDR02to08      );
    sigObj->setVariable(TString::Format("%sSUMETDR02to08", getName().Data()), coneConstSumEtDR02to08  );
    //
    if(isdebug) cout<<"        coneConstNDR03: "<< coneConstNDR03         <<endl;
    if(isdebug) cout<<"    coneConstSumEtDR03: "<< coneConstSumEtDR03     <<endl;
    if(isdebug) cout<<"        coneConstNDR04: "<< coneConstNDR04         <<endl;
    if(isdebug) cout<<"    coneConstSumEtDR04: "<< coneConstSumEtDR04     <<endl;
    if(isdebug) cout<<"    coneConstNDR03to07: "<< coneConstNDR03to07     <<endl;
    if(isdebug) cout<<"coneConstSumEtDR03to07: "<< coneConstSumEtDR03to07 <<endl;
    if(isdebug) cout<<"    coneConstNDR04to08: "<< coneConstNDR04to08     <<endl;
    if(isdebug) cout<<"coneConstSumEtDR04to08: "<< coneConstSumEtDR04to08 <<endl;
    if(isdebug) cout<<"    coneConstNDR01to08: "<< coneConstNDR01to08     <<endl;
    if(isdebug) cout<<"coneConstSumEtDR01to08: "<< coneConstSumEtDR01to08 <<endl;
    if(isdebug) cout<<"    coneConstNDR02to08: "<< coneConstNDR02to08     <<endl;
    if(isdebug) cout<<"coneConstSumEtDR02to08: "<< coneConstSumEtDR02to08 <<endl;
  }
  //
  return true;
}
