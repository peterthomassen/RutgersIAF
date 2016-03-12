#include <TF1.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTF1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOS.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOSSF.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariablePairMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMixedPairMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSumPT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTH1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTriggerWeight.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableElectronTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMethod.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMuonTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRelIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_AssociateVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonSkimRecoTracks.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonElectron.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDeltaRCharge.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRename.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F_EventVariableVsEventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F_ObjectVariableVsObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_NearestVertexRank.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableGenVertexR.h"
#include "RutgersIAF/EventAnalyzer/interface/PrintModuleProduct.h"
#include "RutgersIAF/EventAnalyzer/interface/PrintModuleEventVariables.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableExtreme.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableEffectiveArea.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableEffectiveAreaMiniIsolation.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableEventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRhoCorrectedTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableDeltaBetaCorrectedTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableRename.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableConst.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableDvector.h"
//
#include "RutgersIAF/EventAnalyzer/interface/EventVariableLeptonLTChecker.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableLeptonGenChecker.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMatrixWeights3D.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMatrixWeights2D.h"
//
#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_SetupProductsCommon.C"
#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_SetupProductsMatrix.C"
//#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_SetupProductsRA7.C"
//
#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_AddEventVariablesMatrix.C"
//#include "RutgersIAF/EventAnalyzer/test/helperMiniAOD_AddEventVariablesRA7.C"

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFEventAnalyzer.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupProducts(BaseHandler* handler)
{
  // Pick one of setupProductsRA7 or setupProductsMatrix, they define "goodObjects"
  //setupProductsRA7(handler);
  setupProductsMatrix(handler);
  setupProductsCommon(handler);//.... Always KEEP
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupOnZSignatures(BaseHandler* handler)
{
  handler->addSignature("Mu2")->addCut("twoMcMuonsFromZ"); //might need a fix, I think I removed these in setupProductsCommon.
  handler->addSignature("El2")->addCut("twoMcElectronsFromZ");
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupMET(BaseHandler* handler, bool isMC) {
  handler->addEventVariable("NVERTICES",new EventVariableN("NVERTICES","ALLVERTICES"));
  
  if(isMC){
    EventVariableSumPT* METnoSmearing = new EventVariableSumPT("METnoSmearing", "MET");
    handler->addEventVariable("METnoSmearing",METnoSmearing);
    
    EventVariableSmearMET* MET = new EventVariableSmearMET("MET","MET","HT","NVERTICES",7.5,4.0,4.6,8.8,4.4,4.6);
    MET->setSeed(3141592654);
    handler->addEventVariable("MET",MET);
		
    handler->addObjectVariable("isZ",      new ObjectVariableValue<int>("pdgId", 23));
    handler->addObjectVariable("status62", new ObjectVariableValue<int>("status",62));
    handler->addProduct(   "ZBOSONS","ALLMC");
    handler->addProductCut("ZBOSONS","isZ");
    handler->addProductCut("ZBOSONS","status62");
    
    handler->addEventVariable("ZPT",new EventVariableObjectVariableVector<double>("PT","ZBOSONS"));
  } else {
    EventVariableSumPT* MET = new EventVariableSumPT("MET", "MET");
    handler->addEventVariable("MET",MET);
  }
  
  handler->addObjectVariable("PX",  new ObjectVariableMethod("PX",&SignatureObject::Px));
  handler->addObjectVariable("PY",  new ObjectVariableMethod("PY",&SignatureObject::Py));
  handler->addEventVariable("METPX",new EventVariableObjectVariableVector<double>("PX","MET"));
  handler->addEventVariable("METPY",new EventVariableObjectVariableVector<double>("PY","MET"));
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupVariables(BaseHandler* handler,bool isMC = false, double mZ = 91, double zWidth = 10, double mW = 80.385) {

  // Pick one of addEventVariablesRA7 or addEventVariablesMatrix:
  //addEventVariablesRA7(    handler, isMC,  mZ,  zWidth, mW );
  addEventVariablesMatrix( handler, isMC,  mZ,  zWidth, mW );
  
  EventVariableThreshold* pt20first = new EventVariableThreshold("PT20first","goodElectrons");
  pt20first->addProduct("goodMuons");
  pt20first->addThreshold(20);
  handler->addEventVariable("PT20first",pt20first);
  //handler->addHandlerCut("PT20first");
  
  EventVariableThreshold* pt201512 = new EventVariableThreshold("PT201512","goodElectrons");
  pt201512->addProduct("goodMuons");
  pt201512->addThreshold(20);
  pt201512->addThreshold(15);
  pt201512->addThreshold(12);
  handler->addEventVariable("PT201512",pt201512);
  
  EventVariableThreshold* pt201510 = new EventVariableThreshold("PT201510","goodElectrons");
  pt201510->addProduct("goodMuons");
  pt201510->addThreshold(20);
  pt201510->addThreshold(15);
  pt201510->addThreshold(10);
  handler->addEventVariable("PT201510",pt201510);
  
  EventVariableThreshold* pt201010 = new EventVariableThreshold("PT201010","goodElectrons");
  pt201010->addProduct("goodMuons");
  pt201010->addThreshold(20);
  pt201010->addThreshold(10);
  pt201010->addThreshold(10);
  handler->addEventVariable("PT201010",pt201010);

  EventVariableThreshold* pt202010 = new EventVariableThreshold("PT202010","goodElectrons");
  pt202010->addProduct("goodMuons");
  pt202010->addThreshold(20);
  pt202010->addThreshold(20);
  pt202010->addThreshold(10);
  handler->addEventVariable("PT202010",pt202010);

  EventVariableThreshold* pt202020 = new EventVariableThreshold("PT202020","goodElectrons");
  pt202020->addProduct("goodMuons");
  pt202020->addThreshold(20);
  pt202020->addThreshold(20);
  pt202020->addThreshold(20);
  handler->addEventVariable("PT202020",pt202020);

  EventVariableThreshold* pt302020 = new EventVariableThreshold("PT302020","goodElectrons");
  pt302020->addProduct("goodMuons");
  pt302020->addThreshold(30);
  pt302020->addThreshold(20);
  pt302020->addThreshold(20);
  handler->addEventVariable("PT302020",pt302020);

  TString products[6] = {"posGoodMuons","negGoodMuons","posGoodElectrons","negGoodElectrons","posGoodTracks","negGoodTracks"};
  for(int i = 0; i < 6; i++){
    TString varname = TString::Format("N%s",products[i].Data());
    varname.ToUpper();
    handler->addEventVariable(varname,new EventVariableN(varname,products[i]));
  }

  EventVariableObjectVariableVector<double>* leptonPts = new EventVariableObjectVariableVector<double>("PT","goodMuons",true);
  leptonPts->addProduct("goodElectrons");
  leptonPts->addProduct("goodTaus");
  handler->addEventVariable("PTGOODLEPTONS",leptonPts);
  
  EventVariableObjectVariableVector<double>* lightLeptonPts = new EventVariableObjectVariableVector<double>("PT","goodMuons",true);
  lightLeptonPts->addProduct("goodElectrons");
  handler->addEventVariable("PTLIGHTLEPTONS",lightLeptonPts);

  // --------------------------------------------------------------------------------------------------------------
  ////////////////////
  ///Muon Variables///
  ////////////////////
  handler->addEventVariable("NGOODMUONS",             new EventVariableN("NGOODMUONS",                             "goodMuons"));
  handler->addEventVariable("QGOODMUONS",             new EventVariableObjectVariableVector<int>("CHARGE",         "goodMuons"));
  handler->addEventVariable("PTGOODMUONS",            new EventVariableObjectVariableVector<double>("PT",          "goodMuons"));
  handler->addEventVariable("ETAGOODMUONS",           new EventVariableObjectVariableVector<double>("ETA",         "goodMuons"));
  handler->addEventVariable("PHIGOODMUONS",           new EventVariableObjectVariableVector<double>("PHI",         "goodMuons"));
  handler->addEventVariable("MINIISOGOODMUONS",       new EventVariableObjectVariableVector<double>("MINIISO",     "goodMuons"));
  handler->addEventVariable("PTRATIOGOODMUONS",       new EventVariableObjectVariableVector<double>("ptRatio",     "goodMuons"));
  handler->addEventVariable("PTRELGOODMUONS",         new EventVariableObjectVariableVector<double>("ptRel",       "goodMuons"));
  handler->addEventVariable("RELISOGOODMUONS",        new EventVariableObjectVariableVector<double>("RELISO",      "goodMuons"));
  handler->addEventVariable("RELISODBDR0p4GOODMUONS", new EventVariableObjectVariableVector<double>("MUON_RELISO", "goodMuons"));
  handler->addEventVariable("fakeRoleGOODMUONS",      new EventVariableObjectVariableVector<int>("fakeRole",  "goodMuons"));
  handler->addEventVariable("goodMuonsDgoodPhotons",  new EventVariableDvector("goodMuons", "goodPhotons"));
  handler->addEventVariable("goodMuonsDgoodJets",     new EventVariableDvector("goodMuons", "goodJets"));
  handler->addEventVariable("goodMuonsDgoodLeptons",  new EventVariableDvector("goodMuons", {"goodElectrons", "goodMuons"}, "goodLeptons"));
  //
  handler->addEventVariable("QBASICMUONS",       new EventVariableObjectVariableVector<int>("CHARGE",    "basicMuons"));
  handler->addEventVariable("PTBASICMUONS",      new EventVariableObjectVariableVector<double>("PT",     "basicMuons"));
  handler->addEventVariable("ETABASICMUONS",     new EventVariableObjectVariableVector<double>("ETA",    "basicMuons"));
  handler->addEventVariable("PHIBASICMUONS",     new EventVariableObjectVariableVector<double>("PHI",    "basicMuons"));
  handler->addEventVariable("DXYBASICMUONS",     new EventVariableObjectVariableVector<double>("dxy",    "basicMuons"));
  handler->addEventVariable("RELISOBASICMUONS",  new EventVariableObjectVariableVector<double>("RELISO", "basicMuons"));
  handler->addEventVariable("MINIISOBASICMUONS", new EventVariableObjectVariableVector<double>("MINIISO","basicMuons"));
  handler->addEventVariable("PTRATIOBASICMUONS", new EventVariableObjectVariableVector<double>("ptRatio","basicMuons"));
  handler->addEventVariable("PTRELBASICMUONS",   new EventVariableObjectVariableVector<double>("ptRel",  "basicMuons"));
  // -----
  handler->addEventVariable("QNONPROMPTMUONS",       new EventVariableObjectVariableVector<int>("CHARGE",    "nonPromptMuons"));
  handler->addEventVariable("PTNONPROMPTMUONS",      new EventVariableObjectVariableVector<double>("PT",     "nonPromptMuons"));
  handler->addEventVariable("ETANONPROMPTMUONS",     new EventVariableObjectVariableVector<double>("ETA",    "nonPromptMuons"));
  handler->addEventVariable("PHINONPROMPTMUONS",     new EventVariableObjectVariableVector<double>("PHI",    "nonPromptMuons"));
  handler->addEventVariable("RELISONONPROMPTMUONS",  new EventVariableObjectVariableVector<double>("RELISO", "nonPromptMuons"));
  handler->addEventVariable("MINIISONONPROMPTMUONS", new EventVariableObjectVariableVector<double>("MINIISO","nonPromptMuons"));
  handler->addEventVariable("PTRATIONONPROMPTMUONS", new EventVariableObjectVariableVector<double>("ptRatio","nonPromptMuons"));
  handler->addEventVariable("PTRELNONPROMPTMUONS",   new EventVariableObjectVariableVector<double>("ptRel",  "nonPromptMuons"));
  //
  handler->addEventVariable("nINPMUONS",    new EventVariableN("nINPMUONS",                      "isoNonPromptMuons"));
  handler->addEventVariable("QINPMUONS",    new EventVariableObjectVariableVector<int>("CHARGE", "isoNonPromptMuons"));
  handler->addEventVariable("PTINPMUONS",   new EventVariableObjectVariableVector<double>("PT",  "isoNonPromptMuons"));
  handler->addEventVariable("ETAINPMUONS",  new EventVariableObjectVariableVector<double>("ETA", "isoNonPromptMuons"));
  handler->addEventVariable("PHIINPMUONS",  new EventVariableObjectVariableVector<double>("PHI", "isoNonPromptMuons"));
  //  
  handler->addEventVariable("nNIPMUONS",    new EventVariableN("nNIPMUONS",                      "promptNonIsoMuons"));
  handler->addEventVariable("QNIPMUONS",    new EventVariableObjectVariableVector<int>("CHARGE", "promptNonIsoMuons"));
  handler->addEventVariable("PTNIPMUONS",   new EventVariableObjectVariableVector<double>("PT",  "promptNonIsoMuons"));
  handler->addEventVariable("ETANIPMUONS",  new EventVariableObjectVariableVector<double>("ETA", "promptNonIsoMuons"));
  handler->addEventVariable("PHINIPMUONS",  new EventVariableObjectVariableVector<double>("PHI", "promptNonIsoMuons"));
  //
  handler->addEventVariable("nNINPMUONS",   new EventVariableN("nNIPMUONS",                      "nonPromptNonIsoMuons"));
  handler->addEventVariable("QNINPMUONS",   new EventVariableObjectVariableVector<int>("CHARGE", "nonPromptNonIsoMuons"));
  handler->addEventVariable("PTNINPMUONS",  new EventVariableObjectVariableVector<double>("PT",  "nonPromptNonIsoMuons"));
  handler->addEventVariable("ETANINPMUONS", new EventVariableObjectVariableVector<double>("ETA", "nonPromptNonIsoMuons"));
  handler->addEventVariable("PHININPMUONS", new EventVariableObjectVariableVector<double>("PHI", "nonPromptNonIsoMuons"));


  // --------------------------------------------------------------------------------------------------------------
  ////////////////////////
  ///Electron Variables///
  ////////////////////////
  handler->addEventVariable("NGOODELECTRONS",            new EventVariableN("NGOODELECTRONS",                             "goodElectrons"));
  handler->addEventVariable("QGOODELECTRONS",            new EventVariableObjectVariableVector<int>("CHARGE",             "goodElectrons"));
  handler->addEventVariable("PTGOODELECTRONS",           new EventVariableObjectVariableVector<double>("PT",              "goodElectrons"));
  handler->addEventVariable("ETAGOODELECTRONS",          new EventVariableObjectVariableVector<double>("ETA",             "goodElectrons"));
  handler->addEventVariable("PHIGOODELECTRONS",          new EventVariableObjectVariableVector<double>("PHI",             "goodElectrons"));
  handler->addEventVariable("MINIISOGOODELECTRONS",      new EventVariableObjectVariableVector<double>("MINIISO",         "goodElectrons"));
  handler->addEventVariable("PTRATIOGOODELECTRONS",      new EventVariableObjectVariableVector<double>("ptRatio",         "goodElectrons"));
  handler->addEventVariable("PTRELGOODELECTRONS",        new EventVariableObjectVariableVector<double>("ptRel",           "goodElectrons"));
  handler->addEventVariable("RELISOGOODELECTRONS",       new EventVariableObjectVariableVector<double>("RELISO",          "goodElectrons"));
  handler->addEventVariable("RELISOCUTIDGOODELECTRONS",  new EventVariableObjectVariableVector<double>("ELECTRON_RELISO", "goodElectrons"));
  handler->addEventVariable("fakeRoleGOODELECTRONS",     new EventVariableObjectVariableVector<int>("fakeRole",  "goodElectrons"));
  handler->addEventVariable("goodElectronsDgoodPhotons", new EventVariableDvector("goodElectrons", "goodPhotons"));
  handler->addEventVariable("goodElectronsDgoodJets",    new EventVariableDvector("goodElectrons", "goodJets"));
  handler->addEventVariable("goodElectronsDgoodLeptons", new EventVariableDvector("goodElectrons", {"goodElectrons", "goodMuons"}, "goodLeptons"));
  //
  handler->addEventVariable("QBASICELECTRONS",       new EventVariableObjectVariableVector<int>("CHARGE",    "basicElectrons"));
  handler->addEventVariable("PTBASICELECTRONS",      new EventVariableObjectVariableVector<double>("PT",     "basicElectrons"));
  handler->addEventVariable("ETABASICELECTRONS",     new EventVariableObjectVariableVector<double>("ETA",    "basicElectrons"));
  handler->addEventVariable("PHIBASICELECTRONS",     new EventVariableObjectVariableVector<double>("PHI",    "basicElectrons"));
  handler->addEventVariable("RELISOBASICELECTRONS",  new EventVariableObjectVariableVector<double>("RELISO", "basicElectrons"));
  handler->addEventVariable("MINIISOBASICELECTRONS", new EventVariableObjectVariableVector<double>("MINIISO","basicElectrons"));
  handler->addEventVariable("PTRATIOBASICELECTRONS", new EventVariableObjectVariableVector<double>("ptRatio","basicElectrons"));
  handler->addEventVariable("PTRELBASICELECTRONS",   new EventVariableObjectVariableVector<double>("ptRel",  "basicElectrons"));
  handler->addEventVariable("DXYBASICELECTRONS",     new EventVariableObjectVariableVector<double>("dxy",    "basicElectrons"));
  // -----
  handler->addEventVariable("QNONPROMPTELECTRONS",       new EventVariableObjectVariableVector<int>("CHARGE",    "nonPromptElectrons"));
  handler->addEventVariable("PTNONPROMPTELECTRONS",      new EventVariableObjectVariableVector<double>("PT",     "nonPromptElectrons"));
  handler->addEventVariable("ETANONPROMPTELECTRONS",     new EventVariableObjectVariableVector<double>("ETA",    "nonPromptElectrons"));
  handler->addEventVariable("PHINONPROMPTELECTRONS",     new EventVariableObjectVariableVector<double>("PHI",    "nonPromptElectrons"));
  handler->addEventVariable("RELISONONPROMPTELECTRONS",  new EventVariableObjectVariableVector<double>("RELISO", "nonPromptElectrons"));
  handler->addEventVariable("MINIISONONPROMPTELECTRONS", new EventVariableObjectVariableVector<double>("MINIISO","nonPromptElectrons"));
  handler->addEventVariable("PTRATIONONPROMPTELECTRONS", new EventVariableObjectVariableVector<double>("ptRatio","nonPromptElectrons"));  
  handler->addEventVariable("PTRELNONPROMPTELECTRONS",   new EventVariableObjectVariableVector<double>("ptRel",  "nonPromptElectrons"));
  handler->addEventVariable("DXYNONPROMPTELECTRONS",     new EventVariableObjectVariableVector<double>("dxy",    "nonPromptElectrons"));
  //
  handler->addEventVariable("nINPELECTRONS",   new EventVariableN("nINPELECTRONS",                  "isoNonPromptElectrons"));
  handler->addEventVariable("QINPELECTRONS",   new EventVariableObjectVariableVector<int>("CHARGE", "isoNonPromptElectrons"));
  handler->addEventVariable("PTINPELECTRONS",  new EventVariableObjectVariableVector<double>("PT",  "isoNonPromptElectrons"));
  handler->addEventVariable("ETAINPELECTRONS", new EventVariableObjectVariableVector<double>("ETA", "isoNonPromptElectrons"));
  handler->addEventVariable("PHIINPELECTRONS", new EventVariableObjectVariableVector<double>("PHI", "isoNonPromptElectrons"));
  //
  handler->addEventVariable("nNIPELECTRONS",   new EventVariableN("nNIPELECTRONS",                  "promptNonIsoElectrons"));
  handler->addEventVariable("QNIPELECTRONS",   new EventVariableObjectVariableVector<int>("CHARGE", "promptNonIsoElectrons"));
  handler->addEventVariable("PTNIPELECTRONS",  new EventVariableObjectVariableVector<double>("PT",  "promptNonIsoElectrons"));
  handler->addEventVariable("ETANIPELECTRONS", new EventVariableObjectVariableVector<double>("ETA", "promptNonIsoElectrons"));
  handler->addEventVariable("PHINIPELECTRONS", new EventVariableObjectVariableVector<double>("PHI", "promptNonIsoElectrons"));
  //
  handler->addEventVariable("nNINPELECTRONS",   new EventVariableN("nNIPELECTRONS",                  "nonPromptNonIsoElectrons"));
  handler->addEventVariable("QNINPELECTRONS",   new EventVariableObjectVariableVector<int>("CHARGE", "nonPromptNonIsoElectrons"));
  handler->addEventVariable("PTNINPELECTRONS",  new EventVariableObjectVariableVector<double>("PT",  "nonPromptNonIsoElectrons"));
  handler->addEventVariable("ETANINPELECTRONS", new EventVariableObjectVariableVector<double>("ETA", "nonPromptNonIsoElectrons"));
  handler->addEventVariable("PHININPELECTRONS", new EventVariableObjectVariableVector<double>("ETA", "nonPromptNonIsoElectrons"));


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////
  ///Tau Variables///
  ///////////////////
  handler->addEventVariable("NGOODTAUS",            new EventVariableN("NGOODTAUS",                          "goodTaus"));
  handler->addEventVariable("QGOODTAUS",            new EventVariableObjectVariableVector<int>("CHARGE",     "goodTaus"));
  handler->addEventVariable("PTGOODTAUS",           new EventVariableObjectVariableVector<double>("PT",      "goodTaus"));
  handler->addEventVariable("ETAGOODTAUS",          new EventVariableObjectVariableVector<double>("ETA",     "goodTaus"));
  handler->addEventVariable("PHIGOODTAUS",          new EventVariableObjectVariableVector<double>("PHI",     "goodTaus"));
  handler->addEventVariable("fakeRoleGOODTAUS",     new EventVariableObjectVariableVector<int>("fakeRole",   "goodTaus"));
  handler->addEventVariable("TOTALISOGOODTAUS",     new EventVariableObjectVariableVector<double>("TOTALISO","goodTaus"));
  handler->addEventVariable("TOTALMINIISOGOODTAUS", new EventVariableObjectVariableVector<double>("TOTALMINIISO","goodTaus"));
  handler->addEventVariable("MINIISOGOODTAUS",      new EventVariableObjectVariableVector<double>("MINIISO","goodTaus"));
  //
  handler->addEventVariable("NBASICTAUS",        new EventVariableN("NBASICTAUS",                         "basicTaus"));
  handler->addEventVariable("PTBASICTAUS",       new EventVariableObjectVariableVector<double>("PT",      "basicTaus"));
  handler->addEventVariable("ETABASICTAUS",      new EventVariableObjectVariableVector<double>("ETA",     "basicTaus"));
  handler->addEventVariable("PHIBASICTAUS",      new EventVariableObjectVariableVector<double>("PHI",     "basicTaus"));
  handler->addEventVariable("RELISOBASICTAUS",   new EventVariableObjectVariableVector<double>("RELISO",  "basicTaus"));
  handler->addEventVariable("TOTALISOBASICTAUS", new EventVariableObjectVariableVector<double>("TOTALISO","basicTaus"));
  //
  handler->addEventVariable("NNONISOTAUS", new EventVariableN("NNONISOTAUS","nonIsoTaus"));



  // --------------------------------------------------------------------------------------------------------------
  ///////////////////
  ///Jet Variables///
  ///////////////////
  handler->addEventVariable("NBASICJETS",       new EventVariableN("NBASICJETS",                         "basicJets"));
  handler->addEventVariable("PTBASICJETS",      new EventVariableObjectVariableVector<double>("PT",      "basicJets"));
  handler->addEventVariable("ETABASICJETS",     new EventVariableObjectVariableVector<double>("ETA",     "basicJets"));
  handler->addEventVariable("PHIBASICJETS",     new EventVariableObjectVariableVector<double>("PHI",     "basicJets"));
  handler->addEventVariable("CSVRAWBASICJETS",  new EventVariableObjectVariableVector<double>("CSVraw",  "basicJets"));
  handler->addEventVariable("JPRAWBASICJETS",   new EventVariableObjectVariableVector<double>("JPraw",   "basicJets"));
  handler->addEventVariable("CMVARAWBASICJETS", new EventVariableObjectVariableVector<double>("cMVAraw", "basicJets"));
  handler->addEventVariable("TOTALMULTBASICJETS",         new EventVariableObjectVariableVector<double>("numberOfConstituents",        "basicJets"));
  handler->addEventVariable("CHARMULTBASICJETS",          new EventVariableObjectVariableVector<double>("chargedMultiplicity",         "basicJets"));
  handler->addEventVariable("NEUTMULTBASICJETS",          new EventVariableObjectVariableVector<double>("neutralMultiplicity",         "basicJets"));
  handler->addEventVariable("MUONENERGYFRACBASICJETS",    new EventVariableObjectVariableVector<double>("muonEnergyFraction",          "basicJets"));
  handler->addEventVariable("CHARHADENERGYFRACBASICJETS", new EventVariableObjectVariableVector<double>("chargedHadronEnergyFraction", "basicJets"));
  handler->addEventVariable("CHAREMENERGYFRACBASICJETS",  new EventVariableObjectVariableVector<double>("chargedEmEnergyFraction",     "basicJets"));
  handler->addEventVariable("NEUTHADENERGYFRACBASICJETS", new EventVariableObjectVariableVector<double>("neutralHadronEnergyFraction", "basicJets"));
  handler->addEventVariable("NEUTEMENERGYFRACBASICJETS",  new EventVariableObjectVariableVector<double>("neutralEmEnergyFraction",     "basicJets"));
  //
  handler->addEventVariable("NGOODJETS",          new EventVariableN("NGOODJETS",                          "goodJets"));
  handler->addEventVariable("PTGOODJETS",         new EventVariableObjectVariableVector<double>("PT",      "goodJets"));
  handler->addEventVariable("ETAGOODJETS",        new EventVariableObjectVariableVector<double>("ETA",     "goodJets"));
  handler->addEventVariable("PHIGOODJETS",        new EventVariableObjectVariableVector<double>("PHI",     "goodJets"));
  handler->addEventVariable("CSVRAWGOODJETS",     new EventVariableObjectVariableVector<double>("CSVraw",  "goodJets"));
  handler->addEventVariable("JPRAWGOODJETS",      new EventVariableObjectVariableVector<double>("JPraw",   "goodJets"));
  handler->addEventVariable("CMVARAWGOODJETS",    new EventVariableObjectVariableVector<double>("cMVAraw", "goodJets"));
  //
  handler->addEventVariable("NGOODFORWARDJETS",   new EventVariableN("NGOODFORWARDJETS",                "goodForwardJets"));
  handler->addEventVariable("PTGOODFORWARDJETS",  new EventVariableObjectVariableVector<double>("PT",   "goodForwardJets"));
  handler->addEventVariable("ETAGOODFORWARDJETS", new EventVariableObjectVariableVector<double>("ETA",  "goodForwardJets"));
  handler->addEventVariable("PHIGOODFORWARDJETS", new EventVariableObjectVariableVector<double>("PHI",  "goodForwardJets"));
  //
  handler->addEventVariable("NGOODBJETSCSVL",     new EventVariableN("NGOODJETS",                       "goodbJetsCSVL"));
  handler->addEventVariable("PTGOODBJETSCSVL",    new EventVariableObjectVariableVector<double>("PT",   "goodbJetsCSVL"));
  handler->addEventVariable("ETAGOODBJETSCSVL",   new EventVariableObjectVariableVector<double>("ETA",  "goodbJetsCSVL"));
  handler->addEventVariable("PHIGOODBJETSCSVL",   new EventVariableObjectVariableVector<double>("PHI",  "goodbJetsCSVL"));
  //
  handler->addEventVariable("NGOODBJETSCSVM",     new EventVariableN("NGOODJETS",                       "goodbJetsCSVM"));
  handler->addEventVariable("PTGOODBJETSCSVM",    new EventVariableObjectVariableVector<double>("PT",   "goodbJetsCSVM"));
  handler->addEventVariable("ETAGOODBJETSCSVM",   new EventVariableObjectVariableVector<double>("ETA",  "goodbJetsCSVM"));
  handler->addEventVariable("PHIGOODBJETSCSVM",   new EventVariableObjectVariableVector<double>("PHI",  "goodbJetsCSVM"));
  //
  handler->addEventVariable("HT",         new EventVariableSumPT("HT",     "goodJets"));
  handler->addEventVariable("HTCSVL",     new EventVariableSumPT("HTCSVL", "goodbJetsCSVL"));
  handler->addEventVariable("HTCSVM",     new EventVariableSumPT("HTCSVM", "goodbJetsCSVM"));
  handler->addEventVariable("NBJETSCSVL", new EventVariableN("NBJETSCSVL", "goodbJetsCSVL"));
  handler->addEventVariable("NBJETSCSVM", new EventVariableN("NBJETSCSVM", "goodbJetsCSVM"));
  handler->addEventVariable("WDIJETMASS", new EventVariablePairMass("WDIJETMASS", "goodJets", "WJET", mW, 10));


  // --------------------------------------------------------------------------------------------------------------
  //////////////////////
  ///Photon Variables///
  //////////////////////
  handler->addEventVariable("NBASICPHOTONS",   new EventVariableN("NBASICPHOTONS",                  "basicPhotons"));
  handler->addEventVariable("PTBASICPHOTONS",  new EventVariableObjectVariableVector<double>("PT",  "basicPhotons"));
  handler->addEventVariable("ETABASICPHOTONS", new EventVariableObjectVariableVector<double>("ETA", "basicPhotons"));
  handler->addEventVariable("PHIBASICPHOTONS", new EventVariableObjectVariableVector<double>("PHI", "basicPhotons"));
  //
  handler->addEventVariable("NGOODPHOTONS",    new EventVariableN("NGOODPHOTONS",                   "goodPhotons"));
  handler->addEventVariable("PTGOODPHOTONS",   new EventVariableObjectVariableVector<double>("PT",  "goodPhotons"));
  handler->addEventVariable("ETAGOODPHOTONS",  new EventVariableObjectVariableVector<double>("ETA", "goodPhotons"));
  handler->addEventVariable("PHIGOODPHOTONS",  new EventVariableObjectVariableVector<double>("PHI", "goodPhotons"));
  //
  handler->addEventVariable("goodPhotonsDgoodJets",      new EventVariableDvector("goodPhotons", "goodJets"));
  handler->addEventVariable("goodPhotonsDgoodTaus",      new EventVariableDvector("goodPhotons", "goodTaus"));
  handler->addEventVariable("goodPhotonsDgoodElectrons", new EventVariableDvector("goodPhotons", "goodElectrons"));
  handler->addEventVariable("goodPhotonsDgoodMuons",     new EventVariableDvector("goodPhotons", "goodMuons"));
  //
  handler->addEventVariable("MPHOTONS",   new EventVariableMass("MPHOTONS", "goodPhotons"));

  
  // --------------------------------------------------------------------------------------------------------------
  /////////////////////
  ///Track Variables///
  /////////////////////
  handler->addEventVariable("NGOODINCLUSIVETRACKS",           new EventVariableN("NGOODTRACKS",                    "goodInclusiveTracks"));
  handler->addEventVariable("NBASICTRACKS",                   new EventVariableN("NBASICTRACKS",                   "basicTracks"));
  handler->addEventVariable("NISOTRACKS",                     new EventVariableN("NISOTRACKS",                     "isoTracks"));
  handler->addEventVariable("NISOINCLUSIVETRACKS",            new EventVariableN("NISOINCLUSIVETRACKS",            "isoInclusiveTracks"));
  handler->addEventVariable("NPROMPTTRACKS",                  new EventVariableN("NPROMPTTRACKS",                  "promptTracks"));
  handler->addEventVariable("NPROMPTINCLUSIVETRACKS",         new EventVariableN("NPROMPTINCLUSIVETRACKS",         "promptInclusiveTracks"));
  handler->addEventVariable("NISONONPROMPTINCLUSIVETRACKS",   new EventVariableN("NISONONPROMPTINCLUSIVETRACKS",   "isoNonPromptInclusiveTracks"));
  handler->addEventVariable("NPROMPTNONISOINCLUSIVETRACKS",   new EventVariableN("NPROMPTNONISOINCLUSIVETRACKS",   "promptNonIsoInclusiveTracks"));
  handler->addEventVariable("NINCLUSIVETRACKS7",              new EventVariableN("NINCLUSIVETRACKS7",              "inclusiveTracks7"));
  handler->addEventVariable("NISOINCLUSIVETRACKS7",           new EventVariableN("NISOINCLUSIVETRACKS7",           "isoInclusiveTracks7"));
  handler->addEventVariable("NPROMPTINCLUSIVETRACKS7",        new EventVariableN("NPROMPTINCLUSIVETRACKS7",        "promptInclusiveTracks7"));
  handler->addEventVariable("NPROMPTIREL0p30INCLUSIVETRACKS7",new EventVariableN("NPROMPTIREL0p30INCLUSIVETRACKS7","promptIREL0p30InclusiveTracks7"));
  handler->addEventVariable("NISONONPROMPTINCLUSIVETRACKS7",  new EventVariableN("NISONONPROMPTINCLUSIVETRACKS7",  "isoNonPromptInclusiveTracks7"));
  handler->addEventVariable("NPROMPTNONISOINCLUSIVETRACKS7",  new EventVariableN("NPROMPTNONISOINCLUSIVETRACKS7",  "promptNonIsoInclusiveTracks7"));
  handler->addEventVariable("NBASICTRACKS7",                  new EventVariableN("NBASICTRACKS7",                  "basicTracks7"));
  handler->addEventVariable("NISOTRACKS7",                    new EventVariableN("NISOTRACKS7",                    "isoTracks7"));
  handler->addEventVariable("NPROMPTTRACKS7",                 new EventVariableN("NPROMPTTRACKS7",                 "promptTracks7"));
  handler->addEventVariable("NISONONPROMPTTRACKS7",           new EventVariableN("NISONONPROMPTTRACKS7",           "isoNonPromptTracks7"));
  handler->addEventVariable("NPROMPTNONISOTRACKS7",           new EventVariableN("NPROMPTNONISOTRACKS7",           "promptNonIsoTracks7"));
  //
  handler->addEventVariable("NGOODTRACKS",            new EventVariableN("NGOODTRACKS",                       "goodTracks"));
  handler->addEventVariable("QGOODTRACKS",            new EventVariableObjectVariableVector<int>("CHARGE",    "goodTracks"));
  handler->addEventVariable("PTGOODTRACKS",           new EventVariableObjectVariableVector<double>("PT",     "goodTracks"));
  handler->addEventVariable("ETAGOODTRACKS",          new EventVariableObjectVariableVector<double>("ETA",    "goodTracks"));
  //
  handler->addEventVariable("NINCLUSIVETRACKS",       new EventVariableN("NINCLUSIVETRACKS",                  "inclusiveTracks"));
  handler->addEventVariable("PTINCLUSIVETRACKS",      new EventVariableObjectVariableVector<double>("PT",     "inclusiveTracks"));
  handler->addEventVariable("ETAINCLUSIVETRACKS",     new EventVariableObjectVariableVector<double>("ETA",    "inclusiveTracks"));
  handler->addEventVariable("RELISOINCLUSIVETRACKS",  new EventVariableObjectVariableVector<double>("RELISO", "inclusiveTracks"));
  handler->addEventVariable("MINIISOINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("MINIISO","inclusiveTracks"));
  handler->addEventVariable("PTRATIOINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("ptRatio","inclusiveTracks"));
  handler->addEventVariable("PTRELINCLUSIVETRACKS",   new EventVariableObjectVariableVector<double>("ptRel",  "inclusiveTracks"));
  //  
  handler->addEventVariable("NISONONPROMPTTRACKS",    new EventVariableN("NISONONPROMPTTRACKS",               "isoNonPromptTracks"));
  handler->addEventVariable("PTISONONPROMPTTRACKS",   new EventVariableObjectVariableVector<double>("PT",     "isoNonPromptTracks"));
  handler->addEventVariable("ETAISONONPROMPTTRACKS",  new EventVariableObjectVariableVector<double>("ETA",    "isoNonPromptTracks"));
  //
  handler->addEventVariable("NPROMPTNONISOTRACKS",    new EventVariableN("NPROMPTNONISOTRACKS",               "promptNonIsoTracks"));
  handler->addEventVariable("PTPROMPTNONISOTRACKS",   new EventVariableObjectVariableVector<double>("PT",     "promptNonIsoTracks"));
  handler->addEventVariable("ETAPROMPTNONISOTRACKS",  new EventVariableObjectVariableVector<double>("ETA",    "promptNonIsoTracks"));


  // --------------------------------------------------------------------------------------------------------------
  //////////////////////
  ///Vertex Variables///
  //////////////////////
  handler->addEventVariable("NRECOVERTICES",          new EventVariableN("NRECOVERTICES","recoVertices"));
  handler->addEventVariable("NRECOVERTICESDRCLEANED", new EventVariableN("NRECOVERTICES","recoVerticesDrCleaned"));


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////
  ///MET Variables///
  ///////////////////
  setupMET(handler, isMC);


  // --------------------------------------------------------------------------------------------------------------
  /////////////////////////
  ///Composite Variables///
  /////////////////////////
  handler->addEventVariable("MT", new EventVariableMT("MT", mZ,"","goodElectrons","goodMuons",""));
  //
  EventVariableSumPT* LT = new EventVariableSumPT("LT","goodMuons");//sum over all leptons
  LT->addProduct("goodElectrons");
  LT->addProduct("goodTaus");
  handler->addEventVariable("LT",LT);
  //
  EventVariableSumPT* LT2 = new EventVariableSumPT("LT2","goodMuons",2);//sum over leading 2 leptons only! (if present)
  LT2->addProduct("goodElectrons");
  LT2->addProduct("goodTaus");
  handler->addEventVariable("LT2",LT2);
  //
  EventVariableSumPT* LT3 = new EventVariableSumPT("LT3","goodMuons",3);//sum over leading 3 leptons only! (if present)
  LT3->addProduct("goodElectrons");
  LT3->addProduct("goodTaus");
  handler->addEventVariable("LT3",LT3);
  //
  EventVariableSumPT* LT4 = new EventVariableSumPT("LT4","goodMuons",4);//sum over leading 4 leptons only! (if present)
  LT4->addProduct("goodElectrons");
  LT4->addProduct("goodTaus");
  handler->addEventVariable("LT4",LT4);
  //
  EventVariableSumPT* ST = new EventVariableSumPT("ST","goodMuons");
  ST->addProduct("goodElectrons");
  ST->addProduct("goodTaus");
  ST->addProduct("goodJets");
  ST->addProduct("MET");
  handler->addEventVariable("ST",ST);
  //
  EventVariableMass* massLeptons = new EventVariableMass("MLEPTONS", "goodElectrons");
  massLeptons->addProduct("goodMuons");
  massLeptons->addProduct("goodTaus");
  handler->addEventVariable("MLEPTONS", massLeptons);
  //
  EventVariableMass* massLightLeptons = new EventVariableMass("MLIGHTLEPTONS", "goodElectrons");
  massLightLeptons->addProduct("goodMuons");
  handler->addEventVariable("MLIGHTLEPTONS", massLightLeptons);
  //
  EventVariableN* nLeptons = new EventVariableN("NLEPTONS", "goodElectrons");
  nLeptons->addProduct("goodMuons");
  nLeptons->addProduct("goodTaus");
  handler->addEventVariable("NLEPTONS", nLeptons);
  //  
  EventVariableN* nLightLeptons = new EventVariableN("NLIGHTLEPTONS", "goodElectrons");
  nLightLeptons->addProduct("goodMuons");
  handler->addEventVariable("NLIGHTLEPTONS", nLightLeptons);
  //
  EventVariableInRange<double>* mLightLeptonsOnZ = new EventVariableInRange<double>("MLIGHTLEPTONS", mZ-zWidth, mZ+zWidth, "MLIGHTLEPTONSONZ");
  handler->addEventVariable("MLIGHTLEPTONSONZ", mLightLeptonsOnZ);
  //
  EventVariableInRange<int>* threeLightLeptons = new EventVariableInRange<int>("NLIGHTLEPTONS", 3, 3, "THREELIGHTLEPTONS");
  handler->addEventVariable("THREELIGHTLEPTONS", threeLightLeptons);
  //
  EventVariableOSSF* OSSF = new EventVariableOSSF("OSSF","goodMuons","",mZ,zWidth);
  OSSF->addProduct("goodElectrons");
  handler->addEventVariable("OSSF",OSSF);
  //
  EventVariableOSSF* OSSFnoFake = new EventVariableOSSF("OSSFnoFake","goodMuons","NOFAKE",mZ,zWidth, false);
  OSSFnoFake->addProduct("goodElectrons");
  handler->addEventVariable("OSSFnoFake",OSSFnoFake);
  //
  EventVariableOSSF* RA7OSSF = new EventVariableOSSF("RA7OSSF", "goodMuons", "RA7", 91, 15);
  RA7OSSF->addProduct("goodElectrons");
  handler->addEventVariable("RA7OSSF", RA7OSSF);
  //
  EventVariableReversed* offZ = new EventVariableReversed("ONZ", "OFFZ");
  handler->addEventVariable("OFFZ", offZ);
  //
  EventVariableInRange<int>* NOSSFgt0 = new EventVariableInRange<int>("NOSSF", 1, 1e6, "NOSSFgt0");
  handler->addEventVariable("NOSSFgt0", NOSSFgt0);
  //
  EventVariableCombined* AIC = new EventVariableCombined("THREELIGHTLEPTONS", "MLIGHTLEPTONSONZ", true, "AIC");
  AIC->addVariable("NOSSFgt0");
  AIC->addVariable("OFFZ");
  handler->addEventVariable("AIC", AIC);
  
  /*
  if(handler->getMode("singleGoodMuon")) {// fix
    handler->addEventVariable("WRITEEVENT", new EventVariableInRange<int>("NGOODMUONS", 1, 1e6, "GOODMUON"));
  } else if(handler->getMode("theoryMinituples")) {
    handler->addEventVariable("WRITEEVENT", new EventVariableRename<bool>("ALWAYSTRUE"));
  } else {
    EventVariableCombined* writeEvent = handler->getMode("RA7")
      ? new EventVariableCombined("MLOWDYCUT", "MLOWDYCUT", true, "WRITEEVENT")
      : new EventVariableCombined("DILEPTONSLOWPT", "MLOWDYCUT", true, "WRITEEVENT");
    handler->addEventVariable("WRITEEVENT", writeEvent);
  }
  */

  handler->addEventVariable("ALWAYSTRUE", new EventVariableConst<bool>(true));
  handler->addEventVariable("WRITEEVENT", new EventVariableRename<bool>("ALWAYSTRUE"));

}


// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------


void setupTriggers(BaseHandler* handler,int mode){
  // --------------------------------------------------------------------------------------------------------------
  ///////////////////////////////////
  ///HLT-related Offline Variables///
  ///////////////////////////////////
  // handler->addObjectVariable("ETA3",new ObjectVariableInRange<double>("ETA",-3.0,3.0,"ETA3"));  
  EventVariableSumPT* HLT_HT = new EventVariableSumPT("HLT_HT","hltJets");
  HLT_HT->addProduct("hltForwardJets");
  handler->addEventVariable("HLT_HT",HLT_HT);


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////////////////////
  ///HLT Variables///
  ///////////////////////////////////
  //handler->addObjectVariable("ACCEPT", new ObjectVariableRename<bool>("accept","ACCEPT"));
  //handler->addObjectVariable("TRIGGERNAME", new ObjectVariableRename<TString>("triggerName","TRIGGERNAME"));
  
  //handler->addProduct("ALLTRIGGERS","ALL");
  //handler->addObjectVariable("isTrigger", new ObjectVariableValue<TString>("INPUTTYPE", "trigger"));
  //handler->addProductCut("TRIGGERS","isTrigger");
  //handler->addHistogram(new SignatureTH1F_TriggerName("TriggerNames","ALLTRIGGERS"));
  
  //handler->addObjectVariable("Accepted", new ObjectVariableValue<bool>("ACCEPT", true));
  //handler->addObjectVariable("WasRun", new ObjectVariableValue<bool>("wasrun", true));

  // ------------------------------------------------------------------------
  // ------------------------------------------------------------------------
  // HLT bundles
  // These are supposed to include all paths for data and MC.
  // To be maintained! (Feb 26, 2016)
  // ------------------------------------------------------------------------
  // All available final HLT variables are listed here:
  //    -------------- All Muon
  //    IsoMuHLT
  //    MuHLTprescaled
  //    Mu45eta2p1HLT
  //    Mu50HLT
  //    IsoDiMuHLT
  //    DiMuHLT
  //    DiMuSSHLTmc   <<<< for  MC  only
  //    DiMuSSHLTdata <<<< for DATA only
  //    TripleMuHLT
  //    -------------- All Electron
  //    IsoEleHLTmc   <<<< for  MC  only
  //    IsoEleHLTdata <<<< for DATA only
  //    EleHLT
  //    IsoDiEleHLT
  //    DiEleHLT
  //    TripleEleHLT
  //    -------------- Mixed
  //    IsoMuEleHLT
  //    MuEleHLT
  //    MuMuEleHLT
  //    MuEleEleHLT
  //    DiMuHTHLT
  //    DiEleHTHLT
  //    MuEleHTHLT
  // ------------------------------------------------------------------------
  std::vector< vector<pair<string, string> > > RutgersHLT;
  // All-muon paths
  std::vector< pair<string, string> > IsoMuHLT;
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu20_v1"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu20_v2"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu20_v3"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu20_v1"));//these are ORed for higher eff, mentioned in the muon POG Twiki.
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu20_v2"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu20_v3"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu20_v4"));
  RutgersHLT.push_back(IsoMuHLT);
  std::vector< pair<string, string> > MuHLTprescaled;
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu17_v1"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu17_v2"));
  RutgersHLT.push_back(MuHLTprescaled);
  std::vector< pair<string, string> > Mu45eta2p1HLT;
  Mu45eta2p1HLT.push_back(std::make_pair("Mu45eta2p1HLT","HLT_Mu45_eta2p1_v1"));
  Mu45eta2p1HLT.push_back(std::make_pair("Mu45eta2p1HLT","HLT_Mu45_eta2p1_v2"));
  RutgersHLT.push_back(Mu45eta2p1HLT);
  std::vector< pair<string, string> > Mu50HLT;
  Mu50HLT.push_back(std::make_pair("Mu50HLT","HLT_Mu50_v1"));
  Mu50HLT.push_back(std::make_pair("Mu50HLT","HLT_Mu50_v2"));
  RutgersHLT.push_back(Mu50HLT);
  std::vector< pair<string, string> > IsoDiMuHLT;
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2"));
  RutgersHLT.push_back(IsoDiMuHLT);
  std::vector< pair<string, string> > DiMuHLT;
  DiMuHLT.push_back(std::make_pair("DiMuHLT","HLT_Mu30_TkMu11_v1"));
  DiMuHLT.push_back(std::make_pair("DiMuHLT","HLT_Mu30_TkMu11_v2"));
  RutgersHLT.push_back(DiMuHLT);
  std::vector< pair<string, string> > DiMuSSHLTmc;
  DiMuSSHLTmc.push_back(std::make_pair("DiMuSSHLTmc","HLT_Mu17_Mu8_DZ_v1"));//...........MC and DATA, but not full-lumi in DATA
  RutgersHLT.push_back(DiMuSSHLTmc);
  std::vector< pair<string, string> > DiMuSSHLTdata;
  DiMuSSHLTdata.push_back(std::make_pair("DiMuSSHLTdata","HLT_Mu17_Mu8_SameSign_DZ_v1"));//..DATA-only
  RutgersHLT.push_back(DiMuSSHLTdata);
  std::vector< pair<string, string> > TripleMuHLT;
  TripleMuHLT.push_back(std::make_pair("TripleMuHLT","HLT_TripleMu_12_10_5_v1"));
  TripleMuHLT.push_back(std::make_pair("TripleMuHLT","HLT_TripleMu_12_10_5_v2"));
  RutgersHLT.push_back(TripleMuHLT);
  // ------------------------------------------------------------------------
  // All-electron paths
  std::vector< pair<string, string> > IsoEleHLTmc;
  IsoEleHLTmc.push_back(std::make_pair("IsoEleHLTmc","HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v1"));//..MC and DATA, but not full-lumi in DATA
  RutgersHLT.push_back(IsoEleHLTmc);
  std::vector< pair<string, string> > IsoEleHLTdata;
  IsoEleHLTdata.push_back(std::make_pair("IsoEleHLTdata","HLT_Ele23_WPLoose_Gsf_v1"));//...........Data-only
  IsoEleHLTdata.push_back(std::make_pair("IsoEleHLTdata","HLT_Ele23_WPLoose_Gsf_v2"));//...........Data-only
  IsoEleHLTdata.push_back(std::make_pair("IsoEleHLTdata","HLT_Ele23_WPLoose_Gsf_v3"));//...........Data-only
  RutgersHLT.push_back(IsoEleHLTdata);
  std::vector< pair<string, string> > EleHLT;
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v1"));
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v2"));
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v3"));
  RutgersHLT.push_back(EleHLT);
  std::vector< pair<string, string> > IsoDiEleHLT;
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1"));
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2"));
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3"));
  RutgersHLT.push_back(IsoDiEleHLT);
  std::vector< pair<string, string> > DiEleHLT;
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v1"));
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v2"));
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v3"));
  RutgersHLT.push_back(DiEleHLT);
  std::vector< pair<string, string> > TripleEleHLT;
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1"));
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v2"));
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v3"));
  RutgersHLT.push_back(TripleEleHLT);
  // ------------------------------------------------------------------------
  // Mixed multi-lepton paths
  std::vector< pair<string, string> > IsoMuEleHLT;
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3"));
  RutgersHLT.push_back(IsoMuEleHLT);
  std::vector< pair<string, string> > MuEleHLT;
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v1"));
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v2"));
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v3"));
  RutgersHLT.push_back(MuEleHLT);
  std::vector< pair<string, string> > MuMuEleHLT;
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1"));
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v2"));
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v3"));
  RutgersHLT.push_back(MuMuEleHLT);
  std::vector< pair<string, string> > MuEleEleHLT;
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1"));
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v2"));
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v3"));
  RutgersHLT.push_back(MuEleEleHLT);
  // ------------------------------------------------------------------------
  // Di-lepton + PFHT paths
  std::vector< pair<string, string> > DiMuHTHLT;
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v1"));
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v2"));
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v3"));
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v4"));
  RutgersHLT.push_back(DiMuHTHLT);
  std::vector< pair<string, string> > DiEleHTHLT;
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v2"));
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v3"));
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v4"));
  RutgersHLT.push_back(DiEleHTHLT);
  std::vector< pair<string, string> > MuEleHTHLT;
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2"));
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v3"));
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v4"));
  RutgersHLT.push_back(MuEleHTHLT);
  // ------------------------------------------------------------------------

  // Store all *individual* HLTpaths and HLTpath groups as specified above:
  for(unsigned int i=0; i<RutgersHLT.size(); i++){
    std::vector< pair<string, string> > HLTgroup = RutgersHLT.at(i);
    if( HLTgroup.size()==0 ) continue;
    //
    TString   HLTgroupName = HLTgroup.at(0).first;
    TString isHLTgroupName = TString::Format("is%s",HLTgroupName.Data());
    //
    //cout<<"HLT group: "<<HLTgroupName.Data()<<endl;
    //
    handler->addProduct(HLTgroupName,"goodtriggers");
    //
    ObjectVariableValueInList<TString>* isHLTgroup = new ObjectVariableValueInList<TString>("TRIGGERNAME","placeHolderHLTname");
    // "placeHolderHLTname" in the above line just makes looping over & adding individual hltpaths to isHLTgroup below easier.
    for(unsigned int j=0; j<HLTgroup.size(); j++){
      TString   HLTname = HLTgroup.at(j).second;
      isHLTgroup->addValue(HLTname);
    }
    //
    handler->addObjectVariable(isHLTgroupName,isHLTgroup);
    handler->addProductCut(HLTgroupName,isHLTgroupName);
    TString nname = TString::Format("N%s",HLTgroupName.Data());
    handler->addEventVariable(nname,new EventVariableN(nname,HLTgroupName));// count
    TString acceptname = TString::Format("ACCEPT_%s",HLTgroupName.Data());
    handler->addEventVariable(acceptname,new EventVariableInRange<int>(nname,1,100000));//............................ACCEPT true/false
    handler->addEventVariable(TString::Format("REJECT_%s",HLTgroupName.Data()),new EventVariableReversed(acceptname));//..REJECT true/false
    //
    // ------------------------------------------------------------------------
    // Store all HLT path names specified above
    TString   HLTpathName = HLTgroup.at(0).second;
    TString isHLTpathName = TString::Format("is%s",HLTpathName.Data());
    handler->addProduct(HLTpathName,"goodtriggers");
    //
    ObjectVariableValue<TString>* isHLTpath = new ObjectVariableValue<TString>("TRIGGERNAME",HLTpathName.Data());
    handler->addObjectVariable(isHLTpathName,isHLTpath);
    handler->addProductCut(HLTpathName,isHLTpathName);
    //
    TString nnamepath = TString::Format("N%s",HLTpathName.Data());
    EventVariableN* HLTpathCount = new EventVariableN(nnamepath,HLTpathName);// count
    handler->addEventVariable(nnamepath,HLTpathCount);
    TString acceptnamepath =  TString::Format("ACCEPT_%s",HLTpathName.Data());
    handler->addEventVariable(acceptnamepath,new EventVariableInRange<int>(nnamepath,1,100000));//.......................ACCEPT true/false
    handler->addEventVariable(TString::Format("REJECT_%s",HLTpathName.Data()),new EventVariableReversed(acceptnamepath));//..REJECT true/false
  }
  // ------------------------------------------------------------------------
  // ------------------------------------------------------------------------  


  // WORK-IN-PROGRESS: trig tresholds 

  //Offline tresholds for higher trigger efficiencies
  /*
  // Single Electron
  EventVariableThreshold* singElTrig = new EventVariableThreshold("singeltrig","goodElectrons");
  singElTrig->addThreshold(26);
  handler->addEventVariable("SINGELTRIGTHRESHOLD",singElTrig);

  // Single Muon
  EventVariableThreshold* singMuTrig = new EventVariableThreshold("singmutrig","goodMuons");
  singMuTrig->addThreshold(20);
  handler->addEventVariable("SINGMUTRIGTHRESHOLD",singMuTrig);
  */

  // Di-Electron treshold
  EventVariableThreshold* dieltrig = new EventVariableThreshold("dieltrig","goodElectrons");
  dieltrig->addThreshold(20);
  dieltrig->addThreshold(15);
  handler->addEventVariable("DIELTRIGTHRESHOLD",dieltrig);

  // Di-Muon treshold
  EventVariableThreshold* dimutrig = new EventVariableThreshold("dimutrig","goodMuons");
  dimutrig->addThreshold(17);
  dimutrig->addThreshold(8);
  handler->addEventVariable("DIMUTRIGTHRESHOLD",dimutrig);

  // Mu-Ele treshold
  // Leading Electron - Subleading Muon : (20, 8)
  EventVariableThreshold* ellead = new EventVariableThreshold("ellead","goodElectrons");//........leading ele cut
  ellead->addThreshold(20);
  handler->addEventVariable("EGMULEADTHRESHOLD",ellead);
  EventVariableThreshold* musublead = new EventVariableThreshold("musublead","goodMuons");//......subleading mu cut
  musublead->addThreshold(8);
  handler->addEventVariable("EGMUSUBLEADTHRESHOLD",musublead);
  handler->addEventVariable("EGMUTHRESHOLD",new EventVariableCombined("EGMULEADTHRESHOLD","EGMUSUBLEADTHRESHOLD",true));
  //
  // Leading Muon - Subleading Electron : (17,15)
  EventVariableThreshold* mulead = new EventVariableThreshold("mulead","goodMuons");//............leading mu cut
  mulead->addThreshold(17);
  handler->addEventVariable("MUEGLEADTHRESHOLD",mulead);
  EventVariableThreshold* elsublead = new EventVariableThreshold("elsublead","goodElectrons");//..subleading ele cut
  elsublead->addThreshold(15);
  handler->addEventVariable("MUEGSUBLEADTHRESHOLD",elsublead);
  handler->addEventVariable("MUEGTHRESHOLD",new EventVariableCombined("MUEGLEADTHRESHOLD","MUEGSUBLEADTHRESHOLD",true));
  //
  handler->addEventVariable("MUEGCOMBINEDTHRESHOLD", new EventVariableCombined("MUEGTHRESHOLD","EGMUTHRESHOLD"));


  EventVariableCombined* trigaccept = NULL;
  switch(mode){
  case 1:
    handler->addEventVariable("TRIGGERACCEPT",new EventVariableRename<bool>("ACCEPT_IsoMuEleHLT"));
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("MUEG")));
    break;
  case 2:
    handler->addEventVariable("TRIGGERACCEPT",new EventVariableCombined("ACCEPT_IsoDiMuHLT","REJECT_IsoMuEleHLT",true));
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("DOUBLEMU")));
    break;
  case 3:
    trigaccept = new EventVariableCombined("ACCEPT_IsoDiEleHLT","REJECT_IsoDiMuHLT",true);
    trigaccept->addVariable("REJECT_IsoMuEleHLT");
    handler->addEventVariable("TRIGGERACCEPT",trigaccept);
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("DOUBLEEG")));
    break;
    // -----------------------------------------------------------
  case 4:
    trigaccept = new EventVariableCombined("ACCEPT_IsoMuHLT","REJECT_IsoDiEleHLT",true);
    trigaccept->addVariable("REJECT_IsoDiMuHLT");
    trigaccept->addVariable("REJECT_IsoMuEleHLT");
    handler->addEventVariable("TRIGGERACCEPT",trigaccept);
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("SINGLEMU")));
    break;
  case 5:
    trigaccept = new EventVariableCombined("ACCEPT_IsoEleHLTdata","REJECT_IsoDiEleHLT",true);//................DATA ONLY
    trigaccept->addVariable("REJECT_IsoMuHLT");
    trigaccept->addVariable("REJECT_IsoDiMuHLT");
    trigaccept->addVariable("REJECT_IsoMuEleHLT");
    handler->addEventVariable("TRIGGERACCEPT",trigaccept);
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("SINGLEEL")));
    break;
    // -----------------------------------------------------------
  case 6:
    trigaccept = new EventVariableCombined("ACCEPT_IsoDiEleHLT", "ACCEPT_IsoDiMuHLT",false);
    trigaccept->addVariable("ACCEPT_IsoMuEleHLT");
    trigaccept->addVariable("ACCEPT_DiEleHTHLT");
    trigaccept->addVariable("ACCEPT_DiMuHTHLT");
    trigaccept->addVariable("ACCEPT_MuEleHTHLT");
    trigaccept->addVariable("ACCEPT_TripleEleHLT");
    trigaccept->addVariable("ACCEPT_MuEleEleHLT");
    trigaccept->addVariable("ACCEPT_MuMuEleHLT");
    trigaccept->addVariable("ACCEPT_TripleMuHLT");
    handler->addEventVariable("RA7TRIGGERACCEPT",trigaccept);
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("RA7leptons")));
    break;
  default:
    trigaccept = new EventVariableCombined("DIMUTRIGTHRESHOLD","DIELTRIGTHRESHOLD");
    trigaccept->addVariable("MUEGCOMBINEDTHRESHOLD");
    handler->addEventVariable("TRIGGERACCEPT",trigaccept);
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("DEFAULT")));
    break;
  }

}


// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupMCproducts(BaseHandler* handler) {
	handler->setMode("MC");
	handler->addProduct("ALLMC","ALL");
	handler->addProductCut("ALLMC","isMC");

	////////
	///MC///
	////////
	ObjectVariableValueInList<int>* electronPDGID = new ObjectVariableValueInList<int>("pdgId",11);
	electronPDGID->addValue(-11);
	handler->addObjectVariable("ELECTRONPDGID",electronPDGID);
	ObjectVariableValueInList<int>* muonPDGID = new ObjectVariableValueInList<int>("pdgId",13);
	muonPDGID->addValue(-13);
	handler->addObjectVariable("MUONPDGID",muonPDGID);
	ObjectVariableValueInList<int>* tauPDGID = new ObjectVariableValueInList<int>("pdgId",15);
	tauPDGID->addValue(-15);
	handler->addObjectVariable("TAUPDGID",tauPDGID);
	//
	handler->addObjectVariable("MOTHERZ", new ObjectVariableDescendantOf("allmc",23,handler));// allmc  23 
	handler->addObjectVariable("MOTHERW", new ObjectVariableDescendantOf("allmc",24,handler));
	handler->addObjectVariable("MOTHERH", new ObjectVariableDescendantOf("allmc",25,handler));
	handler->addObjectVariable("MOTHERLQ",new ObjectVariableDescendantOf("allmc",42,handler));
	//
	ObjectVariableCombined* motherBoson = new ObjectVariableCombined("MOTHERZ","MOTHERW",false);
	motherBoson->addVariable("MOTHERH");
	motherBoson->addVariable("MOTHERLQ");
	handler->addObjectVariable("MOTHERBOSON",motherBoson);
	//
	handler->addObjectVariable("MOTHERTAU",new ObjectVariableDescendantOf("allmc",15,handler));//15
	handler->addObjectVariable("STATUS1",  new ObjectVariableValue<int>("status",1));
	//
	ObjectVariableValueInList<int>* isBoson = new ObjectVariableValueInList<int>("pdgId",23);//Z
	isBoson->addValue(24);//..W
	isBoson->addValue(-24);//.W
	isBoson->addValue(25);//..H
	isBoson->addValue(42);//..LQ
	isBoson->addValue(-42);//.LQ
	handler->addObjectVariable("isBOSON",isBoson);


	handler->addProduct(   "BOSONS","ALLMC");
	handler->addProductCut("BOSONS","isBOSON");

	handler->addProduct(   "MCELECTRONS","ALLMC");
	handler->addProductCut("MCELECTRONS","ELECTRONPDGID");
	handler->addProductCut("MCELECTRONS","isLastCopy");
	//
	handler->addProduct(   "MCMUONS","ALLMC");
	handler->addProductCut("MCMUONS","MUONPDGID");
	handler->addProductCut("MCMUONS","isLastCopy");
	//
	handler->addProduct(   "MCTAUS","ALLMC");
	handler->addProductCut("MCTAUS","TAUPDGID");
	handler->addProductCut("MCTAUS","isLastCopy");

	handler->addProduct(   "MCELECTRONSFROMZ","MCELECTRONS");
	handler->addProductCut("MCELECTRONSFROMZ","MOTHERZ");
	//
	handler->addProduct(   "MCMUONSFROMZ","MCMUONS");
	handler->addProductCut("MCMUONSFROMZ","MOTHERZ");

	handler->addProduct(   "MCELECTRONSFROMBOSON","MCELECTRONS");
	handler->addProductCut("MCELECTRONSFROMBOSON","MOTHERBOSON");
	handler->addProductCut("MCELECTRONSFROMBOSON","STATUS1");
	//
	handler->addProduct(   "MCMUONSFROMBOSON","MCMUONS");
	handler->addProductCut("MCMUONSFROMBOSON","MOTHERBOSON");
	handler->addProductCut("MCMUONSFROMBOSON","STATUS1");
	//
	handler->addProduct(   "MCELECTRONSFROMTAU","MCELECTRONS");
	handler->addProductCut("MCELECTRONSFROMTAU","MOTHERTAU");
	handler->addProductCut("MCELECTRONSFROMTAU","STATUS1");
	//
	handler->addProduct(   "MCMUONSFROMTAU","MCMUONS");
	handler->addProductCut("MCMUONSFROMTAU","MOTHERTAU");
	handler->addProductCut("MCMUONSFROMTAU","STATUS1");
	//
	handler->addProduct(   "MCTAUSFROMBOSON","MCTAUS");
	handler->addProductCut("MCTAUSFROMBOSON","MOTHERBOSON");
	//
	// LEPTONICALLY DECAYING TAUS (from BOSON)
	handler->addObjectVariable("DAUGHTERELECTRON",new ObjectVariableMotherOf("allmc",11,handler));
	handler->addObjectVariable("DAUGHTERMUON",    new ObjectVariableMotherOf("allmc",13,handler));
        ObjectVariableCombined* daughterLepton = new ObjectVariableCombined("DAUGHTERELECTRON","DAUGHTERMUON",false);
        handler->addObjectVariable("DAUGHTERLEPTON",daughterLepton);
	handler->addProduct(   "MCLEPTONICTAUSFROMBOSON","MCTAUSFROMBOSON");
	handler->addProductCut("MCLEPTONICTAUSFROMBOSON","DAUGHTERLEPTON");
	//
	// HADRONICALLY DECAYING TAUS (from BOSON)
	ObjectComparisonDeltaR* deltaR0p01 = new ObjectComparisonDeltaR(0.01);	
        handler->addProduct(          "MCHADRONICTAUSFROMBOSON", "MCTAUSFROMBOSON");	
	handler->addProductComparison("MCHADRONICTAUSFROMBOSON", "MCLEPTONICTAUSFROMBOSON", deltaR0p01);//remove leptonically decaying taus
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupMCvariables(BaseHandler* handler, bool doMatching = false) {
  
  //////////////////////////////////////
  ///Matrix Method: Reco-Gen Matching///  EventVariableLeptonGenChecker  produces "IsGenMatched+suffix"
  //////////////////////////////////////
  EventVariableLeptonGenChecker* RecoGenMuons = new EventVariableLeptonGenChecker("RecoGenMuons","goodMuons","");//3rd suffix
  RecoGenMuons->addProduct("MCMUONSFROMBOSON");
  RecoGenMuons->addProduct("BOSONS");//used for debugging.
  handler->addEventVariable("RECOGENMUONS",RecoGenMuons);
  handler->addEventVariable("ISPROMPTMUON",new EventVariableObjectVariableVector<int>("IsGenMatched","goodMuons"));
  // ------------------------------------------------------------------------------------------------------------------------
  EventVariableLeptonGenChecker* RecoGenElectrons = new EventVariableLeptonGenChecker("RecoGenElectrons","goodElectrons","");//3rd suffix
  RecoGenElectrons->addProduct("MCELECTRONSFROMBOSON");
  RecoGenElectrons->addProduct("BOSONS");//used for debugging.
  handler->addEventVariable("RECOGENELECTRONS",RecoGenElectrons);
  handler->addEventVariable("ISPROMPTELECTRON",new EventVariableObjectVariableVector<int>("IsGenMatched","goodElectrons"));
  // ------------------------------------------------------------------------------------------------------------------------
  EventVariableLeptonGenChecker* RecoGenTaus = new EventVariableLeptonGenChecker("RecoGenTaus","goodTaus","");//3rd suffix
  RecoGenTaus->addProduct("MCTAUSFROMBOSON");
  RecoGenTaus->addProduct("BOSONS");//used for debugging.
  handler->addEventVariable("RECOGENTAUS",RecoGenTaus);
  handler->addEventVariable("ISPROMPTTAU",new EventVariableObjectVariableVector<int>("IsGenMatched","goodTaus"));//WARNING!
  // WARNING: NEED TO CHECK "ISPROMPTTAU" FOR ELE/MU->TAU FAKES! - SEE BELOW.
  // ------------------------------------------------------------------------------------------------------------------------
  // Gen Ele -> Reco Tau (checks for tau fakes)
  EventVariableLeptonGenChecker* RecoTauGenEles = new EventVariableLeptonGenChecker("RecoTauGenEles","goodTaus","EleFake");//3rd suffix
  //RecoTauGenEles->addProduct("MCELECTRONS");
  RecoTauGenEles->addProduct("MCELECTRONSFROMBOSON");
  handler->addEventVariable("RECOTAUGENELES",RecoTauGenEles);
  handler->addEventVariable("ISFAKETAUFROMELE",new EventVariableObjectVariableVector<int>("IsGenMatchedEleFake","goodTaus"));
  // ------------------------------------------------------------------------------------------------------------------------
  // Gen Muon -> Reco Tau (checks for tau fakes)
  EventVariableLeptonGenChecker* RecoTauGenMus = new EventVariableLeptonGenChecker("RecoTauGenMus","goodTaus","MuFake");//3rd suffix
  //RecoTauGenMus->addProduct("MCMUONS");
  RecoTauGenMus->addProduct("MCMUONSFROMBOSON");
  handler->addEventVariable("RECOTAUGENMUS",RecoTauGenMus);
  handler->addEventVariable("ISFAKETAUFROMMU",new EventVariableObjectVariableVector<int>("IsGenMatchedMuFake","goodTaus"));
  
  
  ////////////////////////
  ///MC matched leptons///
  ////////////////////////
  ObjectComparisonDeltaR* deltaR0p01 = new ObjectComparisonDeltaR(0.01);
  ObjectComparisonDeltaR* deltaR0p1  = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p3  = new ObjectComparisonDeltaR(0.3);
  //ObjectComparisonMatchDeltaRCharge* mcMatch   = new ObjectComparisonMatchDeltaRCharge(0.2,"genParticle");
  //ObjectComparisonMatchDeltaRCharge* recoMatch = new ObjectComparisonMatchDeltaRCharge(0.2,"recoCandidate");
  // Info:
  // ObjectComparisonMatchDeltaRCharge(double deltar,TString associateName="associate",TString name="objectcomparisonmatchdeltarcharge")
  
  // ------------- ------------- ------------- ------------- ------------- -------------
  // This is not used at the moment
  //if(doMatching) {
  //  handler->addProductComparison("goodElectrons","MCELECTRONSFROMBOSON",mcMatch, false);
  //  handler->addProductComparison("goodMuons",    "MCMUONSFROMBOSON",    mcMatch, false);
  //  handler->addProductComparison("goodTaus",     "MCTAUSFROMBOSON",     mcMatch, false);
  //}
  // ------------- ------------- ------------- ------------- ------------- -------------

  // BaseHandler::addProductComparison(TString pname1,TString pname2, ObjectComparison* comparison, bool requireAnd)
  // "true"  removes the object if they match
  // "false"  keeps  the object if they match  

  // RECO LEPTONS MATCHED TO GEN LEPTONS
  handler->addProduct(          "goodElectronsUnmatched",  "goodElectrons");
  handler->addProductComparison("goodElectronsUnmatched",  "MCELECTRONSFROMBOSON",     deltaR0p3 );
  handler->addProduct(          "goodElectronsMatched",    "goodElectrons");
  handler->addProductComparison("goodElectronsMatched",    "goodElectronsUnmatched",   deltaR0p01);
  handler->addProduct(          "goodMuonsUnmatched",      "goodMuons");
  handler->addProductComparison("goodMuonsUnmatched",      "MCMUONSFROMBOSON",         deltaR0p3 );
  handler->addProduct(          "goodMuonsMatched",        "goodMuons"); 
  handler->addProductComparison("goodMuonsMatched",        "goodMuonsUnmatched",       deltaR0p01);
  handler->addProduct(          "goodTausUnmatched",       "goodTaus");
  handler->addProductComparison("goodTausUnmatched",       "MCTAUSFROMBOSON",          deltaR0p3 );
  handler->addProduct(          "goodTausMatched",         "goodTaus");
  handler->addProductComparison("goodTausMatched",         "goodTausUnmatched",        deltaR0p01);
  handler->addProduct(          "goodElectronsNotFromTau", "goodElectrons");//---------------------- "Not From Tau" stuff
  handler->addProductComparison("goodElectronsNotFromTau", "MCELECTRONSFROMTAU",       deltaR0p3 );
  handler->addProduct(          "goodElectronsFromTau",    "goodElectrons");
  handler->addProductComparison("goodElectronsFromTau",    "goodElectronsNotFromTau",  deltaR0p01);
  handler->addProduct(          "goodMuonsNotFromTau",     "goodMuons");
  handler->addProductComparison("goodMuonsNotFromTau",     "MCMUONSFROMTAU",           deltaR0p3 );  
  handler->addProduct(          "goodMuonsFromTau",        "goodMuons"); 
  handler->addProductComparison("goodMuonsFromTau",        "goodMuonsNotFromTau",      deltaR0p01);  

  // GEN LEPTON MATCHED TO RECO LEPTONS
  //EventVariableReversed* offZ = new EventVariableReversed("ONZ", "OFFZ");
  handler->addProduct(          "MCELECTRONSFROMBOSONUNMATCHED",    "MCELECTRONSFROMBOSON");
  handler->addProductComparison("MCELECTRONSFROMBOSONUNMATCHED",    "goodElectrons",                  deltaR0p3 );
  handler->addProduct(          "MCELECTRONSFROMBOSONMATCHED",      "MCELECTRONSFROMBOSON");
  handler->addProductComparison("MCELECTRONSFROMBOSONMATCHED",      "MCELECTRONSFROMBOSONUNMATCHED",  deltaR0p01);
  handler->addProduct(          "MCMUONSFROMBOSONUNMATCHED",        "MCMUONSFROMBOSON");
  handler->addProductComparison("MCMUONSFROMBOSONUNMATCHED",        "goodMuons",                      deltaR0p3 );
  handler->addProduct(          "MCMUONSFROMBOSONMATCHED",          "MCMUONSFROMBOSON");
  handler->addProductComparison("MCMUONSFROMBOSONMATCHED",          "MCMUONSFROMBOSONUNMATCHED",      deltaR0p01);
  handler->addProduct(          "MCTAUSFROMBOSONUNMATCHED",         "MCTAUSFROMBOSON");
  handler->addProductComparison("MCTAUSFROMBOSONUNMATCHED",         "goodTaus",                       deltaR0p3 );
  handler->addProduct(          "MCTAUSFROMBOSONMATCHED",           "MCTAUSFROMBOSON");
  handler->addProductComparison("MCTAUSFROMBOSONMATCHED",           "MCTAUSFROMBOSONUNMATCHED",       deltaR0p01);
  handler->addProduct(          "MCHADRONICTAUSFROMBOSONUNMATCHED", "MCTAUSFROMBOSON");
  handler->addProductComparison("MCHADRONICTAUSFROMBOSONUNMATCHED", "goodTaus",                       deltaR0p3 );
  handler->addProduct(          "MCHADRONICTAUSFROMBOSONMATCHED",   "MCTAUSFROMBOSON");
  handler->addProductComparison("MCHADRONICTAUSFROMBOSONMATCHED",   "goodTaus",                       deltaR0p01);

  handler->addProduct(   "MCMUONSFROMZPOS","MCMUONSFROMZ");
  handler->addProductCut("MCMUONSFROMZPOS","POSITIVE");
  handler->addProduct(   "MCMUONSFROMZNEG","MCMUONSFROMZ");
  handler->addProductCut("MCMUONSFROMZNEG","NEGATIVE");
  
  handler->addProduct(   "MCELECTRONSFROMZPOS","MCELECTRONSFROMZ");
  handler->addProductCut("MCELECTRONSFROMZPOS","POSITIVE");
  handler->addProduct(   "MCELECTRONSFROMZNEG","MCELECTRONSFROMZ");
  handler->addProductCut("MCELECTRONSFROMZNEG","NEGATIVE");
  
  handler->addEventVariable("NMCMUONSFROMZ",     new EventVariableN("NMCMUONSFROMZ",    "MCMUONSFROMZ"));
  handler->addEventVariable("NMCELECTRONSFROMZ", new EventVariableN("NMCELECTRONSFROMZ","MCELECTRONSFROMZ"));
  
  handler->addEventVariable("NMCELECTRONSFROMBOSON",          new EventVariableN("NMCELECTRONSFROMBOSON",          "MCELECTRONSFROMBOSON"));
  handler->addEventVariable("QMCELECTRONSFROMBOSON",          new EventVariableObjectVariableVector<int>("CHARGE", "MCELECTRONSFROMBOSON"));
  handler->addEventVariable("PTMCELECTRONSFROMBOSON",         new EventVariableObjectVariableVector<double>("PT",  "MCELECTRONSFROMBOSON"));
  handler->addEventVariable("ETAMCELECTRONSFROMBOSON",        new EventVariableObjectVariableVector<double>("ETA", "MCELECTRONSFROMBOSON"));
  handler->addEventVariable("PHIMCELECTRONSFROMBOSON",        new EventVariableObjectVariableVector<double>("PHI", "MCELECTRONSFROMBOSON"));
  handler->addEventVariable("NMCELECTRONSFROMBOSONMATCHED",   new EventVariableN("NMCELECTRONSFROMBOSONMATCHED",   "MCELECTRONSFROMBOSONMATCHED"));
  handler->addEventVariable("QMCELECTRONSFROMBOSONMATCHED",   new EventVariableObjectVariableVector<int>("CHARGE", "MCELECTRONSFROMBOSONMATCHED"));
  handler->addEventVariable("PTMCELECTRONSFROMBOSONMATCHED",  new EventVariableObjectVariableVector<double>("PT",  "MCELECTRONSFROMBOSONMATCHED"));  
  handler->addEventVariable("ETAMCELECTRONSFROMBOSONMATCHED", new EventVariableObjectVariableVector<double>("ETA", "MCELECTRONSFROMBOSONMATCHED"));
  handler->addEventVariable("PHIMCELECTRONSFROMBOSONMATCHED", new EventVariableObjectVariableVector<double>("PHI", "MCELECTRONSFROMBOSONMATCHED"));
  handler->addEventVariable("NGOODELECTRONSMATCHED",          new EventVariableN("NGOODELECTRONSMATCHED",          "goodElectronsMatched"));
  handler->addEventVariable("QGOODELECTRONSMATCHED",          new EventVariableObjectVariableVector<int>("CHARGE", "goodElectronsMatched"));
  handler->addEventVariable("PTGOODELECTRONSMATCHED",         new EventVariableObjectVariableVector<double>("PT",  "goodElectronsMatched"));
  handler->addEventVariable("ETAGOODELECTRONSMATCHED",        new EventVariableObjectVariableVector<double>("ETA", "goodElectronsMatched"));
  handler->addEventVariable("PHIGOODELECTRONSMATCHED",        new EventVariableObjectVariableVector<double>("PHI", "goodElectronsMatched"));
  //
  handler->addEventVariable("NMCMUONSFROMBOSON",          new EventVariableN("NMCMUONSFROMBOSON",              "MCMUONSFROMBOSON"));
  handler->addEventVariable("QMCMUONSFROMBOSON",          new EventVariableObjectVariableVector<int>("CHARGE", "MCMUONSFROMBOSON"));
  handler->addEventVariable("PTMCMUONSFROMBOSON",         new EventVariableObjectVariableVector<double>("PT",  "MCMUONSFROMBOSON"));
  handler->addEventVariable("ETAMCMUONSFROMBOSON",        new EventVariableObjectVariableVector<double>("ETA", "MCMUONSFROMBOSON"));
  handler->addEventVariable("PHIMCMUONSFROMBOSON",        new EventVariableObjectVariableVector<double>("PHI", "MCMUONSFROMBOSON"));
  handler->addEventVariable("NMCMUONSFROMBOSONMATCHED",   new EventVariableN("NMCMUONSFROMBOSONMATCHED",       "MCMUONSFROMBOSONMATCHED"));
  handler->addEventVariable("QMCMUONSFROMBOSONMATCHED",   new EventVariableObjectVariableVector<int>("CHARGE", "MCMUONSFROMBOSONMATCHED"));
  handler->addEventVariable("PTMCMUONSFROMBOSONMATCHED",  new EventVariableObjectVariableVector<double>("PT",  "MCMUONSFROMBOSONMATCHED"));
  handler->addEventVariable("ETAMCMUONSFROMBOSONMATCHED", new EventVariableObjectVariableVector<double>("ETA", "MCMUONSFROMBOSONMATCHED"));
  handler->addEventVariable("PHIMCMUONSFROMBOSONMATCHED", new EventVariableObjectVariableVector<double>("PHI", "MCMUONSFROMBOSONMATCHED"));
  handler->addEventVariable("NGOODMUONSMATCHED",          new EventVariableN("NGOODMUONSMATCHED",              "goodMuonsMatched"));
  handler->addEventVariable("QGOODMUONSMATCHED",          new EventVariableObjectVariableVector<int>("CHARGE", "goodMuonsMatched"));
  handler->addEventVariable("PTGOODMUONSMATCHED",         new EventVariableObjectVariableVector<double>("PT",  "goodMuonsMatched"));
  handler->addEventVariable("ETAGOODMUONSMATCHED",        new EventVariableObjectVariableVector<double>("ETA", "goodMuonsMatched"));
  handler->addEventVariable("PHIGOODMUONSMATCHED",        new EventVariableObjectVariableVector<double>("PHI", "goodMuonsMatched"));
  //
  handler->addEventVariable("NMCTAUSFROMBOSON",           new EventVariableN("NMCTAUSFROMBOSON",               "MCTAUSFROMBOSON"));
  handler->addEventVariable("QMCTAUSFROMBOSON",           new EventVariableObjectVariableVector<int>("CHARGE", "MCTAUSFROMBOSON"));
  handler->addEventVariable("PTMCTAUSFROMBOSON",          new EventVariableObjectVariableVector<double>("PT",  "MCTAUSFROMBOSON"));
  handler->addEventVariable("ETAMCTAUSFROMBOSON",         new EventVariableObjectVariableVector<double>("ETA", "MCTAUSFROMBOSON"));
  handler->addEventVariable("PHIMCTAUSFROMBOSON",         new EventVariableObjectVariableVector<double>("PHI", "MCTAUSFROMBOSON"));
  handler->addEventVariable("NMCHADRONICTAUSFROMBOSON",   new EventVariableN("NMCHADRONICTAUSFROMBOSON",       "MCHADRONICTAUSFROMBOSON"));
  handler->addEventVariable("QMCHADRONICTAUSFROMBOSON",   new EventVariableObjectVariableVector<int>("CHARGE", "MCHADRONICTAUSFROMBOSON"));
  handler->addEventVariable("PTMCHADRONICTAUSFROMBOSON",  new EventVariableObjectVariableVector<double>("PT",  "MCHADRONICTAUSFROMBOSON"));
  handler->addEventVariable("ETAMCHADRONICTAUSFROMBOSON", new EventVariableObjectVariableVector<double>("ETA", "MCHADRONICTAUSFROMBOSON"));
  handler->addEventVariable("PHIMCHADRONICTAUSFROMBOSON", new EventVariableObjectVariableVector<double>("PHI", "MCHADRONICTAUSFROMBOSON"));
  handler->addEventVariable("NMCLEPTONICTAUSFROMBOSON",   new EventVariableN("NMCLEPTONICTAUSFROMBOSON",       "MCLEPTONICTAUSFROMBOSON"));
  handler->addEventVariable("QMCLEPTONICTAUSFROMBOSON",   new EventVariableObjectVariableVector<int>("CHARGE", "MCLEPTONICTAUSFROMBOSON"));
  handler->addEventVariable("PTMCLEPTONICTAUSFROMBOSON",  new EventVariableObjectVariableVector<double>("PT",  "MCLEPTONICTAUSFROMBOSON"));
  handler->addEventVariable("ETAMCLEPTONICTAUSFROMBOSON", new EventVariableObjectVariableVector<double>("ETA", "MCLEPTONICTAUSFROMBOSON"));
  handler->addEventVariable("PHIMCLEPTONICTAUSFROMBOSON", new EventVariableObjectVariableVector<double>("PHI", "MCLEPTONICTAUSFROMBOSON"));
  handler->addEventVariable("NMCHADRONICTAUSFROMBOSONMATCHED",  new EventVariableN("NMCHADRONICTAUSFROMBOSONMATCHED", "MCHADRONICTAUSFROMBOSONMATCHED"));
  handler->addEventVariable("QMCHADRONICTAUSFROMBOSONMATCHED",  new EventVariableObjectVariableVector<int>("CHARGE",  "MCHADRONICTAUSFROMBOSONMATCHED"));
  handler->addEventVariable("PTMCHADRONICTAUSFROMBOSONMATCHED", new EventVariableObjectVariableVector<double>("PT",   "MCHADRONICTAUSFROMBOSONMATCHED"));
  handler->addEventVariable("ETAMCHADRONICTAUSFROMBOSONMATCHED",new EventVariableObjectVariableVector<double>("ETA",  "MCHADRONICTAUSFROMBOSONMATCHED"));
  handler->addEventVariable("PHIMCHADRONICTAUSFROMBOSONMATCHED",new EventVariableObjectVariableVector<double>("PHI",  "MCHADRONICTAUSFROMBOSONMATCHED"));
  handler->addEventVariable("NGOODTAUSMATCHED",           new EventVariableN("NGOODTAUSMATCHED",               "goodTausMatched"));
  handler->addEventVariable("QGOODTAUSMATCHED",           new EventVariableObjectVariableVector<int>("CHARGE", "goodTausMatched"));
  handler->addEventVariable("PTGOODTAUSMATCHED",          new EventVariableObjectVariableVector<double>("PT",  "goodTausMatched"));
  handler->addEventVariable("ETAGOODTAUSMATCHED",         new EventVariableObjectVariableVector<double>("ETA", "goodTausMatched"));
  handler->addEventVariable("PHIGOODTAUSMATCHED",         new EventVariableObjectVariableVector<double>("PHI", "goodTausMatched"));
  
  handler->addEventVariable("HASTWOMCMUONSFROMZ",     new EventVariableValue<int>("NMCMUONSFROMZ",    2));
  handler->addEventVariable("HASTWOMCELECTRONSFROMZ", new EventVariableValue<int>("NMCELECTRONSFROMZ",2));
  
  handler->addEventVariable("NBOSONS",     new EventVariableN("NBOSONS",                        "BOSONS"));
  handler->addEventVariable("PTBOSONS",    new EventVariableObjectVariableVector<double>("PT",  "BOSONS")); 
  handler->addEventVariable("ETABOSONS",   new EventVariableObjectVariableVector<double>("ETA", "BOSONS")); 
  handler->addEventVariable("PHIBOSONS",   new EventVariableObjectVariableVector<double>("PHI", "BOSONS")); 
  handler->addEventVariable("PDGIDBOSONS", new EventVariableObjectVariableVector<int>( "pdgId", "BOSONS")); 
  
  EventVariablePairMass* mumcmass = new EventVariablePairMass("MUMCMASS","MCMUONSFROMZ","MUMC_",91,15);
  handler->addEventVariable("MUMCMASS",mumcmass);
  EventVariablePairMass* elmcmass = new EventVariablePairMass("ELMCMASS","MCELECTRONSFROMZ","ELMC_",91,15);
  handler->addEventVariable("ELMCMASS",elmcmass);
  
  handler->addEventVariable("MAXGENDXY",new EventVariableObjectVariableExtreme<double>("genDxy","ALLMC"));
  
  handler->addEventVariable("MCMUPLUSPT",  new EventVariableObjectVariableExtreme<double>("PT","MCMUONSFROMZPOS"));
  handler->addEventVariable("MCMUMINUSPT", new EventVariableObjectVariableExtreme<double>("PT","MCMUONSFROMZNEG"));
  handler->addEventVariable("MCELPLUSPT",  new EventVariableObjectVariableExtreme<double>("PT","MCELECTRONSFROMZPOS"));
  handler->addEventVariable("MCELMINUSPT", new EventVariableObjectVariableExtreme<double>("PT","MCELECTRONSFROMZNEG"));
  
  TF1* flatWeight = new TF1("flat","1",0,10000000);
  handler->addEventVariable("FLATWEIGHT",new EventVariableTF1<int>("FLATWEIGHT","RUN",flatWeight));
  handler->addWeightVariable("FLATWEIGHT");
  
  handler->addHistogram(new SignatureTH1F_EventVariable<double>("TrueNumInteractions","TrueNumInteractions","",50,0,50));
  //handler->addHistogram(new SignatureTH1F_EventVariable<double>("TrueNumInteractionsNEG","TrueNumInteractions","",50,0,50,"genEventInfo_weight"));
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void addHistograms(BaseHandler* handler)
{
  handler->addHistogram(new SignatureTH1F_TriggerName("TriggerNames","TRIGGERS"));
  //
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("GOODMU_MPAIR","GOODMUPLUSPT","GOODMUPLUS_PTvsM","",120,0,120,100,0,100),"Mu");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("GOODMU_MPAIR","GOODMUMINUSPT","GOODMUMINUS_PTvsM","",120,0,120,100,0,100),"Mu");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("MUMC_MPAIR","MCMUPLUSPT","MCMUPLUS_PTvsM","",120,0,120,100,0,100),"Mu");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("MUMC_MPAIR","MCMUMINUSPT","MCMUMINUS_PTvsM","",120,0,120,100,0,100),"Mu");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("MUPLUS_MPAIR","PROBEMUPLUSPT","PROBEMUPLUS_PTvsM","",120,0,120,100,0,100),"Mu");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("MUMINUS_MPAIR","PROBEMUMINUSPT","PROBEMUMINUS_PTvsM","",120,0,120,100,0,100),"Mu");

  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("GOODEL_MPAIR","GOODELPLUSPT","GOODELPLUS_PTvsM","",120,0,120,100,0,100),"El");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("GOODEL_MPAIR","GOODELMINUSPT","GOODELMINUS_PTvsM","",120,0,120,100,0,100),"El");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("ELMC_MPAIR","MCELPLUSPT","MCELPLUS_PTvsM","",120,0,120,100,0,100),"El");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("ELMC_MPAIR","MCELMINUSPT","MCELMINUS_PTvsM","",120,0,120,100,0,100),"El");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("ELPLUS_MPAIR","PROBEELPLUSPT","PROBEELPLUS_PTvsM","",120,0,120,100,0,100),"El");
  handler->addHistogram(new SignatureTH2F_EventVariableVsEventVariable<double,double>("ELMINUS_MPAIR","PROBEELMINUSPT","PROBEELMINUS_PTvsM","",120,0,120,100,0,100),"El");

  //handler->addHistogram(new SignatureTH1F_N("N_PROBEMUONS","probeMuons"));
  handler->addHistogram(new SignatureTH1F_N("N_GOODMUONS","goodMuons"));
  handler->addHistogram(new SignatureTH1F_N("N_ALLMUONS","ALLMUONS"));
  //handler->addHistogram(new SignatureTH1F_N("N_PROBEELECTRONS","probeElectrons"));
  handler->addHistogram(new SignatureTH1F_N("N_GOODELECTRONS","goodElectrons"));
  handler->addHistogram(new SignatureTH1F_N("N_ALLELECTRONS","ALLELECTRONS"));
  handler->addHistogram(new SignatureTH1F_N("N_PROMPTTRACKS","promptTracks"));
  handler->addHistogram(new SignatureTH1F_N("N_GOODTRACKS","goodTracks"));

  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_GOODMUONS","PT","goodMuons", "PT", 100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_GOODMUONSMATCHED","PT","goodMuonsMatched", "PT", 100,0,200));
  handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("PTGEN_GOODMUONSMATCHED","PT","goodMuonsMatched","genParticle","",100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PTGEN_MCMUONSFROMBOSON","PT","MCMUONSFROMBOSON", "PT", 100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_GOODELECTRONS","PT","goodElectrons", "PT", 100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_GOODELECTRONSMATCHED","PT","goodElectronsMatched", "PT", 100,0,200));
  handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("PTGEN_GOODELECTRONSMATCHED","PT","goodElectronsMatched","genParticle","",100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PTGEN_MCELECTRONSFROMBOSON","PT","MCELECTRONSFROMBOSON", "PT", 100,0,200));

  handler->addHistogram(new SignatureTH1F_NearestVertexRank("nearestVertexRank","BOSONS"));

  handler->addHistogram(new SignatureTH1F_EventVariable<double>("MAXGENDXY","MAXGENDXY","",1000,0,10));
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupPrintElectrons(BaseHandler* handler)
{
  PrintModuleProduct* printElectrons = new PrintModuleProduct("ALLELECTRONS","printElectrons");

  //int iii = 0;
  double ddd = 0;
  //TString ttt = "";
  bool bbb = false;

  printElectrons->addVariable("passConversionVeto",bbb);
  printElectrons->addVariable("deltaEtaSuperClusterTrackAtVtx",ddd);
  printElectrons->addVariable("deltaPhiSuperClusterTrackAtVtx",ddd);
  printElectrons->addVariable("hadronicOverEm",ddd);
  printElectrons->addVariable("full5x5_sigmaIetaIeta",ddd);
  printElectrons->addVariable("1oEm1oP",ddd);
  printElectrons->addVariable("dz",ddd);
  printElectrons->addVariable("dxy",ddd);
  printElectrons->addVariable("superClustereta",ddd);
  printElectrons->addVariable("sumChargedHadronPt",ddd);
  printElectrons->addVariable("sumNeutralHadronEt",ddd);
  printElectrons->addVariable("sumPhotonEt",ddd);
  printElectrons->addVariable("sumPUPt",ddd);
  printElectrons->addVariable("RELISO",ddd);
  printElectrons->addVariable("hasAssociate_genParticle",bbb);
  printElectrons->addVariable("ELECTRON_GOOD",bbb);
  handler->addPrintModule(printElectrons);
}

// ------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

void setupPrintRA7Sync(BaseHandler* handler)
{
  PrintModuleEventVariables* printLines = new PrintModuleEventVariables("print");
  double ddd = 0;
  int iii = 0;
  bool bbb = true;
  printLines->addVariable("NGOODELECTRONS",iii);
  printLines->addVariable("NGOODMUONS",iii);
  printLines->addVariable("NGOODTAUS",iii);
  printLines->addVariable("NGOODRA7JETS",iii);
  printLines->addVariable("NRA7BJETSCSVM",iii);
  printLines->addVariable("NRA7BJETSCSVL",iii);
  printLines->addVariable("MET",ddd);
  printLines->addVariable("MLL",ddd);
  printLines->addVariable("MT",ddd);
  printLines->addVariable("RA7ONZ",bbb);
  printLines->addVariable("NGOODRECOVERTICES",iii);
  printLines->addVariable("OSSFMAXMLL",ddd);
  printLines->addVariable("OSSFMINMLL",ddd);
  printLines->addVariable("RA7MOSSF",ddd);
  printLines->addVariable("PT201510",bbb);
  printLines->addVariable("RA7TRIGGERACCEPT",bbb);
  handler->addPrintModule(printLines);
}
