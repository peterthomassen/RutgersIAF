#include "RutgersIAF/EventAnalyzer/interface/AnalysisTreeWriter.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/FlatTreeReader.h"

#include "helperMiniAOD.C"

void exampleAnalysisTree(const char* ifname="in.root"
	, const char* ofname = "out.root"
	, const char* json = "/cms/thomassen/2015/Analysis/data/current.json"
	, int mode = 0
	, Int_t iLo = 0 // change this to start running here
	, Int_t iHi = 0      // change this to stop running here
	, Int_t noFakes = 0
	, bool isMC = true
) {
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
	
	bool matchingFlag = !(input.Contains("/TTJets") || input.Contains("/TTTo2L") || input.Contains("/DYJets") || input.Contains("/WWTo2L"));
	if(!single && !theory && !matchingFlag && noFakes == 0) {
		cout << "Setting fake modes ..." << endl;
		
		handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakeTracks") , "trackFakeCombination");
		handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakePhotons"), "photonFakeCombination");
//		handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakeTaus")   , "tauFakeCombination");
	}
	
//	handler->setDebugMode(true);
//	handler->addPrintModule(new PrintModuleEverything("everything"));
//	setupPrintElectrons(handler);
	
	setupProducts(handler);
	setupVariables2(handler, isMC);
	setupTriggers(handler, mode);
	if(isMC) {
		setupMCproducts(handler);
		setupMCvariables(handler, matchingFlag);
	}
	
	handler->initSignatures();
	handler->eventLoop();
//	handler->eventLoop(1, 366232);
	handler->finishSignatures();
	
	cout<<"Done, exiting ...."<<endl;
}
