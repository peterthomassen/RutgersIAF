void setupTriggerCut(SignatureHandler* handler, int mode = 0)
{
  SignatureCutTrigger* triggerCut = new SignatureCutTrigger;
  //mode 0 = All
  //mode 1 = MuEG
  //mode 2 = DoubleMuon
  //mode 3 = DoubleElectron
  //mode 4 = SingleMuon
  //mode 5 = SingleElectron

  SignatureCutThresholdElectron* singleElectronThreshold = new SignatureCutThresholdElectron("singleElectronThreshold");
  singleElectronThreshold->addThreshold(85.0);
  SignatureCutThresholdElectron* doubleElectronThreshold = new SignatureCutThresholdElectron("doubleElectronThreshold");
  doubleElectronThreshold->addThreshold(20.0);
  doubleElectronThreshold->addThreshold(10.0);
  SignatureCutThresholdMuon* singleMuonThreshold = new SignatureCutThresholdMuon("singleMuonThreshold");
  singleMuonThreshold->addThreshold(35.0);
  SignatureCutThresholdMuon* doubleMuonThreshold = new SignatureCutThresholdMuon("doubleMuonThreshold");
  doubleMuonThreshold->addThreshold(20.0);
  doubleMuonThreshold->addThreshold(10.0);

  //Setup MuEG cuts
  SignatureCutThresholdElectron* singleElectron_mueg_lead = new SignatureCutThresholdElectron("singleElectron_mueg_lead");
  singleElectron_mueg_lead->addThreshold(20.0);
  SignatureCutThresholdElectron* singleElectron_mueg_nexttolead = new SignatureCutThresholdElectron("singleElectron_mueg_lead");
  singleElectron_mueg_nexttolead->addThreshold(10.0);

  SignatureCutThresholdMuon* singleMuon_mueg_lead = new SignatureCutThresholdMuon("singleMuon_mueg_lead");
  singleMuon_mueg_lead->addThreshold(20.0);
  SignatureCutThresholdMuon* singleMuon_mueg_nexttolead = new SignatureCutThresholdMuon("singleMuon_mueg_lead");
  singleMuon_mueg_nexttolead->addThreshold(10.0);

  SignatureCutCombined* muEG_threshold_electron_lead = new SignatureCutCombined(singleElectron_mueg_lead,singleMuon_mueg_nexttolead,true,"mueg_el_mu");
  SignatureCutCombined* muEG_threshold_muon_lead = new SignatureCutCombined(singleMuon_mueg_lead,singleElectron_mueg_nexttolead,true,"mueg_mu_el");

  SignatureCutCombined* muEG_threshold = new SignatureCutCombined(muEG_threshold_electron_lead,muEG_threshold_muon_lead,false,"mueg_thresh");
  //SignatureCutCombined* muEG_threshold = new SignatureCutCombined(doubleMuonThreshold,doubleElectronThreshold,false,"mueg_thresh");

  triggerCut->addCut("MuEG",muEG_threshold);
  triggerCut->addCut("DoubleMuon",doubleMuonThreshold);
  triggerCut->addCut("DoubleElectron",doubleElectronThreshold);
  triggerCut->addCut("SingleMuon",singleMuonThreshold);
  triggerCut->addCut("SingleElectron",singleElectronThreshold);

  switch(mode){
    case 1:
      addAcceptTriggers(triggerCut,"MuEG",getMuonElectronTriggers());
      break;
    case 2:
      addAcceptTriggers(triggerCut,"DoubleMuon",getDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getMuonElectronTriggers());
      break;
    case 3:
      addAcceptTriggers(triggerCut,"DoubleElectron",getDoubleElectronTriggers());
      addVetoTriggers(triggerCut,"DoubleMuon",getDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getMuonElectronTriggers());
      break;
    case 4:
      addAcceptTriggers(triggerCut,"SingleMuon",getSingleMuonTriggers());//changed geSingleMuonTriggers to getSingleMuonTriggers
      addVetoTriggers(triggerCut,"DoubleElectron",getDoubleElectronTriggers());
      addVetoTriggers(triggerCut,"DoubleMuon",getDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getMuonElectronTriggers());
      break;
    case 5:
      addAcceptTriggers(triggerCut,"SingleElectron",getSingleElectronTriggers());//same here
      addVetoTriggers(triggerCut,"SingleMuon",getSingleMuonTriggers());//same here
      addVetoTriggers(triggerCut,"DoubleElectron",getDoubleElectronTriggers());
      addVetoTriggers(triggerCut,"DoubleMuon",getDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getMuonElectronTriggers());
      break;

  default:
    break;
  }
  handler->addHandlerCut(triggerCut);
}
//--------------------------------
//--------------------------------
void setupFakeTriggers(SignatureHandler* handler, int mode = 0)
{
  SignatureCutTrigger* triggerCut = new SignatureCutTrigger;
  SignatureCutThreshold* jetCut = new SignatureCutThreshold("goodJets","jetThresholdCut");
  jetCut->addThreshold(40.0);
  triggerCut->addCut("jet",jetCut);
  addAcceptTriggers(triggerCut,"jet",getHTTriggers());
}
//--------------------------------
//--------------------------------

//--------------------------------
//--------------------------------
void addVetoTriggers(SignatureCutTrigger* sigcut, TString name, vector<int> trigvec)
{
  for(int i = 0; i < (int)trigvec.size(); i++){
    sigcut->addVetoTrigger(name,trigvec[i]);
  }
}
//--------------------------------
//--------------------------------
void addAcceptTriggers(SignatureCutTrigger* sigcut, TString name, vector<int> trigvec)
{
  for(int i = 0; i < (int)trigvec.size(); i++){
    sigcut->addAcceptTrigger(name,trigvec[i]);
  }
}
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
void setupStandardCuts(SignatureHandler* handler,bool fakeStudy=false)
{
  ObjectCutPt* leptonPtCut = new ObjectCutPt(10.0,-1,"leptonptcut");
  ObjectCutEta* leptonEtaCut = new ObjectCutEta(2.4,"leptonetacut");
  ObjectCutIrel* isolatedLeptonCut = new ObjectCutIrel(0.0,0.15);
  ObjectCutIrel* nonIsolatedLeptonCut = new ObjectCutIrel(0.2,-1);
  ObjectCutIrel* nonIsolatedElectronCut = new ObjectCutIrel(0.2,5.0);
  ObjectCutVertDz* leptonVertDzCut = new ObjectCutVertDz(0.5);
  ObjectCutVertDxy* promptLeptonCut = new ObjectCutVertDxy(0.02);
  ObjectCutReversed* nonPromptLeptonCut = new ObjectCutReversed(promptLeptonCut);
  ObjectCutBeamD0* leptonBeamD0Cut = new ObjectCutBeamD0(0.02);
  ObjectCutBeamDxy* leptonBeamDxyCut = new ObjectCutBeamDxy(0.02);
  ObjectCutValidTrackerHits* isoTrackNHitCut = new ObjectCutValidTrackerHits(11,-1);
  ObjectCutAbsRel* leptonAbsRelCut = new ObjectCutAbsRel(0.0,10.0);
  ObjectCutGlobalMuonPromptTight* muonGlobalPromptTightCut = new ObjectCutGlobalMuonPromptTight;
  ObjectCutTrackerMuon* muonTrackerCut = new ObjectCutTrackerMuon;
  ObjectCutIsPF* isPFcut = new ObjectCutIsPF;
  ObjectCutChi2Ndof* chi2ndofCut = new ObjectCutChi2Ndof;

  ///////////////
  //Setup Muons//
  ///////////////

  ObjectCutCombined* goodMuonCut = new ObjectCutCombined(leptonPtCut,leptonEtaCut,true);
  //goodMuonCut->addCut(new ObjectCutValidPixelHits);
  goodMuonCut->addCut(new ObjectCutMuonInnerNumberOfValidPixelHits(1,-1));
  goodMuonCut->addCut(new ObjectCutTrackLayersWithMeasurement);
  goodMuonCut->addCut(new ObjectCutMuonMatches);
  goodMuonCut->addCut(isPFcut);
  goodMuonCut->addCut(new ObjectCutMuonGlobal);
  goodMuonCut->addCut(new ObjectCutValidMuonHits);
  //goodMuonCut->addCut(leptonVertDxyCut);
  //goodMuonCut->addCut(leptonVertDzCut);
  //goodMuonCut->addCut(chi2ndofCut);
  goodMuonCut->addCut(new ObjectCutMuonNormalizedChi2(0,10));
  goodMuonCut->addCut(new ObjectCutMuonInnerVertDz(0,0.5));
  //goodMuonCut->addCut(new ObjectCutMuonInnerVertDxy(0.0,0.02));
  //goodMuonCut->addCut(muonIrelCut);
  ObjectCutMuonInnerVertDxy* promptMuonCut = new ObjectCutMuonInnerVertDxy(0.0,0.02);
  ObjectCutMuonInnerVertDxy* nonPromptMuonCut = new ObjectCutMuonInnerVertDxy(0.03,-1);

  handler->addProductCut("goodMuons",goodMuonCut);
  handler->addProductCut("goodMuons",promptMuonCut);
  handler->addProductCut("goodMuons",isolatedLeptonCut);

  ///////////////////
  //Setup Electrons//
  ///////////////////

  ObjectCutElectronDeltaEta* electronDeltaEtaCut = new ObjectCutElectronDeltaEta(0.007,0.009);
  ObjectCutElectronDeltaPhi* electronDeltaPhiCut = new ObjectCutElectronDeltaPhi(0.15,0.10);
  ObjectCutElectronHadOverEm* electronHadOverEmCut = new ObjectCutElectronHadOverEm(0.12,0.10);
  ObjectCutElectronMissingHits* electronMissingHitsCut = new ObjectCutElectronMissingHits(1);
  ObjectCutElectronSigmaIetaIeta* electronSigmaIetaIetaCut = new ObjectCutElectronSigmaIetaIeta(0.01,0.03);
  ObjectCutElectronExpectedInnerHits* electronExpectedInnerHitsCut = new ObjectCutElectronExpectedInnerHits;
  ObjectCutElectronEminusP* electronEminusPCut = new ObjectCutElectronEminusP;
  ObjectCutElectronChargeConsistent* electronChargeConsistentCut = new ObjectCutElectronChargeConsistent;
  ObjectCutElectronVertexFitProbability* electronVtxProbCut = new ObjectCutElectronVertexFitProbability;
  ObjectCutElectronIsConversion* electronConversionCut = new ObjectCutElectronIsConversion(false);
  ObjectCutElectronSuperClusterEta* inGap = new ObjectCutElectronSuperClusterEta;
  ObjectCutReversed* gapCut = new ObjectCutReversed(inGap);
  ObjectCutElectronVertDz* electronVertDzCut = new ObjectCutElectronVertDz(0.2);
  ObjectCutElectronVertDxy* promptElectronCut = new ObjectCutElectronVertDxy(0.02);
  ObjectCutReversed* nonPromptElectronCut = new ObjectCutReversed(new ObjectCutElectronVertDxy(0.03));


  ObjectCutCombined* goodElectronCut = new ObjectCutCombined(leptonPtCut,leptonEtaCut,true,"goodElectronCutCombined");
  goodElectronCut->addCut(electronVertDzCut);
  goodElectronCut->addCut(electronDeltaEtaCut);
  goodElectronCut->addCut(electronDeltaPhiCut);
  goodElectronCut->addCut(electronHadOverEmCut);
  goodElectronCut->addCut(electronSigmaIetaIetaCut);
  goodElectronCut->addCut(electronMissingHitsCut);
  //goodElectronCut->addCut(leptonVertDxyCut);
  goodElectronCut->addCut(gapCut);
  goodElectronCut->addCut(electronEminusPCut);
  //goodElectronCut->addCut(electronIrelCut);
  //goodElectronCut->addCut(electronChargeConsistentCut);
  //goodElectronCut->addCut(electronVtxProbCut);
  goodElectronCut->addCut(electronConversionCut);
  //goodElectronCut->addCut(isPFcut);
  handler->addProductSeparation("goodElectrons","goodMuons",0.1);
  handler->addProductCut("goodElectrons",goodElectronCut);
  handler->addProductCut("goodElectrons",isolatedLeptonCut);
  handler->addProductCut("goodElectrons",promptElectronCut);

  /////////////////
  //Setup Photons//
  /////////////////

  ObjectCutPhotonIsTight* photonTightCut = new ObjectCutPhotonIsTight(true);
  ObjectCutElectronSigmaIetaIeta* photonSigmaIetaIetaCut = new ObjectCutElectronSigmaIetaIeta(0.011,0.034);
  ObjectCutElectronHadOverEm* photonHadOverEmCut = new ObjectCutElectronHadOverEm(0.06,0.05);
  ObjectCutEta* barrelEtaCut = new ObjectCutEta(1.48);
  ObjectCutReversed* endcapEtaCut = new ObjectCutReversed(barrelEtaCut);
  ObjectCutCombined* photonBarrelIsolation = new ObjectCutCombined(barrelEtaCut,new ObjectCutIrelChargedHadron(0,0.06),true);
  photonBarrelIsolation->addCut(new ObjectCutIrelNeutralHadron(0,0.16));
  photonBarrelIsolation->addCut(new ObjectCutIrelPhoton(0,0.08));
  ObjectCutCombined* photonEndcapIsolation = new ObjectCutCombined(endcapEtaCut,new ObjectCutIrelChargedHadron(0,0.05),true);
  photonEndcapIsolation->addCut(new ObjectCutIrelNeutralHadron(0,0.1));
  photonEndcapIsolation->addCut(new ObjectCutIrelPhoton(0,0.12));
  ObjectCutCombined* photonIsolationCut = new ObjectCutCombined(photonBarrelIsolation,photonEndcapIsolation);


  handler->addPhotonCut(leptonPtCut);
  handler->addPhotonCut(leptonEtaCut);
  //handler->addPhotonCut(photonTightCut);
  //handler->addPhotonCut(leptonIrelCut);
  handler->addPhotonCut(photonSigmaIetaIetaCut);
  handler->addPhotonCut(photonHadOverEmCut);
  handler->addPhotonCut(photonIsolationCut);
  //handler->addPhotonCut(leptonAbsRelCut);

  //////////////
  //Setup Jets//
  //////////////

  ObjectCutPt* jetPtCut = new ObjectCutPt(30,-1);
  ObjectCutEta* jetEtaCut = new ObjectCutEta(2.5);
  ObjectCutCombined* jetLowEtaCut = new ObjectCutCombined(new ObjectCutEta(2.4),new ObjectCutJetChargedHadronFraction,true);
  jetLowEtaCut->addCut(new ObjectCutJetChargedEMFraction);
  jetLowEtaCut->addCut(new ObjectCutJetChargedMultiplicity);
  ObjectCutReversed* jetHighEtaCut = new ObjectCutReversed(new ObjectCutEta(2.4));
  ObjectCutCombined* jetEtaCuts = new ObjectCutCombined(jetLowEtaCut,jetHighEtaCut);

  handler->addJetCut(jetPtCut);
  handler->addJetCut(jetEtaCut);
  handler->addJetCut(new ObjectCutJetNumberConstituents);
  handler->addJetCut(new ObjectCutJetNeutralEMFraction);
  handler->addJetCut(new ObjectCutJetNeutralHadronFraction);
  handler->addJetCut(jetEtaCuts);

  handler->addProduct("bJetsCSVM","goodJets");
  handler->addProductCut("bJetsCSVM",new ObjectCutJetBDiscPositive);
  handler->addProductSeparation("bJetsCSVM","goodMuons",0.3);
  handler->addProductSeparation("bJetsCSVM","goodElectrons",0.3);

  //////////////
  //Setup Taus//
  //////////////

  ObjectCutPt* tauPtCut = new ObjectCutPt(20.0,-1,"tauptcut");
  ObjectCutTauIsPF* tauPFCut = new ObjectCutTauIsPF(true);
  ObjectCutIrel* tauIrelCut = new ObjectCutIrelTau(0.0,0.15);
  ObjectCutIrel010to030* tauIrelRingCut = new ObjectCutIrel010to030Tau(0.0,0.15);

  ObjectCutCombined* tauChargeCut = new ObjectCutCombined(new ObjectCutTauCharge(-1.1,-0.9),new ObjectCutTauCharge(0.9,1.1));

  handler->addTauCut(tauPtCut);
  handler->addTauCut(new ObjectCutEta(2.3));
  handler->addTauCut(new ObjectCutTauDiscriminants(19));//decaymodefinding
  handler->addTauCut(new ObjectCutTauDiscriminants(29));//againstelectronmva
  handler->addTauCut(new ObjectCutTauDiscriminants(24));//againstmuontight
  handler->addTauCut(new ObjectCutTauDiscriminants(26));//byloosecombinedisodbsumptcorr
  handler->addTauCut(tauChargeCut);

  ////////////////
  //Setup Tracks//
  ////////////////

  ObjectCutCombined* goodTrackCut = new ObjectCutCombined(leptonPtCut,leptonEtaCut,true);
  goodTrackCut->addCut(new ObjectCutTrackIsTracker(true));
  goodTrackCut->addCut(new ObjectCutTrackIsGlobal(false));
  goodTrackCut->addCut(new ObjectCutTrackIsMuon(false));
  goodTrackCut->addCut(leptonVertDzCut);
  goodTrackCut->addCut(isoTrackNHitCut);
  goodTrackCut->addCut(new ObjectCutNdof());
  goodTrackCut->addCut(new ObjectCutBeamD0(0.2));

  handler->addProduct("goodTracks","allRecoTracks");
  handler->addProductCut("goodTracks",goodTrackCut);
  handler->addProductSeparation("goodTracks","goodMuons",0.1);
  handler->addProductSeparation("goodTracks","goodElectrons",0.1);
  handler->addProductSeparation("goodTracks","goodTaus",0.3);
  handler->setSelfSeparate("goodTracks",0.005);

  handler->addProduct("isoTracksPrompt","goodTracks");
  handler->addProductCut("isoTracksPrompt",promptLeptonCut);
  handler->addProductCut("isoTracksPrompt",isolatedLeptonCut);
  handler->addProduct("nonIsoTracksPrompt","goodTracks");
  handler->addProductCut("nonIsoTracksPrompt",nonIsolatedLeptonCut);
  handler->addProductCut("nonIsoTracksPrompt",promptLeptonCut);

  handler->addProduct("isoTracksNonPrompt","goodTracks");
  handler->addProductCut("isoTracksNonPrompt",nonPromptLeptonCut);
  handler->addProductCut("isoTracksNonPrompt",isolatedLeptonCut);
  handler->addProduct("nonIsoTracksNonPrompt","goodTracks");
  handler->addProductCut("nonIsoTracksNonPrompt",nonPromptLeptonCut);
  handler->addProductCut("nonIsoTracksNonPrompt",nonIsolatedLeptonCut);

  handler->addProduct("nonIsoTracksPromptElectrons","goodTracks");
  handler->addProductCut("nonIsoTracksPromptElectrons",nonIsolatedElectronCut);
  handler->addProductCut("nonIsoTracksPromptElectrons",promptLeptonCut);

  handler->addProduct("nonIsoMuonsPrompt","allMuons");
  handler->addProductCut("nonIsoMuonsPrompt",goodMuonCut);
  handler->addProductCut("nonIsoMuonsPrompt",promptMuonCut);
  handler->addProductCut("nonIsoMuonsPrompt",nonIsolatedLeptonCut);

  handler->addProduct("nonIsoElectronsPrompt","allElectrons");
  handler->addProductCut("nonIsoElectronsPrompt",goodElectronCut);
  handler->addProductCut("nonIsoElectronsPrompt",promptElectronCut);
  handler->addProductCut("nonIsoElectronsPrompt",nonIsolatedElectronCut);

  /////////////////////
  //Setup Vertex Cuts//
  /////////////////////

  handler->addRecoVertexCut(new VertexCutNdof);
  handler->addRecoVertexCut(new VertexCutR);
  handler->addRecoVertexCut(new VertexCutZ);

  handler->addHandlerCut(new SignatureCutNVertex(1.0));

  handler->addHandlerCut(new SignatureCutFilter("primaryVertexFilter"));
  handler->addHandlerCut(new SignatureCutFilter("noScrapingFilter"));
  handler->addHandlerCut(new SignatureCutFilter("HBHENoiseFilter"));
  handler->addHandlerCut(new SignatureCutFilter("CSCTightHaloFilter"));
  handler->addHandlerCut(new SignatureCutFilter("hcalLaserEventFilter"));
  handler->addHandlerCut(new SignatureCutFilter("EcalDeadCellTriggerPrimitiveFilter"));
  handler->addHandlerCut(new SignatureCutFilter("trackingFailureFilter"));
  handler->addHandlerCut(new SignatureCutFilter("eeBadScFilter"));


  handler->setSelfSeparate("goodMuons",0.1);
  handler->setSelfSeparate("goodElectrons",0.1);
  handler->setSelfSeparate("goodTaus",0.15);
  handler->setSelfSeparate("goodIsoTracks",0.005);
  handler->addProductSeparation("goodElectrons","goodMuons",0.1);
  handler->addProductSeparation("goodTaus","goodMuons",0.1);
  handler->addProductSeparation("goodTaus","goodElectrons",0.1);
  //handler->addProductSeparation("goodTaus","goodIsoTracks",0.3);
  handler->addProductSeparation("goodJets","goodMuons",0.4);
  handler->addProductSeparation("goodJets","goodElectrons",0.4);
  handler->addProductSeparation("goodJets","goodTaus",0.4);
  //handler->addProductSeparation("goodJets","goodIsoTracks",0.3);
  handler->addProductSeparation("goodPhotons","goodMuons",0.1);
  handler->addProductSeparation("goodPhotons","goodElectrons",0.1);
  handler->addProductSeparation("goodPhotons","goodTaus",0.1);
  handler->addProductSeparation("goodPhotons","goodJets",0.3);
  //handler->addProductSeparation("goodPhotons","goodIsoTracks",0.1);
  //handler->addProductSeparation("goodIsoTracks","goodMuons",0.1);
  //handler->addProductSeparation("goodIsoTracks","goodElectrons",0.1);

  handler->addProduct("leadingJet","goodJets");
  handler->setSelfSeparate("leadingJet",10000.0);

  //handler->addProductSeparation("nonIsoElectrons","leadingJet",0.6);
  //handler->addProductSeparation("nonIsoMuons","leadingJet",0.6);

  ObjectCutCharge* posChargeCut = new ObjectCutCharge(0.01,300.0);
  ObjectCutCharge* negChargeCut = new ObjectCutCharge(-300.0,-0.01);

  handler->addProduct("negNonIsoElectrons","nonIsoElectrons");
  handler->addProductCut("negNonIsoElectrons",negChargeCut);
  handler->addProduct("posNonIsoElectrons","nonIsoElectrons");
  handler->addProductCut("posNonIsoElectrons",posChargeCut);

  handler->addProduct("negNonIsoMuons","nonIsoMuons");
  handler->addProductCut("negNonIsoMuons",negChargeCut);
  handler->addProduct("posNonIsoMuons","nonIsoMuons");
  handler->addProductCut("posNonIsoMuons",posChargeCut);


  if(fakeStudy){

    ObjectCutMCStatus* statusGoodCut = new ObjectCutMCStatus(3);
    ObjectCutMCMotherPdgID* mothW = new ObjectCutMCMotherPdgID(24,true);
    ObjectCutMCMotherPdgID* motherTau = new ObjectCutMCMotherPdgID(15,true);
    ObjectCutMCPdgID* tauCut = new ObjectCutMCPdgID(15,true);
    ObjectCutCombined* motherW = new ObjectCutCombined(mothW,motherTau,false);
    ObjectCutMCPdgID* electronCut = new ObjectCutMCPdgID(11,true);
    ObjectCutMCPdgID* muonCut = new ObjectCutMCPdgID(13,true);
    ObjectCutCombined* leptonCut = new ObjectCutCombined(electronCut,muonCut,false);
  //leptonCut->addCut(tauCut);

    ObjectCutMCMotherPdgID* mothZ = new ObjectCutMCMotherPdgID(23,true);
    handler->addProduct("leptonsFromZ","allMCparticles");
    handler->addProductCut("leptonsFromZ",statusGoodCut);
    handler->addProductCut("leptonsFromZ",leptonCut);
    handler->addProductCut("leptonsFromZ",mothZ);

    handler->addProduct("leptonsFromW","allMCparticles");
    handler->addProductCut("leptonsFromW",statusGoodCut);
    handler->addProductCut("leptonsFromW",leptonCut);
    handler->addProductCut("leptonsFromW",motherW);

    handler->addProduct("isoMuons","goodMuons");

    handler->addProduct("jetMuons","allMuons");
    handler->addProductCut("jetMuons",goodMuonCut);
    handler->addProductCut("jetMuons",promptMuonCut);
    handler->addProductCut("jetMuons",nonIsolatedLeptonCut);

    handler->addProduct("jetMuonsNonPrompt","allMuons");
    handler->addProductCut("jetMuonsNonPrompt",goodMuonCut);
    handler->addProductCut("jetMuonsNonPrompt",nonPromptMuonCut);
    handler->addProductCut("jetMuonsNonPrompt",nonIsolatedLeptonCut);

    handler->addProduct("isoMuonsNonPrompt","allMuons");
    handler->addProductCut("isoMuonsNonPrompt",goodMuonCut);
    handler->addProductCut("isoMuonsNonPrompt",nonPromptMuonCut);
    handler->addProductCut("isoMuonsNonPrompt",isolatedLeptonCut);

    handler->addProduct("isoTestElectrons","allElectrons");
    handler->addProductCut("isoTestElectrons",goodElectronCut);
    handler->addProductCut("isoTestElectrons",promptLeptonCut);

    handler->addProduct("isoTestMuons","allMuons");
    handler->addProductCut("isoTestMuons",goodMuonCut);
    handler->addProductCut("isoTestMuons",promptMuonCut);

    handler->addProduct("isoTestElectronsNonPrompt","allElectrons");
    handler->addProductCut("isoTestElectronsNonPrompt",goodElectronCut);
    handler->addProductCut("isoTestElectronsNonPrompt",nonPromptElectronCut);

    handler->addProduct("isoTestMuonsNonPrompt","allMuons");
    handler->addProductCut("isoTestMuonsNonPrompt",goodMuonCut);
    handler->addProductCut("isoTestMuonsNonPrompt",nonPromptMuonCut);

    handler->addProduct("isoElectrons","goodElectrons");

    handler->addProduct("baseElectrons","allElectrons");
    handler->addProductCut("baseElectrons",goodElectronCut);

    handler->addProduct("jetElectrons","allElectrons");
    handler->addProductCut("jetElectrons",goodElectronCut);
    handler->addProductCut("jetElectrons",promptLeptonCut);
    handler->addProductCut("jetElectrons",nonIsolatedLeptonCut);

    handler->addProduct("jetElectronsNonPrompt","allElectrons");
    handler->addProductCut("jetElectronsNonPrompt",goodElectronCut);
    handler->addProductCut("jetElectronsNonPrompt",nonPromptElectronCut);
    handler->addProductCut("jetElectronsNonPrompt",nonIsolatedLeptonCut);

    handler->addProduct("isoElectronsNonPrompt","allElectrons");
    handler->addProductCut("isoElectronsNonPrompt",goodElectronCut);
    handler->addProductCut("isoElectronsNonPrompt",nonPromptElectronCut);
    handler->addProductCut("isoElectronsNonPrompt",isolatedLeptonCut);
    
    handler->addIsotrackCut(goodTrackCut);
    handler->addIsotrackCut(isolatedLeptonCut);
    handler->addIsotrackCut(promptLeptonCut);

    handler->addProduct("isoTracks","allRecoTracks");
    handler->addProductCut("isoTracks",goodTrackCut);
    handler->addProductCut("isoTracks",isolatedLeptonCut);
    handler->addProductCut("isoTracks",promptLeptonCut);
    
    handler->addProduct("isoTracksNonPrompt","allRecoTracks");
    handler->addProductCut("isoTracksNonPrompt",goodTrackCut);
    handler->addProductCut("isoTracksNonPrompt",isolatedLeptonCut);
    handler->addProductCut("isoTracksNonPrompt",nonPromptLeptonCut);

    handler->addProduct("jetTracks","allRecoTracks");
    handler->addProductCut("jetTracks",goodTrackCut);
    handler->addProductCut("jetTracks",nonIsolatedLeptonCut);
    handler->addProductCut("jetTracks",promptLeptonCut);

    handler->addProduct("jetTracksNonPrompt","allRecoTracks");
    handler->addProductCut("jetTracksNonPrompt",goodTrackCut);
    handler->addProductCut("jetTracksNonPrompt",nonIsolatedLeptonCut);
    handler->addProductCut("jetTracksNonPrompt",nonPromptLeptonCut);

    handler->addProductSeparation("jetMuons","leadingJet",0.6);
    handler->addProductSeparation("jetTracks","leadingJet",0.6);
    handler->addProductSeparation("jetElectrons","leadingJet",0.6);
    handler->addProductSeparation("jetMuonsNonPrompt","leadingJet",0.6);
    handler->addProductSeparation("jetTracksNonPrompt","leadingJet",0.6);
    handler->addProductSeparation("jetElectronsNonPrompt","leadingJet",0.6);
    handler->addProductSeparation("isoElectronsNonPrompt","leadingJet",0.6);
    handler->addProductSeparation("isoMuonsNonPrompt","leadingJet",0.6);
    handler->addProductSeparation("isoTracksNonPrompt","leadingJet",0.6);
    handler->addProductSeparation("isoTracks","leadingJet",0.6);
    handler->addProductSeparation("isoMuons","leadingJet",0.6);
    handler->addProductSeparation("isoElectrons","leadingJet",0.6);

    handler->addProductSeparation("isoTestElectrons","goodMuons",0.1);
    handler->addProductSeparation("isoTestElectrons","leptonsFromZ",0.3);
    handler->addProductSeparation("isoTestElectrons","leptonsFromW",0.3);
    handler->addProductSeparation("isoTestMuons","leptonsFromZ",0.3);
    handler->addProductSeparation("isoTestMuons","leptonsFromW",0.3);

    handler->addProductSeparation("isoTestElectronsNonPrompt","leptonsFromW",0.3);
    handler->addProductSeparation("isoTestElectronsNonPrompt","leptonsFromZ",0.3);
    handler->addProductSeparation("isoTestMuonsNonPrompt","leptonsFromW",0.3);
    handler->addProductSeparation("isoTestMuonsNonPrompt","leptonsFromZ",0.3);


    handler->addProduct("isoTestElectronsAwayB","isoTestElectrons");
    handler->addProduct("isoTestElectronsNonPromptAwayB","isoTestElectronsNonPrompt");
    handler->addProduct("isoTestMuonsAwayB","isoTestMuons");
    handler->addProduct("isoTestMuonsNonPromptAwayB","isoTestMuonsNonPrompt");

    handler->addProductSeparation("isoTestElectronsAwayB","bJetsCSVM",0.3);
    handler->addProductSeparation("isoTestElectronsNonPromptAwayB","bJetsCSVM",0.3);
    handler->addProductSeparation("isoTestMuonsAwayB","bJetsCSVM",0.3);
    handler->addProductSeparation("isoTestMuonsNonPromptAwayB","bJetsCSVM",0.3);
    
    handler->addProductSeparation("jetTracks","goodElectrons",0.1);
    handler->addProductSeparation("jetTracks","goodMuons",0.1);
    handler->addProductSeparation("jetTracks","jetMuons",0.005,0.05);
    handler->addProductSeparation("jetTracks","jetMuonsNonPrompt",0.005,0.05);
    handler->addProductSeparation("jetTracks","goodTaus",0.3);
    handler->addProductSeparation("jetTracksNonPrompt","goodElectrons",0.1);
    handler->addProductSeparation("jetTracksNonPrompt","goodMuons",0.1);
    handler->addProductSeparation("jetTracksNonPrompt","jetMuons",0.005,0.05);
    handler->addProductSeparation("jetTracksNonPrompt","jetMuonsNonPrompt",0.005,0.05);
    //handler->addProductSeparation("jetTracksNonPrompt","goodTaus",0.3);


  }
}
//--------------------------------
//--------------------------------
void setupTestSignatures(SignatureHandler* handler)
{
  SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);
  SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
  SignatureCutNDYPairs* dy1aboveZ = new SignatureCutNDYPairs(1,1,false,0,105);
  SignatureCutNDYPairs* dy0cut = new SignatureCutNDYPairs(0,0,false);
  SignatureCutNDYPairs* dyAoffZcut = new SignatureCutNDYPairs(0,10,false);
  SignatureCutNDYPairs* dyAonZcut = new SignatureCutNDYPairs(1,10,true);

  SignatureCutST* lowSTcut = new SignatureCutST(0,450);
  SignatureCutST* midSTcut = new SignatureCutST(450,750);
  SignatureCutST* highSTcut = new SignatureCutST(750,-1);
  SignatureCutST* above300STcut = new SignatureCutST(300,-1);
  SignatureCutST* above450STcut = new SignatureCutST(450,-1);

  SignatureCutNTauTrack* zeroTauCut = new SignatureCutNTauTrack(0,0);
  SignatureCutNTauTrack* oneTauCut = new SignatureCutNTauTrack(1,1);
  SignatureCutNTauTrack* twoTauCut = new SignatureCutNTauTrack(2,2);

  SignatureCutNElectron* zeroElectronCut = new SignatureCutNElectron(0,0);
  SignatureCutNElectron* oneElectronCut = new SignatureCutNElectron(1,1);
  SignatureCutNElectron* twoElectronCut = new SignatureCutNElectron(2,2);
  SignatureCutNElectron* threeElectronCut = new SignatureCutNElectron(3,3);
  SignatureCutNElectron* fourElectronCut = new SignatureCutNElectron(4,4);

  SignatureCutNMuon* zeroMuonCut = new SignatureCutNMuon(0,0);
  SignatureCutNMuon* oneMuonCut = new SignatureCutNMuon(1,1);
  SignatureCutNMuon* twoMuonCut = new SignatureCutNMuon(2,2);
  SignatureCutNMuon* threeMuonCut = new SignatureCutNMuon(3,3);
  SignatureCutNMuon* fourMuonCut = new SignatureCutNMuon(4,4);

  SignatureCutMET* lowMETcut = new SignatureCutMET(0,75);
  SignatureCutMET* highMETcut = new SignatureCutMET(75,-1);

  SignatureCutHT* lowHTcut = new SignatureCutHT(0,400);
  SignatureCutHT* highHTcut = new SignatureCutHT(400,-1);
  SignatureCutHT* HT400cut = new SignatureCutHT(400,-1);

  SignatureCutNBjetTrack* zeroBjetCut = new SignatureCutNBjetTrack(0,0,1.7);
  SignatureCutNBjetTrack* oneBjetCut = new SignatureCutNBjetTrack(1,1,1.7);
  SignatureCutNBjetTrack* twoBjetCut = new SignatureCutNBjetTrack(2,2,1.7);
  SignatureCutNBjetTrack* geoneBjetCut = new SignatureCutNBjetTrack(1,-1,1.7);
  SignatureCutNBjetTrack* getwoBjetCut = new SignatureCutNBjetTrack(2,-1,1.7);
  SignatureCutNBjetTrack* gethreeBjetCut = new SignatureCutNBjetTrack(3,-1,1.7);

  SignatureCutNMuEl* twoLepCut = new SignatureCutNMuEl(2,2);
  SignatureCutNMuEl* threeLepCut = new SignatureCutNMuEl(3,3);
  SignatureCutNMuEl* fourLepCut = new SignatureCutNMuEl(4,4);

  SignatureCutSameSignMuEl* sameSignCut = new SignatureCutSameSignMuEl();

  SignatureCutCombined* samesignEl = new SignatureCutCombined(twoElectronCut,dy0cut,true);
  SignatureCutCombined* samesignMu = new SignatureCutCombined(twoMuonCut,dy0cut,true);
  SignatureCutCombined* samesignMuEl = new SignatureCutCombined(samesignEl,samesignMu,false);

  //Now declare signatures and add cuts//
  Signature* L4B0offZ = new Signature("L4B0offZ","");
  L4B0offZ->addCut(dyAoffZcut);
  L4B0offZ->addCut(fourLepCut);
  L4B0offZ->addCut(zeroBjetCut);
  L4B0offZ->addCut(lowHTcut);
  L4B0offZ->addCut(lowMETcut);
  Signature* L4B0onZ = new Signature("L4B0onZ","");
  L4B0onZ->addCut(dyAonZcut);
  L4B0onZ->addCut(fourLepCut);
  L4B0onZ->addCut(zeroBjetCut);
  L4B0onZ->addCut(lowHTcut);
  L4B0onZ->addCut(lowMETcut);
  Signature* L3B0offZ = new Signature("L3B0offZ","");
  L3B0offZ->addCut(dyAoffZcut);
  L3B0offZ->addCut(threeLepCut);
  L3B0offZ->addCut(zeroBjetCut);
  L3B0offZ->addCut(lowHTcut);
  L3B0offZ->addCut(lowMETcut);
  Signature* L3B0onZ = new Signature("L3B0onZ","");
  L3B0onZ->addCut(dyAonZcut);
  L3B0onZ->addCut(threeLepCut);
  L3B0onZ->addCut(zeroBjetCut);
  L3B0onZ->addCut(lowHTcut);
  L3B0onZ->addCut(lowMETcut);
  Signature* L2B0SS = new Signature("L2B0SS","");
  L2B0SS->addCut(sameSignCut);
  L2B0SS->addCut(twoLepCut);
  L2B0SS->addCut(zeroBjetCut);
  L2B0SS->addCut(lowHTcut);
  L2B0SS->addCut(lowMETcut);

  Signature* L4B0offZHT = new Signature("L4B0offZHT","");
  L4B0offZHT->addCut(dyAoffZcut);
  L4B0offZHT->addCut(fourLepCut);
  L4B0offZHT->addCut(zeroBjetCut);
  L4B0offZHT->addCut(highHTcut);
  L4B0offZHT->addCut(lowMETcut);
  Signature* L4B0onZHT = new Signature("L4B0onZHT","");
  L4B0onZHT->addCut(dyAonZcut);
  L4B0onZHT->addCut(fourLepCut);
  L4B0onZHT->addCut(zeroBjetCut);
  L4B0onZHT->addCut(highHTcut);
  L4B0onZHT->addCut(lowMETcut);
  Signature* L3B0offZHT = new Signature("L3B0offZHT","");
  L3B0offZHT->addCut(dyAoffZcut);
  L3B0offZHT->addCut(threeLepCut);
  L3B0offZHT->addCut(zeroBjetCut);
  L3B0offZHT->addCut(highHTcut);
  L3B0offZHT->addCut(lowMETcut);
  Signature* L3B0onZHT = new Signature("L3B0onZHT","");
  L3B0onZHT->addCut(dyAonZcut);
  L3B0onZHT->addCut(threeLepCut);
  L3B0onZHT->addCut(zeroBjetCut);
  L3B0onZHT->addCut(highHTcut);
  L3B0onZHT->addCut(lowMETcut);
  Signature* L2B0SSHT = new Signature("L2B0SSHT","");
  L2B0SSHT->addCut(sameSignCut);
  L2B0SSHT->addCut(twoLepCut);
  L2B0SSHT->addCut(zeroBjetCut);
  L2B0SSHT->addCut(highHTcut);
  L2B0SSHT->addCut(lowMETcut);

  Signature* L4B0offZMET = new Signature("L4B0offZMET","");
  L4B0offZMET->addCut(dyAoffZcut);
  L4B0offZMET->addCut(fourLepCut);
  L4B0offZMET->addCut(zeroBjetCut);
  L4B0offZMET->addCut(lowHTcut);
  L4B0offZMET->addCut(highMETcut);
  Signature* L4B0onZMET = new Signature("L4B0onZMET","");
  L4B0onZMET->addCut(dyAonZcut);
  L4B0onZMET->addCut(fourLepCut);
  L4B0onZMET->addCut(zeroBjetCut);
  L4B0onZMET->addCut(lowHTcut);
  L4B0onZMET->addCut(highMETcut);
  Signature* L3B0offZMET = new Signature("L3B0offZMET","");
  L3B0offZMET->addCut(dyAoffZcut);
  L3B0offZMET->addCut(threeLepCut);
  L3B0offZMET->addCut(zeroBjetCut);
  L3B0offZMET->addCut(lowHTcut);
  L3B0offZMET->addCut(highMETcut);
  Signature* L3B0onZMET = new Signature("L3B0onZMET","");
  L3B0onZMET->addCut(dyAonZcut);
  L3B0onZMET->addCut(threeLepCut);
  L3B0onZMET->addCut(zeroBjetCut);
  L3B0onZMET->addCut(lowHTcut);
  L3B0onZMET->addCut(highMETcut);
  Signature* L2B0SSMET = new Signature("L2B0SSMET","");
  L2B0SSMET->addCut(sameSignCut);
  L2B0SSMET->addCut(twoLepCut);
  L2B0SSMET->addCut(zeroBjetCut);
  L2B0SSMET->addCut(lowHTcut);
  L2B0SSMET->addCut(highMETcut);

  Signature* L4B0offZHTMET = new Signature("L4B0offZHTMET","");
  L4B0offZHTMET->addCut(dyAoffZcut);
  L4B0offZHTMET->addCut(fourLepCut);
  L4B0offZHTMET->addCut(zeroBjetCut);
  L4B0offZHTMET->addCut(highHTcut);
  L4B0offZHTMET->addCut(highMETcut);
  Signature* L4B0onZHTMET = new Signature("L4B0onZHTMET","");
  L4B0onZHTMET->addCut(dyAonZcut);
  L4B0onZHTMET->addCut(fourLepCut);
  L4B0onZHTMET->addCut(zeroBjetCut);
  L4B0onZHTMET->addCut(highHTcut);
  L4B0onZHTMET->addCut(highMETcut);
  Signature* L3B0offZHTMET = new Signature("L3B0offZHTMET","");
  L3B0offZHTMET->addCut(dyAoffZcut);
  L3B0offZHTMET->addCut(threeLepCut);
  L3B0offZHTMET->addCut(zeroBjetCut);
  L3B0offZHTMET->addCut(highHTcut);
  L3B0offZHTMET->addCut(highMETcut);
  Signature* L3B0onZHTMET = new Signature("L3B0onZHTMET","");
  L3B0onZHTMET->addCut(dyAonZcut);
  L3B0onZHTMET->addCut(threeLepCut);
  L3B0onZHTMET->addCut(zeroBjetCut);
  L3B0onZHTMET->addCut(highHTcut);
  L3B0onZHTMET->addCut(highMETcut);
  Signature* L2B0SSHTMET = new Signature("L2B0SSHTMET","");
  L2B0SSHTMET->addCut(sameSignCut);
  L2B0SSHTMET->addCut(twoLepCut);
  L2B0SSHTMET->addCut(zeroBjetCut);
  L2B0SSHTMET->addCut(highHTcut);
  L2B0SSHTMET->addCut(highMETcut);

  Signature* L4B1offZ = new Signature("L4B1offZ","");
  L4B1offZ->addCut(dyAoffZcut);
  L4B1offZ->addCut(fourLepCut);
  L4B1offZ->addCut(oneBjetCut);
  L4B1offZ->addCut(lowHTcut);
  L4B1offZ->addCut(lowMETcut);
  Signature* L4B1onZ = new Signature("L4B1onZ","");
  L4B1onZ->addCut(dyAonZcut);
  L4B1onZ->addCut(fourLepCut);
  L4B1onZ->addCut(oneBjetCut);
  L4B1onZ->addCut(lowHTcut);
  L4B1onZ->addCut(lowMETcut);
  Signature* L3B1offZ = new Signature("L3B1offZ","");
  L3B1offZ->addCut(dyAoffZcut);
  L3B1offZ->addCut(threeLepCut);
  L3B1offZ->addCut(oneBjetCut);
  L3B1offZ->addCut(lowHTcut);
  L3B1offZ->addCut(lowMETcut);
  Signature* L3B1onZ = new Signature("L3B1onZ","");
  L3B1onZ->addCut(dyAonZcut);
  L3B1onZ->addCut(threeLepCut);
  L3B1onZ->addCut(oneBjetCut);
  L3B1onZ->addCut(lowHTcut);
  L3B1onZ->addCut(lowMETcut);
  Signature* L2B1SS = new Signature("L2B1SS","");
  L2B1SS->addCut(sameSignCut);
  L2B1SS->addCut(twoLepCut);
  L2B1SS->addCut(oneBjetCut);
  L2B1SS->addCut(lowHTcut);
  L2B1SS->addCut(lowMETcut);

  Signature* L4B1offZHT = new Signature("L4B1offZHT","");
  L4B1offZHT->addCut(dyAoffZcut);
  L4B1offZHT->addCut(fourLepCut);
  L4B1offZHT->addCut(oneBjetCut);
  L4B1offZHT->addCut(highHTcut);
  L4B1offZHT->addCut(lowMETcut);
  Signature* L4B1onZHT = new Signature("L4B1onZHT","");
  L4B1onZHT->addCut(dyAonZcut);
  L4B1onZHT->addCut(fourLepCut);
  L4B1onZHT->addCut(oneBjetCut);
  L4B1onZHT->addCut(highHTcut);
  L4B1onZHT->addCut(lowMETcut);
  Signature* L3B1offZHT = new Signature("L3B1offZHT","");
  L3B1offZHT->addCut(dyAoffZcut);
  L3B1offZHT->addCut(threeLepCut);
  L3B1offZHT->addCut(oneBjetCut);
  L3B1offZHT->addCut(highHTcut);
  L3B1offZHT->addCut(lowMETcut);
  Signature* L3B1onZHT = new Signature("L3B1onZHT","");
  L3B1onZHT->addCut(dyAonZcut);
  L3B1onZHT->addCut(threeLepCut);
  L3B1onZHT->addCut(oneBjetCut);
  L3B1onZHT->addCut(highHTcut);
  L3B1onZHT->addCut(lowMETcut);
  Signature* L2B1SSHT = new Signature("L2B1SSHT","");
  L2B1SSHT->addCut(sameSignCut);
  L2B1SSHT->addCut(twoLepCut);
  L2B1SSHT->addCut(oneBjetCut);
  L2B1SSHT->addCut(highHTcut);
  L2B1SSHT->addCut(lowMETcut);

  Signature* L4B1offZMET = new Signature("L4B1offZMET","");
  L4B1offZMET->addCut(dyAoffZcut);
  L4B1offZMET->addCut(fourLepCut);
  L4B1offZMET->addCut(oneBjetCut);
  L4B1offZMET->addCut(lowHTcut);
  L4B1offZMET->addCut(highMETcut);
  Signature* L4B1onZMET = new Signature("L4B1onZMET","");
  L4B1onZMET->addCut(dyAonZcut);
  L4B1onZMET->addCut(fourLepCut);
  L4B1onZMET->addCut(oneBjetCut);
  L4B1onZMET->addCut(lowHTcut);
  L4B1onZMET->addCut(highMETcut);
  Signature* L3B1offZMET = new Signature("L3B1offZMET","");
  L3B1offZMET->addCut(dyAoffZcut);
  L3B1offZMET->addCut(threeLepCut);
  L3B1offZMET->addCut(oneBjetCut);
  L3B1offZMET->addCut(lowHTcut);
  L3B1offZMET->addCut(highMETcut);
  Signature* L3B1onZMET = new Signature("L3B1onZMET","");
  L3B1onZMET->addCut(dyAonZcut);
  L3B1onZMET->addCut(threeLepCut);
  L3B1onZMET->addCut(oneBjetCut);
  L3B1onZMET->addCut(lowHTcut);
  L3B1onZMET->addCut(highMETcut);
  Signature* L2B1SSMET = new Signature("L2B1SSMET","");
  L2B1SSMET->addCut(sameSignCut);
  L2B1SSMET->addCut(twoLepCut);
  L2B1SSMET->addCut(oneBjetCut);
  L2B1SSMET->addCut(lowHTcut);
  L2B1SSMET->addCut(highMETcut);

  Signature* L4B1offZHTMET = new Signature("L4B1offZHTMET","");
  L4B1offZHTMET->addCut(dyAoffZcut);
  L4B1offZHTMET->addCut(fourLepCut);
  L4B1offZHTMET->addCut(oneBjetCut);
  L4B1offZHTMET->addCut(highHTcut);
  L4B1offZHTMET->addCut(highMETcut);
  Signature* L4B1onZHTMET = new Signature("L4B1onZHTMET","");
  L4B1onZHTMET->addCut(dyAonZcut);
  L4B1onZHTMET->addCut(fourLepCut);
  L4B1onZHTMET->addCut(oneBjetCut);
  L4B1onZHTMET->addCut(highHTcut);
  L4B1onZHTMET->addCut(highMETcut);
  Signature* L3B1offZHTMET = new Signature("L3B1offZHTMET","");
  L3B1offZHTMET->addCut(dyAoffZcut);
  L3B1offZHTMET->addCut(threeLepCut);
  L3B1offZHTMET->addCut(oneBjetCut);
  L3B1offZHTMET->addCut(highHTcut);
  L3B1offZHTMET->addCut(highMETcut);
  Signature* L3B1onZHTMET = new Signature("L3B1onZHTMET","");
  L3B1onZHTMET->addCut(dyAonZcut);
  L3B1onZHTMET->addCut(threeLepCut);
  L3B1onZHTMET->addCut(oneBjetCut);
  L3B1onZHTMET->addCut(highHTcut);
  L3B1onZHTMET->addCut(highMETcut);
  Signature* L2B1SSHTMET = new Signature("L2B1SSHTMET","");
  L2B1SSHTMET->addCut(sameSignCut);
  L2B1SSHTMET->addCut(twoLepCut);
  L2B1SSHTMET->addCut(oneBjetCut);
  L2B1SSHTMET->addCut(highHTcut);
  L2B1SSHTMET->addCut(highMETcut);

  Signature* L4B2offZ = new Signature("L4B2offZ","");
  L4B2offZ->addCut(dyAoffZcut);
  L4B2offZ->addCut(fourLepCut);
  L4B2offZ->addCut(twoBjetCut);
  L4B2offZ->addCut(lowHTcut);
  L4B2offZ->addCut(lowMETcut);
  Signature* L4B2onZ = new Signature("L4B2onZ","");
  L4B2onZ->addCut(dyAonZcut);
  L4B2onZ->addCut(fourLepCut);
  L4B2onZ->addCut(twoBjetCut);
  L4B2onZ->addCut(lowHTcut);
  L4B2onZ->addCut(lowMETcut);
  Signature* L3B2offZ = new Signature("L3B2offZ","");
  L3B2offZ->addCut(dyAoffZcut);
  L3B2offZ->addCut(threeLepCut);
  L3B2offZ->addCut(twoBjetCut);
  L3B2offZ->addCut(lowHTcut);
  L3B2offZ->addCut(lowMETcut);
  Signature* L3B2onZ = new Signature("L3B2onZ","");
  L3B2onZ->addCut(dyAonZcut);
  L3B2onZ->addCut(threeLepCut);
  L3B2onZ->addCut(twoBjetCut);
  L3B2onZ->addCut(lowHTcut);
  L3B2onZ->addCut(lowMETcut);
  Signature* L2B2SS = new Signature("L2B2SS","");
  L2B2SS->addCut(sameSignCut);
  L2B2SS->addCut(twoLepCut);
  L2B2SS->addCut(twoBjetCut);
  L2B2SS->addCut(lowHTcut);
  L2B2SS->addCut(lowMETcut);

  Signature* L4B2offZHT = new Signature("L4B2offZHT","");
  L4B2offZHT->addCut(dyAoffZcut);
  L4B2offZHT->addCut(fourLepCut);
  L4B2offZHT->addCut(twoBjetCut);
  L4B2offZHT->addCut(highHTcut);
  L4B2offZHT->addCut(lowMETcut);
  Signature* L4B2onZHT = new Signature("L4B2onZHT","");
  L4B2onZHT->addCut(dyAonZcut);
  L4B2onZHT->addCut(fourLepCut);
  L4B2onZHT->addCut(twoBjetCut);
  L4B2onZHT->addCut(highHTcut);
  L4B2onZHT->addCut(lowMETcut);
  Signature* L3B2offZHT = new Signature("L3B2offZHT","");
  L3B2offZHT->addCut(dyAoffZcut);
  L3B2offZHT->addCut(threeLepCut);
  L3B2offZHT->addCut(twoBjetCut);
  L3B2offZHT->addCut(highHTcut);
  L3B2offZHT->addCut(lowMETcut);
  Signature* L3B2onZHT = new Signature("L3B2onZHT","");
  L3B2onZHT->addCut(dyAonZcut);
  L3B2onZHT->addCut(threeLepCut);
  L3B2onZHT->addCut(twoBjetCut);
  L3B2onZHT->addCut(highHTcut);
  L3B2onZHT->addCut(lowMETcut);
  Signature* L2B2SSHT = new Signature("L2B2SSHT","");
  L2B2SSHT->addCut(sameSignCut);
  L2B2SSHT->addCut(twoLepCut);
  L2B2SSHT->addCut(twoBjetCut);
  L2B2SSHT->addCut(highHTcut);
  L2B2SSHT->addCut(lowMETcut);

  Signature* L4B2offZMET = new Signature("L4B2offZMET","");
  L4B2offZMET->addCut(dyAoffZcut);
  L4B2offZMET->addCut(fourLepCut);
  L4B2offZMET->addCut(twoBjetCut);
  L4B2offZMET->addCut(lowHTcut);
  L4B2offZMET->addCut(highMETcut);
  Signature* L4B2onZMET = new Signature("L4B2onZMET","");
  L4B2onZMET->addCut(dyAonZcut);
  L4B2onZMET->addCut(fourLepCut);
  L4B2onZMET->addCut(twoBjetCut);
  L4B2onZMET->addCut(lowHTcut);
  L4B2onZMET->addCut(highMETcut);
  Signature* L3B2offZMET = new Signature("L3B2offZMET","");
  L3B2offZMET->addCut(dyAoffZcut);
  L3B2offZMET->addCut(threeLepCut);
  L3B2offZMET->addCut(twoBjetCut);
  L3B2offZMET->addCut(lowHTcut);
  L3B2offZMET->addCut(highMETcut);
  Signature* L3B2onZMET = new Signature("L3B2onZMET","");
  L3B2onZMET->addCut(dyAonZcut);
  L3B2onZMET->addCut(threeLepCut);
  L3B2onZMET->addCut(twoBjetCut);
  L3B2onZMET->addCut(lowHTcut);
  L3B2onZMET->addCut(highMETcut);
  Signature* L2B2SSMET = new Signature("L2B2SSMET","");
  L2B2SSMET->addCut(sameSignCut);
  L2B2SSMET->addCut(twoLepCut);
  L2B2SSMET->addCut(twoBjetCut);
  L2B2SSMET->addCut(lowHTcut);
  L2B2SSMET->addCut(highMETcut);

  Signature* L4B2offZHTMET = new Signature("L4B2offZHTMET","");
  L4B2offZHTMET->addCut(dyAoffZcut);
  L4B2offZHTMET->addCut(fourLepCut);
  L4B2offZHTMET->addCut(twoBjetCut);
  L4B2offZHTMET->addCut(highHTcut);
  L4B2offZHTMET->addCut(highMETcut);
  Signature* L4B2onZHTMET = new Signature("L4B2onZHTMET","");
  L4B2onZHTMET->addCut(dyAonZcut);
  L4B2onZHTMET->addCut(fourLepCut);
  L4B2onZHTMET->addCut(twoBjetCut);
  L4B2onZHTMET->addCut(highHTcut);
  L4B2onZHTMET->addCut(highMETcut);
  Signature* L3B2offZHTMET = new Signature("L3B2offZHTMET","");
  L3B2offZHTMET->addCut(dyAoffZcut);
  L3B2offZHTMET->addCut(threeLepCut);
  L3B2offZHTMET->addCut(twoBjetCut);
  L3B2offZHTMET->addCut(highHTcut);
  L3B2offZHTMET->addCut(highMETcut);
  Signature* L3B2onZHTMET = new Signature("L3B2onZHTMET","");
  L3B2onZHTMET->addCut(dyAonZcut);
  L3B2onZHTMET->addCut(threeLepCut);
  L3B2onZHTMET->addCut(twoBjetCut);
  L3B2onZHTMET->addCut(highHTcut);
  L3B2onZHTMET->addCut(highMETcut);
  Signature* L2B2SSHTMET = new Signature("L2B2SSHTMET","");
  L2B2SSHTMET->addCut(sameSignCut);
  L2B2SSHTMET->addCut(twoLepCut);
  L2B2SSHTMET->addCut(twoBjetCut);
  L2B2SSHTMET->addCut(highHTcut);
  L2B2SSHTMET->addCut(highMETcut);

  Signature* L4B3offZ = new Signature("L4B3offZ","");
  L4B3offZ->addCut(dyAoffZcut);
  L4B3offZ->addCut(fourLepCut);
  L4B3offZ->addCut(gethreeBjetCut);
  L4B3offZ->addCut(lowHTcut);
  L4B3offZ->addCut(lowMETcut);
  Signature* L4B3onZ = new Signature("L4B3onZ","");
  L4B3onZ->addCut(dyAonZcut);
  L4B3onZ->addCut(fourLepCut);
  L4B3onZ->addCut(gethreeBjetCut);
  L4B3onZ->addCut(lowHTcut);
  L4B3onZ->addCut(lowMETcut);
  Signature* L3B3offZ = new Signature("L3B3offZ","");
  L3B3offZ->addCut(dyAoffZcut);
  L3B3offZ->addCut(threeLepCut);
  L3B3offZ->addCut(gethreeBjetCut);
  L3B3offZ->addCut(lowHTcut);
  L3B3offZ->addCut(lowMETcut);
  Signature* L3B3onZ = new Signature("L3B3onZ","");
  L3B3onZ->addCut(dyAonZcut);
  L3B3onZ->addCut(threeLepCut);
  L3B3onZ->addCut(gethreeBjetCut);
  L3B3onZ->addCut(lowHTcut);
  L3B3onZ->addCut(lowMETcut);
  Signature* L2B3SS = new Signature("L2B3SS","");
  L2B3SS->addCut(sameSignCut);
  L2B3SS->addCut(twoLepCut);
  L2B3SS->addCut(gethreeBjetCut);
  L2B3SS->addCut(lowHTcut);
  L2B3SS->addCut(lowMETcut);

  Signature* L4B3offZHT = new Signature("L4B3offZHT","");
  L4B3offZHT->addCut(dyAoffZcut);
  L4B3offZHT->addCut(fourLepCut);
  L4B3offZHT->addCut(gethreeBjetCut);
  L4B3offZHT->addCut(highHTcut);
  L4B3offZHT->addCut(lowMETcut);
  Signature* L4B3onZHT = new Signature("L4B3onZHT","");
  L4B3onZHT->addCut(dyAonZcut);
  L4B3onZHT->addCut(fourLepCut);
  L4B3onZHT->addCut(gethreeBjetCut);
  L4B3onZHT->addCut(highHTcut);
  L4B3onZHT->addCut(lowMETcut);
  Signature* L3B3offZHT = new Signature("L3B3offZHT","");
  L3B3offZHT->addCut(dyAoffZcut);
  L3B3offZHT->addCut(threeLepCut);
  L3B3offZHT->addCut(gethreeBjetCut);
  L3B3offZHT->addCut(highHTcut);
  L3B3offZHT->addCut(lowMETcut);
  Signature* L3B3onZHT = new Signature("L3B3onZHT","");
  L3B3onZHT->addCut(dyAonZcut);
  L3B3onZHT->addCut(threeLepCut);
  L3B3onZHT->addCut(gethreeBjetCut);
  L3B3onZHT->addCut(highHTcut);
  L3B3onZHT->addCut(lowMETcut);
  Signature* L2B3SSHT = new Signature("L2B3SSHT","");
  L2B3SSHT->addCut(sameSignCut);
  L2B3SSHT->addCut(twoLepCut);
  L2B3SSHT->addCut(gethreeBjetCut);
  L2B3SSHT->addCut(highHTcut);
  L2B3SSHT->addCut(lowMETcut);

  Signature* L4B3offZMET = new Signature("L4B3offZMET","");
  L4B3offZMET->addCut(dyAoffZcut);
  L4B3offZMET->addCut(fourLepCut);
  L4B3offZMET->addCut(gethreeBjetCut);
  L4B3offZMET->addCut(lowHTcut);
  L4B3offZMET->addCut(highMETcut);
  Signature* L4B3onZMET = new Signature("L4B3onZMET","");
  L4B3onZMET->addCut(dyAonZcut);
  L4B3onZMET->addCut(fourLepCut);
  L4B3onZMET->addCut(gethreeBjetCut);
  L4B3onZMET->addCut(lowHTcut);
  L4B3onZMET->addCut(highMETcut);
  Signature* L3B3offZMET = new Signature("L3B3offZMET","");
  L3B3offZMET->addCut(dyAoffZcut);
  L3B3offZMET->addCut(threeLepCut);
  L3B3offZMET->addCut(gethreeBjetCut);
  L3B3offZMET->addCut(lowHTcut);
  L3B3offZMET->addCut(highMETcut);
  Signature* L3B3onZMET = new Signature("L3B3onZMET","");
  L3B3onZMET->addCut(dyAonZcut);
  L3B3onZMET->addCut(threeLepCut);
  L3B3onZMET->addCut(gethreeBjetCut);
  L3B3onZMET->addCut(lowHTcut);
  L3B3onZMET->addCut(highMETcut);
  Signature* L2B3SSMET = new Signature("L2B3SSMET","");
  L2B3SSMET->addCut(sameSignCut);
  L2B3SSMET->addCut(twoLepCut);
  L2B3SSMET->addCut(gethreeBjetCut);
  L2B3SSMET->addCut(lowHTcut);
  L2B3SSMET->addCut(highMETcut);

  Signature* L4B3offZHTMET = new Signature("L4B3offZHTMET","");
  L4B3offZHTMET->addCut(dyAoffZcut);
  L4B3offZHTMET->addCut(fourLepCut);
  L4B3offZHTMET->addCut(gethreeBjetCut);
  L4B3offZHTMET->addCut(highHTcut);
  L4B3offZHTMET->addCut(highMETcut);
  Signature* L4B3onZHTMET = new Signature("L4B3onZHTMET","");
  L4B3onZHTMET->addCut(dyAonZcut);
  L4B3onZHTMET->addCut(fourLepCut);
  L4B3onZHTMET->addCut(gethreeBjetCut);
  L4B3onZHTMET->addCut(highHTcut);
  L4B3onZHTMET->addCut(highMETcut);
  Signature* L3B3offZHTMET = new Signature("L3B3offZHTMET","");
  L3B3offZHTMET->addCut(dyAoffZcut);
  L3B3offZHTMET->addCut(threeLepCut);
  L3B3offZHTMET->addCut(gethreeBjetCut);
  L3B3offZHTMET->addCut(highHTcut);
  L3B3offZHTMET->addCut(highMETcut);
  Signature* L3B3onZHTMET = new Signature("L3B3onZHTMET","");
  L3B3onZHTMET->addCut(dyAonZcut);
  L3B3onZHTMET->addCut(threeLepCut);
  L3B3onZHTMET->addCut(gethreeBjetCut);
  L3B3onZHTMET->addCut(highHTcut);
  L3B3onZHTMET->addCut(highMETcut);
  Signature* L2B3SSHTMET = new Signature("L2B3SSHTMET","");
  L2B3SSHTMET->addCut(sameSignCut);
  L2B3SSHTMET->addCut(twoLepCut);
  L2B3SSHTMET->addCut(gethreeBjetCut);
  L2B3SSHTMET->addCut(highHTcut);
  L2B3SSHTMET->addCut(highMETcut);

  /////////////////////////////
  //add Signatures to handler//
  handler->addSignature(L4B0offZ);
  handler->addSignature(L4B0onZ);
  handler->addSignature(L3B0offZ);
  handler->addSignature(L3B0onZ);
  handler->addSignature(L2B0SS);
  handler->addSignature(L4B0offZHT);
  handler->addSignature(L4B0onZHT);
  handler->addSignature(L3B0offZHT);
  handler->addSignature(L3B0onZHT);
  handler->addSignature(L2B0SSHT);
  handler->addSignature(L4B0offZMET);
  handler->addSignature(L4B0onZMET);
  handler->addSignature(L3B0offZMET);
  handler->addSignature(L3B0onZMET);
  handler->addSignature(L2B0SSMET);
  handler->addSignature(L4B0offZHTMET);
  handler->addSignature(L4B0onZHTMET);
  handler->addSignature(L3B0offZHTMET);
  handler->addSignature(L3B0onZHTMET);
  handler->addSignature(L2B0SSHTMET);

  handler->addSignature(L4B1offZ);
  handler->addSignature(L4B1onZ);
  handler->addSignature(L3B1offZ);
  handler->addSignature(L3B1onZ);
  handler->addSignature(L2B1SS);
  handler->addSignature(L4B1offZHT);
  handler->addSignature(L4B1onZHT);
  handler->addSignature(L3B1offZHT);
  handler->addSignature(L3B1onZHT);
  handler->addSignature(L2B1SSHT);
  handler->addSignature(L4B1offZMET);
  handler->addSignature(L4B1onZMET);
  handler->addSignature(L3B1offZMET);
  handler->addSignature(L3B1onZMET);
  handler->addSignature(L2B1SSMET);
  handler->addSignature(L4B1offZHTMET);
  handler->addSignature(L4B1onZHTMET);
  handler->addSignature(L3B1offZHTMET);
  handler->addSignature(L3B1onZHTMET);
  handler->addSignature(L2B1SSHTMET);

  handler->addSignature(L4B2offZ);
  handler->addSignature(L4B2onZ);
  handler->addSignature(L3B2offZ);
  handler->addSignature(L3B2onZ);
  handler->addSignature(L2B2SS);
  handler->addSignature(L4B2offZHT);
  handler->addSignature(L4B2onZHT);
  handler->addSignature(L3B2offZHT);
  handler->addSignature(L3B2onZHT);
  handler->addSignature(L2B2SSHT);
  handler->addSignature(L4B2offZMET);
  handler->addSignature(L4B2onZMET);
  handler->addSignature(L3B2offZMET);
  handler->addSignature(L3B2onZMET);
  handler->addSignature(L2B2SSMET);
  handler->addSignature(L4B2offZHTMET);
  handler->addSignature(L4B2onZHTMET);
  handler->addSignature(L3B2offZHTMET);
  handler->addSignature(L3B2onZHTMET);
  handler->addSignature(L2B2SSHTMET);

  handler->addSignature(L4B3offZ);
  handler->addSignature(L4B3onZ);
  handler->addSignature(L3B3offZ);
  handler->addSignature(L3B3onZ);
  handler->addSignature(L2B3SS);
  handler->addSignature(L4B3offZHT);
  handler->addSignature(L4B3onZHT);
  handler->addSignature(L3B3offZHT);
  handler->addSignature(L3B3onZHT);
  handler->addSignature(L2B3SSHT);
  handler->addSignature(L4B3offZMET);
  handler->addSignature(L4B3onZMET);
  handler->addSignature(L3B3offZMET);
  handler->addSignature(L3B3onZMET);
  handler->addSignature(L2B3SSMET);
  handler->addSignature(L4B3offZHTMET);
  handler->addSignature(L4B3onZHTMET);
  handler->addSignature(L3B3offZHTMET);
  handler->addSignature(L3B3onZHTMET);
  handler->addSignature(L2B3SSHTMET);
}
//--------------------------------
//--------------------------------
vector<int> getSingleMuonTriggers()
{
  vector<int> m_singleMuTriggerList;
  m_singleMuTriggerList.push_back(126);//("HLT_Mu5_v18"); //126
 m_singleMuTriggerList.push_back(127);//("HLT_Mu8_v16"); //127
 m_singleMuTriggerList.push_back(128);//("HLT_Mu12_v16"); //128
 m_singleMuTriggerList.push_back(129);//("HLT_Mu17_v3"); //129
 m_singleMuTriggerList.push_back(131);//("HLT_Mu15_eta2p1_v3"); //131
 m_singleMuTriggerList.push_back(132);//("HLT_Mu24_eta2p1_v3"); //132
 m_singleMuTriggerList.push_back(133);//("HLT_Mu30_eta2p1_v3"); //133
 m_singleMuTriggerList.push_back(134);//("HLT_Mu40_eta2p1_v9"); //134
 m_singleMuTriggerList.push_back(135);//("HLT_Mu50_eta2p1_v6"); //135
 m_singleMuTriggerList.push_back(139);//("HLT_IsoMu20_eta2p1_v3"); //139
 m_singleMuTriggerList.push_back(140);//("HLT_IsoMu24_eta2p1_v11"); //140
 m_singleMuTriggerList.push_back(141);//("HLT_IsoMu30_eta2p1_v11"); //141
 m_singleMuTriggerList.push_back(142);//("HLT_IsoMu34_eta2p1_v9"); //142
 m_singleMuTriggerList.push_back(143);//("HLT_IsoMu40_eta2p1_v6"); //143

 // Added 20 th April

 m_singleMuTriggerList.push_back(567);//("HLT_IsoMu20_eta2p1_v4"); //567
  m_singleMuTriggerList.push_back(568);//("HLT_IsoMu24_eta2p1_v12"); //568
  m_singleMuTriggerList.push_back(569);//("HLT_IsoMu30_eta2p1_v12"); //569
  m_singleMuTriggerList.push_back(570);//("HLT_IsoMu34_eta2p1_v10"); //570
  m_singleMuTriggerList.push_back(571);//("HLT_IsoMu40_eta2p1_v7"); //571

 // added on 30th April 
  // added on 19th May
 m_singleMuTriggerList.push_back(1129);//m_known_triggers.push_back("HLT_Mu24_v14"); //1129
 m_singleMuTriggerList.push_back(1130);//m_known_triggers.push_back("HLT_Mu30_v14"); //1130
 m_singleMuTriggerList.push_back(1131);//m_known_triggers.push_back("HLT_Mu40_v12"); //1131
 m_singleMuTriggerList.push_back(1135);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v5"); //1135
 m_singleMuTriggerList.push_back(1136);//m_known_triggers.push_back("HLT_IsoMu24_v15"); //1136
 m_singleMuTriggerList.push_back(1137);//m_known_triggers.push_back("HLT_IsoMu24_eta2p1_v13"); //1137
 m_singleMuTriggerList.push_back(1138);//m_known_triggers.push_back("HLT_IsoMu30_v9"); //1138
 m_singleMuTriggerList.push_back(1139);//m_known_triggers.push_back("HLT_IsoMu30_eta2p1_v13"); //1139
m_singleMuTriggerList.push_back(1140);// m_known_triggers.push_back("HLT_IsoMu34_eta2p1_v11"); //1140
 m_singleMuTriggerList.push_back(1141);//_known_triggers.push_back("HLT_IsoMu40_eta2p1_v8"); //1141
 //added on Sept 4 2012
 m_singleMuTriggerList.push_back(1468);//m_known_triggers.push_back("HLT_Mu5_v20"); //1468
 m_singleMuTriggerList.push_back(1469);//m_known_triggers.push_back("HLT_Mu8_v18"); //1469
 m_singleMuTriggerList.push_back(1470);//m_known_triggers.push_back("HLT_Mu12_v18"); //1470
 m_singleMuTriggerList.push_back(1471);//m_known_triggers.push_back("HLT_Mu17_v5"); //1471
 m_singleMuTriggerList.push_back(1475);//m_known_triggers.push_back("HLT_Mu24_v16"); //1475
 m_singleMuTriggerList.push_back(1477);//m_known_triggers.push_back("HLT_Mu30_v16"); //1477
 m_singleMuTriggerList.push_back(1479);//m_known_triggers.push_back("HLT_Mu40_v14"); //1479
m_singleMuTriggerList.push_back(1486);//m_known_triggers.push_back("HLT_IsoMu24_v17"); //1486
m_singleMuTriggerList.push_back(1488);//m_known_triggers.push_back("HLT_IsoMu30_v11"); //1488
 m_singleMuTriggerList.push_back(1877);//m_known_triggers.push_back("HLT_Mu5_v19"); //1877
  m_singleMuTriggerList.push_back(1878);//m_known_triggers.push_back("HLT_Mu8_v17"); //1878
  m_singleMuTriggerList.push_back(1879);//m_known_triggers.push_back("HLT_Mu12_v17"); //1879
  m_singleMuTriggerList.push_back(1880);//m_known_triggers.push_back("HLT_Mu17_v4"); //1880
  m_singleMuTriggerList.push_back(1884);//m_known_triggers.push_back("HLT_Mu24_v15"); //1884
m_singleMuTriggerList.push_back(1886);//m_known_triggers.push_back("HLT_Mu30_v15"); //1886
m_singleMuTriggerList.push_back(1888);//m_known_triggers.push_back("HLT_Mu40_v13"); //1888
 m_singleMuTriggerList.push_back(1894);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v6"); //1894
 m_singleMuTriggerList.push_back(1895);//m_known_triggers.push_back("HLT_IsoMu24_v16"); //1895
m_singleMuTriggerList.push_back(1897);//m_known_triggers.push_back("HLT_IsoMu30_v10"); //1897
m_singleMuTriggerList.push_back(1900);// m_known_triggers.push_back("HLT_IsoMu40_eta2p1_v9"); //1900
 m_singleMuTriggerList.push_back(1485);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v7"); //1485
 m_singleMuTriggerList.push_back(1487);//m_singleMuTriggerList.push_back();//m_known_triggers.push_back("HLT_IsoMu24_eta2p1_v15"); //1487
 m_singleMuTriggerList.push_back(1489);//m_known_triggers.push_back("HLT_IsoMu30_eta2p1_v15"); //1489
  m_singleMuTriggerList.push_back(1490);//m_known_triggers.push_back("HLT_IsoMu34_eta2p1_v13"); //1490
  m_singleMuTriggerList.push_back(1491);//m_known_triggers.push_back("HLT_IsoMu40_eta2p1_v10"); //1491
 m_singleMuTriggerList.push_back(1883);//m_known_triggers.push_back("HLT_Mu15_eta2p1_v4"); //1883
 m_singleMuTriggerList.push_back(1885);//m_known_triggers.push_back("HLT_Mu24_eta2p1_v4"); //1885
 m_singleMuTriggerList.push_back(1887);//m_known_triggers.push_back("HLT_Mu30_eta2p1_v4"); //1887
 m_singleMuTriggerList.push_back(1889);//m_known_triggers.push_back("HLT_Mu40_eta2p1_v10"); //1889
  m_singleMuTriggerList.push_back(1890);//m_known_triggers.push_back("HLT_Mu50_eta2p1_v7"); //1890
 m_singleMuTriggerList.push_back(1894);//m_known_triggers.push_back("HLT_IsoMu20_eta2p1_v6"); //1894
m_singleMuTriggerList.push_back(1896);//m_known_triggers.push_back("HLT_IsoMu24_eta2p1_v14"); //1896
 m_singleMuTriggerList.push_back(1898);//m_known_triggers.push_back("HLT_IsoMu30_eta2p1_v14"); //1898
  m_singleMuTriggerList.push_back(1899);//m_known_triggers.push_back("HLT_IsoMu34_eta2p1_v12"); //1899
  m_singleMuTriggerList.push_back(1900);//m_known_triggers.push_back("HLT_IsoMu40_eta2p1_v9"); //1900

  return m_singleMuTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getSingleElectronTriggers()
{
  vector<int> m_singleElTriggerList;
 m_singleElTriggerList.push_back(237);//("HLT_Ele8_CaloIdT_TrkIdVL_v2"); //237
m_singleElTriggerList.push_back(239); //m_known_triggers.push_back("HLT_Ele8_CaloIdL_CaloIsoVL_v14"); //239
 m_singleElTriggerList.push_back(240);//("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v12"); //240
 m_singleElTriggerList.push_back(241);//("HLT_Ele17_CaloIdL_CaloIsoVL_v14"); //241
 m_singleElTriggerList.push_back(242);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v3"); //242
 m_singleElTriggerList.push_back(246);//("HLT_Ele22_CaloIdL_CaloIsoVL_v3"); //246
 m_singleElTriggerList.push_back(247);//("HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //247
 m_singleElTriggerList.push_back(253);//("HLT_Ele30_CaloIdVT_TrkIdT_v3"); //253
 m_singleElTriggerList.push_back(254);//("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //254
 m_singleElTriggerList.push_back(256);//("HLT_Ele65_CaloIdVT_TrkIdT_v11"); //256
 m_singleElTriggerList.push_back(257);//("HLT_Ele80_CaloIdVT_TrkIdT_v8"); //257
 m_singleElTriggerList.push_back(258);//("HLT_Ele100_CaloIdVT_TrkIdT_v8"); //258

 // Added on 20th April
 m_singleElTriggerList.push_back(619);//("HLT_Ele8_CaloIdT_TrkIdVL_v3"); //619
 m_singleElTriggerList.push_back(621);//("HLT_Ele8_CaloIdL_CaloIsoVL_v15"); //621
 m_singleElTriggerList.push_back(622);//("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v13"); //622
 m_singleElTriggerList.push_back(623);//("HLT_Ele17_CaloIdL_CaloIsoVL_v15"); //623
 m_singleElTriggerList.push_back(624);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //624
m_singleElTriggerList.push_back(628);//("HLT_Ele22_CaloIdL_CaloIsoVL_v4"); //628
 m_singleElTriggerList.push_back(629);//("HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //629
 m_singleElTriggerList.push_back(635);//("HLT_Ele30_CaloIdVT_TrkIdT_v4"); //635
 m_singleElTriggerList.push_back(636);//("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //636
 m_singleElTriggerList.push_back(638);//("HLT_Ele65_CaloIdVT_TrkIdT_v12"); //638
 m_singleElTriggerList.push_back(639);//("HLT_Ele80_CaloIdVT_TrkIdT_v9"); //639
 m_singleElTriggerList.push_back(640);//("HLT_Ele100_CaloIdVT_TrkIdT_v9"); //640
m_singleElTriggerList.push_back(908); //("HLT_Ele8_CaloIdT_TrkIdVL_v4"); //908
 m_singleElTriggerList.push_back(910);//("HLT_Ele8_CaloIdL_CaloIsoVL_v16"); //910
 m_singleElTriggerList.push_back(911);//("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v14"); //911
 m_singleElTriggerList.push_back(912);//("HLT_Ele17_CaloIdL_CaloIsoVL_v16"); //912
m_singleElTriggerList.push_back(913); //("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //913
 m_singleElTriggerList.push_back(917);//("HLT_Ele22_CaloIdL_CaloIsoVL_v5"); //917
 m_singleElTriggerList.push_back(924);//("HLT_Ele30_CaloIdVT_TrkIdT_v5"); //924
 m_singleElTriggerList.push_back(925);//("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v10"); //925
 m_singleElTriggerList.push_back(927);//("HLT_Ele65_CaloIdVT_TrkIdT_v13"); //927
 m_singleElTriggerList.push_back(928);//("HLT_Ele80_CaloIdVT_TrkIdT_v10"); //928
 m_singleElTriggerList.push_back(929);//("HLT_Ele100_CaloIdVT_TrkIdT_v10"); //929
 
 // added on 19 th may
  m_singleElTriggerList.push_back(1162);//m_known_triggers.push_back("HLT_Ele80_CaloIdVT_GsfTrkIdT_v1"); //1162
  m_singleElTriggerList.push_back(1163);//m_known_triggers.push_back("HLT_Ele90_CaloIdVT_GsfTrkIdT_v1"); //1163

  // added on Sept 4
 m_singleElTriggerList.push_back(1585);//m_known_triggers.push_back("HLT_Ele8_CaloIdT_TrkIdVL_v5"); //1585
m_singleElTriggerList.push_back(1588);//m_known_triggers.push_back("HLT_Ele8_CaloIdL_CaloIsoVL_v17"); //1588
 m_singleElTriggerList.push_back(1590);//m_known_triggers.push_back("HLT_Ele17_CaloIdL_CaloIsoVL_v17"); //1590
  m_singleElTriggerList.push_back(1591);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //1591
 m_singleElTriggerList.push_back(1595);//m_known_triggers.push_back("HLT_Ele22_CaloIdL_CaloIsoVL_v6"); //1595
 m_singleElTriggerList.push_back(1596);//m_known_triggers.push_back("HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v11"); //1596
m_singleElTriggerList.push_back(1605);//m_known_triggers.push_back("HLT_Ele30_CaloIdVT_TrkIdT_v6"); //1605
 m_singleElTriggerList.push_back(1606);//m_known_triggers.push_back("HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v11"); //1606
 m_singleElTriggerList.push_back(1608);//m_known_triggers.push_back("HLT_Ele80_CaloIdVT_GsfTrkIdT_v2"); //1608
  m_singleElTriggerList.push_back(1609);//m_known_triggers.push_back("HLT_Ele90_CaloIdVT_GsfTrkIdT_v2"); //1609


  return m_singleElTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getDoubleMuonTriggers()
{
  vector<int> m_doubleMuTriggerList;
  /*
 m_doubleMuTriggerList.push_back(174);//("HLT_Mu13_Mu8_v16"); //174
 m_doubleMuTriggerList.push_back(175);//("HLT_Mu17_Mu8_v16"); //175
 m_doubleMuTriggerList.push_back(176);//("HLT_Mu17_TkMu8_v9"); //176
 m_doubleMuTriggerList.push_back(177);//("HLT_Mu22_TkMu8_v4"); //177
 m_doubleMuTriggerList.push_back(178);//("HLT_Mu22_TkMu22_v4"); //178
 // added on 30th April 
 //added on 19th May 2012
 m_doubleMuTriggerList.push_back(1144);// m_known_triggers.push_back("HLT_Mu13_Mu8_v17"); //1144
 m_doubleMuTriggerList.push_back(1145);// m_known_triggers.push_back("HLT_Mu17_Mu8_v17"); //1145
  m_doubleMuTriggerList.push_back(1146);//m_known_triggers.push_back("HLT_Mu17_TkMu8_v10"); //1146
  m_doubleMuTriggerList.push_back(1147);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v5"); //1147
  m_doubleMuTriggerList.push_back(1148);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v5"); //1148
  // added on 26th May
  m_doubleMuTriggerList.push_back(1248);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v6"); //1248
  m_doubleMuTriggerList.push_back(1249);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v6"); //1249

  m_doubleMuTriggerList.push_back(1334);//m_known_triggers.push_back("HLT_Mu13_Mu8_v18"); //1334
  m_doubleMuTriggerList.push_back(1335);// m_known_triggers.push_back("HLT_Mu17_Mu8_v18"); //1335
  m_doubleMuTriggerList.push_back(1336);// m_known_triggers.push_back("HLT_Mu17_TkMu8_v11"); //1336

  m_doubleMuTriggerList.push_back(1522);
  m_doubleMuTriggerList.push_back(1523);
  m_doubleMuTriggerList.push_back(1524);
  m_doubleMuTriggerList.push_back(1525);
  m_doubleMuTriggerList.push_back(1526);

  m_doubleMuTriggerList.push_back(1928);
  m_doubleMuTriggerList.push_back(1929);
  m_doubleMuTriggerList.push_back(1930);
  m_doubleMuTriggerList.push_back(1931);
  m_doubleMuTriggerList.push_back(1932);

      m_doubleMuTriggerList.push_back(2257);//m_known_triggers.push_back("HLT_Mu13_Mu8_v22"); //2257
      m_doubleMuTriggerList.push_back(2258);//m_known_triggers.push_back("HLT_Mu17_Mu8_v22"); //2258
      m_doubleMuTriggerList.push_back(2259);//m_known_triggers.push_back("HLT_Mu17_TkMu8_v14"); //2259
      m_doubleMuTriggerList.push_back(2260);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v9"); //2260
      m_doubleMuTriggerList.push_back(2261);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v9"); //2261
  */
  m_doubleMuTriggerList.push_back(175);//("HLT_Mu17_Mu8_v16"); //175
  m_doubleMuTriggerList.push_back(1145);// m_known_triggers.push_back("HLT_Mu17_Mu8_v17"); //1145
  m_doubleMuTriggerList.push_back(1335);// m_known_triggers.push_back("HLT_Mu17_Mu8_v18"); //1335
  m_doubleMuTriggerList.push_back(1929);//m_known_triggers.push_back("HLT_Mu17_Mu8_v19"); //1929
  m_doubleMuTriggerList.push_back(1523);//m_known_triggers.push_back("HLT_Mu17_Mu8_v21"); //1523
  m_doubleMuTriggerList.push_back(2258);// m_known_triggers.push_back("HLT_Mu17_Mu8_v22"); //2258 
  return m_doubleMuTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getDoubleElectronTriggers()
{
  vector<int> m_doubleElTriggerList;
  /*
  m_doubleElTriggerList.push_back(243);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v15"); //243
  m_doubleElTriggerList.push_back(248);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v4"); //248
  m_doubleElTriggerList.push_back(259);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v9"); //259
  m_doubleElTriggerList.push_back(260);//("HLT_DoubleEle33_CaloIdL_v11"); //260
  m_doubleElTriggerList.push_back(261);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v3"); //261
  m_doubleElTriggerList.push_back(262);//("HLT_DoubleEle33_CaloIdT_v7"); //262

  //Added 20th April
  m_doubleElTriggerList.push_back(625);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v16"); //625
  m_doubleElTriggerList.push_back(630);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v5"); //630
   m_doubleElTriggerList.push_back(641);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v10"); //641
 m_doubleElTriggerList.push_back(642);// m_known_triggers.push_back("HLT_DoubleEle33_CaloIdL_v12"); //642
  m_doubleElTriggerList.push_back(643);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v4"); //643
  m_doubleElTriggerList.push_back(644);//("HLT_DoubleEle33_CaloIdT_v8"); //644
  // added on 30th April 
  m_doubleElTriggerList.push_back(914);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17"); //914
 m_doubleElTriggerList.push_back(919);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v6"); //919
  m_doubleElTriggerList.push_back(930);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v11"); //930
  m_doubleElTriggerList.push_back(931);//("HLT_DoubleEle33_CaloIdL_v13"); //931
  m_doubleElTriggerList.push_back(932);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v5"); //932
  m_doubleElTriggerList.push_back(933);//("HLT_DoubleEle33_CaloIdT_v9"); //933
  // added on 19 May
  m_doubleElTriggerList.push_back(1164);// m_known_triggers.push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v6"); //1164
  
  m_doubleElTriggerList.push_back(1592);
  m_doubleElTriggerList.push_back(1597);
  m_doubleElTriggerList.push_back(1610);
  m_doubleElTriggerList.push_back(1611);
  m_doubleElTriggerList.push_back(1612);
  m_doubleElTriggerList.push_back(1613);
  m_doubleElTriggerList.push_back(2225);//m_known_triggers.push_back("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v8"); //2225
  m_doubleElTriggerList.push_back(2262);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v19"); //2262 
  */
  m_doubleElTriggerList.push_back(243);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v15"); //243
  m_doubleElTriggerList.push_back(625);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v16"); //625
  m_doubleElTriggerList.push_back(914);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17"); //914
  m_doubleElTriggerList.push_back(1592);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v18");//1592
  m_doubleElTriggerList.push_back(2262);//m_known_triggers.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v19"); //2262

 return m_doubleElTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getMuonElectronTriggers()
{
  vector<int> m_muElTriggerList;
  /*
 m_muElTriggerList.push_back(277);//m_known_triggers.push_back("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v3"); //277
 m_muElTriggerList.push_back(278);//m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //278
 m_muElTriggerList.push_back(310);//m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //310 
 m_muElTriggerList.push_back(318);//("HLT_Mu30_Ele30_CaloIdL_v3"); //318

// Added 20th April
  m_muElTriggerList.push_back(659);//("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v4"); //659
  m_muElTriggerList.push_back(660);//("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //660
  m_muElTriggerList.push_back(691);//("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //691
 m_muElTriggerList.push_back(699);// m_muElTriggerListpush_back(310);//("HLT_Mu30_Ele30_CaloIdL_v4"); //699

 // added on 30th April 
m_muElTriggerList.push_back(943); //("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v5"); //943
m_muElTriggerList.push_back(944); //("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //944
m_muElTriggerList.push_back(971); //("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //971
m_muElTriggerList.push_back(972); //("HLT_Mu30_Ele30_CaloIdL_v5"); //972

// added on 19 th may
 m_muElTriggerList.push_back(1174); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1174
 m_muElTriggerList.push_back(1195); //m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1195
 m_muElTriggerList.push_back(1196); //m_known_triggers.push_back("HLT_Mu30_Ele30_CaloIdL_v6"); //1196

 m_muElTriggerList.push_back(1629);
 m_muElTriggerList.push_back(1630);
 m_muElTriggerList.push_back(1653);
 m_muElTriggerList.push_back(1661);

 m_muElTriggerList.push_back(1967);
 m_muElTriggerList.push_back(1968);
 m_muElTriggerList.push_back(1989);
 m_muElTriggerList.push_back(1997);

  */
  m_muElTriggerList.push_back(278);//m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //278
  m_muElTriggerList.push_back(310);//m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //310
  m_muElTriggerList.push_back(660);//("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //660
  m_muElTriggerList.push_back(691);//("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //691
  m_muElTriggerList.push_back(944); //("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //944
  m_muElTriggerList.push_back(971); //("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //971
  m_muElTriggerList.push_back(1174); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1174
  m_muElTriggerList.push_back(1195); //m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1195
  m_muElTriggerList.push_back(1968); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //1968
  m_muElTriggerList.push_back(1989); // m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"); //1989
  m_muElTriggerList.push_back(1630); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //1630
  m_muElTriggerList.push_back(1653); //m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"); //1653

  return m_muElTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getHTTriggers()
{
  vector<int> m_HTTriggerList;
  //m_known_triggers.push_back("HLT_HT200_v1"); //64
  m_HTTriggerList.push_back(67);//m_known_triggers.push_back("HLT_HT250_v1"); //67
  m_HTTriggerList.push_back(74);//m_known_triggers.push_back("HLT_HT300_v1"); //74
  m_HTTriggerList.push_back(79);//m_known_triggers.push_back("HLT_HT350_v1"); //79
  m_HTTriggerList.push_back(82);//m_known_triggers.push_back("HLT_HT400_v1"); //82
  m_HTTriggerList.push_back(86);//m_known_triggers.push_back("HLT_HT450_v1"); //86
  m_HTTriggerList.push_back(87);//m_known_triggers.push_back("HLT_HT500_v1"); //87
  m_HTTriggerList.push_back(88);//m_known_triggers.push_back("HLT_HT550_v1"); //88
  m_HTTriggerList.push_back(89);//m_known_triggers.push_back("HLT_HT650_v1"); //89
  m_HTTriggerList.push_back(93);// m_known_triggers.push_back("HLT_PFHT350_v3"); //93
  m_HTTriggerList.push_back(94);//m_known_triggers.push_back("HLT_PFHT650_v5"); //94
  m_HTTriggerList.push_back(96);//m_known_triggers.push_back("HLT_PFHT700_v3"); //96
  m_HTTriggerList.push_back(97);//m_known_triggers.push_back("HLT_PFHT750_v3"); //97
  // added 20th April
  m_HTTriggerList.push_back(508);//m_known_triggers.push_back("HLT_HT200_v2"); //508
  m_HTTriggerList.push_back(511);//m_known_triggers.push_back("HLT_HT250_v2"); //511
  m_HTTriggerList.push_back(518);//m_known_triggers.push_back("HLT_HT300_v2"); //518
  m_HTTriggerList.push_back(523);//m_known_triggers.push_back("HLT_HT350_v2"); //523
  m_HTTriggerList.push_back(526);//m_known_triggers.push_back("HLT_HT400_v2"); //526
  m_HTTriggerList.push_back(530);//m_known_triggers.push_back("HLT_HT450_v2"); //530
  m_HTTriggerList.push_back(531);//m_known_triggers.push_back("HLT_HT500_v2"); //531
  m_HTTriggerList.push_back(532);//m_known_triggers.push_back("HLT_HT550_v2"); //532
  m_HTTriggerList.push_back(533);//m_known_triggers.push_back("HLT_HT650_v2"); //533
  m_HTTriggerList.push_back(537);// m_known_triggers.push_back("HLT_PFHT350_v4"); //537
  m_HTTriggerList.push_back(538);//m_known_triggers.push_back("HLT_PFHT650_v6"); //538
  m_HTTriggerList.push_back(540);//m_known_triggers.push_back("HLT_PFHT700_v4"); //540
  m_HTTriggerList.push_back(541);//m_known_triggers.push_back("HLT_PFHT750_v4"); //541
  m_HTTriggerList.push_back(842);//m_known_triggers.push_back("HLT_PFHT350_v5"); //842
  m_HTTriggerList.push_back(843);//m_known_triggers.push_back("HLT_PFHT650_v7"); //843
  m_HTTriggerList.push_back(845);//m_known_triggers.push_back("HLT_PFHT700_v5"); //845
  m_HTTriggerList.push_back(846);//m_known_triggers.push_back("HLT_PFHT750_v5"); //846
  // added on 19 May
  m_HTTriggerList.push_back(1086);//m_known_triggers.push_back("HLT_HT200_v3"); //1086
  m_HTTriggerList.push_back(1089);//m_known_triggers.push_back("HLT_HT250_v3"); //1089
  m_HTTriggerList.push_back(1092);//m_known_triggers.push_back("HLT_HT300_v3"); //1092
  m_HTTriggerList.push_back(1097);// m_known_triggers.push_back("HLT_HT350_v3"); //1097
  m_HTTriggerList.push_back(1100);//m_known_triggers.push_back("HLT_HT400_v3"); //1100
  m_HTTriggerList.push_back(1104);//m_known_triggers.push_back("HLT_HT450_v3"); //1104
  m_HTTriggerList.push_back(1105);//m_known_triggers.push_back("HLT_HT500_v3"); //1105
  m_HTTriggerList.push_back(1106);//m_known_triggers.push_back("HLT_HT550_v3"); //1106
  m_HTTriggerList.push_back(1107);//m_known_triggers.push_back("HLT_HT650_v3"); //1107
  m_HTTriggerList.push_back(1110);//m_known_triggers.push_back("HLT_HT750_v3"); //1110
  m_HTTriggerList.push_back(1111);//m_known_triggers.push_back("HLT_PFHT350_v6"); //1111
  m_HTTriggerList.push_back(1112);//m_known_triggers.push_back("HLT_PFHT650_v8"); //1112
  m_HTTriggerList.push_back(1114);//m_known_triggers.push_back("HLT_PFHT700_v6"); //1114
  m_HTTriggerList.push_back(1115);//m_known_triggers.push_back("HLT_PFHT750_v6"); //1115
  //added on july 05
  m_HTTriggerList.push_back(1307);//m_known_triggers.push_back("HLT_HT250_v4");
  m_HTTriggerList.push_back(1310);// m_known_triggers.push_back("HLT_HT300_v4");
  //m_HTTriggerList.push_back(1310);//m_known_triggers.push_back("HLT_HT300_v4");
  m_HTTriggerList.push_back(1315);//m_known_triggers.push_back("HLT_HT350_v4");
  m_HTTriggerList.push_back(1318);// m_known_triggers.push_back("HLT_HT400_v4");
  m_HTTriggerList.push_back(1322);// m_known_triggers.push_back("HLT_HT450_v4"); //1322
  m_HTTriggerList.push_back(1323);//  m_known_triggers.push_back("HLT_HT500_v4"); //1323
  m_HTTriggerList.push_back(1324);//  m_known_triggers.push_back("HLT_HT550_v4"); //1324
  m_HTTriggerList.push_back(1325);//  m_known_triggers.push_back("HLT_HT650_v4"); //1325
  m_HTTriggerList.push_back(1328);// m_known_triggers.push_back("HLT_HT750_v4"); //1328
  m_HTTriggerList.push_back(1329);//  m_known_triggers.push_back("HLT_PFHT350_v7"); //1329
  m_HTTriggerList.push_back(1330);//  m_known_triggers.push_back("HLT_PFHT650_v9"); //1330
  return m_HTTriggerList;
}
//--------------------------------
//--------------------------------
void addRPVSignatures(SignatureHandler* handler)
{
  SignatureCutNElectron* zeroElectronCut = new SignatureCutNElectron(0,0);
  SignatureCutNElectron* oneElectronCut = new SignatureCutNElectron(1,1);
  SignatureCutNElectron* twoElectronCut = new SignatureCutNElectron(2,2);
  SignatureCutNElectron* threeElectronCut = new SignatureCutNElectron(3,3);
  SignatureCutNElectron* fourElectronCut = new SignatureCutNElectron(4,4);
  SignatureCutNElectron* gezeroElectronCut = new SignatureCutNElectron(0,-1);
  SignatureCutNElectron* geoneElectronCut = new SignatureCutNElectron(1,-1);
  SignatureCutNElectron* getwoElectronCut = new SignatureCutNElectron(2,-1);
  SignatureCutNElectron* gethreeElectronCut = new SignatureCutNElectron(3,-1);
  SignatureCutNElectron* gefourElectronCut = new SignatureCutNElectron(4,-1);

  SignatureCutNMuon* zeroMuonCut = new SignatureCutNMuon(0,0);
  SignatureCutNMuon* oneMuonCut = new SignatureCutNMuon(1,1);
  SignatureCutNMuon* twoMuonCut = new SignatureCutNMuon(2,2);
  SignatureCutNMuon* threeMuonCut = new SignatureCutNMuon(3,3);
  SignatureCutNMuon* fourMuonCut = new SignatureCutNMuon(4,4);
  SignatureCutNMuon* gezeroMuonCut = new SignatureCutNMuon(0,-1);
  SignatureCutNMuon* geoneMuonCut = new SignatureCutNMuon(1,-1);
  SignatureCutNMuon* getwoMuonCut = new SignatureCutNMuon(2,-1);
  SignatureCutNMuon* gethreeMuonCut = new SignatureCutNMuon(3,-1);
  SignatureCutNMuon* gefourMuonCut = new SignatureCutNMuon(4,-1);

  SignatureCutN* zeroTauCut = new SignatureCutN("goodTaus",0,0);
  SignatureCutN* oneTauCut = new SignatureCutN("goodTaus",1,1);
  SignatureCutN* twoTauCut = new SignatureCutN("goodTaus",2,2);
  SignatureCutN* gezeroTauCut = new SignatureCutN("goodTaus",0,-1);
  SignatureCutN* geoneTauCut = new SignatureCutN("goodTaus",1,-1);
  SignatureCutN* getwoTauCut = new SignatureCutN("goodTaus",2,-1);

  SignatureCutMET* lowMETcut = new SignatureCutMET(0,50);
  SignatureCutMET* highMETcut = new SignatureCutMET(50,-1);

  SignatureCutST* lowSTcut = new SignatureCutST(0,400);
  SignatureCutST* midSTcut = new SignatureCutST(400,700);
  SignatureCutST* highSTcut = new SignatureCutST(700,-1);

  SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);
  SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
  SignatureCutNDYPairs* dy2offZcut = new SignatureCutNDYPairs(2,-1,false);
  SignatureCutNDYPairs* dy2onZcut = new SignatureCutNDYPairs(2,-1,true);
  SignatureCutNDYPairs* dy0cut = new SignatureCutNDYPairs(0,0,false);

  SignatureCutQ* zeroLeptonChargeCut = new SignatureCutQ("goodMuons",-0.1,0.1);
  zeroLeptonChargeCut->addProduct("goodElectrons");
  SignatureCutQ* negativeLeptonChargeCut = new SignatureCutQ("goodMuons",-99,-0.1);
  negativeLeptonChargeCut->addProduct("goodElectrons");
  SignatureCutQ* positiveLeptonChargeCut = new SignatureCutQ("goodMuons",0.1,99);
  positiveLeptonChargeCut->addProduct("goodElectrons");
   
  SignatureCutAllLeptonMass* allLeptonZCut = new SignatureCutAllLeptonMass(75,105);

  SignatureCutThreshold* electron20cut = new SignatureCutThreshold("goodElectrons","electronThreshold");
  electron20cut->addThreshold(20);
  SignatureCutThreshold* muon20cut = new SignatureCutThreshold("goodMuons","muonThreshold");
  muon20cut->addThreshold(20);
  SignatureCutCombined* thresholdCut = new SignatureCutCombined(electron20cut,muon20cut,false,"thresholdcut");

  TString met_tags[2] = {"","MET"};
  SignatureCut* met_cuts[2];
  met_cuts[0] = lowMETcut;
  met_cuts[1] = highMETcut;
  TString st_tags[3] = {"STL","STM","STH"};
  SignatureCut* st_cuts[3];
  st_cuts[0] = lowSTcut;
  st_cuts[1] = midSTcut;
  st_cuts[2] = highSTcut;
  TString b_tags[3] = {"B0","B1","B2"};
  SignatureCut* b_cuts[3];
  //b_cuts[0] = zeroBjetCut;
  //b_cuts[1] = oneBjetCut;
  //b_cuts[2] = getwoBjetCut;
  TString dy_tags[3] = {"DY0","DY1","DY2"};
  TString zv_tags[2] = {"offZ","onZ"};
  TString tau_tags[3] = {"Tau0","Tau1","Tau2"};
  SignatureCut* tau_cuts[3];
  tau_cuts[0] = zeroTauCut;
  tau_cuts[1] = oneTauCut;
  tau_cuts[2] = getwoTauCut;

  int bmin[3] = {0,1,2};
  int bmax[3] = {0,1,100};

  TString lep_channels[9] = {"Mu4El0","Mu3El1","Mu2El2","Mu1El3","Mu0El4","Mu3El0","Mu2El1","Mu1El2","Mu0El3"};

  /////////////////////
  ///1 light leptons///
  /////////////////////
  Signature* base1light[4];
  base1light[0] = new Signature("MuP","");
  base1light[0]->addCut(oneMuonCut);
  base1light[0]->addCut(zeroElectronCut);
  base1light[0]->addCut(positiveLeptonChargeCut);
  base1light[1] = new Signature("MuN","");
  base1light[1]->addCut(oneMuonCut);
  base1light[1]->addCut(zeroElectronCut);
  base1light[1]->addCut(negativeLeptonChargeCut);
  base1light[2] = new Signature("ElP","");
  base1light[2]->addCut(oneElectronCut);
  base1light[2]->addCut(zeroMuonCut);
  base1light[2]->addCut(positiveLeptonChargeCut);
  base1light[3] = new Signature("ElN","");
  base1light[3]->addCut(oneElectronCut);
  base1light[3]->addCut(zeroMuonCut);
  base1light[3]->addCut(negativeLeptonChargeCut);


  /////////////////////
  ///2 light leptons///
  /////////////////////
  Signature* base2light[9];
  base2light[0] = new Signature("Mu2El0DY0","");
  base2light[0]->addCut(twoMuonCut);
  base2light[0]->addCut(zeroElectronCut);
  base2light[0]->addCut(dy0cut);
  base2light[1] = new Signature("Mu2El0DY1offZ","");
  base2light[1]->addCut(twoMuonCut);
  base2light[1]->addCut(zeroElectronCut);
  base2light[1]->addCut(dy1offZcut);
  base2light[2] = new Signature("Mu2El0DY1onZ","");
  base2light[2]->addCut(twoMuonCut);
  base2light[2]->addCut(zeroElectronCut);
  base2light[2]->addCut(dy1onZcut);
  base2light[3] = new Signature("Mu0El2DY0","");
  base2light[3]->addCut(zeroMuonCut);
  base2light[3]->addCut(twoElectronCut);
  base2light[3]->addCut(dy0cut);
  base2light[4] = new Signature("Mu0El2DY1offZ","");
  base2light[4]->addCut(zeroMuonCut);
  base2light[4]->addCut(twoElectronCut);
  base2light[4]->addCut(dy1offZcut);
  base2light[5] = new Signature("Mu0El2DY1onZ","");
  base2light[5]->addCut(zeroMuonCut);
  base2light[5]->addCut(twoElectronCut);
  base2light[5]->addCut(dy1onZcut);
  base2light[6] = new Signature("Mu1El1OS","");
  base2light[6]->addCut(oneMuonCut);
  base2light[6]->addCut(oneElectronCut);
  base2light[6]->addCut(zeroLeptonChargeCut);
  base2light[7] = new Signature("Mu1El1SSP","");
  base2light[7]->addCut(oneMuonCut);
  base2light[7]->addCut(oneElectronCut);
  base2light[7]->addCut(positiveLeptonChargeCut);
  base2light[8] = new Signature("Mu1El1SSN","");
  base2light[8]->addCut(oneMuonCut);
  base2light[8]->addCut(oneElectronCut);
  base2light[8]->addCut(negativeLeptonChargeCut);

  /////////////////////
  ///3 light leptons///
  /////////////////////
  Signature* base3light[12];
  base3light[0] = new Signature("Mu3El0DY0","");
  base3light[0]->addCut(threeMuonCut);
  base3light[0]->addCut(zeroElectronCut);
  base3light[0]->addCut(dy0cut);
  base3light[1] = new Signature("Mu3El0DY1offZ","");
  base3light[1]->addCut(threeMuonCut);
  base3light[1]->addCut(zeroElectronCut);
  base3light[1]->addCut(dy1offZcut);
  base3light[2] = new Signature("Mu3El0DY1onZ","");
  base3light[2]->addCut(threeMuonCut);
  base3light[2]->addCut(zeroElectronCut);
  base3light[2]->addCut(dy1onZcut);
  base3light[3] = new Signature("Mu2El1DY0","");
  base3light[3]->addCut(twoMuonCut);
  base3light[3]->addCut(oneElectronCut);
  base3light[3]->addCut(dy0cut);
  base3light[4] = new Signature("Mu2El1DY1offZ","");
  base3light[4]->addCut(twoMuonCut);
  base3light[4]->addCut(oneElectronCut);
  base3light[4]->addCut(dy1offZcut);
  base3light[5] = new Signature("Mu2El1DY1onZ","");
  base3light[5]->addCut(twoMuonCut);
  base3light[5]->addCut(oneElectronCut);
  base3light[5]->addCut(dy1onZcut);
  base3light[6] = new Signature("Mu1El2DY0","");
  base3light[6]->addCut(oneMuonCut);
  base3light[6]->addCut(twoElectronCut);
  base3light[6]->addCut(dy0cut);
  base3light[7] = new Signature("Mu1El2DY1offZ","");
  base3light[7]->addCut(oneMuonCut);
  base3light[7]->addCut(twoElectronCut);
  base3light[7]->addCut(dy1offZcut);
  base3light[8] = new Signature("Mu1El2DY1onZ","");
  base3light[8]->addCut(oneMuonCut);
  base3light[8]->addCut(twoElectronCut);
  base3light[8]->addCut(dy1onZcut);
  base3light[9] = new Signature("Mu0El3DY0","");
  base3light[9]->addCut(zeroMuonCut);
  base3light[9]->addCut(threeElectronCut);
  base3light[9]->addCut(dy0cut);
  base3light[10] = new Signature("Mu0El3DY1offZ","");
  base3light[10]->addCut(zeroMuonCut);
  base3light[10]->addCut(threeElectronCut);
  base3light[10]->addCut(dy1offZcut);
  base3light[11] = new Signature("Mu0El3DY1onZ","");
  base3light[11]->addCut(zeroMuonCut);
  base3light[11]->addCut(threeElectronCut);
  base3light[11]->addCut(dy1onZcut);


  /////////////////////
  ///4 light leptons///
  /////////////////////
  Signature* base4light[21];
  base4light[0] = new Signature("Mu4El0DY0","");
  base4light[0]->addCut(gefourMuonCut);
  base4light[0]->addCut(zeroElectronCut);
  base4light[0]->addCut(dy0cut);
  base4light[1] = new Signature("Mu4El0DY1offZ","");
  base4light[1]->addCut(gefourMuonCut);
  base4light[1]->addCut(zeroElectronCut);
  base4light[1]->addCut(dy1offZcut);
  base4light[2] = new Signature("Mu4El0DY1onZ","");
  base4light[2]->addCut(gefourMuonCut);
  base4light[2]->addCut(zeroElectronCut);
  base4light[2]->addCut(dy1onZcut);
  base4light[3] = new Signature("Mu4El0DY2offZ","");
  base4light[3]->addCut(gefourMuonCut);
  base4light[3]->addCut(zeroElectronCut);
  base4light[3]->addCut(dy2offZcut);
  base4light[4] = new Signature("Mu4El0DY2onZ","");
  base4light[4]->addCut(gefourMuonCut);
  base4light[4]->addCut(zeroElectronCut);
  base4light[4]->addCut(dy2onZcut);
  base4light[5] = new Signature("Mu2El2DY0","");
  base4light[5]->addCut(getwoMuonCut);
  base4light[5]->addCut(getwoElectronCut);
  base4light[5]->addCut(dy0cut);
  base4light[6] = new Signature("Mu2El2DY1offZ","");
  base4light[6]->addCut(getwoMuonCut);
  base4light[6]->addCut(getwoElectronCut);
  base4light[6]->addCut(dy1offZcut);
  base4light[7] = new Signature("Mu2El2DY1onZ","");
  base4light[7]->addCut(getwoMuonCut);
  base4light[7]->addCut(getwoElectronCut);
  base4light[7]->addCut(dy1onZcut);
  base4light[8] = new Signature("Mu2El2DY2offZ","");
  base4light[8]->addCut(getwoMuonCut);
  base4light[8]->addCut(getwoElectronCut);
  base4light[8]->addCut(dy2offZcut);
  base4light[9] = new Signature("Mu2El2DY2onZ","");
  base4light[9]->addCut(getwoMuonCut);
  base4light[9]->addCut(getwoElectronCut);
  base4light[9]->addCut(dy2onZcut);
  base4light[10] = new Signature("Mu0El4DY0","");
  base4light[10]->addCut(zeroMuonCut);
  base4light[10]->addCut(gefourElectronCut);
  base4light[10]->addCut(dy0cut);
  base4light[11] = new Signature("Mu0El4DY1offZ","");
  base4light[11]->addCut(zeroMuonCut);
  base4light[11]->addCut(gefourElectronCut);
  base4light[11]->addCut(dy1offZcut);
  base4light[12] = new Signature("Mu0El4DY1onZ","");
  base4light[12]->addCut(zeroMuonCut);
  base4light[12]->addCut(gefourElectronCut);
  base4light[12]->addCut(dy1onZcut);
  base4light[13] = new Signature("Mu0El4DY2offZ","");
  base4light[13]->addCut(zeroMuonCut);
  base4light[13]->addCut(gefourElectronCut);
  base4light[13]->addCut(dy2offZcut);
  base4light[14] = new Signature("Mu0El4DY2onZ","");
  base4light[14]->addCut(zeroMuonCut);
  base4light[14]->addCut(gefourElectronCut);
  base4light[14]->addCut(dy2onZcut);
  base4light[15] = new Signature("Mu3El1DY0","");
  base4light[15]->addCut(gethreeMuonCut);
  base4light[15]->addCut(oneElectronCut);
  base4light[15]->addCut(dy0cut);
  base4light[16] = new Signature("Mu3El1DY1offZ","");
  base4light[16]->addCut(gethreeMuonCut);
  base4light[16]->addCut(oneElectronCut);
  base4light[16]->addCut(dy1offZcut);
  base4light[17] = new Signature("Mu3El1DY1onZ","");
  base4light[17]->addCut(gethreeMuonCut);
  base4light[17]->addCut(oneElectronCut);
  base4light[17]->addCut(dy1onZcut);
  base4light[18] = new Signature("Mu1El3DY0","");
  base4light[18]->addCut(oneMuonCut);
  base4light[18]->addCut(gethreeElectronCut);
  base4light[18]->addCut(dy0cut);
  base4light[19] = new Signature("Mu1El3DY1offZ","");
  base4light[19]->addCut(oneMuonCut);
  base4light[19]->addCut(gethreeElectronCut);
  base4light[19]->addCut(dy1offZcut);
  base4light[20] = new Signature("Mu1El3DY1onZ","");
  base4light[20]->addCut(oneMuonCut);
  base4light[20]->addCut(gethreeElectronCut);
  base4light[20]->addCut(dy1onZcut);

  ////////////////////----------------
  //now loop and add//----------------
  ////////////////////----------------

  for(int s = 0; s < 3; s++){//ST loop
    for(int b = 0; b < 3; b++){//btag loop
      for(int t = 0; t < 3; t++){//tau loop
	TString extratag=tau_tags[t]+b_tags[b]+st_tags[s];
	for(int i = 0; i < 4; i++){//light1 signatures
	  SignatureWithBjets* nsig = new SignatureWithBjets(*base1light[i],bmin[b],bmax[b]);
	  nsig->setName(TString(base1light[i]->getName()+extratag));
	  nsig->addCut(st_cuts[s]);
	  nsig->addCut(tau_cuts[t]);
	  nsig->addCut(thresholdCut);
	  handler->addBjetSignature(nsig);
	}
	for(int i = 0; i < 9; i++){//light2
	  SignatureWithBjets* nsig = new SignatureWithBjets(*base2light[i],bmin[b],bmax[b]);
	  nsig->setName(TString(base2light[i]->getName()+extratag));
	  nsig->addCut(st_cuts[s]);
	  nsig->addCut(tau_cuts[t]);
	  nsig->addCut(thresholdCut);
	  handler->addBjetSignature(nsig);
	}
	for(int i = 0; i < 12; i++){//light3
	  SignatureWithBjets* nsig = new SignatureWithBjets(*base3light[i],bmin[b],bmax[b]);
	  nsig->setName(TString(base3light[i]->getName()+extratag));
	  nsig->addCut(st_cuts[s]);
	  nsig->addCut(tau_cuts[t]);
	  nsig->addCut(thresholdCut);
	  handler->addBjetSignature(nsig);
	}
	if(t > 0)continue;
	for(int i = 0; i < 21; i++){//light4
	  SignatureWithBjets* nsig = new SignatureWithBjets(*base4light[i],bmin[b],bmax[b]);
	  nsig->setName(TString(base4light[i]->getName()+extratag));
	  nsig->addCut(st_cuts[s]);
	  nsig->addCut(tau_cuts[t]);
	  nsig->addCut(thresholdCut);
	  handler->addBjetSignature(nsig);
	}
      }
    }
  }

}
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
void addTTWSignatures(SignatureHandler* handler)
{
  SignatureCutNElectron* zeroElectronCut = new SignatureCutNElectron(0,0);
  SignatureCutNElectron* oneElectronCut = new SignatureCutNElectron(1,1);
  SignatureCutNElectron* twoElectronCut = new SignatureCutNElectron(2,2);
  SignatureCutNElectron* threeElectronCut = new SignatureCutNElectron(3,3);
  SignatureCutNElectron* fourElectronCut = new SignatureCutNElectron(4,4);
  SignatureCutNElectron* gezeroElectronCut = new SignatureCutNElectron(0,-1);
  SignatureCutNElectron* geoneElectronCut = new SignatureCutNElectron(1,-1);
  SignatureCutNElectron* getwoElectronCut = new SignatureCutNElectron(2,-1);
  SignatureCutNElectron* gethreeElectronCut = new SignatureCutNElectron(3,-1);
  SignatureCutNElectron* gefourElectronCut = new SignatureCutNElectron(4,-1);

  SignatureCutN* oneTrackCut = new SignatureCutN("isoTracksPrompt",1,1);

  SignatureCutNMuon* zeroMuonCut = new SignatureCutNMuon(0,0);
  SignatureCutNMuon* oneMuonCut = new SignatureCutNMuon(1,1);
  SignatureCutNMuon* twoMuonCut = new SignatureCutNMuon(2,2);
  SignatureCutNMuon* threeMuonCut = new SignatureCutNMuon(3,3);
  SignatureCutNMuon* fourMuonCut = new SignatureCutNMuon(4,4);
  SignatureCutNMuon* gezeroMuonCut = new SignatureCutNMuon(0,-1);
  SignatureCutNMuon* geoneMuonCut = new SignatureCutNMuon(1,-1);
  SignatureCutNMuon* getwoMuonCut = new SignatureCutNMuon(2,-1);
  SignatureCutNMuon* gethreeMuonCut = new SignatureCutNMuon(3,-1);
  SignatureCutNMuon* gefourMuonCut = new SignatureCutNMuon(4,-1);

  SignatureCutMET* lowMETcut = new SignatureCutMET(0,50);
  SignatureCutMET* highMETcut = new SignatureCutMET(50,-1);

  SignatureCutHT* lowHTcut = new SignatureCutHT(0,200);
  SignatureCutHT* highHTcut = new SignatureCutHT(200,-1);
  SignatureCutHT* HT400cut = new SignatureCutHT(400,-1);

  /*
  SignatureCutN* zeroBjetCut = new SignatureCutN("bJetsCSVM",0,0);
  SignatureCutN* oneBjetCut = new SignatureCutN("bJetsCSVM",1,1);
  SignatureCutN* twoBjetCut = new SignatureCutN("bJetsCSVM",2,2);
  SignatureCutN* gezeroBjetCut = new SignatureCutN("bJetsCSVM",0,-1);
  SignatureCutN* geoneBjetCut = new SignatureCutN("bJetsCSVM",1,-1);
  SignatureCutN* getwoBjetCut = new SignatureCutN("bJetsCSVM",2,-1);
  SignatureCutN* gethreeBjetCut = new SignatureCutN("bJetsCSVM",3,-1);
  */
  SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);
  SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
  SignatureCutNDYPairs* dy2offZcut = new SignatureCutNDYPairs(2,-1,false);
  SignatureCutNDYPairs* dy2onZcut = new SignatureCutNDYPairs(2,-1,true);
  SignatureCutNDYPairs* dy0cut = new SignatureCutNDYPairs(0,0,false);

  SignatureCutQ* zeroLeptonChargeCut = new SignatureCutQ("goodMuons",-0.1,0.1);
  zeroLeptonChargeCut->addProduct("goodElectrons");
  SignatureCutQ* negativeLeptonChargeCut = new SignatureCutQ("goodMuons",-99,-0.1);
  negativeLeptonChargeCut->addProduct("goodElectrons");
  SignatureCutQ* positiveLeptonChargeCut = new SignatureCutQ("goodMuons",0.1,99);
  positiveLeptonChargeCut->addProduct("goodElectrons");
   
  SignatureCutAllLeptonMass* allLeptonZCut = new SignatureCutAllLeptonMass(75,105);

  TString met_tags[2] = {"","MET"};
  SignatureCut* met_cuts[2];
  met_cuts[0] = lowMETcut;
  met_cuts[1] = highMETcut;
  TString ht_tags[2] = {"","HT"};
  SignatureCut* ht_cuts[2];
  ht_cuts[0] = lowHTcut;
  ht_cuts[1] = highHTcut;
  TString b_tags[3] = {"B0","B1","B2"};
  SignatureCut* b_cuts[3];
  //b_cuts[0] = zeroBjetCut;
  //b_cuts[1] = oneBjetCut;
  //b_cuts[2] = getwoBjetCut;
  TString dy_tags[3] = {"DY0","DY1","DY2"};
  TString zv_tags[2] = {"offZ","onZ"};

  int bmin[3] = {0,1,2};
  int bmax[3] = {0,1,100};

  TString lep_channels[9] = {"Mu4El0","Mu3El1","Mu2El2","Mu1El3","Mu0El4","Mu3El0","Mu2El1","Mu1El2","Mu0El3"};
  int lep_maxdy[9] = {2,1,2,1,2,1,1,1,1};
  SignatureCut* dy_cuts[3][2];
  dy_cuts[0][0] = dy0cut;
  dy_cuts[0][1] = dy0cut;
  dy_cuts[1][1] = dy1onZcut;
  dy_cuts[1][0] = dy1offZcut;
  dy_cuts[2][1] = dy2onZcut;
  dy_cuts[2][0] = dy2offZcut;

  for(int i = 0; i < 2; i++){
    for(int l = 0; l < 2; l++){
      for(int b = 0; b < 3; b++){
	TString extratag =  b_tags[b]+ht_tags[i]+met_tags[l];
	SignatureWithBjets* MuP = new SignatureWithBjets(TString("Mu1El0Pos"+extratag),"",bmin[b],bmax[b]);
	MuP->addCut(oneMuonCut);
	MuP->addCut(zeroElectronCut);
	MuP->addCut(ht_cuts[i]);
	MuP->addCut(met_cuts[l]);
	//MuP->addCut(b_cuts[b]);
	MuP->addCut(positiveLeptonChargeCut);
	SignatureWithBjets* MuN = new SignatureWithBjets(TString("Mu1El0Neg"+extratag),"",bmin[b],bmax[b]);
	MuN->addCut(oneMuonCut);
	MuN->addCut(zeroElectronCut);
	MuN->addCut(ht_cuts[i]);
	MuN->addCut(met_cuts[l]);
	//MuN->addCut(b_cuts[b]);
	MuN->addCut(negativeLeptonChargeCut);

	SignatureWithBjets* ElP = new SignatureWithBjets(TString("Mu0El1Pos"+extratag),"",bmin[b],bmax[b]);
	ElP->addCut(zeroMuonCut);
	ElP->addCut(oneElectronCut);
	ElP->addCut(ht_cuts[i]);
	ElP->addCut(met_cuts[l]);
	//ElP->addCut(b_cuts[b]);
	ElP->addCut(positiveLeptonChargeCut);

	SignatureWithBjets* ElN = new SignatureWithBjets(TString("Mu0El1Neg"+extratag),"",bmin[b],bmax[b]);
	ElN->addCut(zeroMuonCut);
	ElN->addCut(oneElectronCut);
	ElN->addCut(ht_cuts[i]);
	ElN->addCut(met_cuts[l]);
	//ElN->addCut(b_cuts[b]);
	ElN->addCut(negativeLeptonChargeCut);

	handler->addBjetSignature(MuP);
	handler->addBjetSignature(MuN);
	handler->addBjetSignature(ElP);
	handler->addBjetSignature(ElN);
      }
    }
  }

  for(int i = 0; i < 2; i++){
    for(int l = 0; l < 2; l++){
      for(int b = 0; b < 3; b++){
	TString extratag =  b_tags[b]+ht_tags[i]+met_tags[l];
	SignatureWithBjets* Mu2El0DY0 = new SignatureWithBjets(TString("Mu2El0DY0"+extratag),"",bmin[b],bmax[b]);
	Mu2El0DY0->addCut(twoMuonCut);
	Mu2El0DY0->addCut(zeroElectronCut);
	Mu2El0DY0->addCut(dy0cut);
	Mu2El0DY0->addCut(ht_cuts[i]);
	Mu2El0DY0->addCut(met_cuts[l]);
	//Mu2El0DY0->addCut(b_cuts[b]);
	SignatureWithBjets* Mu2El0DY1onZ = new SignatureWithBjets(TString("Mu2El0DY1onZ"+extratag),"",bmin[b],bmax[b]);
	Mu2El0DY1onZ->addCut(twoMuonCut);
	Mu2El0DY1onZ->addCut(zeroElectronCut);
	Mu2El0DY1onZ->addCut(dy1onZcut);
	Mu2El0DY1onZ->addCut(ht_cuts[i]);
	Mu2El0DY1onZ->addCut(met_cuts[l]);
	//Mu2El0DY1onZ->addCut(b_cuts[b]);
	SignatureWithBjets* Mu2El0DY1offZ = new SignatureWithBjets(TString("Mu2El0DY1offZ"+extratag),"",bmin[b],bmax[b]);
	Mu2El0DY1offZ->addCut(twoMuonCut);
	Mu2El0DY1offZ->addCut(zeroElectronCut);
	Mu2El0DY1offZ->addCut(dy1offZcut);
	Mu2El0DY1offZ->addCut(ht_cuts[i]);
	Mu2El0DY1offZ->addCut(met_cuts[l]);
	//Mu2El0DY1offZ->addCut(b_cuts[b]);
	
	SignatureWithBjets* Mu1El1OS = new SignatureWithBjets(TString("Mu1El1OS"+extratag),"",bmin[b],bmax[b]);
	Mu1El1OS->addCut(oneMuonCut);
	Mu1El1OS->addCut(oneElectronCut);
	Mu1El1OS->addCut(ht_cuts[i]);
	Mu1El1OS->addCut(met_cuts[l]);
	Mu1El1OS->addCut(zeroLeptonChargeCut);
	//Mu1El1OS->addCut(b_cuts[b]);
	SignatureWithBjets* Mu1El1SSP = new SignatureWithBjets(TString("Mu1El1SSP"+extratag),"",bmin[b],bmax[b]);
	Mu1El1SSP->addCut(oneMuonCut);
	Mu1El1SSP->addCut(oneElectronCut);
	Mu1El1SSP->addCut(ht_cuts[i]);
	Mu1El1SSP->addCut(met_cuts[l]);
	Mu1El1SSP->addCut(positiveLeptonChargeCut);
	//Mu1El1SSP->addCut(b_cuts[b]);
	SignatureWithBjets* Mu1El1SSN = new SignatureWithBjets(TString("Mu1El1SSN"+extratag),"",bmin[b],bmax[b]);
	Mu1El1SSN->addCut(oneMuonCut);
	Mu1El1SSN->addCut(oneElectronCut);
	Mu1El1SSN->addCut(ht_cuts[i]);
	Mu1El1SSN->addCut(met_cuts[l]);
	Mu1El1SSN->addCut(negativeLeptonChargeCut);
	//Mu1El1SSN->addCut(b_cuts[b]);
	
	
	SignatureWithBjets* Mu0El2DY0 = new SignatureWithBjets(TString("Mu0El2DY0"+extratag),"",bmin[b],bmax[b]);
	Mu0El2DY0->addCut(zeroMuonCut);
	Mu0El2DY0->addCut(twoElectronCut);
	Mu0El2DY0->addCut(dy0cut);
	Mu0El2DY0->addCut(ht_cuts[i]);
	Mu0El2DY0->addCut(met_cuts[l]);
	//Mu0El2DY0->addCut(b_cuts[b]);
	SignatureWithBjets* Mu0El2DY1onZ = new SignatureWithBjets(TString("Mu0El2DY1onZ"+extratag),"",bmin[b],bmax[b]);
	Mu0El2DY1onZ->addCut(zeroMuonCut);
	Mu0El2DY1onZ->addCut(twoElectronCut);
	Mu0El2DY1onZ->addCut(dy1onZcut);
	Mu0El2DY1onZ->addCut(ht_cuts[i]);
	Mu0El2DY1onZ->addCut(met_cuts[l]);
	//Mu0El2DY1onZ->addCut(b_cuts[b]);
	SignatureWithBjets* Mu0El2DY1offZ = new SignatureWithBjets(TString("Mu0El2DY1offZ"+extratag),"",bmin[b],bmax[b]);
	Mu0El2DY1offZ->addCut(zeroMuonCut);
	Mu0El2DY1offZ->addCut(twoElectronCut);
	Mu0El2DY1offZ->addCut(dy1offZcut);
	Mu0El2DY1offZ->addCut(ht_cuts[i]);
	Mu0El2DY1offZ->addCut(met_cuts[l]);
	//Mu0El2DY1offZ->addCut(b_cuts[b]);
	
	if(i == 0 && l == 0){
	  Mu2El0DY0->addCut(allLeptonZCut);
	  //Mu2El0DY1onZ->addCut(allLeptonZCut);
	  Mu2El0DY1offZ->addCut(allLeptonZCut);
	  Mu0El2DY0->addCut(allLeptonZCut);
	  //Mu0El2DY1onZ->addCut(allLeptonZCut);
	  Mu0El2DY1offZ->addCut(allLeptonZCut);
	  Mu1El1OS->addCut(allLeptonZCut);
	  Mu1El1SSP->addCut(allLeptonZCut);
	  Mu1El1SSN->addCut(allLeptonZCut);
	}
	
	handler->addBjetSignature(Mu2El0DY0);
	handler->addBjetSignature(Mu2El0DY1onZ);
	handler->addBjetSignature(Mu2El0DY1offZ);
	handler->addBjetSignature(Mu0El2DY0);
	handler->addBjetSignature(Mu0El2DY1onZ);
	handler->addBjetSignature(Mu0El2DY1offZ);
	handler->addBjetSignature(Mu1El1OS);
	handler->addBjetSignature(Mu1El1SSP);
	handler->addBjetSignature(Mu1El1SSN);

	/////////////////
	//Add Seed Sigs//
	/////////////////
	SignatureWithBjets* Mu2El0DY0Track = new SignatureWithBjets(*Mu2El0DY0);
	Mu2El0DY0Track->addCut(oneTrackCut);
	Mu2El0DY0Track->setName(TString("Mu2El0DY0Track"+extratag));
	SignatureWithBjets* Mu2El0DY1onZTrack = new SignatureWithBjets(*Mu2El0DY1onZ);
	Mu2El0DY1onZTrack->addCut(oneTrackCut);
	Mu2El0DY1onZTrack->setName(TString("Mu2El0DY1onZTrack"+extratag));
	SignatureWithBjets* Mu2El0DY1offZTrack = new SignatureWithBjets(*Mu2El0DY1offZ);
	Mu2El0DY1offZTrack->addCut(oneTrackCut);
	Mu2El0DY1offZTrack->setName(TString("Mu2El0DY1offZTrack"+extratag));
	SignatureWithBjets* Mu0El2DY0Track = new SignatureWithBjets(*Mu0El2DY0);
	Mu0El2DY0Track->addCut(oneTrackCut);
	Mu0El2DY0Track->setName(TString("Mu0El2DY0Track"+extratag));
	SignatureWithBjets* Mu0El2DY1onZTrack = new SignatureWithBjets(*Mu0El2DY1onZ);
	Mu0El2DY1onZTrack->addCut(oneTrackCut);
	Mu0El2DY1onZTrack->setName(TString("Mu0El2DY1onZTrack"+extratag));
	SignatureWithBjets* Mu0El2DY1offZTrack = new SignatureWithBjets(*Mu0El2DY1offZ);
	Mu0El2DY1offZTrack->addCut(oneTrackCut);
	Mu0El2DY1offZTrack->setName(TString("Mu0El2DY1offZTrack"+extratag));
	SignatureWithBjets* Mu1El1OSTrack = new SignatureWithBjets(*Mu1El1OS);
	Mu1El1OSTrack->addCut(oneTrackCut);
	Mu1El1OSTrack->setName(TString("Mu1El1OSTrack"+extratag));
	SignatureWithBjets* Mu1El1SSPTrack = new SignatureWithBjets(*Mu1El1SSP);
	Mu1El1SSPTrack->addCut(oneTrackCut);
	Mu1El1SSPTrack->setName(TString("Mu1El1SSPTrack"+extratag));
	SignatureWithBjets* Mu1El1SSNTrack = new SignatureWithBjets(*Mu1El1SSN);
	Mu1El1SSNTrack->addCut(oneTrackCut);
	Mu1El1SSNTrack->setName(TString("Mu1El1SSNTrack"+extratag));

	handler->addBjetSignature(Mu2El0DY0Track);
	handler->addBjetSignature(Mu2El0DY1onZTrack);
	handler->addBjetSignature(Mu2El0DY1offZTrack);
	handler->addBjetSignature(Mu0El2DY0Track);
	handler->addBjetSignature(Mu0El2DY1onZTrack);
	handler->addBjetSignature(Mu0El2DY1offZTrack);
	handler->addBjetSignature(Mu1El1OSTrack);
	handler->addBjetSignature(Mu1El1SSPTrack);
	handler->addBjetSignature(Mu1El1SSNTrack);


      }
    }
  }
  
  for(int n = 0; n < 9; n++){
    Signature* sig = new Signature("sig","");
    switch(n){
      case 0:
	sig->addCut(gefourMuonCut);
	sig->addCut(zeroElectronCut);
	break;
      case 1:
	sig->addCut(gethreeMuonCut);
	sig->addCut(oneElectronCut);
	break;
      case 2:
	sig->addCut(getwoMuonCut);
	sig->addCut(getwoElectronCut);
	break;
      case 3:
	sig->addCut(oneMuonCut);
	sig->addCut(gethreeElectronCut);
	break;
      case 4:
	sig->addCut(zeroMuonCut);
	sig->addCut(gefourElectronCut);
	break;
      case 5:
	sig->addCut(threeMuonCut);
	sig->addCut(zeroElectronCut);
	break;
      case 6:
	sig->addCut(twoMuonCut);
	sig->addCut(oneElectronCut);
	break;
      case 7:
	sig->addCut(oneMuonCut);
	sig->addCut(twoElectronCut);
	break;
      case 8:
	sig->addCut(zeroMuonCut);
	sig->addCut(threeElectronCut);
	break;
    }
    for(int i = 0; i < 2; i++){
      Signature* nsig = new Signature(*sig);
      nsig->addCut(ht_cuts[i]);
      for(int l = 0; l < 2; l++){
	Signature* n2sig = new Signature(*nsig);
	n2sig->addCut(met_cuts[l]);
	for(int b = 0; b <3; b++){
	  for(int j = 0; j < 3 && j <= lep_maxdy[n]; j++){
	    for(int k = 0; k < 2; k++){
	      if(j == 0 && k > 0)continue;
	      SignatureWithBjets* nnsig = new SignatureWithBjets(*n2sig,bmin[b],bmax[b]);
	      TString newname = lep_channels[n];
	      newname += dy_tags[j];
	      newname += zv_tags[k];
	      newname += b_tags[b];
	      newname += ht_tags[i];
	      newname += met_tags[l];
	      cout<<newname<<endl;
	      //nnsig->addCut(b_cuts[b]);
	      nnsig->addCut(dy_cuts[j][k]);
	      if(i==0 && l == 0)nnsig->addCut(allLeptonZCut);
	      nnsig->setName(newname);
	      handler->addBjetSignature(nnsig);
	      if(n > 4){
		SignatureWithBjets* seedSig = new SignatureWithBjets(*nnsig);
		seedSig->addCut(oneTrackCut);
		TString seedname = lep_channels[n];
		seedname += dy_tags[j];
		seedname += zv_tags[k];
		seedname += "Track";
		seedname += b_tags[b];
		seedname += ht_tags[i];
		seedname += met_tags[l];
		seedSig->setName(seedname);
		handler->addBjetSignature(seedSig);
	      }
	    }
	  }
	}
      }
    }
  }



}
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
//--------------------------------
void addTTbarSignatures(SignatureHandler* handler)
{
  SignatureCutNElectron* zeroElectronCut = new SignatureCutNElectron(0,0);
  SignatureCutNElectron* oneElectronCut = new SignatureCutNElectron(1,1);
  SignatureCutNElectron* twoElectronCut = new SignatureCutNElectron(2,2);
  SignatureCutNElectron* threeElectronCut = new SignatureCutNElectron(3,3);
  SignatureCutNElectron* fourElectronCut = new SignatureCutNElectron(4,4);
  SignatureCutNElectron* gezeroElectronCut = new SignatureCutNElectron(0,-1);
  SignatureCutNElectron* geoneElectronCut = new SignatureCutNElectron(1,-1);
  SignatureCutNElectron* getwoElectronCut = new SignatureCutNElectron(2,-1);
  SignatureCutNElectron* gethreeElectronCut = new SignatureCutNElectron(3,-1);
  SignatureCutNElectron* gefourElectronCut = new SignatureCutNElectron(4,-1);

  SignatureCutNMuon* zeroMuonCut = new SignatureCutNMuon(0,0);
  SignatureCutNMuon* oneMuonCut = new SignatureCutNMuon(1,1);
  SignatureCutNMuon* twoMuonCut = new SignatureCutNMuon(2,2);
  SignatureCutNMuon* threeMuonCut = new SignatureCutNMuon(3,3);
  SignatureCutNMuon* fourMuonCut = new SignatureCutNMuon(4,4);
  SignatureCutNMuon* gezeroMuonCut = new SignatureCutNMuon(0,-1);
  SignatureCutNMuon* geoneMuonCut = new SignatureCutNMuon(1,-1);
  SignatureCutNMuon* getwoMuonCut = new SignatureCutNMuon(2,-1);
  SignatureCutNMuon* gethreeMuonCut = new SignatureCutNMuon(3,-1);
  SignatureCutNMuon* gefourMuonCut = new SignatureCutNMuon(4,-1);

  SignatureCutMET* lowMETcut = new SignatureCutMET(0,50);
  SignatureCutMET* highMETcut = new SignatureCutMET(50,-1);

  SignatureCutHT* lowHTcut = new SignatureCutHT(0,200);
  SignatureCutHT* highHTcut = new SignatureCutHT(200,-1);
  SignatureCutHT* HT400cut = new SignatureCutHT(400,-1);

  SignatureCutST* ttbarSTcut = new SignatureCutST(150,-1);

  SignatureCutN* gethreeJetCut = new SignatureCutN("goodJets",3,-1);

  SignatureCutThreshold* leadingMuon30 = new SignatureCutThreshold("goodMuons");
  leadingMuon30->addThreshold(30);
  SignatureCutThreshold* leadingElectron35 = new SignatureCutThreshold("goodElectrons");
  leadingElectron35->addThreshold(35);

  SignatureCutNBjetTrack* zeroBjetCut = new SignatureCutNBjetTrack(0,0,3.0);
  SignatureCutNBjetTrack* oneBjetCut = new SignatureCutNBjetTrack(1,1,3.0);
  SignatureCutNBjetTrack* twoBjetCut = new SignatureCutNBjetTrack(2,2,3.0);
  SignatureCutNBjetTrack* gezeroBjetCut = new SignatureCutNBjetTrack(0,-1,3.0);
  SignatureCutNBjetTrack* geoneBjetCut = new SignatureCutNBjetTrack(1,-1,3.0);
  SignatureCutNBjetTrack* getwoBjetCut = new SignatureCutNBjetTrack(2,-1,3.0);
  SignatureCutNBjetTrack* gethreeBjetCut = new SignatureCutNBjetTrack(3,-1,3.0);

  SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);
  SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
  SignatureCutNDYPairs* dy2offZcut = new SignatureCutNDYPairs(2,-1,false);
  SignatureCutNDYPairs* dy2onZcut = new SignatureCutNDYPairs(2,-1,true);
  SignatureCutNDYPairs* dy0cut = new SignatureCutNDYPairs(0,0,false);

  SignatureCutQ* zeroLeptonChargeCut = new SignatureCutQ("goodMuons",-0.1,0.1);
  zeroLeptonChargeCut->addProduct("goodElectrons");
  SignatureCutQ* negativeLeptonChargeCut = new SignatureCutQ("goodMuons",-99,-0.1);
  negativeLeptonChargeCut->addProduct("goodElectrons");
  SignatureCutQ* positiveLeptonChargeCut = new SignatureCutQ("goodMuons",0.1,99);
  positiveLeptonChargeCut->addProduct("goodElectrons");
   
  SignatureCutAllLeptonMass* allLeptonZCut = new SignatureCutAllLeptonMass(75,105);


  Signature* TTbarMu1 = new Signature("TTbarMu1","");
  TTbarMu1->addCut(oneMuonCut);
  TTbarMu1->addCut(zeroElectronCut);
  TTbarMu1->addCut(gethreeJetCut);
  TTbarMu1->addCut(geoneBjetCut);
  TTbarMu1->addCut(leadingMuon30);
  TTbarMu1->addCut(ttbarSTcut);
  handler->addSignature(TTbarMu1);

  Signature* TTbarEl1 = new Signature("TTbarEl1","");
  TTbarEl1->addCut(oneElectronCut);
  TTbarEl1->addCut(zeroMuonCut);
  TTbarEl1->addCut(gethreeJetCut);
  TTbarEl1->addCut(geoneBjetCut);
  TTbarEl1->addCut(leadingElectron35);
  TTbarEl1->addCut(ttbarSTcut);
  handler->addSignature(TTbarEl1);

}
//-------------------------------------------\\
//-------------------------------------------\\
void addMCsignatures(SignatureHandler* handler)
{

  ObjectCutMCStatus* statusGoodCut = new ObjectCutMCStatus(3);
  ObjectCutMCMotherPdgID* mothW = new ObjectCutMCMotherPdgID(24,true);
  ObjectCutMCMotherPdgID* motherTau = new ObjectCutMCMotherPdgID(15,true);
  ObjectCutMCPdgID* tauCut = new ObjectCutMCPdgID(15,true);
  ObjectCutCombined* motherW = new ObjectCutCombined(mothW,motherTau,false);
  ObjectCutMCPdgID* electronCut = new ObjectCutMCPdgID(11,true);
  ObjectCutMCPdgID* muonCut = new ObjectCutMCPdgID(13,true);
  ObjectCutCombined* leptonCut = new ObjectCutCombined(electronCut,muonCut,false);
  //leptonCut->addCut(tauCut);


  handler->addProduct("leptonsFromW","allMCparticles");
  handler->addProductCut("leptonsFromW",statusGoodCut);
  handler->addProductCut("leptonsFromW",leptonCut);
  handler->addProductCut("leptonsFromW",motherW);

  handler->addProduct("muonsFromW","allMCparticles");
  handler->addProductCut("muonsFromW",statusGoodCut);
  handler->addProductCut("muonsFromW",muonCut);
  handler->addProductCut("muonsFromW",motherW);

  handler->addProduct("electronsFromW","allMCparticles");
  handler->addProductCut("electronsFromW",statusGoodCut);
  handler->addProductCut("electronsFromW",electronCut);
  handler->addProductCut("electronsFromW",motherW);

  SignatureCutN* threeLepMC = new SignatureCutN("leptonsFromW",3,3);
  //threeLepMC->addProduct("electronsFromW");

  SignatureCutN* twoLepMC = new SignatureCutN("leptonsFromW",2,2);
  //twoLepMC->addProduct("electronsFromW");

  SignatureCutN* oneLepMC = new SignatureCutN("leptonsFromW",1,1);
  //oneLepMC->addProduct("electronsFromW");

  SignatureCutN* zeroLepMC = new SignatureCutN("leptonsFromW",0,0);
  SignatureCutN* fourLepMC = new SignatureCutN("leptonsFromW",4,-1);

  SignatureCutQ* sameSignNeg = new SignatureCutQ("leptonsFromW",-999,-0.1);
  //sameSignNeg->addProduct("electronsFromW");

  SignatureCutQ* sameSignPos = new SignatureCutQ("leptonsFromW",0.1,999);
  //sameSignPos->addProduct("electronsFromW");

  SignatureCutQ* zeroChargeCut = new SignatureCutQ("leptonsFromW",-0.1,0.1);
  //zeroChargeCut->addProduct("electronsFromW");

  SignatureCutCombined* sameSignCut = new SignatureCutCombined(sameSignPos,sameSignNeg,false);

  SignatureTH1F_PT* mcThreeLep_leptonpt = new SignatureTH1F_PT("mcThreeLep_leptonpt","leptonsFromW");
  SignatureTH1F_PT* mcTwoLepOS_leptonpt = new SignatureTH1F_PT("mcTwoLepOS_leptonpt","leptonsFromW");
  SignatureTH1F_PT* mcTwoLepSS_leptonpt = new SignatureTH1F_PT("mcTwoLepSS_leptonpt","leptonsFromW");
  SignatureTH1F_PT* mcOneLep_leptonpt = new SignatureTH1F_PT("mcOneLep_leptonpt","leptonsFromW");
  SignatureTH1F_PT* mcFourLep_leptonpt = new SignatureTH1F_PT("mcFourLep_leptonpt","leptonsFromW");
  SignatureTH1F_PT* mcZeroLep_leptonpt = new SignatureTH1F_PT("mcZeroLep_leptonpt","leptonsFromW");

  Signature* mcThreeLep = new Signature("mcThreeLep","");
  mcThreeLep->addCut(threeLepMC);
  mcThreeLep->addHistogram(mcThreeLep_leptonpt);
  Signature* mcTwoLepOS = new Signature("mcTwoLepOS","");
  mcTwoLepOS->addCut(twoLepMC);
  mcTwoLepOS->addCut(zeroChargeCut);
  mcTwoLepOS->addHistogram(mcTwoLepOS_leptonpt);
  Signature* mcTwoLepSS = new Signature("mcTwoLepSS","");
  mcTwoLepSS->addCut(twoLepMC);
  mcTwoLepSS->addCut(sameSignCut);
  mcTwoLepSS->addHistogram(mcTwoLepSS_leptonpt);
  Signature* mcOneLep = new Signature("mcOneLep","");
  mcOneLep->addCut(oneLepMC);
  mcOneLep->addHistogram(mcOneLep_leptonpt);
  Signature* mcZeroLep = new Signature("mcZeroLep","");
  mcZeroLep->addCut(zeroLepMC);
  mcZeroLep->addHistogram(mcZeroLep_leptonpt);
  Signature* mcFourLep = new Signature("mcFourLep","");
  mcFourLep->addCut(fourLepMC);
  mcFourLep->addHistogram(mcFourLep_leptonpt);


  handler->addPreCutSignature(mcThreeLep);
  handler->addPreCutSignature(mcTwoLepOS);
  handler->addPreCutSignature(mcTwoLepSS);
  handler->addPreCutSignature(mcOneLep);
  handler->addPreCutSignature(mcZeroLep);
  handler->addPreCutSignature(mcFourLep);


}
//--------------------------------------
//--------------------------------------
void setupFakeStudy(SignatureHandler* handler)
{
  SignatureCutN* zeroBjetCut = new SignatureCutN("bJetsCSVM",0,0);
  SignatureCutN* oneBjetCut = new SignatureCutN("bJetsCSVM",1,1);
  SignatureCutN* twoBjetCut = new SignatureCutN("bJetsCSVM",2,2);
  SignatureCutN* gezeroBjetCut = new SignatureCutN("bJetsCSVM",0,-1);
  SignatureCutN* geoneBjetCut = new SignatureCutN("bJetsCSVM",1,-1);
  SignatureCutN* getwoBjetCut = new SignatureCutN("bJetsCSVM",2,-1);
  SignatureCutN* gethreeBjetCut = new SignatureCutN("bJetsCSVM",3,-1);
  SignatureWithBjets* ddB0 = new SignatureWithBjets("ddB0","",0,0);
  //ddB0->addCut(zeroBjetCut);
  SignatureWithBjets* ddB1 = new SignatureWithBjets("ddB1","",1,1);
  //ddB1->addCut(oneBjetCut);
  SignatureWithBjets* ddB2 = new SignatureWithBjets("ddB2","",2,100);
  //ddB2->addCut(getwoBjetCut);

  //addHistograms
  double jetHigh[3] = {60,150,-1};
  double jetLow[3] = {0,60,150};
  TString jetName[3] = {"0to60","60to150","gt150"};
  TString productNames[20] = {"isoTracks","isoMuons","isoElectrons","isoTracksNonPrompt","isoMuonsNonPrompt","isoElectronsNonPrompt","jetTracks","jetMuons","jetElectrons","jetTracksNonPrompt","jetMuonsNonPrompt","jetElectronsNonPrompt","isoTestElectrons","isoTestMuons","isoTestElectronsNonPrompt","isoTestMuonsNonPrompt","isoTestElectronsAwayB","isoTestElectronsNonPromptAwayB","isoTestMuonsAwayB","isoTestMuonsNonPromptAwayB"};

  for(int i = 0; i < 3; i++){
    TString name0dxy = "B0_"+jetName[i]+"_baseElectrons_dxy_vs_relIso";
    TString name1dxy = "B1_"+jetName[i]+"_baseElectrons_dxy_vs_relIso";
    TString name2dxy = "B2_"+jetName[i]+"_baseElectrons_dxy_vs_relIso";
    SignatureTH2F_RelIsoVsDxy* dxy0 = new SignatureTH2F_RelIsoVsDxy(name0dxy,"baseElectrons",jetLow[i],jetHigh[i],"LEAD");
    SignatureTH2F_RelIsoVsDxy* dxy1 = new SignatureTH2F_RelIsoVsDxy(name1dxy,"baseElectrons",jetLow[i],jetHigh[i],"LEAD");
    SignatureTH2F_RelIsoVsDxy* dxy2 = new SignatureTH2F_RelIsoVsDxy(name2dxy,"baseElectrons",jetLow[i],jetHigh[i],"LEAD");
    ddB0->addHistogram(dxy0);
    ddB1->addHistogram(dxy1);
    ddB2->addHistogram(dxy2);
    for(int j = 0; j < 20; j++){
      TString name0pt = "B0_"+jetName[i]+"_"+productNames[j]+"_pt";
      TString name0ptvreliso = "B0_"+jetName[i]+"_"+productNames[j]+"_pt_vs_relIso";
      TString name1pt = "B1_"+jetName[i]+"_"+productNames[j]+"_pt";
      TString name1ptvreliso = "B1_"+jetName[i]+"_"+productNames[j]+"_pt_vs_relIso";
      TString name2pt = "B2_"+jetName[i]+"_"+productNames[j]+"_pt";
      TString name2ptvreliso = "B2_"+jetName[i]+"_"+productNames[j]+"_pt_vs_relIso";

      SignatureTH1F_PT* pt0 = new SignatureTH1F_PT(name0pt,productNames[j],jetLow[i],jetHigh[i],"LEAD");
      SignatureTH2F_RelIsoVsPt* ptvr0 = new SignatureTH2F_RelIsoVsPt(name0ptvreliso,productNames[j],jetLow[i],jetHigh[i],"LEAD");
      ddB0->addHistogram(pt0);
      ddB0->addHistogram(ptvr0);
      SignatureTH1F_PT* pt1 = new SignatureTH1F_PT(name1pt,productNames[j],jetLow[i],jetHigh[i],"LEAD");
      SignatureTH2F_RelIsoVsPt* ptvr1 = new SignatureTH2F_RelIsoVsPt(name1ptvreliso,productNames[j],jetLow[i],jetHigh[i],"LEAD");
      ddB1->addHistogram(pt1);
      ddB1->addHistogram(ptvr1);
      SignatureTH1F_PT* pt2 = new SignatureTH1F_PT(name2pt,productNames[j],jetLow[i],jetHigh[i],"LEAD");
      SignatureTH2F_RelIsoVsPt* ptvr2 = new SignatureTH2F_RelIsoVsPt(name2ptvreliso,productNames[j],jetLow[i],jetHigh[i],"LEAD");
      ddB2->addHistogram(pt2);
      ddB2->addHistogram(ptvr2);
    }
  }
  handler->addBjetSignature(ddB0);
  handler->addBjetSignature(ddB1);
  handler->addBjetSignature(ddB2);

}
//----------------------------------------------------------
//----------------------------------------------------------
void addTTbarISRSignatures(SignatureHandler* handler)
{

  handler->addProduct("ISRJets","goodJets");
  handler->addProductSeparation("ISRJets","bJetsCSVM",0.6);
  handler->setSelfSeparate("ISRJets",2.0);

  SignatureCutNElectron* zeroElectronCut = new SignatureCutNElectron(0,0);
  SignatureCutNElectron* oneElectronCut = new SignatureCutNElectron(1,1);
  SignatureCutNElectron* twoElectronCut = new SignatureCutNElectron(2,2);
  SignatureCutNElectron* threeElectronCut = new SignatureCutNElectron(3,3);
  SignatureCutNElectron* fourElectronCut = new SignatureCutNElectron(4,4);
  SignatureCutNElectron* gezeroElectronCut = new SignatureCutNElectron(0,-1);
  SignatureCutNElectron* geoneElectronCut = new SignatureCutNElectron(1,-1);
  SignatureCutNElectron* getwoElectronCut = new SignatureCutNElectron(2,-1);
  SignatureCutNElectron* gethreeElectronCut = new SignatureCutNElectron(3,-1);
  SignatureCutNElectron* gefourElectronCut = new SignatureCutNElectron(4,-1);

  SignatureCutNMuon* zeroMuonCut = new SignatureCutNMuon(0,0);
  SignatureCutNMuon* oneMuonCut = new SignatureCutNMuon(1,1);
  SignatureCutNMuon* twoMuonCut = new SignatureCutNMuon(2,2);
  SignatureCutNMuon* threeMuonCut = new SignatureCutNMuon(3,3);
  SignatureCutNMuon* fourMuonCut = new SignatureCutNMuon(4,4);
  SignatureCutNMuon* gezeroMuonCut = new SignatureCutNMuon(0,-1);
  SignatureCutNMuon* geoneMuonCut = new SignatureCutNMuon(1,-1);
  SignatureCutNMuon* getwoMuonCut = new SignatureCutNMuon(2,-1);
  SignatureCutNMuon* gethreeMuonCut = new SignatureCutNMuon(3,-1);
  SignatureCutNMuon* gefourMuonCut = new SignatureCutNMuon(4,-1);

  SignatureCutMET* lowMETcut = new SignatureCutMET(0,50);
  SignatureCutMET* highMETcut = new SignatureCutMET(50,-1);

  SignatureCutHT* lowHTcut = new SignatureCutHT(0,200);
  SignatureCutHT* highHTcut = new SignatureCutHT(200,-1);
  SignatureCutHT* HT400cut = new SignatureCutHT(400,-1);

  SignatureWithBjets* L2B2 = new SignatureWithBjets("L2B2","",2,100);
  L2B2->addCut(geoneMuonCut);
  L2B2->addCut(geoneElectronCut);
  handler->addBjetSignature(L2B2);

  SignatureWithBjets* OFTTbar = new SignatureWithBjets("OFTTbar","",2,100);
  OFTTbar->addCut(geoneMuonCut);
  OFTTbar->addCut(geoneElectronCut);
  OFTTbar->addCut(new SignatureCutN("ISRJets",2,-1));
  handler->addBjetSignature(OFTTbar);

  SignatureTH1F_N* nisrj = new SignatureTH1F_N("isrJets_n","ISRJets");
  SignatureTH1F_M* isrm = new SignatureTH1F_M("isrM","ISRJets",2,0,"M Distribution ; M (GeV) ; ",200,0,1500);

  handler->addHistogram(nisrj);
  handler->addHistogram(isrm);
}
//------------------------------------
//------------------------------------
void addBasicHistograms(SignatureHandler* handler)
{
  handler->addBasicHistograms();

  SignatureTH1F_N* h_nonIsoElectronsPrompt = new SignatureTH1F_N("nonIsoElectronsPrompt_n","nonIsoElectronsPrompt");
  SignatureTH1F_N* h_nonIsoMuonsPrompt = new SignatureTH1F_N("nonIsoMuonsPrompt_n","nonIsoMuonsPrompt");
  SignatureTH1F_N* h_isoTracksPrompt = new SignatureTH1F_N("isoTracksPrompt_n","isoTracksPrompt");
  SignatureTH1F_N* h_nonIsoTracksPrompt = new SignatureTH1F_N("nonIsoTracksPrompt_n","nonIsoTracksPrompt");
  SignatureTH1F_N* h_isoTracksNonPrompt = new SignatureTH1F_N("isoTracksNonPrompt_n","isoTracksNonPrompt");
  SignatureTH1F_N* h_nonIsoTracksNonPrompt = new SignatureTH1F_N("nonIsoTracksNonPrompt_n","nonIsoTracksNonPrompt");
  SignatureTH1F_N* h_nonIsoTracksPromptElectrons = new SignatureTH1F_N("nonIsoTracksPromptElectrons_n","nonIsoTracksPromptElectrons");

  handler->addHistogram(h_nonIsoElectronsPrompt);
  handler->addHistogram(h_nonIsoMuonsPrompt);
  handler->addHistogram(h_isoTracksPrompt);
  handler->addHistogram(h_nonIsoTracksPrompt);
  handler->addHistogram(h_isoTracksNonPrompt);
  handler->addHistogram(h_nonIsoTracksNonPrompt);
  handler->addHistogram(h_nonIsoTracksPromptElectrons);

  SignatureTH2F_NvN* h_nonIsoVsIso = new SignatureTH2F_NvN("nonIsoVsIso_n","isoTracksPrompt","nonIsoTracksPrompt");
  SignatureTH2F_NvN* h_nonIsoMuonVsIso = new SignatureTH2F_NvN("nonIsoMuonVsIso_n","isoTracksPrompt","nonIsoMuonsPrompt");
  SignatureTH2F_NvN* h_nonIsoElectronVsIso = new SignatureTH2F_NvN("nonIsoElectronVsIso_n","isoTracksPrompt","nonIsoElectronsPrompt");

  handler->addHistogram(h_nonIsoVsIso);
  handler->addHistogram(h_nonIsoMuonVsIso);
  handler->addHistogram(h_nonIsoElectronVsIso);

  SignatureTH1F_N* h_posnonIsoElectrons = new SignatureTH1F_N("posNonIsoElectrons_n","posNonIsoElectrons");
  SignatureTH1F_N* h_posnonIsoMuons = new SignatureTH1F_N("posNonIsoMuons_n","posNonIsoMuons");
  handler->addHistogram(h_posnonIsoElectrons);
  handler->addHistogram(h_posnonIsoMuons);
  SignatureTH1F_N* h_negnonIsoElectrons = new SignatureTH1F_N("negNonIsoElectrons_n","negNonIsoElectrons");
  SignatureTH1F_N* h_negnonIsoMuons = new SignatureTH1F_N("negNonIsoMuons_n","negNonIsoMuons");
  handler->addHistogram(h_negnonIsoElectrons);
  handler->addHistogram(h_negnonIsoMuons);

  SignatureTH1F_N* nbjets = new SignatureTH1F_N("nbjets","bJetsCSVM");
  handler->addHistogram(nbjets);

  SignatureTH1F_PT* leadingJetpT = new SignatureTH1F_PT("leadingJet_pt","leadingJet");
  handler->addHistogram(leadingJetpT);

}
//-----
//-----
void addTTZSignatures(SignatureHandler* handler)
{
  ObjectCutPt* leptonPt20 = new ObjectCutPt(20,-1);
  handler->addProductCut("goodElectrons",leptonPt20);
  handler->addProductCut("goodMuons",leptonPt20);

  handler->setSelfSeparate("bJetsCSVM",1.5);

  handler->addProduct("goodExtraJets","goodJets");
  handler->addProductSeparation("goodExtraJets","bJetsCSVM",0.3);

  SignatureCutN* zeroElectrons = new SignatureCutN("goodElectrons",0,0);
  SignatureCutN* twoElectrons = new SignatureCutN("goodElectrons",2,2);
  SignatureCutN* zeroMuons = new SignatureCutN("goodMuons",0,0);
  SignatureCutN* twoMuons = new SignatureCutN("goodMuons",2,2);
  SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);

  Signature* Mu2El0onZ = new Signature("Mu2El0onZ","");
  Mu2El0onZ->addCut(zeroElectrons);
  Mu2El0onZ->addCut(twoMuons);
  Mu2El0onZ->addCut(dy1onZcut);

  Signature* Mu0El2onZ = new Signature("Mu0El2onZ","");
  Mu0El2onZ->addCut(zeroMuons);
  Mu0El2onZ->addCut(twoElectrons);
  Mu0El2onZ->addCut(dy1onZcut);

  SignatureCutN* geOneJets = new SignatureCutN("goodExtraJets",1,-1);
  SignatureCutN* geTwoJets = new SignatureCutN("goodExtraJets",2,-1);
  SignatureCutN* geThreeJets = new SignatureCutN("goodExtraJets",3,-1);
  SignatureCutN* geFourJets = new SignatureCutN("goodExtraJets",4,-1);
  SignatureCutN* geFiveJets = new SignatureCutN("goodExtraJets",5,-1);

  SignatureCutHT* gt100 = new SignatureCutHT(100,-1);
  SignatureCutHT* gt200 = new SignatureCutHT(200,-1);
  SignatureCutHT* gt300 = new SignatureCutHT(300,-1);
  SignatureCutHT* gt400 = new SignatureCutHT(400,-1);
  SignatureCutHT* gt500 = new SignatureCutHT(500,-1);

  TString ht_names[5] = {"HT100","HT200","HT300","HT400","HT500"};
  TString nj_names[5] = {"NJ1","NJ2","NJ3","NJ4","NJ5"};

  SignatureCut* ht_cuts[5];
  ht_cuts[0] = gt100;
  ht_cuts[1] = gt200;
  ht_cuts[2] = gt300;
  ht_cuts[3] = gt400;
  ht_cuts[4] = gt500;

  SignatureCut* nj_cuts[5];
  nj_cuts[0] = geOneJets;
  nj_cuts[1] = geTwoJets;
  nj_cuts[2] = geThreeJets;
  nj_cuts[3] = geFourJets;
  nj_cuts[4] = geFiveJets;

  for(int b = 0; b < 3; b++){
    TString bname = "B";
    bname += b;
    SignatureWithBjets* el2 = new SignatureWithBjets(*Mu0El2onZ,b,100);
    SignatureWithBjets* mu2 = new SignatureWithBjets(*Mu2El0onZ,b,100);
    el2->setName(TString("Mu0El2onZ"+bname));
    mu2->setName(TString("Mu2El0onZ"+bname));
    handler->addBjetSignature(el2);
    handler->addBjetSignature(mu2);
    for(int h = 0; h < 5; h++){
      SignatureWithBjets* el2h = new SignatureWithBjets(*el2);
      SignatureWithBjets* mu2h = new SignatureWithBjets(*mu2);
      el2h->addCut(ht_cuts[h]);
      mu2h->addCut(ht_cuts[h]);
      el2h->setName(TString("Mu0El2onZ"+bname+ht_names[h]));
      mu2h->setName(TString("Mu2El0onZ"+bname+ht_names[h]));
      handler->addBjetSignature(el2h);
      handler->addBjetSignature(mu2h);
    }
    for(int j = 1; j < 5; j++){
      SignatureWithBjets* el2j = new SignatureWithBjets(*el2);
      SignatureWithBjets* mu2j = new SignatureWithBjets(*mu2);
      el2j->addCut(nj_cuts[j]);
      mu2j->addCut(nj_cuts[j]);
      el2j->setName(TString("Mu0El2onZ"+bname+nj_names[j]));
      mu2j->setName(TString("Mu2El0onZ"+bname+nj_names[j]));
      handler->addBjetSignature(el2j);
      handler->addBjetSignature(mu2j);
    }
  }

}
//-----
//-----
//-----
//-----


void setupProducts2012(SignatureHandler* handler){

  ObjectCutPt* leptonPtCut = new ObjectCutPt(10.0,-1,"leptonptcut");
  ObjectCutEta* leptonEtaCut = new ObjectCutEta(2.4,"leptonetacut");
  ObjectCutIrel* isolatedLeptonCut = new ObjectCutIrel(0.0,0.15);
  ObjectCutIrel* nonIsolatedLeptonCut = new ObjectCutIrel(0.2,1.0);
  ObjectCutVertDz* leptonVertDzCut = new ObjectCutVertDz(0.5);
  ObjectCutVertDxy* promptLeptonCut = new ObjectCutVertDxy(0.02);
  ObjectCutReversed* nonPromptLeptonCut = new ObjectCutReversed(new ObjectCutVertDxy(0.03));
  ObjectCutBeamD0* leptonBeamD0Cut = new ObjectCutBeamD0(0.02);
  ObjectCutBeamDxy* leptonBeamDxyCut = new ObjectCutBeamDxy(0.02);
  ObjectCutValidTrackerHits* isoTrackNHitCut = new ObjectCutValidTrackerHits(11,-1);
  ObjectCutAbsRel* leptonAbsRelCut = new ObjectCutAbsRel(0.0,10.0);
  ObjectCutGlobalMuonPromptTight* muonGlobalPromptTightCut = new ObjectCutGlobalMuonPromptTight;
  ObjectCutTrackerMuon* muonTrackerCut = new ObjectCutTrackerMuon;
  ObjectCutIsPF* isPFcut = new ObjectCutIsPF;
  ObjectCutChi2Ndof* chi2ndofCut = new ObjectCutChi2Ndof;

  ObjectCutCharge* posChargeCut = new ObjectCutCharge(0.1,1.5);
  ObjectCutCharge* negChargeCut = new ObjectCutCharge(-1.5,-0.1);

  ObjectCutCombined* goodMuonCut = new ObjectCutCombined(leptonPtCut,leptonEtaCut,true);
  //goodMuonCut->addCut(new ObjectCutValidPixelHits);
  goodMuonCut->addCut(new ObjectCutMuonInnerNumberOfValidPixelHits(1,-1));
  goodMuonCut->addCut(new ObjectCutTrackLayersWithMeasurement);
  goodMuonCut->addCut(new ObjectCutMuonMatches);
  goodMuonCut->addCut(isPFcut);
  goodMuonCut->addCut(new ObjectCutMuonGlobal);
  goodMuonCut->addCut(new ObjectCutValidMuonHits);
  //goodMuonCut->addCut(leptonVertDxyCut);
  //goodMuonCut->addCut(leptonVertDzCut);
  //goodMuonCut->addCut(chi2ndofCut);
  goodMuonCut->addCut(new ObjectCutMuonNormalizedChi2(0,10));
  goodMuonCut->addCut(new ObjectCutMuonInnerVertDz(0,0.5));
  //goodMuonCut->addCut(new ObjectCutMuonInnerVertDxy(0.0,0.02));
  //goodMuonCut->addCut(muonIrelCut);
  ObjectCutMuonInnerVertDxy* promptMuonCut = new ObjectCutMuonInnerVertDxy(0.0,0.02);
  ObjectCutMuonInnerVertDxy* nonPromptMuonCut = new ObjectCutMuonInnerVertDxy(0.03,-1);

  handler->addProductCut("goodMuons",goodMuonCut);
  handler->addProductCut("goodMuons",promptMuonCut);
  handler->addProductCut("goodMuons",isolatedLeptonCut);

  handler->addProduct("basicMuons","allMuons");
  handler->addProductCut("basicMuons",goodMuonCut);
  handler->setSelfSeparate("basicMuons",0.1);

  handler->addProduct("basicMuonsPos","basicMuons");
  handler->addProductCut("basicMuonsPos",posChargeCut);
  handler->addProduct("basicMuonsNeg","basicMuons");
  handler->addProductCut("basicMuonsNeg",negChargeCut);

  handler->addProduct("goodMuonsPos","goodMuons");
  handler->addProductCut("goodMuonsPos",posChargeCut);
  handler->addProduct("goodMuonsNeg","goodMuons");
  handler->addProductCut("goodMuonsNeg",negChargeCut);

  handler->addProduct("muonsNINP","basicMuons");
  handler->addProductCut("muonsNINP",nonIsolatedLeptonCut);
  handler->addProductCut("muonsNINP",nonPromptLeptonCut);

  handler->addProduct("muonsNIP","basicMuons");
  handler->addProductCut("muonsNIP",promptMuonCut);
  handler->addProductCut("muonsNIP",nonIsolatedLeptonCut);

  handler->addProduct("muonsINP","basicMuons");
  handler->addProductCut("muonsINP",isolatedLeptonCut);
  handler->addProductCut("muonsINP",nonPromptLeptonCut);

  handler->addProduct("muonsIP","basicMuons");
  handler->addProductCut("muonsIP",isolatedLeptonCut);
  handler->addProductCut("muonsIP",promptLeptonCut);


  ObjectCutElectronDeltaEta* electronDeltaEtaCut = new ObjectCutElectronDeltaEta(0.007,0.009);
  ObjectCutElectronDeltaPhi* electronDeltaPhiCut = new ObjectCutElectronDeltaPhi(0.15,0.10);
  ObjectCutElectronHadOverEm* electronHadOverEmCut = new ObjectCutElectronHadOverEm(0.12,0.10);
  ObjectCutElectronMissingHits* electronMissingHitsCut = new ObjectCutElectronMissingHits(1);
  ObjectCutElectronSigmaIetaIeta* electronSigmaIetaIetaCut = new ObjectCutElectronSigmaIetaIeta(0.01,0.03);
  ObjectCutElectronExpectedInnerHits* electronExpectedInnerHitsCut = new ObjectCutElectronExpectedInnerHits;
  ObjectCutElectronEminusP* electronEminusPCut = new ObjectCutElectronEminusP;
  ObjectCutElectronChargeConsistent* electronChargeConsistentCut = new ObjectCutElectronChargeConsistent;
  ObjectCutElectronVertexFitProbability* electronVtxProbCut = new ObjectCutElectronVertexFitProbability;
  ObjectCutElectronIsConversion* electronConversionCut = new ObjectCutElectronIsConversion(false);
  ObjectCutElectronSuperClusterEta* inGap = new ObjectCutElectronSuperClusterEta;
  ObjectCutReversed* gapCut = new ObjectCutReversed(inGap);
  ObjectCutElectronVertDz* electronVertDzCut = new ObjectCutElectronVertDz(0.2);
  ObjectCutElectronVertDxy* promptElectronCut = new ObjectCutElectronVertDxy(0.02);
  ObjectCutReversed* nonPromptElectronCut = new ObjectCutReversed(new ObjectCutElectronVertDxy(0.03));


  ObjectCutCombined* goodElectronCut = new ObjectCutCombined(leptonPtCut,leptonEtaCut,true,"goodElectronCutCombined");
  goodElectronCut->addCut(electronVertDzCut);
  goodElectronCut->addCut(electronDeltaEtaCut);
  goodElectronCut->addCut(electronDeltaPhiCut);
  goodElectronCut->addCut(electronHadOverEmCut);
  goodElectronCut->addCut(electronSigmaIetaIetaCut);
  goodElectronCut->addCut(electronMissingHitsCut);
  //goodElectronCut->addCut(leptonVertDxyCut);
  goodElectronCut->addCut(gapCut);
  goodElectronCut->addCut(electronEminusPCut);
  //goodElectronCut->addCut(electronIrelCut);
  //goodElectronCut->addCut(electronChargeConsistentCut);
  //goodElectronCut->addCut(electronVtxProbCut);
  goodElectronCut->addCut(electronConversionCut);
  //goodElectronCut->addCut(isPFcut);
  handler->addProductSeparation("goodElectrons","goodMuons",0.1);
  handler->addProductCut("goodElectrons",goodElectronCut);
  handler->addProductCut("goodElectrons",isolatedLeptonCut);
  handler->addProductCut("goodElectrons",promptElectronCut);

  handler->addProduct("goodSSElectrons","goodElectrons");
  handler->addProductCut("goodSSElectrons",electronChargeConsistentCut);


  handler->addProduct("basicElectrons","allElectrons");
  handler->addProductCut("basicElectrons",goodElectronCut);
  handler->setSelfSeparate("basicElectrons",0.1);

  handler->addProduct("basicElectronsPos","basicElectrons");
  handler->addProductCut("basicElectronsPos",posChargeCut);
  handler->addProduct("basicElectronsNeg","basicElectrons");
  handler->addProductCut("basicElectronsNeg",negChargeCut);

  handler->addProduct("goodElectronsPos","goodElectrons");
  handler->addProductCut("goodElectronsPos",posChargeCut);
  handler->addProduct("goodElectronsNeg","goodElectrons");
  handler->addProductCut("goodElectronsNeg",negChargeCut);

  handler->addProduct("electronsNINP","basicElectrons");
  handler->addProductCut("electronsNINP",nonIsolatedLeptonCut);
  handler->addProductCut("electronsNINP",nonPromptLeptonCut);

  handler->addProduct("electronsINP","basicElectrons");
  handler->addProductCut("electronsINP",nonPromptLeptonCut);
  handler->addProductCut("electronsINP",isolatedLeptonCut);

  handler->addProduct("electronsNIP","basicElectrons");
  handler->addProductCut("electronsNIP",nonIsolatedLeptonCut);
  handler->addProductCut("electronsNIP",promptLeptonCut);

  handler->addProduct("electronsIP","basicElectrons");
  handler->addProductCut("electronsIP",isolatedLeptonCut);
  handler->addProductCut("electronsIP",promptLeptonCut);


  ObjectCutPhotonIsTight* photonTightCut = new ObjectCutPhotonIsTight(true);
  ObjectCutElectronSigmaIetaIeta* photonSigmaIetaIetaCut = new ObjectCutElectronSigmaIetaIeta(0.011,0.034);
  ObjectCutElectronHadOverEm* photonHadOverEmCut = new ObjectCutElectronHadOverEm(0.06,0.05);
  ObjectCutEta* barrelEtaCut = new ObjectCutEta(1.48);
  ObjectCutReversed* endcapEtaCut = new ObjectCutReversed(barrelEtaCut);
  ObjectCutCombined* photonBarrelIsolation = new ObjectCutCombined(barrelEtaCut,new ObjectCutIrelChargedHadron(0,0.06),true);
  photonBarrelIsolation->addCut(new ObjectCutIrelNeutralHadron(0,0.16));
  photonBarrelIsolation->addCut(new ObjectCutIrelPhoton(0,0.08));
  ObjectCutCombined* photonEndcapIsolation = new ObjectCutCombined(endcapEtaCut,new ObjectCutIrelChargedHadron(0,0.05),true);
  photonEndcapIsolation->addCut(new ObjectCutIrelNeutralHadron(0,0.1));
  photonEndcapIsolation->addCut(new ObjectCutIrelPhoton(0,0.12));
  ObjectCutCombined* photonIsolationCut = new ObjectCutCombined(photonBarrelIsolation,photonEndcapIsolation);


  handler->addPhotonCut(leptonPtCut);
  handler->addPhotonCut(leptonEtaCut);
  handler->addPhotonCut(photonSigmaIetaIetaCut);
  handler->addPhotonCut(photonHadOverEmCut);
  handler->addPhotonCut(photonIsolationCut);

  ObjectCutPt* jetPtCut = new ObjectCutPt(30,-1);
  ObjectCutEta* jetEtaCut = new ObjectCutEta(2.5);
  ObjectCutCombined* jetLowEtaCut = new ObjectCutCombined(new ObjectCutEta(2.4),new ObjectCutJetChargedHadronFraction,true);
  jetLowEtaCut->addCut(new ObjectCutJetChargedEMFraction);
  jetLowEtaCut->addCut(new ObjectCutJetChargedMultiplicity);
  ObjectCutReversed* jetHighEtaCut = new ObjectCutReversed(new ObjectCutEta(2.4));
  ObjectCutCombined* jetEtaCuts = new ObjectCutCombined(jetLowEtaCut,jetHighEtaCut);

  handler->addJetCut(jetPtCut);
  handler->addJetCut(jetEtaCut);
  handler->addJetCut(new ObjectCutJetNumberConstituents);
  handler->addJetCut(new ObjectCutJetNeutralEMFraction);
  handler->addJetCut(new ObjectCutJetNeutralHadronFraction);
  handler->addJetCut(jetEtaCuts);

  handler->addProduct("basicJets", "allJets");
  handler->addProductCut("basicJets", jetPtCut);
  handler->addProductCut("basicJets", jetEtaCut);
  handler->addProductCut("basicJets", new ObjectCutJetNumberConstituents);
  handler->addProductCut("basicJets", new ObjectCutJetNeutralEMFraction);
  handler->addProductCut("basicJets", new ObjectCutJetNeutralHadronFraction);
  handler->addProductCut("basicJets", jetEtaCuts);

  handler->addProduct("bJetsCSVM","goodJets");
  handler->addProductCut("bJetsCSVM",new ObjectCutJetBDiscPositive);

  ObjectCutJetGenParticle* fromWcut = new ObjectCutJetGenParticle(24, true);
  handler->addProduct("goodJetsFromW", "goodJets");
  handler->addProductCut("goodJetsFromW", fromWcut);

  handler->addProduct("goodAndTauFakeJets", "basicJets");
  
  ObjectCutPt* tauPtCut = new ObjectCutPt(20.0,-1,"tauptcut");
  ObjectCutCombined* tauChargeCut = new ObjectCutCombined(new ObjectCutTauCharge(-1.1,-0.9),new ObjectCutTauCharge(0.9,1.1));
  ObjectCutCombined* basicTauCut = new ObjectCutCombined(tauChargeCut,tauPtCut,true);
  basicTauCut->addCut(new ObjectCutEta(2.3));
  basicTauCut->addCut(new ObjectCutTauDiscriminants(19));//decaymodefinding
  basicTauCut->addCut(new ObjectCutTauDiscriminants(29));//againstelectronmva
  basicTauCut->addCut(new ObjectCutTauDiscriminants(24));//againstmuontight
  //basicTauCut->addCut(new ObjectCutTauDiscriminants(26));//byloosecombinedisodbsumptcorr
  ObjectCutAbsRel* sidebandTauIsolationCut = new ObjectCutAbsRel(6,15);
  ObjectCutReversed* otherTauIsolationCut = new ObjectCutReversed(new ObjectCutTauDiscriminants(26));

  handler->addProductCut("goodTaus",basicTauCut);
  handler->addProductCut("goodTaus",new ObjectCutTauDiscriminants(26));//byloosecombinedisodbsumptcorr

  ObjectCutTauGenLepton* matchingGenTauCut = new ObjectCutTauGenLepton();
  handler->addProduct("goodTausWithMatchingGenLepton", "goodTaus");
  handler->addProductCut("goodTausWithMatchingGenLepton", matchingGenTauCut);

  handler->addProduct("basicTaus","allTaus");
  handler->addProductCut("basicTaus",basicTauCut);
  handler->setSelfSeparate("basicTaus",0.1);

  handler->addProduct("sidebandTaus","basicTaus");
  handler->addProductCut("sidebandTaus",sidebandTauIsolationCut);
  handler->addProductCut("sidebandTaus",otherTauIsolationCut);

  handler->addProduct("otherTaus","basicTaus");
  handler->addProductCut("otherTaus",otherTauIsolationCut);

  handler->addRecoVertexCut(new VertexCutNdof);
  handler->addRecoVertexCut(new VertexCutR);
  handler->addRecoVertexCut(new VertexCutZ);

  handler->addHandlerCut(new SignatureCutNVertex(1.0));
//  handler->addHandlerCut(new SignatureCutFilter("primaryVertexFilter"));
  handler->addHandlerCut(new SignatureCutFilter("noScrapingFilter"));
  handler->addHandlerCut(new SignatureCutFilter("HBHENoiseFilter"));
  handler->addHandlerCut(new SignatureCutFilter("CSCTightHaloFilter"));
  handler->addHandlerCut(new SignatureCutFilter("hcalLaserEventFilter"));
  handler->addHandlerCut(new SignatureCutFilter("EcalDeadCellTriggerPrimitiveFilter"));
  handler->addHandlerCut(new SignatureCutFilter("trackingFailureFilter"));
  handler->addHandlerCut(new SignatureCutFilter("eeBadScFilter"));

  ////////
  //Track cuts//
  /////////
  ObjectCutNdof* trackNdofCut = new ObjectCutNdof;
  ObjectCutValidTrackerHits* trackValidHits = new ObjectCutValidTrackerHits;
  ObjectCutBeamD0* trackBeamD0 = new ObjectCutBeamD0(0.2);
  ObjectCutVertDz* trackVertDz = new ObjectCutVertDz(1.0);

  ObjectCutCombined* trackGoodNoPtNoEta = new ObjectCutCombined(trackNdofCut,trackValidHits,true);
  trackGoodNoPtNoEta->addCut(trackBeamD0);
  trackGoodNoPtNoEta->addCut(trackVertDz);

  ObjectCutPt* trackPt = new ObjectCutPt(10.0);//Change this to 10 later
  ObjectCutEta* trackEta = new ObjectCutEta(2.4);

  ObjectCutCombined* trackGood = new ObjectCutCombined(trackPt,trackEta,true);

  ObjectCutVertDxy* trackPrompt = new ObjectCutVertDxy(0.02);
  ObjectCutReversed* trackNonPrompt = new ObjectCutReversed(new ObjectCutVertDxy(0.03));

  ObjectCutIrel* trackIsolated = new ObjectCutIrel(0,0.15);
  ObjectCutIrel* trackNonIsolated = new ObjectCutIrel(0.2,1.0);

  handler->addProductCut("goodIsoTracks",trackGood);
  handler->addProductCut("goodIsoTracks",trackGoodNoPtNoEta);
  handler->addProductCut("goodIsoTracks",trackIsolated);
  handler->addProductCut("goodIsoTracks",trackPrompt);

  handler->addProduct("jetTracks","allRecoTracks");
  handler->addProductCut("jetTracks",trackGood);
  handler->addProductCut("jetTracks",trackGoodNoPtNoEta);
  handler->addProductCut("jetTracks",trackNonIsolated);

  handler->addProduct("jetTracksPrompt","jetTracks");
  handler->addProductCut("jetTracksPrompt",trackPrompt);
  handler->addProduct("jetTracksNonPrompt","jetTracks");
  handler->addProductCut("jetTracksNonPrompt",trackNonPrompt);

  //handler->addProduct("nonPromptIsoTracks","allRecoTracks");
  //handler->addProductCut("nonPromptIsoTracks",trackGood);
  //handler->addProductCut("nonPromptIsoTracks",trackGoodNoPtNoEta);
  //handler->addProductCut("nonPromptIsoTracks",trackIsolated);
  //handler->addProductCut("nonPromptIsoTracks",trackNonPrompt);

  handler->addProduct("basicTracks","allRecoTracks");
  handler->addProductCut("basicTracks",trackGood);
  handler->addProductCut("basicTracks",trackGoodNoPtNoEta);

  handler->addProduct("basicTracksNeg","basicTracks");
  handler->addProductCut("basicTracksNeg",negChargeCut);
  handler->addProduct("basicTracksPos","basicTracks");
  handler->addProductCut("basicTracksPos",posChargeCut);

  handler->addProduct("tracksNINP","basicTracks");
  handler->addProductCut("tracksNINP",trackNonPrompt);
  handler->addProductCut("tracksNINP",trackNonIsolated);

  handler->addProduct("tracksINP","basicTracks");
  handler->addProductCut("tracksINP",trackIsolated);
  handler->addProductCut("tracksINP",trackNonPrompt);

  handler->addProduct("tracksNIP","basicTracks");
  handler->addProductCut("tracksNIP",trackNonIsolated);
  handler->addProductCut("tracksNIP",trackPrompt);

  handler->addProduct("tracksIP","basicTracks");
  handler->addProductCut("tracksIP",trackIsolated);
  handler->addProductCut("tracksIP",trackPrompt);

  handler->addProduct("leadingJet","goodJets");
  handler->setSelfSeparate("leadingJet",10000.0);

  handler->setSelfSeparate("goodMuons",0.1);
  handler->setSelfSeparate("goodElectrons",0.1);
  handler->setSelfSeparate("goodTaus",0.1);
  handler->setSelfSeparate("goodIsoTracks",0.005);
  handler->addProductSeparation("goodElectrons","goodMuons",0.1);
  handler->addProductSeparation("goodTaus","goodMuons",0.1);
  handler->addProductSeparation("goodTaus","goodElectrons",0.1);
  handler->addProductSeparation("goodJets","goodMuons",0.4);
  handler->addProductSeparation("goodJets","goodElectrons",0.4);
  handler->addProductSeparation("goodJets","goodTaus",0.4);
  handler->addProductSeparation("goodAndTauFakeJets","goodMuons",0.4);
  handler->addProductSeparation("goodAndTauFakeJets","goodElectrons",0.4);
  handler->addProductSeparation("goodAndTauFakeJets","goodJetsFromW",0.4);
  handler->addProductSeparation("goodAndTauFakeJets","goodTausWithMatchingGenLepton",0.4);
  handler->addProductSeparation("goodPhotons","goodMuons",0.1);
  handler->addProductSeparation("goodPhotons","goodElectrons",0.1);
  handler->addProductSeparation("goodPhotons","goodTaus",0.1);
  handler->addProductSeparation("goodPhotons","goodJets",0.3);
  handler->addProductSeparation("jetTracks","goodMuons",0.1);
  handler->addProductSeparation("jetTracks","goodElectrons",0.1);
  handler->addProductSeparation("jetTracks","goodTaus",0.3);
  //handler->addProductSeparation("jetTracks","jetMuons",0.005);
  handler->addProductSeparation("basicTracks","goodMuons",0.1);
  handler->addProductSeparation("basicTracks","goodElectrons",0.1);
  handler->addProductSeparation("basicTracks","goodTaus",0.3);
  handler->setSelfSeparate("basicTracks",0.005);
  handler->setSelfSeparate("nonPromptIsoTracks",0.005);
  //handler->addProductSeparation("nonPromptIsoTracks","goodMuons",0.1);
  //handler->addProductSeparation("nonPromptIsoTracks","goodElectrons",0.1);
  //handler->addProductSeparation("nonPromptIsoTracks","goodTaus",0.3);
  handler->addProductSeparation("basicElectrons","goodMuons",0.1);
  handler->addProductSeparation("basicTaus","goodMuons",0.1);
  handler->addProductSeparation("basicTaus","goodElectrons",0.1);
  //handler->addProductSeparation("basicTaus","leadingJet",0.6);


}
