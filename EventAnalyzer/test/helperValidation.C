#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableVector.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSumPT.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDeltaRCharge.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableExtreme.h"


void setupMCValidation(BaseHandler* handler) {

	//create Mass variable
	handler->addObjectVariable("M",new ObjectVariableMethod("M", &SignatureObject::M));
	handler->addEventVariable("M", new EventVariableObjectVariableVector<double>("M","ALLMC"));
	
	//create Phi variable
	handler->addObjectVariable("PHI",new ObjectVariableMethod("PHI", &SignatureObject::Phi));
	
	//number of jets
	handler->addEventVariable("ValNGOODJETS", new EventVariableN("ValNGOODJETS","goodJets"));
	
	//MC-Leptons: PT, Eta, N
	ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
	
	handler->addProductSelfComparison("MCELECTRONS",deltaR0p1);
	handler->addEventVariable("ValMCELECTRONSPT", new EventVariableObjectVariableVector<double>("PT","MCELECTRONS"));
	handler->addEventVariable("ValMCELECTRONSEta", new EventVariableObjectVariableVector<double>("ETA","MCELECTRONS"));
	handler->addEventVariable("ValMCELECTRONSPhi", new EventVariableObjectVariableVector<double>("PHI","MCELECTRONS"));
	handler->addEventVariable("ValMCELECTRONSN", new EventVariableN("ValMCELECTRONSN","MCELECTRONS"));
	handler->addEventVariable("ValMCELECTRONSM", new EventVariableObjectVariableVector<double>("M","MCELECTRONS"));
	handler->addEventVariable("Mother_MCELECTRONS", new EventVariableObjectVariableVector<int>("motherpdgId","MCELECTRONS"));

	handler->addProductSelfComparison("MCMUONS",deltaR0p1);
	handler->addEventVariable("ValMCMUONSPT", new EventVariableObjectVariableVector<double>("PT","MCMUONS"));
	handler->addEventVariable("ValMCMUONSEta", new EventVariableObjectVariableVector<double>("ETA","MCMUONS"));
	handler->addEventVariable("ValMCMUONSPhi", new EventVariableObjectVariableVector<double>("PHI","MCMUONS"));
	handler->addEventVariable("ValMCMUONSN", new EventVariableN("ValMCMUONSN","MCMUONS"));
	handler->addEventVariable("ValMCMUONSM", new EventVariableObjectVariableVector<double>("M","MCMUONS"));
	handler->addEventVariable("Mother_MCMUONS", new EventVariableObjectVariableVector<int>("motherpdgId","MCMUONS"));
	
	handler->addProductSelfComparison("MCTAUS",deltaR0p1);
	handler->addEventVariable("ValMCTAUSPT", new EventVariableObjectVariableVector<double>("PT","MCTAUS"));
	handler->addEventVariable("ValMCTAUSEta", new EventVariableObjectVariableVector<double>("ETA","MCTAUS"));
	handler->addEventVariable("ValMCTAUSPhi", new EventVariableObjectVariableVector<double>("PHI","MCTAUS"));
	handler->addEventVariable("ValMCTAUSN", new EventVariableN("ValMCTAUSN","MCTAUS"));
	handler->addEventVariable("ValMCTAUSM", new EventVariableObjectVariableVector<double>("M","MCTAUS"));
	handler->addEventVariable("Mother_MCTAUS", new EventVariableObjectVariableVector<int>("motherpdgId","MCTAUS"));
	
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
	ObjectComparisonMatchDeltaRCharge* mcMatch0p1 = new ObjectComparisonMatchDeltaRCharge(0.1);
	
	handler->addProduct("ValMatchingElectrons", "goodElectrons");
	handler->addProductComparison("ValMatchingElectrons", "MCELECTRONS", mcMatch0p1, false);
	handler->addEventVariable("ValMatchingElectronsPT", new EventVariableObjectVariableVector<double>("PT","ValMatchingElectrons"));
	handler->addEventVariable("ValMatchingElectronsEta", new EventVariableObjectVariableVector<double>("ETA","ValMatchingElectrons"));
	handler->addEventVariable("ValMatchingElectronsPhi", new EventVariableObjectVariableVector<double>("PHI","ValMatchingElectrons"));
	handler->addEventVariable("ValMatchingElectronsN", new EventVariableN("ValMatchingElectronsN","ValMatchingElectrons"));
	handler->addEventVariable("ValMatchingElectronsM", new EventVariableObjectVariableVector<double>("M","ValMatchingElectrons"));
	
	handler->addProduct("ValMatchingMuons", "goodMuons");
	handler->addProductComparison("ValMatchingMuons", "MCMUONS", mcMatch0p1, false);
	handler->addEventVariable("ValMatchingMuonsPT", new EventVariableObjectVariableVector<double>("PT","ValMatchingMuons"));
	handler->addEventVariable("ValMatchingMuonsEta", new EventVariableObjectVariableVector<double>("ETA","ValMatchingMuons"));
	handler->addEventVariable("ValMatchingMuonsPhi", new EventVariableObjectVariableVector<double>("PHI","ValMatchingMuons"));
	handler->addEventVariable("ValMatchingMuonsN", new EventVariableN("ValMatchingMuonsN","ValMatchingMuons"));
	handler->addEventVariable("ValMatchingMuonsM", new EventVariableObjectVariableVector<double>("M","ValMatchingMuons"));
	
	handler->addProduct("ValMatchingTaus", "goodTaus");
	handler->addProductComparison("ValMatchingTaus", "MCTAUS", mcMatch0p1, false);
	handler->addEventVariable("ValMatchingTausPT", new EventVariableObjectVariableVector<double>("PT","ValMatchingTaus"));
	handler->addEventVariable("ValMatchingTausEta", new EventVariableObjectVariableVector<double>("ETA","ValMatchingTaus"));
	handler->addEventVariable("ValMatchingTausN", new EventVariableN("ValMatchingTausN","ValMatchingTaus"));
	handler->addEventVariable("ValMatchingTausPhi", new EventVariableObjectVariableVector<double>("PHI","ValMatchingTaus"));
	handler->addEventVariable("ValMatchingTausM", new EventVariableObjectVariableVector<double>("M","ValMatchingTaus"));
		
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
	
	//bottom quark: PT, Eta, Mass
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
	
	//Mother Z
	ObjectVariableValueInList<int>* ValMotherZ = new ObjectVariableValueInList<int>("motherpdgId",23);
	handler->addObjectVariable("ValMOTHERZ",ValMotherZ);

	handler->addProduct("ValMCELECTRONSFromZ","MCELECTRONS");
	handler->addProductCut("ValMCELECTRONSFromZ","ValMOTHERZ");
	handler->addProductSelfComparison("ValMCELECTRONSFromZ",deltaR0p1);
	handler->addEventVariable("ValMCELECTRONSFromZM", new EventVariableObjectVariableVector<double>("M","ValMCELECTRONSFromZ"));
	handler->addEventVariable("ValMCELECTRONSFromZN", new EventVariableN("ValMCELECTRONSFromZN","ValMCELECTRONSFromZ"));
	handler->addEventVariable("ValMCELECTRONSFromZPT", new EventVariableObjectVariableVector<double>("PT","ValMCELECTRONSFromZ"));
	handler->addEventVariable("ValMCELECTRONSFromZEta", new EventVariableObjectVariableVector<double>("ETA","ValMCELECTRONSFromZ"));
	handler->addEventVariable("ValMCELECTRONSFromZPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCELECTRONSFromZ"));

	handler->addProduct("ValMCMUONSFromZ","MCMUONS");
	handler->addProductCut("ValMCMUONSFromZ","ValMOTHERZ");
	handler->addProductSelfComparison("ValMCMUONSFromZ",deltaR0p1);
	handler->addEventVariable("ValMCMUONSFromZM", new EventVariableObjectVariableVector<double>("M","ValMCMUONSFromZ"));
	handler->addEventVariable("ValMCMUONSFromZN", new EventVariableN("ValMCMUONSFromZN","ValMCMUONSFromZ"));
	handler->addEventVariable("ValMCMUONSFromZPT", new EventVariableObjectVariableVector<double>("PT","ValMCMUONSFromZ"));
	handler->addEventVariable("ValMCMUONSFromZEta", new EventVariableObjectVariableVector<double>("ETA","ValMCMUONSFromZ"));
	handler->addEventVariable("ValMCMUONSFromZPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCMUONSFromZ"));
	
	handler->addProduct("ValMCTAUSFromZ","MCTAUS");
	handler->addProductCut("ValMCTAUSFromZ","ValMOTHERZ");
	handler->addProductSelfComparison("ValMCTAUSFromZ",deltaR0p1);
	handler->addEventVariable("ValMCTAUSFromZM", new EventVariableObjectVariableVector<double>("M","ValMCTAUSFromZ"));
	handler->addEventVariable("ValMCTAUSFromZN", new EventVariableN("ValMCTAUSFromZN","ValMCTAUSFromZ"));
	handler->addEventVariable("ValMCTAUSFromZPT", new EventVariableObjectVariableVector<double>("PT","ValMCTAUSFromZ"));
	handler->addEventVariable("ValMCTAUSFromZEta", new EventVariableObjectVariableVector<double>("ETA","ValMCTAUSFromZ"));
	handler->addEventVariable("ValMCTAUSFromZPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCTAUSFromZ"));	
	
	//Mother W
	ObjectVariableValueInList<int>* ValMotherW = new ObjectVariableValueInList<int>("motherpdgId",24);
	ValMotherW->addValue(-24);
	handler->addObjectVariable("ValMOTHERW",ValMotherW);

	handler->addProduct("ValMCELECTRONSFromW","MCELECTRONS");
	handler->addProductCut("ValMCELECTRONSFromW","ValMOTHERW");
	handler->addProductSelfComparison("ValMCELECTRONSFromW",deltaR0p1);
	handler->addEventVariable("ValMCELECTRONSFromWM", new EventVariableObjectVariableVector<double>("M","ValMCELECTRONSFromW"));
	handler->addEventVariable("ValMCELECTRONSFromWN", new EventVariableN("ValMCELECTRONSFromWN","ValMCELECTRONSFromW"));
	handler->addEventVariable("ValMCELECTRONSFromWPT", new EventVariableObjectVariableVector<double>("PT","ValMCELECTRONSFromW"));
	handler->addEventVariable("ValMCELECTRONSFromWEta", new EventVariableObjectVariableVector<double>("ETA","ValMCELECTRONSFromW"));
	handler->addEventVariable("ValMCELECTRONSFromWPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCELECTRONSFromW"));

	handler->addProduct("ValMCMUONSFromW","MCMUONS");
	handler->addProductCut("ValMCMUONSFromW","ValMOTHERW");
	handler->addProductSelfComparison("ValMCMUONSFromW",deltaR0p1);
	handler->addEventVariable("ValMCMUONSFromWM", new EventVariableObjectVariableVector<double>("M","ValMCMUONSFromW"));
	handler->addEventVariable("ValMCMUONSFromWN", new EventVariableN("ValMCMUONSFromWN","ValMCMUONSFromW"));
	handler->addEventVariable("ValMCMUONSFromWPT", new EventVariableObjectVariableVector<double>("PT","ValMCMUONSFromW"));
	handler->addEventVariable("ValMCMUONSFromWEta", new EventVariableObjectVariableVector<double>("ETA","ValMCMUONSFromW"));
	handler->addEventVariable("ValMCMUONSFromWPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCMUONSFromW"));
	
	handler->addProduct("ValMCTAUSFromW","MCTAUS");
	handler->addProductCut("ValMCTAUSFromW","ValMOTHERW");
	handler->addProductSelfComparison("ValMCTAUSFromW",deltaR0p1);
	handler->addEventVariable("ValMCTAUSFromWM", new EventVariableObjectVariableVector<double>("M","ValMCTAUSFromW"));
	handler->addEventVariable("ValMCTAUSFromWN", new EventVariableN("ValMCTAUSFromWN","ValMCTAUSFromW"));
	handler->addEventVariable("ValMCTAUSFromWPT", new EventVariableObjectVariableVector<double>("PT","ValMCTAUSFromW"));
	handler->addEventVariable("ValMCTAUSFromWEta", new EventVariableObjectVariableVector<double>("ETA","ValMCTAUSFromW"));
	handler->addEventVariable("ValMCTAUSFromWPhi", new EventVariableObjectVariableVector<double>("PHI","ValMCTAUSFromW"));	
	
	//dz and dxy
	handler->addProduct("verybasicMuons","ALLMUONS");
	handler->addProductCut("verybasicMuons","PT5");
	handler->addProductCut("verybasicMuons","ETA2p4");
	handler->addProductCut("verybasicMuons","isPFMuon");
	handler->addProductCut("verybasicMuons","MUON_GLOBALORTRACKER");
	
	handler->addProduct("verybasicElectrons","ALLELECTRONS");
	handler->addProductCut("verybasicElectrons", "ELECTRON_MVA_LOOSE");
	handler->addProductCut("verybasicElectrons", "PT7");
	handler->addProductCut("verybasicElectrons", "ETA2p5");

	handler->addEventVariable("ValMuonsDz", new EventVariableObjectVariableVector<double>("dz", "verybasicMuons"));
	handler->addEventVariable("ValMuonsDxy", new EventVariableObjectVariableVector<double>("dxy", "verybasicMuons"));
	handler->addEventVariable("ValElectronsDz", new EventVariableObjectVariableVector<double>("dz", "verybasicElectrons"));
	handler->addEventVariable("ValElectronsDxy", new EventVariableObjectVariableVector<double>("dxy", "verybasicElectrons"));
}