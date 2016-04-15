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
  handler->addProductCut("heepIDElectrons", "PT35");//HEEPID does have a built-in 35GeV pT cut, this is just to make it explicit.
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
  handler->addProductCut("looseMatrixTaus", "byVLooseIsolationMVArun2v1DBnewDMwLT") ;
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
  // These are not tau-DR overlap cleaned: Light Analysis "LA"
  handler->addProduct(   "matrixJetsLA", "ALLJETS");
  handler->addProductCut("matrixJetsLA", "PT30");
  handler->addProductCut("matrixJetsLA", "ETA2p4");
  handler->addProductCut("matrixJetsLA", "PFJETID_LOOSE");
  //
  handler->addProduct(   "matrixForwardJetsLA", "ALLJETS");
  handler->addProductCut("matrixForwardJetsLA", "PT30");
  handler->addProductCut("matrixForwardJetsLA", "JET_not2p4");
  handler->addProductCut("matrixForwardJetsLA", "PFJETID_LOOSE");
  //
  // These derive from matrixJetsLA, matrixForwardJetsLA above, so they are also not tau-DR overlap cleaned:
  handler->addProduct(   "matrixbJetsCSVLLA", "matrixJetsLA");
  handler->addProductCut("matrixbJetsCSVLLA", "CSVL");
  handler->addProduct(   "matrixbJetsCSVMLA", "matrixJetsLA");
  handler->addProductCut("matrixbJetsCSVMLA", "CSVM");
  //
  // --- --- --- --- --- --- --- --- --- ---
  // These are full ele-mu-tau-DR overlap cleaned:
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
  // These derive from matrixJets, matrixForwardJets above, so they are also ele-mu-tau-DR overlap cleaned:
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
  //
  handler->addProductComparison("matrixJetsLA",         "looseMatrixMuons",     deltaR0p4);//discard jet
  handler->addProductComparison("matrixJetsLA",         "looseMatrixElectrons", deltaR0p4);//discard jet
  handler->addProductComparison("matrixForwardJetsLA",  "looseMatrixMuons",     deltaR0p4);//discard jet
  handler->addProductComparison("matrixForwardJetsLA",  "looseMatrixElectrons", deltaR0p4);//discard jet


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////
  ///MATRIX METHOD///   Perhaps these are out of place, but need to go here for now:
  ///////////////////  
  //
  // Matrix method specials, mark loose -> tight muons
  EventVariableLeptonLTChecker* LTMuons = new EventVariableLeptonLTChecker("LTMuons","goodMuons","","good","tightMatrix");//3rd is prefix
  LTMuons->addProduct("tightMatrixMuons");
  handler->addEventVariable("LTMuons",LTMuons);
  //
  // Matrix method specials, mark loose -> tight electrons
  EventVariableLeptonLTChecker* LTElectrons = new EventVariableLeptonLTChecker("LTElectrons","goodElectrons","","good","tightMatrix");//3rd is prefix
  LTElectrons->addProduct("tightMatrixElectrons");
  handler->addEventVariable("LTElectrons",LTElectrons);
  //
  // Matrix method specials, mark loose -> tight taus
  EventVariableLeptonLTChecker* LTTaus = new EventVariableLeptonLTChecker("LTTaus","goodTaus","","good","tightMatrix");//3rd is prefix
  LTTaus->addProduct("tightMatrixTaus");
  handler->addEventVariable("LTTaus",LTTaus);
  //
  // Matrix method specials, store 3D MM weights, mark leptons that are used in this calculation.
  EventVariableMatrixWeights3D* MatrixWeights3D = new EventVariableMatrixWeights3D("MatrixWeights3D","goodMuons","3D","good","tightMatrix");
  MatrixWeights3D->addProduct("goodElectrons");
  MatrixWeights3D->addProduct("goodTaus");
  MatrixWeights3D->addProduct("tightMatrixMuons");
  MatrixWeights3D->addProduct("tightMatrixElectrons");
  MatrixWeights3D->addProduct("tightMatrixTaus");
  handler->addEventVariable("MATRIXWEIGHTS3D",MatrixWeights3D);
  handler->addEventVariable("ISMATRIX3DMUONS",    new EventVariableObjectVariableVector<int>("IsMatrixLep3D","goodMuons"));
  handler->addEventVariable("ISMATRIX3DELECTRONS",new EventVariableObjectVariableVector<int>("IsMatrixLep3D","goodElectrons"));
  handler->addEventVariable("ISMATRIX3DTAUS",     new EventVariableObjectVariableVector<int>("IsMatrixLep3D","goodTaus"));
  // >>>> Also produces nLLL%s, Wfff%s, WfakeBckg%s, WfakeBckgPEU%s %s="3D"
  //
  // Matrix method specials, store 3D MM weights, mark leptons that are used in this calculation.
  // This does not use taus!
  EventVariableMatrixWeights3D* MatrixWeights3DLA = new EventVariableMatrixWeights3D("MatrixWeights3DLA","goodMuons","3DLA","good","tightMatrix");
  MatrixWeights3DLA->addProduct("goodElectrons");
  MatrixWeights3DLA->addProduct("tightMatrixMuons");
  MatrixWeights3DLA->addProduct("tightMatrixElectrons");
  handler->addEventVariable("MATRIXWEIGHTS3DLA",MatrixWeights3DLA);
  handler->addEventVariable("ISMATRIX3DLAMUONS",    new EventVariableObjectVariableVector<int>("IsMatrixLep3DLA","goodMuons"));
  handler->addEventVariable("ISMATRIX3DLAELECTRONS",new EventVariableObjectVariableVector<int>("IsMatrixLep3DLA","goodElectrons"));
  // >>>> Also produces nLLL%s, Wfff%s, WfakeBckg%s, WfakeBckgPEU%s %s="3DLA"
  //
  // 
  // Matrix method specials, store 2D MM weights, mark leptons that are used in this calculation.
  EventVariableMatrixWeights2D* MatrixWeights2D = new EventVariableMatrixWeights2D("MatrixWeights2D","goodMuons","2D","good","tightMatrix");
  MatrixWeights2D->addProduct("goodElectrons");
  MatrixWeights2D->addProduct("goodTaus");
  MatrixWeights2D->addProduct("tightMatrixMuons");
  MatrixWeights2D->addProduct("tightMatrixElectrons");
  MatrixWeights2D->addProduct("tightMatrixTaus");
  handler->addEventVariable("MATRIXWEIGHTS2D",MatrixWeights2D);
  handler->addEventVariable("ISMATRIX2DMUONS",    new EventVariableObjectVariableVector<int>("IsMatrixLep2D","goodMuons"));
  handler->addEventVariable("ISMATRIX2DELECTRONS",new EventVariableObjectVariableVector<int>("IsMatrixLep2D","goodElectrons"));
  handler->addEventVariable("ISMATRIX2DTAUS",     new EventVariableObjectVariableVector<int>("IsMatrixLep2D","goodTaus"));
  //
  // Matrix method specials, store 2D MM weights, mark leptons that are used in this calculation.
  // This does not use taus!
  EventVariableMatrixWeights2D* MatrixWeights2DLA = new EventVariableMatrixWeights2D("MatrixWeights2DLA","goodMuons","2DLA","good","tightMatrix");
  MatrixWeights2DLA->addProduct("goodElectrons");
  MatrixWeights2DLA->addProduct("tightMatrixMuons");
  MatrixWeights2DLA->addProduct("tightMatrixElectrons");
  handler->addEventVariable("MATRIXWEIGHTS2DLA",MatrixWeights2DLA);
  handler->addEventVariable("ISMATRIX2DLAMUONS",    new EventVariableObjectVariableVector<int>("IsMatrixLep2DLA","goodMuons"));
  handler->addEventVariable("ISMATRIX2DLAELECTRONS",new EventVariableObjectVariableVector<int>("IsMatrixLep2DLA","goodElectrons"));

}
