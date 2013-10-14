void inclusiveMacro(const char* ifname="/cms/data26/srarora/Cluster/"
	, const char* ofname="example.root"
	, Int_t mode=0
	, const char* json = "/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json"
) {
	gSystem->Load("libRutgersIAF2012RootC.so");
	gROOT->ProcessLine(".include ../../CMSSW_5_2_2/src");
	gROOT->ProcessLine(".L ../helperIAF.C");
	gROOT->ProcessLine(".L helperInclusive.C+");
	gROOT->ProcessLine(".L helperFakeRate.C");
	//TFile infile(ifname);
	//TTree* tree = (TTree*)infile.Get("SkimTree");
	TChain* tree = new TChain("SkimTree");
	TString input = ifname;
	input += "/*.root";
	tree->Add(input);
	
	SignatureHandler* handler = new SignatureHandler(tree,ofname);
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
	setupInclusiveSignatures(handler);
	setupFakeRateSignatures(handler);
	
	handler->addBasicHistograms();
	
	handler->initSignatures();

	handler->eventLoop();
//	handler->eventLoop(206512, 1193402082); // passes mode 1 (MuEG); /cms/rcg/rcgray/2012/DataLinks2012/DoubleMu_DiLepSkim_18700ipb_Nov30/p17
//	handler->eventLoop(191226, 635207914); // should be mode 3 (DoubleEl); /cms/rcg/rcgray/2012/DataLinks2012/DoubleElectron_DiLepSkim_18700ipb_Nov30/p01
	
	handler->finishSignatures();
	
	std::cout << "Done, exiting ..." << std::endl;
}
