void exampleMacro(const char* ifname="."
		  , const char* ofname="exampleAnalyzer.root"
		  , int mode = 3
		  , const char* json = "/cms/thomassen/2013/tcH/RootC/Merged_190456-208686_8TeV_PromptReReco_Collisions12_19.490ifb.json"
)
{
  gSystem->Load("libRutgersIAF2012EventAnalyzer.so");
  gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
  gROOT->ProcessLine(".L helperEventAnalyzer.C+");
  gROOT->ProcessLine(".L helperTriggers.C");

  TChain* tree = new TChain("SkimTree");
  TString input=ifname;
  input += "/eve*.root";
  tree->Add(input);

  SkimTreeReader* reader = new SkimTreeReader(tree);

  BaseHandler* handler = new BaseHandler(ofname,reader);

  handler->readGoodRunLumiFromJSON(TString(json));

  //handler->setDebugMode(true);

  setupProducts(handler);
  setupTriggers(handler,mode);
  setupVariables(handler);
  setupFilterCuts(handler);
  setupSignatures(handler);
  setupOnZSignatures(handler);
  addHistograms(handler);

  handler->initSignatures();
  handler->eventLoop();
  handler->finishSignatures();

  cout<<"Done, exiting ...."<<endl;
}
