/**
 * This example macro reads some dielectron-triggered data from the 
 * 2012 run and produces a file with a few histograms in it. The input 
 * data is in ntuple format that was used by the Rutgers multilepton 
 * group in 2012.
*/

#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SkimTreeReader.h"

// Initialization: load helpers (which will load library etc.)
#include "helperEventAnalyzer.C"
#include "helperTriggers.C"
#include "helperHistograms.C"

// Will be run for each event if added below using setHookFunction().
// Arguments should not be changed. If the second argument is non-zero, then the event is a fake event with a proxy.
// Event is skipped (i.e. not written to trees or histograms) when returning false.
bool hookFunction(BaseHandler* handler, int incarnation) {
	double MET;
	if(handler->getVariable("MET", MET)) {
		cout << "MET = " << MET << endl;
	}
	return (MET > 20);
}

void exampleHistograms(const char* infile = "/cms/rcg/rcgray/2012/DataLinks2012/DoubleElectron_missing_runs_v1_32ipb_Run2012B_Nov30/All"
	, const char* outfile = "exampleHistograms.root"
	, int mode = 0
	, const char* json = "/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json"
	, Int_t iLo = 0	// change this to start running here
	, Int_t iHi = 1000	// change this to stop running here
) {
	// Prepare input
	TChain* tree = new TChain("SkimTree");
	TString input = infile;
	if(!input.EndsWith(".root")) {
		input += "/*.root";
	}
	tree->Add(input);
	
	// Create reader
	SkimTreeReader* reader = new SkimTreeReader(tree);
	
	// Create the heart of the EventAnalyzer, the handler. Define output file and attach reader.
	BaseHandler* handler = new BaseHandler(outfile, reader);
	
	// Tell the EventAnalyzer which runs / lumi sections to use and which to ignore
	handler->readGoodRunLumiFromJSON(TString(json));
	
	// If specified, only run over a subset of events. Provide indices in iLo, iHi
	if(iLo > 0) handler->setMode("nEntryLow", iLo);
	if(iHi > 0) handler->setMode("nEntryHigh", iHi);
	
	// Debug?
	//handler->setDebugMode(true);
	
	// Set up leptons with quality cuts, triggers, analysis variables, ...
	setupProducts(handler);
	setupTriggers(handler,mode);
	setupVariables(handler);
	setupFilterCuts(handler);
	
	//setupSignatures(handler);
	setupOnZSignatures(handler);
	addHistograms(handler);

	// Hook function for each event?
	//handler->setHookFunction(&hookFunction);
	
	// And send it running ...
	handler->initSignatures();
	handler->eventLoop();
	//handler->eventLoop(run, event); // Run over a single event with given run and event number
	handler->finishSignatures();
	
	cout<<"Done, exiting ...."<<endl;
}
