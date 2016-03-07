//////////////////////////////////////////////////////////
//
// Matrix Method Products:
// Objects as used in the Multilepton - Matrix Method analysis are defined here.
//
//////////////////////////////////////////////////////////
//#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_SetupObjectVariables.C"

void setupProductsMatrix(BaseHandler* handler)
{
  setupObjectVariables(handler);

  handler->addProduct(   "ALLMUONS","ALL");
  handler->addProductCut("ALLMUONS","isMuon");
  handler->addProduct(   "ALLELECTRONS","ALL");
  handler->addProductCut("ALLELECTRONS","isElectron");
  handler->addProduct(   "ALLTAUS","ALL");
  handler->addProductCut("ALLTAUS","isTau");
  handler->addProduct(   "ALLJETS","ALL");
  handler->addProductCut("ALLJETS","isJet");


  // --------------------------------------------------------------------------------------------------------------
  ///////////
  ///Muons///
  ///////////
  handler->addProduct(   "looseMatrixMuons", "ALLMUONS");
  handler->addProductCut("looseMatrixMuons", "PT10");
  handler->addProductCut("looseMatrixMuons", "ETA2p4");
  handler->addProductCut("looseMatrixMuons", "MUON_dxy");
  handler->addProductCut("looseMatrixMuons", "MUON_dz");
  handler->addProductCut("looseMatrixMuons", "MUON_MEDIUMID");
  //
  handler->addProduct(   "tightMatrixMuons", "looseMatrixMuons");
  handler->addProductCut("tightMatrixMuons", "MUON_IREL0p25");
  //
  handler->addProduct("goodMuons","looseMatrixMuons");


  // --------------------------------------------------------------------------------------------------------------
  ///////////////
  ///Electrons///
  ///////////////
  // https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Spring15_selection_25ns
  // https://indico.cern.ch/event/370507/contribution/1/attachments/1140657/1633761/Rami_eleCB_ID_25ns.pdf
  handler->addProduct(   "looseMatrixElectrons", "ALLELECTRONS");
  handler->addProductCut("looseMatrixElectrons", "PT10");
  handler->addProductCut("looseMatrixElectrons", "ETA2p5");
  handler->addProductCut("looseMatrixElectrons", "ELECTRON_CUTIDLOOSENOISO");
  //
  handler->addProduct(   "tightMatrixElectrons", "looseMatrixElectrons");
  handler->addProductCut("tightMatrixElectrons", "ELECTRON_CUT_LOOSEID");
  //
  // https://twiki.cern.ch/twiki/bin/view/CMS/HEEPElectronIdentificationRun2#Selection_Cuts_HEEP_V6_0_Recomme
  handler->addProduct(   "heepIDElectrons", "ALLELECTRONS");
  handler->addProductCut("heepIDElectrons", "PT35");
  handler->addProductCut("heepIDElectrons", "ETA2p5");
  handler->addProductCut("heepIDElectrons", "ELECTRON_HEEPID");
  //
  handler->addProduct("goodElectrons","looseMatrixElectrons");


  // --------------------------------------------------------------------------------------------------------------
  //////////
  ///Taus///
  //////////
  //https://twiki.cern.ch/twiki/bin/view/CMS/TauIDRecommendation13TeV
  handler->addProduct(   "looseMatrixTaus", "ALLTAUS");
  handler->addProductCut("looseMatrixTaus", "PT20");
  handler->addProductCut("looseMatrixTaus", "ETA2p3");
  handler->addProductCut("looseMatrixTaus", "TAU_dz");
  handler->addProductCut("looseMatrixTaus", "decayModeFindingNewDMs");
  handler->addProductCut("looseMatrixTaus", "againstMuonTight3");
  handler->addProductCut("looseMatrixTaus", "againstElectronTightMVA6");
  //
  handler->addProduct(   "tightMatrixTaus", "looseMatrixTaus");
  handler->addProductCut("tightMatrixTaus", "byMediumIsolationMVArun2v1DBnewDMwLT") ;
  //
  handler->addProduct(   "altTightMatrixTaus", "looseMatrixTaus");
  handler->addProductCut("altTightMatrixTaus", "byLooseCombinedIsolationDeltaBetaCorr3Hits");// alternate tau collection
  //
  handler->addProduct("goodTaus","looseMatrixTaus");


  // --------------------------------------------------------------------------------------------------------------
  //////////
  ///Jets///
  //////////
  handler->addProduct(   "matrixJets", "ALLJETS");
  handler->addProductCut("matrixJets", "PT30");
  handler->addProductCut("matrixJets", "ETA2p4");
  handler->addProductCut("matrixJets", "PFJETID_LOOSE");
  //
  handler->addProduct(   "matrixForwardJets", "ALLJETS");
  handler->addProductCut("matrixForwardJets", "PT30");
  handler->addProductCut("matrixForwardJets", "JET_not2p4");
  handler->addProductCut("matrixForwardJets", "PFJETID_LOOSE");
  //
  handler->addProduct(   "matrixbJetsCSVL", "matrixJets");
  handler->addProductCut("matrixbJetsCSVL", "CSVL");
  handler->addProduct(   "matrixbJetsCSVM", "matrixJets");
  handler->addProductCut("matrixbJetsCSVM", "CSVM");
  //
  handler->addProduct("goodJets",        "matrixJets");
  handler->addProduct("goodForwardJets", "matrixForwardJets");
  handler->addProduct("goodbJetsCSVL",   "matrixbJetsCSVL");
  handler->addProduct("goodbJetsCSVM",   "matrixbJetsCSVM");


  // --------------------------------------------------------------------------------------------------------------
  /////////////////
  ///Separations///
  /////////////////
  ObjectComparisonDeltaR* deltaR0p05 = new ObjectComparisonDeltaR(0.05);
  ObjectComparisonDeltaR* deltaR0p1  = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p2  = new ObjectComparisonDeltaR(0.2);
  ObjectComparisonDeltaR* deltaR0p3  = new ObjectComparisonDeltaR(0.3);
  ObjectComparisonDeltaR* deltaR0p4  = new ObjectComparisonDeltaR(0.4);

  handler->addProductComparison("looseMatrixElectrons", "looseMatrixMuons",     deltaR0p2);//discard ele 
  handler->addProductComparison("looseMatrixTaus",      "looseMatrixElectrons", deltaR0p4);//discard tau
  handler->addProductComparison("looseMatrixTaus",      "looseMatrixMuons",     deltaR0p4);//discard tau
  handler->addProductComparison("matrixJets",           "looseMatrixMuons",     deltaR0p4);//discard jet
  handler->addProductComparison("matrixJets",           "looseMatrixElectrons", deltaR0p4);//discard jet
  handler->addProductComparison("matrixJets",           "looseMatrixTaus",      deltaR0p4);//discard jet
  handler->addProductComparison("matrixForwardJets",    "looseMatrixMuons",     deltaR0p4);//discard jet
  handler->addProductComparison("matrixForwardJets",    "looseMatrixElectrons", deltaR0p4);//discard jet
  handler->addProductComparison("matrixForwardJets",    "looseMatrixTaus",      deltaR0p4);//discard jet

}
