#include "RutgersIAF/EventAnalyzer/interface/AnalysisTreeWriter.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/FlatTreeReader.h"

#include "helperMiniAODv2.C"

void produceAnalysisTreev2(
			   const char* ifname = "CondorInputSamples/DoubleMuon_Run2016B-PromptReco-v2_MINIAOD/results_1.root"
			 , const char* ofname = "/tmp/hsaka/results_EAtest.root"
			 , const char*   json = "json/Cert_271036-274421_13TeV_PromptReco_Collisions16_JSON.txt"
			 , int           mode = 0       // primary dataset: 1=MUEG, 2=DOUBLEMU, 3=DOUBLEEG, 4=SINGLEMU, 5=SINGLEEL
			 , Int_t          iLo = 0       // change this to start running here
			 , Int_t          iHi = -1     // change this to stop  running here
			 , Int_t      noFakes = 1       // turns on/off the proxyMethod trees with tracks 
		         , bool          isMC = false   // turns on/off json filtering, some MC-only variables that dont exist for data, etc.
) {

        // Check if the declated variables isMC and trig-mode make sense:
	assert(!(isMC && mode > 0));
	
	TChain* tree = new TChain("tree");
	TString input = ifname;
	bool manual = input.EndsWith(".root");
	//bool single = (mode == 4 || mode == 5);//not used anymore
	bool single=false;
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

	//JSON filter
	//if(!isMC) handler->readGoodRunLumiFromJSON(TString(json));
	
	//bool matchingFlag = !(input.Contains("/TTJets") || input.Contains("/TTTo2L") || input.Contains("/DYJets") || input.Contains("/WWTo2L"));
	//bool matchingFlag = !(input.Contains("/TTJets") || input.Contains("/TTTo2L") || input.Contains("/DYJets") || input.Contains("/WWTo2L") || input.Contains("/WJets"));
	bool matchingFlag=false;//what is this?

	if(!single && !theory && !matchingFlag && noFakes == 0) {
	  cout << "Setting fake modes ..." << endl;
	  handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakeTracks") , "trackFakeCombination");
	  handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakePhotons"), "photonFakeCombination");
	  //handler->setWriter(new AnalysisTreeWriter(handler, "treeRfakeTaus")   , "tauFakeCombination");//proxy method with taus is not ready yet
        }

	//debugging	
	//handler->setDebugMode(true);
	//handler->addPrintModule(new PrintModuleEverything("everything"));
	//setupPrintElectrons(handler);

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
