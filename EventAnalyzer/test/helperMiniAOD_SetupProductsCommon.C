//////////////////////////////////////////////////////////
//
// Matrix Method Products:
// Muons, Electrons, Taus, Jets, bJets are defined here 
//
//////////////////////////////////////////////////////////
#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_SetupObjectVariables.C"

void setupProductsCommon(BaseHandler* handler)
{
  //setupObjectVariables(handler);

  //handler->addProduct(   "ALLMUONS","ALL");
  //handler->addProductCut("ALLMUONS","isMuon");
  //handler->addProduct(   "ALLELECTRONS","ALL");
  //handler->addProductCut("ALLELECTRONS","isElectron");
  //handler->addProduct(   "ALLTAUS","ALL");
  //handler->addProductCut("ALLTAUS","isTau");
  //handler->addProduct(   "ALLJETS","ALL");
  //handler->addProductCut("ALLJETS","isJet");
  handler->addProduct(   "ALLMET","ALL");
  handler->addProductCut("ALLMET","isMET");
  handler->addProduct(   "MET","ALLMET");
  handler->addProductCut("MET","uncertaintyNoShift");
  handler->addProductCut("MET","levelType1");
  handler->addProductCut("MET","INPUTTAGslimmedMETs");
  handler->addProduct(   "ALLPHOTONS","ALL");
  handler->addProductCut("ALLPHOTONS","isPhoton");
  handler->addProduct(   "ALLTRACKS","ALL");
  handler->addProductCut("ALLTRACKS","isTrack");
  handler->addProduct(   "ALLVERTICES","ALL");
  handler->addProductCut("ALLVERTICES","isVertex");
  handler->addProduct(   "ALLTRIGGERS","ALL");
  handler->addProductCut("ALLTRIGGERS","isTrigger");
  handler->addProduct(   "ALLTRIGGEROBJECTS","ALL");
  handler->addProductCut("ALLTRIGGEROBJECTS","isTriggerObject");
  handler->addProduct(   "ALLMC","ALL");
  handler->addProductCut("ALLMC","isMC");


  // --------------------------------------------------------------------------------------------------------------
  ///////////
  ///Muons///
  ///////////
  handler->addProduct(   "basicMuons", "ALLMUONS");
  handler->addProductCut("basicMuons", "PT5");
  handler->addProductCut("basicMuons", "ETA2p4");
  handler->addProductCut("basicMuons", "MUON_dz");
  handler->addProductCut("basicMuons", "MUON_dxy");//"prompt-ness" cut
  handler->addProductCut("basicMuons", "MUON_LOOSEID");
  //
  handler->addProduct(   "nonPromptMuons", "ALLMUONS");
  handler->addProductCut("nonPromptMuons", "PT5");
  handler->addProductCut("nonPromptMuons", "ETA2p4");
  handler->addProductCut("nonPromptMuons", "MUON_dz");
  handler->addProductCut("nonPromptMuons", "MUON_nonprompt");//reversed MUON_dxy cut
  handler->addProductCut("nonPromptMuons", "MUON_LOOSEID");
  //
  handler->addProduct(   "isoNonPromptMuons", "nonPromptMuons");
  handler->addProductCut("isoNonPromptMuons", "IREL0p15");
  //
  handler->addProduct(   "nonPromptNonIsoMuons", "nonPromptMuons");
  handler->addProductCut("nonPromptNonIsoMuons", "NOTIREL0p15");
  //
  handler->addProduct(   "promptNonIsoMuons", "basicMuons");
  handler->addProductCut("promptNonIsoMuons", "NOTIREL0p15");


  // --------------------------------------------------------------------------------------------------------------
  ///////////////
  ///Electrons///
  ///////////////
  handler->addProduct(   "basicElectrons", "ALLELECTRONS");
  handler->addProductCut("basicElectrons", "PT7");
  handler->addProductCut("basicElectrons", "ETA2p5");
  handler->addProductCut("basicElectrons", "ELECTRON_dz");
  handler->addProductCut("basicElectrons", "ELECTRON_dxy");//"prompt-ness" cut 
  handler->addProductCut("basicElectrons", "ELECTRON_CUT_VETOIDNOISO");//very loose ele id, no isolation
  //
  handler->addProduct(   "nonPromptElectrons", "ALLELECTRONS");
  handler->addProductCut("nonPromptElectrons", "PT7");
  handler->addProductCut("nonPromptElectrons", "ETA2p5");
  handler->addProductCut("nonPromptElectrons", "ELECTRON_dz");
  handler->addProductCut("nonPromptElectrons", "ELECTRON_NONPROMPT");//reversed ELECTRON_dxy cut 
  //
  handler->addProduct(   "isoNonPromptElectrons", "nonPromptElectrons");
  handler->addProductCut("isoNonPromptElectrons", "ELECTRON_ISOLATED");// equal to MULTIISOM
  //
  handler->addProduct(   "nonPromptNonIsoElectrons", "nonPromptElectrons");
  handler->addProductCut("nonPromptNonIsoElectrons", "ELECTRON_NOTISOLATED");
  //
  handler->addProduct(   "promptNonIsoElectrons", "ALLELECTRONS");
  handler->addProductCut("promptNonIsoElectrons", "PT7");
  handler->addProductCut("promptNonIsoElectrons", "ETA2p5");
  handler->addProductCut("promptNonIsoElectrons", "ELECTRON_dz");
  handler->addProductCut("promptNonIsoElectrons", "ELECTRON_PROMPT");// same as ELECTRON_dxy cut 
  handler->addProductCut("promptNonIsoElectrons", "ELECTRON_NOTISOLATED");
  handler->addProductCut("promptNonIsoElectrons", "SIP3D_4sigma");


  // --------------------------------------------------------------------------------------------------------------
  //////////
  ///Taus///
  //////////
  //https://twiki.cern.ch/twiki/bin/view/CMS/TauIDRecommendation13TeV
  handler->addProduct(   "basicTaus", "ALLTAUS");
  handler->addProductCut("basicTaus", "PT20");
  handler->addProductCut("basicTaus", "ETA2p3");
  handler->addProductCut("basicTaus", "TAU_dz");
  handler->addProductCut("basicTaus", "TAU_decayModeFindingNewDMs");
  //
  handler->addProduct(   "nonIsoTaus", "basicTaus");
  handler->addProductCut("nonIsoTaus", "TAU_againstMuonTight3");
  handler->addProductCut("nonIsoTaus", "TAU_againstElectronTightMVA6");
  handler->addProductCut("nonIsoTaus", "TAU_nonbyMediumIsolationMVArun2v1DBnewDMwLT");


  // --------------------------------------------------------------------------------------------------------------
  ////////
  //Jets//
  ////////
  handler->addProduct(   "basicJets", "ALLJETS");
  handler->addProductCut("basicJets", "PT20");
  //
  handler->addProduct("hltJets",    "goodJets");
  handler->addProductCut("hltJets", "PT40");
  handler->addProductCut("hltJets", "ETA3");
  //
  handler->addProduct("hltForwardJets",    "goodForwardJets");
  handler->addProductCut("hltForwardJets", "PT40");


  // --------------------------------------------------------------------------------------------------------------
  ////////////
  ///Tracks///
  ////////////
  handler->addProduct(   "inclusiveTracks", "ALLTRACKS");
  handler->addProductCut("inclusiveTracks", "PT10");
  handler->addProductCut("inclusiveTracks", "ETA2p4");
  handler->addProductCut("inclusiveTracks", "trackHighPurity");
  handler->addProductCut("inclusiveTracks", "MUON_dz");
  handler->addProduct(   "goodInclusiveTracks", "inclusiveTracks");
  handler->addProductCut("goodInclusiveTracks", "IREL0p24");
  handler->addProductCut("goodInclusiveTracks", "TRACK_PROMPT");
  handler->addProduct(   "promptInclusiveTracks", "inclusiveTracks");
  handler->addProductCut("promptInclusiveTracks", "TRACK_PROMPT");
  handler->addProduct(   "promptNonIsoInclusiveTracks", "inclusiveTracks");
  handler->addProductCut("promptNonIsoInclusiveTracks", "NOTIREL0p24");
  handler->addProductCut("promptNonIsoInclusiveTracks", "TRACK_PROMPT");
  handler->addProduct(   "isoInclusiveTracks", "inclusiveTracks");
  handler->addProductCut("isoInclusiveTracks", "IREL0p24");
  handler->addProduct(   "isoNonPromptInclusiveTracks", "inclusiveTracks");
  handler->addProductCut("isoNonPromptInclusiveTracks", "IREL0p24");
  handler->addProductCut("isoNonPromptInclusiveTracks", "TRACK_NONPROMPT");
  // 
  handler->addProduct(   "inclusiveTracks7", "ALLTRACKS");
  handler->addProductCut("inclusiveTracks7", "PT7");
  handler->addProductCut("inclusiveTracks7", "trackHighPurity");
  handler->addProductCut("inclusiveTracks7", "MUON_dz");
  handler->addProductCut("inclusiveTracks7", "ETA2p4");
  handler->addProduct(   "promptInclusiveTracks7", "inclusiveTracks7");
  handler->addProductCut("promptInclusiveTracks7", "TRACK_PROMPT");
  handler->addProduct(   "promptIREL0p30InclusiveTracks7", "promptInclusiveTracks7");
  handler->addProductCut("promptIREL0p30InclusiveTracks7", "IREL0p30");
  handler->addProduct(   "promptNonIsoInclusiveTracks7", "inclusiveTracks7");
  handler->addProductCut("promptNonIsoInclusiveTracks7", "NOTIREL0p24");
  handler->addProductCut("promptNonIsoInclusiveTracks7", "TRACK_PROMPT");
  handler->addProduct(   "isoInclusiveTracks7", "inclusiveTracks7");
  handler->addProductCut("isoInclusiveTracks7", "IREL0p24");
  handler->addProduct(   "isoNonPromptInclusiveTracks7", "inclusiveTracks7");
  handler->addProductCut("isoNonPromptInclusiveTracks7", "IREL0p24");
  handler->addProductCut("isoNonPromptInclusiveTracks7", "TRACK_NONPROMPT");
  //
  handler->addProduct(   "basicTracksNoCleaning", "ALLTRACKS");
  handler->addProductCut("basicTracksNoCleaning", "PT10");
  handler->addProductCut("basicTracksNoCleaning", "ETA2p4");
  handler->addProductCut("basicTracksNoCleaning", "trackHighPurity");
  handler->addProductCut("basicTracksNoCleaning", "MUON_dz");
  handler->addProduct(   "basicTracks", "basicTracksNoCleaning");
  handler->addProduct(   "goodTracks", "basicTracks");
  handler->addProductCut("goodTracks", "MULTIISOL");
  handler->addProductCut("goodTracks", "TRACK_PROMPT");
  handler->addProduct(   "goodTracksNoCleaning", "basicTracksNoCleaning");
  handler->addProductCut("goodTracksNoCleaning", "IREL0p15");
  handler->addProductCut("goodTracksNoCleaning", "TRACK_PROMPT");
  handler->addProduct(   "promptTracks", "basicTracks");
  handler->addProductCut("promptTracks", "TRACK_PROMPT");
  handler->addProduct(   "promptNonIsoTracks", "basicTracks");
  handler->addProductCut("promptNonIsoTracks", "NOTIREL0p24");
  handler->addProductCut("promptNonIsoTracks", "TRACK_PROMPT");
  handler->addProduct(   "isoTracks", "basicTracks");
  handler->addProductCut("isoTracks", "IREL0p24");
  handler->addProduct(   "isoNonPromptTracks", "basicTracks");
  handler->addProductCut("isoNonPromptTracks", "IREL0p24");
  handler->addProductCut("isoNonPromptTracks", "TRACK_NONPROMPT");
  //
  handler->addProduct(   "basicTracks7", "ALLTRACKS");
  handler->addProductCut("basicTracks7", "PT7");
  handler->addProductCut("basicTracks7", "ETA2p4");
  handler->addProductCut("basicTracks7", "trackHighPurity");
  handler->addProductCut("basicTracks7", "MUON_dz");
  handler->addProduct(   "promptTracks7", "basicTracks7");
  handler->addProductCut("promptTracks7", "TRACK_PROMPT");
  handler->addProduct(   "promptNonIsoTracks7", "basicTracks7");
  handler->addProductCut("promptNonIsoTracks7", "NOTIREL0p24");
  handler->addProductCut("promptNonIsoTracks7", "TRACK_PROMPT");
  handler->addProduct(   "isoTracks7", "basicTracks7");
  handler->addProductCut("isoTracks7", "IREL0p24");
  handler->addProduct(   "isoNonPromptTracks7", "basicTracks7");
  handler->addProductCut("isoNonPromptTracks7", "IREL0p24");
  handler->addProductCut("isoNonPromptTracks7", "TRACK_NONPROMPT");


  // --------------------------------------------------------------------------------------------------------------
  /////////////
  ///Photons///
  /////////////
  handler->addProduct(   "basicPhotons", "ALLPHOTONS");
  handler->addProductCut("basicPhotons", "PT10");
  handler->addProductCut("basicPhotons", "ETA2p4");
  handler->addProductCut("basicPhotons", "PHOTON_COMBINED");// PHOTON_COMBINED cut is a subset of Loose ID cuts, so it is consistent
  //
  handler->addProduct(   "loosePhotons", "basicPhotons");
  handler->addProductCut("loosePhotons", "PHOTON_CUT_LOOSEID");
  handler->addProduct(   "mediumPhotons", "basicPhotons");
  handler->addProductCut("mediumPhotons", "PHOTON_CUT_MEDIUMID");
  handler->addProduct(   "tightPhotons", "basicPhotons");
  handler->addProductCut("tightPhotons", "PHOTON_CUT_TIGHTID");
  //
  handler->addProduct(   "goodPhotons", "loosePhotons");


  // --------------------------------------------------------------------------------------------------------------
  ///////////////
  ///Vertices////
  ///////////////
  handler->addProduct(   "recoVertices","ALLVERTICES");
  handler->addProductCut("recoVertices","VERTEX_NDOF");
  handler->addProductCut("recoVertices","VERTEX_Z");
  handler->addProductCut("recoVertices","VERTEX_NOTFAKE");
  handler->addProductCut("recoVertices","VERTEX_RHO");
  //
  handler->addProduct("recoVerticesDrCleaned","recoVertices");


  // --------------------------------------------------------------------------------------------------------------
  ///////////////
  ///Triggers////
  ///////////////
  handler->addProduct(   "goodtriggers", "ALLTRIGGERS");
  handler->addProductCut("goodtriggers", "Accepted");
  handler->addProductCut("goodtriggers", "WasRun");
  //
  handler->addProduct("goodtriggerobjects", "ALLTRIGGEROBJECTS");
  //
  //handler->addHistogram(new SignatureTH1F_TriggerName("TriggerNames","ALLTRIGGERS"));


  // --------------------------------------------------------------------------------------------------------------
  /////////////////
  ///Separations///
  /////////////////
  ObjectComparisonDeltaR* deltaR0p05 = new ObjectComparisonDeltaR(0.05);
  ObjectComparisonDeltaR* deltaR0p1  = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p2  = new ObjectComparisonDeltaR(0.2);
  ObjectComparisonDeltaR* deltaR0p3  = new ObjectComparisonDeltaR(0.3);
  ObjectComparisonDeltaR* deltaR0p4  = new ObjectComparisonDeltaR(0.4);
  //
  handler->addProductSelfComparison("recoVerticesDrCleaned",deltaR0p05);
  //
  handler->addProductComparison("basicTracks", "goodMuons",     deltaR0p3);//clean basicTracks
  handler->addProductComparison("basicTracks", "goodElectrons", deltaR0p3);
  handler->addProductComparison("basicTracks", "goodTaus",      deltaR0p3);

  handler->addProductComparison("goodPhotons", "goodMuons",     deltaR0p1);//clean goodPhotons 
  handler->addProductComparison("goodPhotons", "goodElectrons", deltaR0p1);
  handler->addProductComparison("goodPhotons", "goodTaus",      deltaR0p1);
  handler->addProductComparison("goodPhotons", "goodTracks",    deltaR0p1);

  handler->addProductComparison("basicJets",   "goodMuons",     deltaR0p3);//clean basicJets
  handler->addProductComparison("basicJets",   "goodElectrons", deltaR0p3);

  // For consistencey, these are done in helperMiniAOD_SetupProductsMatrix.C  or  helperMiniAOD_SetupProductsRA7.C
  //handler->addProductComparison("goodJets","goodMuons",deltaR0p4);
  //handler->addProductComparison("goodJets","goodElectrons",deltaR0p4);
  //handler->addProductComparison("goodForwardJets","goodMuons",deltaR0p4);
  //handler->addProductComparison("goodForwardJets","goodElectrons",deltaR0p4);
  //handler->addProductComparison("goodForwardJets","goodTaus",deltaR0p4);


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////////
  ///Derived Products////
  ///////////////////////
  handler->addProduct(   "posGoodMuons","goodMuons");
  handler->addProductCut("posGoodMuons","POSITIVE");
  handler->addProduct(   "negGoodMuons","goodMuons");
  handler->addProductCut("negGoodMuons","NEGATIVE");

  handler->addProduct(   "posGoodElectrons","goodElectrons");
  handler->addProductCut("posGoodElectrons","POSITIVE");
  handler->addProduct(   "negGoodElectrons","goodElectrons");
  handler->addProductCut("negGoodElectrons","NEGATIVE");

  handler->addProduct(   "posGoodTracks","goodTracks");
  handler->addProductCut("posGoodTracks","POSITIVE");
  handler->addProduct(   "negGoodTracks","goodTracks");
  handler->addProductCut("negGoodTracks","NEGATIVE");

}
