void inclusiveMacro(const char* ifname="/cms/data26/srarora/Cluster/"
	, const char* ofname="example.root"
	, Int_t mode=0
	, const char* json = "/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json"
) {
	gSystem->Load("libRutgersIAFRootC.so");
	gROOT->ProcessLine(".include ../../CMSSW_5_2_2/src");
	gROOT->ProcessLine(".L ../helperIAF.C");
	gROOT->ProcessLine(".L helperInclusive.C+");
	gROOT->ProcessLine(".L helperFakeRate.C");
	//TFile infile(ifname);
	//TTree* tree = (TTree*)infile.Get("SkimTree");
	TChain* tree = new TChain("SkimTree");
	TString input = ifname;
	if(!input.Contains(".root")) {
		input += "/*.root";
	}
	tree->Add(input);
	
	SignatureHandler* handler = new SignatureHandler(tree,ofname,"CREATE");
//	handler->setDebugMode();
	
	setupTriggerCut(handler,mode);
	
	handler->readGoodRunLumiFromJSON(TString(json));
	
	//addStandardThresholds(handler);
	setupProducts2012(handler);
	//addRPVSignatures(handler);
	
	//setupTestSignatures(handler);
	//addTTWSignatures(handler);
	//addTTbarSignatures(handler);
	//addMCsignatures(handler);
	
	setupHandlerCuts(handler);
	
	bool doInclusiveSignatures = true;
	bool doSeeds = true;
	bool fakeStudy = false;
	if(doInclusiveSignatures) {
		setupInclusiveSignatures(handler, doSeeds);
	}
	if(fakeStudy) {
		setupFakeRateSignatures(handler);
		setupFakeRateHistograms(handler);
	}
	
	handler->addBasicHistograms();
	
	handler->initSignatures();

	handler->eventLoop();
	
	handler->finishSignatures();
	
	std::cout << "Done, exiting ..." << std::endl;
}
