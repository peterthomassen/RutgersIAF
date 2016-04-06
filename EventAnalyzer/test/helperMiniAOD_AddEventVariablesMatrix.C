//////////////////////////////////////////////////////////
//
// Matrix Method specific event variables are defined here.
// These exclude matrix method objects which are mapped to the goodObjects products.
//
//////////////////////////////////////////////////////////

void addEventVariablesMatrix(BaseHandler* handler,bool isMC = false, double mZ = 91, double zWidth = 10, double mW = 80.385)
{

  // Loose Matrix Muons (Good Muons)
  handler->addEventVariable("ISTIGHTMATRIXMUON",            new EventVariableObjectVariableVector<int>("IsTight",     "goodMuons"));
  //
  // Tight Matrix Muons 
  handler->addEventVariable("NTIGHTMATRIXMUONS",            new EventVariableN("NTIGHTMATRIXMUONS",                   "tightMatrixMuons"));
  handler->addEventVariable("QTIGHTMATRIXMUONS",            new EventVariableObjectVariableVector<int>("CHARGE",      "tightMatrixMuons"));
  handler->addEventVariable("PTTIGHTMATRIXMUONS",           new EventVariableObjectVariableVector<double>("PT",       "tightMatrixMuons"));
  handler->addEventVariable("ETATIGHTMATRIXMUONS",          new EventVariableObjectVariableVector<double>("ETA",      "tightMatrixMuons"));
  handler->addEventVariable("PHITIGHTMATRIXMUONS",          new EventVariableObjectVariableVector<double>("PHI",      "tightMatrixMuons"));
  handler->addEventVariable("CONECORRECTEDPTTIGHTMATRIXMUONS",           new EventVariableObjectVariableVector<double>("conecorrectedPt",       "tightMatrixMuons"));
  // ConeConstituents for muons:                                                                                                                              
  handler->addEventVariable("JETCORRJETPTTIGHTMATRIXMUONS",      new EventVariableObjectVariableVector<double>("JETCORRJETPT",       "tightMatrixMuons"));
  handler->addEventVariable("JETNOOFCONSTTIGHTMATRIXMUONS",      new EventVariableObjectVariableVector<int>(   "JETNOOFCONST",       "tightMatrixMuons"));
  handler->addEventVariable("JETCHMULTTIGHTMATRIXMUONS",         new EventVariableObjectVariableVector<int>(   "JETCHMULT",          "tightMatrixMuons"));
  handler->addEventVariable("JETCHHADMULTTIGHTMATRIXMUONS",      new EventVariableObjectVariableVector<int>(   "JETCHHADMULT",       "tightMatrixMuons"));
  handler->addEventVariable("CONESUMETDR03TIGHTMATRIXMUONS",     new EventVariableObjectVariableVector<double>("CONESUMETDR03",      "tightMatrixMuons"));
  handler->addEventVariable("CONENDR03TIGHTMATRIXMUONS",         new EventVariableObjectVariableVector<int>(   "CONENDR03",          "tightMatrixMuons"));
  handler->addEventVariable("CONESUMETDR04TIGHTMATRIXMUONS",     new EventVariableObjectVariableVector<double>("CONESUMETDR04",      "tightMatrixMuons"));
  handler->addEventVariable("CONENDR04TIGHTMATRIXMUONS",         new EventVariableObjectVariableVector<int>(   "CONENDR04",          "tightMatrixMuons"));
  handler->addEventVariable("CONESUMETDR03TO07TIGHTMATRIXMUONS", new EventVariableObjectVariableVector<double>("CONESUMETDR03to07",  "tightMatrixMuons"));
  handler->addEventVariable("CONENDR03TO07TIGHTMATRIXMUONS",     new EventVariableObjectVariableVector<int>(   "CONENDR03to07",      "tightMatrixMuons"));
  handler->addEventVariable("CONESUMETDR04TO08TIGHTMATRIXMUONS", new EventVariableObjectVariableVector<double>("CONESUMETDR04to08",  "tightMatrixMuons"));
  handler->addEventVariable("CONENDR04TO08TIGHTMATRIXMUONS",     new EventVariableObjectVariableVector<int>(   "CONENDR04to08",      "tightMatrixMuons"));



  //
  // Tight Matrix Electrons   
  handler->addEventVariable("NTIGHTMATRIXELECTRONS",        new EventVariableN("NTIGHTMATRIXELECTRONS",               "tightMatrixElectrons"));
  handler->addEventVariable("QTIGHTMATRIXELECTRONS",        new EventVariableObjectVariableVector<int>("CHARGE",      "tightMatrixElectrons"));
  handler->addEventVariable("PTTIGHTMATRIXELECTRONS",       new EventVariableObjectVariableVector<double>("PT",       "tightMatrixElectrons"));
  handler->addEventVariable("ETATIGHTMATRIXELECTRONS",      new EventVariableObjectVariableVector<double>("ETA",      "tightMatrixElectrons"));
  handler->addEventVariable("PHITIGHTMATRIXELECTRONS",      new EventVariableObjectVariableVector<double>("PHI",      "tightMatrixElectrons"));

  // Loose Matrix Electrons (Good Electrons)
  handler->addEventVariable("ISTIGHTMATRIXELECTRON",        new EventVariableObjectVariableVector<int>("IsTight",     "goodElectrons"));
  //
  handler->addEventVariable("CONECORRECTEDPTTIGHTMATRIXELECTRONS",       new EventVariableObjectVariableVector<double>("conecorrectedPt",       "tightMatrixElectrons"));

  // ConeConstituents for electrons:                                                                                                                                                                  
  handler->addEventVariable("JETCORRJETPTTIGHTMATRIXELECTRONS",      new EventVariableObjectVariableVector<double>("JETCORRJETPT",       "tightMatrixElectrons"));
  handler->addEventVariable("JETNOOFCONSTTIGHTMATRIXELECTRONS",      new EventVariableObjectVariableVector<int>(   "JETNOOFCONST",       "tightMatrixElectrons"));
  handler->addEventVariable("JETCHMULTTIGHTMATRIXELECTRONS",         new EventVariableObjectVariableVector<int>(   "JETCHMULT",          "tightMatrixElectrons"));
  handler->addEventVariable("JETCHHADMULTTIGHTMATRIXELECTRONS",      new EventVariableObjectVariableVector<int>(   "JETCHHADMULT",       "tightMatrixElectrons"));
  handler->addEventVariable("CONESUMETDR03TIGHTMATRIXELECTRONS",     new EventVariableObjectVariableVector<double>("CONESUMETDR03",      "tightMatrixElectrons"));
  handler->addEventVariable("CONENDR03TIGHTMATRIXELECTRONS",         new EventVariableObjectVariableVector<int>(   "CONENDR03",          "tightMatrixElectrons"));
  handler->addEventVariable("CONESUMETDR04TIGHTMATRIXELECTRONS",     new EventVariableObjectVariableVector<double>("CONESUMETDR04",      "tightMatrixElectrons"));
  handler->addEventVariable("CONENDR04TIGHTMATRIXELECTRONS",         new EventVariableObjectVariableVector<int>(   "CONENDR04",          "tightMatrixElectrons"));
  handler->addEventVariable("CONESUMETDR03TO07TIGHTMATRIXELECTRONS", new EventVariableObjectVariableVector<double>("CONESUMETDR03to07",  "tightMatrixElectrons"));
  handler->addEventVariable("CONENDR03TO07TIGHTMATRIXELECTRONS",     new EventVariableObjectVariableVector<int>(   "CONENDR03to07",      "tightMatrixElectrons"));
  handler->addEventVariable("CONESUMETDR04TO08TIGHTMATRIXELECTRONS", new EventVariableObjectVariableVector<double>("CONESUMETDR04to08",  "tightMatrixElectrons"));
  handler->addEventVariable("CONENDR04TO08TIGHTMATRIXELECTRONS",     new EventVariableObjectVariableVector<int>(   "CONENDR04to08",      "tightMatrixElectrons"));


  // HEEP ID Electrons
  handler->addEventVariable("NHEEPIDELECTRONS",             new EventVariableN("NHEEPIDELECTRONS",                    "heepIDElectrons"));
  handler->addEventVariable("QHEEPIDELECTRONS",             new EventVariableObjectVariableVector<int>("CHARGE",      "heepIDElectrons"));
  handler->addEventVariable("PTHEEPIDELECTRONS",            new EventVariableObjectVariableVector<double>("PT",       "heepIDElectrons"));
  handler->addEventVariable("ETAHEEPIDELECTRONS",           new EventVariableObjectVariableVector<double>("ETA",      "heepIDElectrons"));
  handler->addEventVariable("PHIHEEPIDELECTRONS",           new EventVariableObjectVariableVector<double>("PHI",      "heepIDElectrons"));
  handler->addEventVariable("MINIISOHEEPIDELECTRONS",       new EventVariableObjectVariableVector<double>("MINIISO",  "heepIDElectrons"));
  handler->addEventVariable("PTRATIOHEEPIDELECTRONS",       new EventVariableObjectVariableVector<double>("ptRatio",  "heepIDElectrons"));
  handler->addEventVariable("PTRELHEEPIDELECTRONS",         new EventVariableObjectVariableVector<double>("ptRel",    "heepIDElectrons"));
  handler->addEventVariable("RELISOHEEPIDELECTRONS",        new EventVariableObjectVariableVector<double>("RELISO",   "heepIDElectrons"));
  handler->addEventVariable("RELISOCUTIDHEEPIDELECTRONS",   new EventVariableObjectVariableVector<double>("ELECTRON_RELISO", "heepIDElectrons"));

  // Loose Matrix Taus (Good Taus)
  handler->addEventVariable("ISTIGHTMATRIXTAU",             new EventVariableObjectVariableVector<int>("IsTight",     "goodTaus"));
  //
  // Tight Matrix Taus
  handler->addEventVariable("NTIGHTMATRIXTAUS",             new EventVariableN("NTIGHTMATRIXTAUS",                    "tightMatrixTaus"));
  handler->addEventVariable("QTIGHTMATRIXTAUS",             new EventVariableObjectVariableVector<int>("CHARGE",      "tightMatrixTaus"));
  handler->addEventVariable("PTTIGHTMATRIXTAUS",            new EventVariableObjectVariableVector<double>("PT",       "tightMatrixTaus"));
  handler->addEventVariable("ETATIGHTMATRIXTAUS",           new EventVariableObjectVariableVector<double>("ETA",      "tightMatrixTaus"));
  handler->addEventVariable("PHITIGHTMATRIXTAUS",           new EventVariableObjectVariableVector<double>("PHI",      "tightMatrixTaus"));
  //

  // ConeConstituents for taus:                                                                                                                                                                       
  handler->addEventVariable("JETCORRJETPTTIGHTMATRIXTAUS",      new EventVariableObjectVariableVector<double>("JETCORRJETPT",       "tightMatrixTaus"));
  handler->addEventVariable("JETNOOFCONSTTIGHTMATRIXTAUS",      new EventVariableObjectVariableVector<int>(   "JETNOOFCONST",       "tightMatrixTaus"));
  handler->addEventVariable("JETCHMULTTIGHTMATRIXTAUS",         new EventVariableObjectVariableVector<int>(   "JETCHMULT",          "tightMatrixTaus"));
  handler->addEventVariable("JETCHHADMULTTIGHTMATRIXTAUS",      new EventVariableObjectVariableVector<int>(   "JETCHHADMULT",       "tightMatrixTaus"));
  handler->addEventVariable("CONESUMETDR03TIGHTMATRIXTAUS",     new EventVariableObjectVariableVector<double>("CONESUMETDR03",      "tightMatrixTaus"));
  handler->addEventVariable("CONENDR03TIGHTMATRIXTAUS",         new EventVariableObjectVariableVector<int>(   "CONENDR03",          "tightMatrixTaus"));
  handler->addEventVariable("CONESUMETDR04TIGHTMATRIXTAUS",     new EventVariableObjectVariableVector<double>("CONESUMETDR04",      "tightMatrixTaus"));
  handler->addEventVariable("CONENDR04TIGHTMATRIXTAUS",         new EventVariableObjectVariableVector<int>(   "CONENDR04",          "tightMatrixTaus"));
  handler->addEventVariable("CONESUMETDR03TO07TIGHTMATRIXTAUS", new EventVariableObjectVariableVector<double>("CONESUMETDR03to07",  "tightMatrixTaus"));
  handler->addEventVariable("CONENDR03TO07TIGHTMATRIXTAUS",     new EventVariableObjectVariableVector<int>(   "CONENDR03to07",      "tightMatrixTaus"));
  handler->addEventVariable("CONESUMETDR04TO08TIGHTMATRIXTAUS", new EventVariableObjectVariableVector<double>("CONESUMETDR04to08",  "tightMatrixTaus"));
  handler->addEventVariable("CONENDR04TO08TIGHTMATRIXTAUS",     new EventVariableObjectVariableVector<int>(   "CONENDR04to08",      "tightMatrixTaus"));



  // Tight Matrix Taus - ALTERNATIVE
  handler->addEventVariable("NALTTIGHTMATRIXTAUS",          new EventVariableN("NALTTIGHTMATRIXTAUS",                 "altTightMatrixTaus"));
  handler->addEventVariable("QALTTIGHTMATRIXTAUS",          new EventVariableObjectVariableVector<int>("CHARGE",      "altTightMatrixTaus"));
  handler->addEventVariable("PTALTTIGHTMATRIXTAUS",         new EventVariableObjectVariableVector<double>("PT",       "altTightMatrixTaus"));
  handler->addEventVariable("ETAALTTIGHTMATRIXTAUS",        new EventVariableObjectVariableVector<double>("ETA",      "altTightMatrixTaus"));
  handler->addEventVariable("PHIALTTIGHTMATRIXTAUS",        new EventVariableObjectVariableVector<double>("PHI",      "altTightMatrixTaus"));

  handler->addEventVariable("CONECORRECTEDPTTIGHTMATRIXTAUS",            new EventVariableObjectVariableVector<double>("conecorrectedPt",       "tightMatrixTaus"));
  // matrixJetsLA : Non-tau-DR cleaned jet variables
  handler->addEventVariable("NMATRIXJETSLA",          new EventVariableN("NMATRIXJETSLA",                      "matrixJetsLA"));
  handler->addEventVariable("PTMATRIXJETSLA",         new EventVariableObjectVariableVector<double>("PT",      "matrixJetsLA"));
  handler->addEventVariable("ETAMATRIXJETSLA",        new EventVariableObjectVariableVector<double>("ETA",     "matrixJetsLA"));
  handler->addEventVariable("PHIMATRIXJETSLA",        new EventVariableObjectVariableVector<double>("PHI",     "matrixJetsLA"));
  handler->addEventVariable("CSVRAWMATRIXJETSLA",     new EventVariableObjectVariableVector<double>("CSVraw",  "matrixJetsLA"));
  handler->addEventVariable("JPRAWMATRIXJETSLA",      new EventVariableObjectVariableVector<double>("JPraw",   "matrixJetsLA"));
  handler->addEventVariable("CMVARAWMATRIXJETSLA",    new EventVariableObjectVariableVector<double>("cMVAraw", "matrixJetsLA"));
  //
  handler->addEventVariable("NMATRIXFORWARDJETSLA",   new EventVariableN("NMATRIXFORWARDJETSLA",               "matrixForwardJetsLA"));
  handler->addEventVariable("PTMATRIXFORWARDJETSLA",  new EventVariableObjectVariableVector<double>("PT",      "matrixForwardJetsLA"));
  handler->addEventVariable("ETAMATRIXFORWARDJETSLA", new EventVariableObjectVariableVector<double>("ETA",     "matrixForwardJetsLA"));
  handler->addEventVariable("PHIMATRIXFORWARDJETSLA", new EventVariableObjectVariableVector<double>("PHI",     "matrixForwardJetsLA"));
  //
  handler->addEventVariable("HTLA",         new EventVariableSumPT("HTLA",     "matrixJetsLA"));
  handler->addEventVariable("HTCSVLLA",     new EventVariableSumPT("HTCSVLLA", "matrixbJetsCSVLLA"));
  handler->addEventVariable("HTCSVMLA",     new EventVariableSumPT("HTCSVMLA", "matrixbJetsCSVMLA"));
  handler->addEventVariable("NBJETSCSVLLA", new EventVariableN("NBJETSCSVLLA", "matrixbJetsCSVLLA"));
  handler->addEventVariable("NBJETSCSVMLA", new EventVariableN("NBJETSCSVMLA", "matrixbJetsCSVMLA"));
  handler->addEventVariable("WDIJETMASSLA", new EventVariablePairMass("WDIJETMASSLA", "matrixJetsLA", "WJETLA", mW, 10));


}
