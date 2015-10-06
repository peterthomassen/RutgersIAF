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

namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFEventAnalyzer.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void setupProducts(BaseHandler* handler)
{
  handler->addObjectVariable("isPhoton",new ObjectVariableValue<TString>("INPUTTYPE","photon"));
  handler->addObjectVariable("isVertex",new ObjectVariableValue<TString>("INPUTTYPE","vertex"));
  handler->addObjectVariable("isMET", new ObjectVariableValue<TString>("INPUTTYPE","met"));
  handler->addObjectVariable("uncertaintyNoShift", new ObjectVariableValue<TString>("uncertainty","NoShift"));
  handler->addObjectVariable("levelType1", new ObjectVariableValue<TString>("level","Type1"));

  handler->addProduct("ALLMUONS","ALL");
  handler->addProductCut("ALLMUONS","isMuon");

  handler->addProduct("ALLELECTRONS","ALL");
  handler->addProductCut("ALLELECTRONS","isElectron");

  handler->addProduct("ALLTAUS","ALL");
  handler->addProductCut("ALLTAUS","isTau");

  handler->addProduct("ALLPHOTONS","ALL");
  handler->addProductCut("ALLPHOTONS","isPhoton");

  handler->addProduct("ALLTRACKS","ALL");
  handler->addProductCut("ALLTRACKS","isTrack");

  handler->addProduct("ALLJETS","ALL");
  handler->addProductCut("ALLJETS","isJet");

  handler->addProduct("ALLVERTICES","ALL");
  handler->addProductCut("ALLVERTICES","isVertex");
  handler->addProduct("ALLRECOVERTICES","ALLVERTICES");

  handler->addProduct("ALLMET","ALL");
  handler->addProductCut("ALLMET","isMET");

  handler->addProduct("MET","ALLMET");
  handler->addProductCut("MET", "uncertaintyNoShift");
  handler->addProductCut("MET", "levelType1");


  ///Some variables///

  handler->addObjectVariable("ETA",new ObjectVariableMethod("ETA", &SignatureObject::Eta));
  handler->addObjectVariable("ETA2p3",new ObjectVariableInRange<double>("ETA",-2.3,2.3,"ETA2p3"));
  handler->addObjectVariable("ETA2p4",new ObjectVariableInRange<double>("ETA",-2.4,2.4));
  handler->addObjectVariable("ETA2p5",new ObjectVariableInRange<double>("ETA",-2.5,2.5,"ETA2p5"));
  handler->addObjectVariable("ETA0p8",new ObjectVariableInRange<double>("ETA",-0.8,0.8,"ETA0p8"));
  handler->addObjectVariable("ETA4p7",new ObjectVariableInRange<double>("ETA",-4.7,4.7,"ETA4p7"));
  handler->addObjectVariable("ETA1p479",new ObjectVariableInRange<double>("ETA",-1.479,1.479,"ETA1p479"));
  handler->addObjectVariable("NOTETA0p8", new ObjectVariableReversed("ETA0p8"));
  handler->addObjectVariable("NOTETA2p4", new ObjectVariableReversed("ETA2p4"));
  handler->addObjectVariable("ETA0p8to1p479", new ObjectVariableCombined("NOTETA0p8","ETA1p479",true,"ETA0p8to1p479"));
  handler->addObjectVariable("ETA2p4to4p7", new ObjectVariableCombined("NOTETA2p4", "ETA4p7", true, "ETA2p4to4p7"));
  handler->addObjectVariable("BARREL",new ObjectVariableInRange<double>("ETA",-1.479,1.479,"barrelEta"));
  handler->addObjectVariable("ENDCAP",new ObjectVariableReversed("BARREL","endcapEta"));
  handler->addObjectVariable("POSITIVE",new ObjectVariableInRange<int>("charge",0,10,"CHARGEPOS"));
  handler->addObjectVariable("NEGATIVE",new ObjectVariableInRange<int>("charge",-10,0,"CHARGENEG"));
  handler->addObjectVariable("PT6",new ObjectVariableInRange<double>("PT",6.0,10000.0,"PT6"));
  handler->addObjectVariable("PT7",new ObjectVariableInRange<double>("PT",7.0,10000.0,"PT7"));
  handler->addObjectVariable("PT20",new ObjectVariableInRange<double>("PT",20.0,10000.0,"PT20"));
  handler->addObjectVariable("PT30",new ObjectVariableInRange<double>("PT",30.0,10000.0,"PT30"));
  handler->addObjectVariable("PT40",new ObjectVariableInRange<double>("PT",40.0,100000.0));
  handler->addObjectVariable("CHARGE",new ObjectVariableRename<int>("charge","CHARGE"));
  handler->addObjectVariable("genDxy", new ObjectVariableGenVertexR("genDxy"));

  handler->addObjectVariable("SIP3D_4sigma", new ObjectVariableInRange<double>("sigPV3D",-4,4));

  ////////////////////
  ///Muon Variables///
  ////////////////////

  handler->addObjectVariable("MUON_normalizedChi2",new ObjectVariableInRange<double>("normalizedChi2",0,3));
  handler->addObjectVariable("MUON_dxy", new ObjectVariableInRange<double>("dxy",-0.05,0.05));
  handler->addObjectVariable("MUON_nonprompt", new ObjectVariableReversed("MUON_dxy","MUON_nonprompt"));
  handler->addObjectVariable("MUON_dz", new ObjectVariableInRange<double>("dz",-0.1,0.1));
  handler->addObjectVariable("MUON_chi2LocalPosition", new ObjectVariableInRange<double>("chi2LocalPosition",0,12));
  handler->addObjectVariable("MUON_trkKink", new ObjectVariableInRange<double>("trkKink",0,20));

  handler->addObjectVariable("MUON_GLOBALORTRACKER", new ObjectVariableCombined("isTrackerMuon","isGlobalMuon",false));

  ObjectVariableCombined* muon_goodGlobal = new ObjectVariableCombined("isGlobalMuon","MUON_normalizedChi2",true);
  muon_goodGlobal->addVariable("MUON_chi2LocalPosition");
  muon_goodGlobal->addVariable("MUON_trkKink");
  handler->addObjectVariable("MUON_GOODGLOBAL",muon_goodGlobal);

  handler->addObjectVariable("MUON_SEGCOM0p303",new ObjectVariableInRange<double>("segmentCompatibility",0.303,1000000));
  handler->addObjectVariable("MUON_SEGCOM0p451",new ObjectVariableInRange<double>("segmentCompatibility",0.451,1000000));

  ObjectVariableCombined* muon_goodGlobalSeg = new ObjectVariableCombined("MUON_GOODGLOBAL","MUON_SEGCOM0p303",true);
  handler->addObjectVariable("MUON_GOODGLOBALSEGCOM",muon_goodGlobalSeg);
  handler->addObjectVariable("MUON_GOODSEGCOM",new ObjectVariableCombined("MUON_GOODGLOBALSEGCOM","MUON_SEGCOM0p451",false));
  handler->addObjectVariable("MUON_validFraction", new ObjectVariableInRange<double>("validFraction",0.8,10000));

  ////////////////////////
  ///Electron Variables///
  ////////////////////////
  handler->addObjectVariable("ELECTRON_INGAPPOS",new ObjectVariableInRange<double>("superClustereta",1.4442,1.566));
  handler->addObjectVariable("ELECTRON_INGAPNEG",new ObjectVariableInRange<double>("superClustereta",-1.566,-1.4442));
  ObjectVariableCombined* electron_ingap = new ObjectVariableCombined("ELECTRON_INGAPPOS","ELECTRON_INGAPNEG",false,"ELECTRON_INGAP");
  handler->addObjectVariable("ELECTRON_INGAP",electron_ingap);
  handler->addObjectVariable("ELECTRON_NOTGAP",new ObjectVariableReversed("ELECTRON_INGAP","ELECTRON_NOTGAP"));
  handler->addObjectVariable("ELECTRON_MISSINGHITS", new ObjectVariableValue<int>("numberOfLostHits",0));
  handler->addObjectVariable("ELECTRON_passConversionVeto",new ObjectVariableValue<bool>("passConversionVeto",true));
  handler->addObjectVariable("ELECTRON_dz", new ObjectVariableInRange<double>("dz",-0.1,0.1));
  handler->addObjectVariable("ELECTRON_dxy", new ObjectVariableInRange<double>("dxy",-0.05,0.05));
  handler->addObjectVariable("ELECTRON_dz5", new ObjectVariableInRange<double>("dz",-5.0,5.0));
  handler->addObjectVariable("ELECTRON_PROMPT", new ObjectVariableRename<bool>("ELECTRON_dxy", "ELECTRON_PROMPT"));
  handler->addObjectVariable("ELECTRON_NONPROMPT",new ObjectVariableReversed("ELECTRON_PROMPT"));

  /////////////////////
  ///Track variables///
  /////////////////////
  handler->addObjectVariable("TRACK_PFCHARGEDHADRONISO", new ObjectVariableRename<double>("chargedHadronIsoFromPF","PF_CHARGEDHADRONISO"),false);
  handler->addObjectVariable("TRACK_PFNEUTRALHADRONISO", new ObjectVariableRename<double>("neutralHadronIsoFromPF","PF_NEUTRALHADRONISO"),false);
  handler->addObjectVariable("TRACK_PFPHOTONISO", new ObjectVariableRename<double>("neutralPhotonIsoFromPF","PF_PHOTONISO"),false);
  handler->addObjectVariable("TRACK_BETA", new ObjectVariableRename<double>("betaIsoFromPF","BETA"),false);
  handler->addObjectVariable("TRACK_fromPV", new ObjectVariableInRange<int>("fromPV",2,100000));


  /////////////////
  ////Variables////
  /////////////////  
  ObjectVariableEffectiveArea* areaEl = new ObjectVariableEffectiveArea("ELECTRON_AREA");
  areaEl->addArea(0.8,0.1013);
  areaEl->addArea(1.3,0.0988);
  areaEl->addArea(2.0,0.0572);
  areaEl->addArea(2.2,0.0842);
  areaEl->addArea(2.5,0.1530);
  handler->addObjectVariable("ELECTRON_AREA", areaEl);

  ObjectVariableEffectiveAreaMiniIsolation* areaElmi = new ObjectVariableEffectiveAreaMiniIsolation("miniIsoCone",0.3,2,"ELECTRON_AREA_MINIISO");
  areaElmi->addArea(0.8,0.1013);
  areaElmi->addArea(1.3,0.0988);
  areaElmi->addArea(2.0,0.0572);
  areaElmi->addArea(2.2,0.0842);
  areaElmi->addArea(2.5,0.1530);
  handler->addObjectVariable("ELECTRON_AREA_MINIISO", areaElmi);

  ObjectVariableEffectiveArea* areaMu = new ObjectVariableEffectiveArea("MUON_AREA");
  areaMu->addArea(0.8,0.0913);
  areaMu->addArea(1.3,0.0765);
  areaMu->addArea(2.0,0.0546);
  areaMu->addArea(2.2,0.0728);
  areaMu->addArea(2.5,0.1177);
  handler->addObjectVariable("MUON_AREA", areaMu);

  ObjectVariableEffectiveAreaMiniIsolation* areaMumi = new ObjectVariableEffectiveAreaMiniIsolation("miniIsoCone",0.3,2,"MUON_AREA_MINIISO");
  areaMumi->addArea(0.8,0.0913);
  areaMumi->addArea(1.3,0.0765);
  areaMumi->addArea(2.0,0.0546);
  areaMumi->addArea(2.2,0.0728);
  areaMumi->addArea(2.5,0.1177);
  handler->addObjectVariable("MUON_AREA_MINIISO", areaMumi);

  handler->addObjectVariable("RHO", new ObjectVariableEventVariable<double>("rhoAll",handler));
  handler->addObjectVariable("ELECTRON_totalIso", new ObjectVariableRhoCorrectedTotalIso("sumChargedHadronPt","sumNeutralHadronEt","sumPhotonEt","RHO","ELECTRON_AREA","TOTALISO"),false);
  handler->addObjectVariable("MUON_totalIso", new ObjectVariableRhoCorrectedTotalIso("pfIsolationR03sumChargedHadronPt","pfIsolationR03sumNeutralHadronEt","pfIsolationR03sumPhotonEt","RHO","MUON_AREA","TOTALISO"),false);
  handler->addObjectVariable("TRACK_totalIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronIsoFromPF","neutralHadronIsoFromPF","neutralPhotonIsoFromPF","RHO","MUON_AREA","TOTALISO","isTrack"),false);
  handler->addObjectVariable("ELECTRON_totalMiniIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronMiniIso","neutralHadronMiniIso","photonMiniIso","RHO","ELECTRON_AREA_MINIISO","TOTALMINIISO","isElectron"),false);
  handler->addObjectVariable("MUON_totalMiniIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronMiniIso","neutralHadronMiniIso","photonMiniIso","RHO","MUON_AREA_MINIISO","TOTALMINIISO","isMuon"),false);
  handler->addObjectVariable("TRACK_totalMiniIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronMiniIso","neutralHadronMiniIso","photonMiniIso","RHO","MUON_AREA_MINIISO","TOTALMINIISO","isTrack"),false);
  handler->addObjectVariable("TAU_totalMiniIso", new ObjectVariableDeltaBetaCorrectedTotalIso("chargedHadronMiniIso","","photonMiniIso","puCorrPtSum","TOTALMINIISO","isTau"),false);
  handler->addObjectVariable("RELISO",new ObjectVariableRelIso("RELISO"));
  handler->addObjectVariable("MINIISO",new ObjectVariableRelIso("MINIISO","TOTALMINIISO"));
  handler->addObjectVariable("MINIISO0p40", new ObjectVariableInRange<double>("MINIISO",0,0.4));
  handler->addObjectVariable("MINIISO0p22", new ObjectVariableInRange<double>("MINIISO",0,0.22));
  handler->addObjectVariable("MINIISO0p14", new ObjectVariableInRange<double>("MINIISO",0,0.14));
  handler->addObjectVariable("MINIISO0p10", new ObjectVariableInRange<double>("MINIISO",0,0.1));
  handler->addObjectVariable("MINIISO0p075", new ObjectVariableInRange<double>("MINIISO",0,0.075));
  handler->addObjectVariable("MINIISO0p05", new ObjectVariableInRange<double>("MINIISO",0,0.05));
  handler->addObjectVariable("PTRATIO0p63",new ObjectVariableInRange<double>("ptRatio",0.63,1e6));
  handler->addObjectVariable("PTRATIO0p68",new ObjectVariableInRange<double>("ptRatio",0.68,1e6));
  handler->addObjectVariable("PTRATIO0p70",new ObjectVariableInRange<double>("ptRatio",0.70,1e6));
  handler->addObjectVariable("PTRATIO0p725",new ObjectVariableInRange<double>("ptRatio",0.725,1e6));
  handler->addObjectVariable("PTREL6",new ObjectVariableInRange<double>("ptRel",6,1e6));
  handler->addObjectVariable("PTREL6p7",new ObjectVariableInRange<double>("ptRel",6.7,1e6));
  handler->addObjectVariable("PTREL7",new ObjectVariableInRange<double>("ptRel",7,1e6));
  handler->addObjectVariable("PTREL8",new ObjectVariableInRange<double>("ptRel",8,1e6));

  handler->addObjectVariable("MULTIISOJETL",new ObjectVariableCombined("PTRATIO0p63","PTREL6",false));
  handler->addObjectVariable("MULTIISOJETM",new ObjectVariableCombined("PTRATIO0p68","PTREL6p7",false));
  handler->addObjectVariable("MULTIISOJETT",new ObjectVariableCombined("PTRATIO0p70","PTREL7",false));
  handler->addObjectVariable("MULTIISOJETVT",new ObjectVariableCombined("PTRATIO0p725","PTREL7",false));
  handler->addObjectVariable("MULTIISOJETHT",new ObjectVariableCombined("PTRATIO0p725","PTREL8",false));

  handler->addObjectVariable("MULTIISOL",new ObjectVariableCombined("MINIISO0p22","MULTIISOJETL",true));
  handler->addObjectVariable("MULTIISOM",new ObjectVariableCombined("MINIISO0p14","MULTIISOJETM",true));
  handler->addObjectVariable("MULTIISOT",new ObjectVariableCombined("MINIISO0p10","MULTIISOJETT",true));
  handler->addObjectVariable("MULTIISOVT",new ObjectVariableCombined("MINIISO0p075","MULTIISOJETVT",true));
  handler->addObjectVariable("MULTIISOHT",new ObjectVariableCombined("MINIISO0p05","MULTIISOJETHT",true));

  handler->addObjectVariable("IREL0p15",new ObjectVariableInRange<double>("RELISO",0,0.15,"IREL0p15"));
  handler->addObjectVariable("NOTIREL0p15", new ObjectVariableReversed("IREL0p15"));
  handler->addObjectVariable("IREL0p23",new ObjectVariableInRange<double>("RELISO",0,0.23,"IREL0p23"));
  handler->addObjectVariable("IREL0p24",new ObjectVariableInRange<double>("RELISO",0,0.24,"IREL0p24"));
  handler->addObjectVariable("NOTIREL0p24", new ObjectVariableReversed("IREL0p24"));
  handler->addObjectVariable("IREL0p25",new ObjectVariableInRange<double>("RELISO",0,0.25,"IREL0p25"));
  handler->addObjectVariable("IREL0p30",new ObjectVariableInRange<double>("RELISO",0,0.30,"IREL0p30"));
  handler->addObjectVariable("IREL0p35",new ObjectVariableInRange<double>("RELISO",0,0.3529,"IREL0p35"));
  handler->addObjectVariable("IREL0p5",new ObjectVariableInRange<double>("RELISO",0,0.5,"IREL0p5"));

  handler->addObjectVariable("ELECTRON_ISOLATED", new ObjectVariableRename<bool>("MULTIISOM", "ELECTRON_ISOLATED"));
  handler->addObjectVariable("ELECTRON_NOTISOLATED",new ObjectVariableReversed("ELECTRON_ISOLATED"));

  handler->addObjectVariable("ELECTRON_MVA_0p35", new ObjectVariableInRange<double>("MVA",0.35,100000));
  handler->addObjectVariable("ELECTRON_MVA_0p73", new ObjectVariableInRange<double>("MVA",0.73,100000));
  handler->addObjectVariable("ELECTRON_MVA_0p20", new ObjectVariableInRange<double>("MVA",0.20,100000));
  handler->addObjectVariable("ELECTRON_MVA_0p57", new ObjectVariableInRange<double>("MVA",0.57,100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p52", new ObjectVariableInRange<double>("MVA",-0.52,100000));
  handler->addObjectVariable("ELECTRON_MVA_0p05", new ObjectVariableInRange<double>("MVA",0.05,100000));

  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_LOOSE",new ObjectVariableCombined("ETA0p8","ELECTRON_MVA_0p35",true,"ELECTRON_MVA_ETA0p8_LOOSE"));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_TIGHT",new ObjectVariableCombined("ETA0p8","ELECTRON_MVA_0p73",true,"ELECTRON_MVA_ETA0p8_TIGHT"));

  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_LOOSE",new ObjectVariableCombined("ETA0p8to1p479","ELECTRON_MVA_0p20",true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_TIGHT",new ObjectVariableCombined("ETA0p8to1p479","ELECTRON_MVA_0p57",true));

  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_LOOSE", new ObjectVariableCombined("ENDCAP","ELECTRON_MVA_m0p52",true));
  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_TIGHT", new ObjectVariableCombined("ENDCAP","ELECTRON_MVA_0p05",true));

  ObjectVariableCombined* electron_mva_loose = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_LOOSE","ELECTRON_MVA_ETA0p8to1p479_LOOSE",false);
  electron_mva_loose->addVariable("ELECTRON_MVA_ENDCAP_LOOSE");
  ObjectVariableCombined* electron_mva_tight = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_TIGHT","ELECTRON_MVA_ETA0p8to1p479_TIGHT",false);
  electron_mva_tight->addVariable("ELECTRON_MVA_ENDCAP_TIGHT");

  handler->addObjectVariable("ELECTRON_MVA_LOOSE",electron_mva_loose);
  handler->addObjectVariable("ELECTRON_MVA_TIGHT",electron_mva_tight);
    

  //////////////////
  ///Muon Product///
  //////////////////

  handler->addProduct("basicMuons","ALLMUONS");
  handler->addProductCut("basicMuons","PT5");
  handler->addProductCut("basicMuons","ETA2p4");
  handler->addProductCut("basicMuons","isPFMuon");
  handler->addProductCut("basicMuons","MUON_GLOBALORTRACKER");
  handler->addProductCut("basicMuons","MUON_dz");

  handler->addProduct("looseMuons","basicMuons");
  handler->addProductCut("looseMuons","MUON_dxy");
  //handler->addProductCut("looseMuons","IREL0p5");
  handler->addProductCut("looseMuons","MINIISO0p40");

  handler->addProduct("goodMuonsLowPt","looseMuons");
  handler->addProductCut("goodMuonsLowPt","MULTIISOL");
  //handler->addProductCut("goodMuons","IREL0p15");
  handler->addProductCut("goodMuonsLowPt","SIP3D_4sigma");
  handler->addProductCut("goodMuonsLowPt","MUON_GOODSEGCOM");
  handler->addProductCut("goodMuonsLowPt","MUON_validFraction");


  handler->addProduct("goodMuons","goodMuonsLowPt");
  handler->addProductCut("goodMuons","PT10");

  handler->addProduct("isoNonPromptMuons","basicMuons");
  handler->addProductCut("isoNonPromptMuons","IREL0p15");
  handler->addProductCut("isoNonPromptMuons","MUON_nonprompt");
  
  handler->addProduct("promptNonIsoMuons","basicMuons");
  handler->addProductCut("promptNonIsoMuons","NOTIREL0p15");
  handler->addProductCut("promptNonIsoMuons","MUON_dxy");
  
  handler->addProduct("nonPromptNonIsoMuons","basicMuons");
  handler->addProductCut("nonPromptNonIsoMuons","NOTIREL0p15");
  handler->addProductCut("nonPromptNonIsoMuons","MUON_nonprompt");
  

  handler->addProduct("probeMuons","ALLMUONS");
  handler->addProductCut("probeMuons","ETA2p4");
  handler->addProductCut("probeMuons","isGlobalMuon");
  handler->addProductCut("probeMuons","MUON_dz");



  //////////////
  ///Electron///
  //////////////
  
  // loose electrons according to RA7Coordination2015 TWiki, except for isolation and promptness
  handler->addProduct("basicElectrons","ALLELECTRONS");
  handler->addProductCut("basicElectrons", "ELECTRON_MVA_LOOSE");
  handler->addProductCut("basicElectrons", "PT7");
  handler->addProductCut("basicElectrons", "ETA2p5");
  handler->addProductCut("basicElectrons", "ELECTRON_dz");
  handler->addProductCut("basicElectrons", "ELECTRON_passConversionVeto");
  handler->addProductCut("basicElectrons", "ELECTRON_MISSINGHITS");
  
  // loose electrons according to RA7Coordination2015 TWiki
  handler->addProduct("looseElectrons","basicElectrons");
  handler->addProductCut("looseElectrons", "ELECTRON_PROMPT");
  handler->addProductCut("looseElectrons", "MINIISO0p40");

  // tight electrons according to RA7Coordination2015 TWiki
  handler->addProduct("goodElectronsLowPt","looseElectrons");
  handler->addProductCut("goodElectronsLowPt", "ELECTRON_MVA_TIGHT");
  handler->addProductCut("goodElectronsLowPt", "SIP3D_4sigma");
  handler->addProductCut("goodElectronsLowPt", "MULTIISOM");

  handler->addProduct("goodElectrons","goodElectronsLowPt");
  handler->addProductCut("goodElectrons", "PT10");

  handler->addProduct("isoNonPromptElectrons","basicElectrons");
  handler->addProductCut("isoNonPromptElectrons","ELECTRON_ISOLATED");
  handler->addProductCut("isoNonPromptElectrons","ELECTRON_NONPROMPT");
  
  handler->addProduct("promptNonIsoElectrons","basicElectrons");
  handler->addProductCut("promptNonIsoElectrons","ELECTRON_NOTISOLATED");
  handler->addProductCut("promptNonIsoElectrons","ELECTRON_PROMPT");
  handler->addProductCut("promptNonIsoElectrons","SIP3D_4sigma");
  
  handler->addProduct("nonPromptNonIsoElectrons","basicElectrons");
  handler->addProductCut("nonPromptNonIsoElectrons","ELECTRON_NOTISOLATED");
  handler->addProductCut("nonPromptNonIsoElectrons","ELECTRON_NONPROMPT");


  handler->addProduct("probeElectrons","ALLELECTRONS");
  handler->addProductCut("probeElectrons","ETA2p4");
  handler->addProductCut("probeElectrons","ELECTRON_NOTGAP");
  handler->addProductCut("probeElectrons","ELECTRON_dz");
  handler->addProductCut("probeElectrons","ELECTRON_passConversionVeto");


  /////////
  ///Tau///
  /////////
  //handler->addObjectVariable("TAU_againstElectronTight3",new ObjectVariableValue<double>("againstElectronTightMVA3",1.0));
  //handler->addObjectVariable("TAU_againstMuonTight3",new ObjectVariableValue<double>("againstMuonTight3",1.0));
  //handler->addObjectVariable("TAU_isoLoose", new ObjectVariableValue<double>("byLooseCombinedIsolationDeltaBetaCorr3Hits",1.0));
  handler->addObjectVariable("TAU_nonIso", new ObjectVariableReversed("byLooseCombinedIsolationDeltaBetaCorr3Hits"));
  handler->addObjectVariable("TAU_dz", new ObjectVariableInRange<double>("dz",-0.2,0.2));

  handler->addProduct("basicTaus","ALLTAUS");
  handler->addProductCut("basicTaus","PT20");
  handler->addProductCut("basicTaus","ETA2p3");
  handler->addProductCut("basicTaus","TAU_dz");
  handler->addProductCut("basicTaus","againstElectronTightMVA5");
  handler->addProductCut("basicTaus","againstMuonTight3");
  handler->addProductCut("basicTaus","decayModeFinding");

  handler->addProduct("goodTaus","basicTaus");
  handler->addProductCut("goodTaus","byLooseCombinedIsolationDeltaBetaCorr3Hits"); 

  handler->addProduct("nonIsoTaus","ALLTAUS");
  handler->addProductCut("nonIsoTaus","TAU_nonIso");

/*  handler->addProduct("sidebandTaus","ALLTAUS");
  handler->addProductCut("sidebandTaus","TAU_nonIso");

  handler->addProduct("otherTaus","ALLTAUS");
  handler->addProductCut("otherTaus","TAU_nonIso");
*/


  ////////////
  ///Tracks///
  ////////////
  handler->addProduct("inclusiveTracks","ALLTRACKS");
  handler->addProductCut("inclusiveTracks","PT10");
  handler->addProductCut("inclusiveTracks","ETA2p4");
  handler->addProductCut("inclusiveTracks","trackHighPurity");
  handler->addProductCut("inclusiveTracks","MUON_dz");

  handler->addObjectVariable("TRACK_PROMPT",new ObjectVariableCombined("TRACK_fromPV","MUON_dxy",true,"TRACK_PROMPT"));
  handler->addObjectVariable("TRACK_NONPROMPT", new ObjectVariableReversed("TRACK_PROMPT"));
  
  handler->addProduct("goodInclusiveTracks","inclusiveTracks");
  handler->addProductCut("goodInclusiveTracks","IREL0p24");
  handler->addProductCut("goodInclusiveTracks","TRACK_PROMPT");
  
  handler->addProduct("promptInclusiveTracks","inclusiveTracks");
  handler->addProductCut("promptInclusiveTracks","TRACK_PROMPT");
  
  handler->addProduct("promptNonIsoInclusiveTracks","inclusiveTracks");
  handler->addProductCut("promptNonIsoInclusiveTracks","NOTIREL0p24");
  handler->addProductCut("promptNonIsoInclusiveTracks","TRACK_PROMPT");
  
  handler->addProduct("isoInclusiveTracks","inclusiveTracks");
  handler->addProductCut("isoInclusiveTracks","IREL0p24");
  
  handler->addProduct("isoNonPromptInclusiveTracks","inclusiveTracks");
  handler->addProductCut("isoNonPromptInclusiveTracks","IREL0p24");
  handler->addProductCut("isoNonPromptInclusiveTracks","TRACK_NONPROMPT");
  
  handler->addProduct("inclusiveTracks7","ALLTRACKS");
  handler->addProductCut("inclusiveTracks7","PT7");
  handler->addProductCut("inclusiveTracks7","trackHighPurity");
  handler->addProductCut("inclusiveTracks7","MUON_dz");
  handler->addProductCut("inclusiveTracks7","ETA2p4");
  
  handler->addProduct("promptInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("promptInclusiveTracks7","TRACK_PROMPT");
  
  handler->addProduct("promptIREL0p30InclusiveTracks7","promptInclusiveTracks7");
  handler->addProductCut("promptIREL0p30InclusiveTracks7","IREL0p30");
  
  handler->addProduct("promptNonIsoInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("promptNonIsoInclusiveTracks7","NOTIREL0p24");
  handler->addProductCut("promptNonIsoInclusiveTracks7","TRACK_PROMPT");
  
  handler->addProduct("isoInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("isoInclusiveTracks7","IREL0p24");
  
  handler->addProduct("isoNonPromptInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("isoNonPromptInclusiveTracks7","IREL0p24");
  handler->addProductCut("isoNonPromptInclusiveTracks7","TRACK_NONPROMPT");

  handler->addProduct("basicTracksNoCleaning","ALLTRACKS");
  handler->addProductCut("basicTracksNoCleaning","PT10");
  handler->addProductCut("basicTracksNoCleaning","ETA2p4");
  handler->addProductCut("basicTracksNoCleaning","trackHighPurity");
  handler->addProductCut("basicTracksNoCleaning","MUON_dz");

  handler->addProduct("basicTracks","basicTracksNoCleaning");

  handler->addProduct("goodTracks","basicTracks");
  handler->addProductCut("goodTracks","MULTIISOL");
  handler->addProductCut("goodTracks","TRACK_PROMPT");
  
  handler->addProduct("goodTracksNoCleaning","basicTracksNoCleaning");
  handler->addProductCut("goodTracksNoCleaning","IREL0p15");
  handler->addProductCut("goodTracksNoCleaning","TRACK_PROMPT");

  handler->addProduct("promptTracks","basicTracks");
  handler->addProductCut("promptTracks","TRACK_PROMPT");
  
  handler->addProduct("promptNonIsoTracks","basicTracks");
  handler->addProductCut("promptNonIsoTracks","NOTIREL0p24");
  handler->addProductCut("promptNonIsoTracks","TRACK_PROMPT");
  
  handler->addProduct("isoTracks","basicTracks");
  handler->addProductCut("isoTracks","IREL0p24");
  
  handler->addProduct("isoNonPromptTracks","basicTracks");
  handler->addProductCut("isoNonPromptTracks","IREL0p24");
  handler->addProductCut("isoNonPromptTracks","TRACK_NONPROMPT");
  
  handler->addProduct("basicTracks7","ALLTRACKS");
  handler->addProductCut("basicTracks7","PT7");
  handler->addProductCut("basicTracks7","ETA2p4");
  handler->addProductCut("basicTracks7","trackHighPurity");
  handler->addProductCut("basicTracks7","MUON_dz");
  
  handler->addProduct("promptTracks7","basicTracks7");
  handler->addProductCut("promptTracks7","TRACK_PROMPT");
  
  handler->addProduct("promptNonIsoTracks7","basicTracks7");
  handler->addProductCut("promptNonIsoTracks7","NOTIREL0p24");
  handler->addProductCut("promptNonIsoTracks7","TRACK_PROMPT");
  
  handler->addProduct("isoTracks7","basicTracks7");
  handler->addProductCut("isoTracks7","IREL0p24");
  
  handler->addProduct("isoNonPromptTracks7","basicTracks7");
  handler->addProductCut("isoNonPromptTracks7","IREL0p24");
  handler->addProductCut("isoNonPromptTracks7","TRACK_NONPROMPT");

  /////////////
  ///Photons///
  /////////////
  handler->addObjectVariable("PHOTON_BARREL_hadronicOverEm", new ObjectVariableInRange<double>("hadronicOverEm",-0.010,0.010));
  handler->addObjectVariable("PHOTON_ENDCAP_hadronicOverEm", new ObjectVariableInRange<double>("hadronicOverEm",-0.0321,0.0321));

  handler->addObjectVariable("PHOTON_BARREL_full5x5_sigmaIetaIeta", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0.0,0.0559));
  handler->addObjectVariable("PHOTON_ENDCAP_full5x5_sigmaIetaIeta", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0.0,0.049));

  ObjectVariableCombined* photon_barrel = new ObjectVariableCombined("BARREL","PHOTON_BARREL_hadronicOverEm",true,"photon_barrel_good");
  photon_barrel->addVariable("PHOTON_BARREL_full5x5_sigmaIetaIeta");

  handler->addObjectVariable("PHOTON_BARREL",photon_barrel);

  ObjectVariableCombined* photon_endcap = new ObjectVariableCombined("ENDCAP","PHOTON_ENDCAP_hadronicOverEm",true,"photon_endcap_good");
  photon_endcap->addVariable("PHOTON_ENDCAP_full5x5_sigmaIetaIeta");

  handler->addObjectVariable("PHOTON_ENDCAP",photon_endcap);

  handler->addObjectVariable("PHOTON_COMBINED", new ObjectVariableCombined("PHOTON_BARREL","PHOTON_ENDCAP",false,"PHOTON_COMBINED"));

  handler->addProduct("basicPhotons","ALLPHOTONS");
  handler->addProductCut("basicPhotons","PT15");
  handler->addProductCut("basicPhotons","ETA2p4");
  handler->addProductCut("basicPhotons","PHOTON_COMBINED");

  handler->addProduct("goodPhotons","basicPhotons");
  handler->addProductCut("goodPhotons","passTightId");

  handler->addProduct("mediumPhotons","basicPhotons");
  handler->addProductCut("mediumPhotons","passMediumId");

  handler->addProduct("loosePhotons","basicPhotons");
  handler->addProductCut("loosePhotons","passLooseId");
  
  //////////////
  //Setup Jets//
  //////////////
  handler->addObjectVariable("JET_NEUTRALHADRONFRACTION", new ObjectVariableInRange<double>("neutralHadronEnergyFraction",0,0.99));
  handler->addObjectVariable("JET_NEUTRALEMFRACTION", new ObjectVariableInRange<double>("neutralEmEnergyFraction", 0,0.99));
  handler->addObjectVariable("JET_NUMBEROFCONSTITUENTS", new ObjectVariableInRange<int>("numberOfConstituents",2,100000));
  handler->addObjectVariable("JET_MUONFRACTION", new ObjectVariableInRange<double>("muonEnergyFraction",0,0.8));
  handler->addObjectVariable("JET_CHARGEDHADRONFRACTION", new ObjectVariableInRange<double>("chargedHadronEnergyFraction",1e-6,1000));
  handler->addObjectVariable("JET_CHARGEDMULTIPLICITY", new ObjectVariableInRange<int>("chargedMultiplicity",1,1e6));
  handler->addObjectVariable("JET_CHARGEDEMFRACTION", new ObjectVariableInRange<double>("chargedEmEnergyFraction",0,0.99));
  handler->addObjectVariable("CSVM",new ObjectVariableInRange<double>("pfCombinedInclusiveSecondaryVertexV2BJetTags",0.814,1000.0));
  handler->addObjectVariable("CSVL",new ObjectVariableInRange<double>("pfCombinedInclusiveSecondaryVertexV2BJetTags",0.423,1000.0));

  handler->addProduct("basicJetsNoCleaning","ALLJETS");
  handler->addProductCut("basicJetsNoCleaning","PT20");
  handler->addProductCut("basicJetsNoCleaning","JET_NEUTRALHADRONFRACTION");
  handler->addProductCut("basicJetsNoCleaning","JET_NEUTRALEMFRACTION");
  handler->addProductCut("basicJetsNoCleaning","JET_NUMBEROFCONSTITUENTS");
  handler->addProductCut("basicJetsNoCleaning","JET_MUONFRACTION");

  handler->addProduct("goodJets","basicJetsNoCleaning");
  handler->addProductCut("goodJets","PT30");
  handler->addProductCut("goodJets","ETA2p4");
  handler->addProductCut("goodJets","JET_CHARGEDHADRONFRACTION");
  handler->addProductCut("goodJets","JET_CHARGEDMULTIPLICITY");
  handler->addProductCut("goodJets","JET_CHARGEDEMFRACTION");

  handler->addProduct("goodForwardJets", "basicJetsNoCleaning");
  handler->addProductCut("goodForwardJets", "PT30");
  handler->addProductCut("goodForwardJets", "ETA2p4to4p7");

  handler->addProduct("bJetsCSVM","goodJets");
  handler->addProductCut("bJetsCSVM","CSVM");

  handler->addProduct("bJetsCSVL","goodJets");
  handler->addProductCut("bJetsCSVL","CSVL");

  //////////////
  ///Vertex/////
  //////////////
  handler->addObjectVariable("VERTEX_NDOF", new ObjectVariableInRange<double>("ndof",4,100000));
  handler->addObjectVariable("VERTEX_Z",new ObjectVariableInRange<double>("z",-24,24));
  handler->addObjectVariable("VERTEX_NOTFAKE",new ObjectVariableReversed("isFake"));
  handler->addObjectVariable("VERTEX_RHO",new ObjectVariableInRange<double>("rho",-4,4));

  handler->addProduct("goodRecoVertices","ALLRECOVERTICES");
  handler->addProductCut("goodRecoVertices","VERTEX_NDOF");
  handler->addProductCut("goodRecoVertices","VERTEX_Z");
  handler->addProductCut("goodRecoVertices","VERTEX_NOTFAKE");
  handler->addProductCut("goodRecoVertices","VERTEX_RHO");


  /////////////////
  ///Separations///
  /////////////////
  ObjectComparisonDeltaR* deltaR0p05 = new ObjectComparisonDeltaR(0.05);
  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p3 = new ObjectComparisonDeltaR(0.3);
  ObjectComparisonDeltaR* deltaR0p4 = new ObjectComparisonDeltaR(0.4);

  /*
  handler->addProductSelfComparison("goodMuons",deltaR0p1);
  handler->addProductSelfComparison("goodElectrons",deltaR0p1);
  handler->addProductSelfComparison("probeMuons",deltaR0p1);
  handler->addProductSelfComparison("probeElectrons",deltaR0p1);
  handler->addProductSelfComparison("basicTracks",deltaR0p005);
  handler->addProductSelfComparison("basicTracks7",deltaR0p005);
  handler->addProductSelfComparison("inclusiveTracks",deltaR0p005);
  handler->addProductSelfComparison("inclusiveTracks7",deltaR0p005);
  */

  handler->addProductSelfComparison("ALLRECOVERTICES",deltaR0p05);

  handler->addProductComparison("looseElectrons","looseMuons",deltaR0p05);
  //handler->addProductComparison("goodElectrons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTaus","looseMuons",deltaR0p3);
  handler->addProductComparison("goodTaus","looseElectrons",deltaR0p3);

  handler->addProductComparison("basicTracks","goodMuons",deltaR0p3);
  handler->addProductComparison("basicTracks","goodElectrons",deltaR0p3);
  handler->addProductComparison("basicTracks","goodTaus",deltaR0p3);

  handler->addProductComparison("goodPhotons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodElectrons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTaus",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTracks",deltaR0p1);

  handler->addProductComparison("basicJetsNoCleaning","goodMuons",deltaR0p3);
  handler->addProductComparison("basicJetsNoCleaning","goodElectrons",deltaR0p3);

  handler->addProductComparison("goodJets","goodMuons",deltaR0p4);
  handler->addProductComparison("goodJets","goodElectrons",deltaR0p4);
  handler->addProductComparison("goodJets","goodTaus",deltaR0p4);
//  handler->addProductComparison("goodJets","goodPhotons",deltaR0p3);

  //////////////////////
  ///Derived Products////
  //////////////////////
  handler->addProduct("posGoodMuons","goodMuons");
  handler->addProductCut("posGoodMuons","POSITIVE");
  handler->addProduct("negGoodMuons","goodMuons");
  handler->addProductCut("negGoodMuons","NEGATIVE");

  handler->addProduct("posGoodElectrons","goodElectrons");
  handler->addProductCut("posGoodElectrons","POSITIVE");
  handler->addProduct("negGoodElectrons","goodElectrons");
  handler->addProductCut("negGoodElectrons","NEGATIVE");

  handler->addProduct("posGoodTracks","goodTracks");
  handler->addProductCut("posGoodTracks","POSITIVE");
  handler->addProduct("negGoodTracks","goodTracks");
  handler->addProductCut("negGoodTracks","NEGATIVE");

  handler->addProduct("goodElectronsNEG","goodElectrons");
  handler->addProductCut("goodElectronsNEG","NEGATIVE");
  handler->addProduct("goodElectronsPOS","goodElectrons");
  handler->addProductCut("goodElectronsPOS","POSITIVE");
  handler->addProduct("probeElectronsNEG","probeElectrons");
  handler->addProductCut("probeElectronsNEG","NEGATIVE");
  handler->addProduct("probeElectronsPOS","probeElectrons");
  handler->addProductCut("probeElectronsPOS","POSITIVE");

  handler->addProduct("goodMuonsNEG","goodMuons");
  handler->addProductCut("goodMuonsNEG","NEGATIVE");
  handler->addProduct("goodMuonsPOS","goodMuons");
  handler->addProductCut("goodMuonsPOS","POSITIVE");
  handler->addProduct("probeMuonsNEG","probeMuons");
  handler->addProductCut("probeMuonsNEG","NEGATIVE");
  handler->addProduct("probeMuonsPOS","probeMuons");
  handler->addProductCut("probeMuonsPOS","POSITIVE");

}


void setupVariables(BaseHandler* handler)
{

  handler->addEventVariable("N_bJetsCSVM", new EventVariableN("N_bJetsCSVM","bJetsCSVM"));
  handler->addEventVariable("N_bJetsCSVL", new EventVariableN("N_bJetsCSVL","bJetsCSVL"));

  handler->addEventVariable("N_promptTracks",new EventVariableN("N_promptTracks","promptTracks"));
  handler->addEventVariable("N_nonPromptTracks",new EventVariableN("N_nonPromptTracks","nonPromptTracks"));
  handler->addEventVariable("N_goodTracks", new EventVariableN("N_goodTracks","goodTracks"));

  handler->addEventVariable("N_fakeElectrons", new EventVariableN("N_fakeElectrons","goodElectronsNotMatched"));
  handler->addEventVariable("N_fakeMuons", new EventVariableN("N_fakeMuons","goodMuonsNotMatched"));

  handler->addEventVariable("N_matchedElectrons", new EventVariableN("N_matchedElectrons","goodElectronsMatched"));
  handler->addEventVariable("N_matchedMuons", new EventVariableN("N_matchedMuons","goodMuonsMatched"));

  handler->addEventVariable("N_electrons", new EventVariableN("N_electrons","goodElectrons"));
  handler->addEventVariable("N_muons", new EventVariableN("N_muons","goodMuons"));

  handler->addEventVariable("N_goodJets", new EventVariableN("N_goodJets","goodJets"));

  handler->addEventVariable("N_goodVertices", new EventVariableN("N_goodVertices","goodRecoVertices"));

  handler->addEventVariable("HT", new EventVariableSumPT("HT","goodJets"));
  handler->addEventVariable("SumPromptTrackPt", new EventVariableSumPT("SumPromptTrackPt","promptTracks"));
  handler->addEventVariable("SumNonPromptTrackPt", new EventVariableSumPT("SumNonPromptTrackPt","nonPromptTracks"));
  handler->addEventVariable("SumBasicTrackPt", new EventVariableSumPT("SumBasicTrackPt","basicTracks"));

  EventVariableMixedPairMass* mumassProbePlus = new EventVariableMixedPairMass("MUPLUSMASS","goodMuonsNEG","MUPLUS_",91,15);
  mumassProbePlus->addProduct("probeMuonsPOS");
  handler->addEventVariable("MUPLUSMASS",mumassProbePlus);
  EventVariableMixedPairMass* mumassProbeMinus = new EventVariableMixedPairMass("MUMINUSMASS","goodMuonsPOS","MUMINUS_",91,15);
  mumassProbeMinus->addProduct("probeMuonsNEG");
  handler->addEventVariable("MUMINUSMASS",mumassProbeMinus);
  EventVariablePairMass* mumassProbe = new EventVariablePairMass("MUPROBEMASS","probeMuons","PROBEMU_",91,15);
  handler->addEventVariable("MUPROBEMASS",mumassProbe);
  EventVariablePairMass* mumassGood = new EventVariablePairMass("MUGOODMASS","goodMuons","GOODMU_",91,15);
  handler->addEventVariable("MUGOODMASS",mumassGood);

  EventVariableMixedPairMass* elmassProbePlus = new EventVariableMixedPairMass("ELPLUSMASS","goodElectronsNEG","ELPLUS_",91,15);
  elmassProbePlus->addProduct("probeElectronsPOS");
  handler->addEventVariable("ELPLUSMASS",elmassProbePlus);
  EventVariableMixedPairMass* elmassProbeMinus = new EventVariableMixedPairMass("ELMINUSMASS","goodElectronsPOS","ELMINUS_",91,15);
  elmassProbeMinus->addProduct("probeElectronsNEG");
  handler->addEventVariable("ELMINUSMASS",elmassProbeMinus);
  EventVariablePairMass* elmassProbe = new EventVariablePairMass("ELPROBEMASS","probeElectrons","PROBEEL_",91,15);
  handler->addEventVariable("ELPROBEMASS",elmassProbe);
  EventVariablePairMass* elmassGood = new EventVariablePairMass("ELGOODMASS","goodElectrons","GOODEL_",91,15);
  handler->addEventVariable("ELGOODMASS",elmassGood);

  handler->addEventVariable("PROBEMUPLUSPT",new  EventVariableObjectVariableExtreme<double>("PT","probeMuonsPOS"));
  handler->addEventVariable("PROBEMUMINUSPT",new  EventVariableObjectVariableExtreme<double>("PT","probeMuonsNEG"));
  handler->addEventVariable("PROBEELPLUSPT",new  EventVariableObjectVariableExtreme<double>("PT","probeElectronsPOS"));
  handler->addEventVariable("PROBEELMINUSPT",new  EventVariableObjectVariableExtreme<double>("PT","probeElectronsNEG"));

  handler->addEventVariable("GOODMUPLUSPT",new  EventVariableObjectVariableExtreme<double>("PT","goodMuonsPOS"));
  handler->addEventVariable("GOODMUMINUSPT",new  EventVariableObjectVariableExtreme<double>("PT","goodMuonsNEG"));
  handler->addEventVariable("GOODELPLUSPT",new  EventVariableObjectVariableExtreme<double>("PT","goodElectronsPOS"));
  handler->addEventVariable("GOODELMINUSPT",new  EventVariableObjectVariableExtreme<double>("PT","goodElectronsNEG"));

}


void setupOnZSignatures(BaseHandler* handler)
{
  handler->addSignature("Mu2")
    ->addCut("twoMcMuonsFromZ")
    ;
  handler->addSignature("El2")
    ->addCut("twoMcElectronsFromZ")
    ;

}


void addHistograms(BaseHandler* handler)
{
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

  handler->addHistogram(new SignatureTH1F_N("N_PROBEMUONS","probeMuons"));
  handler->addHistogram(new SignatureTH1F_N("N_GOODMUONS","goodMuons"));
  handler->addHistogram(new SignatureTH1F_N("N_ALLMUONS","ALLMUONS"));
  handler->addHistogram(new SignatureTH1F_N("N_PROBEELECTRONS","probeElectrons"));
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

void setupPrintRA7Sync(BaseHandler* handler)
{
  PrintModuleEventVariables* printLines = new PrintModuleEventVariables("print");
  double ddd = 0;
  int iii = 0;
  bool bbb = true;
  printLines->addVariable("NGOODELECTRONS",iii);
  printLines->addVariable("NGOODMUONS",iii);
  printLines->addVariable("NGOODTAUS",iii);
  printLines->addVariable("NGOODJETS",iii);
  printLines->addVariable("NBJETSCSVM",iii);
  printLines->addVariable("NBJETSCSVL",iii);
  printLines->addVariable("MET",ddd);
  printLines->addVariable("MLL",ddd);
  printLines->addVariable("MT",ddd);
  printLines->addVariable("ONZ",bbb);
  printLines->addVariable("NGOODRECOVERTICES",iii);
  printLines->addVariable("OSSFMAXMLL",ddd);
  printLines->addVariable("OSSFMINMLL",ddd);
  printLines->addVariable("MOSSF",ddd);
  handler->addPrintModule(printLines);
}


void setupVariables2(BaseHandler* handler,bool isMC = false, double mZ = 91, double zWidth = 10, double mW = 80.385) {
  handler->addEventVariable("ALWAYSTRUE", new EventVariableConst<bool>(true));

  EventVariableThreshold* pt201512 = new EventVariableThreshold("PT201512","goodElectrons");
  pt201512->addProduct("goodMuons");
  pt201512->addThreshold(20);
  pt201512->addThreshold(15);
  pt201512->addThreshold(12);
  handler->addEventVariable("PT201512",pt201512);

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

  EventVariableObjectVariableVector<double>* leptonPts = new EventVariableObjectVariableVector<double>("PT","goodMuons",true);
  leptonPts->addProduct("goodElectrons");
  handler->addEventVariable("PTGOODLEPTONS",leptonPts);
  
  handler->addEventVariable("DXYBASICELECTRONS", new EventVariableObjectVariableVector<double>("dxy","basicElectrons"));
  handler->addEventVariable("RELISOBASICELECTRONS", new EventVariableObjectVariableVector<double>("RELISO","basicElectrons"));
  handler->addEventVariable("MINIISOBASICELECTRONS", new EventVariableObjectVariableVector<double>("MINIISO","basicElectrons"));
  handler->addEventVariable("ptRatioBASICELECTRONS", new EventVariableObjectVariableVector<double>("ptRatio","basicElectrons"));
  handler->addEventVariable("ptRelBASICELECTRONS", new EventVariableObjectVariableVector<double>("ptRel","basicElectrons"));
  handler->addEventVariable("PTBASICELECTRONS", new EventVariableObjectVariableVector<double>("PT","basicElectrons"));
  
  handler->addEventVariable("DXYBASICMUONS", new EventVariableObjectVariableVector<double>("dxy","basicMuons"));
  handler->addEventVariable("RELISOBASICMUONS", new EventVariableObjectVariableVector<double>("RELISO","basicMuons"));
  handler->addEventVariable("MINIISOBASICMUONS", new EventVariableObjectVariableVector<double>("MINIISO","basicMuons"));
  handler->addEventVariable("ptRatioBASICMUONS", new EventVariableObjectVariableVector<double>("ptRatio","basicMuons"));
  handler->addEventVariable("ptRelBASICMUONS", new EventVariableObjectVariableVector<double>("ptRel","basicMuons"));
  handler->addEventVariable("PTBASICMUONS", new EventVariableObjectVariableVector<double>("PT","basicMuons"));
  
  handler->addEventVariable("NBASICTAUS", new EventVariableN("NBASICTAUS","basicTaus"));
  handler->addEventVariable("RELISOBASICTAUS", new EventVariableObjectVariableVector<double>("RELISO","basicTaus"));
  handler->addEventVariable("TOTALISOBASICTAUS", new EventVariableObjectVariableVector<double>("TOTALISO","basicTaus"));
  handler->addEventVariable("PTBASICTAUS", new EventVariableObjectVariableVector<double>("PT","basicTaus"));

  handler->addEventVariable("NGOODELECTRONS", new EventVariableN("NGOODELECTRONS","goodElectrons"));
  handler->addEventVariable("QGOODELECTRONS", new EventVariableObjectVariableVector<int>("CHARGE","goodElectrons"));
  handler->addEventVariable("PTGOODELECTRONS", new EventVariableObjectVariableVector<double>("PT","goodElectrons"));
  handler->addEventVariable("ETAGOODELECTRONS", new EventVariableObjectVariableVector<double>("ETA","goodElectrons"));
  handler->addEventVariable("fakeRoleGOODELECTRONS", new EventVariableObjectVariableVector<int>("fakeRole","goodElectrons"));
  
  handler->addEventVariable("NGOODMUONS",new EventVariableN("NGOODMUONS","goodMuons"));
  handler->addEventVariable("QGOODMUONS", new EventVariableObjectVariableVector<int>("CHARGE","goodMuons"));
  handler->addEventVariable("PTGOODMUONS", new EventVariableObjectVariableVector<double>("PT","goodMuons"));
  handler->addEventVariable("ETAGOODMUONS", new EventVariableObjectVariableVector<double>("ETA","goodMuons"));
  handler->addEventVariable("fakeRoleGOODMUONS", new EventVariableObjectVariableVector<int>("fakeRole","goodMuons"));

  handler->addEventVariable("NGOODELECTRONSLOWPT", new EventVariableN("NGOODELECTRONSLOWPT","goodElectronsLowPt"));
  handler->addEventVariable("QGOODELECTRONSLOWPT", new EventVariableObjectVariableVector<int>("CHARGE","goodElectronsLowPt"));
  handler->addEventVariable("PTGOODELECTRONSLOWPT", new EventVariableObjectVariableVector<double>("PT","goodElectronsLowPt"));
  handler->addEventVariable("ETAGOODELECTRONSLOWPT", new EventVariableObjectVariableVector<double>("ETA","goodElectronsLowPt"));
  handler->addEventVariable("fakeRoleGOODELECTRONSLOWPT", new EventVariableObjectVariableVector<int>("fakeRole","goodElectronsLowPt"));
  
  handler->addEventVariable("NGOODMUONSLOWPT",new EventVariableN("NGOODMUONSLOWPT","goodMuonsLowPt"));
  handler->addEventVariable("QGOODMUONSLOWPT", new EventVariableObjectVariableVector<int>("CHARGE","goodMuonsLowPt"));
  handler->addEventVariable("PTGOODMUONSLOWPT", new EventVariableObjectVariableVector<double>("PT","goodMuonsLowPt"));
  handler->addEventVariable("ETAGOODMUONSLOWPT", new EventVariableObjectVariableVector<double>("ETA","goodMuonsLowPt"));
  handler->addEventVariable("fakeRoleGOODMUONSLOWPT", new EventVariableObjectVariableVector<int>("fakeRole","goodMuonsLowPt"));

  
  handler->addEventVariable("NGOODTAUS", new EventVariableN("NGOODTAUS","goodTaus"));
  handler->addEventVariable("QGOODTAUS", new EventVariableObjectVariableVector<int>("CHARGE","goodTaus"));
  handler->addEventVariable("PTGOODTAUS", new EventVariableObjectVariableVector<double>("PT","goodTaus"));
  handler->addEventVariable("ETAGOODTAUS", new EventVariableObjectVariableVector<double>("ETA","goodTaus"));
  handler->addEventVariable("fakeRoleGOODTAUS", new EventVariableObjectVariableVector<int>("fakeRole","goodTaus"));
  handler->addEventVariable("TOTALISOGOODTAUS", new EventVariableObjectVariableVector<double>("TOTALISO","goodTaus"));
  handler->addEventVariable("TOTALMINIISOGOODTAUS", new EventVariableObjectVariableVector<double>("TOTALMINIISO","goodTaus"));
  handler->addEventVariable("MINIISOGOODTAUS", new EventVariableObjectVariableVector<double>("MINIISO","goodTaus"));
  
  handler->addEventVariable("NNONISOTAUS", new EventVariableN("NNONISOTAUS","nonIsoTaus"));
//  handler->addEventVariable("NSIDEBANDTAUS", new EventVariableN("NSIDEBANDTAUS","sidebandTaus"));
//  handler->addEventVariable("NOTHERTAUS", new EventVariableN("NOTHERTAUS","otherTaus"));
  
  handler->addEventVariable("NGOODJETS", new EventVariableN("NGOODJETS","goodJets"));
  handler->addEventVariable("PTGOODJETS", new EventVariableObjectVariableVector<double>("PT","goodJets"));
  handler->addEventVariable("ETAGOODJETS", new EventVariableObjectVariableVector<double>("ETA","goodJets"));

  handler->addEventVariable("NGOODFORWARDJETS", new EventVariableN("NGOODFORWARDJETS","goodForwardJets"));
  handler->addEventVariable("PTGOODFORWARDJETS", new EventVariableObjectVariableVector<double>("PT","goodForwardJets"));
  handler->addEventVariable("ETAGOODFORWARDJETS", new EventVariableObjectVariableVector<double>("ETA","goodForwardJets"));
  
  handler->addEventVariable("NGOODPHOTONS", new EventVariableN("NGOODPHOTONS","goodPhotons"));
  handler->addEventVariable("PTGOODPHOTONS", new EventVariableObjectVariableVector<double>("PT","goodPhotons"));
  handler->addEventVariable("ETAGOODPHOTONS", new EventVariableObjectVariableVector<double>("ETA","goodPhotons"));

  handler->addEventVariable("NMEDIUMPHOTONS", new EventVariableN("NMEDIUMPHOTONS","mediumPhotons"));
  handler->addEventVariable("NLOOSEPHOTONS", new EventVariableN("NLOOSEPHOTONS","loosePhotons"));

  handler->addEventVariable("nINPELECTRONS", new EventVariableN("nINPELECTRONS","isoNonPromptElectrons"));
  handler->addEventVariable("QINPELECTRONS", new EventVariableObjectVariableVector<int>("CHARGE","isoNonPromptElectrons"));
  handler->addEventVariable("PTINPELECTRONS", new EventVariableObjectVariableVector<double>("PT","isoNonPromptElectrons"));
  handler->addEventVariable("ETAINPELECTRONS", new EventVariableObjectVariableVector<double>("ETA","isoNonPromptElectrons"));

  handler->addEventVariable("nNIPELECTRONS", new EventVariableN("nNIPELECTRONS","promptNonIsoElectrons"));
  handler->addEventVariable("QNIPELECTRONS", new EventVariableObjectVariableVector<int>("CHARGE","promptNonIsoElectrons"));
  handler->addEventVariable("PTNIPELECTRONS", new EventVariableObjectVariableVector<double>("PT","promptNonIsoElectrons"));
  handler->addEventVariable("ETANIPELECTRONS", new EventVariableObjectVariableVector<double>("ETA","promptNonIsoElectrons"));

  handler->addEventVariable("nNINPELECTRONS", new EventVariableN("nNIPELECTRONS","nonPromptNonIsoElectrons"));
  handler->addEventVariable("QNINPELECTRONS", new EventVariableObjectVariableVector<int>("CHARGE","nonPromptNonIsoElectrons"));
  handler->addEventVariable("PTNINPELECTRONS", new EventVariableObjectVariableVector<double>("PT","nonPromptNonIsoElectrons"));
  handler->addEventVariable("ETANINPELECTRONS", new EventVariableObjectVariableVector<double>("ETA","nonPromptNonIsoElectrons"));
  
  handler->addEventVariable("nINPMUONS", new EventVariableN("nINPMUONS","isoNonPromptMuons"));
  handler->addEventVariable("QINPMUONS", new EventVariableObjectVariableVector<int>("CHARGE","isoNonPromptMuons"));
  handler->addEventVariable("PTINPMUONS", new EventVariableObjectVariableVector<double>("PT","isoNonPromptMuons"));
  handler->addEventVariable("ETAINPMUONS", new EventVariableObjectVariableVector<double>("ETA","isoNonPromptMuons"));
  
  handler->addEventVariable("nNIPMUONS", new EventVariableN("nNIPMUONS","promptNonIsoMuons"));
  handler->addEventVariable("QNIPMUONS", new EventVariableObjectVariableVector<int>("CHARGE","promptNonIsoMuons"));
  handler->addEventVariable("PTNIPMUONS", new EventVariableObjectVariableVector<double>("PT","promptNonIsoMuons"));
  handler->addEventVariable("ETANIPMUONS", new EventVariableObjectVariableVector<double>("ETA","promptNonIsoMuons"));
  
  handler->addEventVariable("nNINPMUONS", new EventVariableN("nNIPMUONS","nonPromptNonIsoMuons"));
  handler->addEventVariable("QNINPMUONS", new EventVariableObjectVariableVector<int>("CHARGE","nonPromptNonIsoMuons"));
  handler->addEventVariable("PTNINPMUONS", new EventVariableObjectVariableVector<double>("PT","nonPromptNonIsoMuons"));
  handler->addEventVariable("ETANINPMUONS", new EventVariableObjectVariableVector<double>("ETA","nonPromptNonIsoMuons"));

  // Inclusive tracks
  handler->addEventVariable("NGOODINCLUSIVETRACKS", new EventVariableN("NGOODTRACKS","goodInclusiveTracks"));
  
  handler->addEventVariable("NINCLUSIVETRACKS", new EventVariableN("NINCLUSIVETRACKS","inclusiveTracks"));
  handler->addEventVariable("RELISOINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("RELISO","inclusiveTracks"));
  handler->addEventVariable("MINIISOINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("MINIISO","inclusiveTracks"));
  handler->addEventVariable("ptRatioINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("ptRatio","inclusiveTracks"));
  handler->addEventVariable("ptRelINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("ptRel","inclusiveTracks"));
  handler->addEventVariable("PTINCLUSIVETRACKS", new EventVariableObjectVariableVector<double>("PT","inclusiveTracks"));
  
  handler->addEventVariable("NISOINCLUSIVETRACKS", new EventVariableN("NISOINCLUSIVETRACKS","isoInclusiveTracks"));
  handler->addEventVariable("NPROMPTINCLUSIVETRACKS", new EventVariableN("NPROMPTINCLUSIVETRACKS","promptInclusiveTracks"));
  handler->addEventVariable("NISONONPROMPTINCLUSIVETRACKS", new EventVariableN("NISONONPROMPTINCLUSIVETRACKS","isoNonPromptInclusiveTracks"));
  handler->addEventVariable("NPROMPTNONISOINCLUSIVETRACKS", new EventVariableN("NPROMPTNONISOINCLUSIVETRACKS","promptNonIsoInclusiveTracks"));
  
  handler->addEventVariable("NINCLUSIVETRACKS7", new EventVariableN("NINCLUSIVETRACKS7","inclusiveTracks7"));
  handler->addEventVariable("NISOINCLUSIVETRACKS7", new EventVariableN("NISOINCLUSIVETRACKS7","isoInclusiveTracks7"));
  handler->addEventVariable("NPROMPTINCLUSIVETRACKS7", new EventVariableN("NPROMPTINCLUSIVETRACKS7","promptInclusiveTracks7"));
  handler->addEventVariable("NPROMPTIREL0p30INCLUSIVETRACKS7", new EventVariableN("NPROMPTIREL0p30INCLUSIVETRACKS7","promptIREL0p30InclusiveTracks7"));
  handler->addEventVariable("NISONONPROMPTINCLUSIVETRACKS7", new EventVariableN("NISONONPROMPTINCLUSIVETRACKS7","isoNonPromptInclusiveTracks7"));
  handler->addEventVariable("NPROMPTNONISOINCLUSIVETRACKS7", new EventVariableN("NPROMPTNONISOINCLUSIVETRACKS7","promptNonIsoInclusiveTracks7"));
  
  // Regular tracks
  handler->addEventVariable("NGOODTRACKS", new EventVariableN("NGOODTRACKS","goodTracks"));
  handler->addEventVariable("QGOODTRACKS", new EventVariableObjectVariableVector<int>("CHARGE","goodTracks"));
  handler->addEventVariable("PTGOODTRACKS", new EventVariableObjectVariableVector<double>("PT","goodTracks"));
  handler->addEventVariable("ETAGOODTRACKS", new EventVariableObjectVariableVector<double>("ETA","goodTracks"));
  
  handler->addEventVariable("NBASICTRACKS", new EventVariableN("NBASICTRACKS","basicTracks"));
  handler->addEventVariable("NISOTRACKS", new EventVariableN("NISOTRACKS","isoTracks"));
  handler->addEventVariable("NPROMPTTRACKS", new EventVariableN("NPROMPTTRACKS","promptTracks"));

  handler->addEventVariable("NISONONPROMPTTRACKS", new EventVariableN("NISONONPROMPTTRACKS","isoNonPromptTracks"));
  handler->addEventVariable("PTISONONPROMPTTRACKS", new EventVariableObjectVariableVector<double>("PT","isoNonPromptTracks"));
  handler->addEventVariable("ETAISONONPROMPTTRACKS", new EventVariableObjectVariableVector<double>("ETA","isoNonPromptTracks"));

  handler->addEventVariable("NPROMPTNONISOTRACKS", new EventVariableN("NPROMPTNONISOTRACKS","promptNonIsoTracks"));
  handler->addEventVariable("PTPROMPTNONISOTRACKS", new EventVariableObjectVariableVector<double>("PT","promptNonIsoTracks"));
  handler->addEventVariable("ETAPROMPTNONISOTRACKS", new EventVariableObjectVariableVector<double>("ETA","promptNonIsoTracks"));
  
  handler->addEventVariable("NBASICTRACKS7", new EventVariableN("NBASICTRACKS7","basicTracks7"));
  handler->addEventVariable("NISOTRACKS7", new EventVariableN("NISOTRACKS7","isoTracks7"));
  handler->addEventVariable("NPROMPTTRACKS7", new EventVariableN("NPROMPTTRACKS7","promptTracks7"));
  handler->addEventVariable("NISONONPROMPTTRACKS7", new EventVariableN("NISONONPROMPTTRACKS7","isoNonPromptTracks7"));
  handler->addEventVariable("NPROMPTNONISOTRACKS7", new EventVariableN("NPROMPTNONISOTRACKS7","promptNonIsoTracks7"));
  
  handler->addEventVariable("NRECOVERTICES", new EventVariableN("NRECOVERTICES","ALLRECOVERTICES"));

  EventVariableSumPT* HT = new EventVariableSumPT("HT","goodJets");
  handler->addEventVariable("HT",HT);

  if(isMC){
    EventVariableSmearMET* MET = new EventVariableSmearMET("MET","MET","HT","NRECOVERTICES",2.68,4.14,3.48,2.68,5.10,3.48);
    MET->setSeed(3141592654);
    handler->addEventVariable("MET",MET);
  }else{
    EventVariableSumPT* MET = new EventVariableSumPT("MET","MET");
    handler->addEventVariable("MET",MET);
  }

  EventVariableSumPT* LT = new EventVariableSumPT("LT","goodMuons");
  LT->addProduct("goodElectrons");
  LT->addProduct("goodTaus");
  handler->addEventVariable("LT",LT);
  
  EventVariableSumPT* ST = new EventVariableSumPT("ST","goodMuons");
  ST->addProduct("goodElectrons");
  ST->addProduct("goodTaus");
  ST->addProduct("goodJets");
  ST->addProduct("MET");
  handler->addEventVariable("ST",ST);

  EventVariableSumPT* pTbjetsCSVL = new EventVariableSumPT("HTCSVL","bJetsCSVL");
  handler->addEventVariable("HTCSVL",pTbjetsCSVL);

  EventVariableSumPT* pTbjetsCSVM = new EventVariableSumPT("HTCSVM","bJetsCSVM");
  handler->addEventVariable("HTCSVM",pTbjetsCSVM);

  EventVariableOSSF* OSSF = new EventVariableOSSF("OSSF","goodMuons","",mZ,zWidth);
  OSSF->addProduct("goodElectrons");
  handler->addEventVariable("OSSF",OSSF);

  EventVariableMass* massLeptons = new EventVariableMass("MLEPTONS", "goodElectrons");
  massLeptons->addProduct("goodMuons");
  massLeptons->addProduct("goodTaus");
  handler->addEventVariable("MLEPTONS", massLeptons);

  EventVariableMass* massLightLeptons = new EventVariableMass("MLIGHTLEPTONS", "goodElectrons");
  massLightLeptons->addProduct("goodMuons");
  handler->addEventVariable("MLIGHTLEPTONS", massLightLeptons);

  EventVariableMass* massPhotons = new EventVariableMass("MPHOTONS", "goodPhotons");
  handler->addEventVariable("MPHOTONS", massPhotons);

  EventVariableOS* mLowDY = new EventVariableOS("MLOWDY", "goodElectrons", "LOWDY");
  mLowDY->addProduct("goodMuons");
  handler->addEventVariable("MLOWDY", mLowDY);

  EventVariableOS* mLowDYlo = new EventVariableOS("MLOWDY", "goodElectronsLowPt", "LOWDYLOWPT");
  mLowDYlo->addProduct("goodMuonsLowPt");
  handler->addEventVariable("MLOWDYLOWPT", mLowDYlo);
  
  EventVariableMT* MT = new EventVariableMT("MT", mZ,"","goodElectrons","goodMuons","");
  handler->addEventVariable("MT",MT);

  EventVariablePairMass* mWdijet = new EventVariablePairMass("WDIJETMASS", "goodJets", "WJET", mW, 10);
  handler->addEventVariable("WDIJETMASS", mWdijet);
  
  EventVariableN* nbJetsCSVM = new EventVariableN("NBJETSCSVM", "bJetsCSVM");
  handler->addEventVariable("NBJETSCSVM", nbJetsCSVM);
  
  EventVariableN* nbJetsCSVL = new EventVariableN("NBJETSCSVL", "bJetsCSVL");
  handler->addEventVariable("NBJETSCSVL", nbJetsCSVL);

  handler->addEventVariable("NGOODRECOVERTICES", new EventVariableN("NGOODRECOVERTICES","goodRecoVertices"));
  
  EventVariableN* nLeptons = new EventVariableN("NLEPTONS", "goodElectrons");
  nLeptons->addProduct("goodMuons");
  nLeptons->addProduct("goodTaus");
  handler->addEventVariable("NLEPTONS", nLeptons);
  
  EventVariableN* nLightLeptons = new EventVariableN("NLIGHTLEPTONS", "goodElectrons");
  nLightLeptons->addProduct("goodMuons");
  handler->addEventVariable("NLIGHTLEPTONS", nLightLeptons);
  
  EventVariableN* nLeptonsLo = new EventVariableN("NLEPTONSLO","goodElectronsLowPt");
  nLeptonsLo->addProduct("goodMuonsLowPt");
  nLeptonsLo->addProduct("goodTaus");
  handler->addEventVariable("NLEPTONSLOWPT",nLeptonsLo);

  EventVariableInRange<int>* el2 = new EventVariableInRange<int>("NGOODELECTRONS", 2, 2, "El2");
  handler->addEventVariable("El2", el2);
  
  EventVariableInRange<int>* dileptons = new EventVariableInRange<int>("NLEPTONS", 2, 1e6, "DILEPTONS");
  handler->addEventVariable("DILEPTONS", dileptons);

  handler->addEventVariable("DILEPTONSLOWPT",new EventVariableInRange<int>("NLEPTONSLOWPT",2,1e6));
  
  EventVariableInRange<int>* threeLightLeptons = new EventVariableInRange<int>("NLIGHTLEPTONS", 3, 3, "THREELIGHTLEPTONS");
  handler->addEventVariable("THREELIGHTLEPTONS", threeLightLeptons);
  
  EventVariableInRange<double>* mLightLeptonsOnZ = new EventVariableInRange<double>("MLIGHTLEPTONS", mZ-zWidth, mZ+zWidth, "MLIGHTLEPTONSONZ");
  handler->addEventVariable("MLIGHTLEPTONSONZ", mLightLeptonsOnZ);

  EventVariableReversed* offZ = new EventVariableReversed("ONZ", "OFFZ");
  handler->addEventVariable("OFFZ", offZ);

  EventVariableInRange<int>* NOSSFgt0 = new EventVariableInRange<int>("NOSSF", 1, 1e6, "NOSSFgt0");
  handler->addEventVariable("NOSSFgt0", NOSSFgt0);

  EventVariableCombined* AIC = new EventVariableCombined("THREELIGHTLEPTONS", "MLIGHTLEPTONSONZ", true, "AIC");
  AIC->addVariable("NOSSFgt0");
  AIC->addVariable("OFFZ");
  handler->addEventVariable("AIC", AIC);
  
  EventVariableInRange<double>* mLowDYcut = new EventVariableInRange<double>("LOWDYOSMINMLL", 12, 1e6, "MLOWDYCUT");
  handler->addEventVariable("MLOWDYCUT", mLowDYcut);

  handler->addEventVariable("MLOWDYCUTLOWPT", new EventVariableInRange<double>("LOWDYLOWPTOSMINMLL",10,1e6));
  
  //EventVariableCombined* writeEvent = new EventVariableCombined("DILEPTONS", "MLOWDYCUT", true, "WRITEEVENT");
  EventVariableCombined* writeEvent = new EventVariableCombined("DILEPTONSLOWPT", "MLOWDYCUTLOWPT", true, "WRITEEVENT");
//  writeEvent->addVariable("NOTTRILEPTONONZ");
  handler->addEventVariable("WRITEEVENT", writeEvent);

  //Trigger
  handler->addObjectVariable("ETA3",new ObjectVariableInRange<double>("ETA",-3.0,3.0,"ETA3"));
  
  handler->addProduct("hltJets","goodJets");
  handler->addProductCut("hltJets","PT40");
  handler->addProductCut("hltJets","ETA3");

  handler->addProduct("hltForwardJets", "goodForwardJets");
  handler->addProductCut("hltForwardJets", "PT40");
  
  EventVariableSumPT* HLT_HT = new EventVariableSumPT("HLT_HT","hltJets");
  HLT_HT->addProduct("hltForwardJets");
  handler->addEventVariable("HLT_HT",HLT_HT);
  
  handler->addObjectVariable("ACCEPT", new ObjectVariableRename<bool>("accept","ACCEPT"));
  handler->addObjectVariable("TRIGGERNAME", new ObjectVariableRename<TString>("triggerName","TRIGGERNAME"));
  
  handler->addProduct("TRIGGERS","ALL");
  handler->addObjectVariable("isTrigger", new ObjectVariableValue<TString>("INPUTTYPE", "trigger"));
  handler->addProductCut("TRIGGERS","isTrigger");
  handler->addHistogram(new SignatureTH1F_TriggerName("TriggerNames","TRIGGERS"));
  
  handler->addObjectVariable("Accepted", new ObjectVariableValue<bool>("ACCEPT", true));
  handler->addObjectVariable("WasRun", new ObjectVariableValue<bool>("wasrun", true));
  
  handler->addProduct("goodtriggers", "TRIGGERS");
  handler->addProductCut("goodtriggers", "Accepted");
  handler->addProductCut("goodtriggers", "WasRun");
  
  handler->addProduct("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1"));
  handler->addProductCut("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1", "isHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1");
  handler->addEventVariable("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1_N", new EventVariableN("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1_N", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1"));
  
  handler->addProduct("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1"));
  handler->addProductCut("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1", "isHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1");
  handler->addEventVariable("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1_N", new EventVariableN("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1_N", "HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1"));

  handler->addProduct("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1"));
  handler->addProductCut("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1", "isHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1");
  handler->addEventVariable("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1_N", new EventVariableN("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1_N", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1"));
  
  handler->addProduct("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  handler->addProductCut("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1", "isHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1");
  handler->addEventVariable("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1_N", new EventVariableN("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1_N", "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  
  handler->addProduct("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  handler->addProductCut("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1", "isHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1");
  handler->addEventVariable("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1_N", new EventVariableN("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1_N", "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1"));
  
  handler->addProduct("HLT_DoubleMu8_Mass8_PFHT300_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_DoubleMu8_Mass8_PFHT300_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_DoubleMu8_Mass8_PFHT300_v1"));
  handler->addProductCut("HLT_DoubleMu8_Mass8_PFHT300_v1", "isHLT_DoubleMu8_Mass8_PFHT300_v1");
  handler->addEventVariable("HLT_DoubleMu8_Mass8_PFHT300_v1_N", new EventVariableN("HLT_DoubleMu8_Mass8_PFHT300_v1_N", "HLT_DoubleMu8_Mass8_PFHT300_v1"));
  
  handler->addProduct("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));
  handler->addProductCut("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1", "isHLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1");
  handler->addEventVariable("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1_N", new EventVariableN("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1_N", "HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));
  
  handler->addProduct("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));
  handler->addProductCut("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1", "isHLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1");
  handler->addEventVariable("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1_N", new EventVariableN("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1_N", "HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1"));

  handler->addProduct("HLT_TripleMu_12_10_5_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_TripleMu_12_10_5_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_TripleMu_12_10_5_v1"));
  handler->addProductCut("HLT_TripleMu_12_10_5_v1", "isHLT_TripleMu_12_10_5_v1");
  handler->addEventVariable("HLT_TripleMu_12_10_5_v1_N", new EventVariableN("HLT_TripleMu_12_10_5_v1_N", "HLT_TripleMu_12_10_5_v1"));

  handler->addProduct("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1"));
  handler->addProductCut("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1", "isHLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1");
  handler->addEventVariable("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1_N", new EventVariableN("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1_N", "HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1"));

  handler->addProduct("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1"));
  handler->addProductCut("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1", "isHLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1");
  handler->addEventVariable("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1_N", new EventVariableN("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1_N", "HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1"));
  
  handler->addProduct("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1", "goodtriggers");
  handler->addObjectVariable("isHLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1", new ObjectVariableValue<TString>("TRIGGERNAME", "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1"));
  handler->addProductCut("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1", "isHLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1");
  handler->addEventVariable("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1_N", new EventVariableN("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1_N", "HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1"));

  EventVariableThreshold* dieltrig = new EventVariableThreshold("dieltrig","goodElectrons");
  dieltrig->addThreshold(26);
  dieltrig->addThreshold(15);
  handler->addEventVariable("DIELTRIGTHRESHOLD",dieltrig);

  EventVariableThreshold* dimutrig = new EventVariableThreshold("dimutrig","goodMuons");
  dimutrig->addThreshold(17);
  dimutrig->addThreshold(8);
  handler->addEventVariable("DIMUTRIGTHRESHOLD",dimutrig);

  EventVariableThreshold* ellead = new EventVariableThreshold("ellead","goodElectrons");
  ellead->addThreshold(28);
  handler->addEventVariable("EGMULEADTHRESHOLD",ellead);

  EventVariableThreshold* elsublead = new EventVariableThreshold("elsublead","goodElectrons");
  elsublead->addThreshold(18);
  handler->addEventVariable("MUEGSUBLEADTHRESHOLD",elsublead);

  EventVariableThreshold* mulead = new EventVariableThreshold("mulead","goodMuons");
  mulead->addThreshold(24);
  handler->addEventVariable("MUEGLEADTHRESHOLD",mulead);

  EventVariableThreshold* musublead = new EventVariableThreshold("musublead","goodMuons");
  musublead->addThreshold(8);
  handler->addEventVariable("EGMUSUBLEADTHRESHOLD",musublead);

  handler->addEventVariable("MUEGTHRESHOLD",new EventVariableCombined("MUEGLEADTHRESHOLD","MUEGSUBLEADTHRESHOLD",true));
  handler->addEventVariable("EGMUTHRESHOLD",new EventVariableCombined("EGMULEADTHRESHOLD","EGMUSUBLEADTHRESHOLD",true));

  handler->addEventVariable("MUEGCOMBINEDTHRESHOLD", new EventVariableCombined("MUEGTHRESHOLD","EGMUTHRESHOLD"));

  EventVariableThreshold* tauthresh = new EventVariableThreshold("tauthresh","goodTaus");
  tauthresh->addThreshold(25);
  handler->addEventVariable("TAUTHRESH",tauthresh);

  EventVariableThreshold* eltauthresh = new EventVariableThreshold("eltauthresh","goodElectrons");
  eltauthresh->addThreshold(25);
  handler->addEventVariable("ELTAUTHRESH",eltauthresh);

  handler->addEventVariable("ELTAUTHRESHOLD",new EventVariableCombined("ELTAUTHRESH","TAUTHRESH",true));

  handler->addEventVariable("MUTAUTHRESHOLD",new EventVariableCombined("MUEGLEADTHRESHOLD","TAUTHRESH",true));

  EventVariableThreshold* trimu = new EventVariableThreshold("trimuthresh","goodMuons");
  trimu->addThreshold(13);
  trimu->addThreshold(10);
  trimu->addThreshold(8);
  handler->addEventVariable("TRIMUTHRESHOLD",trimu);

  EventVariableThreshold* triel = new EventVariableThreshold("trielthresh","goodElectrons");
  triel->addThreshold(25);
  triel->addThreshold(18);
  triel->addThreshold(15);
  handler->addEventVariable("TRIELTHRESHOLD",triel);

  EventVariableThreshold* diel = new EventVariableThreshold("diel","goodElectrons");
  diel->addThreshold(20);
  diel->addThreshold(13);
  handler->addEventVariable("DIELTHRESHOLD_FORTRI",diel);

  EventVariableThreshold* mu10 = new EventVariableThreshold("mu10","goodMuons");
  mu10->addThreshold(9);
  handler->addEventVariable("MU11THRESHOLD_FORTRI",mu10);

  EventVariableThreshold* dimu = new EventVariableThreshold("dimu","goodMuons");
  dimu->addThreshold(10);
  dimu->addThreshold(10);
  handler->addEventVariable("DIMUTHRESHOLD_FORTRI",dimu);

  EventVariableThreshold* el12 = new EventVariableThreshold("el12","goodElectrons");
  el12->addThreshold(15);
  handler->addEventVariable("EL12THRESHOLD_FORTRI",el12);

  EventVariableCombined* Mu1El2Threshold = new EventVariableCombined("MU11THRESHOLD_FORTRI","DIELTHRESHOLD_FORTRI",true,"Mu1El2Threshold");
  handler->addEventVariable("MU1EL2THRESHOLD",Mu1El2Threshold);

  EventVariableCombined* Mu2El1Threshold = new EventVariableCombined("EL12THRESHOLD_FORTRI","DIMUTHRESHOLD_FORTRI",true,"Mu2El1Threshold");
  handler->addEventVariable("MU2EL1THRESHOLD",Mu2El1Threshold);


  EventVariableCombined* bestTriLepThresh = new EventVariableCombined("TRIMUTHRESHOLD","TRIELTHRESHOLD",false,"TRILEPTHRESH");
  bestTriLepThresh->addVariable("MU1EL2THRESHOLD");
  bestTriLepThresh->addVariable("MU2EL1THRESHOLD");
  handler->addEventVariable("TRILEPTHRESHOLD",bestTriLepThresh);


  handler->addEventVariable("HLTHT300",new EventVariableInRange<double>("HLT_HT",300,1000000));

  EventVariableThreshold* dieltright = new EventVariableThreshold("dieltrig","goodElectrons");
  dieltright->addThreshold(28);
  dieltright->addThreshold(17);
  handler->addEventVariable("DIELHTTRIGTHRESHOLD",dieltright);

  EventVariableThreshold* dimutright = new EventVariableThreshold("dimutrig","goodMuons");
  dimutright->addThreshold(10);
  dimutright->addThreshold(8);
  handler->addEventVariable("DIMUHTTRIGTHRESHOLD",dimutright);

  EventVariableThreshold* elleadht = new EventVariableThreshold("ellead","goodElectrons");
  elleadht->addThreshold(18);
  handler->addEventVariable("MUEG_ELHTTHRESHOLD",elleadht);

  EventVariableThreshold* muleadht = new EventVariableThreshold("mulead","goodMuons");
  muleadht->addThreshold(8);
  handler->addEventVariable("MUEG_MUHTTHRESHOLD",muleadht);

  handler->addEventVariable("MUEGHTTHRESHOLD",new EventVariableCombined("MUEG_MUHTTHRESHOLD","MUEG_EGHTTHRESHOLD",true));

  handler->addEventVariable("PASSMUEGHTTRIG",new EventVariableCombined("MUEGHTTHRESHOLD","HLTHT300",true));
  handler->addEventVariable("PASSDIMUHTTRIG",new EventVariableCombined("DIMUHTTRIGTHRESHOLD","HLTHT300",true));
  handler->addEventVariable("PASSDIELHTTRIG",new EventVariableCombined("DIELHTTRIGTHRESHOLD","HLTHT300",true));

  /*
  if(isMC){
    handler->addEventVariable("WRITEEVENT", new EventVariableInRange<int>("N_bosons",0,10000));
  }else{
    handler->addEventVariable("WRITEEVENT", new EventVariableRename<bool>("ALWAYSTRUE"));
  }
  */

}

void setupTriggers(BaseHandler* handler,int mode){
if(mode > 0) {
  ObjectVariableValueInList<TString>* isDoubleMuTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v1");
  isDoubleMuTrigger->addValue("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v1");
  isDoubleMuTrigger->addValue("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2");
  isDoubleMuTrigger->addValue("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2");
  handler->addObjectVariable("isDoubleMuTrigger",isDoubleMuTrigger);

  ObjectVariableValueInList<TString>* isDoubleEGTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v1");
  isDoubleEGTrigger->addValue("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v2");
  handler->addObjectVariable("isDoubleEGTrigger",isDoubleEGTrigger);

  ObjectVariableValueInList<TString>* isMuEGTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v1");
  isMuEGTrigger->addValue("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v1");
  isMuEGTrigger->addValue("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v2");
  isMuEGTrigger->addValue("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v2");
  handler->addObjectVariable("isMuEGTrigger",isMuEGTrigger);

  ObjectVariableValueInList<TString>* isDoubleMuHTTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_DoubleMu8_Mass8_PFHT300_v1");
  isDoubleMuHTTrigger->addValue("HLT_DoubleMu8_Mass8_PFHT300_v2");
  handler->addObjectVariable("isDoubleMuHTTrigger",isDoubleMuHTTrigger);

  ObjectVariableValueInList<TString>* isDoubleEGHTTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v1");
  isDoubleEGHTTrigger->addValue("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v2");
  handler->addObjectVariable("isDoubleEGHTTrigger",isDoubleEGHTTrigger);

  ObjectVariableValueInList<TString>* isMuEGHTTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v1");
  isMuEGHTTrigger->addValue("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v2");
  handler->addObjectVariable("isMuEGHTTrigger",isMuEGHTTrigger);

  ObjectVariableValueInList<TString>* isTriMuTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_TripleMu_12_10_5_v1");
  handler->addObjectVariable("isTriMuTrigger",isTriMuTrigger);

  ObjectVariableValueInList<TString>* isDiMuElTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v1");
  isDiMuElTrigger->addValue("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v2");
  handler->addObjectVariable("isDiMuElTrigger",isDiMuElTrigger);

  ObjectVariableValueInList<TString>* isMuDiElTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v1");
  isMuDiElTrigger->addValue("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v2");
  handler->addObjectVariable("isMuDiElTrigger",isMuDiElTrigger);

  ObjectVariableValueInList<TString>* isTriElTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v1");
  isTriElTrigger->addValue("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v2");
  handler->addObjectVariable("isTriElTrigger",isTriElTrigger);

  ObjectVariableValueInList<TString>* isHTTrigger = new ObjectVariableValueInList<TString>("TRIGGERNAME","HLT_PFHT800_v1");
  handler->addObjectVariable("isHTTrigger",isHTTrigger);

  vector<TString> triggers;
  triggers.push_back("DoubleMuTrigger");
  triggers.push_back("DoubleEGTrigger");
  triggers.push_back("MuEGTrigger");
  triggers.push_back("DoubleMuHTTrigger");
  triggers.push_back("DoubleEGHTTrigger");
  triggers.push_back("MuEGHTTrigger");
  triggers.push_back("TriMuTrigger");
  triggers.push_back("DiMuElTrigger");
  triggers.push_back("MuDiElTrigger");
  triggers.push_back("TriElTrigger");
  triggers.push_back("HTTrigger");

  vector<TString> thresholds;
  thresholds.push_back("DIMUTRIGTHRESHOLD");
  thresholds.push_back("DIELTRIGTHRESHOLD");
  thresholds.push_back("MUEGCOMBINEDTHRESHOLD");
  thresholds.push_back("PASSDIMUHTTRIG");
  thresholds.push_back("PASSDIELHTTRIG");
  thresholds.push_back("PASSMUEGHTTRIG");
  thresholds.push_back("TRIMUTHRESHOLD");
  thresholds.push_back("MU2El1THRESHOLD");
  thresholds.push_back("MU1EL2THRESHOLD");
  thresholds.push_back("TRIELTHRESHOLD");
  thresholds.push_back("ALWAYSTRUE");

  for(int i = 0; i < (int) triggers.size(); i++){
    TString trigger = triggers[i];
    handler->addProduct(trigger,"goodtriggers");
    handler->addProductCut(trigger,TString::Format("is%s",trigger.Data()));
    TString nname = TString::Format("N%s",trigger.Data());
    handler->addEventVariable(nname,new EventVariableN(nname,trigger));
    TString nnamege1  = TString::Format("N%sgt0",trigger.Data());
    handler->addEventVariable(nnamege1,new EventVariableInRange<int>(nname,1,100000));
    TString acceptname = TString::Format("ACCEPT_%s",trigger.Data());
    handler->addEventVariable(acceptname,new EventVariableCombined(thresholds[i],nnamege1,true));
    TString nacceptname = TString::Format("REJECT_%s",trigger.Data());
    handler->addEventVariable(nacceptname,new EventVariableReversed(acceptname));
  }
}
  EventVariableCombined* trigaccept = NULL;
  switch(mode){
  case 1:
    handler->addEventVariable("TRIGGERACCEPT",new EventVariableRename<bool>("ACCEPT_MuEGTrigger"));
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("MUEG")));
    break;
  case 2:
    handler->addEventVariable("TRIGGERACCEPT",new EventVariableCombined("ACCEPT_DoubleMuTrigger","REJECT_MuEGTrigger",true));
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("DOUBLEMU")));
    break;
  case 3:
    trigaccept = new EventVariableCombined("ACCEPT_DoubleEGTrigger","REJECT_DoubleMuTrigger",true);
    trigaccept->addVariable("REJECT_MuEGTrigger");
    handler->addEventVariable("TRIGGERACCEPT",trigaccept);
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("DOUBLEEG")));
    break;
  default:
    trigaccept = new EventVariableCombined("DIMUTRIGTHRESHOLD","DIELTRIGTHRESHOLD");
    trigaccept->addVariable("MUEGCOMBINEDTHRESHOLD");
    handler->addEventVariable("TRIGGERACCEPT",trigaccept);
    handler->addEventVariable("DATASET",new EventVariableConst<TString>(TString("DEFAULT")));
    break;
  }

}

void setupMCproducts(BaseHandler* handler) {
	handler->addObjectVariable("isMC",new ObjectVariableValue<TString>("INPUTTYPE","mc"));

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
	handler->addObjectVariable("MOTHERZ",new ObjectVariableValue<int>("motherpdgId",23));
	ObjectVariableValueInList<int>* motherBoson = new ObjectVariableValueInList<int>("motherpdgId",23);
	motherBoson->addValue(24);
	motherBoson->addValue(-24);
	motherBoson->addValue(25);
	handler->addObjectVariable("MOTHERBOSON",motherBoson);

	ObjectVariableValueInList<int>* motherTau = new ObjectVariableValueInList<int>("motherpdgId",15);
	motherTau->addValue(-15);
	handler->addObjectVariable("MOTHERTAU",motherTau);

	ObjectVariableValueInList<int>* isBoson = new ObjectVariableValueInList<int>("pdgId",23);
	isBoson->addValue(24);
	isBoson->addValue(-24);
	isBoson->addValue(25);
	handler->addObjectVariable("isBOSON",isBoson);


	handler->addProduct("BOSONS","ALLMC");
	handler->addProductCut("BOSONS","isBOSON");

	handler->addProduct("MCELECTRONS","ALLMC");
	handler->addProductCut("MCELECTRONS","ELECTRONPDGID");
	handler->addProduct("MCMUONS","ALLMC");
	handler->addProductCut("MCMUONS","MUONPDGID");
	handler->addProduct("MCTAUS","ALLMC");
	handler->addProductCut("MCTAUS","TAUPDGID");

	handler->addProduct("MCELECTRONSFROMZ","MCELECTRONS");
	handler->addProductCut("MCELECTRONSFROMZ","MOTHERZ");
	handler->addProduct("MCMUONSFROMZ","MCMUONS");
	handler->addProductCut("MCMUONSFROMZ","MOTHERZ");

	handler->addProduct("MCELECTRONSFROMBOSON","MCELECTRONS");
	handler->addProductCut("MCELECTRONSFROMBOSON","MOTHERBOSON");
	handler->addProduct("MCMUONSFROMBOSON","MCMUONS");
	handler->addProductCut("MCMUONSFROMBOSON","MOTHERBOSON");
	handler->addProduct("MCTAUSFROMBOSON","MCTAUS");
	handler->addProductCut("MCTAUSFROMBOSON","MOTHERBOSON");

	handler->addProduct("MCELECTRONSFROMTAU","MCELECTRONS");
	handler->addProductCut("MCELECTRONSFROMTAU","MOTHERTAU");
	handler->addProduct("MCMUONSFROMTAU","MCMUONS");
	handler->addProductCut("MCMUONSFROMTAU","MOTHERTAU");
}

void setupMCvariables(BaseHandler* handler) {
	////////////////////////
	///MC matched leptons///
	////////////////////////
	handler->addProduct("goodElectronsMatched","goodElectrons");
	handler->addProduct("goodMuonsMatched","goodMuons");

	handler->addProduct("goodElectronsFromTau","goodElectrons");
	handler->addProduct("goodMuonsFromTau","goodMuons");

	handler->addProduct("goodElectronsNotMatched","goodElectrons");
	handler->addProduct("goodMuonsNotMatched","goodMuons");


	ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
	ObjectComparisonMatchDeltaRCharge* mcMatch = new ObjectComparisonMatchDeltaRCharge(0.1,"genParticle");

	handler->addProductComparison("goodElectronsMatched","MCELECTRONSFROMBOSON",mcMatch,false);
	handler->addProductComparison("goodMuonsMatched","MCMUONSFROMBOSON",mcMatch,false);
	handler->addProductComparison("goodElectronsFromTau","MCELECTRONSFROMTAU",mcMatch,false);
	handler->addProductComparison("goodMuonsFromTau","MCMUONSFROMTAU",mcMatch,false);

	handler->addProductComparison("goodElectronsNotMatched","goodElectronsMatched",deltaR0p1);
	handler->addProductComparison("goodElectronsNotMatched","goodElectronsFromTau",deltaR0p1);
	handler->addProductComparison("goodMuonsNotMatched","goodMuonsMatched",deltaR0p1);
	handler->addProductComparison("goodMuonsNotMatched","goodMuonsFromTau",deltaR0p1);

	//handler->addProductComparison("basicJetsNoCleaning","MCELECTRONSFROMBOSON",deltaR0p4);
	//handler->addProductComparison("basicJetsNoCleaning","MCMUONSFROMBOSON",deltaR0p4);

	handler->addProduct("MCMUONSFROMZPOS","MCMUONSFROMZ");
	handler->addProductCut("MCMUONSFROMZPOS","POSITIVE");
	handler->addProduct("MCMUONSFROMZNEG","MCMUONSFROMZ");
	handler->addProductCut("MCMUONSFROMZNEG","NEGATIVE");

	handler->addProduct("MCELECTRONSFROMZPOS","MCELECTRONSFROMZ");
	handler->addProductCut("MCELECTRONSFROMZPOS","POSITIVE");
	handler->addProduct("MCELECTRONSFROMZNEG","MCELECTRONSFROMZ");
	handler->addProductCut("MCELECTRONSFROMZNEG","NEGATIVE");

	handler->addEventVariable("N_McMuonsFromZ", new EventVariableN("N_McMuonsFromZ","MCMUONSFROMZ"));
	handler->addEventVariable("N_McElectronsFromZ", new EventVariableN("N_McElectronsFromZ","MCELECTRONSFROMZ"));

	handler->addEventVariable("N_McTausFromBoson", new EventVariableN("N_McTausFromBoson","MCTAUSFROMBOSON"));
	handler->addEventVariable("N_McMuonsFromBoson", new EventVariableN("N_McMuonsFromBoson","MCMUONSFROMBOSON"));
	handler->addEventVariable("N_McElectronsFromBoson", new EventVariableN("N_McElectronsFromBoson","MCELECTRONSFROMBOSON"));

	handler->addEventVariable("twoMcMuonsFromZ", new EventVariableValue<int>("N_McMuonsFromZ",2));
	handler->addEventVariable("twoMcElectronsFromZ", new EventVariableValue<int>("N_McElectronsFromZ",2));

	handler->addEventVariable("N_bosons", new EventVariableN("N_bosons","BOSONS"));

	EventVariablePairMass* mumcmass = new EventVariablePairMass("MUMCMASS","MCMUONSFROMZ","MUMC_",91,15);
	handler->addEventVariable("MUMCMASS",mumcmass);
	EventVariablePairMass* elmcmass = new EventVariablePairMass("ELMCMASS","MCELECTRONSFROMZ","ELMC_",91,15);
	handler->addEventVariable("ELMCMASS",elmcmass);

	handler->addEventVariable("MAXGENDXY",new EventVariableObjectVariableExtreme<double>("genDxy","ALLMC"));

	handler->addEventVariable("MCMUPLUSPT",new  EventVariableObjectVariableExtreme<double>("PT","MCMUONSFROMZPOS"));
	handler->addEventVariable("MCMUMINUSPT",new  EventVariableObjectVariableExtreme<double>("PT","MCMUONSFROMZNEG"));
	handler->addEventVariable("MCELPLUSPT",new  EventVariableObjectVariableExtreme<double>("PT","MCELECTRONSFROMZPOS"));
	handler->addEventVariable("MCELMINUSPT",new  EventVariableObjectVariableExtreme<double>("PT","MCELECTRONSFROMZNEG"));

	TF1* flatWeight = new TF1("flat","1",0,10000000);
	handler->addEventVariable("FLATWEIGHT",new EventVariableTF1<int>("FLATWEIGHT","RUN",flatWeight));
	handler->addWeightVariable("FLATWEIGHT");

}

