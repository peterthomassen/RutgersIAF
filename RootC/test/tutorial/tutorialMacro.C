void tutorialMacro(const char* ifname="/cms/rcg/rcgray/2012/DataLinks2012/DoubleElectron_DiLepSkim_18700ipb_Nov30/All/dilepskim_TrigDiEl1DiMu0MuEl0_DoubleElectron_190456-193621_809ipb_Run2012A_Nov30_p10.root",
		   const char* ofname="example.root",
		   Int_t mode=0,
		   const char* json = "/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json"
)
{
  gSystem->Load("libRutgersIAFRootC.so");
  gROOT->ProcessLine(".L helperIAF.C");
  gROOT->ProcessLine(".L helperTutorial.C");

  TChain* tree = new TChain("SkimTree");
  TString input = ifname;
  tree->Add(input);
  
  SignatureHandler* handler = new SignatureHandler(tree,ofname);

  /////////
  //Setup//
  /////////

  //set up trigger cuts with proper veto
  setupTriggerCut(handler,mode);

  //set up products with 2012 analysis cuts
  setupProducts2012(handler);

  //read json file for good lumi
  handler->readGoodRunLumiFromJSON(TString(json));

  //add signatures for this tutorial
  addTutorialSignatures(handler);

  //set up a few histograms -- should be done after all signatures are added
  handler->addBasicHistograms();

  //add a few extra histograms -- should be done after all signatures are in
  addTutorialHistograms(handler);

  //////////////////////////////
  //Actual running of analysis//
  //////////////////////////////

  //handler some signature setup
  handler->initSignatures();

  //perform the event loop
  handler->eventLoop();

  //write histograms and clean up
  handler->finishSignatures();

}
