#include "RutgersIAF/EventAnalyzer/interface/AnalysisTreeWriter.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/FlatTreeReader.h"

//#include "helperMiniAOD.C"
//#include "helperValidation.C" // redefines MCTAUS!
#include "helperMiniAODv2.C"

void exampleAnalysisTree_v2Test(
			 //const char* ifname="/afs/cern.ch/user/h/hsaka/Multilepton/TEST-Mar5/CMSSW_7_6_3_patch2/src/RootFiles/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_local_numEvent10000.root"
			 //, const char* ofname = "/afs/cern.ch/user/h/hsaka/Multilepton/TEST-Mar5/CMSSW_7_6_3_patch2/src/RootFiles/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_local_numEvent10000_EAout.root"
			 const char* ifname="/afs/cern.ch/user/h/hsaka/Multilepton/TEST-Mar5/CMSSW_7_6_3_patch2/src/RootFiles/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_local_numEvent20000.root"
                         , const char* ofname = "/afs/cern.ch/user/h/hsaka/Multilepton/TEST-Mar5/CMSSW_7_6_3_patch2/src/RootFiles/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_local_numEvent20000_EAout.root"
			 , const char* json = ""
			 , int mode = 0
			 , Int_t iLo = 0    // change this to start running here
			 , Int_t iHi = -1     // change this to stop running here
			 , Int_t noFakes = 0
			 , bool isMC = true
) {
        // Check if the declated variables isMC and trig-mode make sense:
	assert(!(isMC && mode > 0));
	
	TChain* tree = new TChain("tree");
	TString input = ifname;
	bool manual = input.EndsWith(".root");
	bool single = (mode == 4 || mode == 5);
	if(!manual) {
		input += "/*.root";
	}
	tree->Add(input);
	
	FlatTreeReader* reader = new FlatTreeReader(tree);
	
	BaseHandler* handler = new BaseHandler(ofname,reader);
	
	// If specified, only run over a subset of events
	if(iLo > 0) handler->setMode("nEntryLow", iLo);
	if(iHi > 0) handler->setMode("nEntryHigh", iHi);
	
	if(single) handler->setMode("singleGoodMuon");
	
	//handler->setMode("theoryMinituples");
	bool theory = handler->getMode("theoryMinituples"); // the mode setting is also used inside the helper

	BaseTreeWriter* writer;
	if(theory) {
		writer = new TheoryTreeWriter(handler, "tree");
	} else {
		writer = new AnalysisTreeWriter(handler);
	}
	handler->setWriter(writer);
	
	if(!isMC) handler->readGoodRunLumiFromJSON(TString(json));
	
	
	//bool matchingFlag = !(input.Contains("/TTJets") || input.Contains("/TTTo2L") || input.Contains("/DYJets") || input.Contains("/WWTo2L"));
	//bool matchingFlag = !(input.Contains("/TTJets") || input.Contains("/TTTo2L") || input.Contains("/DYJets") || input.Contains("/WWTo2L") || input.Contains("/WJets"));
	/*
	if(!single && !theory && !matchingFlag && noFakes == 0) {
		cout << "Setting fake modes ..." << endl;
		
		handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakeTracks") , "trackFakeCombination");
		handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakePhotons"), "photonFakeCombination");
//		handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakeTaus")   , "tauFakeCombination");
        }*/
	
//	handler->setDebugMode(true);
//	handler->addPrintModule(new PrintModuleEverything("everything"));
//	setupPrintElectrons(handler);
	setupProducts(handler);
	setupVariables(handler, isMC);
	setupTriggers(handler, mode);
	if(isMC) {
	  setupMCproducts(handler);
	  //setupMCvariables(handler, matchingFlag);
	  setupMCvariables(handler);
	}
	handler->initSignatures();
	handler->eventLoop();
	//handler->eventLoop(1, 366232);
	handler->finishSignatures();
	
	cout<<"Done, exiting ...."<<endl;
}
