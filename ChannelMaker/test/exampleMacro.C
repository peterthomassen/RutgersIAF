void exampleMacro(const char* ofname="exampleOutput.root")
{

  gSystem->Load("libRutgersIAF2012RootC.so");
  gROOT->ProcessLine(".L helperChannelHandler.C");

  ChannelHandler* handler = new ChannelHandler(ofname);

  setConstants2011(handler);

  addDataFiles2011(handler,"datafiles.list",4700.0,0.045);
  addSimulations2011(handler,"simufiles.list");

  addChannels2011(handler);

  handler->initialize();
  handler->processChannels();
  handler->addChannels();
  handler->finish();

}
