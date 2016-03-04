//////////////////////////////////////////////////////////
//
// Matrix Method specific event variables are defined here.
// These exclude matrix method objects which are mapped to the goodObjects products.
//
//////////////////////////////////////////////////////////

void addEventVariablesMatrix(BaseHandler* handler,bool isMC = false, double mZ = 91, double zWidth = 10, double mW = 80.385)
{
  // Tight Matrix Muons 
  handler->addEventVariable("NTIGHTMATRIXMUONS",            new EventVariableN("NTIGHTMATRIXMUONS",                   "tightMatrixMuons"));
  handler->addEventVariable("QTIGHTMATRIXMUONS",            new EventVariableObjectVariableVector<int>("CHARGE",      "tightMatrixMuons"));
  handler->addEventVariable("PTTIGHTMATRIXMUONS",           new EventVariableObjectVariableVector<double>("PT",       "tightMatrixMuons"));
  handler->addEventVariable("ETATIGHTMATRIXMUONS",          new EventVariableObjectVariableVector<double>("ETA",      "tightMatrixMuons"));
  handler->addEventVariable("PHITIGHTMATRIXMUONS",          new EventVariableObjectVariableVector<double>("PHI",      "tightMatrixMuons"));
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
  handler->addEventVariable("MINIISOHEEPIDELECTRONS",       new EventVariableObjectVariableVector<double>("MINIISO",  "heepidElectrons"));
  handler->addEventVariable("PTRATIOHEEPIDELECTRONS",       new EventVariableObjectVariableVector<double>("ptRatio",  "heepidElectrons"));
  handler->addEventVariable("PTRELHEEPIDELECTRONS",         new EventVariableObjectVariableVector<double>("ptRel",    "heepidElectrons"));
  handler->addEventVariable("RELISOHEEPIDELECTRONS",        new EventVariableObjectVariableVector<double>("RELISO",   "heepidElectrons"));
  handler->addEventVariable("RELISOCUTIDHEEPIDELECTRONS",   new EventVariableObjectVariableVector<double>("ELECTRON_RELISO", "heepidElectrons"));
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


  //matrix method weights

}
