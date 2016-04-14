//////////////////////////////////////////////////////////
//
// Declare all object variables here:
//
//////////////////////////////////////////////////////////

void setupObjectVariables(BaseHandler* handler){
  handler->addObjectVariable("isPhoton",            new ObjectVariableValue<TString>("INPUTTYPE",  "photon"));
  handler->addObjectVariable("isVertex",            new ObjectVariableValue<TString>("INPUTTYPE",  "vertex"));
  handler->addObjectVariable("isMET",               new ObjectVariableValue<TString>("INPUTTYPE",  "met"));
  handler->addObjectVariable("isTrigger",           new ObjectVariableValue<TString>("INPUTTYPE",  "trigger"));
  handler->addObjectVariable("uncertaintyNoShift",  new ObjectVariableValue<TString>("uncertainty","NoShift"));
  handler->addObjectVariable("levelType1",          new ObjectVariableValue<TString>("level",      "Type1"));
  handler->addObjectVariable("INPUTTAGslimmedMETs", new ObjectVariableValue<TString>("INPUTTAG",   "slimmedMETs"));
  handler->addObjectVariable("isMC",                new ObjectVariableValue<TString>("INPUTTYPE",  "mc"));

  // --------------------------------------------------------------------------------------------------------------
  /////////////////////////////
  ///Miscellaneous variables///
  /////////////////////////////
  handler->addObjectVariable("ETA",           new ObjectVariableMethod("ETA", &SignatureObject::Eta));
  handler->addObjectVariable("ETA2p3",        new ObjectVariableInRange<double>("ETA",-2.3,2.3,"ETA2p3"));
  handler->addObjectVariable("ETA2p4",        new ObjectVariableInRange<double>("ETA",-2.4,2.4));
  handler->addObjectVariable("ETA2p5",        new ObjectVariableInRange<double>("ETA",-2.5,2.5,"ETA2p5"));
  handler->addObjectVariable("ETA0p8",        new ObjectVariableInRange<double>("ETA",-0.8,0.8,"ETA0p8"));
  handler->addObjectVariable("ETA4p7",        new ObjectVariableInRange<double>("ETA",-4.7,4.7,"ETA4p7"));
  handler->addObjectVariable("ETA3",          new ObjectVariableInRange<double>("ETA",-3.0,3.0,"ETA3"));
  handler->addObjectVariable("ETA1p479",      new ObjectVariableInRange<double>("ETA",-1.479,1.479,"ETA1p479"));
  handler->addObjectVariable("NOTETA0p8",     new ObjectVariableReversed("ETA0p8"));
  handler->addObjectVariable("NOTETA2p4",     new ObjectVariableReversed("ETA2p4"));
  handler->addObjectVariable("ETA0p8to1p479", new ObjectVariableCombined("NOTETA0p8","ETA1p479",true,"ETA0p8to1p479"));
  handler->addObjectVariable("ETA2p4to4p7",   new ObjectVariableCombined("NOTETA2p4", "ETA4p7", true, "ETA2p4to4p7"));
  handler->addObjectVariable("BARREL",        new ObjectVariableInRange<double>("ETA",-1.479,1.479,"barrelEta"));
  handler->addObjectVariable("ENDCAP",        new ObjectVariableReversed("BARREL","endcapEta"));
  handler->addObjectVariable("POSITIVE",      new ObjectVariableInRange<int>("charge",0,10,"CHARGEPOS"));
  handler->addObjectVariable("NEGATIVE",      new ObjectVariableInRange<int>("charge",-10,0,"CHARGENEG"));
  //
  handler->addObjectVariable("PT",            new ObjectVariableMethod("PT", &SignatureObject::Pt)); 
  handler->addObjectVariable("PT6",           new ObjectVariableInRange<double>("PT",6.0,10000.0,"PT6"));
  handler->addObjectVariable("PT7",           new ObjectVariableInRange<double>("PT",7.0,10000.0,"PT7"));
  handler->addObjectVariable("PT20",          new ObjectVariableInRange<double>("PT",20.0,10000.0,"PT20"));
  handler->addObjectVariable("PT30",          new ObjectVariableInRange<double>("PT",30.0,10000.0,"PT30"));
  handler->addObjectVariable("PT40",          new ObjectVariableInRange<double>("PT",40.0,100000.0));
  //
  handler->addObjectVariable("CHARGE",        new ObjectVariableRename<int>("charge","CHARGE"));
  handler->addObjectVariable("genDxy",        new ObjectVariableGenVertexR("genDxy"));
  handler->addObjectVariable("SIP3D_4sigma",  new ObjectVariableInRange<double>("sigPV3D",-4,4));
  //
  handler->addObjectVariable("PHI",           new ObjectVariableMethod("PHI", &SignatureObject::Phi)); 
  //
  handler->addObjectVariable("JET",           new ObjectVariableConeConstituents(10,handler,true,false));//jet matching, with given jet pt cut
  handler->addObjectVariable("CONE",          new ObjectVariableConeConstituents( 1,handler,false,false));//PF candidates in cone, with a given pt cut
  handler->addObjectVariable("CONECH",        new ObjectVariableConeConstituents( 2,handler,false, true));//CHARGED PF candidates in cone, with a given pt cut
  //
  
  // --------------------------------------------------------------------------------------------------------------
  /////////////////////////
  ///Isolation Variables///
  /////////////////////////
  ObjectVariableEffectiveArea* areaEl = new ObjectVariableEffectiveArea("ELECTRON_AREA");
  areaEl->addArea(1,     0.1752);
  areaEl->addArea(1.479, 0.1862);
  areaEl->addArea(2.0,   0.1411);
  areaEl->addArea(2.2,   0.1534);
  areaEl->addArea(2.3,   0.1903);
  areaEl->addArea(2.4,   0.2243);
  areaEl->addArea(2.5,   0.2687);
  handler->addObjectVariable("ELECTRON_AREA", areaEl);
  //
  ObjectVariableEffectiveAreaMiniIsolation* areaElmi = new ObjectVariableEffectiveAreaMiniIsolation("miniIsoCone",0.3,2,"ELECTRON_AREA_MINIISO");
  areaElmi->addArea(1,     0.1752);
  areaElmi->addArea(1.479, 0.1862);
  areaElmi->addArea(2.0,   0.1411);
  areaElmi->addArea(2.2,   0.1534);
  areaElmi->addArea(2.3,   0.1903);
  areaElmi->addArea(2.4,   0.2243);
  areaElmi->addArea(2.5,   0.2687);
  handler->addObjectVariable("ELECTRON_AREA_MINIISO", areaElmi);
  //
  ObjectVariableEffectiveArea* areaMu = new ObjectVariableEffectiveArea("MUON_AREA");
  areaMu->addArea(0.8, 0.0735);
  areaMu->addArea(1.3, 0.0619);
  areaMu->addArea(2.0, 0.0465);
  areaMu->addArea(2.2, 0.0433);
  areaMu->addArea(2.5, 0.0577);
  handler->addObjectVariable("MUON_AREA", areaMu);
  //
  ObjectVariableEffectiveAreaMiniIsolation* areaMumi = new ObjectVariableEffectiveAreaMiniIsolation("miniIsoCone",0.3,2,"MUON_AREA_MINIISO");
  areaMumi->addArea(0.8, 0.0735);
  areaMumi->addArea(1.3, 0.0619);
  areaMumi->addArea(2.0, 0.0465);
  areaMumi->addArea(2.2, 0.0433);
  areaMumi->addArea(2.5, 0.0577);
  handler->addObjectVariable("MUON_AREA_MINIISO", areaMumi);
  //
  // Electron, Muon, Tau, and Track isolations:
  handler->addObjectVariable("RHO", new ObjectVariableEventVariable<double>("rhoNeutral",handler));
  handler->addObjectVariable("ELECTRON_totalIso", new ObjectVariableRhoCorrectedTotalIso("sumChargedHadronPt","sumNeutralHadronEt","sumPhotonEt","RHO","ELECTRON_AREA","TOTALISO"),false);
  handler->addObjectVariable("MUON_totalIso", new ObjectVariableRhoCorrectedTotalIso("pfIsolationR03sumChargedHadronPt","pfIsolationR03sumNeutralHadronEt","pfIsolationR03sumPhotonEt","RHO","MUON_AREA","TOTALISO"),false);
  handler->addObjectVariable("TRACK_totalIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronIsoFromPF","neutralHadronIsoFromPF","neutralPhotonIsoFromPF","RHO","MUON_AREA","TOTALISO","isTrack"),false);
  handler->addObjectVariable("ELECTRON_totalMiniIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronMiniIso","neutralHadronMiniIso","photonMiniIso","RHO","ELECTRON_AREA_MINIISO","TOTALMINIISO","isElectron"),false);
  handler->addObjectVariable("MUON_totalMiniIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronMiniIso","neutralHadronMiniIso","photonMiniIso","RHO","MUON_AREA_MINIISO","TOTALMINIISO","isMuon"),false);
  handler->addObjectVariable("TRACK_totalMiniIso", new ObjectVariableRhoCorrectedTotalIso("chargedHadronMiniIso","neutralHadronMiniIso","photonMiniIso","RHO","MUON_AREA_MINIISO","TOTALMINIISO","isTrack"),false);
  handler->addObjectVariable("TAU_totalMiniIso", new ObjectVariableDeltaBetaCorrectedTotalIso("chargedHadronMiniIso","","photonMiniIso","puCorrPtSum","TOTALMINIISO","isTau"),false);
  //
  // ADDING MUON PF-ISO-DR0.4, DB CORRECTED:
  handler->addObjectVariable("MUON_totalIsoDB0p4", new ObjectVariableDeltaBetaCorrectedTotalIso("pfIsolationR04sumChargedHadronPt","pfIsolationR04sumNeutralHadronEt","pfIsolationR04sumPhotonEt","pfIsolationR04sumPUPt","MUON_TOTALISODB0p4","isMuon"),false);
  handler->addObjectVariable("MUON_RELISO", new ObjectVariableRelIso("MUON_RELISO","MUON_TOTALISODB0p4"));
  //
  // ADDING ELECTRON CUT-ID PF-ISO, RHO CORRECTED:
  // https://github.com/cms-sw/cmssw/blob/CMSSW_7_6_X/RecoEgamma/ElectronIdentification/plugins/cuts/GsfEleEffAreaPFIsoCut.cc#L71
  // https://github.com/cms-sw/cmssw/blob/CMSSW_7_6_X/RecoEgamma/ElectronIdentification/python/Identification/cutBasedElectronID_tools.py#L262
  handler->addObjectVariable("RHO_ALL", new ObjectVariableEventVariable<double>("rhoAll",handler));
  handler->addObjectVariable("ELECTRON_CutIDtotalIso", new ObjectVariableRhoCorrectedTotalIso("sumChargedHadronPt","sumNeutralHadronEt","sumPhotonEt","RHO_ALL","ELECTRON_AREA","ELECTRON_CutIDTOTALISO","isElectron"),false);
  handler->addObjectVariable("ELECTRON_RELISO", new ObjectVariableRelIso("ELECTRON_RELISO","ELECTRON_CutIDTOTALISO"));
  //
  handler->addObjectVariable("RELISO",      new ObjectVariableRelIso("RELISO"));
  handler->addObjectVariable("MINIISO",     new ObjectVariableRelIso("MINIISO","TOTALMINIISO"));
  handler->addObjectVariable("MINIISO0p40", new ObjectVariableInRange<double>("MINIISO",0,0.4));
  handler->addObjectVariable("MINIISO0p25", new ObjectVariableInRange<double>("MINIISO",0,0.25));
  handler->addObjectVariable("MINIISO0p20", new ObjectVariableInRange<double>("MINIISO",0,0.20));
  handler->addObjectVariable("MINIISO0p16", new ObjectVariableInRange<double>("MINIISO",0,0.16));
  handler->addObjectVariable("MINIISO0p12", new ObjectVariableInRange<double>("MINIISO",0,0.12));
  handler->addObjectVariable("MINIISO0p09", new ObjectVariableInRange<double>("MINIISO",0,0.09));
  handler->addObjectVariable("PTRATIO0p67", new ObjectVariableInRange<double>("ptRatio",0.67,1e6));
  handler->addObjectVariable("PTRATIO0p69", new ObjectVariableInRange<double>("ptRatio",0.69,1e6));
  handler->addObjectVariable("PTRATIO0p76", new ObjectVariableInRange<double>("ptRatio",0.76,1e6));
  handler->addObjectVariable("PTRATIO0p80", new ObjectVariableInRange<double>("ptRatio",0.80,1e6));
  handler->addObjectVariable("PTRATIO0p84", new ObjectVariableInRange<double>("ptRatio",0.84,1e6));
  handler->addObjectVariable("PTREL4p4",    new ObjectVariableInRange<double>("ptRel",4.4,1e6));
  handler->addObjectVariable("PTREL6p0",    new ObjectVariableInRange<double>("ptRel",6,1e6));
  handler->addObjectVariable("PTREL7p2",    new ObjectVariableInRange<double>("ptRel",7.2,1e6));
  //
  handler->addObjectVariable("MULTIISOJETVL", new ObjectVariableCombined("PTRATIO0p67","PTREL4p4",false));
  handler->addObjectVariable("MULTIISOJETL",  new ObjectVariableCombined("PTRATIO0p69","PTREL6p0",false));
  handler->addObjectVariable("MULTIISOJETM",  new ObjectVariableCombined("PTRATIO0p76","PTREL7p2",false));
  handler->addObjectVariable("MULTIISOJETT",  new ObjectVariableCombined("PTRATIO0p80","PTREL7p2",false));
  handler->addObjectVariable("MULTIISOJETVT", new ObjectVariableCombined("PTRATIO0p84","PTREL7p2",false));
  //
  handler->addObjectVariable("MULTIISOVL", new ObjectVariableCombined("MINIISO0p25","MULTIISOJETVL",true));
  handler->addObjectVariable("MULTIISOL",  new ObjectVariableCombined("MINIISO0p20","MULTIISOJETL", true));
  handler->addObjectVariable("MULTIISOM",  new ObjectVariableCombined("MINIISO0p16","MULTIISOJETM", true));
  handler->addObjectVariable("MULTIISOT",  new ObjectVariableCombined("MINIISO0p12","MULTIISOJETT", true));
  handler->addObjectVariable("MULTIISOVT", new ObjectVariableCombined("MINIISO0p09","MULTIISOJETVT",true));
  //
  handler->addObjectVariable("IREL0p15",     new ObjectVariableInRange<double>("RELISO",0,0.15,"IREL0p15"));
  handler->addObjectVariable("NOTIREL0p15",  new ObjectVariableReversed("IREL0p15"));
  handler->addObjectVariable("IREL0p23",     new ObjectVariableInRange<double>("RELISO",0,0.23,"IREL0p23"));
  handler->addObjectVariable("IREL0p24",     new ObjectVariableInRange<double>("RELISO",0,0.24,"IREL0p24"));
  handler->addObjectVariable("NOTIREL0p24",  new ObjectVariableReversed("IREL0p24"));
  handler->addObjectVariable("IREL0p25",     new ObjectVariableInRange<double>("RELISO",0,0.25,"IREL0p25"));
  handler->addObjectVariable("IREL0p30",     new ObjectVariableInRange<double>("RELISO",0,0.30,"IREL0p30"));
  handler->addObjectVariable("IREL0p35",     new ObjectVariableInRange<double>("RELISO",0,0.3529,"IREL0p35"));
  handler->addObjectVariable("IREL0p5",      new ObjectVariableInRange<double>("RELISO",0,0.5,"IREL0p5"));


  // --------------------------------------------------------------------------------------------------------------
  ////////////////////
  ///Muon Variables///
  ////////////////////
  handler->addObjectVariable("MUON_dxy",               new ObjectVariableInRange<double>("dxy",-0.05,0.05));
  handler->addObjectVariable("MUON_dz",                new ObjectVariableInRange<double>("dz",-0.1,0.1));
  handler->addObjectVariable("MUON_nonprompt",         new ObjectVariableReversed("MUON_dxy","MUON_nonprompt"));
  handler->addObjectVariable("MUON_GLOBALORTRACKER",   new ObjectVariableCombined("isTrackerMuon","isGlobalMuon",false));
  //
  handler->addObjectVariable("MUON_LOOSEID",  new ObjectVariableValue<bool>("isLooseMuon",  true));
  handler->addObjectVariable("MUON_MEDIUMID", new ObjectVariableValue<bool>("isMediumMuon", true));
  handler->addObjectVariable("MUON_TIGHTID",  new ObjectVariableValue<bool>("isTightMuon",  true));
  handler->addObjectVariable("MUON_SOFTID",   new ObjectVariableValue<bool>("isSoftMuon",   true));
  handler->addObjectVariable("MUON_HIGHPTID", new ObjectVariableValue<bool>("isHighPtMuon", true));
  //
  handler->addObjectVariable("MUON_IREL0p25",new ObjectVariableInRange<double>("MUON_RELISO",0,0.25,"MUON_IREL0p25"));
  handler->addObjectVariable("MUON_IREL0p15",new ObjectVariableInRange<double>("MUON_RELISO",0,0.15,"MUON_IREL0p15"));
  //
  // These are not used at the moment >>>>
  //handler->addObjectVariable("MUON_normalizedChi2",    new ObjectVariableInRange<double>("normalizedChi2",0,3));
  //handler->addObjectVariable("MUON_chi2LocalPosition", new ObjectVariableInRange<double>("chi2LocalPosition",0,12));
  //handler->addObjectVariable("MUON_trkKink",           new ObjectVariableInRange<double>("trkKink",0,20));
  //handler->addObjectVariable("MUON_SEGCOM0p303",       new ObjectVariableInRange<double>("segmentCompatibility",0.303,1000000));
  //handler->addObjectVariable("MUON_SEGCOM0p451",       new ObjectVariableInRange<double>("segmentCompatibility",0.451,1000000));
  //handler->addObjectVariable("MUON_validFraction",     new ObjectVariableInRange<double>("validFraction",0.8+1e-9,10000));
  //
  //ObjectVariableCombined* muon_goodGlobal = new ObjectVariableCombined("isGlobalMuon","MUON_normalizedChi2",true);
  //muon_goodGlobal->addVariable("MUON_chi2LocalPosition");
  //muon_goodGlobal->addVariable("MUON_trkKink");
  //handler->addObjectVariable("MUON_GOODGLOBAL",muon_goodGlobal);
  //ObjectVariableCombined* muon_goodGlobalSeg = new ObjectVariableCombined("MUON_GOODGLOBAL","MUON_SEGCOM0p303",true);
  //handler->addObjectVariable("MUON_GOODGLOBALSEGCOM",muon_goodGlobalSeg);
  //
  //handler->addObjectVariable("MUON_GOODSEGCOM",new ObjectVariableCombined("MUON_GOODGLOBALSEGCOM","MUON_SEGCOM0p451",false));
  // <<<<
  //


  // --------------------------------------------------------------------------------------------------------------
  ////////////////////////
  ///Electron Variables///
  ////////////////////////
  handler->addObjectVariable("ELECTRON_ISOLATED",    new ObjectVariableRename<bool>("MULTIISOM", "ELECTRON_ISOLATED"));
  handler->addObjectVariable("ELECTRON_NOTISOLATED", new ObjectVariableReversed("ELECTRON_ISOLATED"));
  //
  handler->addObjectVariable("ELECTRON_INGAPPOS", new ObjectVariableInRange<double>("superClustereta",1.4442,1.566));
  handler->addObjectVariable("ELECTRON_INGAPNEG", new ObjectVariableInRange<double>("superClustereta",-1.566,-1.4442));
  ObjectVariableCombined* electron_ingap = new ObjectVariableCombined("ELECTRON_INGAPPOS","ELECTRON_INGAPNEG",false,"ELECTRON_INGAP");
  handler->addObjectVariable("ELECTRON_INGAP",electron_ingap);
  handler->addObjectVariable("ELECTRON_NOTGAP",new ObjectVariableReversed("ELECTRON_INGAP","ELECTRON_NOTGAP"));
  //
  handler->addObjectVariable("ELECTRON_MISSINGHITS0", new ObjectVariableValue<int>(  "numberOfLostHits",0  ));
  handler->addObjectVariable("ELECTRON_MISSINGHITS1", new ObjectVariableInRange<int>("numberOfLostHits",0,1));
  handler->addObjectVariable("ELECTRON_MISSINGHITS2", new ObjectVariableInRange<int>("numberOfLostHits",0,2));
  //
  handler->addObjectVariable("ELECTRON_passConversionVeto",new ObjectVariableValue<bool>("passConversionVeto",true));
  //
  handler->addObjectVariable("ELECTRON_dz",       new ObjectVariableInRange<double>("dz",-0.1,0.1));
  handler->addObjectVariable("ELECTRON_dxy",      new ObjectVariableInRange<double>("dxy",-0.05,0.05));
  handler->addObjectVariable("ELECTRON_dz5",      new ObjectVariableInRange<double>("dz",-5.0,5.0));
  handler->addObjectVariable("ELECTRON_PROMPT",   new ObjectVariableRename<bool>("ELECTRON_dxy", "ELECTRON_PROMPT"));
  handler->addObjectVariable("ELECTRON_NONPROMPT",new ObjectVariableReversed("ELECTRON_PROMPT"));
  //
  handler->addObjectVariable("ELECTRON_full5x5_sigmaIetaIeta_0p011", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.011));
  handler->addObjectVariable("ELECTRON_full5x5_sigmaIetaIeta_0p031", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.031));
  handler->addObjectVariable("ELECTRON_hcalOverEcal_0p08",           new ObjectVariableInRange<double>("hcalOverEcal",0,0.08));
  handler->addObjectVariable("ELECTRON_1oEm1oPcorrected_0p01",       new ObjectVariableInRange<double>("1oEm1oPcorrected",-0.01,0.01));
  //
  handler->addObjectVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p01", new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.01,0.01));
  handler->addObjectVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p04", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.04,0.04));
  handler->addObjectVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p08", new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.08,0.08));
  //  
  handler->addObjectVariable("ELECTRON_RelIso_EcalPFClusterIso", new ObjectVariableRelIso("ELECTRON_RelIso_EcalPFClusterIso","EcalPFClusterIso"));
  handler->addObjectVariable("ELECTRON_RelIso_HcalPFClusterIso", new ObjectVariableRelIso("ELECTRON_RelIso_HcalPFClusterIso","HcalPFClusterIso"));
  handler->addObjectVariable("ELECTRON_RelIso_TrackIso",         new ObjectVariableRelIso("ELECTRON_RelIso_TrackIso","TrackIso"));
  //
  handler->addObjectVariable("ELECTRON_RelIso_EcalPFClusterIso_0p45", new ObjectVariableInRange<double>("ELECTRON_RelIso_EcalPFClusterIso",0,0.45));
  handler->addObjectVariable("ELECTRON_RelIso_HcalPFClusterIso_0p25", new ObjectVariableInRange<double>("ELECTRON_RelIso_HcalPFClusterIso",0,0.25));
  handler->addObjectVariable("ELECTRON_RelIso_TrackIso_0p45",         new ObjectVariableInRange<double>("ELECTRON_RelIso_TrackIso",0,0.2));
  //
  // Electron trig-id emulation
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/RA7Coordination2015
  ObjectVariableCombined* electron_IDemu_barrel = new ObjectVariableCombined("BARREL","ELECTRON_full5x5_sigmaIetaIeta_0p011",true);
  electron_IDemu_barrel->addVariable("ELECTRON_hcalOverEcal_0p08");
  electron_IDemu_barrel->addVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p01");
  electron_IDemu_barrel->addVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p04");
  electron_IDemu_barrel->addVariable("ELECTRON_1oEm1oPcorrected_0p01");
  handler->addObjectVariable("ELECTRON_IDemu_BARREL", electron_IDemu_barrel);
  ObjectVariableCombined* electron_IDemu_endcap = new ObjectVariableCombined("ENDCAP","ELECTRON_full5x5_sigmaIetaIeta_0p031",true);
  electron_IDemu_endcap->addVariable("ELECTRON_hcalOverEcal_0p08");
  electron_IDemu_endcap->addVariable("ELECTRON_deltaEtaSuperClusterTrackAtVtx_0p01");
  electron_IDemu_endcap->addVariable("ELECTRON_deltaPhiSuperClusterTrackAtVtx_0p08");
  electron_IDemu_endcap->addVariable("ELECTRON_1oEm1oPcorrected_0p01");
  handler->addObjectVariable("ELECTRON_IDemu_ENDCAP", electron_IDemu_endcap);
  handler->addObjectVariable("ELECTRON_IDemu", new ObjectVariableCombined("ELECTRON_IDemu_BARREL","ELECTRON_IDemu_ENDCAP",false));
  //
  // Electron trig-iso emulation
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/RA7Coordination2015
  ObjectVariableCombined* electron_ISOemu = new ObjectVariableCombined("ELECTRON_RelIso_EcalPFClusterIso_0p45","ELECTRON_RelIso_HcalPFClusterIso_0p25",true);
  electron_ISOemu->addVariable("ELECTRON_RelIso_TrackIso_0p45");
  handler->addObjectVariable("ELECTRON_ISOemu", electron_ISOemu);
  handler->addObjectVariable("ELECTRON_IDISOemu", new ObjectVariableCombined("ELECTRON_IDemu","ELECTRON_ISOemu",true));
  //
  // RA7 MVA cuts (non-standard)
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/RA7Coordination2015
  handler->addObjectVariable("ELECTRON_MVA_m0p92",                new ObjectVariableInRange<double>("MVA", -0.92,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p83",                new ObjectVariableInRange<double>("MVA", -0.83,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p76",                new ObjectVariableInRange<double>("MVA", -0.76,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p70",                new ObjectVariableInRange<double>("MVA", -0.70,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p56",                new ObjectVariableInRange<double>("MVA", -0.56,  100000));
  handler->addObjectVariable("ELECTRON_MVA_m0p155",               new ObjectVariableInRange<double>("MVA", -0.155, 100000));
  handler->addObjectVariable("ELECTRON_MVA_0p17",                 new ObjectVariableInRange<double>("MVA",  0.17,  100000));
  handler->addObjectVariable("ELECTRON_MVA_0p60",                 new ObjectVariableInRange<double>("MVA",  0.60,  100000));
  handler->addObjectVariable("ELECTRON_MVA_0p87",                 new ObjectVariableInRange<double>("MVA",  0.87,  100000));
  //
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_LOOSE",         new ObjectVariableCombined("ETA0p8", "ELECTRON_MVA_m0p70",  true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_RA7FO",         new ObjectVariableCombined("ETA0p8", "ELECTRON_MVA_m0p70",  true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8_TIGHT",         new ObjectVariableCombined("ETA0p8", "ELECTRON_MVA_0p87",   true));
  //
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_LOOSE",  new ObjectVariableCombined("ETA0p8to1p479", "ELECTRON_MVA_m0p83", true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_RA7FO",  new ObjectVariableCombined("ETA0p8to1p479", "ELECTRON_MVA_m0p83", true));
  handler->addObjectVariable("ELECTRON_MVA_ETA0p8to1p479_TIGHT",  new ObjectVariableCombined("ETA0p8to1p479", "ELECTRON_MVA_0p60",  true));
  //
  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_LOOSE",         new ObjectVariableCombined("ENDCAP", "ELECTRON_MVA_m0p92", true));
  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_RA7FO",         new ObjectVariableCombined("ENDCAP", "ELECTRON_MVA_m0p92", true));
  handler->addObjectVariable("ELECTRON_MVA_ENDCAP_TIGHT",         new ObjectVariableCombined("ENDCAP", "ELECTRON_MVA_0p17",  true));
  //
  ObjectVariableCombined* electron_mva_loose = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_LOOSE", "ELECTRON_MVA_ETA0p8to1p479_LOOSE", false);
  electron_mva_loose->addVariable("ELECTRON_MVA_ENDCAP_LOOSE");
  ObjectVariableCombined* electron_mva_RA7FO = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_RA7FO", "ELECTRON_MVA_ETA0p8to1p479_RA7FO", false);
  electron_mva_loose->addVariable("ELECTRON_MVA_ENDCAP_RA7FO");
  ObjectVariableCombined* electron_mva_tight = new ObjectVariableCombined("ELECTRON_MVA_ETA0p8_TIGHT", "ELECTRON_MVA_ETA0p8to1p479_TIGHT", false);
  electron_mva_tight->addVariable("ELECTRON_MVA_ENDCAP_TIGHT");
  //
  handler->addObjectVariable("ELECTRON_MVA_RA7LOOSE", electron_mva_loose);
  handler->addObjectVariable("ELECTRON_MVA_RA7FO",    electron_mva_RA7FO);
  handler->addObjectVariable("ELECTRON_MVA_RA7TIGHT", electron_mva_tight);
  //
  // This is the manual cut based  electron isolation LOOSE WP, **without** the relIsoWithEA:
  // The isolation requirement is built into the ID value flags, so can't use passCutBasedLooseId for looseMatrixElectrons.
  // https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Spring15_selection_25ns
  handler->addObjectVariable("ELECTRON_full5x5_sigmaIetaIeta_0p0103", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.0103));
  handler->addObjectVariable("ELECTRON_deltaEtaIn_0p0105",      new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.0105,0.0105));
  handler->addObjectVariable("ELECTRON_deltaPhiIn_0p115",       new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.115,0.115));
  handler->addObjectVariable("ELECTRON_hcalOverEcal_0p104",     new ObjectVariableInRange<double>("hcalOverEcal",0,0.104));
  handler->addObjectVariable("ELECTRON_1oEm1oPcorrected_0p102", new ObjectVariableInRange<double>("1oEm1oPcorrected",-0.102,0.102));
  handler->addObjectVariable("ELECTRON_dxy_0p0261",             new ObjectVariableInRange<double>("dxy",-0.0261,0.0261));
  handler->addObjectVariable("ELECTRON_dz_0p41",                new ObjectVariableInRange<double>("dxy",-0.41,0.41));
  handler->addObjectVariable("ELECTRON_full5x5_sigmaIetaIeta_0p0301", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0,0.0301));
  handler->addObjectVariable("ELECTRON_deltaEtaIn_0p00814",     new ObjectVariableInRange<double>("deltaEtaSuperClusterTrackAtVtx",-0.00814,0.00814));
  handler->addObjectVariable("ELECTRON_deltaPhiIn_0p182",       new ObjectVariableInRange<double>("deltaPhiSuperClusterTrackAtVtx",-0.182,0.182));
  handler->addObjectVariable("ELECTRON_hcalOverEcal_0p0897",    new ObjectVariableInRange<double>("hcalOverEcal",0,0.0897));
  handler->addObjectVariable("ELECTRON_1oEm1oPcorrected_0p126", new ObjectVariableInRange<double>("1oEm1oPcorrected",-0.126,0.126));
  handler->addObjectVariable("ELECTRON_dxy_0p118",              new ObjectVariableInRange<double>("dxy",-0.118,0.118));
  handler->addObjectVariable("ELECTRON_dz_0p822",               new ObjectVariableInRange<double>("dxy",-0.822,0.822));
  ObjectVariableCombined* electron_cutIDLooseNoIso_barrel = new ObjectVariableCombined("BARREL","ELECTRON_full5x5_sigmaIetaIeta_0p0103",true);
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_deltaEtaIn_0p0105");
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_deltaPhiIn_0p115");
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_hcalOverEcal_0p104");
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_1oEm1oPcorrected_0p102");
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_dxy_0p0261");
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_dz_0p41");
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_MISSINGHITS2");
  electron_cutIDLooseNoIso_barrel->addVariable("ELECTRON_passConversionVeto");
  handler->addObjectVariable("ELECTRON_CUTIDLOOSENOISO_BARREL",electron_cutIDLooseNoIso_barrel);
  ObjectVariableCombined* electron_cutIDLooseNoIso_endcap = new ObjectVariableCombined("ENDCAP","ELECTRON_full5x5_sigmaIetaIeta_0p0301",true);
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_deltaEtaIn_0p00814");
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_deltaPhiIn_0p182");
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_hcalOverEcal_0p0897");
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_1oEm1oPcorrected_0p126");
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_dxy_0p118");
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_dz_0p822");
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_MISSINGHITS1");
  electron_cutIDLooseNoIso_endcap->addVariable("ELECTRON_passConversionVeto");
  handler->addObjectVariable("ELECTRON_CUTIDLOOSENOISO_ENDCAP",electron_cutIDLooseNoIso_endcap);
  handler->addObjectVariable("ELECTRON_CUTIDLOOSENOISO", new ObjectVariableCombined("ELECTRON_CUTIDLOOSENOISO_BARREL","ELECTRON_CUTIDLOOSENOISO_ENDCAP",false));
  //
  // Standard POG-supported ids (MVA, CUT, HEEP) -  MVA not used due to complications with "triggering" and "not triggering" versions.
  //handler->addObjectVariable("ELECTRON_MVA_MEDIUMID", new ObjectVariableValue<bool>("passMediumId",         true));
  //handler->addObjectVariable("ELECTRON_MVA_TIGHTID",  new ObjectVariableValue<bool>("passTightId",          true));
  handler->addObjectVariable("ELECTRON_CUT_VETOID",   new ObjectVariableValue<bool>("passCutBasedVetoId",   true));
  handler->addObjectVariable("ELECTRON_CUT_LOOSEID",  new ObjectVariableValue<bool>("passCutBasedLooseId",  true));
  handler->addObjectVariable("ELECTRON_CUT_MEDIUMID", new ObjectVariableValue<bool>("passCutBasedMediumId", true));
  handler->addObjectVariable("ELECTRON_CUT_TIGHTID",  new ObjectVariableValue<bool>("passCutBasedTightId",  true));
  handler->addObjectVariable("ELECTRON_HEEPID",       new ObjectVariableValue<bool>("passHEEP",             true));



  // --------------------------------------------------------------------------------------------------------------
  ///////////////////
  ///Tau Variables///
  ///////////////////
  handler->addObjectVariable("TAU_nonbyMediumIsolationMVArun2v1DBnewDMwLT", new ObjectVariableReversed("byMediumIsolationMVArun2v1DBnewDMwLT"));
  handler->addObjectVariable("TAU_dz",     new ObjectVariableInRange<double>("dz",-0.2,0.2));


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////
  ///Jet Variables///
  ///////////////////
  // Loose PF Jet ID : https://twiki.cern.ch/twiki/bin/view/CMS/JetID#Recommendations_for_13_TeV_data
  handler->addObjectVariable("JET_NEUTRALHADRONFRACTION",      new ObjectVariableInRange<double>("neutralHadronEnergyFraction",0,0.99));
  handler->addObjectVariable("JET_NEUTRALEMFRACTION",          new ObjectVariableInRange<double>("neutralEmEnergyFraction", 0,0.99));
  handler->addObjectVariable("JET_NUMBEROFCONSTITUENTS",       new ObjectVariableInRange<int>("numberOfConstituents",2,100000));
  handler->addObjectVariable("JET_CHARGEDHADRONFRACTION",      new ObjectVariableInRange<double>("chargedHadronEnergyFraction",1e-6,1000));
  handler->addObjectVariable("JET_CHARGEDMULTIPLICITY",        new ObjectVariableInRange<int>("chargedMultiplicity",1,1e6));
  handler->addObjectVariable("JET_CHARGEDEMFRACTION",          new ObjectVariableInRange<double>("chargedEmEnergyFraction",0,0.99));
  handler->addObjectVariable("JET_NEUTRALEMFRACTIONforward",   new ObjectVariableInRange<double>("neutralEmEnergyFraction", 0,0.90));
  handler->addObjectVariable("JET_NEUTRALMULTIPLICITYforward", new ObjectVariableInRange<int>("neutralMultiplicity",10,100000));
  handler->addObjectVariable("JET_2p4",     new ObjectVariableInRange<double>("ETA",-2.4,2.4));
  handler->addObjectVariable("JET_3p0",     new ObjectVariableInRange<double>("ETA",-3.0,3.0));
  handler->addObjectVariable("JET_5p0",     new ObjectVariableInRange<double>("ETA",-5.0,5.0));
  handler->addObjectVariable("JET_not2p4",  new ObjectVariableReversed("JET_2p4"));
  handler->addObjectVariable("JET_not3p0",  new ObjectVariableReversed("JET_3p0"));
  handler->addObjectVariable("JET_CENTRAL", new ObjectVariableInRange<double>("ETA",-2.4,2.4));//repeated for clarity
  ObjectVariableCombined* JET_ENDCAP  = new ObjectVariableCombined("JET_3p0","JET_not2p4",true);
  handler->addObjectVariable("JET_ENDCAP",JET_ENDCAP);
  ObjectVariableCombined* JET_FORWARD = new ObjectVariableCombined("JET_5p0","JET_not3p0",true);
  handler->addObjectVariable("JET_FORWARD",JET_FORWARD);
  //
  ObjectVariableCombined* PFJETID_CENTRAL = new ObjectVariableCombined("JET_NEUTRALHADRONFRACTION","JET_NEUTRALEMFRACTION",true);
  PFJETID_CENTRAL->addVariable("JET_NUMBEROFCONSTITUENTS");
  PFJETID_CENTRAL->addVariable("JET_CHARGEDHADRONFRACTION");
  PFJETID_CENTRAL->addVariable("JET_CHARGEDMULTIPLICITY");
  PFJETID_CENTRAL->addVariable("JET_CHARGEDEMFRACTION");
  PFJETID_CENTRAL->addVariable("JET_CENTRAL");
  handler->addObjectVariable("PFJETID_CENTRAL",PFJETID_CENTRAL);//....central jet ID
  ObjectVariableCombined* PFJETID_ENDCAP = new ObjectVariableCombined("JET_NEUTRALHADRONFRACTION","JET_NEUTRALEMFRACTION",true);
  PFJETID_ENDCAP->addVariable("JET_NUMBEROFCONSTITUENTS");
  PFJETID_ENDCAP->addVariable("JET_ENDCAP");
  handler->addObjectVariable("PFJETID_ENDCAP",PFJETID_ENDCAP);//......endcap  jet ID
  ObjectVariableCombined* PFJETID_FORWARD = new ObjectVariableCombined("JET_NEUTRALEMFRACTIONforward","JET_NEUTRALMULTIPLICITYforward",true);
  PFJETID_FORWARD->addVariable("JET_FORWARD");
  handler->addObjectVariable("PFJETID_FORWARD",PFJETID_FORWARD);//....forward jet ID
  //
  ObjectVariableCombined* PFJETID_LOOSE = new ObjectVariableCombined("PFJETID_CENTRAL","PFJETID_ENDCAP",false);
  PFJETID_LOOSE->addVariable("PFJETID_FORWARD");
  handler->addObjectVariable("PFJETID_LOOSE",PFJETID_LOOSE);
  // Btagging : https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation76X
  handler->addObjectVariable("CSVT",new ObjectVariableInRange<double>("pfCombinedInclusiveSecondaryVertexV2BJetTags",0.935,1000.0));
  handler->addObjectVariable("CSVM",new ObjectVariableInRange<double>("pfCombinedInclusiveSecondaryVertexV2BJetTags",0.800,1000.0));
  handler->addObjectVariable("CSVL",new ObjectVariableInRange<double>("pfCombinedInclusiveSecondaryVertexV2BJetTags",0.460,1000.0));
  //
  handler->addObjectVariable("CSVraw",  new ObjectVariableRename<double>("pfCombinedInclusiveSecondaryVertexV2BJetTags",  "CSVraw"),false);
  handler->addObjectVariable("JPraw",   new ObjectVariableRename<double>("pfJetProbabilityBJetTags",                       "JPraw"),false);
  handler->addObjectVariable("cMVAraw", new ObjectVariableRename<double>("pfCombinedMVAV2BJetTags",                      "cMVAraw"),false);


  // --------------------------------------------------------------------------------------------------------------
  /////////////////////
  ///Track Variables///
  /////////////////////
  handler->addObjectVariable("TRACK_PFCHARGEDHADRONISO", new ObjectVariableRename<double>("chargedHadronIsoFromPF","PF_CHARGEDHADRONISO"),false);
  handler->addObjectVariable("TRACK_PFNEUTRALHADRONISO", new ObjectVariableRename<double>("neutralHadronIsoFromPF","PF_NEUTRALHADRONISO"),false);
  handler->addObjectVariable("TRACK_PFPHOTONISO",        new ObjectVariableRename<double>("neutralPhotonIsoFromPF","PF_PHOTONISO"),false);
  handler->addObjectVariable("TRACK_BETA",               new ObjectVariableRename<double>("betaIsoFromPF","BETA"),false);
  handler->addObjectVariable("TRACK_fromPV",             new ObjectVariableInRange<int>("fromPV",2,100000));
  handler->addObjectVariable("TRACK_PROMPT",             new ObjectVariableCombined("TRACK_fromPV","MUON_dxy",true,"TRACK_PROMPT"));
  handler->addObjectVariable("TRACK_NONPROMPT",          new ObjectVariableReversed("TRACK_PROMPT"));


  // --------------------------------------------------------------------------------------------------------------
  //////////////////////
  ///Photon Variables///
  //////////////////////
  // Cut Based Photon ID: https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonIdentificationRun2
  handler->addObjectVariable("PHOTON_BARREL_hadronicOverEm",        new ObjectVariableInRange<double>("hadronicOverEm",0.0,0.05));
  handler->addObjectVariable("PHOTON_ENDCAP_hadronicOverEm",        new ObjectVariableInRange<double>("hadronicOverEm",0.0,0.05));
  handler->addObjectVariable("PHOTON_BARREL_full5x5_sigmaIetaIeta", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0.0,0.0102));
  handler->addObjectVariable("PHOTON_ENDCAP_full5x5_sigmaIetaIeta", new ObjectVariableInRange<double>("full5x5_sigmaIetaIeta",0.0,0.0274));
  // BARREL : |eta|<1.479   |   ENDCAP : |eta|>1.479
  ObjectVariableCombined* photon_barrel = new ObjectVariableCombined("BARREL","PHOTON_BARREL_hadronicOverEm",true,"photon_barrel_good");
  photon_barrel->addVariable("PHOTON_BARREL_full5x5_sigmaIetaIeta");
  handler->addObjectVariable("PHOTON_BARREL",photon_barrel);
  ObjectVariableCombined* photon_endcap = new ObjectVariableCombined("ENDCAP","PHOTON_ENDCAP_hadronicOverEm",true,"photon_endcap_good");
  photon_endcap->addVariable("PHOTON_ENDCAP_full5x5_sigmaIetaIeta");
  handler->addObjectVariable("PHOTON_ENDCAP",photon_endcap);
  handler->addObjectVariable("PHOTON_COMBINED", new ObjectVariableCombined("PHOTON_BARREL","PHOTON_ENDCAP",false,"PHOTON_COMBINED"));
  //
  handler->addObjectVariable("PHOTON_CUT_LOOSEID",  new ObjectVariableValue<bool>("passLooseId",  true));
  handler->addObjectVariable("PHOTON_CUT_MEDIUMID", new ObjectVariableValue<bool>("passMediumId", true));
  handler->addObjectVariable("PHOTON_CUT_TIGHTID",  new ObjectVariableValue<bool>("passTightId",  true));


  // --------------------------------------------------------------------------------------------------------------
  //////////////////////
  ///Vertex Variables///
  //////////////////////
  handler->addObjectVariable("VERTEX_NDOF",   new ObjectVariableInRange<double>("ndof",4,100000));
  handler->addObjectVariable("VERTEX_Z",      new ObjectVariableInRange<double>("z",-24,24));
  handler->addObjectVariable("VERTEX_RHO",    new ObjectVariableInRange<double>("rho",-4,4));
  handler->addObjectVariable("VERTEX_NOTFAKE",new ObjectVariableReversed("isFake"));


  // --------------------------------------------------------------------------------------------------------------
  ///////////////////////
  ///Trigger Variables///
  ///////////////////////
  handler->addObjectVariable("ACCEPT",      new ObjectVariableRename<bool>("accept","ACCEPT"));
  handler->addObjectVariable("TRIGGERNAME", new ObjectVariableRename<TString>("triggerName","TRIGGERNAME"));
  handler->addObjectVariable("Accepted",    new ObjectVariableValue<bool>("ACCEPT", true));
  handler->addObjectVariable("WasRun",      new ObjectVariableValue<bool>("wasrun", true));
  
  //...................................................................................................................  
  //////////////////////
  ///CONECORRECTEDPT////
  //////////////////////
  //This should be declared after PT, MINIISO, ptRatio and ptRel
  handler->addObjectVariable("conecorrectedPt", new ObjectVariableConeCorrectedPt("PT","MINIISO","ptRatio","ptRel",0.4,0,0,"conecorrectedPt"));
  
}


