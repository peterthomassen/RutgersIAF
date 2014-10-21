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
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRename.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F_EventVariableVsEventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F_ObjectVariableVsObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_NearestVertexRank.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableMax.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableGenVertexR.h"
#include "RutgersIAF/EventAnalyzer/interface/PrintModuleProduct.h"

void setupProducts(BaseHandler* handler)
{
  handler->addObjectVariable("isPhoton",new ObjectVariableValue<TString>("INPUTTYPE","photon"));
  handler->addObjectVariable("isMC",new ObjectVariableValue<TString>("INPUTTYPE","mc"));
  handler->addObjectVariable("isVertex",new ObjectVariableValue<TString>("INPUTTYPE","vertex"));
  handler->addObjectVariable("isMET", new ObjectVariableValue<TString>("INPUTTYPE","met"));

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

  handler->addProduct("ALLMC","ALL");
  handler->addProductCut("ALLMC","isMC");

  handler->addProduct("ALLVERTICES","ALL");
  handler->addProductCut("ALLVERTICES","isVertex");
  handler->addProduct("ALLRECOVERTICES","ALLVERTICES");

  handler->addProduct("ALLMET","ALL");
  handler->addProductCut("ALLMET","isMET");

  handler->addProduct("MET","ALLMET");


  ///Some variables///

  handler->addObjectVariable("ETA",new ObjectVariableMethod("ETA", &SignatureObject::Eta));
  handler->addObjectVariable("ETA2p3",new ObjectVariableInRange<double>("ETA",-2.3,2.3,"ETA2p3"));
  handler->addObjectVariable("ETA2p4",new ObjectVariableInRange<double>("ETA",-2.4,2.4));
  handler->addObjectVariable("ETA2p5",new ObjectVariableInRange<double>("ETA",-2.5,2.5,"ETA2p5"));
  handler->addObjectVariable("BARREL",new ObjectVariableInRange<double>("ETA",-1.5,1.5,"barrelEta"));
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

  ////////////////////
  ///Muon Variables///
  ////////////////////

  handler->addObjectVariable("MUON_normalizedChi2",new ObjectVariableInRange<double>("normalizedChi2",0,10));
  handler->addObjectVariable("MUON_numberOfValidMuonHits", new ObjectVariableInRange<int>("numberOfValidMuonHits",1,100000));
  handler->addObjectVariable("MUON_numberOfMatchedStations",new ObjectVariableInRange<int>("numberOfMatchedStations",2,1000000));
  handler->addObjectVariable("MUON_dxy", new ObjectVariableInRange<double>("dxy",-0.02,0.02));
  handler->addObjectVariable("MUON_nonprompt", new ObjectVariableReversed("MUON_dxy","MUON_nonprompt"));
  handler->addObjectVariable("MUON_dz", new ObjectVariableInRange<double>("dz",-0.5,0.5));
  handler->addObjectVariable("MUON_numberOfValidPixelHits", new ObjectVariableInRange<int>("numberOfValidPixelHits",1,1000000));
  handler->addObjectVariable("MUON_trackerLayersWithMeasurement", new ObjectVariableInRange<int>("trackerLayersWithMeasurement",6,1000000));
  handler->addObjectVariable("MUON_PFCHARGEDHADRONISO", new ObjectVariableRename<double>("pfIsolationR03sumChargedHadronPt","PF_CHARGEDHADRONISO"),false);
  handler->addObjectVariable("MUON_PFNEUTRALHADRONISO", new ObjectVariableRename<double>("pfIsolationR03sumNeutralHadronEt","PF_NEUTRALHADRONISO"),false);
  handler->addObjectVariable("MUON_PFPHOTONISO", new ObjectVariableRename<double>("pfIsolationR03sumPhotonEt","PF_PHOTONISO"),false);
  handler->addObjectVariable("MUON_BETA", new ObjectVariableRename<double>("pfIsolationR03sumPUPt","BETA"),false);

  ////////////////////////
  ///Electron Variables///
  ////////////////////////
  handler->addObjectVariable("ELECTRON_PFCHARGEDHADRONISO", new ObjectVariableRename<double>("sumChargedHadronPt","PF_CHARGEDHADRONISO"),false);
  handler->addObjectVariable("ELECTRON_PFNEUTRALHADRONISO", new ObjectVariableRename<double>("sumNeutralHadronEt","PF_NEUTRALHADRONISO"),false);
  handler->addObjectVariable("ELECTRON_PFPHOTONISO", new ObjectVariableRename<double>("sumPhotonEt","PF_PHOTONISO"),false);
  handler->addObjectVariable("ELECTRON_BETA", new ObjectVariableRename<double>("sumPUPt","BETA"),false);
  handler->addObjectVariable("ELECTRON_INGAPPOS",new ObjectVariableInRange<double>("superClustereta",1.4442,1.566));
  handler->addObjectVariable("ELECTRON_INGAPNEG",new ObjectVariableInRange<double>("superClustereta",-1.566,-1.4442));
  ObjectVariableCombined* electron_ingap = new ObjectVariableCombined("ELECTRON_INGAPPOS","ELECTRON_INGAPNEG",false,"ELECTORN_INGAP");
  handler->addObjectVariable("ELECTRON_INGAP",electron_ingap);
  handler->addObjectVariable("ELECTRON_NOTGAP",new ObjectVariableReversed("ELECTRON_INGAP","ELECTRON_NOTGAP"));
  handler->addObjectVariable("ELECTRON_BARREL_deltaEtaSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.0181,0.0181));
  handler->addObjectVariable("ELECTRON_BARREL_deltaPhiSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.0936,0.0936));
  handler->addObjectVariable("ELECTRON_ENDCAP_deltaEtaSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.0124,0.0124));
  handler->addObjectVariable("ELECTRON_ENDCAP_deltaPhiSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.0642,0.0642));
  handler->addObjectVariable("ELECTRON_BARREL_hadronicOverEm",new ObjectVariableInRange<double>("hadronicOverEm",0.0,0.141));
  handler->addObjectVariable("ELECTRON_ENDCAP_hadronicOverEm",new ObjectVariableInRange<double>("hadronicOverEm",0.0,0.1115));
  handler->addObjectVariable("ELECTRON_BARREL_sigmaIetaIeta",new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.0123));
  handler->addObjectVariable("ELECTRON_ENDCAP_sigmaIetaIeta",new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.035));
  handler->addObjectVariable("ELECTRON_BARREL_1oEm1oP", new ObjectVariableInRange<double>("1oEm1oP",0,0.1353));
  handler->addObjectVariable("ELECTRON_ENDCAP_1oEm1oP", new ObjectVariableInRange<double>("1oEm1oP",0,0.1443));
  handler->addObjectVariable("ELECTRON_passConversionVeto",new ObjectVariableValue<bool>("passConversionVeto",true));
  handler->addObjectVariable("ELECTRON_BARREL_dz", new ObjectVariableInRange<double>("dz",-0.54342,0.54342));
  handler->addObjectVariable("ELECTRON_BARREL_dxy", new ObjectVariableInRange<double>("dxy",-0.0166,0.0166));
  handler->addObjectVariable("ELECTRON_ENDCAP_dz", new ObjectVariableInRange<double>("dz",-0.9187,0.9187));
  handler->addObjectVariable("ELECTRON_ENDCAP_dxy", new ObjectVariableInRange<double>("dxy",-0.098,0.098));
  handler->addObjectVariable("ELECTRON_dz5", new ObjectVariableInRange<double>("dz",-5.0,5.0));

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
  handler->addObjectVariable("LEPTON_totalIso", new ObjectVariableMuonTotalIso("TOTALISO"),false);
  handler->addObjectVariable("RELISO",new ObjectVariableRelIso("RELISO"));
  handler->addObjectVariable("IREL0p15",new ObjectVariableInRange<double>("RELISO",0,0.15,"IREL0p15"));
  handler->addObjectVariable("NOTIREL0p15", new ObjectVariableReversed("IREL0p15"));
  handler->addObjectVariable("IREL0p23",new ObjectVariableInRange<double>("RELISO",0,0.23,"IREL0p23"));
  handler->addObjectVariable("IREL0p24",new ObjectVariableInRange<double>("RELISO",0,0.24,"IREL0p24"));
  handler->addObjectVariable("NOTIREL0p24", new ObjectVariableReversed("IREL0p24"));
  handler->addObjectVariable("IREL0p25",new ObjectVariableInRange<double>("RELISO",0,0.25,"IREL0p25"));
  handler->addObjectVariable("IREL0p30",new ObjectVariableInRange<double>("RELISO",0,0.30,"IREL0p30"));
  handler->addObjectVariable("IREL0p35",new ObjectVariableInRange<double>("RELISO",0,0.3529,"IREL0p35"));


  ObjectVariableCombined* electron_barrel = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_hadronicOverEm",true,"electron_barrel_good");
  electron_barrel->addVariable("ELECTRON_BARREL_sigmaIetaIeta");
  electron_barrel->addVariable("ELECTRON_BARREL_deltaPhiSuperClusterTrackAtVtx");
  electron_barrel->addVariable("ELECTRON_BARREL_deltaEtaSuperClusterTrackAtVtx");
  electron_barrel->addVariable("ELECTRON_BARREL_dz");
  //electron_barrel->addVariable("ELECTRON_BARREL_dxy");
  electron_barrel->addVariable("ELECTRON_BARREL_1oEm1oP");
  //electron_barrel->addVariable("IREL0p24");
  handler->addObjectVariable("ELECTRON_BARREL",electron_barrel);

  ObjectVariableCombined* electron_endcap = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_hadronicOverEm",true,"electron_endcap_good");
  electron_endcap->addVariable("ELECTRON_ENDCAP_sigmaIetaIeta");
  electron_endcap->addVariable("ELECTRON_ENDCAP_deltaPhiSuperClusterTrackAtVtx");
  electron_endcap->addVariable("ELECTRON_ENDCAP_deltaEtaSuperClusterTrackAtVtx");
  electron_endcap->addVariable("ELECTRON_ENDCAP_dz");
  //electron_endcap->addVariable("ELECTRON_ENDCAP_dxy");
  electron_endcap->addVariable("ELECTRON_ENDCAP_1oEm1oP");
  //electron_endcap->addVariable("IREL0p35");
  handler->addObjectVariable("ELECTRON_ENDCAP",electron_endcap);

  handler->addObjectVariable("ELECTRON_COMBINED",new ObjectVariableCombined("ELECTRON_BARREL","ELECTRON_ENDCAP",false,"ELECTRON_COMBINED"));

  ObjectVariableCombined* electron_barrel_isolated = new ObjectVariableCombined("BARREL","IREL0p24",true,"electron_barrel_isolated");
  ObjectVariableCombined* electron_endcap_isolated = new ObjectVariableCombined("ENDCAP","IREL0p35",true,"electron_endcap_isolated");
  ObjectVariableCombined* electron_isolated = new ObjectVariableCombined("ELECTRON_BARREL_ISOLATED","ELECTRON_ENDCAP_ISOLATED",false,"ELECTRON_ISOLATED");
  handler->addObjectVariable("ELECTRON_BARREL_ISOLATED",electron_barrel_isolated);
  handler->addObjectVariable("ELECTRON_ENDCAP_ISOLATED",electron_endcap_isolated);
  handler->addObjectVariable("ELECTRON_ISOLATED",electron_isolated);
  handler->addObjectVariable("ELECTORN_NOTISOLATED",new ObjectVariableReversed("ELECTRON_ISOLATED"));

  ObjectVariableCombined* electron_barrel_prompt = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_DXY",true,"electron_barrel_prompt");
  ObjectVariableCombined* electron_endcap_prompt = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_DXY",true,"electron_endcap_prompt");
  ObjectVariableCombined* electron_prompt = new ObjectVariableCombined("ELECTRON_BARREL_PROMPT","ELECTRON_ENDCAP_PROMPT",false,"ELECTRON_PROMPT");
  handler->addObjectVariable("ELECTRON_BARREL_PROMPT",electron_barrel_prompt);
  handler->addObjectVariable("ELECTRON_ENDCAP_PROMPT",electron_endcap_prompt);
  handler->addObjectVariable("ELECTRON_PROMPT",electron_prompt);
  handler->addObjectVariable("ELECTORN_NONPROMPT",new ObjectVariableReversed("ELECTRON_PROMPT"));




  ObjectVariableCombined* electron_good = new ObjectVariableCombined("ELECTRON_COMBINED","PT10",true,"ELECTRON_GOOD");
  electron_good->addVariable("ETA2p4");
  electron_good->addVariable("ELECTRON_passConversionVeto");
  electron_good->addVariable("ELECTRON_NOTGAP");
  electron_good->addVariable("ELECTRON_ISOLATED");
  electron_good->addVariable("ELECTRON_PROMPT");
  //electron_good->addVariable("ELECTRON_1oEm1oP");

  handler->addObjectVariable("ELECTRON_GOOD",electron_good);

  //////////////////
  ///Muon Product///
  //////////////////

  handler->addProduct("basicMuons","ALLMUONS");
  handler->addProductCut("basicMuons","PT10");
  handler->addProductCut("basicMuons","ETA2p4");
  handler->addProductCut("basicMuons","isGlobalMuon");
  handler->addProductCut("basicMuons","isPFMuon");
  handler->addProductCut("basicMuons","MUON_normalizedChi2");
  handler->addProductCut("basicMuons","MUON_numberOfValidMuonHits");
  handler->addProductCut("basicMuons","MUON_numberOfMatchedStations");
  handler->addProductCut("basicMuons","MUON_dz");
  handler->addProductCut("basicMuons","MUON_numberOfValidPixelHits");
  handler->addProductCut("basicMuons","MUON_trackerLayersWithMeasurement");

  handler->addProduct("goodMuons","basicMuons");
  handler->addProductCut("goodMuons","IREL0p15");
  handler->addProductCut("goodMuons","MUON_dxy");

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

  handler->addProduct("basicElectrons","ALLELECTRONS");
  handler->addProductCut("basicElectrons","PT10");
  handler->addProductCut("basicElectrons","ETA2p4");
  //handler->addProductCut("goodElectrons","IREL0p23");
  handler->addProductCut("basicElectrons","ELECTRON_COMBINED");
  //handler->addProductCut("goodElectrons","ELECTRON_dxy");
  handler->addProductCut("basicElectrons","ELECTRON_passConversionVeto");
  //handler->addProductCut("goodElectrons","ELECTRON_dz");
  handler->addProductCut("basicElectrons","ELECTRON_NOTGAP");
  //handler->addProductCut("goodElectrons","ELECTRON_1oEm1oP");

  handler->addProduct("goodElectrons","basicElectrons");
  handler->addProductCut("goodElectrons","ELECTRON_ISOLATED");
  handler->addProductCut("goodElectrons","ELECTRON_PROMPT");

  handler->addProduct("isoNonPromptElectrons","basicElectrons");
  handler->addProductCut("isoNonPromptElectrons","ELECTRON_ISOLATED");
  handler->addProductCut("isoNonPromptElectrons","ELECTRON_NONPROMPT");
  
  handler->addProduct("promptNonIsoElectrons","basicElectrons");
  handler->addProductCut("promptNonIsoElectrons","ELECTRON_NOTISOLATED");
  handler->addProductCut("promptNonIsoElectrons","ELECTRON_PROMPT");
  
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
  handler->addObjectVariable("TAU_againstElectronTight3",new ObjectVariableValue<double>("againstElectronTightMVA3",1.0));
  handler->addObjectVariable("TAU_againstMuonTight3",new ObjectVariableValue<double>("againstMuonTight3",1.0));
  handler->addObjectVariable("TAU_isoLoose", new ObjectVariableValue<double>("byLooseCombinedIsolationDeltaBetaCorr3Hits",1.0));
  handler->addObjectVariable("TAU_nonIso", new ObjectVariableReversed("TAU_isoLoose"));

  handler->addProduct("basicTaus","ALLTAUS");
  handler->addProductCut("basicTaus","PT20");
  handler->addProductCut("basicTaus","ETA2p3");
  handler->addProductCut("basicTaus","TAU_againstElectronTight3");
  handler->addProductCut("basicTaus","TAU_againstMuontTight3");

  handler->addProduct("goodTaus","basicTaus");
  handler->addProductCut("goodTaus","TAU_isoLoose"); 

  handler->addProduct("sidebandTaus","ALLTAUS");
  handler->addProductCut("sidebandTaus","TAU_nonIso");

  handler->addProduct("otherTaus","ALLTAUS");
  handler->addProductCut("otherTaus","TAU_nonIso");


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

  handler->addProduct("basicTracks","ALLTRACKS");
  handler->addProductCut("basicTracks","PT10");
  handler->addProductCut("basicTracks","ETA2p4");
  handler->addProductCut("basicTracks","trackHighPurity");
  handler->addProductCut("basicTracks","MUON_dz");

  handler->addProduct("goodTracks","basicTracks");
  handler->addProductCut("goodTracks","IREL0p24");
  handler->addProductCut("goodTracks","TRACK_PROMPT");
  
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

  handler->addProduct("goodPhotons","ALLPHOTONS");
  handler->addProductCut("goodPhotons","PT15");
  handler->addProductCut("goodPhotons","ETA2p4");
  handler->addProductCut("goodPhotons","PHOTON_COMBINED");

  //////////////
  //Setup Jets//
  //////////////
  handler->addObjectVariable("JET_NEUTRALHADRONFRACTION", new ObjectVariableInRange<double>("neutralHadronEnergyFraction",0,0.99));
  handler->addObjectVariable("JET_NEUTRALEMFRACTION", new ObjectVariableInRange<double>("neutralEmEnergyFraction", 0,0.99));
  handler->addObjectVariable("JET_NUMBEROFCONSTITUENTS", new ObjectVariableInRange<int>("chargedMultiplicity",1,100000));
  handler->addObjectVariable("CSVM",new ObjectVariableInRange<double>("combinedSecondaryVertexBJetTags",0.679,1000.0));
  handler->addObjectVariable("CSVL",new ObjectVariableInRange<double>("combinedSecondaryVertexBJetTags",0.244,1000.0));

  handler->addProduct("goodJets","ALLJETS");
  handler->addProductCut("goodJets","PT30");
  handler->addProductCut("goodJets","ETA2p4");
  handler->addProductCut("goodJets","JET_NEUTRALHADRONFRACTION");
  handler->addProductCut("goodJets","JET_NEUTRALEMFRACTION");
  handler->addProductCut("goodJets","JET_NUMBEROFCONSTITUENTS");

  handler->addProduct("bJetsCSVM","goodJets");
  handler->addProductCut("bJetsCSVM","CSVM");

  handler->addProduct("bJetsCSVL","goodJets");
  handler->addProductCut("bJetsCSVL","CSVL");

  ////////////////////////
  ///MC matched leptons///
  ////////////////////////
  handler->addProduct("goodElectronsMatched","goodElectrons");
  handler->addProduct("goodMuonsMatched","goodMuons");

  handler->addProduct("goodElectronsFromTau","goodElectrons");
  handler->addProduct("goodMuonsFromTau","goodMuons");

  handler->addProduct("goodElectronsNotMatched","goodElectrons");
  handler->addProduct("goodMuonsNotMatched","goodMuons");


  /////////////////
  ///Separations///
  /////////////////
  ObjectComparisonDeltaR* deltaR0p005 = new ObjectComparisonDeltaR(0.005);
  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p3 = new ObjectComparisonDeltaR(0.3);
  //ObjectComparisonDeltaR* deltaR0p4 = new ObjectComparisonDeltaR(0.4);

  ObjectComparisonMatchDeltaRCharge* mcMatch = new ObjectComparisonMatchDeltaRCharge(0.1,"genParticle");

  handler->addProductSelfComparison("goodMuons",deltaR0p1);
  handler->addProductSelfComparison("goodElectrons",deltaR0p1);
  handler->addProductSelfComparison("probeMuons",deltaR0p1);
  handler->addProductSelfComparison("probeElectrons",deltaR0p1);
  handler->addProductSelfComparison("basicTracks",deltaR0p005);
  handler->addProductSelfComparison("basicTracks7",deltaR0p005);
  handler->addProductSelfComparison("inclusiveTracks",deltaR0p005);
  handler->addProductSelfComparison("inclusiveTracks7",deltaR0p005);

  handler->addProductComparison("goodElectrons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTaus","goodMuons",deltaR0p3);
  handler->addProductComparison("goodTaus","goodElectrons",deltaR0p3);

  handler->addProductComparison("basicTracks","goodMuons",deltaR0p3);
  handler->addProductComparison("basicTracks","goodElectrons",deltaR0p3);
  handler->addProductComparison("basicTracks","goodTaus",deltaR0p3);

  handler->addProductComparison("goodPhotons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodElectrons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTaus",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTracks",deltaR0p1);

  handler->addProductComparison("goodJets","goodMuons",deltaR0p3);
  handler->addProductComparison("goodJets","goodElectrons",deltaR0p3);
  handler->addProductComparison("goodJets","goodTaus",deltaR0p3);
  handler->addProductComparison("goodJets","goodPhotons",deltaR0p3);

  handler->addProductComparison("goodElectronsMatched","MCELECTRONSFROMBOSON",mcMatch,false);
  handler->addProductComparison("goodMuonsMatched","MCMUONSFROMBOSON",mcMatch,false);
  handler->addProductComparison("goodElectronsFromTau","MCELECTRONSFROMTAU",mcMatch,false);
  handler->addProductComparison("goodMuonsFromTau","MCMUONSFROMTAU",mcMatch,false);

  handler->addProductComparison("goodElectronsNotMatched","goodElectronsMatched",deltaR0p1);
  handler->addProductComparison("goodElectronsNotMatched","goodElectronsFromTau",deltaR0p1);
  handler->addProductComparison("goodMuonsNotMatched","goodMuonsMatched",deltaR0p1);
  handler->addProductComparison("goodMuonsNotMatched","goodMuonsFromTau",deltaR0p1);

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

  handler->addProduct("MCMUONSFROMZPOS","MCMUONSFROMZ");
  handler->addProductCut("MCMUONSFROMZPOS","POSITIVE");
  handler->addProduct("MCMUONSFROMZNEG","MCMUONSFROMZ");
  handler->addProductCut("MCMUONSFROMZNEG","NEGATIVE");

  handler->addProduct("MCELECTRONSFROMZPOS","MCELECTRONSFROMZ");
  handler->addProductCut("MCELECTRONSFROMZPOS","POSITIVE");
  handler->addProduct("MCELECTRONSFROMZNEG","MCELECTRONSFROMZ");
  handler->addProductCut("MCELECTRONSFROMZNEG","NEGATIVE");
}


void setupVariables(BaseHandler* handler)
{

  handler->addEventVariable("N_McMuonsFromZ", new EventVariableN("N_McMuonsFromZ","MCMUONSFROMZ"));
  handler->addEventVariable("N_McElectronsFromZ", new EventVariableN("N_McElectronsFromZ","MCELECTRONSFROMZ"));

  handler->addEventVariable("N_McTausFromBoson", new EventVariableN("N_McTausFromBoson","MCTAUSFROMBOSON"));
  handler->addEventVariable("N_McMuonsFromBoson", new EventVariableN("N_McMuonsFromBoson","MCMUONSFROMBOSON"));
  handler->addEventVariable("N_McElectronsFromBoson", new EventVariableN("N_McElectronsFromBoson","MCELECTRONSFROMBOSON"));

  handler->addEventVariable("twoMcMuonsFromZ", new EventVariableValue<int>("N_McMuonsFromZ",2));
  handler->addEventVariable("twoMcElectronsFromZ", new EventVariableValue<int>("N_McElectronsFromZ",2));

  handler->addEventVariable("N_bosons", new EventVariableN("N_bosons","BOSONS"));
  handler->addEventVariable("N_bJetsCSVM", new EventVariableN("N_bJetsCSVM","bJetsCSVM"));
  handler->addEventVariable("N_bJetsCSVL", new EventVariableN("N_bJetsCSVL","bJetsCSVL"));
  handler->addEventVariable("WRITEEVENT", new EventVariableInRange<int>("N_bosons",0,10000));

  handler->addEventVariable("N_promptTracks",new EventVariableN("N_promptTracks","promptTracks"));
  handler->addEventVariable("N_nonPromptTracks",new EventVariableN("N_nonPromptTracks","nonPromptTracks"));
  handler->addEventVariable("N_goodTracks", new EventVariableN("N_goodTracks","goodTracks"));

  //handler->addEventVariable("WRITEEVENT", new EventVariableCombined("twoMcElectronsFromZ","twoMcMuonsFromZ"));

  handler->addEventVariable("N_fakeElectrons", new EventVariableN("N_fakeElectrons","goodElectronsNotMatched"));
  handler->addEventVariable("N_fakeMuons", new EventVariableN("N_fakeMuons","goodMuonsNotMatched"));

  handler->addEventVariable("N_matchedElectrons", new EventVariableN("N_matchedElectrons","goodElectronsMatched"));
  handler->addEventVariable("N_matchedMuons", new EventVariableN("N_matchedMuons","goodMuonsMatched"));

  handler->addEventVariable("N_electrons", new EventVariableN("N_electrons","goodElectrons"));
  handler->addEventVariable("N_muons", new EventVariableN("N_muons","goodMuons"));

  handler->addEventVariable("N_goodJets", new EventVariableN("N_goodJets","goodJets"));

  handler->addEventVariable("HT", new EventVariableSumPT("HT","goodJets"));
  handler->addEventVariable("SumPromptTrackPt", new EventVariableSumPT("SumPromptTrackPt","promptTracks"));
  handler->addEventVariable("SumNonPromptTrackPt", new EventVariableSumPT("SumNonPromptTrackPt","nonPromptTracks"));
  handler->addEventVariable("SumBasicTrackPt", new EventVariableSumPT("SumBasicTrackPt","basicTracks"));

  EventVariablePairMass* mumcmass = new EventVariablePairMass("MUMCMASS","MCMUONSFROMZ","MUMC_",91,15);
  handler->addEventVariable("MUMCMASS",mumcmass);
  EventVariablePairMass* elmcmass = new EventVariablePairMass("ELMCMASS","MCELECTRONSFROMZ","ELMC_",91,15);
  handler->addEventVariable("ELMCMASS",elmcmass);

  handler->addEventVariable("MAXGENDXY",new EventVariableObjectVariableMax<double>("genDxy","ALLMC"));

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

  handler->addEventVariable("PROBEMUPLUSPT",new  EventVariableObjectVariableMax<double>("PT","probeMuonsPOS"));
  handler->addEventVariable("PROBEMUMINUSPT",new  EventVariableObjectVariableMax<double>("PT","probeMuonsNEG"));
  handler->addEventVariable("PROBEELPLUSPT",new  EventVariableObjectVariableMax<double>("PT","probeElectronsPOS"));
  handler->addEventVariable("PROBEELMINUSPT",new  EventVariableObjectVariableMax<double>("PT","probeElectronsNEG"));

  handler->addEventVariable("GOODMUPLUSPT",new  EventVariableObjectVariableMax<double>("PT","goodMuonsPOS"));
  handler->addEventVariable("GOODMUMINUSPT",new  EventVariableObjectVariableMax<double>("PT","goodMuonsNEG"));
  handler->addEventVariable("GOODELPLUSPT",new  EventVariableObjectVariableMax<double>("PT","goodElectronsPOS"));
  handler->addEventVariable("GOODELMINUSPT",new  EventVariableObjectVariableMax<double>("PT","goodElectronsNEG"));

  handler->addEventVariable("MCMUPLUSPT",new  EventVariableObjectVariableMax<double>("PT","MCMUONSFROMZPOS"));
  handler->addEventVariable("MCMUMINUSPT",new  EventVariableObjectVariableMax<double>("PT","MCMUONSFROMZNEG"));
  handler->addEventVariable("MCELPLUSPT",new  EventVariableObjectVariableMax<double>("PT","MCELECTRONSFROMZPOS"));
  handler->addEventVariable("MCELMINUSPT",new  EventVariableObjectVariableMax<double>("PT","MCELECTRONSFROMZNEG"));



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
