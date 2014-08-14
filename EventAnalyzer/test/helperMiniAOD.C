#include <TF1.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableN.h"
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

  handler->addProduct("ALLMET","ALL");
  handler->addProductCut("ALLMET","isMET");


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
  //handler->addObjectVariable("CHARGE",new ObjectVariableRename<int>("charge","CHARGE"));
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
  handler->addObjectVariable("ELECTRON_BARREL_deltaEtaSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.018,0.018));
  handler->addObjectVariable("ELECTRON_BARREL_deltaPhiSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.09,0.09));
  handler->addObjectVariable("ELECTRON_ENDCAP_deltaEtaSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.012,0.012));
  handler->addObjectVariable("ELECTRON_ENDCAP_deltaPhiSuperClusterTrackAtVtx", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.064,0.064));
  handler->addObjectVariable("ELECTRON_BARREL_hadronicOverEm",new ObjectVariableInRange<double>("hadronicOverEm",0.0,0.14));
  handler->addObjectVariable("ELECTRON_ENDCAP_hadronicOverEm",new ObjectVariableInRange<double>("hadronicOverEm",0.0,0.11));
  handler->addObjectVariable("ELECTRON_BARREL_sigmaIetaIeta",new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.01));
  handler->addObjectVariable("ELECTRON_ENDCAP_sigmaIetaIeta",new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.035));
  handler->addObjectVariable("ELECTRON_1oEm1oP", new ObjectVariableInRange<double>("1oEm1oP",0,0.13));
  handler->addObjectVariable("ELECTRON_passConversionVeto",new ObjectVariableValue<bool>("passConversionVeto",true));
  handler->addObjectVariable("ELECTRON_BARREL_dz", new ObjectVariableInRange<double>("dz",-0.54,0.54));
  handler->addObjectVariable("ELECTRON_BARREL_dxy", new ObjectVariableInRange<double>("dxy",-0.017,0.017));
  handler->addObjectVariable("ELECTRON_ENDCAP_dz", new ObjectVariableInRange<double>("dz",-0.92,0.92));
  handler->addObjectVariable("ELECTRON_ENDCAP_dxy", new ObjectVariableInRange<double>("dxy",-0.1,0.1));
  handler->addObjectVariable("ELECTRON_dz1", new ObjectVariableInRange<double>("dz",-1.0,1.0));

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
  handler->addObjectVariable("IREL0p23",new ObjectVariableInRange<double>("RELISO",0,0.23,"IREL0p23"));
  handler->addObjectVariable("IREL0p24",new ObjectVariableInRange<double>("RELISO",0,0.24,"IREL0p24"));
  handler->addObjectVariable("IREL0p25",new ObjectVariableInRange<double>("RELISO",0,0.25,"IREL0p25"));
  handler->addObjectVariable("IREL0p35",new ObjectVariableInRange<double>("RELISO",0,0.35,"IREL0p35"));


  ObjectVariableCombined* electron_barrel = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_hadronicOverEm",true,"electron_barrel_good");
  electron_barrel->addVariable("ELECTRON_BARREL_sigmaIetaIeta");
  electron_barrel->addVariable("ELECTRON_BARREL_deltaPhiSuperClusterTrackAtVtx");
  electron_barrel->addVariable("ELECTRON_BARREL_deltaEtaSuperClusterTrackAtVtx");
  electron_barrel->addVariable("ELECTRON_BARREL_dz");
  electron_barrel->addVariable("ELECTRON_BARREL_dxy");
  electron_barrel->addVariable("IREL0p24");
  handler->addObjectVariable("ELECTRON_BARREL",electron_barrel);

  ObjectVariableCombined* electron_endcap = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_hadronicOverEm",true,"electron_endcap_good");
  electron_endcap->addVariable("ELECTRON_ENDCAP_sigmaIetaIeta");
  electron_endcap->addVariable("ELECTRON_ENDCAP_deltaPhiSuperClusterTrackAtVtx");
  electron_endcap->addVariable("ELECTRON_ENDCAP_deltaEtaSuperClusterTrackAtVtx");
  electron_endcap->addVariable("ELECTRON_ENDCAP_dz");
  electron_endcap->addVariable("ELECTRON_ENDCAP_dxy");
  electron_endcap->addVariable("IREL0p35");
  handler->addObjectVariable("ELECTRON_ENDCAP",electron_endcap);

  handler->addObjectVariable("ELECTRON_COMBINED",new ObjectVariableCombined("ELECTRON_BARREL","ELECTRON_ENDCAP",false,"ELECTRON_COMBINED"));


  //////////////////
  ///Muon Product///
  //////////////////

  handler->addProduct("goodMuons","ALLMUONS");
  handler->addProductCut("goodMuons","PT10");
  handler->addProductCut("goodMuons","ETA2p4");
  handler->addProductCut("goodMuons","IREL0p15");
  handler->addProductCut("goodMuons","isGlobalMuon");
  handler->addProductCut("goodMuons","isPFMuon");
  handler->addProductCut("goodMuons","MUON_normalizedChi2");
  handler->addProductCut("goodMuons","MUON_numberOfValidMuonHits");
  handler->addProductCut("goodMuons","MUON_numberOfMatchedStations");
  handler->addProductCut("goodMuons","MUON_dxy");
  handler->addProductCut("goodMuons","MUON_dz");
  handler->addProductCut("goodMuons","MUON_numberOfValidPixelHits");
  handler->addProductCut("goodMuons","MUON_trackerLayersWithMeasurement");

  handler->addProduct("probeMuons","ALLMUONS");
  handler->addProductCut("probeMuons","ETA2p4");
  handler->addProductCut("probeMuons","isGlobalMuon");
  handler->addProductCut("probeMuons","MUON_dz");

  //////////////
  ///Electron///
  //////////////

  handler->addProduct("goodElectrons","ALLELECTRONS");
  handler->addProductCut("goodElectrons","PT10");
  handler->addProductCut("goodElectrons","ETA2p4");
  //handler->addProductCut("goodElectrons","IREL0p23");
  handler->addProductCut("goodElectrons","ELECTRON_COMBINED");
  //handler->addProductCut("goodElectrons","ELECTRON_dxy");
  handler->addProductCut("goodElectrons","ELECTRON_passConversionVeto");
  //handler->addProductCut("goodElectrons","ELECTRON_dz");
  handler->addProductCut("goodElectrons","ELECTRON_NOTGAP");
  handler->addProductCut("goodElectrons","ELECTRON_1oEm1oP");

  handler->addProduct("probeElectrons","ALLELECTRONS");
  handler->addProductCut("probeElectrons","ETA2p4");
  handler->addProductCut("probeElectrons","ELECTRON_NOTGAP");
  handler->addProductCut("probeElectrons","ELECTRON_dz");
  handler->addProductCut("probeElectrons","ELECTRON_passConversionVeto");

  ////////
  ///MC///
  ////////
  ObjectVariableValueInList<int>* electronPDGID = new ObjectVariableValueInList<int>("pdgId",11);
  electronPDGID->addValue(-11);
  handler->addObjectVariable("ELECTRONPDGID",electronPDGID);
  ObjectVariableValueInList<int>* muonPDGID = new ObjectVariableValueInList<int>("pdgId",13);
  muonPDGID->addValue(-13);
  handler->addObjectVariable("MUONPDGID",muonPDGID);
  handler->addObjectVariable("MOTHERZ",new ObjectVariableValue<int>("motherpdgId",23));
  ObjectVariableValueInList<int>* motherBoson = new ObjectVariableValueInList<int>("motherpdgId",23);
  motherBoson->addValue(24);
  motherBoson->addValue(-24);
  motherBoson->addValue(25);
  handler->addObjectVariable("MOTHERBOSON",motherBoson);

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

  handler->addProduct("MCELECTRONSFROMZ","MCELECTRONS");
  handler->addProductCut("MCELECTRONSFROMZ","MOTHERZ");
  handler->addProduct("MCMUONSFROMZ","MCMUONS");
  handler->addProductCut("MCMUONSFROMZ","MOTHERZ");

  handler->addProduct("MCELECTRONSFROMBOSON","MCELECTRONS");
  handler->addProductCut("MCELECTRONSFROMBOSON","MOTHERBOSON");
  handler->addProduct("MCMUONSFROMBOSON","MCMUONS");
  handler->addProductCut("MCMUONSFROMBOSON","MOTHERBOSON");


  ////////////
  ///Tracks///
  ////////////
  handler->addProduct("basicTracks","ALLTRACKS");
  handler->addProductCut("basicTracks","PT6");
  handler->addProductCut("basicTracks","ETA2p4");
  handler->addProductCut("basicTracks","trackHighPurity");
  handler->addProductCut("basicTracks","MUON_dz");

  handler->addProduct("promptTracks","basicTracks");
  handler->addProductCut("promptTracks","MUON_dxy");
  handler->addProductCut("promptTracks","TRACK_fromPV");
  handler->addProduct("nonPromptTracks","basicTracks");
  handler->addProductCut("nonPromptTracks","MUON_nonprompt");

  handler->addProduct("goodTracks","promptTracks");
  handler->addProductCut("goodTracks","IREL0p24");
  handler->addProductCut("goodTracks","PT10");

  //////////////
  //Setup Jets//
  //////////////
  handler->addObjectVariable("JET_NEUTRALHADRONFRACTION", new ObjectVariableInRange<double>("neutralHadronEnergyFraction",0,0.99));
  handler->addObjectVariable("JET_NEUTRALEMFRACTION", new ObjectVariableInRange<double>("neutralEmEnergyFraction", 0,0.99));
  handler->addObjectVariable("JET_NUMBEROFCONSTITUENTS", new ObjectVariableInRange<int>("chargedMultiplicity",1,100000));

  handler->addProduct("goodJets","ALLJETS");
  handler->addProductCut("goodJets","PT30");
  handler->addProductCut("goodJets","ETA2p4");
  handler->addProductCut("goodJets","JET_NEUTRALHADRONFRACTION");
  handler->addProductCut("goodJets","JET_NEUTRALEMFRACTION");
  handler->addProductCut("goodJets","JET_NUMBEROFCONSTITUENTS");


  ////////////////////////
  ///MC matched leptons///
  ////////////////////////
  handler->addProduct("goodElectronsMatched","goodElectrons");
  handler->addProduct("goodMuonsMatched","goodMuons");

  handler->addProduct("goodElectronsNotMatched","goodElectrons");
  handler->addProduct("goodMuonsNotMatched","goodMuons");

  /////////////////
  ///Separations///
  /////////////////
  ObjectComparisonDeltaR* deltaR0p005 = new ObjectComparisonDeltaR(0.005);
  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p3 = new ObjectComparisonDeltaR(0.3);

  ObjectComparisonMatchDeltaRCharge* mcMatch = new ObjectComparisonMatchDeltaRCharge(0.1,"genParticle");

  handler->addProductSelfComparison("goodMuons",deltaR0p1);
  handler->addProductSelfComparison("goodElectrons",deltaR0p1);
  handler->addProductSelfComparison("probeMuons",deltaR0p1);
  handler->addProductSelfComparison("probeElectrons",deltaR0p1);
  handler->addProductSelfComparison("basicTracks",deltaR0p005);

  handler->addProductComparison("goodElectrons","goodMuons",deltaR0p1);
  handler->addProductComparison("basicTracks","goodMuons",deltaR0p3);
  handler->addProductComparison("basicTracks","goodElectrons",deltaR0p3);

  handler->addProductComparison("goodJets","goodMuons",deltaR0p3);
  handler->addProductComparison("goodJets","goodElectrons",deltaR0p3);

  handler->addProductComparison("goodElectronsMatched","MCELECTRONSFROMBOSON",mcMatch,false);
  handler->addProductComparison("goodMuonsMatched","MCMUONSFROMBOSON",mcMatch,false);

  handler->addProductComparison("goodElectronsNotMatched","goodElectronsMatched",deltaR0p1);
  handler->addProductComparison("goodMuonsNotMatched","goodMuonsMatched",deltaR0p1);

  //////////////////////
  ///Derived Products////
  //////////////////////

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

  handler->addEventVariable("twoMcMuonsFromZ", new EventVariableValue<int>("N_McMuonsFromZ",2));
  handler->addEventVariable("twoMcElectronsFromZ", new EventVariableValue<int>("N_McElectronsFromZ",2));

  handler->addEventVariable("N_bosons", new EventVariableN("N_bosons","BOSONS"));
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
