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
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonSkimRecoTracks.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonElectron.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDeltaRCharge.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"

TString makeName(int qMu, int nMu,int qEl,int nEl, int qTr, int nTr)
{

  TString name = "El";
  name += nEl;
  if(qEl == 0){
    name += "q";
  }else if(qEl < 0){
    name += "m";
  }else{
    name += "p";
  }

  name += abs(qEl);
  name += "Mu";
  name += nMu;

  if(qMu == 0){
    name += "q";
  }else if(qMu < 0){
    name += "m";
  }else{
    name += "p";
  }
  name += abs(qMu);

  if(nTr == 0)return name;

  name += "T";
  name += nTr;

  if(qTr == 0){
    name += "q";
  }else if(qTr < 0){
    name += "m";
  }else{
    name += "p";
  }
  name += abs(qTr);

  return name;
}

void setupProducts(BaseHandler* handler)
{
  //////////////////
  ///General Cuts///
  //////////////////
  handler->addObjectVariable("PT",new ObjectVariableMethod("PT", &SignatureObject::Pt));
  handler->addObjectVariable("ETA",new ObjectVariableMethod("ETA", &SignatureObject::Eta));
  ObjectVariableInRange<double>* leptonPtCut = new ObjectVariableInRange<double>("PT",10.0,10000.0,"leptonPtCut");
  ObjectVariableInRange<double>* leptonEtaCut = new ObjectVariableInRange<double>("ETA",-2.4,2.4,"leptonEtaCut");
  ObjectVariableInRange<double>* PT40 = new ObjectVariableInRange<double>("PT",40.0,10000.0,"PT40");
  handler->addObjectVariable("MUONTOTALISO",new ObjectVariableMuonTotalIso("TOTALISO"),false);
  handler->addObjectVariable("ELECTRONTOTALISO",new ObjectVariableElectronTotalIso("TOTALISO"),false);
  handler->addObjectVariable("RELISO",new ObjectVariableRelIso("RELISO"));

  handler->addObjectVariable("PT10",leptonPtCut);
  handler->addObjectVariable("PT15",new ObjectVariableInRange<double>("PT",15.0,10000.0,"PT15"));
  handler->addObjectVariable("PT20",new ObjectVariableInRange<double>("PT",20.0,10000.0,"PT20"));
  handler->addObjectVariable("PT30",new ObjectVariableInRange<double>("PT",30.0,10000.0,"PT30"));
  handler->addObjectVariable("PT40",PT40);
  handler->addObjectVariable("ETA2p3",new ObjectVariableInRange<double>("ETA",-2.3,2.3,"ETA2p3"));
  handler->addObjectVariable("ETA2p4",leptonEtaCut);
  handler->addObjectVariable("ETA2p5",new ObjectVariableInRange<double>("ETA",-2.5,2.5,"ETA2p5"));
  handler->addObjectVariable("IREL0p15",new ObjectVariableInRange<double>("RELISO",0,0.15,"IREL0p15"));
  handler->addObjectVariable("BARREL",new ObjectVariableInRange<double>("ETA",-1.5,1.5,"barrelEta"));
  handler->addObjectVariable("ENDCAP",new ObjectVariableReversed("BARREL","endcapEta"));
  handler->addObjectVariable("POSITIVE",new ObjectVariableInRange<double>("CHARGE",0,10,"CHARGEPOS"));
  handler->addObjectVariable("NEGATIVE",new ObjectVariableInRange<double>("CHARGE",-10,0,"CHARGENEG"));


  /////////////////
  ///Muon Cuts ///
  ////////////////

  handler->addObjectVariable("MUON_VALID_INNER_PIXEL_HITS",new ObjectVariableInRange<int>("INNERNUMBEROFVALIDPIXELHITS",1,10000,"MUON_VALID_INNER_PIXEL_HITS"));
  handler->addObjectVariable("MUON_TRACK_LAYERS_WM", new ObjectVariableInRange<int>("NTRACKERLAYERSWM",6,10000,"MUON_TRACK_LAYERS_WM"));
  handler->addObjectVariable("MUON_MATCHES",new ObjectVariableInRange<int>("NUMBEROFMATCHES",2,100000,"MUON_MATCHES"));
  handler->addObjectVariable("ISPF",new ObjectVariableValue<int>("ISPF",1,"ISPF"));
  handler->addObjectVariable("MUON_ISGLOBAL",new ObjectVariableValue<int>("ISGLOBALMUON",1,"MUON_ISGLOBAL"));
  handler->addObjectVariable("MUON_VALID_MUON_HITS",new ObjectVariableInRange<int>("NVALIDMUONHITS",1,10000,"MUON_VALID_MUON_HITS"));
  handler->addObjectVariable("MUON_NORMALIZED_CHI2",new ObjectVariableInRange<double>("NORMALIZEDCHI2",0,10,"MUON_NORMALIZED_CHI2"));
  handler->addObjectVariable("MUON_INNER_VERT_DZ",new ObjectVariableInRange<double>("INNERVERTDZ",-0.5,0.5,"MUON_INNER_VERT_DZ"));
  handler->addObjectVariable("MUON_PROMPT",new ObjectVariableInRange<double>("INNERVERTDXY",-0.02,0.02,"MUON_PROMPT"));
  handler->addObjectVariable("MUON_NONPROMPT",new ObjectVariableInRange<double>("INNERVERTDXY",0.03,1000,"MUON_NONPROMPT"));

  handler->addProduct("goodMuons","ALLMUONS");
  handler->addProductCut("goodMuons","PT10");
  handler->addProductCut("goodMuons","ETA2p4");
  handler->addProductCut("goodMuons","IREL0p15");
  handler->addProductCut("goodMuons","MUON_VALID_INNER_PIXEL_HITS");
  handler->addProductCut("goodMuons","MUON_TRACK_LAYERS_WM");
  handler->addProductCut("goodMuons","MUON_MATCHES");
  handler->addProductCut("goodMuons","ISPF");
  handler->addProductCut("goodMuons","MUON_ISGLOBAL");
  handler->addProductCut("goodMuons","MUON_VALID_MUON_HITS");
  handler->addProductCut("goodMuons","MUON_NORMALIZED_CHI2");
  handler->addProductCut("goodMuons","MUON_INNER_VERT_DZ");
  handler->addProductCut("goodMuons","MUON_PROMPT");

  ///////////////////
  ///Electron Cuts///
  //////////////////

  handler->addObjectVariable("ELECTRON_INGAPPOS",new ObjectVariableInRange<double>("FMVAVAR_ETA",1.4442,1.566,"ELECTRON_INGAPPOS"));
  handler->addObjectVariable("ELECTRON_INGAPNEG",new ObjectVariableInRange<double>("FMVAVAR_ETA",-1.566,-1.4442,"ELECTRON_INGAPNEG"));
  ObjectVariableCombined* electron_ingap = new ObjectVariableCombined("ELECTRON_INGAPPOS","ELECTRON_INGAPNEG",false,"ELECTORN_INGAP");
  handler->addObjectVariable("ELECTRON_INGAP",electron_ingap);
  handler->addObjectVariable("ELECTRON_NOTGAP",new ObjectVariableReversed("ELECTRON_INGAP","ELECTRON_NOTGAP"));
  handler->addObjectVariable("ELECTRON_BARREL_DETA",new ObjectVariableInRange<double>("DELTAETA",-0.007,0.007,"ELECTRON_BARREL_DETA"));
  handler->addObjectVariable("ELECTRON_ENDCAP_DETA",new ObjectVariableInRange<double>("DELTAETA",-0.009,0.009,"ELECTRON_ENDCAP_DETA"));
  handler->addObjectVariable("ELECTRON_BARREL_DPHI",new ObjectVariableInRange<double>("DELTAPHI",-0.15,0.15,"ELECTRON_BARREL_DPHI"));
  handler->addObjectVariable("ELECTRON_ENDCAP_DPHI",new ObjectVariableInRange<double>("DELTAPHI",-0.10,0.10,"ELECTRON_ENDCAP_DPHI"));
  handler->addObjectVariable("ELECTRON_BARREL_HADOVEREM",new ObjectVariableInRange<double>("HADOVEREM",0.0,0.12));
  handler->addObjectVariable("ELECTRON_ENDCAP_HADOVEREM",new ObjectVariableInRange<double>("HADOVEREM",0.0,0.10));
  handler->addObjectVariable("ELECTRON_BARREL_SIGMAIETAIETA",new ObjectVariableInRange<double>("SIGMAIETAIETA",-0.01,0.01));
  handler->addObjectVariable("ELECTRON_ENDCAP_SIGMAIETAIETA",new ObjectVariableInRange<double>("SIGMAIETAIETA",-0.03,0.03));
  handler->addObjectVariable("ELECTRON_MISSING_HITS",new ObjectVariableInRange<int>("NUMBEROFEXPECTEDINNERHITS",0,1));
  handler->addObjectVariable("ELECTRON_EMINUSP",new ObjectVariableInRange<double>("FMVAVAR_IOEMIOP",-0.05,0.05));
  handler->addObjectVariable("ELECTRON_CONVERSION",new ObjectVariableValue<int>("ISCONVERSION",0));
  handler->addObjectVariable("ELECTRON_VERT_DZ", new ObjectVariableInRange<double>("FMVAVAR_DZ",-0.2,0.2));
  handler->addObjectVariable("ELECTRON_PROMPT", new ObjectVariableInRange<double>("FMVAVAR_D0",-0.02,0.02));

  ObjectVariableCombined* electron_barrel = new ObjectVariableCombined("BARREL","ELECTRON_BARREL_DETA",true,"electron_barrel_good");
  electron_barrel->addVariable("ELECTRON_BARREL_DPHI");
  electron_barrel->addVariable("ELECTRON_BARREL_HADOVEREM");
  electron_barrel->addVariable("ELECTRON_BARREL_SIGMAIETAIETA");
  handler->addObjectVariable("ELECTRON_BARREL",electron_barrel);

  ObjectVariableCombined* electron_endcap = new ObjectVariableCombined("ENDCAP","ELECTRON_ENDCAP_DETA",true,"electron_endcap_good");
  electron_endcap->addVariable("ELECTRON_ENDCAP_DPHI");
  electron_endcap->addVariable("ELECTRON_ENDCAP_HADOVEREM");
  electron_endcap->addVariable("ELECTRON_ENDCAP_SIGMAIETAIETA");
  handler->addObjectVariable("ELECTRON_ENDCAP",electron_endcap);

  handler->addObjectVariable("ELECTRON_COMBINED",new ObjectVariableCombined("ELECTRON_BARREL","ELECTRON_ENDCAP",false,"ELECTRON_COMBINED"));

  handler->addProduct("goodElectrons","ALLELECTRONS");
  handler->addProductCut("goodElectrons","PT10");
  handler->addProductCut("goodElectrons","ETA2p4");
  handler->addProductCut("goodElectrons","IREL0p15");
  handler->addProductCut("goodElectrons","ELECTRON_COMBINED");
  handler->addProductCut("goodElectrons","ELECTRON_PROMPT");
  handler->addProductCut("goodElectrons","ELECTRON_MISSING_HITS");
  handler->addProductCut("goodElectrons","ELECTRON_EMINUSP");
  handler->addProductCut("goodElectrons","ELECTRON_CONVERSION");
  handler->addProductCut("goodElectrons","ELECTRON_VERT_DZ");
  handler->addProductCut("goodElectrons","ELECTRON_NOTGAP");

  //////////////
  ///Tau Cuts///
  //////////////

  handler->addObjectVariable("TAU_DECAYMODEFINDING",new ObjectVariableInRange<double>("DISC_DECAYMODEFINDING",0.9,1e6));
  handler->addObjectVariable("TAU_AGAINSTELECTRONMVA",new ObjectVariableInRange<double>("DISC_AGAINSTELECTRONMVA",0.9,1e6));
  handler->addObjectVariable("TAU_AGAINSTMUONTIGHT",new ObjectVariableInRange<double>("DISC_AGAINSTMUONTIGHT",0.9,1e6));
  handler->addObjectVariable("TAU_BYLOOSECOMBINEDISODBSUMPTCORR",new ObjectVariableInRange<double>("DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR",0.9,1e6));
  handler->addObjectVariable("TAU_CHARGE_ZERO",new ObjectVariableInRange<double>("PF_SIGNALCHARGE",-0.9,0.9));
  handler->addObjectVariable("TAU_SIGNAL_CHARGE",new ObjectVariableReversed("TAU_CHARGE_ZERO"));

  handler->addProduct("goodTaus","ALLTAUS");
  handler->addProductCut("goodTaus","PT20");
  handler->addProductCut("goodTaus","ETA2p3");
  handler->addProductCut("goodTaus","TAU_DECAYMODEFINDING");
  handler->addProductCut("goodTaus","TAU_AGAINSTELECTRONMVA");
  handler->addProductCut("goodTaus","TAU_AGAINSTMUONTIGHT");
  handler->addProductCut("goodTaus","TAU_BYLOOSECOMBINEDISODBSUMPTCORR");
  handler->addProductCut("goodTaus","TAU_SIGNAL_CHARGE");


  //////////////
  ///Jet Cuts///
  /////////////

  handler->addObjectVariable("JET_CHARGEDEMFRACTION",new ObjectVariableInRange<double>("CHARGEDEMFRACTION",0,0.99));
  handler->addObjectVariable("JET_CHARGEDMULTIPLICITY",new ObjectVariableInRange<int>("CHARGEDHADRONMULTIPLICITY",1,10000));
  handler->addObjectVariable("JET_CHARGEDHADRONFRACTION", new ObjectVariableInRange<double>("CHARGEDHADRONFRACTION",0.00001,1.0));
  handler->addObjectVariable("JET_NCONSTITUENTS", new ObjectVariableInRange<int>("NUMBERCONSTITUENTS",2,10000));
  handler->addObjectVariable("JET_NEUTRALEMFRACTION", new ObjectVariableInRange<double>("NEUTRALEMFRACTION",0.0,0.99));
  handler->addObjectVariable("JET_NEUTRALHADRONFRACTION",new ObjectVariableInRange<double>("NEUTRALHADRONFRACTION",0.0,0.99));


  handler->addProduct("goodJets","ALLJETS");
  handler->addProductCut("goodJets","PT30");
  handler->addProductCut("goodJets","ETA2p5");
  handler->addProductCut("goodJets","JET_CHARGEDEMFRACTION");
  handler->addProductCut("goodJets","JET_CHARGEDMULTIPLICITY");
  handler->addProductCut("goodJets","JET_CHARGEDHADRONFRACTION");
  handler->addProductCut("goodJets","JET_NCONSTITUENTS");
  handler->addProductCut("goodJets","JET_NEUTRALEMFRACTION");
  handler->addProductCut("goodJets","JET_NEUTRALHADRONFRACTION");

  handler->addObjectVariable("BJET_CSVL", new ObjectVariableInRange<double>("BDISCPOS_COMBINEDSECONDARYVERTEXBJETTAGS",0.244,1000.0));
  handler->addObjectVariable("BJET_CSVM", new ObjectVariableInRange<double>("BDISCPOS_COMBINEDSECONDARYVERTEXBJETTAGS",0.679,1000.0));

  ////////////////
  ///Track Cuts///
  /////////////////

  handler->addObjectVariable("TRACK_NDOF",new ObjectVariableInRange<double>("NDOF",1,10000));
  handler->addObjectVariable("TRACK_VALID_HITS",new ObjectVariableInRange<int>("NVALIDTRACKERHITS",10,10000));
  handler->addObjectVariable("TRACK_BEAM_D0", new ObjectVariableInRange<double>("BEAM_D0",-0.2,0.2));
  handler->addObjectVariable("TRACK_VERT_DZ", new ObjectVariableInRange<double>("VERT_DZ",-1.0,1.0));
  handler->addObjectVariable("TRACK_PROMPT", new ObjectVariableInRange<double>("VERT_DXY",-0.02,0.02));

  handler->addProduct("goodTracks","ALLRECOTRACKS");
  handler->addProductCut("goodTracks","PT10");
  handler->addProductCut("goodTracks","ETA2p4");
  handler->addProductCut("goodTracks","IREL0p15");
  handler->addProductCut("goodTracks","TRACK_NDOF");
  handler->addProductCut("goodTracks","TRACK_VALID_HITS");
  handler->addProductCut("goodTracks","TRACK_BEAM_D0");
  handler->addProductCut("goodTracks","TRACK_VERT_DZ");
  handler->addProductCut("goodTracks","TRACK_PROMPT");
  
  /////////////////
  ///Photon Cuts///
  /////////////////
  
  handler->addObjectVariable("IRELCHARGEDHADRONISO", new ObjectVariableRelIso("IRELCHARGEDHADRONISO", "CHARGEDHADRONISO"));
  handler->addObjectVariable("IRELNEUTRALHADRONISO", new ObjectVariableRelIso("IRELNEUTRALHADRONISO", "NEUTRALHADRONISO"));
  handler->addObjectVariable("IRELPHOTONISO", new ObjectVariableRelIso("IRELPHOTONISO", "PHOTONISO"));
  
  handler->addObjectVariable("PHOTON_BARREL_SIGMAIETAIETA", new ObjectVariableInRange<double>("SIGMAIETAIETA", -0.011, 0.011));
  handler->addObjectVariable("PHOTON_BARREL_HADOVEREM", new ObjectVariableInRange<double>("HADOVEREM", 0.0, 0.06));
  handler->addObjectVariable("PHOTON_BARREL_IRELCHARGEDHADRONISO", new ObjectVariableInRange<double>("IRELCHARGEDHADRONISO", 0, 0.06));
  handler->addObjectVariable("PHOTON_BARREL_IRELNEUTRALHADRONISO", new ObjectVariableInRange<double>("IRELNEUTRALHADRONISO", 0, 0.16));
  handler->addObjectVariable("PHOTON_BARREL_IRELPHOTONISO", new ObjectVariableInRange<double>("IRELPHOTONISO", 0, 0.08));
  
  handler->addObjectVariable("PHOTON_ENDCAP_SIGMAIETAIETA", new ObjectVariableInRange<double>("SIGMAIETAIETA", -0.034, 0.034));
  handler->addObjectVariable("PHOTON_ENDCAP_HADOVEREM", new ObjectVariableInRange<double>("HADOVEREM", 0.0, 0.05));
  handler->addObjectVariable("PHOTON_ENDCAP_IRELCHARGEDHADRONISO", new ObjectVariableInRange<double>("IRELCHARGEDHADRONISO", 0, 0.05));
  handler->addObjectVariable("PHOTON_ENDCAP_IRELNEUTRALHADRONISO", new ObjectVariableInRange<double>("IRELNEUTRALHADRONISO", 0, 0.10));
  handler->addObjectVariable("PHOTON_ENDCAP_IRELPHOTONISO", new ObjectVariableInRange<double>("IRELPHOTONISO", 0, 0.12));
  
  ObjectVariableCombined* photon_barrel = new ObjectVariableCombined("BARREL", "PHOTON_BARREL_SIGMAIETAIETA", true, "photon_barrel_good");
  photon_barrel->addVariable("PHOTON_BARREL_HADOVEREM");
  photon_barrel->addVariable("PHOTON_BARREL_IRELCHARGEDHADRONISO");
  photon_barrel->addVariable("PHOTON_BARREL_IRELNEUTRALHADRONISO");
  photon_barrel->addVariable("PHOTON_BARREL_IRELPHOTONISO");
  handler->addObjectVariable("PHOTON_BARREL", photon_barrel);
  
  ObjectVariableCombined* photon_endcap = new ObjectVariableCombined("ENDCAP", "PHOTON_ENDCAP_SIGMAIETAIETA", true, "photon_endcap_good");
  photon_barrel->addVariable("PHOTON_ENDCAP_HADOVEREM");
  photon_barrel->addVariable("PHOTON_ENDCAP_IRELCHARGEDHADRONISO");
  photon_barrel->addVariable("PHOTON_ENDCAP_IRELNEUTRALHADRONISO");
  photon_barrel->addVariable("PHOTON_ENDCAP_IRELPHOTONISO");
  handler->addObjectVariable("PHOTON_ENDCAP", photon_endcap);
  
  handler->addObjectVariable("PHOTON_COMBINED", new ObjectVariableCombined("PHOTON_BARREL", "PHOTON_ENDCAP", false, "PHOTON_COMBINED"));
  
  handler->addProduct("goodPhotons", "ALLPHOTONS");
  handler->addProductCut("goodPhotons", "PT15");
  handler->addProductCut("goodPhotons", "ETA2p4");
  handler->addProductCut("goodPhotons", "PHOTON_COMBINED");
  
  //////////////////
  //Threshold cuts//
  //////////////////
  EventVariableThreshold* firstLeptonThreshold = new EventVariableThreshold("FIRSTLEPTHRESH","goodMuons");
  firstLeptonThreshold->addProduct("goodElectrons");
  firstLeptonThreshold->addThreshold(20);
  handler->addEventVariable("FIRSTLEPTHRESH",firstLeptonThreshold);
  handler->addHandlerCut("FIRSTLEPTHRESH");


  /////////////////////////
  ///handler comparisons///
  /////////////////////////

  //ObjectComparisonDeltaR* deltaR0p005 = new ObjectComparisonDeltaR(0.005);
  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
  ObjectComparisonDeltaR* deltaR0p3 = new ObjectComparisonDeltaR(0.3);
  ObjectComparisonDeltaR* deltaR0p4 = new ObjectComparisonDeltaR(0.4);
  ObjectComparisonSkimRecoTracks* trackSelfComp = new ObjectComparisonSkimRecoTracks(0.005);
  ObjectComparisonElectron* electronSelfComp = new ObjectComparisonElectron(0.1);

  handler->addProductSelfComparison("goodMuons",deltaR0p1);
  handler->addProductSelfComparison("goodElectrons",electronSelfComp);
  handler->addProductSelfComparison("goodTracks",trackSelfComp);

  handler->addProductComparison("goodElectrons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTaus","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTaus","goodElectrons",deltaR0p1);

  handler->addProductComparison("goodTracks","goodMuons",deltaR0p1);
  handler->addProductComparison("goodTracks","goodElectrons",deltaR0p1);
  handler->addProductComparison("goodTracks","goodTaus",deltaR0p3);

  handler->addProductComparison("goodJets","goodMuons",deltaR0p4);
  handler->addProductComparison("goodJets","goodElectrons",deltaR0p4);
  handler->addProductComparison("goodJets","goodTaus",deltaR0p4);

  handler->addProductComparison("goodPhotons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodElectrons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTaus",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTracks",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodJets",deltaR0p3);


  //////////////////////////
  ///add derived products///
  //////////////////////////

  handler->addProduct("posGoodMuons","goodMuons");
  handler->addProductCut("posGoodMuons","POSITIVE");
  handler->addProduct("negGoodMuons","goodMuons");
  handler->addProductCut("negGoodMuons","NEGATIVE");

  handler->addProduct("posGoodElectrons","goodElectrons");
  handler->addProductCut("posGoodElectrons","POSITIVE");
  handler->addProduct("negGoodElectrons","goodElectrons");
  handler->addProductCut("negGoodElectrons","NEGATIVE");

  handler->addProduct("bJetsCSVL","goodJets");
  handler->addProduct("bJetsCSVM","bJetsCSVL");
  handler->addProductCut("bJetsCSVL","BJET_CSVL");
  handler->addProductCut("bJetsCSVM","BJET_CSVM");

  handler->addProduct("posGoodTracks","goodTracks");
  handler->addProductCut("posGoodTracks","POSITIVE");
  handler->addProduct("negGoodTracks","goodTracks");
  handler->addProductCut("negGoodTracks","NEGATIVE");

}


void setupVariables(BaseHandler* handler,bool isMC = false)
{
  const double mZ = 91;
  const double mW = 80.385;
  
  handler->addEventVariable("NGOODELECTRONS", new EventVariableN("NGOODELECTRONS","goodElectrons"));
  handler->addEventVariable("NGOODMUONS",new EventVariableN("NGOODMUONS","goodMuons"));
  handler->addEventVariable("NGOODTAUS", new EventVariableN("NGOODTAUS","goodTaus"));
  handler->addEventVariable("NGOODJETS", new EventVariableN("NGOODJETS","goodJets"));
  handler->addEventVariable("NGOODPHOTONS", new EventVariableN("NGOODPHOTONS","goodPhotons"));

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

  EventVariableSumPT* pTgoodMuons = new EventVariableSumPT("PTGOODMUONS","goodMuons");
  handler->addEventVariable("PTGOODMUONS",pTgoodMuons);

  EventVariableSumPT* pTgoodElectrons = new EventVariableSumPT("PTGOODELECTRONS","goodElectrons");
  handler->addEventVariable("PTGOODELECTRONS",pTgoodElectrons);

  EventVariableSumPT* pTgoodPhotons = new EventVariableSumPT("PTGOODPHOTONS","goodPhotons");
  handler->addEventVariable("PTGOODPHOTONS",pTgoodPhotons);

  EventVariableOSSF* OSSF = new EventVariableOSSF("OSSF","goodMuons","",mZ,15);
  OSSF->addProduct("goodElectrons");
  handler->addEventVariable("OSSF",OSSF);

  EventVariableMass* massLeptons = new EventVariableMass("MLEPTONS", "goodElectrons");
  massLeptons->addProduct("goodMuons");
  massLeptons->addProduct("goodTaus");
  handler->addEventVariable("MLEPTONS", massLeptons);

  EventVariableOS* mLowDY = new EventVariableOS("MLOWDY", "goodElectrons", "LOWDY");
  mLowDY->addProduct("goodMuons");
  handler->addEventVariable("MLOWDY", mLowDY);
  
  EventVariableMT* MT = new EventVariableMT("MT", mZ);
  handler->addEventVariable("MT",MT);

  EventVariablePairMass* mWdijet = new EventVariablePairMass("WDIJETMASS", "goodJets", "WJET", mW, 10);
  handler->addEventVariable("WDIJETMASS", mWdijet);
  
  EventVariableN* nbJetsCSVM = new EventVariableN("NBJETSCSVM", "bJetsCSVM");
  handler->addEventVariable("NBJETSCSVM", nbJetsCSVM);
  
  EventVariableN* nbJetsCSVL = new EventVariableN("NBJETSCSVL", "bJetsCSVL");
  handler->addEventVariable("NBJETSCSVL", nbJetsCSVL);
  
  EventVariableN* nLeptons = new EventVariableN("NLEPTONS", "goodElectrons");
  nLeptons->addProduct("goodMuons");
  nLeptons->addProduct("goodTaus");
  handler->addEventVariable("NLEPTONS", nLeptons);
  
  EventVariableInRange<int>* dileptons = new EventVariableInRange<int>("NLEPTONS", 2, 1e6, "DILEPTONS");
  handler->addEventVariable("DILEPTONS", dileptons);
  
  EventVariableInRange<int>* trileptons = new EventVariableInRange<int>("NLEPTONS", 3, 1e6, "TRILEPTONS");
  handler->addEventVariable("TRILEPTONS", trileptons);
  
  EventVariableInRange<double>* mLeptonsOnZ = new EventVariableInRange<double>("MLEPTONS", mZ-15, mZ+15, "MLEPTONSONZ");
  handler->addEventVariable("MLEPTONSONZ", mLeptonsOnZ);

  EventVariableInRange<double>* met0to50 = new EventVariableInRange<double>("MET", 0, 50, "MET0to50");
  handler->addEventVariable("MET0to50", met0to50);

  EventVariableInRange<double>* ht0to200 = new EventVariableInRange<double>("HT", 0, 200, "HT0to200");
  handler->addEventVariable("HT0to200", ht0to200);

  EventVariableReversed* offZ = new EventVariableReversed("ONZ", "OFFZ");
  handler->addEventVariable("OFFZ", offZ);

  EventVariableInRange<int>* NOSSFgt0 = new EventVariableInRange<int>("NOSSF", 1, 1e6, "NOSSFgt0");
  handler->addEventVariable("NOSSFgt0", NOSSFgt0);

  EventVariableCombined* trileptonOnZcut = new EventVariableCombined("TRILEPTONS", "MLEPTONSONZ", true, "TRILEPTONONZ");
  trileptonOnZcut->addVariable("MET0to50");
  trileptonOnZcut->addVariable("HT0to200");
  trileptonOnZcut->addVariable("NOSSFgt0");
  trileptonOnZcut->addVariable("OFFZ");
  handler->addEventVariable("TRILEPTONONZ", trileptonOnZcut);
  
  EventVariableReversed* notTrileptonOnZcut = new EventVariableReversed("TRILEPTONONZ", "NOTTRILEPTONONZ");
  handler->addEventVariable("NOTTRILEPTONONZ", notTrileptonOnZcut);
  
  EventVariableInRange<double>* mLowDYcut = new EventVariableInRange<double>("LOWDYOSMINMLL", 12, 1e6, "MLOWDYCUT");
  handler->addEventVariable("MLOWDYCUT", mLowDYcut);
  
  EventVariableCombined* writeEvent = new EventVariableCombined("DILEPTONS", "MLOWDYCUT", true, "WRITEEVENT");
//  writeEvent->addVariable("NOTTRILEPTONONZ");
  handler->addEventVariable("WRITEEVENT", writeEvent);
}

void addHistograms(BaseHandler* handler)
{
  SignatureTH1F_EventVariable<double>* h_ht = new SignatureTH1F_EventVariable<double>("HT","HT","H_{T} Distribution",200,0,2000);
  handler->addHistogram(h_ht);
  
  SignatureTH1F_EventVariable<double>* h_met = new SignatureTH1F_EventVariable<double>("MET","MET","MET Distribution",50,0,500);
  handler->addHistogram(h_met);

  SignatureTH1F_EventVariable<double>* h_mossf = new SignatureTH1F_EventVariable<double>("MLL","MOSSF","M_{ll} Distribution",200,0,200);
  handler->addHistogram(h_mossf);
  
  SignatureTH1F_ObjectVariable<double>* h_ptEl = new SignatureTH1F_ObjectVariable<double>("PTel","PT","goodElectrons","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptEl);
  
  SignatureTH1F_ObjectVariable<double>* h_etaEl = new SignatureTH1F_ObjectVariable<double>("ETAel","ETA","goodElectrons","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaEl);
  
  SignatureTH1F_ObjectVariable<double>* h_ptMu = new SignatureTH1F_ObjectVariable<double>("PTmu","PT","goodMuons","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptMu);
  
  SignatureTH1F_ObjectVariable<double>* h_etaMu = new SignatureTH1F_ObjectVariable<double>("ETAmu","ETA","goodMuons","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaMu);
}


void setupFilterCuts(BaseHandler* handler)
{
  handler->addHandlerCut("PRIMARYVERTEXFILTER");
  handler->addHandlerCut("NOSCRAPINGFILTER");
  handler->addHandlerCut("HBHENOISEFILTER");
  handler->addHandlerCut("CSCTIGHTHALOFILTER");
  handler->addHandlerCut("HCALLASEREVENTFILTER");
  handler->addHandlerCut("ECALDEADCELLTRIGGERPRIMITIVEFILTER");
  handler->addHandlerCut("TRACKINGFAILUREFILTER");
  handler->addHandlerCut("EEBADSCFILTER");

}

void setupMC(BaseHandler* handler, TString pufile, bool doMatching = true)
{

  if(doMatching) {
	  ////Additional products
	  
	  ObjectVariableValueInList<int>* pdgid11 = new ObjectVariableValueInList<int>("PDGID",11);
	  pdgid11->addValue(-11);
	  ObjectVariableValueInList<int>* pdgid13 = new ObjectVariableValueInList<int>("PDGID",13);
	  pdgid13->addValue(-13);
	  ObjectVariableValueInList<int>* pdgid15 = new ObjectVariableValueInList<int>("PDGID",15);
	  pdgid15->addValue(-15);

	  ObjectVariableValueInList<int>* motherWZTau = new ObjectVariableValueInList<int>("MOTHER_PDGID",24);
	  motherWZTau->addValue(-24);
	  motherWZTau->addValue(23);
	  motherWZTau->addValue(15);
	  motherWZTau->addValue(-15);


	  handler->addObjectVariable("PDGID11",pdgid11);
	  handler->addObjectVariable("PDGID13",pdgid13);
	  handler->addObjectVariable("PDGID15",pdgid15);
	  handler->addObjectVariable("MOTHERWZTau",motherWZTau);

	  handler->addProduct("MCelectrons","ALLMCPARTICLES");
	  handler->addProductCut("MCelectrons","PDGID11");

	  handler->addProduct("MCelectronsFromWZTau","MCelectrons");
	  handler->addProductCut("MCelectronsFromWZTau","MOTHERWZTau");

	  handler->addProduct("MCmuons","ALLMCPARTICLES");
	  handler->addProductCut("MCmuons","PDGID13");

	  handler->addProduct("MCmuonsFromWZTau","MCmuons");
	  handler->addProductCut("MCmuonsFromWZTau","MOTHERWZTau");

	  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
	  handler->addProductSelfComparison("MCmuonsFromWZTau",deltaR0p1);
	  handler->addProductSelfComparison("MCelectronsFromWZTau",deltaR0p1);

	  ObjectComparisonMatchDeltaRCharge* mcMatchComparison = new ObjectComparisonMatchDeltaRCharge(0.1);
	  handler->addProductComparison("goodElectrons","MCelectronsFromWZTau",mcMatchComparison,false);
	  handler->addProductComparison("goodMuons","MCmuonsFromWZTau",mcMatchComparison,false);
  }



  TFile infile(pufile.Data());
  TH1F* pu = (TH1F*)infile.Get("puweights");
  pu->SetDirectory(0);
  EventVariableTH1<double>* pureweight = new EventVariableTH1<double>("pureweight","TRUENUMINTERACTIONS",pu);
  handler->addEventVariable("PUWEIGHT",pureweight);
  handler->addWeightVariable("PUWEIGHT");

  //eps_inf*erf((pt-c)/sigma) + eps_c * (1-erf((pt-c)/sigma))
  TF1* electronIDISO = new TF1("elidiso","(TMath::Erf((x-[0])/[1])*([2]-[3])+[3])*(TMath::Erf((x-[0])/[4])*([5]-[6])+[6])",8,10000);
  electronIDISO->SetParameter(0,8);
  electronIDISO->SetParameter(1,40);
  electronIDISO->SetParameter(2,1.0055);
  electronIDISO->SetParameter(3,0.90);
  electronIDISO->SetParameter(4,11.83);
  electronIDISO->SetParameter(5,1.0074);
  electronIDISO->SetParameter(6,0.76);

  TF1* muonIDISO = new TF1("muidiso","(TMath::Erf((x-[0])/[1])*([2]-[3])+[3])*[4]",8,10000);
  muonIDISO->SetParameter(0,8);
  muonIDISO->SetParameter(1,10.9);
  muonIDISO->SetParameter(2,0.9905);
  muonIDISO->SetParameter(3,0.8584);
  muonIDISO->SetParameter(4,0.9901);

  handler->addEventVariable("ELIDISOWEIGHT",new EventVariableObjectWeightPtTF1("ELIDISO","goodElectrons",electronIDISO));
  handler->addEventVariable("MUIDISOWEIGHT",new EventVariableObjectWeightPtTF1("MUIDISO","goodMuons",muonIDISO));
  handler->addWeightVariable("ELIDISOWEIGHT");
  handler->addWeightVariable("MUIDISOWEIGHT");
  
  handler->addEventVariable("TRIGGERWEIGHT", new EventVariableTriggerWeight("TRIGGERWEIGHT"));
  handler->addWeightVariable("TRIGGERWEIGHT");
}

void setupOnZSignatures(BaseHandler* handler)
{
  handler->addEventVariable("getwoGoodMuons", new EventVariableInRange<int>("NGOODMUONS",2,100000));
  handler->addEventVariable("getwoGoodElectrons",new EventVariableInRange<int>("NGOODELECTRONS",2,100000));

  handler->addSignature("Mu2OnZ")
    ->addCut("getwoGoodMuons")
    ->addCut("ONZ")
    ;
  handler->addSignature("El2OnZ")
    ->addCut("getwoGoodElectrons")
    ->addCut("ONZ")
    ;

  SignatureTH1F_N* nnegmuons = new SignatureTH1F_N("nmuonsneg","negGoodMuons");
  SignatureTH1F_N* nposmuons = new SignatureTH1F_N("nmuonspos","posGoodMuons");
  SignatureTH1F_N* nnegelectrons = new SignatureTH1F_N("nelectronsneg","negGoodElectrons");
  SignatureTH1F_N* nposelectrons = new SignatureTH1F_N("nelectronspos","posGoodElectrons");
  SignatureTH1F_N* nnegtracks = new SignatureTH1F_N("ntracksneg","negGoodTracks");
  SignatureTH1F_N* npostracks = new SignatureTH1F_N("ntrackspos","posGoodTracks");

  handler->addHistogram(nnegmuons,"OnZ");
  handler->addHistogram(nposmuons,"OnZ");
  handler->addHistogram(nnegelectrons,"OnZ");
  handler->addHistogram(nposelectrons,"OnZ");
  handler->addHistogram(nnegtracks,"OnZ");
  handler->addHistogram(npostracks,"OnZ");

}

void setupSignatures(BaseHandler* handler)
{
  TString products[6] = {"posGoodMuons","negGoodMuons","posGoodElectrons","negGoodElectrons","posGoodTracks","negGoodTracks"};
  for(int i = 0; i < 6; i++){
    //products[i].ToUpper();
    TString varname = TString::Format("N%s",products[i].Data());
    varname.ToUpper();
    handler->addEventVariable(varname,new EventVariableN(varname,products[i]));
    for(int j = 0; j < 4; j++){
      TString varname1 = TString::Format("N%sEQ%i",products[i].Data(),j);
      varname1.ToUpper();
      handler->addEventVariable(varname1,new EventVariableInRange<int>(varname,j,j,varname1));
    }
  }

  //Signal channels
  for(int i_posMuons = 0; i_posMuons < 4; i_posMuons++){
    for(int i_negMuons = 0; i_negMuons < 4; i_negMuons++){
      for(int i_posElectrons = 0; i_posElectrons < 4; i_posElectrons++){
	for(int i_negElectrons = 0; i_negElectrons < 4; i_negElectrons++){
	  if(i_posMuons + i_negMuons + i_posElectrons + i_negElectrons != 3)continue;
	  int nMu = i_posMuons + i_negMuons;
	  int nEl = i_posElectrons + i_negElectrons;
	  //int nTr = i_posTracks + i_negTracks;
	  int qMu = i_posMuons - i_negMuons;
	  int qEl = i_posElectrons - i_negElectrons;
	  //int qTr = i_posTracks - i_negTracks;
	  TString chanName = makeName(qMu,nMu,qEl,nEl,0,0);
	  
	  //cout<<chanName<<" mu+: "<<i_posMuons<<" mu-: "<<i_negMuons<<" el+: "<<i_posElectrons<<" el-: "<<i_negElectrons<<" tr+: "<<i_posTracks<<" tr-: "<<i_negTracks<<" "<<endl;
	  
	  TString cut_posMuons = TString::Format("NPOSGOODMUONSEQ%i",i_posMuons);
	  TString cut_negMuons = TString::Format("NNEGGOODMUONSEQ%i",i_negMuons);
	  TString cut_posElectrons = TString::Format("NPOSGOODELECTRONSEQ%i",i_posElectrons);
	  TString cut_negElectrons = TString::Format("NNEGGOODELECTRONSEQ%i",i_negElectrons);
	  
	  handler->addSignature(chanName)
	    ->addCut(cut_posMuons)
	    ->addCut(cut_negMuons)
	    ->addCut(cut_posElectrons)
	    ->addCut(cut_negElectrons)
	    ;
	}
      }
    }
  }

  cout<<"test"<<endl;


  //Sideband channels
  for(int i_posMuons = 0; i_posMuons < 4; i_posMuons++){
    for(int i_negMuons = 0; i_negMuons < 4; i_negMuons++){
      for(int i_posElectrons = 0; i_posElectrons < 4; i_posElectrons++){
	for(int i_negElectrons = 0; i_negElectrons < 4; i_negElectrons++){
	  if(i_posMuons + i_negMuons + i_posElectrons + i_negElectrons != 2)continue;
	  //cout<<i_posMuons<<" "<<i_negMuons<<" "<<i_posElectrons<<" "<<i_negElectrons<<endl;
	  for(int i_tracks = 1; i_tracks < 4; i_tracks++){
	    int nMu = i_posMuons + i_negMuons;
	    int nEl = i_posElectrons + i_negElectrons;
	    int nTr = i_tracks;
	    int qMu = i_posMuons - i_negMuons;
	    int qEl = i_posElectrons - i_negElectrons;
	    int qTrp = i_tracks;
	    int qTrn = -i_tracks;
	    TString chanNamep = makeName(qMu,nMu,qEl,nEl,qTrp,nTr);
	    TString chanNamem = makeName(qMu,nMu,qEl,nEl,qTrn,nTr);
	    
	    cout<<chanNamep<<" mu+: "<<i_posMuons<<" mu-: "<<i_negMuons<<" el+: "<<i_posElectrons<<" el-: "<<i_negElectrons<<" tr: "<<i_tracks<<endl;
	    
	    TString cut_posMuons = TString::Format("NPOSGOODMUONSEQ%i",i_posMuons);
	    TString cut_negMuons = TString::Format("NNEGGOODMUONSEQ%i",i_negMuons);
	    TString cut_posElectrons = TString::Format("NPOSGOODELECTRONSEQ%i",i_posElectrons);
	    TString cut_negElectrons = TString::Format("NNEGGOODELECTRONSEQ%i",i_negElectrons);
	    TString cut_posTracks = TString::Format("NPOSGOODTRACKSEQ%i",i_tracks);
	    TString cut_negTracks = TString::Format("NNEGGOODTRACKSEQ%i",i_tracks);
	    
	    handler->addSignature(chanNamep)
	      ->addCut(cut_posMuons)
	      ->addCut(cut_negMuons)
	      ->addCut(cut_posElectrons)
	      ->addCut(cut_negElectrons)
	      ->addCut(cut_posTracks)
	      ;
	    handler->addSignature(chanNamem)
	      ->addCut(cut_posMuons)
	      ->addCut(cut_negMuons)
	      ->addCut(cut_posElectrons)
	      ->addCut(cut_negElectrons)
	      ->addCut(cut_negTracks)
	      ;
	  }
	}
      }
    }
  }
 


}


void setupControlRegions(BaseHandler* handler)
{

}
