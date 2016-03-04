//////////////////////////////////////////////////////////
//
// RA7 Products:
// Objects as used in he RA7 analysis are defined here.
//
//////////////////////////////////////////////////////////
#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_SetupObjectVariables.C"

void setupProductsRA7(BaseHandler* handler)
{
  setupObjectVariables(handler);

  handler->addProduct(   "ALLMUONS","ALL");
  handler->addProductCut("ALLMUONS","isMuon");

  handler->addProduct(   "ALLELECTRONS","ALL");
  handler->addProductCut("ALLELECTRONS","isElectron");

  handler->addProduct(   "ALLTAUS","ALL");
  handler->addProductCut("ALLTAUS","isTau");

  //handler->addProduct(   "ALLPHOTONS","ALL");
  //handler->addProductCut("ALLPHOTONS","isPhoton");
  //
  //handler->addProduct(   "ALLTRACKS","ALL");
  //handler->addProductCut("ALLTRACKS","isTrack");

  handler->addProduct(   "ALLJETS","ALL");
  handler->addProductCut("ALLJETS","isJet");

  //handler->addProduct(   "ALLVERTICES","ALL");
  //handler->addProductCut("ALLVERTICES","isVertex");
  //handler->addProduct("ALLRECOVERTICES","ALLVERTICES"); // fix
  //
  //handler->addProduct(   "ALLMET","ALL");
  //handler->addProductCut("ALLMET","isMET");
  //
  //handler->addProduct(   "MET","ALLMET");
  //handler->addProductCut("MET","uncertaintyNoShift");
  //handler->addProductCut("MET","levelType1");
  //handler->addProductCut("MET","INPUTTAGslimmedMETs");


  // --------------------------------------------------------------------------------------------------------------
  ///////////
  ///Muons///
  ///////////
  handler->addProduct(   "looseRA7Muons", "ALLMUONS");
  handler->addProductCut("looseRA7Muons", "PT5");
  handler->addProductCut("looseRA7Muons", "ETA2p4");
  handler->addProductCut("looseRA7Muons", "MUON_dxy");
  handler->addProductCut("looseRA7Muons", "MUON_dz");
  handler->addProductCut("looseRA7Muons", "MUON_LOOSEID");
  handler->addProductCut("looseRA7Muons", "MINIISO0p40");
  //
  handler->addProduct(   "foRA7Muons", "looseRA7Muons");
  handler->addProductCut("foRA7Muons", "MUON_MEDIUMID");
  handler->addProductCut("foRA7Muons", "SIP3D_4sigma");
  //
  handler->addProduct(   "tightRA7Muons", "foRA7Muons");
  handler->addProductCut("tightRA7Muons", "MULTIISOL");
  //
  handler->addProduct("goodMuons","tightRA7Muons");


  // --------------------------------------------------------------------------------------------------------------
  ///////////////
  ///Electrons///
  ///////////////
  handler->addProduct(   "looseRA7Electrons", "ALLELECTRONS");
  handler->addProductCut("looseRA7Electrons", "ELECTRON_MVA_RA7LOOSE");
  handler->addProductCut("looseRA7Electrons", "ELECTRON_IDemu");
  handler->addProductCut("looseRA7Electrons", "PT7");
  handler->addProductCut("looseRA7Electrons", "ETA2p5");
  handler->addProductCut("looseRA7Electrons", "ELECTRON_dz");
  handler->addProductCut("looseRA7Electrons", "ELECTRON_PROMPT");
  handler->addProductCut("looseRA7Electrons", "MINIISO0p40");
  handler->addProductCut("looseRA7Electrons", "ELECTRON_MISSINGHITS1");
  handler->addProductCut("looseRA7Electrons", "ELECTRON_passConversionVeto");
  //
  handler->addProduct(   "foRA7Electrons", "looseRA7Electrons");
  handler->addProductCut("foRA7Electrons", "ELECTRON_MVA_RA7FO");
  handler->addProductCut("foRA7Electrons", "ELECTRON_IDemu");
  handler->addProductCut("foRA7Electrons", "ELECTRON_MISSINGHITS0");
  handler->addProductCut("foRA7Electrons", "SIP3D_4sigma");
  //
  handler->addProduct(   "tightRA7Electrons", "looseRA7Electrons");
  handler->addProductCut("tightRA7Electrons", "ELECTRON_MVA_RA7TIGHT");
  handler->addProductCut("tightRA7Electrons", "ELECTRON_ISOLATED");// equal to MULTIISOM
  //
  handler->addProduct("goodElectrons","tightRA7Electrons");


  // --------------------------------------------------------------------------------------------------------------
  //////////
  ///Taus///
  //////////
  //
  //  N/A


  // --------------------------------------------------------------------------------------------------------------
  ////////
  //Jets//
  ////////
  handler->addProduct(   "RA7Jets", "ALLJETS");
  handler->addProductCut("RA7Jets", "PT30");
  handler->addProductCut("RA7Jets", "ETA2p4");
  handler->addProductCut("RA7Jets", "PFJETID_LOOSE");
  //
  handler->addProduct(   "RA7ForwardJets", "ALLJETS");//not used in the RA7 analysis, but introduced here anyway.
  handler->addProductCut("RA7ForwardJets", "PT30");
  handler->addProductCut("RA7ForwardJets", "JET_not2p4");
  handler->addProductCut("RA7ForwardJets", "PFJETID_LOOSE");
  //
  handler->addProduct(   "RA7bJetsCSVL", "RA7Jets");
  handler->addProductCut("RA7bJetsCSVL", "CSVL");
  handler->addProduct(   "RA7bJetsCSVM", "RA7Jets");
  handler->addProductCut("RA7bJetsCSVM", "CSVM");
  //
  handler->addProduct("goodJets",        "RA7Jets");
  handler->addProduct("goodForwardJets", "RA7ForwardJets");
  handler->addProduct("goodbJetsCSVL",   "RA7bJetsCSVL");
  handler->addProduct("goodbJetsCSVM",   "RA7bJetsCSVM");


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
  handler->addProductComparison("looseRA7Electrons", "looseRA7Muons",   deltaR0p05);//discard ele 
  handler->addProductComparison("RA7Jets",           "foRA7Electrons",  deltaR0p4 );//discard jet
  handler->addProductComparison("RA7Jets",           "foRA7Muons",      deltaR0p4 );//discard jet 
  handler->addProductComparison("RA7ForwardJets",    "foRA7Electrons",  deltaR0p4 );//discard jet
  handler->addProductComparison("RA7ForwardJets",    "foRA7Muons",      deltaR0p4 );//discard jet 

}
