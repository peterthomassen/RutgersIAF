void setupLJJTriggers(SignatureHandler* handler,int mode=0)
{
  SignatureCutTrigger* triggerCut = new SignatureCutTrigger;
  SignatureCutThreshold* singleElectronThreshold = new SignatureCutThreshold("tightElectrons","singleElectronThreshold");
  singleElectronThreshold->addThreshold(35.0);
  SignatureCutThreshold* singleMuonThreshold = new SignatureCutThreshold("tightMuons","singleMuonThreshold");
  singleMuonThreshold->addThreshold(35.0);

  triggerCut->addCut("SingleMuon",singleMuonThreshold);
  triggerCut->addCut("SingleElectron",singleElectronThreshold);
  switch(mode){
  case 1:
    addAcceptTriggers(triggerCut,"SingleMuon",getSingleMuonTriggers());
    break;
  case 2:
    addAcceptTriggers(triggerCut,"SingleElectron",getSingleElectronTriggers());
    addVetoTriggers(triggerCut,"SingleMuon",getSingleMuonTriggers());
    break;
  default:
    break;
  }

  handler->addHandlerCut(triggerCut);
}
//----------------------------------------------------------------
//----------------------------------------------------------------
void setupLJJProducts(SignatureHandler* handler)
{
  ObjectCutPt* leptonPtCut = new ObjectCutPt(20,-1);
  ObjectCutIrel* isolatedLeptonCut = new ObjectCutIrel(0.0,0.15);
  ObjectCutIrel* nonIsolatedLeptonCut = new ObjectCutIrel(0.2,-1);
  ObjectCutIrel* nonIsolatedElectronCut = new ObjectCutIrel(0.2,5.0);
  ////////////////////////
  //common electron cuts//
  ////////////////////////


  ///////////////////////
  //loose electron cuts//
  ///////////////////////
  ObjectCutMissingPixelHits* electronLooseMissingPixelHits = new ObjectCutMissingPixelHits(0,1);
  ObjectCutMissingPixelHits* electronTightMissingPixelHits = new ObjectCutMissingPixelHits(0,0);
  ObjectCutElectronSuperClusterEta* electronSuperClusterEtaCut = new ObjectCutElectronSuperClusterEta(0.0,2.4);
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
  ObjectCutElectronVertDz* electronVertDzCut = new ObjectCutElectronVertDz(0.1);
  ObjectCutElectronVertDxy* promptElectronCut = new ObjectCutElectronVertDxy(0.02);
  ObjectCutReversed* nonPromptElectronCut = new ObjectCutReversed(new ObjectCutElectronVertDxy(0.03));
  ObjectCutIrel* looseElectronIrelCut = new ObjectCutIrel(0.0,0.15);
  ObjectCutMissingPixelHits* electronLooseMissingPixelHits = new ObjectCutMissingPixelHits(0,1);
  ObjectCutMissingPixelHits* electronTightMissingPixelHits = new ObjectCutMissingPixelHits(0,0);
  ObjectCutElectronVertDxy* promptElectronCut = new ObjectCutElectronVertDxy(0.02);


  ObjectCutCombined* looseElectronCut = new ObjectCutCombined(leptonPtCut,electronSuperClusterEtaCut,true,"looseElectronCut");
  looseElectronCut->addCut(electronVertDzCut);
  looseElectronCut->addCut(electronDeltaEtaCut);
  looseElectronCut->addCut(electronDeltaPhiCut);
  looseElectronCut->addCut(electronHadOverEmCut);
  looseElectronCut->addCut(electronSigmaIetaIetaCut);
  looseElectronCut->addCut(electronMissingHitsCut);
  //looseElectronCut->addCut(leptonVertDxyCut);
  looseElectronCut->addCut(gapCut);
  looseElectronCut->addCut(electronEminusPCut);
  looseElectronCut->addCut(electronConversionCut);
  looseElectronCut->addCut(looseElectronIrelCut);
  looseElectronCut->addCut(promptElectronCut);
  looseElectronCut->addCut(electronLooseMissingPixelHits);
  //looseElectronCut->addCut(isPFcut);


  ///////////////////////
  //tight electron cuts//
  ///////////////////////
  ObjectCutElectronDeltaEta* tightElectronDeltaEtaCut = new ObjectCutElectronDeltaEta(0.004,0.007);
  ObjectCutElectronDeltaPhi* tightElectronDeltaPhiCut = new ObjectCutElectronDeltaPhi(0.06,0.03);
  ObjectCutIrel* tightElectronIrelCut = new ObjectCutIrel(0.0,0.09);
  ObjectCutCombined* tightElectronCut = new ObjectCutCombined(leptonPtCut,electronSuperClusterEtaCut,true,"tightElectronCut");
  tightElectronCut->addCut(electronEminusPCut);
  tightElectronCut->addCut(electronSigmaIetaIetaCut);
  tightElectronCut->addCut(electronHadOverEmCut);
  tightElectronCut->addCut(tightElectronDeltaEtaCut);
  tightElectronCut->addCut(tightElectronDeltaPhiCut);
  tightElectronCut->addCut(promptElectronCut);
  tightElectronCut->addCut(electronVertDzCut);
  tightElectronCut->addCut(tightElectronIrelCut);
  tightElectronCut->addCut(electronConversionCut);
  tightElectronCut->addCut(electronMissingHitsCut);
  tightElectronCut->addCut(electronTightMissingPixelHits);

  ////////////////////
  //common muon cuts//
  ////////////////////

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
  ObjectCutEta* muonEtaCut = new ObjectCutEta(2.5);

  //////////////////
  //loose muon cut//
  //////////////////

  ObjectCutCombined* looseMuonCut = new ObjectCutCombined(leptonPtCut,muonEtaCut,true,"looseMuonCut");
  looseMuonCut->addCut(new ObjectCutMuonInnerNumberOfValidPixelHits(1,-1));
  looseMuonCut->addCut(new ObjectCutTrackLayersWithMeasurement);
  looseMuonCut->addCut(new ObjectCutMuonMatches);
  looseMuonCut->addCut(isPFcut);
  looseMuonCut->addCut(new ObjectCutMuonGlobal);
  looseMuonCut->addCut(new ObjectCutValidMuonHits);
  looseMuonCut->addCut(new ObjectCutMuonNormalizedChi2(0,10));
  looseMuonCut->addCut(new ObjectCutMuonInnerVertDz(0,0.1));
  ObjectCutMuonInnerVertDxy* promptMuonCut = new ObjectCutMuonInnerVertDxy(0.0,0.02);
  ObjectCutMuonInnerVertDxy* nonPromptMuonCut = new ObjectCutMuonInnerVertDxy(0.03,-1);
  looseMuonCut->addCut(promptMuonCut);
  ObjectCutIrel* looseMuonIrelCut = new ObjectCutIrel(0,0.15);
  looseMuonCut->addCut(looseMuonIrelCut);

  //////////////////
  //tight muon cut//
  //////////////////
  ObjectCutHcalIso* hcalIsoCut = new ObjectCutHcalIso(-1,6);
  ObjectCutEcalIso* ecalIsoCut = new ObjectCutEcalIso(-1,4);
  ObjectCutIrel* tightMuonIrelCut = new ObjectCutIrel(0,0.1);
  ObjectCutCombined* tightMuonCut = new ObjectCutCombined(hcalIsoCut,ecalIsoCut,true,"tightMuonCut");
  tightMuonCut->addCut(tightMuonIrelCut);

  handler->addProductCut("goodMuons",looseMuonCut);
  handler->addProductCut("goodElectrons",looseElectronCut);

  handler->addProduct("tightElectrons","allElectrons");
  handler->addProductCut("tightElectrons",tightElectronCut);
  handler->addProduct("tightMuons","goodMuons");
  handler->addProductCut("tightMuons",tightMuonIrelCut);

  handler->addProductSeparation("goodElectrons","goodMuons",0.1);
  handler->addProductSeparation("tightElectrons","goodMuons",0.1);

  //////////////
  //Setup Taus//
  //////////////

  ObjectCutPt* tauPtCut = new ObjectCutPt(20.0,-1,"tauptcut");
  ObjectCutCombined* tauChargeCut = new ObjectCutCombined(new ObjectCutTauCharge(-1.1,-0.9),new ObjectCutTauCharge(0.9,1.1));

  ObjectCutEta* tauEtaCut = new ObjectCutEta(2.3);
  ObjectCutTauDiscriminants* tauDiscCut19 = new ObjectCutTauDiscriminants(19);
  ObjectCutTauDiscriminants* tauDiscCut29 = new ObjectCutTauDiscriminants(29);
  ObjectCutTauDiscriminants* tauDiscCut24 = new ObjectCutTauDiscriminants(24);
  ObjectCutTauDiscriminants* tauDiscCut26 = new ObjectCutTauDiscriminants(26);

  handler->addTauCut(tauPtCut);
  handler->addTauCut(tauEtaCut);
  handler->addTauCut(tauDiscCut19);//decaymodefinding
  handler->addTauCut(tauDiscCut29);//againstelectronmva
  handler->addTauCut(tauDiscCut24);//againstmuontight
  handler->addTauCut(tauDiscCut26);//byloosecombinedisodbsumptcorr
  handler->addTauCut(tauChargeCut);

  //////////////
  //Setup Jets//
  //////////////
  ObjectCutPt* jetPtCut = new ObjectCutPt(30,-1);
  ObjectCutEta* jetEtaCut = new ObjectCutEta(2.4);
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

  handler->addProductSeparation("goodJets","goodMuons",0.5);
  handler->addProductSeparation("goodJets","goodElectrons",0.5);

  handler->addProduct("bJetsCSVM","goodJets");
  handler->addProductCut("bJetsCSVM",new ObjectCutJetBDiscPositive);
  handler->addProduct("bJetsCSVL","goodJets");
  handler->addProductCut("bJetsCSVL",new ObjectCutJetBDiscPositive(10,0.244));

  handler->addProduct("nonBjetsCSVM","goodJets");
  handler->addProductSeparation("nonBjetsCSVM","bJetsCSVM",0.5);

  ////////////////////
  //Fakeable Objects//
  ////////////////////

  ObjectCutAbsRelTau* sidebandTauIso = new ObjectCutAbsRelTau(6.0,15.0);
  ObjectCutCombined* sidebandTauCut = new ObjectCutCombined(tauPtCut,tauEtaCut,true,"sidebandTauCut");
  sidebandTauCut->addCut(tauDiscCut19);
  sidebandTauCut->addCut(tauDiscCut29);
  sidebandTauCut->addCut(tauDiscCut24);
  sidebandTauCut->addCut(tauChargeCut);
  sidebandTauCut->addCut(sidebandTauIso);
  handler->addProduct("sidebandTaus","allTaus");
  handler->addProductCut("sidebandTaus",sidebandTauCut);

  ObjectCutIrel* sidebandElectronIrelCut = new ObjectCutIrel(0.15,2.0);
  ObjectCutCombined* sidebandElectronCut = new ObjectCutCombined(leptonPtCut,electronSuperClusterEtaCut,true,"sidebandElectronCut");
  sidebandElectronCut->addCut(electronEminusPCut);
  sidebandElectronCut->addCut(electronSigmaIetaIetaCut);
  sidebandElectronCut->addCut(electronHadOverEmCut);
  sidebandElectronCut->addCut(tightElectronDeltaEtaCut);
  sidebandElectronCut->addCut(tightElectronDeltaPhiCut);
  sidebandElectronCut->addCut(promptElectronCut);
  sidebandElectronCut->addCut(electronVertDzCut);
  sidebandElectronCut->addCut(sidebandElectronIrelCut);
  sidebandElectronCut->addCut(electronConversionCut);
  sidebandElectronCut->addCut(electronMissingHitsCut);
  sidebandElectronCut->addCut(electronTightMissingPixelHits);
  handler->addProduct("sidebandElectrons","allElectrons");
  handler->addProductCut("sidebandElectrons",sidebandElectronCut);

  ObjectCutCombined* sidebandMuonCut = new ObjectCutCombined(leptonPtCut,muonEtaCut,true,"sidebandMuonCut");
  sidebandMuonCut->addCut(new ObjectCutMuonInnerNumberOfValidPixelHits(1,-1));
  sidebandMuonCut->addCut(new ObjectCutTrackLayersWithMeasurement);
  sidebandMuonCut->addCut(new ObjectCutMuonMatches);
  sidebandMuonCut->addCut(isPFcut);
  sidebandMuonCut->addCut(new ObjectCutMuonGlobal);
  sidebandMuonCut->addCut(new ObjectCutValidMuonHits);
  sidebandMuonCut->addCut(new ObjectCutMuonNormalizedChi2(0,10));
  sidebandMuonCut->addCut(new ObjectCutMuonInnerVertDz(0,0.1));
  ObjectCutMuonInnerVertDxy* promptMuonCut = new ObjectCutMuonInnerVertDxy(0.0,0.02);
  ObjectCutMuonInnerVertDxy* nonPromptMuonCut = new ObjectCutMuonInnerVertDxy(0.03,-1);
  sidebandMuonCut->addCut(promptMuonCut);
  ObjectCutIrel* sidebandMuonIrelCut = new ObjectCutIrel(0.15,2.0);
  sidebandMuonCut->addCut(sidebandMuonIrelCut);

  ////////////////
  //Setup Tracks//
  ////////////////

  ObjectCutCombined* goodTrackCut = new ObjectCutCombined(leptonPtCut,muonEtaCut,true);
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

  /////////////////////////
  //Fake Study Products////
  /////////////////////////
  ObjectCutCombined* fakeTauCut = new ObjectCutCombined(tauPtCut,tauEtaCut,true,"fakeTauCut");
  fakeTauCut->addCut(tauDiscCut19);
  fakeTauCut->addCut(tauDiscCut29);
  fakeTauCut->addCut(tauDiscCut24);
  fakeTauCut->addCut(tauChargeCut);

  ObjectCutCombined* fakeElectronCut = new ObjectCutCombined(leptonPtCut,electronSuperClusterEtaCut,true,"fakeElectronCut");
  fakeElectronCut->addCut(electronEminusPCut);
  fakeElectronCut->addCut(electronSigmaIetaIetaCut);
  fakeElectronCut->addCut(electronHadOverEmCut);
  fakeElectronCut->addCut(tightElectronDeltaEtaCut);
  fakeElectronCut->addCut(tightElectronDeltaPhiCut);
  fakeElectronCut->addCut(electronVertDzCut);
  fakeElectronCut->addCut(electronConversionCut);
  fakeElectronCut->addCut(electronMissingHitsCut);
  fakeElectronCut->addCut(electronTightMissingPixelHits);

  ObjectCutCombined* fakeMuonCut = new ObjectCutCombined(leptonPtCut,muonEtaCut,true,"fakeMuonCut");
  fakeMuonCut->addCut(new ObjectCutMuonInnerNumberOfValidPixelHits(1,-1));
  fakeMuonCut->addCut(new ObjectCutTrackLayersWithMeasurement);
  fakeMuonCut->addCut(new ObjectCutMuonMatches);
  fakeMuonCut->addCut(isPFcut);
  fakeMuonCut->addCut(new ObjectCutMuonGlobal);
  fakeMuonCut->addCut(new ObjectCutValidMuonHits);
  fakeMuonCut->addCut(new ObjectCutMuonNormalizedChi2(0,10));
  fakeMuonCut->addCut(new ObjectCutMuonInnerVertDz(0,0.1));

  handler->addProduct("fakeStudyTaus","allTaus");
  handler->addProductCut("fakeStudyTaus",fakeTauCut);
  handler->addProduct("fakeStudyElectrons","allElectrons");
  handler->addProductCut("fakeStudyElectrons",fakeElectronCut);
  handler->addProduct("fakeStudyMuons","allMuons");
  handler->addProductCut("fakeStudyMuons",fakeMuonCut);


}
//-----------------------------------------------------------
//-----------------------------------------------------------
void addLJJSignatures(SignatureHandler* handler)
{
  SignatureCutN* geoneTightLeptons = new SignatureCutN("tightMuons",1,-1);
  geoneTightLeptons->addProduct("tightElectrons");
  SignatureCutN* gefourJets = new SignatureCutN("goodJets",4,-1);
  SignatureCutN* geoneCSVM = new SignatureCutN("bJetsCSVM",1,-1);
  SignatureCutN* zeroCSVM = new SignatureCutN("bJetsCSVM",0,0);

  Signature* Lge1B0Jge4 = new Signature("Lge1B0Jge4","");
  Lge1B0Jge4->addCut(geoneTightLeptons);
  Lge1B0Jge4->addCut(zeroCSVM);
  Lge1B0Jge4->addCut(gefourJets);

  Signature* Lge1B1Jge4 = new Signature("Lge1B1Jge4","");
  Lge1B1Jge4->addCut(geoneTightLeptons);
  Lge1B1Jge4->addCut(geoneCSVM);
  Lge1B1Jge4->addCut(gefourJets);

  handler->addSignature(Lge1B0Jge4);
  handler->addSignature(Lge1B1Jge4);

}
//-----------------------------------------------------------
void addLJJBreakdownSignatures(SignatureHandler* handler)
{
  SignatureCutN* zeroLeptonCut = new SignatureCutN("tightMuons",0,0);
  zeroLeptonCut->addProduct("tightElectrons");
  SignatureCutN* oneLeptonCut = new SignatureCutN("tightMuons",1,1);
  oneLeptonCut->addProduct("tightElectrons");
  SignatureCutN* twoLeptonCut = new SignatureCutN("tightMuons",2,2);
  twoLeptonCut->addProduct("tightElectrons");
  SignatureCutN* gethreeLeptonCut = new SignatureCutN("tightMuons",3,-1);
  gethreeLeptonCut->addProduct("tightElectrons");
  SignatureCutN* lethreeJets = new SignatureCutN("goodJets",-1,3);
  SignatureCutN* fourJets = new SignatureCutN("goodJets",4,4);
  SignatureCutN* fiveJets = new SignatureCutN("goodJets",5,5);
  SignatureCutN* gesixJets = new SignatureCutN("goodJets",6,-1);
  SignatureCutN* geoneCSVM = new SignatureCutN("bJetsCSVM",1,-1);
  SignatureCutN* zeroCSVM = new SignatureCutN("bJetsCSVM",0,0);

  SignatureCutQ* zeroLeptonChargeCut = new SignatureCutQ("tightMuons",-0.1,0.1);
  zeroLeptonChargeCut->addProduct("tightElectrons");
  SignatureCutQ* negativeLeptonChargeCut = new SignatureCutQ("tightMuons",-99,-0.1);
  negativeLeptonChargeCut->addProduct("tightElectrons");
  SignatureCutQ* positiveLeptonChargeCut = new SignatureCutQ("tightMuons",0.1,99);
  positiveLeptonChargeCut->addProduct("tightElectrons");
  SignatureCutCombined* sameSignLeptonChargeCut = new SignatureCutCombined(negativeLeptonChargeCut,positiveLeptonChargeCut,false,"same_sign_lep");
  
  //-------------------------------------------

  Signature* L0B0Jle3 = new Signature("L0B0Jle3","");
  L0B0Jle3->addCut(zeroLeptonCut);
  L0B0Jle3->addCut(zeroCSVM);
  L0B0Jle3->addCut(lethreeJets);

  Signature* L0B1Jle3 = new Signature("L0B1Jle3","");
  L0B1Jle3->addCut(zeroLeptonCut);
  L0B1Jle3->addCut(geoneCSVM);
  L0B1Jle3->addCut(lethreeJets);
  
  Signature* L1B0Jle3 = new Signature("L1B0Jle3","");
  L1B0Jle3->addCut(oneLeptonCut);
  L1B0Jle3->addCut(zeroCSVM);
  L1B0Jle3->addCut(lethreeJets);

  Signature* L1B1Jle3 = new Signature("L1B1Jle3","");
  L1B1Jle3->addCut(oneLeptonCut);
  L1B1Jle3->addCut(geoneCSVM);
  L1B1Jle3->addCut(lethreeJets);
  
  Signature* L2sameB0Jle3 = new Signature("L2sameB0Jle3","");
  L2sameB0Jle3->addCut(twoLeptonCut);
  L2sameB0Jle3->addCut(zeroLeptonChargeCut);
  L2sameB0Jle3->addCut(zeroCSVM);
  L2sameB0Jle3->addCut(lethreeJets);

  Signature* L2sameB1Jle3 = new Signature("L2sameB1Jle3","");
  L2sameB1Jle3->addCut(twoLeptonCut);
  L2sameB1Jle3->addCut(zeroLeptonChargeCut);
  L2sameB1Jle3->addCut(geoneCSVM);
  L2sameB1Jle3->addCut(lethreeJets);

  Signature* L2oppB0Jle3 = new Signature("L2oppB0Jle3","");
  L2oppB0Jle3->addCut(twoLeptonCut);
  L2oppB0Jle3->addCut(sameSignLeptonChargeCut);
  L2oppB0Jle3->addCut(zeroCSVM);
  L2oppB0Jle3->addCut(lethreeJets);

  Signature* L2oppB1Jle3 = new Signature("L2oppB1Jle3","");
  L2oppB1Jle3->addCut(twoLeptonCut);
  L2oppB1Jle3->addCut(sameSignLeptonChargeCut);
  L2oppB1Jle3->addCut(geoneCSVM);
  L2oppB1Jle3->addCut(lethreeJets);
  
  Signature* L3B0Jle3 = new Signature("L3B0Jle3","");
  L3B0Jle3->addCut(gethreeLeptonCut);
  L3B0Jle3->addCut(zeroCSVM);
  L3B0Jle3->addCut(lethreeJets);

  Signature* L3B1Jle3 = new Signature("L3B1Jle3","");
  L3B1Jle3->addCut(gethreeLeptonCut);
  L3B1Jle3->addCut(geoneCSVM);
  L3B1Jle3->addCut(lethreeJets);

  //-------------------------------------------
  Signature* L0B0J4 = new Signature("L0B0J4","");
  L0B0J4->addCut(zeroLeptonCut);
  L0B0J4->addCut(zeroCSVM);
  L0B0J4->addCut(fourJets);

  Signature* L0B1J4 = new Signature("L0B1J4","");
  L0B1J4->addCut(zeroLeptonCut);
  L0B1J4->addCut(geoneCSVM);
  L0B1J4->addCut(fourJets);
  
  Signature* L1B0J4 = new Signature("L1B0J4","");
  L1B0J4->addCut(oneLeptonCut);
  L1B0J4->addCut(zeroCSVM);
  L1B0J4->addCut(fourJets);

  Signature* L1B1J4 = new Signature("L1B1J4","");
  L1B1J4->addCut(oneLeptonCut);
  L1B1J4->addCut(geoneCSVM);
  L1B1J4->addCut(fourJets);
  
  //Signature* L2B0J4 = new Signature("L2B0J4","");
  //L2B0J4->addCut(twoLeptonCut);
  //L2B0J4->addCut(zeroCSVM);
  //L2B0J4->addCut(fourJets);

  //Signature* L2B1J4 = new Signature("L2B1J4","");
  //L2B1J4->addCut(twoLeptonCut);
  //L2B1J4->addCut(geoneCSVM);
  //L2B1J4->addCut(fourJets);

  Signature* L2sameB0J4 = new Signature("L2sameB0J4","");
  L2sameB0J4->addCut(twoLeptonCut);
  L2sameB0J4->addCut(zeroLeptonChargeCut);
  L2sameB0J4->addCut(zeroCSVM);
  L2sameB0J4->addCut(fourJets);

  Signature* L2sameB1J4 = new Signature("L2sameB1J4","");
  L2sameB1J4->addCut(twoLeptonCut);
  L2sameB1J4->addCut(zeroLeptonChargeCut);
  L2sameB1J4->addCut(geoneCSVM);
  L2sameB1J4->addCut(fourJets);

  Signature* L2oppB0J4 = new Signature("L2oppB0J4","");
  L2oppB0J4->addCut(twoLeptonCut);
  L2oppB0J4->addCut(sameSignLeptonChargeCut);
  L2oppB0J4->addCut(zeroCSVM);
  L2oppB0J4->addCut(fourJets);

  Signature* L2oppB1J4 = new Signature("L2oppB1J4","");
  L2oppB1J4->addCut(twoLeptonCut);
  L2oppB1J4->addCut(sameSignLeptonChargeCut);
  L2oppB1J4->addCut(geoneCSVM);
  L2oppB1J4->addCut(fourJets);
  
  Signature* L3B0J4 = new Signature("L3B0J4","");
  L3B0J4->addCut(gethreeLeptonCut);
  L3B0J4->addCut(zeroCSVM);
  L3B0J4->addCut(fourJets);

  Signature* L3B1J4 = new Signature("L3B1J4","");
  L3B1J4->addCut(gethreeLeptonCut);
  L3B1J4->addCut(geoneCSVM);
  L3B1J4->addCut(fourJets);
  
  //-------------------------------------------
  Signature* L0B0J5 = new Signature("L0B0J5","");
  L0B0J5->addCut(zeroLeptonCut);
  L0B0J5->addCut(zeroCSVM);
  L0B0J5->addCut(fiveJets);

  Signature* L0B1J5 = new Signature("L0B1J5","");
  L0B1J5->addCut(zeroLeptonCut);
  L0B1J5->addCut(geoneCSVM);
  L0B1J5->addCut(fiveJets);
  
  Signature* L1B0J5 = new Signature("L1B0J5","");
  L1B0J5->addCut(oneLeptonCut);
  L1B0J5->addCut(zeroCSVM);
  L1B0J5->addCut(fiveJets);

  Signature* L1B1J5 = new Signature("L1B1J5","");
  L1B1J5->addCut(oneLeptonCut);
  L1B1J5->addCut(geoneCSVM);
  L1B1J5->addCut(fiveJets);

  Signature* L2sameB0J5 = new Signature("L2sameB0J5","");
  L2sameB0J5->addCut(twoLeptonCut);
  L2sameB0J5->addCut(zeroLeptonChargeCut);
  L2sameB0J5->addCut(zeroCSVM);
  L2sameB0J5->addCut(fiveJets);

  Signature* L2sameB1J5 = new Signature("L2sameB1J5","");
  L2sameB1J5->addCut(twoLeptonCut);
  L2sameB1J5->addCut(zeroLeptonChargeCut);
  L2sameB1J5->addCut(geoneCSVM);
  L2sameB1J5->addCut(fiveJets);

  Signature* L2oppB0J5 = new Signature("L2oppB0J5","");
  L2oppB0J5->addCut(twoLeptonCut);
  L2oppB0J5->addCut(sameSignLeptonChargeCut);
  L2oppB0J5->addCut(zeroCSVM);
  L2oppB0J5->addCut(fiveJets);

  Signature* L2oppB1J5 = new Signature("L2oppB1J5","");
  L2oppB1J5->addCut(twoLeptonCut);
  L2oppB1J5->addCut(sameSignLeptonChargeCut);
  L2oppB1J5->addCut(geoneCSVM);
  L2oppB1J5->addCut(fiveJets);
  
  Signature* L3B0J5 = new Signature("L3B0J5","");
  L3B0J5->addCut(gethreeLeptonCut);
  L3B0J5->addCut(zeroCSVM);
  L3B0J5->addCut(fiveJets);

  Signature* L3B1J5 = new Signature("L3B1J5","");
  L3B1J5->addCut(gethreeLeptonCut);
  L3B1J5->addCut(geoneCSVM);
  L3B1J5->addCut(fiveJets);
  
  //-------------------------------------------
  Signature* L0B0Jge6 = new Signature("L0B0Jge6","");
  L0B0Jge6->addCut(zeroLeptonCut);
  L0B0Jge6->addCut(zeroCSVM);
  L0B0Jge6->addCut(gesixJets);

  Signature* L0B1Jge6 = new Signature("L0B1Jge6","");
  L0B1Jge6->addCut(zeroLeptonCut);
  L0B1Jge6->addCut(geoneCSVM);
  L0B1Jge6->addCut(gesixJets);
  
  Signature* L1B0Jge6 = new Signature("L1B0Jge6","");
  L1B0Jge6->addCut(oneLeptonCut);
  L1B0Jge6->addCut(zeroCSVM);
  L1B0Jge6->addCut(gesixJets);

  Signature* L1B1Jge6 = new Signature("L1B1Jge6","");
  L1B1Jge6->addCut(oneLeptonCut);
  L1B1Jge6->addCut(geoneCSVM);
  L1B1Jge6->addCut(gesixJets);

  Signature* L2sameB0Jge6 = new Signature("L2sameB0Jge6","");
  L2sameB0Jge6->addCut(twoLeptonCut);
  L2sameB0Jge6->addCut(zeroLeptonChargeCut);
  L2sameB0Jge6->addCut(zeroCSVM);
  L2sameB0Jge6->addCut(gesixJets);

  Signature* L2sameB1Jge6 = new Signature("L2sameB1Jge6","");
  L2sameB1Jge6->addCut(twoLeptonCut);
  L2sameB1Jge6->addCut(zeroLeptonChargeCut);
  L2sameB1Jge6->addCut(geoneCSVM);
  L2sameB1Jge6->addCut(gesixJets);

  Signature* L2oppB0Jge6 = new Signature("L2oppB0Jge6","");
  L2oppB0Jge6->addCut(twoLeptonCut);
  L2oppB0Jge6->addCut(sameSignLeptonChargeCut);
  L2oppB0Jge6->addCut(zeroCSVM);
  L2oppB0Jge6->addCut(gesixJets);

  Signature* L2oppB1Jge6 = new Signature("L2oppB1Jge6","");
  L2oppB1Jge6->addCut(twoLeptonCut);
  L2oppB1Jge6->addCut(sameSignLeptonChargeCut);
  L2oppB1Jge6->addCut(geoneCSVM);
  L2oppB1Jge6->addCut(gesixJets);
  
  Signature* L3B0Jge6 = new Signature("L3B0Jge6","");
  L3B0Jge6->addCut(gethreeLeptonCut);
  L3B0Jge6->addCut(zeroCSVM);
  L3B0Jge6->addCut(gesixJets);

  Signature* L3B1Jge6 = new Signature("L3B1Jge6","");
  L3B1Jge6->addCut(gethreeLeptonCut);
  L3B1Jge6->addCut(geoneCSVM);
  L3B1Jge6->addCut(gesixJets);

  //-------------------------------------------
  
  handler->addSignature(L0B0Jle3);
  handler->addSignature(L0B1Jle3);
  handler->addSignature(L1B0Jle3);
  handler->addSignature(L1B1Jle3);
  handler->addSignature(L2sameB0Jle3);
  handler->addSignature(L2sameB1Jle3);
  handler->addSignature(L2oppB0Jle3);
  handler->addSignature(L2oppB1Jle3);
  handler->addSignature(L3B0Jle3);
  handler->addSignature(L3B1Jle3);
  
  handler->addSignature(L0B0J4);
  handler->addSignature(L0B1J4);
  handler->addSignature(L1B0J4);
  handler->addSignature(L1B1J4);
  handler->addSignature(L2sameB0J4);
  handler->addSignature(L2sameB1J4);
  handler->addSignature(L2oppB0J4);
  handler->addSignature(L2oppB1J4);
  handler->addSignature(L3B0J4);
  handler->addSignature(L3B1J4);

  handler->addSignature(L0B0J5);
  handler->addSignature(L0B1J5);
  handler->addSignature(L1B0J5);
  handler->addSignature(L1B1J5);
  handler->addSignature(L2sameB0J5);
  handler->addSignature(L2sameB1J5);
  handler->addSignature(L2oppB0J5);
  handler->addSignature(L2oppB1J5);
  handler->addSignature(L3B0J5);
  handler->addSignature(L3B1J5);

  handler->addSignature(L0B0Jge6);
  handler->addSignature(L0B1Jge6);
  handler->addSignature(L1B0Jge6);
  handler->addSignature(L1B1Jge6);
  handler->addSignature(L2sameB0Jge6);
  handler->addSignature(L2sameB1Jge6);
  handler->addSignature(L2oppB0Jge6);
  handler->addSignature(L2oppB1Jge6);
  handler->addSignature(L3B0Jge6);
  handler->addSignature(L3B1Jge6);

}
