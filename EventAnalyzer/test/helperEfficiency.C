#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableCombined.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableMass.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableN.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableMT.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableOS.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableOSSF.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariablePairMass.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableMixedPairMass.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableReversed.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableSumPT.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableTH1.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableTriggerWeight.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableValue.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableCombined.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableElectronTotalIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableMethod.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableMuonTotalIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableRelIso.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableReversed.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableValue.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_AssociateVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparisonSkimRecoTracks.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparisonElectron.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectComparisonMatchDeltaRCharge.h"
#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableRename.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH2F_EventVariableVsEventVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH2F_ObjectVariableVsObjectVariable.h"
#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableObjectVariableMax.h"

void setupEfficiencyProducts(BaseHandler* handler)
{
  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonMatchDeltaRCharge* mcMatch = new ObjectComparisonMatchDeltaRCharge(0.1,"genParticle");
  ////////
  //Muon//
  ////////


  vector<TString> muonCuts;
  muonCuts.push_back("isGlobalMuon");
  muonCuts.push_back("isPFMuon");
  muonCuts.push_back("MUON_dz");
  muonCuts.push_back("MUON_normalizedChi2");
  muonCuts.push_back("MUON_numberOfValidMuonHits");
  muonCuts.push_back("MUON_numberOfMatchedStations");
  muonCuts.push_back("MUON_numberOfValidPixelHits");
  muonCuts.push_back("MUON_trackerLayersWithMeasurement");
  muonCuts.push_back("MUON_dxy");
  muonCuts.push_back("IREL0p15");

  handler->addProduct("startMuons","ALLMUONS");
  handler->addProductCut("startMuons","PT10");
  handler->addProductCut("startMuons","ETA2p4");
  handler->addProduct("startMuons_matched","startMuons");
  handler->addProductComparison("startMuons_matched","MCMUONSFROMBOSON",mcMatch,false);

  handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("PTGEN_startMuons_matched","PT","startMuons_matched","genParticle","",100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_startMuons_matched","PT","startMuons_matched","",100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_startMuons","PT","startMuons","",100,0,200));

  vector<TString> muonProductNames;

  for(int i = 0; i < (int)muonCuts.size(); i++){
    TString pname = TString::Format("effMuons_%s",muonCuts[i].Data());
    muonProductNames.push_back(pname);
    if (i == 0){
      handler->addProduct(pname,"startMuons");
    }else{
      handler->addProduct(pname,muonProductNames[i-1]);
    }
    handler->addProductCut(pname,muonCuts[i]);
    handler->addProductSelfComparison(pname,deltaR0p1);
    TString pnameMatched = TString::Format("effMuons_%s_matched",muonCuts[i].Data());
    handler->addProduct(pnameMatched,pname);
    handler->addProductComparison(pnameMatched,"MCMUONSFROMBOSON",mcMatch,false);
    handler->addHistogram(new SignatureTH1F_AssociateVariable<double>(TString::Format("PTGEN_%s",pnameMatched.Data()),"PT",pnameMatched,"genParticle","",100,0,200));
    handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(TString::Format("PT_%s",pnameMatched.Data()),"PT",pnameMatched,"",100,0,200));
    handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(TString::Format("PT_%s",pname.Data()),"PT",pname,"",100,0,200));

  }


  ////////////
  //Electron//
  ////////////

  //////////////////
  //refactor electron barrel/endcap cuts to make this easier//
  ///////////////////////////////

  ObjectVariableCombined* electron_combined_barrel_dz = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_dz",true,"electron_combined_barrel_dz");
  ObjectVariableCombined* electron_combined_endcap_dz = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_dz",true,"electron_combined_endcap_dz");
  ObjectVariableCombined* electron_combined_dz = new ObjectVariableCombined("electron_combined_barrel_dz","electron_combined_endcap_dz",false,"electron_combined_dz");
  handler->addObjectVariable("electron_combined_barrel_dz",electron_combined_barrel_dz);
  handler->addObjectVariable("electron_combined_endcap_dz",electron_combined_endcap_dz);
  handler->addObjectVariable("ELECTRON_dz",electron_combined_dz);

  ObjectVariableCombined* electron_combined_barrel_dxy = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_dxy",true,"electron_combined_barrel_dxy");
  ObjectVariableCombined* electron_combined_endcap_dxy = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_dxy",true,"electron_combined_endcap_dxy");
  ObjectVariableCombined* electron_combined_dxy = new ObjectVariableCombined("electron_combined_barrel_dxy","electron_combined_endcap_dxy",false,"electron_combined_dxy");
  handler->addObjectVariable("electron_combined_barrel_dxy",electron_combined_barrel_dxy);
  handler->addObjectVariable("electron_combined_endcap_dxy",electron_combined_endcap_dxy);
  handler->addObjectVariable("ELECTRON_dxy",electron_combined_dxy);

  ObjectVariableCombined* electron_combined_barrel_IREL = new ObjectVariableCombined("BARREL","IREL0p24",true,"electron_combined_barrel_IREL");
  ObjectVariableCombined* electron_combined_endcap_IREL = new ObjectVariableCombined("ENDCAP","IREL0p35",true,"electron_combined_endcap_IREL");
  ObjectVariableCombined* electron_combined_IREL = new ObjectVariableCombined("electron_combined_barrel_IREL","electron_combined_endcap_IREL",false,"electron_combined_IREL");
  handler->addObjectVariable("electron_combined_barrel_IREL",electron_combined_barrel_IREL);
  handler->addObjectVariable("electron_combined_endcap_IREL",electron_combined_endcap_IREL);
  handler->addObjectVariable("ELECTRON_IREL",electron_combined_IREL);


  ObjectVariableCombined* electron_combined_barrel_deltaEtaSuperClusterTrackAtVtx = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_deltaEtaSuperClusterTrackAtVtx",true,"electron_combined_barrel_deltaEtaSuperClusterTrackAtVtx");
  ObjectVariableCombined* electron_combined_endcap_deltaEtaSuperClusterTrackAtVtx = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_deltaEtaSuperClusterTrackAtVtx",true,"electron_combined_endcap_deltaEtaSuperClusterTrackAtVtx");
  ObjectVariableCombined* electron_combined_deltaEtaSuperClusterTrackAtVtx = new ObjectVariableCombined("electron_combined_barrel_deltaEtaSuperClusterTrackAtVtx","electron_combined_endcap_deltaEtaSuperClusterTrackAtVtx",false,"electron_combined_deltaEtaSuperClusterTrackAtVtx");
  handler->addObjectVariable("electron_combined_barrel_deltaEtaSuperClusterTrackAtVtx",electron_combined_barrel_deltaEtaSuperClusterTrackAtVtx);
  handler->addObjectVariable("electron_combined_endcap_deltaEtaSuperClusterTrackAtVtx",electron_combined_endcap_deltaEtaSuperClusterTrackAtVtx);
  handler->addObjectVariable("ELECTRON_DELTAETA",electron_combined_deltaEtaSuperClusterTrackAtVtx);

  ObjectVariableCombined* electron_combined_barrel_deltaPhiSuperClusterTrackAtVtx = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_deltaPhiSuperClusterTrackAtVtx",true,"electron_combined_barrel_deltaPhiSuperClusterTrackAtVtx");
  ObjectVariableCombined* electron_combined_endcap_deltaPhiSuperClusterTrackAtVtx = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_deltaPhiSuperClusterTrackAtVtx",true,"electron_combined_endcap_deltaPhiSuperClusterTrackAtVtx");
  ObjectVariableCombined* electron_combined_deltaPhiSuperClusterTrackAtVtx = new ObjectVariableCombined("electron_combined_barrel_deltaPhiSuperClusterTrackAtVtx","electron_combined_endcap_deltaPhiSuperClusterTrackAtVtx",false,"electron_combined_deltaPhiSuperClusterTrackAtVtx");
  handler->addObjectVariable("electron_combined_barrel_deltaPhiSuperClusterTrackAtVtx",electron_combined_barrel_deltaPhiSuperClusterTrackAtVtx);
  handler->addObjectVariable("electron_combined_endcap_deltaPhiSuperClusterTrackAtVtx",electron_combined_endcap_deltaPhiSuperClusterTrackAtVtx);
  handler->addObjectVariable("ELECTRON_DELTAPHI",electron_combined_deltaPhiSuperClusterTrackAtVtx);

  ObjectVariableCombined* electron_combined_barrel_sigmaIetaIeta = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_sigmaIetaIeta",true,"electron_combined_barrel_sigmaIetaIeta");
  ObjectVariableCombined* electron_combined_endcap_sigmaIetaIeta = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_sigmaIetaIeta",true,"electron_combined_endcap_sigmaIetaIeta");
  ObjectVariableCombined* electron_combined_sigmaIetaIeta = new ObjectVariableCombined("electron_combined_barrel_sigmaIetaIeta","electron_combined_endcap_sigmaIetaIeta",false,"electron_combined_sigmaIetaIeta");
  handler->addObjectVariable("electron_combined_barrel_sigmaIetaIeta",electron_combined_barrel_sigmaIetaIeta);
  handler->addObjectVariable("electron_combined_endcap_sigmaIetaIeta",electron_combined_endcap_sigmaIetaIeta);
  handler->addObjectVariable("ELECTRON_SIGMAIETAIETA",electron_combined_sigmaIetaIeta);

  ObjectVariableCombined* electron_combined_barrel_hadronicOverEm = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_hadronicOverEm",true,"electron_combined_barrel_hadronicOverEm");
  ObjectVariableCombined* electron_combined_endcap_hadronicOverEm = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_hadronicOverEm",true,"electron_combined_endcap_hadronicOverEm");
  ObjectVariableCombined* electron_combined_hadronicOverEm = new ObjectVariableCombined("electron_combined_barrel_hadronicOverEm","electron_combined_endcap_hadronicOverEm",false,"electron_combined_hadronicOverEm");
  handler->addObjectVariable("electron_combined_barrel_hadronicOverEm",electron_combined_barrel_hadronicOverEm);
  handler->addObjectVariable("electron_combined_endcap_hadronicOverEm",electron_combined_endcap_hadronicOverEm);
  handler->addObjectVariable("ELECTRON_HADRONICOVEREM",electron_combined_hadronicOverEm);


  vector<TString> electronCuts;
  electronCuts.push_back("ELECTRON_passConversionVeto");
  electronCuts.push_back("ELECTRON_1oEm1oP");
  electronCuts.push_back("ELECTRON_dxy");
  electronCuts.push_back("ELECTRON_dz");
  electronCuts.push_back("ELECTRON_HADRONICOVEREM");
  electronCuts.push_back("ELECTRON_SIGMAIETAIETA");
  electronCuts.push_back("ELECTRON_DELTAETA");
  electronCuts.push_back("ELECTRON_DELTAPHI");
  electronCuts.push_back("ELECTRON_IREL");

  handler->addProduct("startElectrons","ALLELECTRONS");
  handler->addProductCut("startElectrons","PT10");
  handler->addProductCut("startElectrons","ETA2p4");
  handler->addProductCut("startElectrons","ELECTRON_NOTGAP");

  handler->addProduct("startElectrons_matched","startElectrons");
  handler->addProductComparison("startElectrons_matched","MCELECTRONSFROMBOSON",mcMatch,false);


  handler->addHistogram(new SignatureTH1F_AssociateVariable<double>("PTGEN_startElectrons_matched","PT","startElectrons_matched","genParticle","",100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_startElectrons_matched","PT","startElectrons_matched","",100,0,200));
  handler->addHistogram(new SignatureTH1F_ObjectVariable<double>("PT_startElectrons","PT","startElectrons","",100,0,200));

  vector<TString> electronProductNames;

  for(int i = 0; i < (int)electronCuts.size(); i++){
    TString pname = TString::Format("effElectrons_%s",electronCuts[i].Data());
    electronProductNames.push_back(pname);
    if (i == 0){
      handler->addProduct(pname,"startElectrons");
    }else{
      handler->addProduct(pname,electronProductNames[i-1]);
    }
    handler->addProductCut(pname,electronCuts[i]);
    handler->addProductSelfComparison(pname,deltaR0p1);
    handler->addProductComparison(pname,"goodMuons",deltaR0p1);
    TString pnameMatched = TString::Format("effElectrons_%s_matched",electronCuts[i].Data());
    handler->addProduct(pnameMatched,pname);
    handler->addProductComparison(pnameMatched,"MCELECTRONSFROMBOSON",mcMatch,false);
    handler->addHistogram(new SignatureTH1F_AssociateVariable<double>(TString::Format("PTGEN_%s",pnameMatched.Data()),"PT",pnameMatched,"genParticle","",100,0,200));
    handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(TString::Format("PT_%s",pnameMatched.Data()),"PT",pnameMatched,"",100,0,200));
    handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(TString::Format("PT_%s",pname.Data()),"PT",pname,"",100,0,200));
    if(electronCuts[i] == "ELECTRON_dxy"){
      handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(TString::Format("dz_%s",pnameMatched.Data()),"dz",pnameMatched,"dz Distribution",200,-5,5));
    }else if(electronCuts[i] == "ELECTRON_HADRONICOVEREM"){
      handler->addHistogram(new SignatureTH1F_ObjectVariable<double>(TString::Format("full5x5_sigmaIetaIeta_%s",pnameMatched.Data()),"full5x5_sigmaIetaIeta",pnameMatched,"full5x5_sigmaIetaIeta Distribution",200,0,0.1));
      handler->addHistogram(new SignatureTH2F_ObjectVariableVsObjectVariable<double,double>("PT","full5x5_sigmaIetaIeta",pnameMatched,TString::Format("full5x5_sigmaIetaIeta_vs_PT_%s",pnameMatched.Data()),"",100,0,200,200,0,0.1));
    }
  }

}
