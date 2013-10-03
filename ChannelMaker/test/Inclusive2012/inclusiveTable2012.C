void inclusiveTable2012()
{
  gSystem->Load("libRutgersIAF2012RootC.so");
  gROOT->ProcessLine(".L helperChannelHandler.C");
  gROOT->ProcessLine(".L helperTable2012.C");

  ChannelHandler* handler = new ChannelHandler(ofname);

  addDataFiles(handler,"datafiles.list",19500.0,0.026);
  addSimulations(handler,"simufiles.list");

  addInclusiveChannels2012(handler);

  handler->initialize();
  handler->processChannels();
  handler->addChannels();
  handler->finish();

}
