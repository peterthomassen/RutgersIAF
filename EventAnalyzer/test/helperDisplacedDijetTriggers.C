void setupTriggers(AdvancedHandler* handler)
{
  EventVariableThreshold* singleMuThresh = new EventVariableThreshold("smutrig","goodMuons");
  singleMuThresh->addThreshold(20);
  //handler->addEventVariable("SINGMUTRIGTHRESHOLD",singleMuThresh);

  handler->addEventVariable("HLTHT450", new EventVariableInRange<double>("HLTHT",450,1e6));
  handler->addEventVariable("MET200", new EventVariableInRange<double>("MET",200,1e6));

  ObjectVariableValueInList<TString>* isHTMETTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_PFHT350_PFMET100_v1");
  isHTMETTrigger->addValue("HLT_PFHT350_PFMET100_JetIdCleaned_v1");
  isHTMETTrigger->addValue("HLT_PFHT350_PFMET100_JetIdCleaned_v2");
  handler->addObjectVariable("isHTMETTrigger",isHTMETTrigger);

  ObjectVariableValueInList<TString>* isSingleMuTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_IsoMu20_v1");
  isSingleMuTrigger->addValue("HLT_IsoMu20_v2");
  isSingleMuTrigger->addValue("HLT_IsoMu20_v3");
  isSingleMuTrigger->addValue("HLT_IsoMu20_v4");
  isSingleMuTrigger->addValue("HLT_IsoTkMu20_v1");
  isSingleMuTrigger->addValue("HLT_IsoTkMu20_v2");
  isSingleMuTrigger->addValue("HLT_IsoTkMu20_v3");
  isSingleMuTrigger->addValue("HLT_IsoTkMu20_v4");
  handler->addObjectVariable("isSingleMuTrigger",isSingleMuTrigger);

  ObjectVariableValueInList<TString>* isSingleElTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_Ele23_WPLoose_Gsf_v1");
  isSingleElTrigger->addValue("HLT_Ele23_WPLoose_Gsf_v2");
  isSingleElTrigger->addValue("HLT_Ele23_WPLoose_Gsf_v3");
  isSingleElTrigger->addValue("HLT_Ele23_WPLoose_Gsf_v4");
  handler->addObjectVariable("isSingleElTrigger",isSingleElTrigger);

  //handler->addObjectVariable("Accepted", new ObjectVariableValue<bool>("ACCEPT", true));
  //handler->addObjectVariable("WasRun", new ObjectVariableValue<bool>("wasrun", true));

  handler->addProduct("goodtriggers", "TRIGGERS");
  handler->addProductCut("goodtriggers", "ACCEPT");
  handler->addProductCut("goodtriggers", "WASRUN");

  handler->addProduct("singleMuTriggers","goodtriggers");
  handler->addProductCut("singleMuTriggers","isSingleMuTrigger");
  handler->addEventVariable("NSingleMuTriggers", new EventVariableN("NSingleMuTriggers","singleMuTriggers"));
  handler->addEventVariable("hasSingleMuTriggers",new EventVariableInRange<int>("NSingleMuTriggers",1,10000));

  handler->addProduct("singleElTriggers","goodtriggers");
  handler->addProductCut("singleElTriggers","isSingleElTrigger");
  handler->addEventVariable("NSingleElTriggers", new EventVariableN("NSingleElTriggers","singleElTriggers"));
  handler->addEventVariable("hasSingleElTriggers",new EventVariableInRange<int>("NSingleElTriggers",1,10000));

  handler->addProduct("htmetTriggers","goodtriggers");
  handler->addProductCut("htmetTriggers","isHTMETTrigger");
  handler->addEventVariable("NHTMETTriggers",new EventVariableN("NHTMETTriggers","htmetTriggers"));
  handler->addEventVariable("hasHTMETTriggers",new EventVariableInRange<int>("NHTMETTriggers",1,10000));
  
}
