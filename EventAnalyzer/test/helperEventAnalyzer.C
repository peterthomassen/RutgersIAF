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
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectVariableVector.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableObjectWeightPtTF1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOS.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableOSSF.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariablePairMass.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariablePairMass2.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableProductAngle.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSumPT.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableThreshold.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTH1.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableTriggerWeight.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonDeltaR.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableAssociateVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableCombined.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableElectronTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableInRange.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMethod.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableMuonTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableRelIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableReversed.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableTauTotalIso.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValue.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_ObjectVariable.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonSkimRecoTracks.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonElectron.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_N.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableValueInList.h"
#include "RutgersIAF/EventAnalyzer/interface/ObjectComparisonMatchDeltaRCharge.h"
#include "RutgersIAF/EventAnalyzer/interface/EventVariableSmearMET.h"

// Load library, see https://root.cern.ch/phpBB2/viewtopic.php?f=3&t=19471
namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFEventAnalyzer.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void setupProducts(BaseHandler* handler)
{
  //////////////////
  ///General Cuts///
  //////////////////
  handler->addObjectVariable("PT",new ObjectVariableMethod("PT", &SignatureObject::Pt));
  handler->addObjectVariable("ETA",new ObjectVariableMethod("ETA", &SignatureObject::Eta));
  handler->addObjectVariable("M",new ObjectVariableMethod("M", &SignatureObject::M));
  ObjectVariableInRange<double>* leptonPtCut = new ObjectVariableInRange<double>("PT",10.0,10000.0,"leptonPtCut");
  ObjectVariableInRange<double>* leptonEtaCut = new ObjectVariableInRange<double>("ETA",-2.4,2.4,"leptonEtaCut");
  ObjectVariableInRange<double>* PT40 = new ObjectVariableInRange<double>("PT",40.0,10000.0,"PT40");
  handler->addObjectVariable("MUONTOTALISO",new ObjectVariableMuonTotalIso("TOTALISO"),false);
  handler->addObjectVariable("ELECTRONTOTALISO",new ObjectVariableElectronTotalIso("TOTALISO"),false);
  handler->addObjectVariable("DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR",new ObjectVariableInRange<double>("DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR",0.9,1e6));
  handler->addObjectVariable("!DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR",new ObjectVariableReversed("DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR", "!DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR"));
  handler->addObjectVariable("TAUTOTALISO",new ObjectVariableTauTotalIso("TOTALISO"),false);
  handler->addObjectVariable("RELISO",new ObjectVariableRelIso("RELISO"));

  handler->addObjectVariable("PT7",new ObjectVariableInRange<double>("PT",7.0,10000.0,"PT7"));
  handler->addObjectVariable("PT10",leptonPtCut);
  handler->addObjectVariable("PT15",new ObjectVariableInRange<double>("PT",15.0,10000.0,"PT15"));
  handler->addObjectVariable("PT20",new ObjectVariableInRange<double>("PT",20.0,10000.0,"PT20"));
  handler->addObjectVariable("PT30",new ObjectVariableInRange<double>("PT",30.0,10000.0,"PT30"));
  handler->addObjectVariable("PT40",PT40);
  handler->addObjectVariable("ETA2p3",new ObjectVariableInRange<double>("ETA",-2.3,2.3,"ETA2p3"));
  handler->addObjectVariable("ETA2p4",leptonEtaCut);
  handler->addObjectVariable("ETA2p5",new ObjectVariableInRange<double>("ETA",-2.5,2.5,"ETA2p5"));
  handler->addObjectVariable("IREL0p15",new ObjectVariableInRange<double>("RELISO",0,0.15,"IREL0p15"));
  handler->addObjectVariable("IREL0p30",new ObjectVariableInRange<double>("RELISO",0,0.30,"IREL0p30"));
  handler->addObjectVariable("NOTIREL0p15",new ObjectVariableInRange<double>("RELISO",0.15,10000.0,"NOTIREL0p15"));
  handler->addObjectVariable("ISO0to2",new ObjectVariableInRange<double>("TOTALISO",0,2,"ISO0to2"));
  handler->addObjectVariable("ISO6to15",new ObjectVariableInRange<double>("TOTALISO",6,15,"ISO5to15"));
  handler->addObjectVariable("ISOgt15",new ObjectVariableInRange<double>("TOTALISO",15,1e6,"ISOgt15"));
  handler->addObjectVariable("BARREL",new ObjectVariableInRange<double>("ETA",-1.5,1.5,"barrelEta"));
  handler->addObjectVariable("ENDCAP",new ObjectVariableReversed("BARREL","endcapEta"));
  handler->addObjectVariable("POSITIVE",new ObjectVariableInRange<int>("CHARGE",0,10,"CHARGEPOS"));
  handler->addObjectVariable("NEGATIVE",new ObjectVariableInRange<int>("CHARGE",-10,0,"CHARGENEG"));

  handler->addObjectVariable("LEADTRACKDZ",new ObjectVariableAssociateVariable<double>("LEADTRACK","DZ","LEADTRACKDZ"));
  handler->addObjectVariable("LEADTRACKDXY",new ObjectVariableAssociateVariable<double>("LEADTRACK","DXY","LEADTRACKDXY"));

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

  handler->addProduct("basicMuons","ALLMUONS");
  handler->addProductCut("basicMuons","PT10");
  handler->addProductCut("basicMuons","ETA2p4");
  handler->addProductCut("basicMuons","MUON_VALID_INNER_PIXEL_HITS");
  handler->addProductCut("basicMuons","MUON_TRACK_LAYERS_WM");
  handler->addProductCut("basicMuons","MUON_MATCHES");
  handler->addProductCut("basicMuons","ISPF");
  handler->addProductCut("basicMuons","MUON_ISGLOBAL");
  handler->addProductCut("basicMuons","MUON_VALID_MUON_HITS");
  handler->addProductCut("basicMuons","MUON_NORMALIZED_CHI2");
  handler->addProductCut("basicMuons","MUON_INNER_VERT_DZ");
  
  handler->addProduct("goodMuons","basicMuons");
  handler->addProductCut("goodMuons","IREL0p15");
  handler->addProductCut("goodMuons","MUON_PROMPT");

  handler->addProduct("isoNonPromptMuons","basicMuons");
  handler->addProductCut("isoNonPromptMuons","IREL0p15");
  handler->addProductCut("isoNonPromptMuons","MUON_NONPROMPT");
  
  handler->addProduct("nonPromptMuons","basicMuons");
  handler->addProductCut("nonPromptMuons","MUON_NONPROMPT");
  
  handler->addProduct("promptNonIsoMuons","basicMuons");
  handler->addProductCut("promptNonIsoMuons","NOTIREL0p15");
  handler->addProductCut("promptNonIsoMuons","MUON_PROMPT");
  
  handler->addProduct("nonPromptNonIsoMuons","basicMuons");
  handler->addProductCut("nonPromptNonIsoMuons","NOTIREL0p15");
  handler->addProductCut("nonPromptNonIsoMuons","MUON_NONPROMPT");
  
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
  handler->addObjectVariable("ELECTRON_NONPROMPT",new ObjectVariableReversed("ELECTRON_PROMPT","ELECTRON_NONPROMPT"));

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

  handler->addProduct("basicElectrons","ALLELECTRONS");
  handler->addProductCut("basicElectrons","PT10");
  handler->addProductCut("basicElectrons","ETA2p4");
  handler->addProductCut("basicElectrons","ELECTRON_COMBINED");
  handler->addProductCut("basicElectrons","ELECTRON_MISSING_HITS");
  handler->addProductCut("basicElectrons","ELECTRON_EMINUSP");
  handler->addProductCut("basicElectrons","ELECTRON_CONVERSION");
  handler->addProductCut("basicElectrons","ELECTRON_VERT_DZ");
  handler->addProductCut("basicElectrons","ELECTRON_NOTGAP");

  handler->addProduct("goodElectrons","basicElectrons");
  handler->addProductCut("goodElectrons","IREL0p15");
  handler->addProductCut("goodElectrons","ELECTRON_PROMPT");

  handler->addProduct("isoNonPromptElectrons","basicElectrons");
  handler->addProductCut("isoNonPromptElectrons","IREL0p15");
  handler->addProductCut("isoNonPromptElectrons","ELECTRON_NONPROMPT");
  
  handler->addProduct("nonPromptElectrons","basicElectrons");
  handler->addProductCut("nonPromptElectrons","ELECTRON_NONPROMPT");
    
  handler->addProduct("promptNonIsoElectrons","basicElectrons");
  handler->addProductCut("promptNonIsoElectrons","NOTIREL0p15");
  handler->addProductCut("promptNonIsoElectrons","ELECTRON_PROMPT");
  
  handler->addProduct("nonPromptNonIsoElectrons","basicElectrons");
  handler->addProductCut("nonPromptNonIsoElectrons","NOTIREL0p15");
  handler->addProductCut("nonPromptNonIsoElectrons","ELECTRON_NONPROMPT");
  
  //////////////
  ///Tau Cuts///
  //////////////

  handler->addObjectVariable("TAU_DECAYMODEFINDING",new ObjectVariableInRange<double>("DISC_DECAYMODEFINDING",0.9,1e6));
  handler->addObjectVariable("TAU_AGAINSTELECTRONMVA",new ObjectVariableInRange<double>("DISC_AGAINSTELECTRONMVA",0.9,1e6));
  handler->addObjectVariable("TAU_AGAINSTMUONTIGHT",new ObjectVariableInRange<double>("DISC_AGAINSTMUONTIGHT",0.9,1e6));
  handler->addObjectVariable("TAU_CHARGE_ZERO",new ObjectVariableInRange<double>("PF_SIGNALCHARGE",-0.9,0.9));
  handler->addObjectVariable("TAU_SIGNAL_CHARGE",new ObjectVariableReversed("TAU_CHARGE_ZERO"));

  handler->addProduct("basicTaus","ALLTAUS");
  handler->addProductCut("basicTaus","PT20");
  handler->addProductCut("basicTaus","ETA2p3");
  handler->addProductCut("basicTaus","TAU_DECAYMODEFINDING");
  handler->addProductCut("basicTaus","TAU_AGAINSTELECTRONMVA");
  handler->addProductCut("basicTaus","TAU_AGAINSTMUONTIGHT");
  handler->addProductCut("basicTaus","TAU_SIGNAL_CHARGE");

  handler->addProduct("goodTaus","basicTaus");
  handler->addProductCut("goodTaus","DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR"); // supposed to contain ISO0to2 -- what else?
  //handler->addProductCut("goodTaus","ISO0to2");

  handler->addProduct("nonIsoTaus", "basicTaus");
  handler->addProductCut("nonIsoTaus", "!DISC_BYLOOSECOMBINEDISOLATIONDELTABETACORR");

/*  handler->addProduct("sidebandTaus","basicTaus");
  handler->addProductCut("sidebandTaus","ISO6to15");

  handler->addProduct("otherTaus","basicTaus");
  handler->addProductCut("otherTaus","ISOgt15");
*/

  ////////////////
  ///Track Cuts///
  /////////////////

  handler->addObjectVariable("TRACK_NDOF",new ObjectVariableInRange<double>("NDOF",1,10000));
  handler->addObjectVariable("TRACK_VALID_HITS",new ObjectVariableInRange<int>("NVALIDTRACKERHITS",10,10000));
  handler->addObjectVariable("TRACK_BEAM_D0", new ObjectVariableInRange<double>("BEAM_D0",-0.2,0.2));
  handler->addObjectVariable("TRACK_VERT_DZ", new ObjectVariableInRange<double>("VERT_DZ",-1.0,1.0));
  handler->addObjectVariable("TRACK_PROMPT", new ObjectVariableInRange<double>("VERT_DXY",-0.02,0.02));
  handler->addObjectVariable("TRACK_NONPROMPT", new ObjectVariableReversed("TRACK_PROMPT","TRACK_NONPROMPT"));

  // Inclusive tracks
  handler->addProduct("inclusiveTracks","ALLRECOTRACKS");
  handler->addProductCut("inclusiveTracks","PT10");
  handler->addProductCut("inclusiveTracks","ETA2p4");
  handler->addProductCut("inclusiveTracks","TRACK_NDOF");
  handler->addProductCut("inclusiveTracks","TRACK_VALID_HITS");
  handler->addProductCut("inclusiveTracks","TRACK_BEAM_D0");
  handler->addProductCut("inclusiveTracks","TRACK_VERT_DZ");
  
  handler->addProduct("goodInclusiveTracks","inclusiveTracks");
  handler->addProductCut("goodInclusiveTracks","IREL0p15");
  handler->addProductCut("goodInclusiveTracks","TRACK_PROMPT");
  
  handler->addProduct("promptInclusiveTracks","inclusiveTracks");
  handler->addProductCut("promptInclusiveTracks","TRACK_PROMPT");
  
  handler->addProduct("promptNonIsoInclusiveTracks","inclusiveTracks");
  handler->addProductCut("promptNonIsoInclusiveTracks","NOTIREL0p15");
  handler->addProductCut("promptNonIsoInclusiveTracks","TRACK_PROMPT");
  
  handler->addProduct("isoInclusiveTracks","inclusiveTracks");
  handler->addProductCut("isoInclusiveTracks","IREL0p15");
  
  handler->addProduct("isoNonPromptInclusiveTracks","inclusiveTracks");
  handler->addProductCut("isoNonPromptInclusiveTracks","IREL0p15");
  handler->addProductCut("isoNonPromptInclusiveTracks","TRACK_NONPROMPT");
  
  handler->addProduct("nonIsoNonPromptInclusiveTracks","inclusiveTracks");
  handler->addProductCut("nonIsoNonPromptInclusiveTracks","NOTIREL0p15");
  handler->addProductCut("nonIsoNonPromptInclusiveTracks","TRACK_NONPROMPT");
  
  handler->addProduct("inclusiveTracks7","ALLRECOTRACKS");
  handler->addProductCut("inclusiveTracks7","PT7");
  handler->addProductCut("inclusiveTracks7","ETA2p4");
  handler->addProductCut("inclusiveTracks7","TRACK_NDOF");
  handler->addProductCut("inclusiveTracks7","TRACK_VALID_HITS");
  handler->addProductCut("inclusiveTracks7","TRACK_BEAM_D0");
  handler->addProductCut("inclusiveTracks7","TRACK_VERT_DZ");
  
  handler->addProduct("promptInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("promptInclusiveTracks7","TRACK_PROMPT");
  
  handler->addProduct("promptIREL0p30InclusiveTracks7","promptInclusiveTracks7");
  handler->addProductCut("promptIREL0p30InclusiveTracks7","IREL0p30");
  
  handler->addProduct("promptNonIsoInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("promptNonIsoInclusiveTracks7","NOTIREL0p15");
  handler->addProductCut("promptNonIsoInclusiveTracks7","TRACK_PROMPT");
  
  handler->addProduct("isoInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("isoInclusiveTracks7","IREL0p15");
  
  handler->addProduct("isoNonPromptInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("isoNonPromptInclusiveTracks7","IREL0p15");
  handler->addProductCut("isoNonPromptInclusiveTracks7","TRACK_NONPROMPT");
  
  handler->addProduct("nonIsoNonPromptInclusiveTracks7","inclusiveTracks7");
  handler->addProductCut("nonIsoNonPromptInclusiveTracks7","NOTIREL0p15");
  handler->addProductCut("nonIsoNonPromptInclusiveTracks7","TRACK_NONPROMPT");
  
  // Regular tracks
  handler->addProduct("basicTracks","ALLRECOTRACKS");
  handler->addProductCut("basicTracks","PT10");
  handler->addProductCut("basicTracks","ETA2p4");
  handler->addProductCut("basicTracks","TRACK_NDOF");
  handler->addProductCut("basicTracks","TRACK_VALID_HITS");
  handler->addProductCut("basicTracks","TRACK_BEAM_D0");
  handler->addProductCut("basicTracks","TRACK_VERT_DZ");
  
  handler->addProduct("goodTracks","basicTracks");
  handler->addProductCut("goodTracks","IREL0p15");
  handler->addProductCut("goodTracks","TRACK_PROMPT");
  
  handler->addProduct("promptTracks","basicTracks");
  handler->addProductCut("promptTracks","TRACK_PROMPT");
  
  handler->addProduct("promptNonIsoTracks","basicTracks");
  handler->addProductCut("promptNonIsoTracks","NOTIREL0p15");
  handler->addProductCut("promptNonIsoTracks","TRACK_PROMPT");
  
  handler->addProduct("isoTracks","basicTracks");
  handler->addProductCut("isoTracks","IREL0p15");
  
  handler->addProduct("isoNonPromptTracks","basicTracks");
  handler->addProductCut("isoNonPromptTracks","IREL0p15");
  handler->addProductCut("isoNonPromptTracks","TRACK_NONPROMPT");
  
  handler->addProduct("basicTracks7","ALLRECOTRACKS");
  handler->addProductCut("basicTracks7","PT7");
  handler->addProductCut("basicTracks7","ETA2p4");
  handler->addProductCut("basicTracks7","TRACK_NDOF");
  handler->addProductCut("basicTracks7","TRACK_VALID_HITS");
  handler->addProductCut("basicTracks7","TRACK_BEAM_D0");
  handler->addProductCut("basicTracks7","TRACK_VERT_DZ");
  
  handler->addProduct("promptTracks7","basicTracks7");
  handler->addProductCut("promptTracks7","TRACK_PROMPT");
  
  handler->addProduct("promptNonIsoTracks7","basicTracks7");
  handler->addProductCut("promptNonIsoTracks7","NOTIREL0p15");
  handler->addProductCut("promptNonIsoTracks7","TRACK_PROMPT");
  
  handler->addProduct("isoTracks7","basicTracks7");
  handler->addProductCut("isoTracks7","IREL0p15");
  
  handler->addProduct("isoNonPromptTracks7","basicTracks7");
  handler->addProductCut("isoNonPromptTracks7","IREL0p15");
  handler->addProductCut("isoNonPromptTracks7","TRACK_NONPROMPT");
  
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
  handler->addProductCut("goodPhotons", "PT10");
  handler->addProductCut("goodPhotons", "ETA2p4");
  handler->addProductCut("goodPhotons", "PHOTON_COMBINED");
  
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
  handler->addProductSelfComparison("inclusiveTracks",trackSelfComp);
  handler->addProductSelfComparison("inclusiveTracks7",trackSelfComp);

  handler->addProductComparison("goodElectrons","goodMuons",deltaR0p1);
  handler->addProductComparison("basicTaus","goodMuons",deltaR0p1);
  handler->addProductComparison("basicTaus","goodElectrons",deltaR0p1);

  handler->addProductComparison("basicTracks","goodMuons",deltaR0p1);
  handler->addProductComparison("basicTracks","goodElectrons",deltaR0p1);
  handler->addProductComparison("basicTracks","goodTaus",deltaR0p3);

  handler->addProductComparison("basicTracks7","goodMuons",deltaR0p1);
  handler->addProductComparison("basicTracks7","goodElectrons",deltaR0p1);
  handler->addProductComparison("basicTracks7","goodTaus",deltaR0p3);

  handler->addProductComparison("goodPhotons","goodMuons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodElectrons",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTaus",deltaR0p1);
  handler->addProductComparison("goodPhotons","goodTracks",deltaR0p1);

  handler->addProductComparison("goodJets","goodMuons",deltaR0p4);
  handler->addProductComparison("goodJets","goodElectrons",deltaR0p4);
  handler->addProductComparison("goodJets","goodTaus",deltaR0p4);
  handler->addProductComparison("goodJets","goodPhotons",deltaR0p3);


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


void setupVariables(BaseHandler* handler, bool isMC = false, bool singleLeptonSample = false)
{
  const double mZ = 91; // 90
  const double zWidth = 10; // 15
  const double mW = 80.385;
  
  TString products[6] = {"posGoodMuons","negGoodMuons","posGoodElectrons","negGoodElectrons","posGoodTracks","negGoodTracks"};
  for(int i = 0; i < 6; i++){
    TString varname = TString::Format("N%s",products[i].Data());
    varname.ToUpper();
    handler->addEventVariable(varname,new EventVariableN(varname,products[i]));
  }
  
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

  handler->addEventVariable("QNONPROMPTELECTRONS", new EventVariableObjectVariableVector<int>("CHARGE","nonPromptElectrons"));
  handler->addEventVariable("PTNONPROMPTELECTRONS", new EventVariableObjectVariableVector<double>("PT","nonPromptElectrons"));
  handler->addEventVariable("ETANONPROMPTELECTRONS", new EventVariableObjectVariableVector<double>("ETA","nonPromptElectrons"));
  handler->addEventVariable("RELISONONPROMPTELECTRONS", new EventVariableObjectVariableVector<double>("RELISO","nonPromptElectrons"));
  
  handler->addEventVariable("QNONPROMPTMUONS", new EventVariableObjectVariableVector<int>("CHARGE","nonPromptMuons"));
  handler->addEventVariable("PTNONPROMPTMUONS", new EventVariableObjectVariableVector<double>("PT","nonPromptMuons"));
  handler->addEventVariable("ETANONPROMPTMUONS", new EventVariableObjectVariableVector<double>("ETA","nonPromptMuons"));
  handler->addEventVariable("RELISONONPROMPTMUONS", new EventVariableObjectVariableVector<double>("RELISO","nonPromptMuons"));
  
  handler->addEventVariable("RELISOBASICELECTRONS", new EventVariableObjectVariableVector<double>("RELISO","basicElectrons"));
  handler->addEventVariable("DXYBASICELECTRONS", new EventVariableObjectVariableVector<double>("FMVAVAR_D0","basicElectrons"));
  handler->addEventVariable("RELISOBASICMUONS", new EventVariableObjectVariableVector<double>("RELISO","basicMuons"));
  handler->addEventVariable("DXYBASICMUONS", new EventVariableObjectVariableVector<double>("INNERVERTDXY","basicMuons"));
  
  handler->addEventVariable("NBASICTAUS", new EventVariableN("NBASICTAUS","basicTaus"));
  handler->addEventVariable("RELISOBASICTAUS", new EventVariableObjectVariableVector<double>("RELISO","basicTaus"));
  handler->addEventVariable("TOTALISOBASICTAUS", new EventVariableObjectVariableVector<double>("TOTALISO","basicTaus"));
  
  handler->addEventVariable("NGOODTAUS", new EventVariableN("NGOODTAUS","goodTaus"));
  handler->addEventVariable("QGOODTAUS", new EventVariableObjectVariableVector<int>("CHARGE","goodTaus"));
  handler->addEventVariable("PTGOODTAUS", new EventVariableObjectVariableVector<double>("PT","goodTaus"));
  handler->addEventVariable("ETAGOODTAUS", new EventVariableObjectVariableVector<double>("ETA","goodTaus"));
  handler->addEventVariable("TAULEADTRACKDZ", new EventVariableObjectVariableVector<double>("LEADTRACKDZ","goodTaus"));
  handler->addEventVariable("TAULEADTRACKDXY", new EventVariableObjectVariableVector<double>("LEADTRACKDXY","goodTaus"));
  handler->addEventVariable("fakeRoleGOODTAUS", new EventVariableObjectVariableVector<int>("fakeRole","goodTaus"));
  handler->addEventVariable("TOTALISOGOODTAUS", new EventVariableObjectVariableVector<double>("TOTALISO","goodTaus"));
  
//  handler->addEventVariable("NSIDEBANDTAUS", new EventVariableN("NSIDEBANDTAUS","sidebandTaus"));
//  handler->addEventVariable("NOTHERTAUS", new EventVariableN("NOTHERTAUS","otherTaus"));
  handler->addEventVariable("TOTALISONONISOTAUS", new EventVariableObjectVariableVector<double>("TOTALISO","nonIsoTaus"));
  
  handler->addEventVariable("NGOODJETS", new EventVariableN("NGOODJETS","goodJets"));
  handler->addEventVariable("PTGOODJETS", new EventVariableObjectVariableVector<double>("PT","goodJets"));
  handler->addEventVariable("ETAGOODJETS", new EventVariableObjectVariableVector<double>("ETA","goodJets"));
  handler->addEventVariable("BDISCCSVGOODJETS", new EventVariableObjectVariableVector<double>("BDISCPOS_COMBINEDSECONDARYVERTEXBJETTAGS","goodJets"));
  handler->addEventVariable("BDISCJETPROBBJETTAGSGOODJETS", new EventVariableObjectVariableVector<double>("BDISCPOS_JETPROBABILITYBJETTAGS","goodJets"));
  handler->addEventVariable("BDISCJETBPROBBJETTAGSGOODJETS", new EventVariableObjectVariableVector<double>("BDISCPOS_JETBPROBABILITYBJETTAGS","goodJets"));
  
  handler->addEventVariable("NGOODPHOTONS", new EventVariableN("NGOODPHOTONS","goodPhotons"));
  handler->addEventVariable("PTGOODPHOTONS", new EventVariableObjectVariableVector<double>("PT","goodPhotons"));
  handler->addEventVariable("ETAGOODPHOTONS", new EventVariableObjectVariableVector<double>("ETA","goodPhotons"));

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
  handler->addEventVariable("NISOINCLUSIVETRACKS", new EventVariableN("NISOINCLUSIVETRACKS","isoInclusiveTracks"));
  handler->addEventVariable("NPROMPTINCLUSIVETRACKS", new EventVariableN("NPROMPTINCLUSIVETRACKS","promptInclusiveTracks"));
  handler->addEventVariable("NISONONPROMPTINCLUSIVETRACKS", new EventVariableN("NISONONPROMPTINCLUSIVETRACKS","isoNonPromptInclusiveTracks"));
  handler->addEventVariable("NPROMPTNONISOINCLUSIVETRACKS", new EventVariableN("NPROMPTNONISOINCLUSIVETRACKS","promptNonIsoInclusiveTracks"));
  handler->addEventVariable("NNONISONONPROMPTINCLUSIVETRACKS", new EventVariableN("NNONISONONPROMPTINCLUSIVETRACKS","nonIsoNonPromptInclusiveTracks"));
  
  handler->addEventVariable("NINCLUSIVETRACKS7", new EventVariableN("NINCLUSIVETRACKS7","inclusiveTracks7"));
  handler->addEventVariable("NISOINCLUSIVETRACKS7", new EventVariableN("NISOINCLUSIVETRACKS7","isoInclusiveTracks7"));
  handler->addEventVariable("NPROMPTINCLUSIVETRACKS7", new EventVariableN("NPROMPTINCLUSIVETRACKS7","promptInclusiveTracks7"));
  handler->addEventVariable("NPROMPTIREL0p30INCLUSIVETRACKS7", new EventVariableN("NPROMPTIREL0p30INCLUSIVETRACKS7","promptIREL0p30InclusiveTracks7"));
  handler->addEventVariable("NISONONPROMPTINCLUSIVETRACKS7", new EventVariableN("NISONONPROMPTINCLUSIVETRACKS7","isoNonPromptInclusiveTracks7"));
  handler->addEventVariable("NPROMPTNONISOINCLUSIVETRACKS7", new EventVariableN("NPROMPTNONISOINCLUSIVETRACKS7","promptNonIsoInclusiveTracks7"));
  handler->addEventVariable("NNONISONONPROMPTINCLUSIVETRACKS7", new EventVariableN("NNONISONONPROMPTINCLUSIVETRACKS7","nonIsoNonPromptInclusiveTracks7"));
  
  // Regular tracks
  handler->addEventVariable("NGOODTRACKS", new EventVariableN("NGOODTRACKS","goodTracks"));
  handler->addEventVariable("QGOODTRACKS", new EventVariableObjectVariableVector<int>("CHARGE","goodTracks"));
  handler->addEventVariable("PTGOODTRACKS", new EventVariableObjectVariableVector<double>("PT","goodTracks"));
  handler->addEventVariable("ETAGOODTRACKS", new EventVariableObjectVariableVector<double>("ETA","goodTracks"));
  
  handler->addEventVariable("NBASICTRACKS", new EventVariableN("NBASICTRACKS","basicTracks"));
  handler->addEventVariable("DXYBASICTRACKS", new EventVariableObjectVariableVector<double>("VERT_DXY","basicTracks"));
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

  EventVariableOSSF* OSSFnoFake = new EventVariableOSSF("OSSFnoFake","goodMuons","NOFAKE",mZ,zWidth, false);
  OSSFnoFake->addProduct("goodElectrons");
  handler->addEventVariable("OSSFnoFake",OSSFnoFake);

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
  
  EventVariableMT* MT = new EventVariableMT("MT", mZ);
  handler->addEventVariable("MT",MT);

  EventVariablePairMass2* mElecBjet = new EventVariablePairMass2("ELECBJETMASS", "goodElectrons", "ELECBJETMASS");
  mElecBjet->addProduct("bJetsCSVM");
  handler->addEventVariable("ELECBJETMASS", mElecBjet);
  
  EventVariablePairMass2* mMuonBjet = new EventVariablePairMass2("MUONBJETMASS", "goodMuons", "MUONBJETMASS");
  mMuonBjet->addProduct("bJetsCSVM");
  handler->addEventVariable("MUONBJETMASS", mMuonBjet);

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
  
  EventVariableInRange<int>* el2 = new EventVariableInRange<int>("NGOODELECTRONS", 2, 2, "El2");
  handler->addEventVariable("El2", el2);
  
  EventVariableInRange<int>* dileptons = new EventVariableInRange<int>("NLEPTONS", 2, 1e6, "DILEPTONS");
  handler->addEventVariable("DILEPTONS", dileptons);
  
  EventVariableInRange<int>* trileptons = new EventVariableInRange<int>("NLEPTONS", 3, 1e6, "TRILEPTONS");
  handler->addEventVariable("TRILEPTONS", trileptons);
  
  EventVariableInRange<double>* mLeptonsOnZ = new EventVariableInRange<double>("MLEPTONS", mZ-zWidth, mZ+zWidth, "MLEPTONSONZ");
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
  
  EventVariableInRange<double>* mLowDYcut = new EventVariableInRange<double>("LOWDYOSMINMLL", 12, 1e7, "MLOWDYCUT");
  handler->addEventVariable("MLOWDYCUT", mLowDYcut);

  if(singleLeptonSample) {
	  EventVariableInRange<int>* singlelepton = new EventVariableInRange<int>("NLEPTONS", 1, 1e6, "SINGLELEPTON");
	  handler->addEventVariable("SINGLELEPTON", singlelepton);
	  
	  EventVariableInRange<int>* btagged = new EventVariableInRange<int>("NBJETSCSVM", 1, 1e6, "BTAGGED");
	  handler->addEventVariable("BTAGGED", btagged);
	  
	  EventVariableCombined* btagged1L = new EventVariableCombined("BTAGGED", "SINGLELEPTON", true, "BTAGGED1L");
	  handler->addEventVariable("BTAGGED1L", btagged1L);
	  
	  EventVariableCombined* dileptonNotBelow12 = new EventVariableCombined("DILEPTONS", "MLOWDYCUT", true, "DILEPTONNOTBELOW12");
	  handler->addEventVariable("DILEPTONNOTBELOW12", dileptonNotBelow12);

	  EventVariableCombined* writeEvent = new EventVariableCombined("BTAGGED1L", "DILEPTONNOTBELOW12", false, "WRITEEVENT");
	  //EventVariableInRange<int>* writeEvent = new EventVariableInRange<int>("NLEPTONS", -1e6, 1e6, "WRITEEVENT");
	  handler->addEventVariable("WRITEEVENT", writeEvent);
  } else {
	  EventVariableCombined* writeEvent = new EventVariableCombined("DILEPTONS", "MLOWDYCUT", true, "WRITEEVENT");
	//  writeEvent->addVariable("NOTTRILEPTONONZ");
	  handler->addEventVariable("WRITEEVENT", writeEvent);
  }
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

void setupMC1(BaseHandler* handler, TString pufile, bool doMatching = true, bool wzKinematics = false)
{
  // Avoid compiler warnings
  pufile = pufile;
  doMatching = doMatching;


  ////Additional products
  
  ObjectVariableValueInList<int>* pdgid11 = new ObjectVariableValueInList<int>("PDGID",11);
  pdgid11->addValue(-11);
  ObjectVariableValueInList<int>* pdgid13 = new ObjectVariableValueInList<int>("PDGID",13);
  pdgid13->addValue(-13);
  ObjectVariableValueInList<int>* pdgid15 = new ObjectVariableValueInList<int>("PDGID",15);
  pdgid15->addValue(-15);

  ObjectVariableValueInList<int>* status1 = new ObjectVariableValueInList<int>("STATUS", 1);
  handler->addObjectVariable("STATUS1", status1);

  ObjectVariableValueInList<int>* motherWZTau = new ObjectVariableValueInList<int>("MOTHER_PDGID",24);
  motherWZTau->addValue(-24);
  motherWZTau->addValue(23);
  motherWZTau->addValue(15);
  motherWZTau->addValue(-15);

  handler->addObjectVariable("PDGID11",pdgid11);
  handler->addObjectVariable("PDGID13",pdgid13);
  handler->addObjectVariable("PDGID15",pdgid15);
  handler->addObjectVariable("MOTHERWZTau",motherWZTau);
  handler->addObjectVariable("MOTHERnotWZTau",new ObjectVariableReversed("MOTHERWZTau","MOTHERnotWZTau"));

  handler->addProduct("MCelectrons","ALLMCPARTICLES");
  handler->addProductCut("MCelectrons","PDGID11");

  handler->addProduct("MCelectronsFromWZTau","MCelectrons");
  handler->addProductCut("MCelectronsFromWZTau","MOTHERWZTau");

  handler->addProduct("MCelectronsFake","MCelectrons");
  handler->addProductCut("MCelectronsFake", "MOTHERnotWZTau");
  handler->addProductCut("MCelectronsFake", "STATUS1");

  handler->addProduct("MCmuons","ALLMCPARTICLES");
  handler->addProductCut("MCmuons","PDGID13");

  handler->addProduct("MCmuonsFromWZTau","MCmuons");
  handler->addProductCut("MCmuonsFromWZTau","MOTHERWZTau");

  handler->addProduct("MCmuonsFake","MCmuons");
  handler->addProductCut("MCmuonsFake","MOTHERnotWZTau");
  handler->addProductCut("MCmuonsFake", "STATUS1");
  
  handler->addProduct("MCtaus","ALLMCPARTICLES");
  handler->addProductCut("MCtaus","PDGID15");

  handler->addProduct("MCtausFromWZTau","MCtaus");
  handler->addProductCut("MCtausFromWZTau","MOTHERWZTau");

  handler->addProduct("MCtausFake","MCtaus");
  handler->addProductCut("MCtausFake","MOTHERnotWZTau");
  handler->addProductCut("MCtausFake", "STATUS1");
  
  ObjectComparisonDeltaR* deltaR0p1 = new ObjectComparisonDeltaR(0.1);
  handler->addProductSelfComparison("MCmuonsFromWZTau",deltaR0p1);
  handler->addProductSelfComparison("MCelectronsFromWZTau",deltaR0p1);
  handler->addProductSelfComparison("MCtausFromWZTau",deltaR0p1);

  handler->addProductSelfComparison("MCmuonsFake",deltaR0p1);
  handler->addProductSelfComparison("MCelectronsFake",deltaR0p1);
  handler->addProductSelfComparison("MCtausFake",deltaR0p1);

  if(wzKinematics) {
	  ObjectVariableValueInList<int>* pdgid6 = new ObjectVariableValueInList<int>("PDGID",6);
	  pdgid6->addValue(-6);
	  ObjectVariableValueInList<int>* pdgid23 = new ObjectVariableValueInList<int>("PDGID",23);
	  ObjectVariableValueInList<int>* pdgid24 = new ObjectVariableValueInList<int>("PDGID",24);
	  pdgid24->addValue(-24);
	  ObjectVariableValueInList<int>* status3 = new ObjectVariableValueInList<int>("STATUS", 3);
	  handler->addObjectVariable("STATUS3", status3);
	  handler->addObjectVariable("PDGID6",pdgid6);
	  handler->addObjectVariable("PDGID23",pdgid23);
	  handler->addObjectVariable("PDGID24",pdgid24);

	  handler->addProduct("MCZ","ALLMCPARTICLES");
	  handler->addProductCut("MCZ", "PDGID23");
	  handler->addProductCut("MCZ", "STATUS3");

	  handler->addProduct("MCW","ALLMCPARTICLES");
	  handler->addProductCut("MCW", "PDGID24");
	  handler->addProductCut("MCW", "STATUS3");

	  handler->addProduct("MCt","ALLMCPARTICLES");
	  handler->addProductCut("MCt", "PDGID6");
	  handler->addProductCut("MCt", "STATUS3");

	  handler->addEventVariable("NMCZ", new EventVariableN("NMCZ","MCZ"));
	  handler->addEventVariable("PTMCZ", new EventVariableObjectVariableVector<double>("PT","MCZ"));
	  handler->addEventVariable("MMCZ", new EventVariableObjectVariableVector<double>("M","MCZ"));

	  handler->addEventVariable("NMCW", new EventVariableN("NMCW","MCW"));
	  handler->addEventVariable("PTMCW", new EventVariableObjectVariableVector<double>("PT","MCW"));
	  handler->addEventVariable("MMCW", new EventVariableObjectVariableVector<double>("M","MCW"));

	  handler->addEventVariable("NMCt", new EventVariableN("NMCt","MCt"));
  }
}

void setupMC2(BaseHandler* handler, TString pufile, bool doMatching = true) {
  handler->addProduct("goodMuonsNoMC", "goodMuons");
  handler->addProduct("goodElectronsNoMC", "goodElectrons");

  ObjectComparisonMatchDeltaRCharge* mcMatchComparison = new ObjectComparisonMatchDeltaRCharge(0.1);
  handler->addProductComparison("goodMuonsNoMC","MCmuonsFromWZTau",mcMatchComparison);
  handler->addProductComparison("goodElectronsNoMC","MCelectronsFromWZTau",mcMatchComparison);
  handler->addProductComparison("goodTausNoMC","MCtausFromWZTau",mcMatchComparison);
  
  EventVariableProductAngle* fakeAngle = new EventVariableProductAngle("MCmuonsFake", "bJetsCSVM", "FAKEANGLE");
  fakeAngle->addProduct("MCelectronsFake");
  handler->addEventVariable("FAKEANGLE", fakeAngle);

  EventVariableInRange<int>* nTrackFakeElectrons0 = new EventVariableInRange<int>("nTrackFakeElectrons", 0, 0, "nTrackFakeElectrons0");
  handler->addEventVariable("nTrackFakeElectrons0", nTrackFakeElectrons0);
  EventVariableInRange<int>* nTrackFakeMuons0 = new EventVariableInRange<int>("nTrackFakeMuons", 0, 0, "nTrackFakeMuons0");
  handler->addEventVariable("nTrackFakeMuons0", nTrackFakeMuons0);
  EventVariableInRange<int>* nPhotonFakeElectrons0 = new EventVariableInRange<int>("nPhotonFakeElectrons", 0, 0, "nPhotonFakeElectrons0");
  handler->addEventVariable("nPhotonFakeElectrons0", nPhotonFakeElectrons0);
  EventVariableInRange<int>* nPhotonFakeMuons0 = new EventVariableInRange<int>("nPhotonFakeMuons", 0, 0, "nPhotonFakeMuons0");
  handler->addEventVariable("nPhotonFakeMuons0", nPhotonFakeMuons0);
  
  handler->addSignature("L3trackFake0")->addCut("TRILEPTONS")->addCut("nTrackFakeElectrons0")->addCut("nTrackFakeMuons0");
  handler->addSignature("L3photonFake0")->addCut("TRILEPTONS")->addCut("nPhotonFakeElectrons0")->addCut("nPhotonFakeMuons0");
  handler->addSignature("L3fake0")->addCut("TRILEPTONS")->addCut("nTrackFakeElectrons0")->addCut("nTrackFakeMuons0")->addCut("nPhotonFakeElectrons0")->addCut("nPhotonFakeMuons0");

  handler->addSignature("L3El2DYz1trackFake0")->addCut("TRILEPTONS")->addCut("El2")->addCut("ONZ")->addCut("nTrackFakeElectrons0")->addCut("nTrackFakeMuons0");
  handler->addSignature("L3El2DYz1photonFake0")->addCut("TRILEPTONS")->addCut("El2")->addCut("ONZ")->addCut("nPhotonFakeElectrons0")->addCut("nPhotonFakeMuons0");
  handler->addSignature("L3El2DYz1fake0")->addCut("TRILEPTONS")->addCut("El2")->addCut("ONZ")->addCut("nTrackFakeElectrons0")->addCut("nTrackFakeMuons0")->addCut("nPhotonFakeElectrons0")->addCut("nPhotonFakeMuons0");

  SignatureTH1F_ObjectVariable<double>* h_ptElMC = new SignatureTH1F_ObjectVariable<double>("PTfakeElMC","PT","MCelectronsFake","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptElMC);
  
  SignatureTH1F_ObjectVariable<double>* h_etaElMC = new SignatureTH1F_ObjectVariable<double>("ETAfakeElMC","ETA","MCelectronsFake","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaElMC);

  SignatureTH1F_ObjectVariable<double>* h_ptMuMC = new SignatureTH1F_ObjectVariable<double>("PTfakeMuMC","PT","MCmuonsFake","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptMuMC);
  
  SignatureTH1F_ObjectVariable<double>* h_etaMuMC = new SignatureTH1F_ObjectVariable<double>("ETAfakeMuMC","ETA","MCmuonsFake","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaMuMC);
  
  SignatureTH1F_ObjectVariable<double>* h_ptElReco = new SignatureTH1F_ObjectVariable<double>("PTfakeElReco","PT","goodElectronsNoMC","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptElReco);
  
  SignatureTH1F_ObjectVariable<double>* h_etaElReco = new SignatureTH1F_ObjectVariable<double>("ETAfakeElReco","ETA","goodElectronsNoMC","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaElReco);

  SignatureTH1F_ObjectVariable<double>* h_ptMuReco = new SignatureTH1F_ObjectVariable<double>("PTfakeMuReco","PT","goodMuonsNoMC","PT Distribution",100,0,1000);
  handler->addHistogram(h_ptMuReco);
  
  SignatureTH1F_ObjectVariable<double>* h_etaMuReco = new SignatureTH1F_ObjectVariable<double>("ETAfakeMuReco","ETA","goodMuonsNoMC","ETA Distribution",100,-3,3);
  handler->addHistogram(h_etaMuReco);
  
  if(doMatching) {
	  handler->addProductComparison("goodElectrons","MCelectronsFromWZTau",mcMatchComparison,false);
	  handler->addProductComparison("goodMuons","MCmuonsFromWZTau",mcMatchComparison,false);
	  handler->addProductComparison("goodTaus","MCtausFromWZTau",mcMatchComparison,false);
  }

  if(pufile != "") {
    TFile infile(pufile.Data());
    TH1F* pu = (TH1F*)infile.Get("puweights");
    pu->SetDirectory(0);
    EventVariableTH1<double>* pureweight = new EventVariableTH1<double>("pureweight","TRUENUMINTERACTIONS",pu);
    handler->addEventVariable("PUWEIGHT",pureweight);
    handler->addWeightVariable("PUWEIGHT");
  }

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

