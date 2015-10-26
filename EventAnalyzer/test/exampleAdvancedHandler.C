/**
 * This example macro reads some dielectron-triggered data from the 
 * 2012 run and produces a file with an AnalysisTree in it. The input 
 * data is in ntuple format that was used by the Rutgers multilepton 
 * group in 2012.
*/

#include "RutgersIAF/EventAnalyzer/interface/AnalysisTreeWriter.h"
#include "RutgersIAF/EventAnalyzer/interface/AdvancedHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/FlatTreeReader.h"

// Initialization: load helpers (which will load library etc.)
#include "helperAdvancedMiniAOD.C"

void exampleAdvancedHandler(const char* infile = "/cms/matt/mwalker/Analysis/20140320_nftest/Simulation/WZJetsTo3LNu/results_mc_v1_1_1_lzt.root"
	, TString pufile = "/cms/matt/mwalker/Analysis/20140320_nftest/PU/WZJetsTo3LNu.pu.root" // change to an empty string "" to run without a pileup file
	, const char* outfile = "exampleAnalysisTree.root"
	, int mode = 0
	, const char* json = "/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json"
	, Int_t iLo = 0	// change this to start running here
	, Int_t iHi = 1000	// change this to stop running here
	, Bool_t isMC = true // change this to run over MC simulations
) {
	// Prepare input
	TChain* tree = new TChain("tree");
	TString input = infile;
	if(!input.EndsWith(".root")) {
		input += "/*.root";
	}
	tree->Add(input);
	
	// Create reader
	FlatTreeReader* reader = new FlatTreeReader(tree);
	
	// Create the heart of the EventAnalyzer, the handler. Define output file and attach reader.
	AdvancedHandler* handler = new AdvancedHandler(outfile, reader);
	
	// Tell the EventAnalyzer that we want an AnalysisTree in our output file
	AnalysisTreeWriter* writer = new AnalysisTreeWriter(handler);
	handler->setWriter(writer);
	
	// Tell the EventAnalyzer which runs / lumi sections to use and which to ignore
	if (!isMC) handler->readGoodRunLumiFromJSON(TString(json));
	
	// If specified, only run over a subset of events. Provide indices in iLo, iHi
	if(iLo > 0) handler->setMode("nEntryLow", iLo);
	if(iHi > 0) handler->setMode("nEntryHigh", iHi);
	
	Bool_t matchingFlag = !(input.Contains("/TTJets") || input.Contains("/DYJets") || input.Contains("Zbb"));
	Bool_t wzKinematics = input.Contains("/WZJetsTo3LNu");

	// Debug?
	//handler->setDebugMode(true);
	
	// Set up leptons with quality cuts, triggers, analysis variables, ...
	if (isMC) setupMC1(handler,pufile,matchingFlag,wzKinematics);
	setupProducts(handler);
	if (isMC) setupMC2(handler,pufile,matchingFlag);
	setupTriggers(handler, mode);
	setupVariables(handler, isMC);
	setupFilterCuts(handler);
	
	// And send it running ...
	handler->initSignatures();
	handler->eventLoop();
	//handler->eventLoop(run, event); // Run over a single event with given run and event number
	handler->finishSignatures();
	
	cout<<"Done, exiting ...."<<endl;
}
