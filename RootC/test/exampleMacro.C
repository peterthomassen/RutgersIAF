void exampleMacro(const char* ifname="/cms/data26/srarora/Cluster/",const char* ofname="example.root",Int_t mode=0)
{
  gSystem->Load("libRutgersIAF2012RootC.so");
  gROOT->ProcessLine(".L helperIAF.C");
  gROOT->ProcessLine(".L ewkinoHelperIAF.C");

  //TFile infile(ifname);
  //TTree* tree = (TTree*)infile.Get("SkimTree");
  TChain* tree = new TChain("SkimTree");
  TString input = ifname;
  input += "/*.root";
  tree->Add(input);
  
  SignatureHandler* handler = new SignatureHandler(tree,ofname);

  setupTriggerCut(handler,mode);

  //addStandardThresholds(handler);
  setupStandardCuts(handler);
  //addRPVSignatures(handler);

  //setupTestSignatures(handler);
  addTTWSignatures(handler);
  addTTbarSignatures(handler);
  addMCsignatures(handler);

  handler->addBasicHistograms();

  handler->initSignatures();

  handler->eventLoop();

  handler->finishSignatures();

}
