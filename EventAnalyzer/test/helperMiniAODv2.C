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
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableChangeType.h"
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
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableConeCorrectedPt.h"
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

  EventVariableThreshold* pt25first = new EventVariableThreshold("PT25first","goodElectrons");
  pt25first->addProduct("goodMuons");
  pt25first->addThreshold(25);
  handler->addEventVariable("PT25first",pt25first);
  
  EventVariableThreshold* pt251510 = new EventVariableThreshold("PT251510","goodElectrons");
  pt251510->addProduct("goodMuons");
  pt251510->addThreshold(25);
  pt251510->addThreshold(15);
  pt251510->addThreshold(10);
  handler->addEventVariable("PT251510",pt251510);

  EventVariableThreshold* pt252515 = new EventVariableThreshold("PT252515","goodElectrons");
  pt252515->addProduct("goodMuons");
  pt252515->addThreshold(25);
  pt252515->addThreshold(15);
  pt252515->addThreshold(10);
  handler->addEventVariable("PT252515",pt252515);

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
  handler->addEventVariable("NGOODMUONS",              new EventVariableN("NGOODMUONS",                                "goodMuons"));
  handler->addEventVariable("QGOODMUONS",              new EventVariableObjectVariableVector<int>("CHARGE",            "goodMuons"));
  handler->addEventVariable("PTGOODMUONS",             new EventVariableObjectVariableVector<double>("PT",             "goodMuons"));
  handler->addEventVariable("ETAGOODMUONS",            new EventVariableObjectVariableVector<double>("ETA",            "goodMuons"));
  handler->addEventVariable("PHIGOODMUONS",            new EventVariableObjectVariableVector<double>("PHI",            "goodMuons"));
  handler->addEventVariable("RELISODBDR0p4GOODMUONS",  new EventVariableObjectVariableVector<double>("MUON_RELISO",    "goodMuons"));
  handler->addEventVariable("RELTRKISOGOODMUONS",      new EventVariableObjectVariableVector<double>("MUON_RELTRKISO", "goodMuons"));
  handler->addEventVariable("ISTIGHTIDGOODMUONS",      new EventVariableObjectVariableVector<int>("isTightMuon",       "goodMuons"));
  handler->addEventVariable("ISHIGHPTIDGOODMUONS",     new EventVariableObjectVariableVector<int>("isHighPtMuon",      "goodMuons"));
  handler->addEventVariable("MINIISOGOODMUONS",        new EventVariableObjectVariableVector<double>("MINIISO",        "goodMuons"));
  handler->addEventVariable("PTRATIOGOODMUONS",        new EventVariableObjectVariableVector<double>("ptRatio",        "goodMuons"));
  handler->addEventVariable("PTRELGOODMUONS",          new EventVariableObjectVariableVector<double>("ptRel",          "goodMuons"));
  handler->addEventVariable("RELISOGOODMUONS",         new EventVariableObjectVariableVector<double>("RELISO",         "goodMuons"));
  handler->addEventVariable("CONECORRECTEDPTGOODMUONS",new EventVariableObjectVariableVector<double>("conecorrectedPt","goodMuons"));
  handler->addEventVariable("fakeRoleGOODMUONS",       new EventVariableObjectVariableVector<int>("fakeRole",          "goodMuons"));//is Fake role (track proxy)
  //
  handler->addEventVariable("goodMuonsDgoodPhotons",   new EventVariableDvector("goodMuons", "goodPhotons"));
  handler->addEventVariable("goodMuonsDgoodJets",      new EventVariableDvector("goodMuons", "goodJets"));
  handler->addEventVariable("goodMuonsDgoodLeptons",   new EventVariableDvector("goodMuons", {"goodElectrons", "goodMuons"}, "goodLeptons"));
  //
  // ConeConstituents for muons:
  handler->addEventVariable("JETCORRJETPTGOODMUONS",        new EventVariableObjectVariableVector<double>("JETCORRJETPT",         "goodMuons"));
  handler->addEventVariable("JETLRMGOODMUONS",              new EventVariableObjectVariableVector<double>("JETLRM",               "goodMuons"));
  handler->addEventVariable("JETNOOFCONSTGOODMUONS",        new EventVariableObjectVariableVector<int>(   "JETNOOFCONST",         "goodMuons"));
  handler->addEventVariable("JETCHMULTGOODMUONS",           new EventVariableObjectVariableVector<int>(   "JETCHMULT",            "goodMuons"));
  handler->addEventVariable("JETCHHADMULTGOODMUONS",        new EventVariableObjectVariableVector<int>(   "JETCHHADMULT",         "goodMuons"));
  handler->addEventVariable("JETCSVRAWGOODMUONS",           new EventVariableObjectVariableVector<double>("JETCSVBTAG",           "goodMuons"));
  handler->addEventVariable("JETJPRAWGOODMUONS",            new EventVariableObjectVariableVector<double>("JETJPBTAG",            "goodMuons"));
  handler->addEventVariable("JETMVARAWGOODMUONS",           new EventVariableObjectVariableVector<double>("JETMVABTAG",           "goodMuons"));
  //
  handler->addEventVariable("CONESUMETDR03GOODMUONS",       new EventVariableObjectVariableVector<double>("CONESUMETDR03",        "goodMuons"));
  handler->addEventVariable("CONENDR03GOODMUONS",           new EventVariableObjectVariableVector<int>(   "CONENDR03",            "goodMuons"));
  handler->addEventVariable("CONESUMETDR04GOODMUONS",       new EventVariableObjectVariableVector<double>("CONESUMETDR04",        "goodMuons"));
  handler->addEventVariable("CONENDR04GOODMUONS",           new EventVariableObjectVariableVector<int>(   "CONENDR04",            "goodMuons"));
  handler->addEventVariable("CONESUMETDR03TO07GOODMUONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR03to07",    "goodMuons"));
  handler->addEventVariable("CONENDR03TO07GOODMUONS",       new EventVariableObjectVariableVector<int>(   "CONENDR03to07",        "goodMuons"));
  handler->addEventVariable("CONESUMETDR04TO08GOODMUONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR04to08",    "goodMuons"));
  handler->addEventVariable("CONENDR04TO08GOODMUONS",       new EventVariableObjectVariableVector<int>(   "CONENDR04to08",        "goodMuons"));
  handler->addEventVariable("CONESUMETDR01TO08GOODMUONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR01to08",    "goodMuons"));
  handler->addEventVariable("CONENDR01TO08GOODMUONS",       new EventVariableObjectVariableVector<int>(   "CONENDR01to08",        "goodMuons"));
  handler->addEventVariable("CONESUMETDR02TO08GOODMUONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR02to08",    "goodMuons"));
  handler->addEventVariable("CONENDR02TO08GOODMUONS",       new EventVariableObjectVariableVector<int>(   "CONENDR02to08",        "goodMuons"));
  handler->addEventVariable("CONEPTDR03GOODMUONS",          new EventVariableObjectVariableVector<double>("CONEPTDR03",           "goodMuons"));
  handler->addEventVariable("CONEMASSDR03GOODMUONS",        new EventVariableObjectVariableVector<double>("CONEMASSDR03",         "goodMuons"));
  handler->addEventVariable("CONEPTDR04GOODMUONS",          new EventVariableObjectVariableVector<double>("CONEPTDR04",           "goodMuons"));
  handler->addEventVariable("CONEMASSDR04GOODMUONS",        new EventVariableObjectVariableVector<double>("CONEMASSDR04",         "goodMuons"));
  handler->addEventVariable("CONEPTDR03TO07GOODMUONS",      new EventVariableObjectVariableVector<double>("CONEPTDR03to07",       "goodMuons"));
  handler->addEventVariable("CONEMASSDR03TO07GOODMUONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR03to07",     "goodMuons"));
  handler->addEventVariable("CONEPTDR04TO08GOODMUONS",      new EventVariableObjectVariableVector<double>("CONEPTDR04to08",       "goodMuons"));
  handler->addEventVariable("CONEMASSDR04TO08GOODMUONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR04to08",     "goodMuons"));
  handler->addEventVariable("CONEPTDR01TO08GOODMUONS",      new EventVariableObjectVariableVector<double>("CONEPTDR01to08",       "goodMuons"));
  handler->addEventVariable("CONEMASSDR01TO08GOODMUONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR01to08",     "goodMuons"));
  handler->addEventVariable("CONEPTDR02TO08GOODMUONS",      new EventVariableObjectVariableVector<double>("CONEPTDR02to08",       "goodMuons"));
  handler->addEventVariable("CONEMASSDR02TO08GOODMUONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR02to08",     "goodMuons"));
  handler->addEventVariable("CONECHSUMETDR03GOODMUONS",     new EventVariableObjectVariableVector<double>("CONECHSUMETDR03",      "goodMuons"));
  handler->addEventVariable("CONECHNDR03GOODMUONS",         new EventVariableObjectVariableVector<int>(   "CONECHNDR03",          "goodMuons"));
  handler->addEventVariable("CONECHSUMETDR04GOODMUONS",     new EventVariableObjectVariableVector<double>("CONECHSUMETDR04",      "goodMuons"));
  handler->addEventVariable("CONECHNDR04GOODMUONS",         new EventVariableObjectVariableVector<int>(   "CONECHNDR04",          "goodMuons"));
  handler->addEventVariable("CONECHSUMETDR03TO07GOODMUONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR03to07",  "goodMuons"));
  handler->addEventVariable("CONECHNDR03TO07GOODMUONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR03to07",      "goodMuons"));
  handler->addEventVariable("CONECHSUMETDR04TO08GOODMUONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR04to08",  "goodMuons"));
  handler->addEventVariable("CONECHNDR04TO08GOODMUONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR04to08",      "goodMuons"));
  handler->addEventVariable("CONECHSUMETDR01TO08GOODMUONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR01to08",  "goodMuons"));
  handler->addEventVariable("CONECHNDR01TO08GOODMUONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR01to08",      "goodMuons"));
  handler->addEventVariable("CONECHSUMETDR02TO08GOODMUONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR02to08",  "goodMuons"));
  handler->addEventVariable("CONECHNDR02TO08GOODMUONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR02to08",      "goodMuons"));
  handler->addEventVariable("CONECHPTDR03GOODMUONS",        new EventVariableObjectVariableVector<double>("CONECHPTDR03",         "goodMuons"));
  handler->addEventVariable("CONECHMASSDR03GOODMUONS",      new EventVariableObjectVariableVector<double>("CONECHMASSDR03",       "goodMuons"));
  handler->addEventVariable("CONECHPTDR04GOODMUONS",        new EventVariableObjectVariableVector<double>("CONECHPTDR04",         "goodMuons"));
  handler->addEventVariable("CONECHMASSDR04GOODMUONS",      new EventVariableObjectVariableVector<double>("CONECHMASSDR04",       "goodMuons"));
  handler->addEventVariable("CONECHPTDR03TO07GOODMUONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR03to07",     "goodMuons"));
  handler->addEventVariable("CONECHMASSDR03TO07GOODMUONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR03to07",   "goodMuons"));
  handler->addEventVariable("CONECHPTDR04TO08GOODMUONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR04to08",     "goodMuons"));
  handler->addEventVariable("CONECHMASSDR04TO08GOODMUONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR04to08",   "goodMuons"));
  handler->addEventVariable("CONECHPTDR01TO08GOODMUONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR01to08",     "goodMuons"));
  handler->addEventVariable("CONECHMASSDR01TO08GOODMUONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR01to08",   "goodMuons"));
  handler->addEventVariable("CONECHPTDR02TO08GOODMUONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR02to08",     "goodMuons"));
  handler->addEventVariable("CONECHMASSDR02TO08GOODMUONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR02to08",   "goodMuons"));
  //
  handler->addEventVariable("NBASICMUONS",             new EventVariableN("NBASICMUONS",                               "basicMuons"));
  handler->addEventVariable("QBASICMUONS",             new EventVariableObjectVariableVector<int>("CHARGE",            "basicMuons"));
  handler->addEventVariable("PTBASICMUONS",            new EventVariableObjectVariableVector<double>("PT",             "basicMuons"));
  handler->addEventVariable("ETABASICMUONS",           new EventVariableObjectVariableVector<double>("ETA",            "basicMuons"));
  handler->addEventVariable("PHIBASICMUONS",           new EventVariableObjectVariableVector<double>("PHI",            "basicMuons"));
  handler->addEventVariable("DXYBASICMUONS",           new EventVariableObjectVariableVector<double>("dxy",            "basicMuons"));
  handler->addEventVariable("ISLOOSEIDBASICMUONS",     new EventVariableObjectVariableVector<int>("isLooseMuon",       "basicMuons"));
  handler->addEventVariable("ISMEDIUMIDBASICMUONS",    new EventVariableObjectVariableVector<int>("isMediumMuon",      "basicMuons"));
  handler->addEventVariable("ISTIGHTIDBASICMUONS",     new EventVariableObjectVariableVector<int>("isTightMuon",       "basicMuons"));
  handler->addEventVariable("ISSOFTIDBASICMUONS",      new EventVariableObjectVariableVector<int>("isSoftMuon",        "basicMuons"));
  handler->addEventVariable("ISHIGHPTIDBASICMUONS",    new EventVariableObjectVariableVector<int>("isHighPtMuon",      "basicMuons"));
  handler->addEventVariable("RELISODBDR0p4BASICMUONS", new EventVariableObjectVariableVector<double>("MUON_RELISO",    "basicMuons"));
  handler->addEventVariable("RELTRKISOBASICMUONS",     new EventVariableObjectVariableVector<double>("MUON_RELTRKISO", "basicMuons"));
  handler->addEventVariable("RELISOBASICMUONS",        new EventVariableObjectVariableVector<double>("RELISO",         "basicMuons"));
  handler->addEventVariable("MINIISOBASICMUONS",       new EventVariableObjectVariableVector<double>("MINIISO",        "basicMuons"));
  handler->addEventVariable("PTRATIOBASICMUONS",       new EventVariableObjectVariableVector<double>("ptRatio",        "basicMuons"));
  handler->addEventVariable("PTRELBASICMUONS",         new EventVariableObjectVariableVector<double>("ptRel",          "basicMuons"));
  //
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
  handler->addEventVariable("NGOODELECTRONS",                    new EventVariableN("NGOODELECTRONS",                                              "goodElectrons"));
  handler->addEventVariable("QGOODELECTRONS",                    new EventVariableObjectVariableVector<int>("CHARGE",                              "goodElectrons"));
  handler->addEventVariable("PTGOODELECTRONS",                   new EventVariableObjectVariableVector<double>("PT",                               "goodElectrons"));
  handler->addEventVariable("ETAGOODELECTRONS",                  new EventVariableObjectVariableVector<double>("ETA",                              "goodElectrons"));
  handler->addEventVariable("PHIGOODELECTRONS",                  new EventVariableObjectVariableVector<double>("PHI",                              "goodElectrons"));
  handler->addEventVariable("ISCUTVETOIDGOODELECTRONS",          new EventVariableObjectVariableVector<int>("passCutBasedVetoId",                  "goodElectrons"));
  handler->addEventVariable("ISCUTLOOSEIDGOODELECTRONS",         new EventVariableObjectVariableVector<int>("passCutBasedLooseId",                 "goodElectrons"));
  handler->addEventVariable("ISCUTMEDIUMIDGOODELECTRONS",        new EventVariableObjectVariableVector<int>("passCutBasedMediumId",                "goodElectrons"));
  handler->addEventVariable("ISCUTTIGHTIDGOODELECTRONS",         new EventVariableObjectVariableVector<int>("passCutBasedTightId",                 "goodElectrons"));
  handler->addEventVariable("ISHEEPIDGOODELECTRONS",             new EventVariableObjectVariableVector<int>("passHEEP",                            "goodElectrons"));
  handler->addEventVariable("ISCUTVETOIDNOISOGOODELECTRONS",     new EventVariableObjectVariableVector<int>("passCutBasedVetoIdNoIso",             "goodElectrons"));
  handler->addEventVariable("ISCUTLOOSEIDNOISOGOODELECTRONS",    new EventVariableObjectVariableVector<int>("passCutBasedLooseIdNoIso",            "goodElectrons"));
  handler->addEventVariable("ISCUTMEDIUMIDNOISOGOODELECTRONS",   new EventVariableObjectVariableVector<int>("passCutBasedMediumIdNoIso",           "goodElectrons"));
  handler->addEventVariable("ISCUTTIGHTIDNOISOGOODELECTRONS",    new EventVariableObjectVariableVector<int>("passCutBasedTightIdNoIso",            "goodElectrons"));
  handler->addEventVariable("ISCUTTRIGIDISOVLGOODELECTRONS",     new EventVariableObjectVariableVector<int>("passCutBasedTrigIdIsoVL",             "goodElectrons"));//Missing in first set of 80X ntuples
  handler->addEventVariable("ECALPFCLUSTERRELISOGOODELECTRONS",  new EventVariableObjectVariableVector<double>("ELECTRON_RelIso_EcalPFClusterIso", "goodElectrons"));
  handler->addEventVariable("HCALPFCLUSTERRELISOGOODELECTRONS",  new EventVariableObjectVariableVector<double>("ELECTRON_RelIso_HcalPFClusterIso", "goodElectrons"));
  handler->addEventVariable("TRACKRELISOGOODELECTRONS",          new EventVariableObjectVariableVector<double>("ELECTRON_RelIso_TrackIso",         "goodElectrons"));
  handler->addEventVariable("RELISOCUTIDGOODELECTRONS",          new EventVariableObjectVariableVector<double>("ELECTRON_RELISO",                  "goodElectrons"));
  handler->addEventVariable("MINIISOGOODELECTRONS",              new EventVariableObjectVariableVector<double>("MINIISO",                          "goodElectrons"));
  handler->addEventVariable("PTRATIOGOODELECTRONS",              new EventVariableObjectVariableVector<double>("ptRatio",                          "goodElectrons"));
  handler->addEventVariable("PTRELGOODELECTRONS",                new EventVariableObjectVariableVector<double>("ptRel",                            "goodElectrons"));
  handler->addEventVariable("RELISOGOODELECTRONS",               new EventVariableObjectVariableVector<double>("RELISO",                           "goodElectrons"));
  handler->addEventVariable("CONECORRECTEDPTGOODELECTRONS",      new EventVariableObjectVariableVector<double>("conecorrectedPt",                  "goodElectrons"));
  handler->addEventVariable("SCETAGOODELECTRONS",                new EventVariableObjectVariableVector<double>("superClustereta",                  "goodElectrons"));
  handler->addEventVariable("FULL5X5SIGMAIETAIETAGOODELECTRONS", new EventVariableObjectVariableVector<double>("full5x5_sigmaIetaIeta",            "goodElectrons"));
  handler->addEventVariable("DETAGOODELECTRONS",                 new EventVariableObjectVariableVector<double>("deltaEtaSuperClusterTrackAtVtx",   "goodElectrons"));
  handler->addEventVariable("DPHIGOODELECTRONS",                 new EventVariableObjectVariableVector<double>("deltaPhiSuperClusterTrackAtVtx",   "goodElectrons"));
  handler->addEventVariable("HOVEREGOODELECTRONS",               new EventVariableObjectVariableVector<double>("hcalOverEcal",                     "goodElectrons"));
  handler->addEventVariable("OOEMOOPGOODELECTRONS",              new EventVariableObjectVariableVector<double>("1oEm1oPcorrected",                 "goodElectrons"));
  handler->addEventVariable("DXYGOODELECTRONS",                  new EventVariableObjectVariableVector<double>("dxy",                              "goodElectrons"));
  handler->addEventVariable("DZGOODELECTRONS",                   new EventVariableObjectVariableVector<double>("dz",                               "goodElectrons"));
  handler->addEventVariable("QCTFGOODELECTRONS",                 new EventVariableObjectVariableVector<int>("ctfTrackCharge",                      "goodElectrons"));
  handler->addEventVariable("QSCPIXGOODELECTRONS",               new EventVariableObjectVariableVector<int>("scPixCharge",                         "goodElectrons"));
  handler->addEventVariable("QGSFGOODELECTRONS",                 new EventVariableObjectVariableVector<int>("gsfTrackCharge",                      "goodElectrons"));
  handler->addEventVariable("ISALLQCONSISTENTGOODELECTRONS",     new EventVariableObjectVariableVector<int>("isGsfCtfScPixChargeConsistent",       "goodElectrons"));
  handler->addEventVariable("fakeRoleGOODELECTRONS",             new EventVariableObjectVariableVector<int>("fakeRole",                            "goodElectrons"));//is Fake role (track proxy)
  //
  handler->addEventVariable("goodElectronsDgoodPhotons",   new EventVariableDvector("goodElectrons", "goodPhotons"));
  handler->addEventVariable("goodElectronsDgoodJets",      new EventVariableDvector("goodElectrons", "goodJets"));
  handler->addEventVariable("goodElectronsDgoodLeptons",   new EventVariableDvector("goodElectrons", {"goodElectrons", "goodMuons"}, "goodLeptons"));
  //
  // ConeConstituents for electrons:
  handler->addEventVariable("JETCORRJETPTGOODELECTRONS",        new EventVariableObjectVariableVector<double>("JETCORRJETPT",         "goodElectrons"));
  handler->addEventVariable("JETLRMGOODELECTRONS",              new EventVariableObjectVariableVector<double>("JETLRM",               "goodElectrons"));
  handler->addEventVariable("JETNOOFCONSTGOODELECTRONS",        new EventVariableObjectVariableVector<int>(   "JETNOOFCONST",         "goodElectrons"));
  handler->addEventVariable("JETCHMULTGOODELECTRONS",           new EventVariableObjectVariableVector<int>(   "JETCHMULT",            "goodElectrons"));
  handler->addEventVariable("JETCHHADMULTGOODELECTRONS",        new EventVariableObjectVariableVector<int>(   "JETCHHADMULT",         "goodElectrons"));
  handler->addEventVariable("JETCSVRAWGOODELECTRONS",           new EventVariableObjectVariableVector<double>("JETCSVBTAG",           "goodElectrons"));
  handler->addEventVariable("JETJPRAWGOODELECTRONS",            new EventVariableObjectVariableVector<double>("JETJPBTAG",            "goodElectrons"));
  handler->addEventVariable("JETMVARAWGOODELECTRONS",           new EventVariableObjectVariableVector<double>("JETMVABTAG",           "goodElectrons"));
  handler->addEventVariable("CONESUMETDR03GOODELECTRONS",       new EventVariableObjectVariableVector<double>("CONESUMETDR03",        "goodElectrons"));
  handler->addEventVariable("CONENDR03GOODELECTRONS",           new EventVariableObjectVariableVector<int>(   "CONENDR03",            "goodElectrons"));
  handler->addEventVariable("CONESUMETDR04GOODELECTRONS",       new EventVariableObjectVariableVector<double>("CONESUMETDR04",        "goodElectrons"));
  handler->addEventVariable("CONENDR04GOODELECTRONS",           new EventVariableObjectVariableVector<int>(   "CONENDR04",            "goodElectrons"));
  handler->addEventVariable("CONESUMETDR03TO07GOODELECTRONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR03to07",    "goodElectrons"));
  handler->addEventVariable("CONENDR03TO07GOODELECTRONS",       new EventVariableObjectVariableVector<int>(   "CONENDR03to07",        "goodElectrons"));
  handler->addEventVariable("CONESUMETDR04TO08GOODELECTRONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR04to08",    "goodElectrons"));
  handler->addEventVariable("CONENDR04TO08GOODELECTRONS",       new EventVariableObjectVariableVector<int>(   "CONENDR04to08",        "goodElectrons"));
  handler->addEventVariable("CONESUMETDR01TO08GOODELECTRONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR01to08",    "goodElectrons"));
  handler->addEventVariable("CONENDR01TO08GOODELECTRONS",       new EventVariableObjectVariableVector<int>(   "CONENDR01to08",        "goodElectrons"));
  handler->addEventVariable("CONESUMETDR02TO08GOODELECTRONS",   new EventVariableObjectVariableVector<double>("CONESUMETDR02to08",    "goodElectrons"));
  handler->addEventVariable("CONENDR02TO08GOODELECTRONS",       new EventVariableObjectVariableVector<int>(   "CONENDR02to08",        "goodElectrons"));
  handler->addEventVariable("CONEPTDR03GOODELECTRONS",          new EventVariableObjectVariableVector<double>("CONEPTDR03",           "goodElectrons"));
  handler->addEventVariable("CONEMASSDR03GOODELECTRONS",        new EventVariableObjectVariableVector<double>("CONEMASSDR03",         "goodElectrons"));
  handler->addEventVariable("CONEPTDR04GOODELECTRONS",          new EventVariableObjectVariableVector<double>("CONEPTDR04",           "goodElectrons"));
  handler->addEventVariable("CONEMASSDR04GOODELECTRONS",        new EventVariableObjectVariableVector<double>("CONEMASSDR04",         "goodElectrons"));
  handler->addEventVariable("CONEPTDR03TO07GOODELECTRONS",      new EventVariableObjectVariableVector<double>("CONEPTDR03to07",       "goodElectrons"));
  handler->addEventVariable("CONEMASSDR03TO07GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR03to07",     "goodElectrons"));
  handler->addEventVariable("CONEPTDR04TO08GOODELECTRONS",      new EventVariableObjectVariableVector<double>("CONEPTDR04to08",       "goodElectrons"));
  handler->addEventVariable("CONEMASSDR04TO08GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR04to08",     "goodElectrons"));
  handler->addEventVariable("CONEPTDR01TO08GOODELECTRONS",      new EventVariableObjectVariableVector<double>("CONEPTDR01to08",       "goodElectrons"));
  handler->addEventVariable("CONEMASSDR01TO08GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR01to08",     "goodElectrons"));
  handler->addEventVariable("CONEPTDR02TO08GOODELECTRONS",      new EventVariableObjectVariableVector<double>("CONEPTDR02to08",       "goodElectrons"));
  handler->addEventVariable("CONEMASSDR02TO08GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONEMASSDR02to08",     "goodElectrons"));
  handler->addEventVariable("CONECHSUMETDR03GOODELECTRONS",     new EventVariableObjectVariableVector<double>("CONECHSUMETDR03",      "goodElectrons"));
  handler->addEventVariable("CONECHNDR03GOODELECTRONS",         new EventVariableObjectVariableVector<int>(   "CONECHNDR03",          "goodElectrons"));
  handler->addEventVariable("CONECHSUMETDR04GOODELECTRONS",     new EventVariableObjectVariableVector<double>("CONECHSUMETDR04",      "goodElectrons"));
  handler->addEventVariable("CONECHNDR04GOODELECTRONS",         new EventVariableObjectVariableVector<int>(   "CONECHNDR04",          "goodElectrons"));
  handler->addEventVariable("CONECHSUMETDR03TO07GOODELECTRONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR03to07",  "goodElectrons"));
  handler->addEventVariable("CONECHNDR03TO07GOODELECTRONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR03to07",      "goodElectrons"));
  handler->addEventVariable("CONECHSUMETDR04TO08GOODELECTRONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR04to08",  "goodElectrons"));
  handler->addEventVariable("CONECHNDR04TO08GOODELECTRONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR04to08",      "goodElectrons"));
  handler->addEventVariable("CONECHSUMETDR01TO08GOODELECTRONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR01to08",  "goodElectrons"));
  handler->addEventVariable("CONECHNDR01TO08GOODELECTRONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR01to08",      "goodElectrons"));
  handler->addEventVariable("CONECHSUMETDR02TO08GOODELECTRONS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR02to08",  "goodElectrons"));
  handler->addEventVariable("CONECHNDR02TO08GOODELECTRONS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR02to08",      "goodElectrons"));
  handler->addEventVariable("CONECHPTDR03GOODELECTRONS",        new EventVariableObjectVariableVector<double>("CONECHPTDR03",         "goodElectrons"));
  handler->addEventVariable("CONECHMASSDR03GOODELECTRONS",      new EventVariableObjectVariableVector<double>("CONECHMASSDR03",       "goodElectrons"));
  handler->addEventVariable("CONECHPTDR04GOODELECTRONS",        new EventVariableObjectVariableVector<double>("CONECHPTDR04",         "goodElectrons"));
  handler->addEventVariable("CONECHMASSDR04GOODELECTRONS",      new EventVariableObjectVariableVector<double>("CONECHMASSDR04",       "goodElectrons"));
  handler->addEventVariable("CONECHPTDR03TO07GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR03to07",     "goodElectrons"));
  handler->addEventVariable("CONECHMASSDR03TO07GOODELECTRONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR03to07",   "goodElectrons"));
  handler->addEventVariable("CONECHPTDR04TO08GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR04to08",     "goodElectrons"));
  handler->addEventVariable("CONECHMASSDR04TO08GOODELECTRONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR04to08",   "goodElectrons"));
  handler->addEventVariable("CONECHPTDR01TO08GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR01to08",     "goodElectrons"));
  handler->addEventVariable("CONECHMASSDR01TO08GOODELECTRONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR01to08",   "goodElectrons"));
  handler->addEventVariable("CONECHPTDR02TO08GOODELECTRONS",    new EventVariableObjectVariableVector<double>("CONECHPTDR02to08",     "goodElectrons"));
  handler->addEventVariable("CONECHMASSDR02TO08GOODELECTRONS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR02to08",   "goodElectrons"));
  //
  handler->addEventVariable("NBASICELECTRONS",                    new EventVariableN("NBASICELECTRONS",                                             "basicElectrons"));
  handler->addEventVariable("QBASICELECTRONS",                    new EventVariableObjectVariableVector<int>("CHARGE",                              "basicElectrons"));
  handler->addEventVariable("PTBASICELECTRONS",                   new EventVariableObjectVariableVector<double>("PT",                               "basicElectrons"));
  handler->addEventVariable("ETABASICELECTRONS",                  new EventVariableObjectVariableVector<double>("ETA",                              "basicElectrons"));
  handler->addEventVariable("PHIBASICELECTRONS",                  new EventVariableObjectVariableVector<double>("PHI",                              "basicElectrons"));
  handler->addEventVariable("RELISOBASICELECTRONS",               new EventVariableObjectVariableVector<double>("RELISO",                           "basicElectrons"));
  handler->addEventVariable("MINIISOBASICELECTRONS",              new EventVariableObjectVariableVector<double>("MINIISO",                          "basicElectrons"));
  handler->addEventVariable("PTRATIOBASICELECTRONS",              new EventVariableObjectVariableVector<double>("ptRatio",                          "basicElectrons"));
  handler->addEventVariable("PTRELBASICELECTRONS",                new EventVariableObjectVariableVector<double>("ptRel",                            "basicElectrons"));
  handler->addEventVariable("SCETABASICELECTRONS",                new EventVariableObjectVariableVector<double>("superClustereta",                  "basicElectrons"));
  handler->addEventVariable("FULL5X5SIGMAIETAIETABASICELECTRONS", new EventVariableObjectVariableVector<double>("full5x5_sigmaIetaIeta",            "basicElectrons"));
  handler->addEventVariable("DETABASICELECTRONS",                 new EventVariableObjectVariableVector<double>("deltaEtaSuperClusterTrackAtVtx",   "basicElectrons"));
  handler->addEventVariable("DPHIBASICELECTRONS",                 new EventVariableObjectVariableVector<double>("deltaPhiSuperClusterTrackAtVtx",   "basicElectrons"));
  handler->addEventVariable("HOVEREBASICELECTRONS",               new EventVariableObjectVariableVector<double>("hcalOverEcal",                     "basicElectrons"));
  handler->addEventVariable("OOEMOOPBASICELECTRONS",              new EventVariableObjectVariableVector<double>("1oEm1oPcorrected",                 "basicElectrons"));
  handler->addEventVariable("DXYBASICELECTRONS",                  new EventVariableObjectVariableVector<double>("dxy",                              "basicElectrons"));
  handler->addEventVariable("DZBASICELECTRONS",                   new EventVariableObjectVariableVector<double>("dz",                               "basicElectrons"));
  handler->addEventVariable("QCTFBASICELECTRONS",                 new EventVariableObjectVariableVector<int>("ctfTrackCharge",                      "basicElectrons"));
  handler->addEventVariable("QSCPIXBASICELECTRONS",               new EventVariableObjectVariableVector<int>("scPixCharge",                         "basicElectrons"));
  handler->addEventVariable("QGSFBASICELECTRONS",                 new EventVariableObjectVariableVector<int>("gsfTrackCharge",                      "basicElectrons"));
  handler->addEventVariable("ISALLQCONSISTENTBASICELECTRONS",     new EventVariableObjectVariableVector<int>("isGsfCtfScPixChargeConsistent",       "basicElectrons"));
  handler->addEventVariable("ISCUTVETOIDBASICELECTRONS",          new EventVariableObjectVariableVector<int>("passCutBasedVetoId",                  "basicElectrons"));
  handler->addEventVariable("ISCUTLOOSEIDBASICELECTRONS",         new EventVariableObjectVariableVector<int>("passCutBasedLooseId",                 "basicElectrons"));
  handler->addEventVariable("ISCUTMEDIUMIDBASICELECTRONS",        new EventVariableObjectVariableVector<int>("passCutBasedMediumId",                "basicElectrons"));
  handler->addEventVariable("ISCUTTIGHTIDBASICELECTRONS",         new EventVariableObjectVariableVector<int>("passCutBasedTightId",                 "basicElectrons"));
  handler->addEventVariable("ISHEEPIDBASICELECTRONS",             new EventVariableObjectVariableVector<int>("passHEEP",                            "basicElectrons"));
  handler->addEventVariable("ISCUTVETOIDNOISOBASICELECTRONS",     new EventVariableObjectVariableVector<int>("passCutBasedVetoIdNoIso",             "basicElectrons"));
  handler->addEventVariable("ISCUTLOOSEIDNOISOBASICELECTRONS",    new EventVariableObjectVariableVector<int>("passCutBasedLooseIdNoIso",            "basicElectrons"));
  handler->addEventVariable("ISCUTMEDIUMIDNOISOBASICELECTRONS",   new EventVariableObjectVariableVector<int>("passCutBasedMediumIdNoIso",           "basicElectrons"));
  handler->addEventVariable("ISCUTTIGHTIDNOISOBASICELECTRONS",    new EventVariableObjectVariableVector<int>("passCutBasedTightIdNoIso",            "basicElectrons"));
  handler->addEventVariable("ISCUTTRIGIDISOVLBASICELECTRONS",     new EventVariableObjectVariableVector<int>("passCutBasedTrigIdIsoVL",             "basicElectrons"));//Missing in first set of 80X ntuples
  handler->addEventVariable("ECALPFCLUSTERRELISOBASICELECTRONS",  new EventVariableObjectVariableVector<double>("ELECTRON_RelIso_EcalPFClusterIso", "basicElectrons"));
  handler->addEventVariable("HCALPFCLUSTERRELISOBASICELECTRONS",  new EventVariableObjectVariableVector<double>("ELECTRON_RelIso_HcalPFClusterIso", "basicElectrons"));
  handler->addEventVariable("TRACKRELISOBASICELECTRONS",          new EventVariableObjectVariableVector<double>("ELECTRON_RelIso_TrackIso",         "basicElectrons"));
  //
  handler->addEventVariable("QNONPROMPTELECTRONS",       new EventVariableObjectVariableVector<int>("CHARGE",     "nonPromptElectrons"));
  handler->addEventVariable("PTNONPROMPTELECTRONS",      new EventVariableObjectVariableVector<double>("PT",      "nonPromptElectrons"));
  handler->addEventVariable("ETANONPROMPTELECTRONS",     new EventVariableObjectVariableVector<double>("ETA",     "nonPromptElectrons"));
  handler->addEventVariable("PHINONPROMPTELECTRONS",     new EventVariableObjectVariableVector<double>("PHI",     "nonPromptElectrons"));
  handler->addEventVariable("RELISONONPROMPTELECTRONS",  new EventVariableObjectVariableVector<double>("RELISO",  "nonPromptElectrons"));
  handler->addEventVariable("MINIISONONPROMPTELECTRONS", new EventVariableObjectVariableVector<double>("MINIISO", "nonPromptElectrons"));
  handler->addEventVariable("PTRATIONONPROMPTELECTRONS", new EventVariableObjectVariableVector<double>("ptRatio", "nonPromptElectrons"));  
  handler->addEventVariable("PTRELNONPROMPTELECTRONS",   new EventVariableObjectVariableVector<double>("ptRel",   "nonPromptElectrons"));
  handler->addEventVariable("DXYNONPROMPTELECTRONS",     new EventVariableObjectVariableVector<double>("dxy",     "nonPromptElectrons"));
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
  handler->addEventVariable("NGOODTAUS",                   new EventVariableN("NGOODTAUS",                                                      "goodTaus"));
  handler->addEventVariable("QGOODTAUS",                   new EventVariableObjectVariableVector<int>("CHARGE",                                 "goodTaus"));
  handler->addEventVariable("PTGOODTAUS",                  new EventVariableObjectVariableVector<double>("PT",                                  "goodTaus"));
  handler->addEventVariable("ETAGOODTAUS",                 new EventVariableObjectVariableVector<double>("ETA",                                 "goodTaus"));
  handler->addEventVariable("PHIGOODTAUS",                 new EventVariableObjectVariableVector<double>("PHI",                                 "goodTaus"));
  handler->addEventVariable("fakeRoleGOODTAUS",            new EventVariableObjectVariableVector<int>("fakeRole",                               "goodTaus")); 
  handler->addEventVariable("MINIISOGOODTAUS",             new EventVariableObjectVariableVector<double>("MINIISO",                             "goodTaus"));//this + next 3 lines are not necessarly..
  handler->addEventVariable("PTRATIOGOODTAUS",             new EventVariableObjectVariableVector<double>("ptRatio",                             "goodTaus"));//..relevant for taus, but are kept since..
  handler->addEventVariable("PTRELGOODTAUS",               new EventVariableObjectVariableVector<double>("ptRel",                               "goodTaus"));//..they are needed for the conecorrectedPt..
  handler->addEventVariable("RELISOGOODTAUS",              new EventVariableObjectVariableVector<double>("RELISO",                              "goodTaus"));//..calculation.
  handler->addEventVariable("CONECORRECTEDPTGOODTAUS",     new EventVariableObjectVariableVector<double>("conecorrectedPt",                     "goodTaus"));//
  handler->addEventVariable("VLOOSEISOMVARUN2DBGOODTAUS",  new EventVariableObjectVariableVector<int>("byVLooseIsolationMVArun2v1DBnewDMwLT",   "goodTaus"));
  handler->addEventVariable("LOOSEISOMVARUN2DBGOODTAUS",   new EventVariableObjectVariableVector<int>("byLooseIsolationMVArun2v1DBnewDMwLT",    "goodTaus"));
  handler->addEventVariable("MEDIUMISOMVARUN2DBGOODTAUS",  new EventVariableObjectVariableVector<int>("byMediumIsolationMVArun2v1DBnewDMwLT",   "goodTaus"));
  handler->addEventVariable("TIGHTISOMVARUN2DBGOODTAUS",   new EventVariableObjectVariableVector<int>("byTightIsolationMVArun2v1DBnewDMwLT",    "goodTaus"));
  handler->addEventVariable("VTIGHTISOMVARUN2DBGOODTAUS",  new EventVariableObjectVariableVector<int>("byVTightIsolationMVArun2v1DBnewDMwLT",   "goodTaus"));
  handler->addEventVariable("VVTIGHTISOMVARUN2DBGOODTAUS", new EventVariableObjectVariableVector<int>("byVVTightIsolationMVArun2v1DBnewDMwLT",  "goodTaus"));
  handler->addEventVariable("VLOOSEISOMVARUN2PWGOODTAUS",  new EventVariableObjectVariableVector<int>("byVLooseIsolationMVArun2v1PWnewDMwLT",   "goodTaus"));
  handler->addEventVariable("LOOSEISOMVARUN2PWGOODTAUS",   new EventVariableObjectVariableVector<int>("byLooseIsolationMVArun2v1PWnewDMwLT",    "goodTaus"));
  handler->addEventVariable("MEDIUMISOMVARUN2PWGOODTAUS",  new EventVariableObjectVariableVector<int>("byMediumIsolationMVArun2v1PWnewDMwLT",   "goodTaus"));
  handler->addEventVariable("TIGHTISOMVARUN2PWGOODTAUS",   new EventVariableObjectVariableVector<int>("byTightIsolationMVArun2v1PWnewDMwLT",    "goodTaus"));
  handler->addEventVariable("VTIGHTISOMVARUN2PWGOODTAUS",  new EventVariableObjectVariableVector<int>("byVTightIsolationMVArun2v1PWnewDMwLT",   "goodTaus"));
  handler->addEventVariable("VVTIGHTISOMVARUN2PWGOODTAUS", new EventVariableObjectVariableVector<int>("byVVTightIsolationMVArun2v1PWnewDMwLT",  "goodTaus"));
  handler->addEventVariable("VLOOSEANTIELEMVA6GOODTAUS",   new EventVariableObjectVariableVector<int>("againstElectronVLooseMVA6",              "goodTaus"));
  handler->addEventVariable("LOOSEANTIELEMVA6GOODTAUS",    new EventVariableObjectVariableVector<int>("againstElectronLooseMVA6",               "goodTaus"));
  handler->addEventVariable("MEDIUMANTIELEMVA6GOODTAUS",   new EventVariableObjectVariableVector<int>("againstElectronMediumMVA6",              "goodTaus"));
  handler->addEventVariable("TIGHTANTIELEMVA6GOODTAUS",    new EventVariableObjectVariableVector<int>("againstElectronTightMVA6",               "goodTaus"));
  handler->addEventVariable("VTIGHTANTIELEMVA6GOODTAUS",   new EventVariableObjectVariableVector<int>("againstElectronVTightMVA6",              "goodTaus"));
  handler->addEventVariable("LOOSEANTIMU3GOODTAUS",        new EventVariableObjectVariableVector<int>("againstMuonLoose3",                      "goodTaus"));
  handler->addEventVariable("TIGHTANTIMU3GOODTAUS",        new EventVariableObjectVariableVector<int>("againstMuonTight3",                      "goodTaus"));
  //
  // ConeConstituents for taus:
  handler->addEventVariable("JETCORRJETPTGOODTAUS",        new EventVariableObjectVariableVector<double>("JETCORRJETPT",         "goodTaus"));
  handler->addEventVariable("JETLRMGOODTAUS",              new EventVariableObjectVariableVector<double>("JETLRM",               "goodTaus"));
  handler->addEventVariable("JETNOOFCONSTGOODTAUS",        new EventVariableObjectVariableVector<int>(   "JETNOOFCONST",         "goodTaus"));
  handler->addEventVariable("JETCHMULTGOODTAUS",           new EventVariableObjectVariableVector<int>(   "JETCHMULT",            "goodTaus"));
  handler->addEventVariable("JETCHHADMULTGOODTAUS",        new EventVariableObjectVariableVector<int>(   "JETCHHADMULT",         "goodTaus"));
  handler->addEventVariable("JETCSVRAWGOODTAUS",           new EventVariableObjectVariableVector<double>("JETCSVBTAG",           "goodTaus"));
  handler->addEventVariable("JETJPRAWGOODTAUS",            new EventVariableObjectVariableVector<double>("JETJPBTAG",            "goodTaus"));
  handler->addEventVariable("JETMVARAWGOODTAUS",           new EventVariableObjectVariableVector<double>("JETMVABTAG",           "goodTaus"));
  handler->addEventVariable("CONESUMETDR03GOODTAUS",       new EventVariableObjectVariableVector<double>("CONESUMETDR03",        "goodTaus"));
  handler->addEventVariable("CONENDR03GOODTAUS",           new EventVariableObjectVariableVector<int>(   "CONENDR03",            "goodTaus"));
  handler->addEventVariable("CONESUMETDR04GOODTAUS",       new EventVariableObjectVariableVector<double>("CONESUMETDR04",        "goodTaus"));
  handler->addEventVariable("CONENDR04GOODTAUS",           new EventVariableObjectVariableVector<int>(   "CONENDR04",            "goodTaus"));
  handler->addEventVariable("CONESUMETDR03TO07GOODTAUS",   new EventVariableObjectVariableVector<double>("CONESUMETDR03to07",    "goodTaus"));
  handler->addEventVariable("CONENDR03TO07GOODTAUS",       new EventVariableObjectVariableVector<int>(   "CONENDR03to07",        "goodTaus"));
  handler->addEventVariable("CONESUMETDR04TO08GOODTAUS",   new EventVariableObjectVariableVector<double>("CONESUMETDR04to08",    "goodTaus"));
  handler->addEventVariable("CONENDR04TO08GOODTAUS",       new EventVariableObjectVariableVector<int>(   "CONENDR04to08",        "goodTaus"));
  handler->addEventVariable("CONESUMETDR01TO08GOODTAUS",   new EventVariableObjectVariableVector<double>("CONESUMETDR01to08",    "goodTaus"));
  handler->addEventVariable("CONENDR01TO08GOODTAUS",       new EventVariableObjectVariableVector<int>(   "CONENDR01to08",        "goodTaus"));
  handler->addEventVariable("CONESUMETDR02TO08GOODTAUS",   new EventVariableObjectVariableVector<double>("CONESUMETDR02to08",    "goodTaus"));
  handler->addEventVariable("CONENDR02TO08GOODTAUS",       new EventVariableObjectVariableVector<int>(   "CONENDR02to08",        "goodTaus"));
  handler->addEventVariable("CONEPTDR03GOODTAUS",          new EventVariableObjectVariableVector<double>("CONEPTDR03",           "goodTaus"));
  handler->addEventVariable("CONEMASSDR03GOODTAUS",        new EventVariableObjectVariableVector<double>("CONEMASSDR03",         "goodTaus"));
  handler->addEventVariable("CONEPTDR04GOODTAUS",          new EventVariableObjectVariableVector<double>("CONEPTDR04",           "goodTaus"));
  handler->addEventVariable("CONEMASSDR04GOODTAUS",        new EventVariableObjectVariableVector<double>("CONEMASSDR04",         "goodTaus"));
  handler->addEventVariable("CONEPTDR03TO07GOODTAUS",      new EventVariableObjectVariableVector<double>("CONEPTDR03to07",       "goodTaus"));
  handler->addEventVariable("CONEMASSDR03TO07GOODTAUS",    new EventVariableObjectVariableVector<double>("CONEMASSDR03to07",     "goodTaus"));
  handler->addEventVariable("CONEPTDR04TO08GOODTAUS",      new EventVariableObjectVariableVector<double>("CONEPTDR04to08",       "goodTaus"));
  handler->addEventVariable("CONEMASSDR04TO08GOODTAUS",    new EventVariableObjectVariableVector<double>("CONEMASSDR04to08",     "goodTaus"));
  handler->addEventVariable("CONEPTDR01TO08GOODTAUS",      new EventVariableObjectVariableVector<double>("CONEPTDR01to08",       "goodTaus"));
  handler->addEventVariable("CONEMASSDR01TO08GOODTAUS",    new EventVariableObjectVariableVector<double>("CONEMASSDR01to08",     "goodTaus"));
  handler->addEventVariable("CONEPTDR02TO08GOODTAUS",      new EventVariableObjectVariableVector<double>("CONEPTDR02to08",       "goodTaus"));
  handler->addEventVariable("CONEMASSDR02TO08GOODTAUS",    new EventVariableObjectVariableVector<double>("CONEMASSDR02to08",     "goodTaus"));
  handler->addEventVariable("CONECHSUMETDR03GOODTAUS",     new EventVariableObjectVariableVector<double>("CONECHSUMETDR03",      "goodTaus"));
  handler->addEventVariable("CONECHNDR03GOODTAUS",         new EventVariableObjectVariableVector<int>(   "CONECHNDR03",          "goodTaus"));
  handler->addEventVariable("CONECHSUMETDR04GOODTAUS",     new EventVariableObjectVariableVector<double>("CONECHSUMETDR04",      "goodTaus"));
  handler->addEventVariable("CONECHNDR04GOODTAUS",         new EventVariableObjectVariableVector<int>(   "CONECHNDR04",          "goodTaus"));
  handler->addEventVariable("CONECHSUMETDR03TO07GOODTAUS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR03to07",  "goodTaus"));
  handler->addEventVariable("CONECHNDR03TO07GOODTAUS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR03to07",      "goodTaus"));
  handler->addEventVariable("CONECHSUMETDR04TO08GOODTAUS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR04to08",  "goodTaus"));
  handler->addEventVariable("CONECHNDR04TO08GOODTAUS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR04to08",      "goodTaus"));
  handler->addEventVariable("CONECHSUMETDR01TO08GOODTAUS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR01to08",  "goodTaus"));
  handler->addEventVariable("CONECHNDR01TO08GOODTAUS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR01to08",      "goodTaus"));
  handler->addEventVariable("CONECHSUMETDR02TO08GOODTAUS", new EventVariableObjectVariableVector<double>("CONECHSUMETDR02to08",  "goodTaus"));
  handler->addEventVariable("CONECHNDR02TO08GOODTAUS",     new EventVariableObjectVariableVector<int>(   "CONECHNDR02to08",      "goodTaus"));
  handler->addEventVariable("CONECHPTDR03GOODTAUS",        new EventVariableObjectVariableVector<double>("CONECHPTDR03",         "goodTaus"));
  handler->addEventVariable("CONECHMASSDR03GOODTAUS",      new EventVariableObjectVariableVector<double>("CONECHMASSDR03",       "goodTaus"));
  handler->addEventVariable("CONECHPTDR04GOODTAUS",        new EventVariableObjectVariableVector<double>("CONECHPTDR04",         "goodTaus"));
  handler->addEventVariable("CONECHMASSDR04GOODTAUS",      new EventVariableObjectVariableVector<double>("CONECHMASSDR04",       "goodTaus"));
  handler->addEventVariable("CONECHPTDR03TO07GOODTAUS",    new EventVariableObjectVariableVector<double>("CONECHPTDR03to07",     "goodTaus"));
  handler->addEventVariable("CONECHMASSDR03TO07GOODTAUS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR03to07",   "goodTaus"));
  handler->addEventVariable("CONECHPTDR04TO08GOODTAUS",    new EventVariableObjectVariableVector<double>("CONECHPTDR04to08",     "goodTaus"));
  handler->addEventVariable("CONECHMASSDR04TO08GOODTAUS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR04to08",   "goodTaus"));
  handler->addEventVariable("CONECHPTDR01TO08GOODTAUS",    new EventVariableObjectVariableVector<double>("CONECHPTDR01to08",     "goodTaus"));
  handler->addEventVariable("CONECHMASSDR01TO08GOODTAUS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR01to08",   "goodTaus"));
  handler->addEventVariable("CONECHPTDR02TO08GOODTAUS",    new EventVariableObjectVariableVector<double>("CONECHPTDR02to08",     "goodTaus"));
  handler->addEventVariable("CONECHMASSDR02TO08GOODTAUS",  new EventVariableObjectVariableVector<double>("CONECHMASSDR02to08",   "goodTaus"));
  //
  handler->addEventVariable("NBASICTAUS",                   new EventVariableN("NBASICTAUS",                                                     "basicTaus"));
  handler->addEventVariable("PTBASICTAUS",                  new EventVariableObjectVariableVector<double>("PT",                                  "basicTaus"));
  handler->addEventVariable("ETABASICTAUS",                 new EventVariableObjectVariableVector<double>("ETA",                                 "basicTaus"));
  handler->addEventVariable("PHIBASICTAUS",                 new EventVariableObjectVariableVector<double>("PHI",                                 "basicTaus"));
  handler->addEventVariable("VLOOSEISOMVARUN2DBBASICTAUS",  new EventVariableObjectVariableVector<int>("byVLooseIsolationMVArun2v1DBnewDMwLT",   "basicTaus"));
  handler->addEventVariable("LOOSEISOMVARUN2DBBASICTAUS",   new EventVariableObjectVariableVector<int>("byLooseIsolationMVArun2v1DBnewDMwLT",    "basicTaus"));
  handler->addEventVariable("MEDIUMISOMVARUN2DBBASICTAUS",  new EventVariableObjectVariableVector<int>("byMediumIsolationMVArun2v1DBnewDMwLT",   "basicTaus"));
  handler->addEventVariable("TIGHTISOMVARUN2DBBASICTAUS",   new EventVariableObjectVariableVector<int>("byTightIsolationMVArun2v1DBnewDMwLT",    "basicTaus"));
  handler->addEventVariable("VTIGHTISOMVARUN2DBBASICTAUS",  new EventVariableObjectVariableVector<int>("byVTightIsolationMVArun2v1DBnewDMwLT",   "basicTaus"));
  handler->addEventVariable("VVTIGHTISOMVARUN2DBBASICTAUS", new EventVariableObjectVariableVector<int>("byVVTightIsolationMVArun2v1DBnewDMwLT",  "basicTaus"));
  handler->addEventVariable("VLOOSEISOMVARUN2PWBASICTAUS",  new EventVariableObjectVariableVector<int>("byVLooseIsolationMVArun2v1PWnewDMwLT",   "basicTaus"));
  handler->addEventVariable("LOOSEISOMVARUN2PWBASICTAUS",   new EventVariableObjectVariableVector<int>("byLooseIsolationMVArun2v1PWnewDMwLT",    "basicTaus"));
  handler->addEventVariable("MEDIUMISOMVARUN2PWBASICTAUS",  new EventVariableObjectVariableVector<int>("byMediumIsolationMVArun2v1PWnewDMwLT",   "basicTaus"));
  handler->addEventVariable("TIGHTISOMVARUN2PWBASICTAUS",   new EventVariableObjectVariableVector<int>("byTightIsolationMVArun2v1PWnewDMwLT",    "basicTaus"));
  handler->addEventVariable("VTIGHTISOMVARUN2PWBASICTAUS",  new EventVariableObjectVariableVector<int>("byVTightIsolationMVArun2v1PWnewDMwLT",   "basicTaus"));
  handler->addEventVariable("VVTIGHTISOMVARUN2PWBASICTAUS", new EventVariableObjectVariableVector<int>("byVVTightIsolationMVArun2v1PWnewDMwLT",  "basicTaus"));
  handler->addEventVariable("VLOOSEANTIELEMVA6BASICTAUS",   new EventVariableObjectVariableVector<int>("againstElectronVLooseMVA6",              "basicTaus"));
  handler->addEventVariable("LOOSEANTIELEMVA6BASICTAUS",    new EventVariableObjectVariableVector<int>("againstElectronLooseMVA6",               "basicTaus"));
  handler->addEventVariable("MEDIUMANTIELEMVA6BASICTAUS",   new EventVariableObjectVariableVector<int>("againstElectronMediumMVA6",              "basicTaus"));
  handler->addEventVariable("TIGHTANTIELEMVA6BASICTAUS",    new EventVariableObjectVariableVector<int>("againstElectronTightMVA6",               "basicTaus"));
  handler->addEventVariable("VTIGHTANTIELEMVA6BASICTAUS",   new EventVariableObjectVariableVector<int>("againstElectronVTightMVA6",              "basicTaus"));
  handler->addEventVariable("LOOSEANTIMU3BASICTAUS",        new EventVariableObjectVariableVector<int>("againstMuonLoose3",                      "basicTaus"));
  handler->addEventVariable("TIGHTANTIMU3BASICTAUS",        new EventVariableObjectVariableVector<int>("againstMuonTight3",                      "basicTaus"));
  // additional "non-mva" Comb Iso DB Corr variables 
  handler->addEventVariable("LOOSECOMBINEDISODBCORR3HITSBASICTAUS", new EventVariableObjectVariableVector<int>("byLooseCombinedIsolationDeltaBetaCorr3Hits",  "basicTaus"));
  handler->addEventVariable("MEDIUMCOMBINEDISODBCORR3HITSBASICTAUS",new EventVariableObjectVariableVector<int>("byMediumCombinedIsolationDeltaBetaCorr3Hits", "basicTaus"));
  handler->addEventVariable("TIGHTCOMBINEDISODBCORR3HITSBASICTAUS", new EventVariableObjectVariableVector<int>("byTightCombinedIsolationDeltaBetaCorr3Hits",  "basicTaus"));
  //
  handler->addEventVariable("NNONISOTAUS", new EventVariableN("NNONISOTAUS","nonIsoTaus"));


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////
  ///Jet Variables///
  ///////////////////
  handler->addEventVariable("NGOODJETS",                 new EventVariableN("NGOODJETS",                                              "goodJets"));
  handler->addEventVariable("PTGOODJETS",                new EventVariableObjectVariableVector<double>("PT",                          "goodJets"));
  handler->addEventVariable("ETAGOODJETS",               new EventVariableObjectVariableVector<double>("ETA",                         "goodJets"));
  handler->addEventVariable("PHIGOODJETS",               new EventVariableObjectVariableVector<double>("PHI",                         "goodJets"));
  handler->addEventVariable("CSVRAWGOODJETS",            new EventVariableObjectVariableVector<double>("CSVraw",                      "goodJets"));
  handler->addEventVariable("JPRAWGOODJETS",             new EventVariableObjectVariableVector<double>("JPraw",                       "goodJets"));
  handler->addEventVariable("CMVARAWGOODJETS",           new EventVariableObjectVariableVector<double>("cMVAraw",                     "goodJets"));
  handler->addEventVariable("TOTALMULTGOODJETS",         new EventVariableObjectVariableVector<int>(   "numberOfConstituents",        "goodJets"));
  handler->addEventVariable("CHARMULTGOODJETS",          new EventVariableObjectVariableVector<int>(   "chargedMultiplicity",         "goodJets"));
  handler->addEventVariable("NEUTMULTGOODJETS",          new EventVariableObjectVariableVector<int>(   "neutralMultiplicity",         "goodJets"));
  handler->addEventVariable("MUONENERGYFRACGOODJETS",    new EventVariableObjectVariableVector<double>("muonEnergyFraction",          "goodJets"));
  handler->addEventVariable("CHARHADENERGYFRACGOODJETS", new EventVariableObjectVariableVector<double>("chargedHadronEnergyFraction", "goodJets"));
  handler->addEventVariable("CHAREMENERGYFRACGOODJETS",  new EventVariableObjectVariableVector<double>("chargedEmEnergyFraction",     "goodJets"));
  handler->addEventVariable("NEUTHADENERGYFRACGOODJETS", new EventVariableObjectVariableVector<double>("neutralHadronEnergyFraction", "goodJets"));
  handler->addEventVariable("NEUTEMENERGYFRACGOODJETS",  new EventVariableObjectVariableVector<double>("neutralEmEnergyFraction",     "goodJets"));
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
  handler->addEventVariable("HT",         new EventVariableSumPT("HT",          "goodJets"));
  handler->addEventVariable("HTCSVL",     new EventVariableSumPT("HTCSVL", "goodbJetsCSVL"));
  handler->addEventVariable("HTCSVM",     new EventVariableSumPT("HTCSVM", "goodbJetsCSVM"));
  handler->addEventVariable("NBJETSCSVL", new EventVariableN("NBJETSCSVL", "goodbJetsCSVL"));
  handler->addEventVariable("NBJETSCSVM", new EventVariableN("NBJETSCSVM", "goodbJetsCSVM"));
  handler->addEventVariable("WDIJETMASS", new EventVariablePairMass("WDIJETMASS", "goodJets", "WJET", mW, 10));
  //
  handler->addEventVariable("NBASICJETS",                 new EventVariableN("NBASICJETS",                                             "basicJets"));
  handler->addEventVariable("PTBASICJETS",                new EventVariableObjectVariableVector<double>("PT",                          "basicJets"));
  handler->addEventVariable("ETABASICJETS",               new EventVariableObjectVariableVector<double>("ETA",                         "basicJets"));
  handler->addEventVariable("PHIBASICJETS",               new EventVariableObjectVariableVector<double>("PHI",                         "basicJets"));
  handler->addEventVariable("CSVRAWBASICJETS",            new EventVariableObjectVariableVector<double>("CSVraw",                      "basicJets"));
  handler->addEventVariable("JPRAWBASICJETS",             new EventVariableObjectVariableVector<double>("JPraw",                       "basicJets"));
  handler->addEventVariable("CMVARAWBASICJETS",           new EventVariableObjectVariableVector<double>("cMVAraw",                     "basicJets"));
  handler->addEventVariable("TOTALMULTBASICJETS",         new EventVariableObjectVariableVector<int>(   "numberOfConstituents",        "basicJets"));
  handler->addEventVariable("CHARMULTBASICJETS",          new EventVariableObjectVariableVector<int>(   "chargedMultiplicity",         "basicJets"));
  handler->addEventVariable("NEUTMULTBASICJETS",          new EventVariableObjectVariableVector<int>(   "neutralMultiplicity",         "basicJets"));
  handler->addEventVariable("MUONENERGYFRACBASICJETS",    new EventVariableObjectVariableVector<double>("muonEnergyFraction",          "basicJets"));
  handler->addEventVariable("CHARHADENERGYFRACBASICJETS", new EventVariableObjectVariableVector<double>("chargedHadronEnergyFraction", "basicJets"));
  handler->addEventVariable("CHAREMENERGYFRACBASICJETS",  new EventVariableObjectVariableVector<double>("chargedEmEnergyFraction",     "basicJets"));
  handler->addEventVariable("NEUTHADENERGYFRACBASICJETS", new EventVariableObjectVariableVector<double>("neutralHadronEnergyFraction", "basicJets"));
  handler->addEventVariable("NEUTEMENERGYFRACBASICJETS",  new EventVariableObjectVariableVector<double>("neutralEmEnergyFraction",     "basicJets"));


  // --------------------------------------------------------------------------------------------------------------
  //////////////////////
  ///Photon Variables///
  //////////////////////
  handler->addEventVariable("NBASICPHOTONS",   new EventVariableN("NBASICPHOTONS",                  "basicPhotons"));
  handler->addEventVariable("PTBASICPHOTONS",  new EventVariableObjectVariableVector<double>("PT",  "basicPhotons"));
  handler->addEventVariable("ETABASICPHOTONS", new EventVariableObjectVariableVector<double>("ETA", "basicPhotons"));
  handler->addEventVariable("PHIBASICPHOTONS", new EventVariableObjectVariableVector<double>("PHI", "basicPhotons"));
  //
  handler->addEventVariable("NLOOSEPHOTONS",    new EventVariableN("NLOOSEPHOTONS",                  "loosePhotons"));//this collection doesnt have overlap cleaning
  handler->addEventVariable("PTLOOSEPHOTONS",   new EventVariableObjectVariableVector<double>("PT",  "loosePhotons"));//otherwise it is identical to "goodPhotons"
  handler->addEventVariable("ETALOOSEPHOTONS",  new EventVariableObjectVariableVector<double>("ETA", "loosePhotons"));
  handler->addEventVariable("PHILOOSEPHOTONS",  new EventVariableObjectVariableVector<double>("PHI", "loosePhotons"));
  //
  handler->addEventVariable("NGOODPHOTONS",    new EventVariableN("NGOODPHOTONS",                   "goodPhotons"));
  handler->addEventVariable("PTGOODPHOTONS",   new EventVariableObjectVariableVector<double>("PT",  "goodPhotons"));
  handler->addEventVariable("ETAGOODPHOTONS",  new EventVariableObjectVariableVector<double>("ETA", "goodPhotons"));
  handler->addEventVariable("PHIGOODPHOTONS",  new EventVariableObjectVariableVector<double>("PHI", "goodPhotons"));
  handler->addEventVariable("MPHOTONS",        new EventVariableMass("MPHOTONS",                    "goodPhotons"));
  //
  handler->addEventVariable("goodPhotonsDgoodJets",      new EventVariableDvector("goodPhotons", "goodJets"));
  handler->addEventVariable("goodPhotonsDgoodTaus",      new EventVariableDvector("goodPhotons", "goodTaus"));
  handler->addEventVariable("goodPhotonsDgoodElectrons", new EventVariableDvector("goodPhotons", "goodElectrons"));
  handler->addEventVariable("goodPhotonsDgoodMuons",     new EventVariableDvector("goodPhotons", "goodMuons"));

  
  // --------------------------------------------------------------------------------------------------------------
  /////////////////////
  ///Track Variables///
  /////////////////////
  handler->addEventVariable("NGOODINCLUSIVETRACKS",           new EventVariableN("NGOODINCLUSIVETRACKS",           "goodInclusiveTracks"));
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
  handler->addEventVariable("NPROMPTTRACKS7",                 new EventVariableN("NPROMPTTRACKS7",                 "promptTracks7"));
  handler->addEventVariable("NISOTRACKS7",                    new EventVariableN("NISOTRACKS7",                    "isoTracks7"));
  handler->addEventVariable("NISONONPROMPTTRACKS7",           new EventVariableN("NISONONPROMPTTRACKS7",           "isoNonPromptTracks7"));
  handler->addEventVariable("NPROMPTNONISOTRACKS7",           new EventVariableN("NPROMPTNONISOTRACKS7",           "promptNonIsoTracks7"));
  //
  handler->addEventVariable("NGOODTRACKS",            new EventVariableN("NGOODTRACKS",                                      "goodTracks"));
  handler->addEventVariable("QGOODTRACKS",            new EventVariableObjectVariableVector<int>("CHARGE",                   "goodTracks"));
  handler->addEventVariable("PTGOODTRACKS",           new EventVariableObjectVariableVector<double>("PT",                    "goodTracks"));
  handler->addEventVariable("ETAGOODTRACKS",          new EventVariableObjectVariableVector<double>("ETA",                   "goodTracks"));
  handler->addEventVariable("PHIGOODTRACKS",          new EventVariableObjectVariableVector<double>("PHI",                   "goodTracks"));
  handler->addEventVariable("RELISODBCORRGOODTRACKS", new EventVariableObjectVariableVector<double>("TRACK_RELISODBCORR",    "goodTracks"));// similar to relPFisoDBcorr Muon style
  handler->addEventVariable("RELISORHOCORRGOODTRACKS",new EventVariableObjectVariableVector<double>("TRACK_RELISORHOCORR",   "goodTracks"));// similar to relPFisoRHOcorr Electron style
  handler->addEventVariable("RELCHHADISOGOODTRACKS",  new EventVariableObjectVariableVector<double>("TRACK_RELCHHADISO",     "goodTracks"));// similar to relTrkiso Mu style, or part of relHCALiso Ele style
  handler->addEventVariable("RELNHADISOGOODTRACKS",   new EventVariableObjectVariableVector<double>("TRACK_RELNHADISO",      "goodTracks"));// similar to part of relHCALiso Ele style
  handler->addEventVariable("RELPHOTONISOGOODTRACKS", new EventVariableObjectVariableVector<double>("TRACK_RELPHOTONISO",    "goodTracks"));// similar to relECALiso Ele style
  handler->addEventVariable("RELBETAISOGOODTRACKS",   new EventVariableObjectVariableVector<double>("TRACK_RELBETAISO",      "goodTracks"));// added just to have relative PU isolation quantity.
  //
  handler->addEventVariable("NPROMPTTRACKS",            new EventVariableN("NPROMPTTRACKS",                                    "promptTracks"));
  handler->addEventVariable("QPROMPTTRACKS",            new EventVariableObjectVariableVector<int>("CHARGE",                   "promptTracks"));
  handler->addEventVariable("PTPROMPTTRACKS",           new EventVariableObjectVariableVector<double>("PT",                    "promptTracks"));
  handler->addEventVariable("ETAPROMPTTRACKS",          new EventVariableObjectVariableVector<double>("ETA",                   "promptTracks"));
  handler->addEventVariable("PHIPROMPTTRACKS",          new EventVariableObjectVariableVector<double>("PHI",                   "promptTracks"));
  handler->addEventVariable("RELISODBCORRPROMPTTRACKS", new EventVariableObjectVariableVector<double>("TRACK_RELISODBCORR",    "promptTracks"));// similar to relPFisoDBcorr Muon style
  handler->addEventVariable("RELISORHOCORRPROMPTTRACKS",new EventVariableObjectVariableVector<double>("TRACK_RELISORHOCORR",   "promptTracks"));// similar to relPFisoRHOcorr Electron style
  handler->addEventVariable("RELCHHADISOPROMPTTRACKS",  new EventVariableObjectVariableVector<double>("TRACK_RELCHHADISO",     "promptTracks"));// similar to relTrkiso Mu style, or part of relHCALiso Ele style
  handler->addEventVariable("RELNHADISOPROMPTTRACKS",   new EventVariableObjectVariableVector<double>("TRACK_RELNHADISO",      "promptTracks"));// similar to part of relHCALiso Ele style
  handler->addEventVariable("RELPHOTONISOPROMPTTRACKS", new EventVariableObjectVariableVector<double>("TRACK_RELPHOTONISO",    "promptTracks"));// similar to relECALiso Ele style
  handler->addEventVariable("RELBETAISOPROMPTTRACKS",   new EventVariableObjectVariableVector<double>("TRACK_RELBETAISO",      "promptTracks"));// added just to have relative PU isolation quantity.
  //
  handler->addEventVariable("NINCLUSIVETRACKS",       new EventVariableN("NINCLUSIVETRACKS",                  "inclusiveTracks"));
  handler->addEventVariable("PTINCLUSIVETRACKS",      new EventVariableObjectVariableVector<double>("PT",     "inclusiveTracks"));
  handler->addEventVariable("ETAINCLUSIVETRACKS",     new EventVariableObjectVariableVector<double>("ETA",    "inclusiveTracks"));
  handler->addEventVariable("MINIISOINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("MINIISO","inclusiveTracks"));
  handler->addEventVariable("RELISOINCLUSIVETRACKS",  new EventVariableObjectVariableVector<double>("RELISO", "inclusiveTracks"));
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
  EventVariableSumPT* LTLA = new EventVariableSumPT("LTLA","goodMuons");//sum over light leptons
  LTLA->addProduct("goodElectrons");
  handler->addEventVariable("LTLA",LTLA);
  //
  EventVariableSumPT* LTLA2 = new EventVariableSumPT("LTLA2","goodMuons",2);//sum over leading 2 light leptons only! (if present)
  LTLA2->addProduct("goodElectrons");
  handler->addEventVariable("LTLA2",LTLA2);
  //
  EventVariableSumPT* LTLA3 = new EventVariableSumPT("LTLA3","goodMuons",3);//sum over leading 3 light leptons only! (if present)
  LTLA3->addProduct("goodElectrons");
  handler->addEventVariable("LTLA3",LTLA3);
  //
  EventVariableSumPT* LTLA4 = new EventVariableSumPT("LTLA4","goodMuons",4);//sum over leading 4 light leptons only! (if present)
  LTLA4->addProduct("goodElectrons");
  handler->addEventVariable("LTLA4",LTLA4);
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
  //  
  //handler->addProduct("ALLTRIGGERS","ALL");
  //handler->addObjectVariable("isTrigger", new ObjectVariableValue<TString>("INPUTTYPE", "trigger"));
  //handler->addProductCut("TRIGGERS","isTrigger");
  //handler->addHistogram(new SignatureTH1F_TriggerName("TriggerNames","ALLTRIGGERS"));
  //
  //handler->addObjectVariable("Accepted", new ObjectVariableValue<bool>("ACCEPT", true));
  //handler->addObjectVariable("WasRun", new ObjectVariableValue<bool>("wasrun", true));

  // ------------------------------------------------------------------------
  // ------------------------------------------------------------------------
  // HLT bundles
  // These are supposed to include all paths for data and MC.
  // To be maintained! (Jun 3, 2016)
  // ------------------------------------------------------------------------
  // All available final HLT variables are listed here:
  //    -------------- All Muon
  //    IsoMuHLT
  //    MuHLTprescaled
  //    Mu45eta2p1HLT
  //    Mu50HLT
  //    IsoDiMuHLT
  //    DiMuHLT
  //    DiMuSSHLT
  //    TripleMuHLT
  //    -------------- All Electron
  //    IsoEleHLT
  //    EleHLT
  //    IsoDiEleHLT
  //    DiEleHLT
  //    TripleEleHLT
  //    -------------- Mixed
  //    IsoMu23Ele8HLTdata
  //    IsoMu23Ele12HLT
  //    IsoMu8Ele23HLT
  //    IsoMuEleHLTdata
  //    IsoMuEleHLT
  //    MuEleHLT
  //    MuEleHLTdata
  //    MuMuEleHLT
  //    MuEleEleHLT
  //    DiMuHTHLT
  //    DiEleHTHLT
  //    MuEleHTHLT
  //    -------------- Photon Triggers
  //    SinglePhotonHLT
  //    SinglePhotonMETHLT
  //    SinglePhotonHTHLT
  //    DiPhoton60HLT
  //    DiPhoton85HLT
  // ------------------------------------------------------------------------
  std::vector< vector<pair<string, string> > > RutgersHLT;
  // All-muon paths
  std::vector< pair<string, string> > IsoMuHLT;
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu22_v1"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu22_v2"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu22_v3"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu22_v4"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoMu22_v5"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu22_v1"));//these are ORed for higher eff, mentioned in the muon POG Twiki.
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu22_v2"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu22_v3"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu22_v4"));
  IsoMuHLT.push_back(std::make_pair("IsoMuHLT","HLT_IsoTkMu22_v5"));
  RutgersHLT.push_back(IsoMuHLT);
  std::vector< pair<string, string> > MuHLTprescaled;
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu17_v1"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu17_v2"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu17_v3"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu17_v4"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu17_v5"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu20_v1"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu20_v2"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu20_v3"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu20_v4"));
  MuHLTprescaled.push_back(std::make_pair("MuHLTprescaled","HLT_Mu20_v5"));
  RutgersHLT.push_back(MuHLTprescaled);
  std::vector< pair<string, string> > Mu45eta2p1HLT;
  Mu45eta2p1HLT.push_back(std::make_pair("Mu45eta2p1HLT","HLT_Mu45_eta2p1_v1"));
  Mu45eta2p1HLT.push_back(std::make_pair("Mu45eta2p1HLT","HLT_Mu45_eta2p1_v2"));
  Mu45eta2p1HLT.push_back(std::make_pair("Mu45eta2p1HLT","HLT_Mu45_eta2p1_v3"));
  Mu45eta2p1HLT.push_back(std::make_pair("Mu45eta2p1HLT","HLT_Mu45_eta2p1_v4"));
  Mu45eta2p1HLT.push_back(std::make_pair("Mu45eta2p1HLT","HLT_Mu45_eta2p1_v5"));
  RutgersHLT.push_back(Mu45eta2p1HLT);
  std::vector< pair<string, string> > Mu50HLT;
  Mu50HLT.push_back(std::make_pair("Mu50HLT","HLT_Mu50_v1"));
  Mu50HLT.push_back(std::make_pair("Mu50HLT","HLT_Mu50_v2"));
  Mu50HLT.push_back(std::make_pair("Mu50HLT","HLT_Mu50_v3"));
  Mu50HLT.push_back(std::make_pair("Mu50HLT","HLT_Mu50_v4"));
  Mu50HLT.push_back(std::make_pair("Mu50HLT","HLT_Mu50_v5"));
  RutgersHLT.push_back(Mu50HLT);
  std::vector< pair<string, string> > IsoDiMuHLT;//Analysis Trigger
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v1"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v5"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v1"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4"));
  IsoDiMuHLT.push_back(std::make_pair("IsoDiMuHLT","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v5"));
  RutgersHLT.push_back(IsoDiMuHLT);
  std::vector< pair<string, string> > DiMuHLT;
  DiMuHLT.push_back(std::make_pair("DiMuHLT","HLT_Mu30_TkMu11_v1"));
  DiMuHLT.push_back(std::make_pair("DiMuHLT","HLT_Mu30_TkMu11_v2"));
  DiMuHLT.push_back(std::make_pair("DiMuHLT","HLT_Mu30_TkMu11_v3"));
  DiMuHLT.push_back(std::make_pair("DiMuHLT","HLT_Mu30_TkMu11_v4"));
  DiMuHLT.push_back(std::make_pair("DiMuHLT","HLT_Mu30_TkMu11_v5"));
  RutgersHLT.push_back(DiMuHLT);
  std::vector< pair<string, string> > DiMuSSHLT;
  DiMuSSHLT.push_back(std::make_pair("DiMuSSHLT","HLT_Mu17_Mu8_SameSign_DZ_v1"));
  DiMuSSHLT.push_back(std::make_pair("DiMuSSHLT","HLT_Mu17_Mu8_SameSign_DZ_v2"));
  DiMuSSHLT.push_back(std::make_pair("DiMuSSHLT","HLT_Mu17_Mu8_SameSign_DZ_v3"));
  DiMuSSHLT.push_back(std::make_pair("DiMuSSHLT","HLT_Mu17_Mu8_SameSign_DZ_v4"));
  DiMuSSHLT.push_back(std::make_pair("DiMuSSHLT","HLT_Mu17_Mu8_SameSign_DZ_v5"));
  RutgersHLT.push_back(DiMuSSHLT);
  std::vector< pair<string, string> > TripleMuHLT;
  TripleMuHLT.push_back(std::make_pair("TripleMuHLT","HLT_TripleMu_12_10_5_v1"));
  TripleMuHLT.push_back(std::make_pair("TripleMuHLT","HLT_TripleMu_12_10_5_v2"));
  TripleMuHLT.push_back(std::make_pair("TripleMuHLT","HLT_TripleMu_12_10_5_v3"));
  TripleMuHLT.push_back(std::make_pair("TripleMuHLT","HLT_TripleMu_12_10_5_v4"));
  TripleMuHLT.push_back(std::make_pair("TripleMuHLT","HLT_TripleMu_12_10_5_v5"));
  RutgersHLT.push_back(TripleMuHLT);
  // ------------------------------------------------------------------------
  // All-electron paths
  std::vector< pair<string, string> > IsoEleHLT;
  IsoEleHLT.push_back(std::make_pair("IsoEleHLT","HLT_Ele27_eta2p1_WPLoose_Gsf_v1"));
  IsoEleHLT.push_back(std::make_pair("IsoEleHLT","HLT_Ele27_eta2p1_WPLoose_Gsf_v2"));
  IsoEleHLT.push_back(std::make_pair("IsoEleHLT","HLT_Ele27_eta2p1_WPLoose_Gsf_v3"));
  IsoEleHLT.push_back(std::make_pair("IsoEleHLT","HLT_Ele27_eta2p1_WPLoose_Gsf_v4"));
  IsoEleHLT.push_back(std::make_pair("IsoEleHLT","HLT_Ele27_eta2p1_WPLoose_Gsf_v5"));
  RutgersHLT.push_back(IsoEleHLT);
  std::vector< pair<string, string> > EleHLT;
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v1"));
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v2"));
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v3"));
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v4"));
  EleHLT.push_back(std::make_pair("EleHLT","HLT_Ele105_CaloIdVT_GsfTrkIdT_v5"));
  RutgersHLT.push_back(EleHLT);
  std::vector< pair<string, string> > EleHLTprescaled;
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v2"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v3"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v4"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v5"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele17_CaloIdL_GsfTrkIdVL_v1"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele17_CaloIdL_GsfTrkIdVL_v2"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele17_CaloIdL_GsfTrkIdVL_v3"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele17_CaloIdL_GsfTrkIdVL_v4"));
  EleHLTprescaled.push_back(std::make_pair("EleHLTprescaled","HLT_Ele17_CaloIdL_GsfTrkIdVL_v5"));
  RutgersHLT.push_back(EleHLTprescaled);
  std::vector< pair<string, string> > IsoDiEleHLT;//Analysis Trigger
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v1"));
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2"));
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3"));
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4"));
  IsoDiEleHLT.push_back(std::make_pair("IsoDiEleHLT","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5"));
  RutgersHLT.push_back(IsoDiEleHLT);
  std::vector< pair<string, string> > DiEleHLT;
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v1"));
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v2"));
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v3"));
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v4"));
  DiEleHLT.push_back(std::make_pair("DiEleHLT","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v5"));
  RutgersHLT.push_back(DiEleHLT);
  std::vector< pair<string, string> > TripleEleHLT;
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1"));
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v2"));
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v3"));
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v4"));
  TripleEleHLT.push_back(std::make_pair("TripleEleHLT","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v5"));
  RutgersHLT.push_back(TripleEleHLT);
  // ------------------------------------------------------------------------
  // Mixed multi-lepton paths
  std::vector< pair<string, string> > IsoMu23Ele8HLTdata;//Analysis Trigger - Data ONLY!
  IsoMu23Ele8HLTdata.push_back(std::make_pair("IsoMu23Ele8HLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMu23Ele8HLTdata.push_back(std::make_pair("IsoMu23Ele8HLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMu23Ele8HLTdata.push_back(std::make_pair("IsoMu23Ele8HLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMu23Ele8HLTdata.push_back(std::make_pair("IsoMu23Ele8HLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v4"));
  IsoMu23Ele8HLTdata.push_back(std::make_pair("IsoMu23Ele8HLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v5"));
  RutgersHLT.push_back(IsoMu23Ele8HLTdata);
  std::vector< pair<string, string> > IsoMu23Ele12HLT;//Analysis Trigger 
  IsoMu23Ele12HLT.push_back(std::make_pair("IsoMu23Ele12HLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMu23Ele12HLT.push_back(std::make_pair("IsoMu23Ele12HLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMu23Ele12HLT.push_back(std::make_pair("IsoMu23Ele12HLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMu23Ele12HLT.push_back(std::make_pair("IsoMu23Ele12HLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4"));
  IsoMu23Ele12HLT.push_back(std::make_pair("IsoMu23Ele12HLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v5"));
  RutgersHLT.push_back(IsoMu23Ele12HLT);
  std::vector< pair<string, string> > IsoMu8Ele23HLT;//Analysis Trigger
  IsoMu8Ele23HLT.push_back(std::make_pair("IsoMu8Ele23HLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMu8Ele23HLT.push_back(std::make_pair("IsoMu8Ele23HLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMu8Ele23HLT.push_back(std::make_pair("IsoMu8Ele23HLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMu8Ele23HLT.push_back(std::make_pair("IsoMu8Ele23HLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4"));
  IsoMu8Ele23HLT.push_back(std::make_pair("IsoMu8Ele23HLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v5"));
  RutgersHLT.push_back(IsoMu8Ele23HLT);
  std::vector< pair<string, string> > IsoMuEleHLTdata;//Analysis Trigger - Data ONLY!
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v5"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v4"));
  IsoMuEleHLTdata.push_back(std::make_pair("IsoMuEleHLTdata","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v5"));
  RutgersHLT.push_back(IsoMuEleHLTdata);
  std::vector< pair<string, string> > IsoMuEleHLT;//Analysis Trigger
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v4"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v5"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v3"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v4"));
  IsoMuEleHLT.push_back(std::make_pair("IsoMuEleHLT","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v5"));
  RutgersHLT.push_back(IsoMuEleHLT);
  std::vector< pair<string, string> > MuEleHLT;
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v1"));
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v2"));
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v3"));
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v4"));
  MuEleHLT.push_back(std::make_pair("MuEleHLT","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v5"));
  RutgersHLT.push_back(MuEleHLT);
  std::vector< pair<string, string> > MuEleHLTdata;// Data ONLY!
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v1"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v2"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v3"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v4"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v5"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v1"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v2"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v3"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v4"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu27_Ele37_CaloIdL_GsfTrkIdVL_v5"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v1"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v2"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v3"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v4"));
  MuEleHLTdata.push_back(std::make_pair("MuEleHLTdata","HLT_Mu37_Ele27_CaloIdL_GsfTrkIdVL_v5"));
  RutgersHLT.push_back(MuEleHLTdata);
  std::vector< pair<string, string> > MuMuEleHLT;
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1"));
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v2"));
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v3"));
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v4"));
  MuMuEleHLT.push_back(std::make_pair("MuMuEleHLT","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v5"));
  RutgersHLT.push_back(MuMuEleHLT);
  std::vector< pair<string, string> > MuEleEleHLT;
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1"));
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v2"));
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v3"));
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v4"));
  MuEleEleHLT.push_back(std::make_pair("MuEleEleHLT","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v5"));
  RutgersHLT.push_back(MuEleEleHLT);
  // ------------------------------------------------------------------------
  // Di-lepton + PFHT paths
  std::vector< pair<string, string> > DiMuHTHLT;
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v1"));
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v2"));
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v3"));
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v4"));
  DiMuHTHLT.push_back(std::make_pair("DiMuHTHLT","HLT_DoubleMu8_Mass8_PFHT300_v5"));
  RutgersHLT.push_back(DiMuHTHLT);
  std::vector< pair<string, string> > DiEleHTHLT;
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v2"));
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v3"));
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v4"));
  DiEleHTHLT.push_back(std::make_pair("DiEleHTHLT","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v5"));
  RutgersHLT.push_back(DiEleHTHLT);
  std::vector< pair<string, string> > MuEleHTHLT;
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2"));
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v3"));
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v4"));
  MuEleHTHLT.push_back(std::make_pair("MuEleHTHLT","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v5"));
  RutgersHLT.push_back(MuEleHTHLT);
  // ------------------------------------------------------------------------
  // Single and double photon paths
  std::vector< pair<string, string> > SinglePhotonHLT;
  SinglePhotonHLT.push_back(std::make_pair("SinglePhotonHLT","HLT_Photon175_v1"));
  SinglePhotonHLT.push_back(std::make_pair("SinglePhotonHLT","HLT_Photon175_v2"));
  SinglePhotonHLT.push_back(std::make_pair("SinglePhotonHLT","HLT_Photon175_v3"));
  SinglePhotonHLT.push_back(std::make_pair("SinglePhotonHLT","HLT_Photon175_v4"));
  SinglePhotonHLT.push_back(std::make_pair("SinglePhotonHLT","HLT_Photon175_v5"));
  RutgersHLT.push_back(SinglePhotonHLT);
  std::vector< pair<string, string> > SinglePhotonMETHLT;
  SinglePhotonMETHLT.push_back(std::make_pair("SinglePhotonMETHLT","HLT_Photon135_PFMET100_v1"));
  SinglePhotonMETHLT.push_back(std::make_pair("SinglePhotonMETHLT","HLT_Photon135_PFMET100_v2"));
  SinglePhotonMETHLT.push_back(std::make_pair("SinglePhotonMETHLT","HLT_Photon135_PFMET100_v3"));
  SinglePhotonMETHLT.push_back(std::make_pair("SinglePhotonMETHLT","HLT_Photon135_PFMET100_v4"));
  SinglePhotonMETHLT.push_back(std::make_pair("SinglePhotonMETHLT","HLT_Photon135_PFMET100_v5"));
  RutgersHLT.push_back(SinglePhotonMETHLT);
  std::vector< pair<string, string> > SinglePhotonHTHLT;
  SinglePhotonHTHLT.push_back(std::make_pair("SinglePhotonHTHLT","HLT_Photon90_CaloIdL_PFHT500_v1"));
  SinglePhotonHTHLT.push_back(std::make_pair("SinglePhotonHTHLT","HLT_Photon90_CaloIdL_PFHT500_v2"));
  SinglePhotonHTHLT.push_back(std::make_pair("SinglePhotonHTHLT","HLT_Photon90_CaloIdL_PFHT500_v3"));
  SinglePhotonHTHLT.push_back(std::make_pair("SinglePhotonHTHLT","HLT_Photon90_CaloIdL_PFHT500_v4"));
  SinglePhotonHTHLT.push_back(std::make_pair("SinglePhotonHTHLT","HLT_Photon90_CaloIdL_PFHT500_v5"));
  RutgersHLT.push_back(SinglePhotonHTHLT);
  std::vector< pair<string, string> > DiPhoton60HLT;
  DiPhoton60HLT.push_back(std::make_pair("DiPhoton60HLT","HLT_DoublePhoton60_v1"));
  DiPhoton60HLT.push_back(std::make_pair("DiPhoton60HLT","HLT_DoublePhoton60_v2"));
  DiPhoton60HLT.push_back(std::make_pair("DiPhoton60HLT","HLT_DoublePhoton60_v3"));
  DiPhoton60HLT.push_back(std::make_pair("DiPhoton60HLT","HLT_DoublePhoton60_v4"));
  DiPhoton60HLT.push_back(std::make_pair("DiPhoton60HLT","HLT_DoublePhoton60_v5"));
  RutgersHLT.push_back(DiPhoton60HLT);
  std::vector< pair<string, string> > DiPhoton85HLT;
  DiPhoton85HLT.push_back(std::make_pair("DiPhoton85HLT","HLT_DoublePhoton85_v1"));
  DiPhoton85HLT.push_back(std::make_pair("DiPhoton85HLT","HLT_DoublePhoton85_v2"));
  DiPhoton85HLT.push_back(std::make_pair("DiPhoton85HLT","HLT_DoublePhoton85_v3"));
  DiPhoton85HLT.push_back(std::make_pair("DiPhoton85HLT","HLT_DoublePhoton85_v4"));
  DiPhoton85HLT.push_back(std::make_pair("DiPhoton85HLT","HLT_DoublePhoton85_v5"));
  RutgersHLT.push_back(DiPhoton85HLT);
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
      TString   HLTpathName = HLTgroup.at(j).second;
      isHLTgroup->addValue(HLTpathName);
      // ---------------------------------------------
      // Storing all individual HLT paths here (as specified above):
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
      handler->addEventVariable(acceptnamepath,new EventVariableInRange<int>(nnamepath,1,100000));//...........................ACCEPT true/false
      handler->addEventVariable(TString::Format("REJECT_%s",HLTpathName.Data()),new EventVariableReversed(acceptnamepath));//..REJECT true/false
      // ---------------------------------------------
    }
    //
    handler->addObjectVariable(isHLTgroupName,isHLTgroup);
    handler->addProductCut(HLTgroupName,isHLTgroupName);
    TString nname = TString::Format("N%s",HLTgroupName.Data());
    handler->addEventVariable(nname,new EventVariableN(nname,HLTgroupName));// count
    TString acceptname = TString::Format("ACCEPT_%s",HLTgroupName.Data());
    handler->addEventVariable(acceptname,new EventVariableInRange<int>(nname,1,100000));//................................ACCEPT true/false
    handler->addEventVariable(TString::Format("REJECT_%s",HLTgroupName.Data()),new EventVariableReversed(acceptname));//..REJECT true/false
    //
  }
  // ------------------------------------------------------------------------
  // ------------------------------------------------------------------------  

  //std::vector< vector<pair<string, string> > > RutgersTrigObjects;
  std::vector<string>  RutgersTrigObjects;
  RutgersTrigObjects.push_back("HLT_IsoMu22_v");
  RutgersTrigObjects.push_back("HLT_IsoTkMu22_v");
  RutgersTrigObjects.push_back("HLT_Mu45_eta2p1_v");
  RutgersTrigObjects.push_back("HLT_Mu50_v");
  RutgersTrigObjects.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  RutgersTrigObjects.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
  RutgersTrigObjects.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
  RutgersTrigObjects.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
  RutgersTrigObjects.push_back("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  RutgersTrigObjects.push_back("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
  RutgersTrigObjects.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  RutgersTrigObjects.push_back("HLT_Mu20_v");//............prescaled control trigger & trig-obj.
  RutgersTrigObjects.push_back("HLT_TkMu20_v");//..........prescaled control trigger & trig-obj.
  RutgersTrigObjects.push_back("HLT_Mu17_TrkIsoVVL_v");//..prescaled control trigger & trig-obj.
  RutgersTrigObjects.push_back("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23");//......HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v
  RutgersTrigObjects.push_back("hltMu23TrkIsoVVLEle12CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter");//...HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v
  RutgersTrigObjects.push_back("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered23");//.......HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v
  RutgersTrigObjects.push_back("hltMu23TrkIsoVVLEle8CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter");//....HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v
  RutgersTrigObjects.push_back("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8");//........HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v
  RutgersTrigObjects.push_back("hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLElectronlegTrackIsoFilter");//....HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v
  RutgersTrigObjects.push_back("hltDiMu9Ele9CaloIdLTrackIdLMuonlegL3Filtered9");//........................HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v
  RutgersTrigObjects.push_back("hltDiMu9Ele9CaloIdLTrackIdLElectronlegDphiFilter");//.....................HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v
  RutgersTrigObjects.push_back("hltL3fL1sMu22orMu25orMu20EG15orMu5EG20L1f0L2f10QL3Filtered30Q");//........HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v
  RutgersTrigObjects.push_back("hltEle30CaloIdLGsfTrkIdVLDPhiUnseededFilter");//..........................HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v
  RutgersTrigObjects.push_back("hltMu8DiEle12CaloIdLTrackIdLMuonlegL3Filtered8");//.......................HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v
  RutgersTrigObjects.push_back("hltMu8DiEle12CaloIdLTrackIdLElectronlegDphiFilter");//....................HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v

  // Store all *individual* HLT trigger objects as specified above and in BaseAODReader/python/miniAOD_cfi.py
  for(unsigned int i=0; i<RutgersTrigObjects.size(); i++){
    TString   trigObjName = RutgersTrigObjects.at(i);
    //TString isTrigObjName = TString::Format("is%s",trigObjName.Data());
    //
    handler->addProduct(trigObjName,"goodtriggerobjects");
    handler->addEventVariable(TString::Format("N%s",trigObjName.Data()),          new EventVariableN(TString::Format("N%s",trigObjName.Data()),  trigObjName));
    handler->addEventVariable(TString::Format("PT%s",trigObjName.Data()),         new EventVariableObjectVariableVector<double>("PT",            trigObjName));
    handler->addEventVariable(TString::Format("ETA%s",trigObjName.Data()),        new EventVariableObjectVariableVector<double>("ETA",           trigObjName));
    handler->addEventVariable(TString::Format("PHI%s",trigObjName.Data()),        new EventVariableObjectVariableVector<double>("PHI",           trigObjName));
  }


  // Offline Trigger Tresholds 
  //Offline tresholds for higher trigger efficiencies
  // Single Electron
  EventVariableThreshold* singElTrig = new EventVariableThreshold("singeltrig","goodElectrons");
  singElTrig->addThreshold(27);
  handler->addEventVariable("SINGELTRIGTHRESHOLD",singElTrig);

  // Single Muon
  EventVariableThreshold* singMuTrig = new EventVariableThreshold("singmutrig","goodMuons");
  singMuTrig->addThreshold(22);
  handler->addEventVariable("SINGMUTRIGTHRESHOLD",singMuTrig);

  // Di-Electron treshold
  EventVariableThreshold* dieltrig = new EventVariableThreshold("dieltrig","goodElectrons");
  dieltrig->addThreshold(23);
  dieltrig->addThreshold(12);
  handler->addEventVariable("DIELTRIGTHRESHOLD",dieltrig);

  // Di-Muon treshold
  EventVariableThreshold* dimutrig = new EventVariableThreshold("dimutrig","goodMuons");
  dimutrig->addThreshold(17);
  dimutrig->addThreshold(8);
  handler->addEventVariable("DIMUTRIGTHRESHOLD",dimutrig);

  // Mu-Ele treshold
  // Leading Electron - Subleading Muon : (23, 8)
  EventVariableThreshold* ellead = new EventVariableThreshold("ellead","goodElectrons");//........leading ele cut
  ellead->addThreshold(23);
  handler->addEventVariable("EGMULEADTHRESHOLD",ellead);
  EventVariableThreshold* musublead = new EventVariableThreshold("musublead","goodMuons");//......subleading mu cut
  musublead->addThreshold(8);
  handler->addEventVariable("EGMUSUBLEADTHRESHOLD",musublead);
  handler->addEventVariable("EGMUTHRESHOLD",new EventVariableCombined("EGMULEADTHRESHOLD","EGMUSUBLEADTHRESHOLD",true));
  //
  // Leading Muon - Subleading Electron : (23, 8)
  EventVariableThreshold* mulead = new EventVariableThreshold("mulead","goodMuons");//............leading mu cut
  mulead->addThreshold(23);
  handler->addEventVariable("MUEGLEADTHRESHOLD",mulead);
  EventVariableThreshold* elsublead = new EventVariableThreshold("elsublead","goodElectrons");//..subleading ele cut
  elsublead->addThreshold(8);
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
    trigaccept = new EventVariableCombined("ACCEPT_IsoEleHLT","REJECT_IsoDiEleHLT",true);
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
  // first lets do these gen-reco match checks for goodLeptons:
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
  //RecoGenTaus->addProduct("MCTAUSFROMBOSON");
  RecoGenTaus->addProduct("MCHADRONICTAUSFROMBOSON");
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
  // ------------------------------------------------------------------------------------------------------------------------
  // ------------------------------------------------------------------------------------------------------------------------
  // then do these gen-reco match checks for basicLeptons:
  EventVariableLeptonGenChecker* BasicRecoGenMuons = new EventVariableLeptonGenChecker("BasicRecoGenMuons","basicMuons","");//3rd suffix
  RecoGenMuons->addProduct("MCMUONSFROMBOSON");
  RecoGenMuons->addProduct("BOSONS");//used for debugging.
  handler->addEventVariable("BASICRECOGENMUONS",BasicRecoGenMuons);
  handler->addEventVariable("ISPROMPTBASICMUON",new EventVariableObjectVariableVector<int>("IsGenMatched","basicMuons"));
  // ------------------------------------------------------------------------------------------------------------------------
  EventVariableLeptonGenChecker* BasicRecoGenElectrons = new EventVariableLeptonGenChecker("BasicRecoGenElectrons","basicElectrons","");//3rd suffix
  RecoGenElectrons->addProduct("MCELECTRONSFROMBOSON");
  RecoGenElectrons->addProduct("BOSONS");//used for debugging.
  handler->addEventVariable("BASICRECOGENELECTRONS",BasicRecoGenElectrons);
  handler->addEventVariable("ISPROMPTBASICELECTRON",new EventVariableObjectVariableVector<int>("IsGenMatched","basicElectrons"));
  // ------------------------------------------------------------------------------------------------------------------------
  EventVariableLeptonGenChecker* BasicRecoGenTaus = new EventVariableLeptonGenChecker("BasicRecoGenTaus","basicTaus","");//3rd suffix
  RecoGenTaus->addProduct("MCHADRONICTAUSFROMBOSON");
  RecoGenTaus->addProduct("BOSONS");//used for debugging.
  handler->addEventVariable("BASICRECOGENTAUS",BasicRecoGenTaus);
  handler->addEventVariable("ISPROMPTBASICTAU",new EventVariableObjectVariableVector<int>("IsGenMatched","basicTaus"));//WARNING!
  // WARNING: NEED TO CHECK "ISPROMPTTAU" FOR ELE/MU->TAU FAKES! - SEE BELOW.
  // ------------------------------------------------------------------------------------------------------------------------
  // Gen Ele -> Reco Tau (checks for tau fakes)
  EventVariableLeptonGenChecker* BasicRecoTauGenEles = new EventVariableLeptonGenChecker("BasicRecoTauGenEles","basicTaus","EleFake");//3rd suffix
  //RecoTauGenEles->addProduct("MCELECTRONS");
  RecoTauGenEles->addProduct("MCELECTRONSFROMBOSON");
  handler->addEventVariable("BASICRECOTAUGENELES",BasicRecoTauGenEles);
  handler->addEventVariable("ISFAKEBASICTAUFROMELE",new EventVariableObjectVariableVector<int>("IsGenMatchedEleFake","basicTaus"));
  // ------------------------------------------------------------------------------------------------------------------------
  // Gen Muon -> Reco Tau (checks for tau fakes)
  EventVariableLeptonGenChecker* BasicRecoTauGenMus = new EventVariableLeptonGenChecker("BasicRecoTauGenMus","basicTaus","MuFake");//3rd suffix
  //RecoTauGenMus->addProduct("MCMUONS");
  RecoTauGenMus->addProduct("MCMUONSFROMBOSON");
  handler->addEventVariable("BASICRECOTAUGENMUS",BasicRecoTauGenMus);
  handler->addEventVariable("ISFAKEBASICTAUFROMMU",new EventVariableObjectVariableVector<int>("IsGenMatchedMuFake","basicTaus"));
  //
  // Matrix Method Disclaimer:
  //   Events with all prompt electrons, muons, and taus (as tagged by ISPROMPT flags) are taken from MC in the MM.
  //   Fake taus as used in the MM mainly include "jet->tau" fakes.
  //   Fake taus from light-leptons (ele/mu->tau fakes) are generally isolated, so should not be estimated via the MM.
  //   The "ele/mu->tau fakes" should also be taken from MC
  //
  
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
