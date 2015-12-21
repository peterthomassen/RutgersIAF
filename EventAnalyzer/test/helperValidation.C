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
	
	//create Phi variable
	handler->addObjectVariable("PHI",new ObjectVariableMethod("PHI", &SignatureObject::Phi));
	
	//number of jets
	handler->addEventVariable("PHIGOODJETS", new EventVariableObjectVariableVector<double>("PHI","goodJets"));
	
	//MC-Leptons: PT, Eta, N
	ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
	
	handler->addProductSelfComparison("MCELECTRONS",deltaR0p1);
	handler->addEventVariable("MCELECTRONSPT", new EventVariableObjectVariableVector<double>("PT","MCELECTRONS"));
	handler->addEventVariable("MCELECTRONSEta", new EventVariableObjectVariableVector<double>("ETA","MCELECTRONS"));
	handler->addEventVariable("MCELECTRONSPhi", new EventVariableObjectVariableVector<double>("PHI","MCELECTRONS"));
	handler->addEventVariable("MCELECTRONSN", new EventVariableN("MCELECTRONSN","MCELECTRONS"));
	handler->addEventVariable("MCELECTRONSM", new EventVariableObjectVariableVector<double>("M","MCELECTRONS"));
	handler->addEventVariable("Mother_MCELECTRONS", new EventVariableObjectVariableVector<int>("motherpdgId","MCELECTRONS"));

	handler->addProductSelfComparison("MCMUONS",deltaR0p1);
	handler->addEventVariable("MCMUONSPT", new EventVariableObjectVariableVector<double>("PT","MCMUONS"));
	handler->addEventVariable("MCMUONSEta", new EventVariableObjectVariableVector<double>("ETA","MCMUONS"));
	handler->addEventVariable("MCMUONSPhi", new EventVariableObjectVariableVector<double>("PHI","MCMUONS"));
	handler->addEventVariable("MCMUONSN", new EventVariableN("MCMUONSN","MCMUONS"));
	handler->addEventVariable("MCMUONSM", new EventVariableObjectVariableVector<double>("M","MCMUONS"));
	handler->addEventVariable("Mother_MCMUONS", new EventVariableObjectVariableVector<int>("motherpdgId","MCMUONS"));
	
	handler->addProductSelfComparison("MCTAUS",deltaR0p1);
	handler->addEventVariable("MCTAUSPT", new EventVariableObjectVariableVector<double>("PT","MCTAUS"));
	handler->addEventVariable("MCTAUSEta", new EventVariableObjectVariableVector<double>("ETA","MCTAUS"));
	handler->addEventVariable("MCTAUSPhi", new EventVariableObjectVariableVector<double>("PHI","MCTAUS"));
	handler->addEventVariable("MCTAUSN", new EventVariableN("MCTAUSN","MCTAUS"));
	handler->addEventVariable("MCTAUSM", new EventVariableObjectVariableVector<double>("M","MCTAUS"));
	handler->addEventVariable("Mother_MCTAUS", new EventVariableObjectVariableVector<int>("motherpdgId","MCTAUS"));
	
	//reconstructed Leptons: PT, Eta, N, Mass
	handler->addEventVariable("PHIGOODELECTRONS", new EventVariableObjectVariableVector<double>("PHI","goodElectrons"));
	handler->addEventVariable("MGOODELECTRONS", new EventVariableObjectVariableVector<double>("M","goodElectrons"));

	handler->addEventVariable("PHIGOODMUONS", new EventVariableObjectVariableVector<double>("PHI","goodMuons"));
	handler->addEventVariable("MGOODMUONS", new EventVariableObjectVariableVector<double>("M","goodMuons"));
	
	handler->addEventVariable("PHIGOODTAUS", new EventVariableObjectVariableVector<double>("PHI","goodTaus"));
	handler->addEventVariable("MGOODTAUS", new EventVariableObjectVariableVector<double>("M","goodTaus"));
	
	//Matching: reconstructed <-> MC Leptons (PT, Eta, N)
	ObjectComparisonMatchDeltaRCharge* mcMatch0p1 = new ObjectComparisonMatchDeltaRCharge(0.1);
	
	handler->addProduct("MatchingElectrons", "goodElectrons");
	handler->addProductComparison("MatchingElectrons", "MCELECTRONS", mcMatch0p1, false);
	handler->addEventVariable("MatchingElectronsPT", new EventVariableObjectVariableVector<double>("PT","MatchingElectrons"));
	handler->addEventVariable("MatchingElectronsEta", new EventVariableObjectVariableVector<double>("ETA","MatchingElectrons"));
	handler->addEventVariable("MatchingElectronsPhi", new EventVariableObjectVariableVector<double>("PHI","MatchingElectrons"));
	handler->addEventVariable("MatchingElectronsN", new EventVariableN("MatchingElectronsN","MatchingElectrons"));
	handler->addEventVariable("MatchingElectronsM", new EventVariableObjectVariableVector<double>("M","MatchingElectrons"));
	
	handler->addProduct("MatchingMuons", "goodMuons");
	handler->addProductComparison("MatchingMuons", "MCMUONS", mcMatch0p1, false);
	handler->addEventVariable("MatchingMuonsPT", new EventVariableObjectVariableVector<double>("PT","MatchingMuons"));
	handler->addEventVariable("MatchingMuonsEta", new EventVariableObjectVariableVector<double>("ETA","MatchingMuons"));
	handler->addEventVariable("MatchingMuonsPhi", new EventVariableObjectVariableVector<double>("PHI","MatchingMuons"));
	handler->addEventVariable("MatchingMuonsN", new EventVariableN("MatchingMuonsN","MatchingMuons"));
	handler->addEventVariable("MatchingMuonsM", new EventVariableObjectVariableVector<double>("M","MatchingMuons"));
	
	handler->addProduct("MatchingTaus", "goodTaus");
	handler->addProductComparison("MatchingTaus", "MCTAUS", mcMatch0p1, false);
	handler->addEventVariable("MatchingTausPT", new EventVariableObjectVariableVector<double>("PT","MatchingTaus"));
	handler->addEventVariable("MatchingTausEta", new EventVariableObjectVariableVector<double>("ETA","MatchingTaus"));
	handler->addEventVariable("MatchingTausN", new EventVariableN("MatchingTausN","MatchingTaus"));
	handler->addEventVariable("MatchingTausPhi", new EventVariableObjectVariableVector<double>("PHI","MatchingTaus"));
	handler->addEventVariable("MatchingTausM", new EventVariableObjectVariableVector<double>("M","MatchingTaus"));
		
	//top quark: PT, Eta, Mass
	ObjectVariableValueInList<int>* isTop = new ObjectVariableValueInList<int>("pdgId",6);
	isTop->addValue(-6);
	handler->addObjectVariable("isTop",isTop);
	handler->addProduct("MCTOP", "ALLMC");
	handler->addProductCut("MCTOP", "isTop");
	handler->addEventVariable("MCTopPT", new EventVariableObjectVariableVector<double>("PT","MCTOP"));
	handler->addEventVariable("MCTopEta", new EventVariableObjectVariableVector<double>("ETA","MCTOP"));
	handler->addEventVariable("MCTopPhi", new EventVariableObjectVariableVector<double>("PHI","MCTOP"));
	handler->addEventVariable("MCTopM", new EventVariableObjectVariableVector<double>("M","MCTOP"));
	handler->addEventVariable("MCTopN", new EventVariableN("MCTopN","MCTOP"));
	
	//bottom quark: PT, Eta, Mass
	ObjectVariableValueInList<int>* isBottom = new ObjectVariableValueInList<int>("pdgId",5);
	isBottom->addValue(-5);
	handler->addObjectVariable("isBottom",isBottom);
	handler->addProduct("MCBOTTOM", "ALLMC");
	handler->addProductCut("MCBOTTOM", "isBottom");
	handler->addEventVariable("MCBottomPT", new EventVariableObjectVariableVector<double>("PT","MCBOTTOM"));
	handler->addEventVariable("MCBottomEta", new EventVariableObjectVariableVector<double>("ETA","MCBOTTOM"));
	handler->addEventVariable("MCBottomPhi", new EventVariableObjectVariableVector<double>("PHI","MCBOTTOM"));
	handler->addEventVariable("MCBottomM", new EventVariableObjectVariableVector<double>("M","MCBOTTOM"));
	handler->addEventVariable("MCBottomN", new EventVariableN("MCBottomN","MCBOTTOM"));
	
	//Bosons (Z, W, H): PT, Eta, Mass
	handler->addObjectVariable("isZ_Boson",new ObjectVariableValue<int>("pdgId",23));
	handler->addObjectVariable("status_62", new ObjectVariableValue<int>("status",62));
	handler->addProduct("Z_BOSON","ALLMC");
	handler->addProductCut("Z_BOSON","isZ_Boson");
	handler->addProductCut("Z_BOSON","status_62");
	handler->addEventVariable("Z_BOSONPT", new EventVariableObjectVariableVector<double>("PT","Z_BOSON"));
	handler->addEventVariable("Z_BOSONEta", new EventVariableObjectVariableVector<double>("ETA","Z_BOSON"));
	handler->addEventVariable("Z_BOSONPhi", new EventVariableObjectVariableVector<double>("PHI","Z_BOSON"));
	handler->addEventVariable("Z_BOSONM", new EventVariableObjectVariableVector<double>("M","Z_BOSON"));
	handler->addEventVariable("Z_BOSONN", new EventVariableN("Z_BOSONN","Z_BOSON"));
	
	ObjectVariableValueInList<int>* isW_Boson = new ObjectVariableValueInList<int>("pdgId",24);
	isW_Boson->addValue(-24);
	handler->addObjectVariable("isW_Boson",isW_Boson);
	handler->addProduct("W_BOSON","ALLMC");
	handler->addProductCut("W_BOSON","isW_Boson");
	handler->addProductCut("W_BOSON","status_62");
	handler->addEventVariable("W_BOSONPT", new EventVariableObjectVariableVector<double>("PT","W_BOSON"));
	handler->addEventVariable("W_BOSONEta", new EventVariableObjectVariableVector<double>("ETA","W_BOSON"));
	handler->addEventVariable("W_BOSONPhi", new EventVariableObjectVariableVector<double>("PHI","W_BOSON"));
	handler->addEventVariable("W_BOSONM", new EventVariableObjectVariableVector<double>("M","W_BOSON"));
	handler->addEventVariable("W_BOSONN", new EventVariableN("W_BOSONN","W_BOSON"));
	
	handler->addObjectVariable("isHiggs",new ObjectVariableValue<int>("pdgId",25));
	handler->addProduct("Higgs_BOSON", "ALLMC");
	handler->addProductCut("Higgs_BOSON", "isHiggs");
	handler->addEventVariable("Higgs_BOSONPT", new EventVariableObjectVariableVector<double>("PT","Higgs_BOSON"));
	handler->addEventVariable("Higgs_BOSONEta", new EventVariableObjectVariableVector<double>("ETA","Higgs_BOSON"));
	handler->addEventVariable("Higgs_BOSONPhi", new EventVariableObjectVariableVector<double>("PHI","Higgs_BOSON"));
	handler->addEventVariable("Higgs_BOSONM", new EventVariableObjectVariableVector<double>("M","Higgs_BOSON"));
	handler->addEventVariable("Higgs_BOSONN", new EventVariableN("Higgs_BOSONN","Higgs_BOSON"));	
	
	//Mother Z
	handler->addEventVariable("MCELECTRONSFROMZM", new EventVariableObjectVariableVector<double>("M","MCELECTRONSFROMZ"));
	handler->addEventVariable("MCELECTRONSFROMZN", new EventVariableN("MCELECTRONSFROMZN","MCELECTRONSFROMZ"));
	handler->addEventVariable("MCELECTRONSFROMZPT", new EventVariableObjectVariableVector<double>("PT","MCELECTRONSFROMZ"));
	handler->addEventVariable("MCELECTRONSFROMZEta", new EventVariableObjectVariableVector<double>("ETA","MCELECTRONSFROMZ"));
	handler->addEventVariable("MCELECTRONSFROMZPhi", new EventVariableObjectVariableVector<double>("PHI","MCELECTRONSFROMZ"));

	handler->addEventVariable("MCMUONSFROMZM", new EventVariableObjectVariableVector<double>("M","MCMUONSFROMZ"));
	handler->addEventVariable("MCMUONSFROMZN", new EventVariableN("MCMUONSFROMZN","MCMUONSFROMZ"));
	handler->addEventVariable("MCMUONSFROMZPT", new EventVariableObjectVariableVector<double>("PT","MCMUONSFROMZ"));
	handler->addEventVariable("MCMUONSFROMZEta", new EventVariableObjectVariableVector<double>("ETA","MCMUONSFROMZ"));
	handler->addEventVariable("MCMUONSFROMZPhi", new EventVariableObjectVariableVector<double>("PHI","MCMUONSFROMZ"));
	
	handler->addProduct("MCTAUSFROMZ","MCTAUS");
	handler->addProductCut("MCTAUSFROMZ","MOTHERZ");
	handler->addEventVariable("MCTAUSFROMZM", new EventVariableObjectVariableVector<double>("M","MCTAUSFROMZ"));
	handler->addEventVariable("MCTAUSFROMZN", new EventVariableN("MCTAUSFROMZN","MCTAUSFROMZ"));
	handler->addEventVariable("MCTAUSFROMZPT", new EventVariableObjectVariableVector<double>("PT","MCTAUSFROMZ"));
	handler->addEventVariable("MCTAUSFROMZEta", new EventVariableObjectVariableVector<double>("ETA","MCTAUSFROMZ"));
	handler->addEventVariable("MCTAUSFROMZPhi", new EventVariableObjectVariableVector<double>("PHI","MCTAUSFROMZ"));	
	
	//Mother W
	ObjectVariableValueInList<int>* MotherW = new ObjectVariableValueInList<int>("motherpdgId",24);
	MotherW->addValue(-24);
	handler->addObjectVariable("MOTHERW",MotherW);

	handler->addProduct("MCELECTRONSFROMW","MCELECTRONS");
	handler->addProductCut("MCELECTRONSFROMW","MOTHERW");
	handler->addEventVariable("MCELECTRONSFROMWM", new EventVariableObjectVariableVector<double>("M","MCELECTRONSFROMW"));
	handler->addEventVariable("MCELECTRONSFROMWN", new EventVariableN("MCELECTRONSFROMWN","MCELECTRONSFROMW"));
	handler->addEventVariable("MCELECTRONSFROMWPT", new EventVariableObjectVariableVector<double>("PT","MCELECTRONSFROMW"));
	handler->addEventVariable("MCELECTRONSFROMWEta", new EventVariableObjectVariableVector<double>("ETA","MCELECTRONSFROMW"));
	handler->addEventVariable("MCELECTRONSFROMWPhi", new EventVariableObjectVariableVector<double>("PHI","MCELECTRONSFROMW"));

	handler->addProduct("MCMUONSFROMW","MCMUONS");
	handler->addProductCut("MCMUONSFROMW","MOTHERW");
	handler->addEventVariable("MCMUONSFROMWM", new EventVariableObjectVariableVector<double>("M","MCMUONSFROMW"));
	handler->addEventVariable("MCMUONSFROMWN", new EventVariableN("MCMUONSFROMWN","MCMUONSFROMW"));
	handler->addEventVariable("MCMUONSFROMWPT", new EventVariableObjectVariableVector<double>("PT","MCMUONSFROMW"));
	handler->addEventVariable("MCMUONSFROMWEta", new EventVariableObjectVariableVector<double>("ETA","MCMUONSFROMW"));
	handler->addEventVariable("MCMUONSFROMWPhi", new EventVariableObjectVariableVector<double>("PHI","MCMUONSFROMW"));
	
	handler->addProduct("MCTAUSFROMW","MCTAUS");
	handler->addProductCut("MCTAUSFROMW","MOTHERW");
	handler->addEventVariable("MCTAUSFROMWM", new EventVariableObjectVariableVector<double>("M","MCTAUSFROMW"));
	handler->addEventVariable("MCTAUSFROMWN", new EventVariableN("MCTAUSFROMWN","MCTAUSFROMW"));
	handler->addEventVariable("MCTAUSFROMWPT", new EventVariableObjectVariableVector<double>("PT","MCTAUSFROMW"));
	handler->addEventVariable("MCTAUSFROMWEta", new EventVariableObjectVariableVector<double>("ETA","MCTAUSFROMW"));
	handler->addEventVariable("MCTAUSFROMWPhi", new EventVariableObjectVariableVector<double>("PHI","MCTAUSFROMW"));	
	
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
	
	handler->addProduct("verybasicTaus","ALLTAUS");
	handler->addProductCut("verybasicTaus","PT20");
	handler->addProductCut("verybasicTaus","ETA2p3");

	handler->addEventVariable("MuonsDz", new EventVariableObjectVariableVector<double>("dz", "verybasicMuons"));
	handler->addEventVariable("MuonsDxy", new EventVariableObjectVariableVector<double>("dxy", "verybasicMuons"));
	handler->addEventVariable("ElectronsDz", new EventVariableObjectVariableVector<double>("dz", "verybasicElectrons"));
	handler->addEventVariable("ElectronsDxy", new EventVariableObjectVariableVector<double>("dxy", "verybasicElectrons"));
	handler->addEventVariable("TausDz", new EventVariableObjectVariableVector<double>("dz", "verybasicTaus"));
}