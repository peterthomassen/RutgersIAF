/**
 * This example macro reads some dielectron-triggered data from the 
 * 2012 run and produces a file with an AnalysisTree in it. The input 
 * data is in ntuple format that was used by the Rutgers multilepton 
 * group in 2012.
*/

void exampleAnalysisTree(const char* infile = "/cms/rcg/rcgray/2012/DataLinks2012/DoubleElectron_missing_runs_v1_32ipb_Run2012B_Nov30/All"
    , TString pufile = "PU/WZJetsTo3LNu.pu.root"
	, const char* outfile = "exampleAnalysisTree.root"
	, int mode = 0
	, const char* json = "/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json"
	, Int_t iLo = 0	// change this to start running here
	, Int_t iHi = 0	// change this to stop running here
    , Bool_t isMCData = false // change this to run over MC simulations
) {
	// Initialization. Read library, set up include path, and load helpers.
	gSystem->Load("libRutgersIAFEventAnalyzer.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperEventAnalyzer.C+");
	gROOT->ProcessLine(".L helperTriggers.C");
	
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
	
	// Tell the EventAnalyzer which runs / lumi sections to use and which to ignore
	if (!isMCData) handler->readGoodRunLumiFromJSON(TString(json));
	
	// If specified, only run over a subset of events. Provide indices in iLo, iHi
	if(iLo > 0) handler->setMode("nEntryLow", iLo);
	if(iHi > 0) handler->setMode("nEntryHigh", iHi);
	
    Bool_t matchingFlag = !(input.Contains("/TTJets") || input.Contains("/DYJets") || input.Contains("Zbb"));
    Bool_t wzKinematics = input.Contains("/WZJetsTo3LNu");

	// Debug?
	//handler->setDebugMode(true);
	
	// Set up leptons with quality cuts, triggers, analysis variables, ...
    if (isMCData) setupMC1(handler,pufile,matchingFlag,wzKinematics);
	setupProducts(handler);
    if (isMCData) setupMC2(handler,pufile,matchingFlag);
	setupTriggers(handler, mode);
	setupVariables(handler);
	setupFilterCuts(handler);
	
	// And send it running ...
	handler->initSignatures();
	handler->eventLoop();
	//handler->eventLoop(run, event); // Run over a single event with given run and event number
	handler->finishSignatures();
	
	cout<<"Done, exiting ...."<<endl;
}