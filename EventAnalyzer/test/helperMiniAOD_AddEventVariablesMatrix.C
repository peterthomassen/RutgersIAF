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


  // Loose Matrix Electrons (Good Electrons)
  handler->addEventVariable("ISTIGHTMATRIXELECTRON",        new EventVariableObjectVariableVector<int>("IsTight",     "goodElectrons"));
  //
  // Tight Matrix Electrons   
  handler->addEventVariable("NTIGHTMATRIXELECTRONS",        new EventVariableN("NTIGHTMATRIXELECTRONS",               "tightMatrixElectrons"));
  handler->addEventVariable("QTIGHTMATRIXELECTRONS",        new EventVariableObjectVariableVector<int>("CHARGE",      "tightMatrixElectrons"));
  handler->addEventVariable("PTTIGHTMATRIXELECTRONS",       new EventVariableObjectVariableVector<double>("PT",       "tightMatrixElectrons"));
  handler->addEventVariable("ETATIGHTMATRIXELECTRONS",      new EventVariableObjectVariableVector<double>("ETA",      "tightMatrixElectrons"));
  handler->addEventVariable("PHITIGHTMATRIXELECTRONS",      new EventVariableObjectVariableVector<double>("PHI",      "tightMatrixElectrons"));
  //
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
  // Tight Matrix Taus - ALTERNATIVE
  handler->addEventVariable("NALTTIGHTMATRIXTAUS",          new EventVariableN("NALTTIGHTMATRIXTAUS",                 "altTightMatrixTaus"));
  handler->addEventVariable("QALTTIGHTMATRIXTAUS",          new EventVariableObjectVariableVector<int>("CHARGE",      "altTightMatrixTaus"));
  handler->addEventVariable("PTALTTIGHTMATRIXTAUS",         new EventVariableObjectVariableVector<double>("PT",       "altTightMatrixTaus"));
  handler->addEventVariable("ETAALTTIGHTMATRIXTAUS",        new EventVariableObjectVariableVector<double>("ETA",      "altTightMatrixTaus"));
  handler->addEventVariable("PHIALTTIGHTMATRIXTAUS",        new EventVariableObjectVariableVector<double>("PHI",      "altTightMatrixTaus"));


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
