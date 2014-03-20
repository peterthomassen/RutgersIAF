void inclusiveTable2012()
{
  gSystem->Load("libRutgersIAF2012ChannelMaker.so");
  gSystem->Load("libRutgersIAF2012RootC.so");
  gROOT->ProcessLine(".include ../../CMSSW_5_2_2/src");
  gROOT->ProcessLine(".L helperChannelHandler.C+");
  gROOT->ProcessLine(".L helperTable2012.C+");

  const char* ofname="example.root";

  ChannelHandler* handler = new ChannelHandler(ofname);

  addDataFiles(handler,"datafiles.list",19500.0,0.026);
  addSimulations(handler,"simufiles.list");

  int nMicro = setupInclusiveSignatures(handler, true);
  
  handler->addHistogram("MET", "PFMET");
  handler->addHistogram("HT", "HT");

  handler->addHistogram("RelIsoVsDxy_electrons", "RelIsoVsDxy_electrons");
  handler->addHistogram("RelIsoVsDxy_muons", "RelIsoVsDxy_muons");
  handler->addHistogram("RelIsoVsDxy_tracks", "RelIsoVsDxy_tracks");


  handler->initialize();
  handler->processChannels();
  int nMacro = handler->addChannels();
  cout << "Combined " << nMicro << " channels into " << nMacro << " sum channels" << endl;
  handler->finish();
}
