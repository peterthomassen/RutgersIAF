/**
 * This example macro reads WZto3LNu background from 2015 MC data 
 * and produces a file with AnalysisTree with all MC validation variables.
 * Output is used for ValidationPlotMacro.C.
*/

#include "RutgersIAF/EventAnalyzer/interface/AnalysisTreeWriter.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/FlatTreeReader.h"

// Initialization: load helpers (which will load library etc.)
#include "helperMiniAOD.C"
#include "helperValidation.C"

void exampleValidation(const char* infile = "/cms/multilepton/thomassen/2015/MCData/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1_MINIAODSIM/151030_030656/0000/results_1.root"
	, const char* outfile = "WZto3LNu_1.simulation.root"
	, int mode = 0
	, Int_t iLo = 0	// change this to start running here
	, Int_t iHi = 0	// change this to stop running here
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
	BaseHandler* handler = new BaseHandler(outfile, reader);
	
	// Tell the EventAnalyzer that we want an AnalysisTree in our output file
	AnalysisTreeWriter* writer = new AnalysisTreeWriter(handler);
	handler->setWriter(writer);
		
	// If specified, only run over a subset of events. Provide indices in iLo, iHi
	//if(iLo > 0) handler->setMode("nEntryLow", iLo);
	//if(iHi > 0) handler->setMode("nEntryHigh", iHi);
	
	// Set up leptons with quality cuts, triggers, analysis variables, ...
	setupMCproducts(handler);
	setupProducts(handler);
	setupMCvariables(handler);
	setupMCValidation(handler);
	setupVariables2(handler, isMC);
	setupTriggers(handler, mode);

	
	// And send it running ...
	handler->initSignatures();
	handler->eventLoop();
	//handler->eventLoop(run, event); // Run over a single event with given run and event number
	handler->finishSignatures();
	
	cout<<"Done, exiting ...."<<endl;
}
