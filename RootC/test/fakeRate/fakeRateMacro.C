void fakeRateMacro(const char* ifname="/cms/data26/srarora/Cluster/",const char* ofname="example.root",Int_t mode=0)
{
  gSystem->Load("libRutgersIAF2012RootC.so");
  gROOT->ProcessLine(".L ../helperIAF.C");
  gROOT->ProcessLine(".L helperFakeRate.C");
  //TFile infile(ifname);
  //TTree* tree = (TTree*)infile.Get("SkimTree");
  TChain* tree = new TChain("SkimTree");
  TString input = ifname;
  input += "/*.root";
  tree->Add(input);
  
  SignatureHandler* handler = new SignatureHandler(tree,ofname);

  setupTriggerCut(handler,mode);

	handler->readGoodRunLumiFromJSON("/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json");
	
  //addStandardThresholds(handler);
  setupProducts2012(handler);
  //addRPVSignatures(handler);

  //setupTestSignatures(handler);
  //addTTWSignatures(handler);
  //addTTbarSignatures(handler);
  //addMCsignatures(handler);
  setupFakeRateSignatures(handler);

  handler->addBasicHistograms();

  handler->initSignatures();

  handler->eventLoop();

  handler->finishSignatures();

}
