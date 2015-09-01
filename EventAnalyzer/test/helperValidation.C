#include <TF1.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableVector.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOS.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOSSF.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariablePairMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableProductAngle.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSumPT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTH1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTriggerWeight.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableAssociateVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableElectronTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMethod.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMuonTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRelIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableTauTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonSkimRecoTracks.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonElectron.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDeltaRCharge.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"



void setupMCValidation(BaseHandler* handler, bool doMatching = true) {

	
	//create PDGID and NTID variable
	handler->addEventVariable("PDGID", new EventVariableObjectVariableVector<int>("pdgId","ALLMC"));
	handler->addEventVariable("Mother_PDGID", new EventVariableObjectVariableVector<int>("motherpdgId","ALLMC"));
	handler->addEventVariable("Mother_NTID", new EventVariableObjectVariableVector<int>("MOTHER_NTID","ALLMC"));
	
	//create Mass variable
	handler->addObjectVariable("M",new ObjectVariableMethod("M", &SignatureObject::M));
	handler->addEventVariable("M", new EventVariableObjectVariableVector<double>("M","ALLMC"));
	
	//create Phi variable
	handler->addObjectVariable("PHI",new ObjectVariableMethod("PHI", &SignatureObject::Phi));
	
	//create Status variable and status3, status2, status1
	handler->addEventVariable("STATUS", new EventVariableObjectVariableVector<int>("status","ALLMC"));
	ObjectVariableValueInList<int>* status3 = new ObjectVariableValueInList<int>("status", 3);
	handler->addObjectVariable("STATUS3", status3);
	ObjectVariableValueInList<int>* status2 = new ObjectVariableValueInList<int>("status", 2);
	handler->addObjectVariable("STATUS2", status2);
	ObjectVariableValueInList<int>* status1 = new ObjectVariableValueInList<int>("status", 1);
	handler->addObjectVariable("STATUS1", status1);
	
	//MC-Leptons: PT, Eta, N
	ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
	handler->addProductSelfComparison("MCELECTRONS",deltaR0p1);
	handler->addEventVariable("ValMCelectronsPT", new EventVariableObjectVariableVector<double>("PT","MCELECTRONS"));
	handler->addEventVariable("ValMCelectronsEta", new EventVariableObjectVariableVector<double>("ETA","MCELECTRONS"));
	handler->addEventVariable("ValMCelectronsPhi", new EventVariableObjectVariableVector<double>("PHI","MCELECTRONS"));
	handler->addEventVariable("ValMCelectronsN", new EventVariableN("ValMCelectronsN","MCELECTRONS"));
	handler->addEventVariable("ValMCelectronsM", new EventVariableObjectVariableVector<double>("M","MCELECTRONS"));
	handler->addEventVariable("Mother_MCelectrons", new EventVariableObjectVariableVector<int>("motherpdgId","MCELECTRONS"));

	handler->addProductSelfComparison("MCMUONS",deltaR0p1);
	handler->addEventVariable("ValMCmuonsPT", new EventVariableObjectVariableVector<double>("PT","MCMUONS"));
	handler->addEventVariable("ValMCmuonsEta", new EventVariableObjectVariableVector<double>("ETA","MCMUONS"));
	handler->addEventVariable("ValMCmuonsPhi", new EventVariableObjectVariableVector<double>("PHI","MCMUONS"));
	handler->addEventVariable("ValMCmuonsN", new EventVariableN("ValMCmuonsN","MCMUONS"));
	handler->addEventVariable("ValMCmuonsM", new EventVariableObjectVariableVector<double>("M","MCMUONS"));
	handler->addEventVariable("Mother_MCmuons", new EventVariableObjectVariableVector<int>("motherpdgId","MCMUONS"));
	
	ObjectVariableValueInList<int>* pdgidTau = new ObjectVariableValueInList<int>("pdgId",15);
	pdgidTau->addValue(-15);
	handler->addObjectVariable("PDGIDtau",pdgidTau);
	handler->addProduct("MCtaus", "ALLMC");
	handler->addProductCut("MCtaus", "PDGIDtau");
	handler->addProductSelfComparison("MCtaus",deltaR0p1);
	handler->addEventVariable("ValMCtausPT", new EventVariableObjectVariableVector<double>("PT","MCtaus"));
	handler->addEventVariable("ValMCtausEta", new EventVariableObjectVariableVector<double>("ETA","MCtaus"));
	handler->addEventVariable("ValMCtausPhi", new EventVariableObjectVariableVector<double>("PHI","MCtaus"));
	handler->addEventVariable("ValMCtausN", new EventVariableN("ValMCtausN","MCtaus"));
	handler->addEventVariable("ValMCtausM", new EventVariableObjectVariableVector<double>("M","MCtaus"));
	handler->addEventVariable("Mother_MCtaus", new EventVariableObjectVariableVector<int>("motherpdgId","MCtaus"));
	
	//reconstructed Leptons: PT, Eta, N, Mass
	handler->addEventVariable("ValRecElectronsPT", new EventVariableObjectVariableVector<double>("PT","goodElectrons"));
	handler->addEventVariable("ValRecElectronsEta", new EventVariableObjectVariableVector<double>("ETA","goodElectrons"));
	handler->addEventVariable("ValRecElectronsPhi", new EventVariableObjectVariableVector<double>("PHI","goodElectrons"));
	handler->addEventVariable("ValRecElectronsN", new EventVariableN("ValRecElectronsN","goodElectrons"));
	handler->addEventVariable("ValRecElectronsM", new EventVariableObjectVariableVector<double>("M","goodElectrons"));

	handler->addEventVariable("ValRecMuonsPT", new EventVariableObjectVariableVector<double>("PT","goodMuons"));
	handler->addEventVariable("ValRecMuonsEta", new EventVariableObjectVariableVector<double>("ETA","goodMuons"));
	handler->addEventVariable("ValRecMuonsPhi", new EventVariableObjectVariableVector<double>("PHI","goodMuons"));
	handler->addEventVariable("ValRecMuonsN", new EventVariableN("ValRecMuonsN","goodMuons"));
	handler->addEventVariable("ValRecMuonsM", new EventVariableObjectVariableVector<double>("M","goodMuons"));
	
	handler->addEventVariable("ValRecTausPT", new EventVariableObjectVariableVector<double>("PT","goodTaus"));
	handler->addEventVariable("ValRecTausEta", new EventVariableObjectVariableVector<double>("ETA","goodTaus"));
	handler->addEventVariable("ValRecTausPhi", new EventVariableObjectVariableVector<double>("PHI","goodTaus"));
	handler->addEventVariable("ValRecTausN", new EventVariableN("ValRecTausN","goodTaus"));
	handler->addEventVariable("ValRecTausM", new EventVariableObjectVariableVector<double>("M","goodTaus"));
	
	//Matching: reconstructed <-> MC Leptons (PT, Eta, N)
	ObjectComparisonMatchDeltaRCharge* mcMatchComparison1 = new ObjectComparisonMatchDeltaRCharge(0.1);
	if (doMatching) {
		handler->addProduct("ValMatchingElectrons", "goodElectrons");
		handler->addProductComparison("ValMatchingElectrons", "MCELECTRONS", mcMatchComparison1, false);
		handler->addEventVariable("ValMatchingElectronsPT", new EventVariableObjectVariableVector<double>("PT","ValMatchingElectrons"));
		handler->addEventVariable("ValMatchingElectronsEta", new EventVariableObjectVariableVector<double>("ETA","ValMatchingElectrons"));
		handler->addEventVariable("ValMatchingElectronsPhi", new EventVariableObjectVariableVector<double>("PHI","ValMatchingElectrons"));
		handler->addEventVariable("ValMatchingElectronsN", new EventVariableN("ValMatchingElectronsN","ValMatchingElectrons"));
		handler->addEventVariable("ValMatchingElectronsM", new EventVariableObjectVariableVector<double>("M","ValMatchingElectrons"));
		
		handler->addProduct("ValMatchingMuons", "goodMuons");
		handler->addProductComparison("ValMatchingMuons", "MCMUONS", mcMatchComparison1, false);
		handler->addEventVariable("ValMatchingMuonsPT", new EventVariableObjectVariableVector<double>("PT","ValMatchingMuons"));
		handler->addEventVariable("ValMatchingMuonsEta", new EventVariableObjectVariableVector<double>("ETA","ValMatchingMuons"));
		handler->addEventVariable("ValMatchingMuonsPhi", new EventVariableObjectVariableVector<double>("PHI","ValMatchingMuons"));
		handler->addEventVariable("ValMatchingMuonsN", new EventVariableN("ValMatchingMuonsN","ValMatchingMuons"));
		handler->addEventVariable("ValMatchingMuonsM", new EventVariableObjectVariableVector<double>("M","ValMatchingMuons"));
		
		handler->addProduct("ValMatchingTaus", "goodTaus");
		handler->addProductComparison("ValMatchingTaus", "MCtaus", mcMatchComparison1, false);
		handler->addEventVariable("ValMatchingTausPT", new EventVariableObjectVariableVector<double>("PT","ValMatchingTaus"));
		handler->addEventVariable("ValMatchingTausEta", new EventVariableObjectVariableVector<double>("ETA","ValMatchingTaus"));
		handler->addEventVariable("ValMatchingTausN", new EventVariableN("ValMatchingTausN","ValMatchingTaus"));
		handler->addEventVariable("ValMatchingTausPhi", new EventVariableObjectVariableVector<double>("PHI","ValMatchingTaus"));
		handler->addEventVariable("ValMatchingTausM", new EventVariableObjectVariableVector<double>("M","ValMatchingTaus"));
	}
	
	//top quark: PT, Eta, Mass
	handler->addProduct("ValTOP", "ALLMC");
	ObjectVariableValueInList<int>* pdgidTop = new ObjectVariableValueInList<int>("pdgId",6);
	pdgidTop->addValue(-6);
	handler->addObjectVariable("PDGIDt",pdgidTop);
	handler->addProductCut("ValTOP", "PDGIDt");
	handler->addEventVariable("ValTopPT", new EventVariableObjectVariableVector<double>("PT","ValTOP"));
	handler->addEventVariable("ValTopEta", new EventVariableObjectVariableVector<double>("ETA","ValTOP"));
	handler->addEventVariable("ValTopPhi", new EventVariableObjectVariableVector<double>("PHI","ValTOP"));
	handler->addEventVariable("ValTopM", new EventVariableObjectVariableVector<double>("M","ValTOP"));
	handler->addEventVariable("ValTopN", new EventVariableN("ValTopN","ValTOP"));
	
	//bottom quark: PT, Eta, Mass; bottom with status 3
	ObjectVariableValueInList<int>* pdgidBottom = new ObjectVariableValueInList<int>("pdgId",5);
	pdgidBottom->addValue(-5);
	handler->addObjectVariable("PDGIDb",pdgidBottom);
	
	handler->addProduct("ValBOTTOM", "ALLMC");
	handler->addProductCut("ValBOTTOM", "PDGIDb");
	handler->addEventVariable("ValBottomPT", new EventVariableObjectVariableVector<double>("PT","ValBOTTOM"));
	handler->addEventVariable("ValBottomEta", new EventVariableObjectVariableVector<double>("ETA","ValBOTTOM"));
	handler->addEventVariable("ValBottomPhi", new EventVariableObjectVariableVector<double>("PHI","ValBOTTOM"));
	handler->addEventVariable("ValBottomM", new EventVariableObjectVariableVector<double>("M","ValBOTTOM"));
	handler->addEventVariable("ValBottomN", new EventVariableN("ValBottomN","ValBOTTOM"));
	handler->addEventVariable("Mother_Bottom", new EventVariableObjectVariableVector<int>("motherpdgId","ValBOTTOM"));
	
	//Bosons (Z, W, H): PT, Eta, Mass
	handler->addProduct("ValZ", "ALLMC");
	ObjectVariableValueInList<int>* pdgidZ = new ObjectVariableValueInList<int>("pdgId",23);
	handler->addObjectVariable("PDGIDZ",pdgidZ);
	handler->addProductCut("ValZ", "PDGIDZ");
	handler->addEventVariable("ValZPT", new EventVariableObjectVariableVector<double>("PT","ValZ"));
	handler->addEventVariable("ValZEta", new EventVariableObjectVariableVector<double>("ETA","ValZ"));
	handler->addEventVariable("ValZPhi", new EventVariableObjectVariableVector<double>("PHI","ValZ"));
	handler->addEventVariable("ValZM", new EventVariableObjectVariableVector<double>("M","ValZ"));
	handler->addEventVariable("ValZN", new EventVariableN("ValZN","ValZ"));
	
	handler->addProduct("ValW", "ALLMC");
	ObjectVariableValueInList<int>* pdgidW = new ObjectVariableValueInList<int>("pdgId",24);
	pdgidW->addValue(-24);
	handler->addObjectVariable("PDGIDW",pdgidW);
	handler->addProductCut("ValW", "PDGIDW");
	handler->addEventVariable("ValWPT", new EventVariableObjectVariableVector<double>("PT","ValW"));
	handler->addEventVariable("ValWEta", new EventVariableObjectVariableVector<double>("ETA","ValW"));
	handler->addEventVariable("ValWPhi", new EventVariableObjectVariableVector<double>("PHI","ValW"));
	handler->addEventVariable("ValWM", new EventVariableObjectVariableVector<double>("M","ValW"));
	handler->addEventVariable("ValWN", new EventVariableN("ValWN","ValW"));
	
	handler->addProduct("ValHiggs", "ALLMC");
	ObjectVariableValueInList<int>* pdgidHiggs = new ObjectVariableValueInList<int>("pdgId",25);
	handler->addObjectVariable("PDGIDHiggs",pdgidHiggs);
	handler->addProductCut("ValHiggs", "PDGIDHiggs");
	handler->addEventVariable("ValHiggsPT", new EventVariableObjectVariableVector<double>("PT","ValHiggs"));
	handler->addEventVariable("ValHiggsEta", new EventVariableObjectVariableVector<double>("ETA","ValHiggs"));
	handler->addEventVariable("ValHiggsPhi", new EventVariableObjectVariableVector<double>("PHI","ValHiggs"));
	handler->addEventVariable("ValHiggsM", new EventVariableObjectVariableVector<double>("M","ValHiggs"));
	handler->addEventVariable("ValHiggsN", new EventVariableN("ValHiggsN","ValHiggs"));
	
	//Number of jets
	handler->addEventVariable("ValJetsN", new EventVariableN("ValJetsN","goodJets"));
	handler->addEventVariable("ValBJetsCSVMN", new EventVariableN("ValBJetsCSVMN","bJetsCSVM"));
	handler->addEventVariable("ValBJetsCSVLN", new EventVariableN("ValBJetsCSVLN","bJetsCSVL"));
	
	//mT, MET, HT, LT, ST
	double mZ = 91;
	EventVariableMT* ValMT = new EventVariableMT("MT", mZ, "Val");
	handler->addEventVariable("ValMT",ValMT);
	
	EventVariableSumPT* ValHT = new EventVariableSumPT("HT","goodJets");
	handler->addEventVariable("ValHT",ValHT);
		
	EventVariableSumPT* ValLT = new EventVariableSumPT("LT","goodMuons");
	ValLT->addProduct("goodElectrons");
	ValLT->addProduct("goodTaus");
	handler->addEventVariable("ValLT",ValLT);
  
	EventVariableSumPT* ValST = new EventVariableSumPT("ST","goodMuons");
	ValST->addProduct("goodElectrons");
	ValST->addProduct("goodTaus");
	ValST->addProduct("goodJets");
	ValST->addProduct("MET");
	handler->addEventVariable("ValST",ValST);
	
	//Mother Z
	ObjectVariableValueInList<int>* ValMotherZ = new ObjectVariableValueInList<int>("motherpdgId",23);
	handler->addObjectVariable("ValMOTHERZ",ValMotherZ);

	handler->addProduct("ValMCelectronsFromZ","MCELECTRONS");
	handler->addProductCut("ValMCelectronsFromZ","ValMOTHERZ");
	handler->addProductSelfComparison("ValMCelectronsFromZ",deltaR0p1);
	handler->addEventVariable("ValMCelectronsFromZM", new EventVariableObjectVariableVector<double>("M","ValMCelectronsFromZ"));
	handler->addEventVariable("ValMCelectronsFromZN", new EventVariableN("ValMCelectronsFromZN","ValMCelectronsFromZ"));
	handler->addEventVariable("ValMCelectronsFromZPT", new EventVariableObjectVariableVector<double>("PT","ValMCelectronsFromZ"));
	handler->addEventVariable("ValMCelectronsFromZEta", new EventVariableObjectVariableVector<double>("ETA","ValMCelectronsFromZ"));
	handler->addEventVariable("ValMCelectronsFromZPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCelectronsFromZ"));

	handler->addProduct("ValMCmuonsFromZ","MCMUONS");
	handler->addProductCut("ValMCmuonsFromZ","ValMOTHERZ");
	handler->addProductSelfComparison("ValMCmuonsFromZ",deltaR0p1);
	handler->addEventVariable("ValMCmuonsFromZM", new EventVariableObjectVariableVector<double>("M","ValMCmuonsFromZ"));
	handler->addEventVariable("ValMCmuonsFromZN", new EventVariableN("ValMCmuonsFromZN","ValMCmuonsFromZ"));
	handler->addEventVariable("ValMCmuonsFromZPT", new EventVariableObjectVariableVector<double>("PT","ValMCmuonsFromZ"));
	handler->addEventVariable("ValMCmuonsFromZEta", new EventVariableObjectVariableVector<double>("ETA","ValMCmuonsFromZ"));
	handler->addEventVariable("ValMCmuonsFromZPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCmuonsFromZ"));
	
	handler->addProduct("ValMCtausFromZ","MCtaus");
	handler->addProductCut("ValMCtausFromZ","ValMOTHERZ");
	handler->addProductSelfComparison("ValMCtausFromZ",deltaR0p1);
	handler->addEventVariable("ValMCtausFromZM", new EventVariableObjectVariableVector<double>("M","ValMCtausFromZ"));
	handler->addEventVariable("ValMCtausFromZN", new EventVariableN("ValMCtausFromZN","ValMCtausFromZ"));
	handler->addEventVariable("ValMCtausFromZPT", new EventVariableObjectVariableVector<double>("PT","ValMCtausFromZ"));
	handler->addEventVariable("ValMCtausFromZEta", new EventVariableObjectVariableVector<double>("ETA","ValMCtausFromZ"));
	handler->addEventVariable("ValMCtausFromZPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCtausFromZ"));	
	
}



void setupMCValidationHistograms(BaseHandler* handler)
{
  handler->addHistogram(new SignatureTH2F_ObjectVariableVsObjectVariable<double,int>("PHI","status","ValZ","Z_statusVsPhi","",100,-3.142,3.142,110,-0.5,109.5));
  handler->addHistogram(new SignatureTH2F_ObjectVariableVsObjectVariable<double,int>("PHI","status","ValBOTTOM","b_statusVsPhi","",100,-3.142,3.142,110,-0.5,109.5));

}
