void setupEWKinoProducts(SignatureHandler* handler){

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

  handler->addProduct("bJetsCSVM","goodJets");
  handler->addProductCut("bJetsCSVM",new ObjectCutJetBDiscPositive);

  ObjectCutPt* tauPtCut = new ObjectCutPt(20.0,-1,"tauptcut");
  ObjectCutCombined* tauChargeCut = new ObjectCutCombined(new ObjectCutTauCharge(-1.1,-0.9),new ObjectCutTauCharge(0.9,1.1));

  handler->addTauCut(tauPtCut);
  handler->addTauCut(new ObjectCutEta(2.3));
  handler->addTauCut(new ObjectCutTauDiscriminants(19));//decaymodefinding
  handler->addTauCut(new ObjectCutTauDiscriminants(29));//againstelectronmva
  handler->addTauCut(new ObjectCutTauDiscriminants(24));//againstmuontight
  handler->addTauCut(new ObjectCutTauDiscriminants(26));//byloosecombinedisodbsumptcorr
  handler->addTauCut(tauChargeCut);


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
  handler->setSelfSeparate("goodTaus",0.1);
  handler->setSelfSeparate("goodIsoTracks",0.005);
  handler->addProductSeparation("goodElectrons","goodMuons",0.1);
  handler->addProductSeparation("goodTaus","goodMuons",0.1);
  handler->addProductSeparation("goodTaus","goodElectrons",0.1);
  handler->addProductSeparation("goodJets","goodMuons",0.4);
  handler->addProductSeparation("goodJets","goodElectrons",0.4);
  handler->addProductSeparation("goodJets","goodTaus",0.4);
  handler->addProductSeparation("goodPhotons","goodMuons",0.1);
  handler->addProductSeparation("goodPhotons","goodElectrons",0.1);
  handler->addProductSeparation("goodPhotons","goodTaus",0.1);
  handler->addProductSeparation("goodPhotons","goodJets",0.3);

  handler->addProduct("leadingJet","goodJets");
  handler->setSelfSeparate("leadingJet",10000.0);

  handler->addProduct("nonIsoElectrons","allElectrons");
  handler->addProductCut("nonIsoElectrons",goodElectronCut);
  handler->addProductCut("nonIsoElectrons",promptLeptonCut);
  handler->addProductCut("nonIsoElectrons",nonIsolatedLeptonCut);

  handler->addProduct("nonIsoMuons","allMuons");
  handler->addProductCut("nonIsoMuons",goodMuonCut);
  handler->addProductCut("nonIsoMuons",promptMuonCut);
  handler->addProductCut("nonIsoMuons",nonIsolatedLeptonCut);

  handler->addProduct("nonIsoTracks","allRecoTracks");
  handler->addProductCut("nonIsoTracks",new ObjectCutValidTrackerHits(11));
  handler->addProductCut("nonIsoTracks",new ObjectCutBeamD0(0.20));
  handler->addProductCut("nonIsoTracks",new ObjectCutVertDz(1.0));
  handler->addProductCut("nonIsoTracks",leptonEtaCut);
  handler->addProductCut("nonIsoTracks",new ObjectCutPt(8.0,-1,"trackPtCut"));
  handler->addProductCut("nonIsoTracks",new ObjectCutIrel(0.2,1.0));

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

}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
void setupEWKinoTriggers(SignatureHandler* handler, int mode = 0)
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
  //doubleElectronThreshold->addThreshold(10.0);
  SignatureCutThresholdMuon* singleMuonThreshold = new SignatureCutThresholdMuon("singleMuonThreshold");
  singleMuonThreshold->addThreshold(35.0);
  SignatureCutThresholdMuon* doubleMuonThreshold = new SignatureCutThresholdMuon("doubleMuonThreshold");
  doubleMuonThreshold->addThreshold(20.0);
  //doubleMuonThreshold->addThreshold(10.0);

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

  //SignatureCutCombined* muEG_threshold = new SignatureCutCombined(muEG_threshold_electron_lead,muEG_threshold_muon_lead,false,"mueg_thresh");
  SignatureCutCombined* muEG_threshold = new SignatureCutCombined(doubleMuonThreshold,doubleElectronThreshold,false,"mueg_thresh");

  triggerCut->addCut("MuEG",muEG_threshold);
  triggerCut->addCut("DoubleMuon",doubleMuonThreshold);
  triggerCut->addCut("DoubleElectron",doubleElectronThreshold);
  triggerCut->addCut("SingleMuon",singleMuonThreshold);
  triggerCut->addCut("SingleElectron",singleElectronThreshold);

  switch(mode){
    case 1:
      addAcceptTriggers(triggerCut,"MuEG",getEWKinoMuonElectronTriggers());
      break;
    case 2:
      addAcceptTriggers(triggerCut,"DoubleMuon",getEWKinoDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getEWKinoMuonElectronTriggers());
      break;
    case 3:
      addAcceptTriggers(triggerCut,"DoubleElectron",getEWKinoDoubleElectronTriggers());
      addVetoTriggers(triggerCut,"DoubleMuon",getEWKinoDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getEWKinoMuonElectronTriggers());
      break;
    case 4:
      addAcceptTriggers(triggerCut,"SingleMuon",getSingleMuonTriggers());//changed geSingleMuonTriggers to getSingleMuonTriggers
      addVetoTriggers(triggerCut,"DoubleElectron",getEWKinoDoubleElectronTriggers());
      addVetoTriggers(triggerCut,"DoubleMuon",getEWKinoDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getEWKinoMuonElectronTriggers());
      break;
    case 5:
      addAcceptTriggers(triggerCut,"SingleElectron",getSingleElectronTriggers());//same here
      addVetoTriggers(triggerCut,"SingleMuon",getSingleMuonTriggers());//same here
      addVetoTriggers(triggerCut,"DoubleElectron",getEWKinoDoubleElectronTriggers());
      addVetoTriggers(triggerCut,"DoubleMuon",getEWKinoDoubleMuonTriggers());
      addVetoTriggers(triggerCut,"MuEG",getEWKinoMuonElectronTriggers());
      break;

  default:
    break;
  }
  handler->addHandlerCut(triggerCut);

}
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
//-------------------------------------------------
void setupEWKinoSignatures(SignatureHandler* handler)
{
  SignatureCutN* zeroBjetCut = new SignatureCutN("bJetsCSVM",0,0);

  handler->addHandlerCut(zeroBjetCut);

  SignatureCutPairMass* dyBelow12 = new SignatureCutPairMass("goodElectrons",0,12,true,0,2,"dybelow12cut");
  dyBelow12->addProduct("goodMuons");
  handler->addHandlerCut(new SignatureCutReversed(dyBelow12));

  SignatureCutMT* lowMTCut = new SignatureCutMT(0,120,"lowMTCut");
  SignatureCutMT* midMTCut = new SignatureCutMT(120,160,"midMTCut");
  SignatureCutMT* highMTCut = new SignatureCutMT(160,-1,"highMTCut");

  SignatureCutMET* metCut0 = new SignatureCutMET(0,50,"metCut0");
  SignatureCutMET* metCut1 = new SignatureCutMET(50,100,"metCut1");
  SignatureCutMET* metCut2 = new SignatureCutMET(100,150,"metCut2");
  SignatureCutMET* metCut3 = new SignatureCutMET(150,200,"metCut3");
  SignatureCutMET* metCut4 = new SignatureCutMET(200,-1,"metCut4");
  SignatureCutMET* metCut5 = new SignatureCutMET(250,-1,"metCut5");
  SignatureCutMET* metCutFull = new SignatureCutMET(0,-1,"metCutFul");

  SignatureCutMll* lowMllCut = new SignatureCutMll(12,75,"lowMllCut");
  SignatureCutMll* highMllCut = new SignatureCutMll(105,-1,"highMllCut");
  SignatureCutMll* lowOFMllCut = new SignatureCutMll(12,100,"lowOFMllCut");
  SignatureCutMll* highOFMllCut = new SignatureCutMll(100,-1,"highOFMllCut");

  SignatureCutN* zeroElectrons = new SignatureCutN("goodElectrons",0,0);
  SignatureCutN* oneElectrons = new SignatureCutN("goodElectrons",1,1);
  SignatureCutN* twoElectrons = new SignatureCutN("goodElectrons",2,2);
  SignatureCutN* threeElectrons = new SignatureCutN("goodElectrons",3,3);
  SignatureCutN* fourElectrons = new SignatureCutN("goodElectrons",4,4);

  SignatureCutN* zeroMuons = new SignatureCutN("goodMuons",0,0);
  SignatureCutN* oneMuons = new SignatureCutN("goodMuons",1,1);
  SignatureCutN* twoMuons = new SignatureCutN("goodMuons",2,2);
  SignatureCutN* threeMuons = new SignatureCutN("goodMuons",3,3);
  SignatureCutN* fourMuons = new SignatureCutN("goodMuons",4,4);

  SignatureCutN* zeroTaus = new SignatureCutN("goodTaus",0,0);
  SignatureCutN* oneTaus = new SignatureCutN("goodTaus",1,1);
  SignatureCutN* twoTaus = new SignatureCutN("goodTaus",2,2);
  SignatureCutN* threeTaus = new SignatureCutN("goodTaus",3,3);
  SignatureCutN* fourTaus = new SignatureCutN("goodTaus",4,4);

  SignatureCutN* zeroSSelectrons = new SignatureCutN("goodSSElectrons",0,0);
  SignatureCutN* oneSSelectrons = new SignatureCutN("goodSSElectrons",1,1);
  SignatureCutN* twoSSelectrons = new SignatureCutN("goodSSElectrons",2,2);

  SignatureCutNDYPairs* dy1offZcut = new SignatureCutNDYPairs(1,1,false);
  SignatureCutNDYPairs* dy1onZcut = new SignatureCutNDYPairs(1,1,true);
  SignatureCutNDYPairs* dy2offZcut = new SignatureCutNDYPairs(2,-1,false);
  SignatureCutNDYPairs* dy2onZcut = new SignatureCutNDYPairs(2,-1,true);
  SignatureCutNDYPairs* dy0cut = new SignatureCutNDYPairs(0,0,false);

  SignatureCutQ* zeroChargeCut = new SignatureCutQ("goodElectrons",-0.1,0.1);
  zeroChargeCut->addProductName("goodMuons");
  SignatureCutReversed* nonZeroChargeCut = new SignatureCutReversed(zeroChargeCut);

  SignatureCut* met_cuts[7] = {metCut0,metCut1,metCut2,metCut3,metCut4,metCut5,metCutFull};
  TString met_labels[7] = {"MET0to50","MET50to100","MET100to150","MET150to200","METgt200","METgt250","METFULL"};
  SignatureCut* mt_cuts[3] = {lowMTCut,midMTCut,highMTCut};
  TString mt_labels[3] = {"MT0to120","MT120to160","MTgt160"};

  SignatureCut* NOSSFMASS_cuts[5];
  NOSSFMASS_cuts[0] = new SignatureCutCombined(dy0cut,lowOFMllCut,true);
  NOSSFMASS_cuts[1] = new SignatureCutCombined(dy0cut,highOFMllCut,true);
  NOSSFMASS_cuts[2] = new SignatureCutCombined(dy1offZcut,lowMllCut,true);
  NOSSFMASS_cuts[3] = dy1onZcut;
  NOSSFMASS_cuts[4] = new SignatureCutCombined(dy1offZcut,highMllCut,true);
  TString NOSSFMASS_labels[5] = {"OSSF0lowM","OSSF0highM","OSSF1lowM","OSSF1onZ","OSSF1highM"};

  TString L4OSSF_labels[5] = {"OSSF0","OSSF1offZ","OSSF1onZ","OSSF2offZ","OSSF2onZ"};
  SignatureCut* L4OSSF_cuts[5];
  L4OSSF_cuts[0] = dy0cut;
  L4OSSF_cuts[1] = dy1offZcut;
  L4OSSF_cuts[2] = dy1onZcut;
  L4OSSF_cuts[3] = dy2offZcut;
  L4OSSF_cuts[4] = dy2onZcut;

  Signature* baseT0[4];
  baseT0[0] = new Signature("Mu3El0Tau0","");
  baseT0[0]->addCut(zeroTaus);
  baseT0[0]->addCut(threeMuons);
  baseT0[0]->addCut(zeroElectrons);
  baseT0[1] = new Signature("Mu2El1Tau0","");
  baseT0[1]->addCut(zeroTaus);
  baseT0[1]->addCut(twoMuons);
  baseT0[1]->addCut(oneElectrons);
  baseT0[2] = new Signature("Mu1El2Tau0","");
  baseT0[2]->addCut(zeroTaus);
  baseT0[2]->addCut(oneMuons);
  baseT0[2]->addCut(twoElectrons);
  baseT0[3] = new Signature("Mu0El3Tau0","");
  baseT0[3]->addCut(zeroTaus);
  baseT0[3]->addCut(zeroMuons);
  baseT0[3]->addCut(threeElectrons);

  Signature* baseT1[3];
  baseT1[0] = new Signature("Mu2El0Tau1","");
  baseT1[0]->addCut(oneTaus);
  baseT1[0]->addCut(twoMuons);
  baseT1[0]->addCut(zeroElectrons);
  baseT1[1] = new Signature("Mu1El1Tau1","");
  baseT1[1]->addCut(oneTaus);
  baseT1[1]->addCut(oneMuons);
  baseT1[1]->addCut(oneElectrons);
  baseT1[2] = new Signature("Mu0El2Tau1","");
  baseT1[2]->addCut(oneTaus);
  baseT1[2]->addCut(zeroMuons);
  baseT1[2]->addCut(twoElectrons);

  Signature* base4lT0[5];
  base4lT0[0] = new Signature("Mu4El0Tau0","");
  base4lT0[0]->addCut(zeroTaus);
  base4lT0[0]->addCut(fourMuons);
  base4lT0[0]->addCut(zeroElectrons);
  base4lT0[1] = new Signature("Mu3El1Tau0","");
  base4lT0[1]->addCut(zeroTaus);
  base4lT0[1]->addCut(threeMuons);
  base4lT0[1]->addCut(oneElectrons);
  base4lT0[2] = new Signature("Mu2El2Tau0","");
  base4lT0[2]->addCut(zeroTaus);
  base4lT0[2]->addCut(twoMuons);
  base4lT0[2]->addCut(twoElectrons);
  base4lT0[3] = new Signature("Mu1El3Tau0","");
  base4lT0[3]->addCut(zeroTaus);
  base4lT0[3]->addCut(oneMuons);
  base4lT0[3]->addCut(threeElectrons);
  base4lT0[4] = new Signature("Mu0El4Tau0","");
  base4lT0[4]->addCut(zeroTaus);
  base4lT0[4]->addCut(zeroMuons);
  base4lT0[4]->addCut(fourElectrons);

  Signature* base4lT1[5];
  base4lT1[0] = new Signature("Mu3El0Tau1","");
  base4lT1[0]->addCut(oneTaus);
  base4lT1[0]->addCut(threeMuons);
  base4lT1[0]->addCut(zeroElectrons);
  base4lT1[1] = new Signature("Mu2El1Tau1","");
  base4lT1[1]->addCut(oneTaus);
  base4lT1[1]->addCut(twoMuons);
  base4lT1[1]->addCut(oneElectrons);
  base4lT1[2] = new Signature("Mu1El2Tau1","");
  base4lT1[2]->addCut(oneTaus);
  base4lT1[2]->addCut(oneMuons);
  base4lT1[2]->addCut(twoElectrons);
  base4lT1[3] = new Signature("Mu0El3Tau1","");
  base4lT1[3]->addCut(oneTaus);
  base4lT1[3]->addCut(zeroMuons);
  base4lT1[3]->addCut(threeElectrons);

  for(int met = 0; met < 7; met++){
    for(int nossf = 0; nossf < 5; nossf++){
      TString extratag = L4OSSF_labels[nossf]+met_labels[met];
      for(int i = 0; i < 5; i++){
	  Signature* nsig = new Signature(*base4lT0[i]);
	  nsig->setName(TString(base4lT0[i]->getName()+extratag));
	  nsig->addCut(met_cuts[met]);
	  nsig->addCut(L4OSSF_cuts[nossf]);
	  handler->addSignature(nsig);
	}
      if(nossf > 2) continue;
      for(int i = 0; i < 4; i++){
	Signature* nsig = new Signature(*base4lT1[i]);
	nsig->setName(TString(base4lT1[i]->getName()+extratag));
	nsig->addCut(met_cuts[met]);
	nsig->addCut(L4OSSF_cuts[nossf]);
	handler->addSignature(nsig);
      }
    }
  }


  for(int mt = 0; mt < 3; mt++){
    for(int met = 0; met < 7; met++){
      for(int nossf = 0; nossf < 5; nossf++){
	TString extratag = mt_labels[mt]+NOSSFMASS_labels[nossf]+met_labels[met];
	for(int i = 0; i < 4; i++){
	  Signature* nsig = new Signature(*baseT0[i]);
	  nsig->setName(TString(baseT0[i]->getName()+extratag));
	  nsig->addCut(met_cuts[met]);
	  nsig->addCut(mt_cuts[mt]);
	  nsig->addCut(NOSSFMASS_cuts[nossf]);
	  handler->addSignature(nsig);
	}
	for(int i = 0; i < 3; i++){
	  Signature* nsig = new Signature(*baseT1[i]);
	  nsig->setName(TString(baseT1[i]->getName()+extratag));
	  nsig->addCut(met_cuts[met]);
	  nsig->addCut(mt_cuts[mt]);
	  nsig->addCut(NOSSFMASS_cuts[nossf]);
	  if(i == 2 && nossf < 2){
	    nsig->addCut(twoSSelectrons);
	  }
	  if(i == 1 && nossf < 2){
	    nsig->setName(TString(baseT1[i]->getName()+"OS"+extratag));
	    Signature* nsig2 = new Signature(*nsig);
	    nsig2->setName(TString(baseT1[i]->getName()+"SS"+extratag));
	    nsig2->addCut(nonZeroChargeCut);
	    nsig2->addCut(oneSSelectrons);
	    nsig->addCut(zeroChargeCut);
	    handler->addSignature(nsig2);
	  }
	  handler->addSignature(nsig);
	}
      }
    }
  }
}
///-----------------------------------------------
///-----------------------------------------------
///-----------------------------------------------
///-----------------------------------------------
///-----------------------------------------------
///-----------------------------------------------
///-----------------------------------------------
///-----------------------------------------------
vector<int> getEWKinoDoubleMuonTriggers()
{
  vector<int> m_doubleMuTriggerList;
  //m_doubleMuTriggerList.push_back(174);//("HLT_Mu13_Mu8_v16"); //174
 m_doubleMuTriggerList.push_back(175);//("HLT_Mu17_Mu8_v16"); //175
 //m_doubleMuTriggerList.push_back(176);//("HLT_Mu17_TkMu8_v9"); //176
 //m_doubleMuTriggerList.push_back(177);//("HLT_Mu22_TkMu8_v4"); //177
 //m_doubleMuTriggerList.push_back(178);//("HLT_Mu22_TkMu22_v4"); //178
 // added on 30th April 
 //added on 19th May 2012
 //m_doubleMuTriggerList.push_back(1144);// m_known_triggers.push_back("HLT_Mu13_Mu8_v17"); //1144
 m_doubleMuTriggerList.push_back(1145);// m_known_triggers.push_back("HLT_Mu17_Mu8_v17"); //1145
 //m_doubleMuTriggerList.push_back(1146);//m_known_triggers.push_back("HLT_Mu17_TkMu8_v10"); //1146
 //m_doubleMuTriggerList.push_back(1147);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v5"); //1147
 //m_doubleMuTriggerList.push_back(1148);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v5"); //1148
  // added on 26th May
  //m_doubleMuTriggerList.push_back(1248);//m_known_triggers.push_back("HLT_Mu22_TkMu8_v6"); //1248
  //m_doubleMuTriggerList.push_back(1249);//m_known_triggers.push_back("HLT_Mu22_TkMu22_v6"); //1249

  //m_doubleMuTriggerList.push_back(1334);//m_known_triggers.push_back("HLT_Mu13_Mu8_v18"); //1334
  m_doubleMuTriggerList.push_back(1335);// m_known_triggers.push_back("HLT_Mu17_Mu8_v18"); //1335
  //m_doubleMuTriggerList.push_back(1336);// m_known_triggers.push_back("HLT_Mu17_TkMu8_v11"); //1336

  //m_doubleMuTriggerList.push_back(1522);
  m_doubleMuTriggerList.push_back(1523);
  //m_doubleMuTriggerList.push_back(1524);
  //m_doubleMuTriggerList.push_back(1525);
  //m_doubleMuTriggerList.push_back(1526);
  m_doubleMuTriggerList.push_back(1929);
  return m_doubleMuTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getEWKinoDoubleElectronTriggers()
{
  vector<int> m_doubleElTriggerList;
  m_doubleElTriggerList.push_back(243);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v15"); //243
  //m_doubleElTriggerList.push_back(248);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v4"); //248
  //m_doubleElTriggerList.push_back(259);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v9"); //259
  //m_doubleElTriggerList.push_back(260);//("HLT_DoubleEle33_CaloIdL_v11"); //260
  //m_doubleElTriggerList.push_back(261);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v3"); //261
  //m_doubleElTriggerList.push_back(262);//("HLT_DoubleEle33_CaloIdT_v7"); //262

  //Added 20th April
  m_doubleElTriggerList.push_back(625);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v16"); //625
  //m_doubleElTriggerList.push_back(630);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v5"); //630
  //m_doubleElTriggerList.push_back(641);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v10"); //641
  //m_doubleElTriggerList.push_back(642);// m_known_triggers.push_back("HLT_DoubleEle33_CaloIdL_v12"); //642
  //m_doubleElTriggerList.push_back(643);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v4"); //643
  //m_doubleElTriggerList.push_back(644);//("HLT_DoubleEle33_CaloIdT_v8"); //644
  // added on 30th April 
  m_doubleElTriggerList.push_back(914);//("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v17"); //914
  //m_doubleElTriggerList.push_back(919);//("HLT_Ele27_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele15_CaloIdT_CaloIsoVL_trackless_v6"); //919
  //m_doubleElTriggerList.push_back(930);//("HLT_DoubleEle8_CaloIdT_TrkIdVL_v11"); //930
  //m_doubleElTriggerList.push_back(931);//("HLT_DoubleEle33_CaloIdL_v13"); //931
  //m_doubleElTriggerList.push_back(932);//("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v5"); //932
  //m_doubleElTriggerList.push_back(933);//("HLT_DoubleEle33_CaloIdT_v9"); //933
  // added on 19 May
  //m_doubleElTriggerList.push_back(1164);// m_known_triggers.push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v6"); //1164

 m_doubleElTriggerList.push_back(1592);
 //m_doubleElTriggerList.push_back(1593);
 //m_doubleElTriggerList.push_back(1597);
 //m_doubleElTriggerList.push_back(1610);
 //m_doubleElTriggerList.push_back(1611);
 //m_doubleElTriggerList.push_back(1612);
 //m_doubleElTriggerList.push_back(1613);
  return m_doubleElTriggerList;
}
//--------------------------------
//--------------------------------
vector<int> getEWKinoMuonElectronTriggers()
{
  vector<int> m_muElTriggerList;
  //m_muElTriggerList.push_back(277);//m_known_triggers.push_back("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v3"); //277
 m_muElTriggerList.push_back(278);//m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //278
 m_muElTriggerList.push_back(310);//m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v4"); //310 
 //m_muElTriggerList.push_back(318);//("HLT_Mu30_Ele30_CaloIdL_v3"); //318

// Added 20th April
 //m_muElTriggerList.push_back(659);//("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v4"); //659
  m_muElTriggerList.push_back(660);//("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //660
  m_muElTriggerList.push_back(691);//("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v5"); //691
  // m_muElTriggerList.push_back(699);// m_muElTriggerListpush_back(310);//("HLT_Mu30_Ele30_CaloIdL_v4"); //699

 // added on 30th April 
  //m_muElTriggerList.push_back(943); //("HLT_Mu7_Ele7_CaloIdT_CaloIsoVL_v5"); //943
m_muElTriggerList.push_back(944); //("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //944
m_muElTriggerList.push_back(971); //("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"); //971
//m_muElTriggerList.push_back(972); //("HLT_Mu30_Ele30_CaloIdL_v5"); //972

// added on 19 th may
 m_muElTriggerList.push_back(1174); //m_known_triggers.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1174
 m_muElTriggerList.push_back(1195); //m_known_triggers.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"); //1195
 // m_muElTriggerList.push_back(1196); //m_known_triggers.push_back("HLT_Mu30_Ele30_CaloIdL_v6"); //1196

 //m_muElTriggerList.push_back(1629);
 m_muElTriggerList.push_back(1630);
 m_muElTriggerList.push_back(1653);
 //m_muElTriggerList.push_back(1661);
 m_muElTriggerList.push_back(1968);
 m_muElTriggerList.push_back(1989);
  return m_muElTriggerList;
}
