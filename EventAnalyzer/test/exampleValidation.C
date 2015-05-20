/**
 * This example macro reads ZZ background MC data and produces a file 
 * with AnalysisTree in it with all MC validation variables.
*/


void ValidationAnalysis(const char* infile = "/cms/zywicki/2012/DataLinks2012_MC_53X/ZZJetsTo4L/All/results_mc_v1_1_*.root"
	, TString pufile="/cms/matt/mwalker/Analysis/20120920_newPU/histograms/ZZJetsTo4L.pu.root"
	, const char* outfile = "validation_ZZ_1.root"
	, int mode = 0
	, Int_t iLo = 0	// change this to start running here
	, Int_t iHi = 0	// change this to stop running here
	, Bool_t isMCData = true // change this to run over MC simulations
) {
	// Initialization. Read library, set up include path, and load helpers.
	gSystem->Load("libRutgersIAFEventAnalyzer.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperValidation.C+");
	gROOT->ProcessLine(".L helperTriggers.C");
	gROOT->ProcessLine(".L helperHistograms.C+");
	
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
	
	// Tell the EventAnalyzer that we want an AnalysisTree in our output file
	AnalysisTreeWriter* writer = new AnalysisTreeWriter(handler);
	handler->setWriter(writer);
		
	// If specified, only run over a subset of events. Provide indices in iLo, iHi
	if(iLo > 0) handler->setMode("nEntryLow", iLo);
	if(iHi > 0) handler->setMode("nEntryHigh", iHi);
	
	Bool_t matchingFlag = !(input.Contains("/TTJets") || input.Contains("/DYJets") || input.Contains("Zbb"));
	Bool_t wzKinematics = input.Contains("/WZJetsTo3LNu");

	
	// Set up leptons with quality cuts, triggers, analysis variables, ...
	if (isMCData) setupMC1(handler,pufile,matchingFlag,wzKinematics);
	setupProducts(handler);
	if (isMCData) setupMC2(handler,pufile,matchingFlag);
	setupMCValidation(handler);
	setupTriggers(handler, mode);
	setupVariables(handler);
	setupFilterCuts(handler);
	
	addHistograms(handler);
	
	// And send it running ...
	handler->initSignatures();
	handler->eventLoop();
	//handler->eventLoop(run, event); // Run over a single event with given run and event number
	handler->finishSignatures();
	
	cout<<"Done, exiting ...."<<endl;
}