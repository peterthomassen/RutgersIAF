#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

//-----------------------------------------
void SignatureHandler::readMuons()
{
  for(int i = 0; i < pat_muon_n; i++){
    int gtID = pat_muon_globalTrackID[i];
    if(gtID < 0)continue;
    SignatureObjectMuon* muon = new SignatureObjectMuon(pat_muon_px[i],pat_muon_py[i],pat_muon_pz[i],pat_muon_energy[i]);
    muon->setRho(pat_rho);
    muon->setChargedHadronIso(pat_muon_PF_chargedHadronIso[i]);
    muon->setNeutralHadronIso(pat_muon_PF_neutralHadronIso[i]);
    muon->setPhotonIso(pat_muon_PF_photonIso[i]);

    muon->setDz(reco_track_dz[gtID]);
    muon->setGenParticle_ntID(reco_track_genParticle_ntID[gtID]);
    muon->setCaloIso9(reco_track_caloIso9[gtID]);
    muon->setDxy(reco_track_dxy[gtID]);
    muon->setNValidMuonHits(reco_track_nValidMuonHits[gtID]);
    muon->setCaloIso2(reco_track_caloIso2[gtID]);
    muon->setVert_dxy(pat_muon_innerVertDxy[i]);
    muon->setCharge(reco_track_charge[gtID]);
    muon->setCaloIso1(reco_track_caloIso1[gtID]);
    muon->setIsGlobal(reco_track_isGlobal[gtID]);
    muon->setBeam_dsz(reco_track_beam_dsz[gtID]);
    muon->setNLostPixelHits(reco_track_nLostPixelHits[gtID]);
    muon->setNpixelLayersWM(reco_track_npixelLayersWM[gtID]);
    muon->setVx(reco_track_vx[gtID]);
    muon->setVy(reco_track_vy[gtID]);
    muon->setLambdaError(reco_track_lambdaError[gtID]);
    muon->setPF_chargedHadronIso(reco_track_PF_chargedHadronIso[gtID]);
    muon->setNValidPixelHits(reco_track_nValidPixelHits[gtID]);
    muon->setVz(reco_track_vz[gtID]);
    muon->setD0(reco_track_d0[gtID]);
    muon->setGenParticle_mother_ntID(reco_track_genParticle_mother_ntID[gtID]);
    muon->setDsz(reco_track_dsz[gtID]);
    muon->setNValidTrackerHits(reco_track_nValidTrackerHits[gtID]);
    muon->setNBadMuonHitsInFirstStation(reco_track_nBadMuonHitsInFirstStation[gtID]);
    muon->setThetaError(reco_track_thetaError[gtID]);
    muon->setVert_dz(reco_track_vert_dz[gtID]);
    muon->setPF_photonIso(reco_track_PF_photonIso[gtID]);
    muon->setOutermostMuonStationWithValidHits(reco_track_outermostMuonStationWithValidHits[gtID]);
    muon->setPhiError(reco_track_phiError[gtID]);
    muon->setNAnyMuonHitsInFirstStation(reco_track_nAnyMuonHitsInFirstStation[gtID]);
    muon->setTrackIso6(reco_track_trackIso6[gtID]);
    muon->setNtrackerLayersWM(reco_track_ntrackerLayersWM[gtID]);
    muon->setTrackIso2(reco_track_trackIso2[gtID]);
    muon->setTheta(reco_track_theta[gtID]);
    muon->setNLostTrackerHits(reco_track_nLostTrackerHits[gtID]);
    muon->setIsMuon(reco_track_isMuon[gtID]);
    muon->setTrackIso9(reco_track_trackIso9[gtID]);
    muon->setD0Error(reco_track_d0Error[gtID]);
    muon->setTrackIso1(reco_track_trackIso1[gtID]);
    muon->setNBadMuonHits(reco_track_nBadMuonHits[gtID]);
    muon->setChi2(reco_track_chi2[gtID]);
    muon->setCaloIso6(reco_track_caloIso6[gtID]);
    muon->setEtaError(reco_track_etaError[gtID]);
    muon->setTrackIso12(reco_track_trackIso12[gtID]);
    muon->setNdof(reco_track_ndof[gtID]);
    muon->setNstripLayersWM(reco_track_nstripLayersWM[gtID]);
    muon->setBeam_dz(reco_track_beam_dz[gtID]);
    muon->setIsTracker(reco_track_isTracker[gtID]);
    muon->setNValidHits(reco_track_nValidHits[gtID]);
    muon->setDzError(reco_track_dzError[gtID]);
    muon->setNValidMuonHitsInFirstStation(reco_track_nValidMuonHitsInFirstStation[gtID]);
    muon->setDxyError(reco_track_dxyError[gtID]);
    muon->setGenParticle_mother_pdgID(reco_track_genParticle_mother_pdgID[gtID]);
    muon->setGenParticle_dR(reco_track_genParticle_dR[gtID]);
    muon->setPF_neutralHadronIso(reco_track_PF_neutralHadronIso[gtID]);
    muon->setNLostMuonHitsInFirstStation(reco_track_nLostMuonHitsInFirstStation[gtID]);
    muon->setGenParticle_pdgID(reco_track_genParticle_pdgID[gtID]);
    muon->setBeam_dxy(reco_track_beam_dxy[gtID]);
    muon->setCaloIso12(reco_track_caloIso12[gtID]);
    muon->setMuonStationsWAH(reco_track_muonStationsWAH[gtID]);
    muon->setNLostMuonHits(reco_track_nLostMuonHits[gtID]);
    muon->setNLostHits(reco_track_nLostHits[gtID]);
    muon->setMuonStationsWVH(reco_track_muonStationsWVH[gtID]);
    muon->setBeam_d0(reco_track_beam_d0[gtID]);
    muon->setVertWeight(reco_track_vertWeight[gtID]);
    muon->setIsGlobalMuon(pat_muon_isGlobalMuon[i]);
    muon->setEcaloIso(pat_muon_ecaloIso[i]);//###
    muon->setGlobalTrackID(pat_muon_globalTrackID[i]);
    muon->setDRmin10(pat_muon_dRmin10[i]);
    muon->setTrackID(pat_muon_trackID[i]);
    muon->setTrackIso(pat_muon_trackIso[i]);//###
    muon->setPFMatchPdgId(pat_muon_PFMatchPdgId[i]);
    muon->setIsTMLastStationAngTight(pat_muon_isTMLastStationAngTight[i]);
    muon->setPFPAT_dq(pat_muon_PFPAT_dq[i]);
    muon->setIsPF(pat_muon_isPF[i]);
    muon->setHcalIsoDep(pat_muon_hcalIsoDep[i]);
    muon->setPFPAT_deta(pat_muon_PFPAT_deta[i]);
    muon->setDirection(pat_muon_Direction[i]);
    muon->setVertTrackIso(pat_muon_vertTrackIso[i]);
    muon->setPF_chargedHadronIso(pat_muon_PF_chargedHadronIso[i]);//###
    muon->setIsGlobalMuonPromptTight(pat_muon_isGlobalMuonPromptTight[i]);
    muon->setPF_photonIso(pat_muon_PF_photonIso[i]);//###
    muon->setDRmin(pat_muon_dRmin[i]);
    muon->setCharge(pat_muon_charge[i]);//###
    muon->setCalEnergyHad(pat_muon_calEnergyHad[i]);
    muon->setCaloCompatibility(pat_muon_caloCompatibility[i]);
    muon->setDRmin_track_ntID(pat_muon_dRmin_track_ntID[i]);
    muon->setSegmentCompatibility(pat_muon_segmentCompatibility[i]);
    muon->setOverlapCompatibility(pat_muon_overlapCompatibility[i]);
    muon->setIsCaloMuon(pat_muon_isCaloMuon[i]);
    muon->setCosmicCompatibility(pat_muon_cosmicCompatibility[i]);
    muon->setPF_neutralHadronIso(pat_muon_PF_neutralHadronIso[i]);//###
    muon->setIsTMLastStationTight(pat_muon_isTMLastStationTight[i]);
    muon->setIsCaloCompatibilityValid(pat_muon_isCaloCompatibilityValid[i]);
    muon->setNumberOfMatches(pat_muon_numberOfMatches[i]);
    muon->setPFPAT_dpt(pat_muon_PFPAT_dpt[i]);
    muon->setGenLepton_pdgID(pat_muon_genLepton_pdgID[i]);
    muon->setCalEnergyEM(pat_muon_calEnergyEM[i]);
    muon->setDRmin05_track_ntID(pat_muon_dRmin05_track_ntID[i]);
    muon->setHcaloIso(pat_muon_hcaloIso[i]);//###
    muon->setDRmin05(pat_muon_dRmin05[i]);
    muon->setGenLepton_dR(pat_muon_genLepton_dR[i]);
    muon->setMuonTrackID(pat_muon_muonTrackID[i]);
    muon->setIsTrackerMuon(pat_muon_isTrackerMuon[i]);
    muon->setBackToBackCompatibility(pat_muon_backToBackCompatibility[i]);
    muon->setEcalIsoDep(pat_muon_ecalIsoDep[i]);
    muon->setCaloIso(pat_muon_caloIso[i]);//###
    muon->setAllTrackIso(pat_muon_allTrackIso[i]);
    muon->setPFPAT_dphi(pat_muon_PFPAT_dphi[i]);
    muon->setIsStandAloneMuon(pat_muon_isStandAloneMuon[i]);
    muon->setDRmin10_track_ntID(pat_muon_dRmin10_track_ntID[i]);
    muon->setGenLepton_mother_ntID(pat_muon_genLepton_mother_ntID[i]);
    muon->setTrigger_nfilter(pat_muon_trigger_nfilter[i]);
    muon->setTimeCompatibility(pat_muon_timeCompatibility[i]);
    muon->setGenLepton_mother_pdgID(pat_muon_genLepton_mother_pdgID[i]);
    muon->setGenLepton_ntID(pat_muon_genLepton_ntID[i]);
    if(pat_muon_genLepton_ntID[i] >= 0 && pat_muon_genLepton_ntID[i] < (int)m_mcparticles.size()) {
    	muon->setGenLepton(dynamic_cast<SignatureObjectMCPart*>(m_mcparticles[pat_muon_genLepton_ntID[i]]));
    }
    muon->setBeta(pat_muon_beta[i]);
    muon->setInnerVertDxy(pat_muon_innerVertDxy[i]);
    muon->setInnerNumberOfValidPixelHits(pat_muon_innerNumberOfValidPixelHits[i]);
    muon->setInnerVertDz(pat_muon_innerVertDz[i]);
    muon->setNormalizedChi2(pat_muon_normalizedChi2[i]);
    muon->setPDGid(13*-1*muon->getCharge());
    for(int j = 0; j < pat_muon_trigger_nfilter[i] && j < 5; j++){
      muon->addTrigger_objectType(pat_muon_trigger_objectType[i][j]);
      muon->addTrigger_objectID(pat_muon_trigger_objectID[i][j]);
    }
    m_muons.push_back(muon);
  }
  sort(m_muons.begin(),m_muons.end(),SignatureObjectComparison);
  reverse(m_muons.begin(),m_muons.end());
}

//-----------------------------------------
void SignatureHandler::readElectrons()
{
  for(int i = 0; i < pat_electron_n; i++){
    int gtID = pat_electron_trackID[i];
    if(gtID < 0)continue;
    SignatureObjectElectron* electron = new SignatureObjectElectron(pat_electron_px[i],pat_electron_py[i],pat_electron_pz[i],pat_electron_energy[i]);
    electron->setRho(pat_rho);
    electron->setRhoNeutral(pat_rho_neutral);
    electron->setChargedHadronIso(pat_electron_PF_chargedHadronIso[i]);
    electron->setNeutralHadronIso(pat_electron_PF_neutralHadronIso[i]);
    electron->setPhotonIso(pat_electron_PF_photonIso[i]);


    electron->setDz(reco_track_dz[gtID]);
    electron->setGenParticle_ntID(reco_track_genParticle_ntID[gtID]);
    electron->setCaloIso9(reco_track_caloIso9[gtID]);
    electron->setDxy(reco_track_dxy[gtID]);
    electron->setNValidMuonHits(reco_track_nValidMuonHits[gtID]);
    electron->setCaloIso2(reco_track_caloIso2[gtID]);
    electron->setVert_dxy(pat_electron_fMVAVar_d0[i]);
    electron->setCharge(reco_track_charge[gtID]);
    electron->setCaloIso1(reco_track_caloIso1[gtID]);
    electron->setIsGlobal(reco_track_isGlobal[gtID]);
    electron->setBeam_dsz(reco_track_beam_dsz[gtID]);
    electron->setNLostPixelHits(reco_track_nLostPixelHits[gtID]);
    electron->setNpixelLayersWM(reco_track_npixelLayersWM[gtID]);
    electron->setVx(reco_track_vx[gtID]);
    electron->setVy(reco_track_vy[gtID]);
    electron->setLambdaError(reco_track_lambdaError[gtID]);
    electron->setPF_chargedHadronIso(reco_track_PF_chargedHadronIso[gtID]);
    electron->setNValidPixelHits(reco_track_nValidPixelHits[gtID]);
    electron->setVz(reco_track_vz[gtID]);
    electron->setD0(reco_track_d0[gtID]);
    electron->setGenParticle_mother_ntID(reco_track_genParticle_mother_ntID[gtID]);
    electron->setDsz(reco_track_dsz[gtID]);
    electron->setNValidTrackerHits(reco_track_nValidTrackerHits[gtID]);
    electron->setNBadMuonHitsInFirstStation(reco_track_nBadMuonHitsInFirstStation[gtID]);
    electron->setThetaError(reco_track_thetaError[gtID]);
    electron->setVert_dz(reco_track_vert_dz[gtID]);
    electron->setPF_photonIso(reco_track_PF_photonIso[gtID]);
    electron->setOutermostMuonStationWithValidHits(reco_track_outermostMuonStationWithValidHits[gtID]);
    electron->setPhiError(reco_track_phiError[gtID]);
    electron->setNAnyMuonHitsInFirstStation(reco_track_nAnyMuonHitsInFirstStation[gtID]);
    electron->setTrackIso6(reco_track_trackIso6[gtID]);
    electron->setNtrackerLayersWM(reco_track_ntrackerLayersWM[gtID]);
    electron->setTrackIso2(reco_track_trackIso2[gtID]);
    electron->setTheta(reco_track_theta[gtID]);
    electron->setNLostTrackerHits(reco_track_nLostTrackerHits[gtID]);
    electron->setIsMuon(reco_track_isMuon[gtID]);
    electron->setTrackIso9(reco_track_trackIso9[gtID]);
    electron->setD0Error(reco_track_d0Error[gtID]);
    electron->setTrackIso1(reco_track_trackIso1[gtID]);
    electron->setNBadMuonHits(reco_track_nBadMuonHits[gtID]);
    electron->setChi2(reco_track_chi2[gtID]);
    electron->setCaloIso6(reco_track_caloIso6[gtID]);
    electron->setEtaError(reco_track_etaError[gtID]);
    electron->setTrackIso12(reco_track_trackIso12[gtID]);
    electron->setNdof(reco_track_ndof[gtID]);
    electron->setNstripLayersWM(reco_track_nstripLayersWM[gtID]);
    electron->setBeam_dz(reco_track_beam_dz[gtID]);
    electron->setIsTracker(reco_track_isTracker[gtID]);
    electron->setNValidHits(reco_track_nValidHits[gtID]);
    electron->setDzError(reco_track_dzError[gtID]);
    electron->setNValidMuonHitsInFirstStation(reco_track_nValidMuonHitsInFirstStation[gtID]);
    electron->setDxyError(reco_track_dxyError[gtID]);
    electron->setGenParticle_mother_pdgID(reco_track_genParticle_mother_pdgID[gtID]);
    electron->setGenParticle_dR(reco_track_genParticle_dR[gtID]);
    electron->setPF_neutralHadronIso(reco_track_PF_neutralHadronIso[gtID]);
    electron->setNLostMuonHitsInFirstStation(reco_track_nLostMuonHitsInFirstStation[gtID]);
    electron->setGenParticle_pdgID(reco_track_genParticle_pdgID[gtID]);
    electron->setBeam_dxy(reco_track_beam_dxy[gtID]);
    electron->setCaloIso12(reco_track_caloIso12[gtID]);
    electron->setMuonStationsWAH(reco_track_muonStationsWAH[gtID]);
    electron->setNLostMuonHits(reco_track_nLostMuonHits[gtID]);
    electron->setNLostHits(reco_track_nLostHits[gtID]);
    electron->setMuonStationsWVH(reco_track_muonStationsWVH[gtID]);
    electron->setBeam_d0(reco_track_beam_d0[gtID]);
    electron->setVertWeight(reco_track_vertWeight[gtID]);
    electron->setFbrem(pat_electron_fbrem[i]);
    electron->setTrackID(pat_electron_trackID[i]);
    electron->setPF_chargedHadronIso_04(pat_electron_PF_chargedHadronIso_04[i]);
    electron->setConversionDCotTheta(pat_electron_ConversionDCotTheta[i]);
    electron->setFMVAVar_detacalo(pat_electron_fMVAVar_detacalo[i]);
    electron->setPF_neutralHadronIso(pat_electron_PF_neutralHadronIso[i]);//###
    electron->setFMVAVar_eta(pat_electron_fMVAVar_eta[i]);
    electron->setFMVAVar_dphicalo(pat_electron_fMVAVar_dphicalo[i]);
    electron->setSwissCross(pat_electron_swissCross[i]);
    electron->setPF_photonIso(pat_electron_PF_photonIso[i]);//###
    electron->setCharge(pat_electron_charge[i]);//###
    electron->setFMVAVar_PreShowerOverRaw(pat_electron_fMVAVar_PreShowerOverRaw[i]);
    electron->setFMVAVar_kfhits(pat_electron_fMVAVar_kfhits[i]);
    electron->setEidTight(pat_electron_eidTight[i]);
    electron->setGenLepton_ntID(pat_electron_genLepton_ntID[i]);
    if(pat_electron_genLepton_ntID[i] >= 0 && pat_electron_genLepton_ntID[i] < (int)m_mcparticles.size()) {
    	electron->setGenLepton(dynamic_cast<SignatureObjectMCPart*>(m_mcparticles[pat_electron_genLepton_ntID[i]]));
    }
    electron->setHcaloIso(pat_electron_hcaloIso[i]);//###
    electron->setFMVAVar_kfchi2(pat_electron_fMVAVar_kfchi2[i]);
    electron->setHadOverEm(pat_electron_hadOverEm[i]);
    electron->setFMVAVar_IoEmIoP(pat_electron_fMVAVar_IoEmIoP[i]);
    electron->setFMVAVar_pt(pat_electron_fMVAVar_pt[i]);
    electron->setTrigger_nfilter(pat_electron_trigger_nfilter[i]);
    electron->setFMVAVar_phiwidth(pat_electron_fMVAVar_phiwidth[i]);
    electron->setFMVAVar_EoP(pat_electron_fMVAVar_EoP[i]);
    electron->setEcaloIso(pat_electron_ecaloIso[i]);//###
    electron->setPFPAT_dphi(pat_electron_PFPAT_dphi[i]);
    electron->setGsfScPixChargeConsistent(pat_electron_GsfScPixChargeConsistent[i]);
    electron->setFMVAVar_eleEoPout(pat_electron_fMVAVar_eleEoPout[i]);
    electron->setTrackIso(pat_electron_trackIso[i]);//###
    electron->setPFMatchPdgId(pat_electron_PFMatchPdgId[i]);
    electron->setPF_neutralHadronIso_04(pat_electron_PF_neutralHadronIso_04[i]);
    electron->setEidRobustLoose(pat_electron_eidRobustLoose[i]);
    electron->setIsPF(pat_electron_isPF[i]);
    electron->setFMVAVar_etawidth(pat_electron_fMVAVar_etawidth[i]);
    electron->setPF_chargedHadronIso(pat_electron_PF_chargedHadronIso[i]);//###
    electron->setDeltaEta(pat_electron_deltaEta[i]);
    electron->setDRmin(pat_electron_dRmin[i]);
    electron->setESeedClusterOverPout(pat_electron_eSeedClusterOverPout[i]);
    electron->setDRmin_track_ntID(pat_electron_dRmin_track_ntID[i]);
    electron->setSigmaIetaIeta(pat_electron_sigmaIetaIeta[i]);
    electron->setFMVAVar_d0(pat_electron_fMVAVar_d0[i]);
    electron->setFMVAVar_dz(pat_electron_fMVAVar_dz[i]);
    electron->setFMVAVar_nbrems(pat_electron_fMVAVar_nbrems[i]);
    electron->setFMVAVar_see(pat_electron_fMVAVar_see[i]);
    electron->setCaloEnergy(pat_electron_caloEnergy[i]);
    electron->setFMVAVar_fbrem(pat_electron_fMVAVar_fbrem[i]);
    electron->setClassification(pat_electron_classification[i]);
    electron->setE2x5Max(pat_electron_e2x5Max[i]);
    electron->setPFPAT_dq(pat_electron_PFPAT_dq[i]);
    electron->setPFPAT_deta(pat_electron_PFPAT_deta[i]);
    electron->setDeltaPhi(pat_electron_deltaPhi[i]);
    electron->setNumberOfLostInnerHits(pat_electron_NumberOfLostInnerHits[i]);
    electron->setConversionDist(pat_electron_ConversionDist[i]);
    electron->setPFPAT_dpt(pat_electron_PFPAT_dpt[i]);
    electron->setGenLepton_pdgID(pat_electron_genLepton_pdgID[i]);
    electron->setFMVAVar_gsfchi2(pat_electron_fMVAVar_gsfchi2[i]);
    electron->setEOverPin(pat_electron_eOverPin[i]);
    electron->setFMVAVar_HoE(pat_electron_fMVAVar_HoE[i]);
    electron->setIsConversion(pat_electron_IsConversion[i]);
    electron->setEcalDriven(pat_electron_ecalDriven[i]);
    electron->setGsfCtfChargeConsistent(pat_electron_GsfCtfChargeConsistent[i]);
    electron->setFMVAVar_spp(pat_electron_fMVAVar_spp[i]);
    electron->setFMVAVar_dphi(pat_electron_fMVAVar_dphi[i]);
    electron->setFMVAVar_e1x5e5x5(pat_electron_fMVAVar_e1x5e5x5[i]);
    electron->setE1x5(pat_electron_e1x5[i]);
    electron->setEidRobustHighEnergy(pat_electron_eidRobustHighEnergy[i]);
    electron->setEMax(pat_electron_eMax[i]);
    electron->setSigmaEtaEta(pat_electron_sigmaEtaEta[i]);
    electron->setConv_vtxProb(pat_electron_conv_vtxProb[i]);
    electron->setStatus(pat_electron_status[i]);
    electron->setE5x5(pat_electron_e5x5[i]);
    electron->setFMVAVar_R9(pat_electron_fMVAVar_R9[i]);
    electron->setCaloIso(pat_electron_caloIso[i]);//###
    electron->setEidRobustTight(pat_electron_eidRobustTight[i]);
    electron->setFMVAVar_deta(pat_electron_fMVAVar_deta[i]);
    electron->setPF_photonIso_04(pat_electron_PF_photonIso_04[i]);
    electron->setEidLoose(pat_electron_eidLoose[i]);
    electron->setGsfCtfScPixChargeConsistent(pat_electron_GsfCtfScPixChargeConsistent[i]);
    electron->setNumberOfExpectedInnerHits(pat_electron_NumberOfExpectedInnerHits[i]);    
    for(int j = 0; j < pat_electron_trigger_nfilter[i] && j < 5; j++){
      electron->addTrigger_objectID(pat_electron_trigger_objectID[i][j]);
      electron->addTrigger_objectType(pat_electron_trigger_objectType[i][j]);
    }
    electron->setPDGid(11*-1*electron->getCharge());
    /*
    bool debugMyVar = false;
    if(m_debugMode)debugMyVar=true;
    double mvaValTrig = myMVATrig_->mvaValue(electron->getFMVAVar_fbrem(),
					     electron->getFMVAVar_kfchi2(),
					     electron->getFMVAVar_kfhits(),
					     electron->getFMVAVar_gsfchi2(),
					     electron->getFMVAVar_deta(),
					     electron->getFMVAVar_dphi(),
					     electron->getFMVAVar_detacalo(),
					     electron->getFMVAVar_see(),
					     electron->getFMVAVar_spp(),
					     electron->getFMVAVar_etawidth(),
					     electron->getFMVAVar_phiwidth(),
					     electron->getFMVAVar_e1x5e5x5(),
					     electron->getFMVAVar_R9(),
					     electron->getFMVAVar_HoE(),
					     electron->getFMVAVar_EoP(),
					     electron->getFMVAVar_IoEmIoP(),
					     electron->getFMVAVar_eleEoPout(),
					     electron->getFMVAVar_PreShowerOverRaw(),
					     electron->getFMVAVar_eta(),
					     electron->getFMVAVar_pt(),
					     debugMyVar);

    double mvaValNoTrig = myMVANonTrig_->mvaValue(electron->getFMVAVar_fbrem(),
						  electron->getFMVAVar_kfchi2(),
						  electron->getFMVAVar_kfhits(),
						  electron->getFMVAVar_gsfchi2(),
						  electron->getFMVAVar_deta(),
						  electron->getFMVAVar_dphi(),
						  electron->getFMVAVar_detacalo(),
						  electron->getFMVAVar_see(),
						  electron->getFMVAVar_spp(),
						  electron->getFMVAVar_etawidth(),
						  electron->getFMVAVar_phiwidth(),
						  electron->getFMVAVar_e1x5e5x5(),
						  electron->getFMVAVar_R9(),
						  electron->getFMVAVar_HoE(),
						  electron->getFMVAVar_EoP(),
						  electron->getFMVAVar_IoEmIoP(),
						  electron->getFMVAVar_eleEoPout(),
						  electron->getFMVAVar_PreShowerOverRaw(),
						  electron->getFMVAVar_eta(),
						  electron->getFMVAVar_pt(),
						  debugMyVar);

    electron->setMvaTrig(mvaValTrig);
    electron->setMvaNoTrig(mvaValNoTrig);
    */

    m_electrons.push_back(electron);
  }
  sort(m_electrons.begin(),m_electrons.end(),SignatureObjectComparison);
  reverse(m_electrons.begin(),m_electrons.end());
}

//-----------------------------------------
void SignatureHandler::readPhotons()
{
  for(int i = 0; i < pat_photon_n; i++){
    SignatureObjectPhoton* photon = new SignatureObjectPhoton(pat_photon_px[i],pat_photon_py[i],pat_photon_pz[i],pat_photon_pmag[i]);
    photon->setRho(pat_rho);
    photon->setRhoNeutral(pat_rho_neutral);
    photon->setPhotonIso(pat_photon_photonIso[i]);
    photon->setTrackIso(pat_photon_trackIso[i]);//###
    photon->setGenPhoton_pdgID(pat_photon_genPhoton_pdgID[i]);
    photon->setEndcap(pat_photon_endcap[i]);
    photon->setTrack_nSolidR03(pat_photon_track_nSolidR03[i]);
    photon->setNeutralHadronIso(pat_photon_neutralHadronIso[i]);
    photon->setIsLoose(pat_photon_isLoose[i]);
    photon->setHcalDepth2TowerEtR04(pat_photon_hcalDepth2TowerEtR04[i]);
    photon->setChargedHadronIso(pat_photon_chargedHadronIso[i]);
    photon->setEOut(pat_photon_EOut[i]);
    photon->setScEt(pat_photon_scEt[i]);
    photon->setEcalRecHitEtR04(pat_photon_ecalRecHitEtR04[i]);
    photon->setEcalRecHitEtR03(pat_photon_ecalRecHitEtR03[i]);
    photon->setConversionSafeElectronVeto(pat_photon_conversionSafeElectronVeto[i]);
    photon->setGenPhoton_ntID(pat_photon_genPhoton_ntID[i]);
    if(pat_photon_genPhoton_ntID[i] >= 0 && pat_photon_genPhoton_ntID[i] < (int)m_mcparticles.size()) {
    	photon->setGenPhoton(dynamic_cast<SignatureObjectMCPart*>(m_mcparticles[pat_photon_genPhoton_ntID[i]]));
    }
    photon->setTrackSumPtSolidR04(pat_photon_trackSumPtSolidR04[i]);
    photon->setHadTowOverEm(pat_photon_hadTowOverEm[i]);
    photon->setSigmaIetaIeta(pat_photon_sigmaIetaIeta[i]);
    photon->setPFPhotonRes(pat_photon_PFPhotonRes[i]);
    photon->setMVAGlobalCorrEError(pat_photon_MVAGlobalCorrEError[i]);
    photon->setHcalTowerEtR04(pat_photon_hcalTowerEtR04[i]);
    photon->setHcalDepth1TowerEtR03(pat_photon_hcalDepth1TowerEtR03[i]);
    photon->setMustacheEt(pat_photon_mustacheEt[i]);
    photon->setHcalDepth1TowerEtR04(pat_photon_hcalDepth1TowerEtR04[i]);
    photon->setHcalTowerEtR03(pat_photon_hcalTowerEtR03[i]);
    photon->setTrack_nHollowR03(pat_photon_track_nHollowR03[i]);
    photon->setTrack_nHollowR04(pat_photon_track_nHollowR04[i]);
    photon->setTrack_nSolidR04(pat_photon_track_nSolidR04[i]);
    photon->setIsTight(pat_photon_isTight[i]);
    photon->setMVAGlobalCorrE(pat_photon_MVAGlobalCorrE[i]);
    photon->setCaloIso(pat_photon_caloIso[i]);//###
    photon->setHadOverEm(pat_photon_hadOverEm[i]);
    photon->setR9(pat_photon_r9[i]);
    photon->setTrigger_nfilter(pat_photon_trigger_nfilter[i]);
    photon->setTrackSumPtHollowR04(pat_photon_trackSumPtHollowR04[i]);
    photon->setBarrel(pat_photon_barrel[i]);
    photon->setTrackSumPtSolidR03(pat_photon_trackSumPtSolidR03[i]);
    photon->setHcalDepth2TowerEtR03(pat_photon_hcalDepth2TowerEtR03[i]);
    photon->setTrackSumPtHollowR03(pat_photon_trackSumPtHollowR03[i]);
    for(int j = 0; j < pat_photon_trigger_nfilter[i] && j < 5; j++){
      photon->addTrigger_objectType(pat_photon_trigger_objectType[i][j]);
      photon->addTrigger_objectID(pat_photon_trigger_objectID[i][j]);
    }
    m_photons.push_back(photon);
  }
}

//-----------------------------------------
void SignatureHandler::readJets()
{
  for(int i = 0; i < pat_jet_n; i++){
    double corr = 1.0;
    double unc = pat_jet_uncertainty[i];
    if(getMode("jetCorrection") > 0){
      corr += unc/pat_jet_pt[i];
    }else if(getMode("jetCorrection") < 0){
      corr -= unc/pat_jet_pt[i];
    }

    SignatureObjectJet* jet = new SignatureObjectJet(pat_jet_px[i]*corr,pat_jet_py[i]*corr,pat_jet_pz[i]*corr,pat_jet_energy[i]*corr);
    jet->setCorrLevel(pat_jet_corrLevel[i]);
    jet->setBDiscriminator_combined(pat_jet_bDiscriminator_combined[i]);
    jet->setChargedHadronFraction(pat_jet_chargedHadronFraction[i]);
    jet->setGenParton_ntID(pat_jet_genParton_ntID[i]);
    if(pat_jet_genParton_ntID[i] >= 0 && pat_jet_genParton_ntID[i] < (int)m_mcparticles.size()) {
    	jet->setGenParton(dynamic_cast<SignatureObjectMCPart*>(m_mcparticles[pat_jet_genParton_ntID[i]]));
    }
    jet->setEtaetaMoment(pat_jet_etaetaMoment[i]);
    jet->setRaw_pt(pat_jet_raw_pt[i]);
    //jet->setVy(pat_jet_vy[i]);//###
    //jet->setVx(pat_jet_vx[i]);//###
    jet->setBDiscriminator_trackCount(pat_jet_bDiscriminator_trackCount[i]);
    jet->setNeutralEMFraction(pat_jet_neutralEMFraction[i]);
    jet->setChargedEMFraction(pat_jet_chargedEMFraction[i]);
    jet->setTrigger_nfilter(pat_jet_trigger_nfilter[i]);
    jet->setNeutralHadronFraction(pat_jet_neutralHadronFraction[i]);
    jet->setIsCalo(pat_jet_isCalo[i]);
    jet->setEhf(pat_jet_ehf[i]);
    //jet->setCharge(pat_jet_charge[i]);//###
    jet->setBDiscriminator_ssVertexPure(pat_jet_bDiscriminator_ssVertexPure[i]);
    jet->setBDiscriminator(pat_jet_bDiscriminator[i]);
    jet->setPhiphiMoment(pat_jet_phiphiMoment[i]);
    //jet->setVz(pat_jet_vz[i]);//###
    jet->setGenParton_pdgID(pat_jet_genParton_pdgID[i]);
    jet->setSumTrackPt(pat_jet_sumTrackPt[i]);
    jet->setTight_PFjetID(pat_jet_tight_PFjetID[i]);
    jet->setChargedHadronMultiplicity(pat_jet_chargedHadronMultiplicity[i]);
    jet->setBDiscriminator_trackCountPure(pat_jet_bDiscriminator_trackCountPure[i]);
    jet->setIsPF(pat_jet_isPF[i]);
    jet->setEmf(pat_jet_emf[i]);
    jet->setUncertainty(pat_jet_uncertainty[i]);
    jet->setNtracks(pat_jet_ntracks[i]);
    jet->setRaw_et(pat_jet_raw_et[i]);
    jet->setEtaphiMoment(pat_jet_etaphiMoment[i]);
    jet->setMass(pat_jet_mass[i]);
    jet->setLoose_PFjetID(pat_jet_loose_PFjetID[i]);
    jet->setMedium_PFjetID(pat_jet_medium_PFjetID[i]);
    jet->setNumberConstituents(pat_jet_numberConstituents[i]);
    jet->setBDiscriminator_ssVertex(pat_jet_bDiscriminator_ssVertex[i]);

    for(int j = 0; j < 50; j++){
      jet->addBDiscNegative(pat_jet_bDiscNegative[i][j]);
      jet->addBDiscPositive(pat_jet_bDiscPositive[i][j]);
    }

    for(int j = 0; j < pat_jet_ntracks[i]; j++){
      jet->addTrkIDs(pat_jet_trkIDs[i][j]);
    }
    
    for(int j = 0; j < 7; j++){
      jet->addCorr_glue(pat_jet_corr_glue[i][j]);
      jet->addCorr_uds(pat_jet_corr_uds[i][j]);
      jet->addCorr_c(pat_jet_corr_c[i][j]);
      jet->addCorr_b(pat_jet_corr_b[i][j]);
    }

    for(int j = 0; j < pat_jet_trigger_nfilter[i] && j < 5; j++){
      jet->addTrigger_objectType(pat_jet_trigger_objectType[i][j]);
      jet->addTrigger_objectID(pat_jet_trigger_objectID[i][j]);
    }
    jet->setBeta(calculateJetBeta(jet,m_recovertices[0]));
    m_jets.push_back(jet);
  }

}

//-----------------------------------------
void SignatureHandler::readMET()
{
  m_met = new SignatureObjectMET(0,0,0);
  m_met->SetPtEtaPhiM(pat_met_pt,pat_met_eta,pat_met_phi,0);
  m_met->setPat_sumEt(pat_met_sumEt);
  m_met->setPf_pt(pf_met_pt);
  //m_met->setPf_eta(pf_met_eta);
  m_met->setPat_phi(pat_met_phi);
  m_met->setPat_eta(pat_met_eta);
  m_met->setPf_phi(pf_met_phi);
  m_met->setPat_px(pat_met_px);
  m_met->setPat_py(pat_met_py);
  m_met->setPat_pz(pat_met_pz);
  m_met->setPat_pt(pat_met_pt);
  m_met->setPf_sumEt(pf_met_sumEt);
  m_met->setPat_gen_sumEt(pat_met_gen_sumEt);
  m_met->setPat_mEtSig(pat_met_mEtSig);
  m_met->setTc_sumEt(tc_met_sumEt);
  m_met->setTc_pt(tc_met_pt);
  m_met->setTc_phi(tc_met_phi);

  for(int j = 0; j < pat_met_trigger_nfilter && j<5; j++){
    m_met->addPat_trigger_objectID(pat_met_trigger_objectID[j]);
    m_met->addPat_trigger_objectType(pat_met_trigger_objectType[j]);
  }
}

//-----------------------------------------
void SignatureHandler::readRecoTracks()
{
  for(int i = 0; i < reco_track_n; i++){
    SignatureObjectRecoTrack* recotrack = new SignatureObjectRecoTrack(0,0,0,0);
    recotrack->SetPtEtaPhiM(reco_track_pt[i],reco_track_eta[i],reco_track_phi[i],0);
    recotrack->setRho(pat_rho);
    recotrack->setChargedHadronIso(reco_track_PF_chargedHadronIso[i]);
    recotrack->setNeutralHadronIso(reco_track_PF_neutralHadronIso[i]);
    recotrack->setPhotonIso(reco_track_PF_photonIso[i]);
    recotrack->setDz(reco_track_dz[i]);//###
    recotrack->setEcaloIso(reco_track_ecaloIso[i]);//###
    recotrack->setGenParticle_ntID(reco_track_genParticle_ntID[i]);//###
    if(reco_track_genParticle_ntID[i] >= 0 && reco_track_genParticle_ntID[i] < (int)m_mcparticles.size()) {
    	recotrack->setGenParticle(dynamic_cast<SignatureObjectMCPart*>(m_mcparticles[reco_track_genParticle_ntID[i]]));
    }
    recotrack->setCaloIso9(reco_track_caloIso9[i]);//###
    recotrack->setDxy(reco_track_dxy[i]);//###
    recotrack->setNValidMuonHits(reco_track_nValidMuonHits[i]);//###
    recotrack->setCaloIso2(reco_track_caloIso2[i]);//###
    recotrack->setVert_dxy(reco_track_vert_dxy[i]);//###
    recotrack->setCharge(reco_track_charge[i]);//###
    recotrack->setCaloIso1(reco_track_caloIso1[i]);//###
    recotrack->setTrackIso(reco_track_trackIso[i]);//###
    recotrack->setIsGlobal(reco_track_isGlobal[i]);//###
    recotrack->setBeam_dsz(reco_track_beam_dsz[i]);//###
    recotrack->setNLostPixelHits(reco_track_nLostPixelHits[i]);//###
    recotrack->setNpixelLayersWM(reco_track_npixelLayersWM[i]);//###
    recotrack->setVx(reco_track_vx[i]);//###
    recotrack->setVy(reco_track_vy[i]);//###
    recotrack->setLambdaError(reco_track_lambdaError[i]);//###
    recotrack->setPF_chargedHadronIso(reco_track_PF_chargedHadronIso[i]);//###
    recotrack->setNValidPixelHits(reco_track_nValidPixelHits[i]);//###
    recotrack->setVz(reco_track_vz[i]);//###
    recotrack->setD0(reco_track_d0[i]);//###
    recotrack->setGenParticle_mother_ntID(reco_track_genParticle_mother_ntID[i]);//###
    recotrack->setDsz(reco_track_dsz[i]);//###
    recotrack->setNValidTrackerHits(reco_track_nValidTrackerHits[i]);//###
    recotrack->setNBadMuonHitsInFirstStation(reco_track_nBadMuonHitsInFirstStation[i]);//###
    recotrack->setThetaError(reco_track_thetaError[i]);//###
    recotrack->setVert_dz(reco_track_vert_dz[i]);//###
    recotrack->setPF_photonIso(reco_track_PF_photonIso[i]);//###
    recotrack->setOutermostMuonStationWithValidHits(reco_track_outermostMuonStationWithValidHits[i]);//###
    recotrack->setPhiError(reco_track_phiError[i]);//###
    recotrack->setNAnyMuonHitsInFirstStation(reco_track_nAnyMuonHitsInFirstStation[i]);//###
    recotrack->setTrackIso6(reco_track_trackIso6[i]);//###
    recotrack->setNtrackerLayersWM(reco_track_ntrackerLayersWM[i]);//###
    recotrack->setTrackIso2(reco_track_trackIso2[i]);//###
    recotrack->setTheta(reco_track_theta[i]);//###
    recotrack->setNLostTrackerHits(reco_track_nLostTrackerHits[i]);//###
    recotrack->setIsMuon(reco_track_isMuon[i]);//###
    recotrack->setTrackIso9(reco_track_trackIso9[i]);//###
    recotrack->setD0Error(reco_track_d0Error[i]);//###
    recotrack->setTrackIso1(reco_track_trackIso1[i]);//###
    recotrack->setNBadMuonHits(reco_track_nBadMuonHits[i]);//###
    recotrack->setChi2(reco_track_chi2[i]);//###
    recotrack->setCaloIso6(reco_track_caloIso6[i]);//###
    recotrack->setEtaError(reco_track_etaError[i]);//###
    recotrack->setTrackIso12(reco_track_trackIso12[i]);//###
    recotrack->setNdof(reco_track_ndof[i]);//###
    recotrack->setNstripLayersWM(reco_track_nstripLayersWM[i]);//###
    recotrack->setBeam_dz(reco_track_beam_dz[i]);//###
    recotrack->setIsTracker(reco_track_isTracker[i]);//###
    recotrack->setHcaloIso(reco_track_hcaloIso[i]);//###
    recotrack->setNValidHits(reco_track_nValidHits[i]);//###
    recotrack->setDzError(reco_track_dzError[i]);//###
    recotrack->setNValidMuonHitsInFirstStation(reco_track_nValidMuonHitsInFirstStation[i]);//###
    recotrack->setDxyError(reco_track_dxyError[i]);//###
    recotrack->setGenParticle_mother_pdgID(reco_track_genParticle_mother_pdgID[i]);//###
    recotrack->setCaloIso(reco_track_caloIso[i]);//###
    recotrack->setGenParticle_dR(reco_track_genParticle_dR[i]);//###
    recotrack->setPF_neutralHadronIso(reco_track_PF_neutralHadronIso[i]);//###
    recotrack->setNLostMuonHitsInFirstStation(reco_track_nLostMuonHitsInFirstStation[i]);//###
    recotrack->setGenParticle_pdgID(reco_track_genParticle_pdgID[i]);//###
    recotrack->setBeam_dxy(reco_track_beam_dxy[i]);//###
    recotrack->setCaloIso12(reco_track_caloIso12[i]);//###
    recotrack->setMuonStationsWAH(reco_track_muonStationsWAH[i]);//###
    recotrack->setNLostMuonHits(reco_track_nLostMuonHits[i]);//###
    recotrack->setNLostHits(reco_track_nLostHits[i]);//###
    recotrack->setMuonStationsWVH(reco_track_muonStationsWVH[i]);//###
    recotrack->setBeam_d0(reco_track_beam_d0[i]);//###
    recotrack->setVertWeight(reco_track_vertWeight[i]);//###


    m_recotracks.push_back(recotrack);
  }
}

//-----------------------------------------
void SignatureHandler::readTaus()
{
  //cout<<"=========="<<endl;
  for(int i = 0; i < pat_tau_n; i++){
    SignatureObjectTau* tau = new SignatureObjectTau(0,0,0,0);
    int gtID = pat_tau_leadTrack_ntID[i];
    tau->SetPtEtaPhiM(pat_tau_pt[i],pat_tau_eta[i],pat_tau_phi[i],1.777);
    tau->setRho(pat_rho);
    int id = findTauLeadingTrack(tau);
    gtID = id;

    if(gtID >= 0){
      tau->setLeadingTrack((SignatureObjectRecoTrack*)m_recotracks[gtID]);
      tau->setDz(reco_track_dz[gtID]);
      tau->setGenParticle_ntID(reco_track_genParticle_ntID[gtID]);
      tau->setCaloIso9(reco_track_caloIso9[gtID]);
      tau->setDxy(reco_track_dxy[gtID]);
      tau->setNValidMuonHits(reco_track_nValidMuonHits[gtID]);
      tau->setCaloIso2(reco_track_caloIso2[gtID]);
      tau->setVert_dxy(reco_track_vert_dxy[gtID]);
      tau->setCaloIso1(reco_track_caloIso1[gtID]);
      tau->setIsGlobal(reco_track_isGlobal[gtID]);
      tau->setBeam_dsz(reco_track_beam_dsz[gtID]);
      tau->setNLostPixelHits(reco_track_nLostPixelHits[gtID]);
      tau->setNpixelLayersWM(reco_track_npixelLayersWM[gtID]);
      tau->setVx(reco_track_vx[gtID]);
      tau->setVy(reco_track_vy[gtID]);
      tau->setLambdaError(reco_track_lambdaError[gtID]);
      tau->setPF_chargedHadronIso(reco_track_PF_chargedHadronIso[gtID]);
      tau->setNValidPixelHits(reco_track_nValidPixelHits[gtID]);
      tau->setVz(reco_track_vz[gtID]);
      tau->setD0(reco_track_d0[gtID]);
      tau->setGenParticle_mother_ntID(reco_track_genParticle_mother_ntID[gtID]);
      tau->setDsz(reco_track_dsz[gtID]);
      tau->setNValidTrackerHits(reco_track_nValidTrackerHits[gtID]);
      tau->setNBadMuonHitsInFirstStation(reco_track_nBadMuonHitsInFirstStation[gtID]);
      tau->setThetaError(reco_track_thetaError[gtID]);
      tau->setVert_dz(reco_track_vert_dz[gtID]);
      tau->setPF_photonIso(reco_track_PF_photonIso[gtID]);
      tau->setOutermostMuonStationWithValidHits(reco_track_outermostMuonStationWithValidHits[gtID]);
      tau->setPhiError(reco_track_phiError[gtID]);
      tau->setNAnyMuonHitsInFirstStation(reco_track_nAnyMuonHitsInFirstStation[gtID]);
      tau->setTrackIso6(reco_track_trackIso6[gtID]);
      tau->setNtrackerLayersWM(reco_track_ntrackerLayersWM[gtID]);
      tau->setTrackIso2(reco_track_trackIso2[gtID]);
      tau->setTheta(reco_track_theta[gtID]);
      tau->setNLostTrackerHits(reco_track_nLostTrackerHits[gtID]);
      tau->setIsMuon(reco_track_isMuon[gtID]);
      tau->setTrackIso9(reco_track_trackIso9[gtID]);
      tau->setD0Error(reco_track_d0Error[gtID]);
      tau->setTrackIso1(reco_track_trackIso1[gtID]);
      tau->setNBadMuonHits(reco_track_nBadMuonHits[gtID]);
      tau->setChi2(reco_track_chi2[gtID]);
      tau->setCaloIso6(reco_track_caloIso6[gtID]);
      tau->setEtaError(reco_track_etaError[gtID]);
      tau->setTrackIso12(reco_track_trackIso12[gtID]);
      tau->setNdof(reco_track_ndof[gtID]);
      tau->setNstripLayersWM(reco_track_nstripLayersWM[gtID]);
      tau->setBeam_dz(reco_track_beam_dz[gtID]);
      tau->setIsTracker(reco_track_isTracker[gtID]);
      tau->setNValidHits(reco_track_nValidHits[gtID]);
      tau->setDzError(reco_track_dzError[gtID]);
      tau->setNValidMuonHitsInFirstStation(reco_track_nValidMuonHitsInFirstStation[gtID]);
      tau->setDxyError(reco_track_dxyError[gtID]);
      tau->setGenParticle_mother_pdgID(reco_track_genParticle_mother_pdgID[gtID]);
      tau->setGenParticle_dR(reco_track_genParticle_dR[gtID]);
      tau->setPF_neutralHadronIso(reco_track_PF_neutralHadronIso[gtID]);
      tau->setNLostMuonHitsInFirstStation(reco_track_nLostMuonHitsInFirstStation[gtID]);
      tau->setGenParticle_pdgID(reco_track_genParticle_pdgID[gtID]);
      tau->setBeam_dxy(reco_track_beam_dxy[gtID]);
      tau->setCaloIso12(reco_track_caloIso12[gtID]);
      tau->setMuonStationsWAH(reco_track_muonStationsWAH[gtID]);
      tau->setNLostMuonHits(reco_track_nLostMuonHits[gtID]);
      tau->setNLostHits(reco_track_nLostHits[gtID]);
      tau->setMuonStationsWVH(reco_track_muonStationsWVH[gtID]);
      tau->setBeam_d0(reco_track_beam_d0[gtID]);
      tau->setVertWeight(reco_track_vertWeight[gtID]);
    }

    tau->setChargedHadronIso(pat_tau_PF_chargedHadronIso03[i]);
    tau->setNeutralHadronIso(pat_tau_PF_neutralHadronIso03[i]);
    tau->setPhotonIso(pat_tau_PF_photonIso03[i]);
    tau->setCharge(pat_tau_PF_signalCharge[i]);

    tau->setPF_neutralHadronIso05(pat_tau_PF_neutralHadronIso05[i]);
    tau->setTrackIso(pat_tau_trackIso[i]);//###
    tau->setPF_isoGammaEtSum(pat_tau_PF_isoGammaEtSum[i]);
    tau->setPF_NsigGamma(pat_tau_PF_NsigGamma[i]);
    tau->setIsPF(pat_tau_isPF[i]);
    tau->setIsCalo(pat_tau_isCalo[i]);
    tau->setEmFraction(pat_tau_emFraction[i]);
    tau->setPF_againstMuon(pat_tau_PF_againstMuon[i]);
    tau->setPF_neutralHadronIso03(pat_tau_PF_neutralHadronIso03[i]);
    tau->setCalo_leadTracksignedSipt(pat_tau_calo_leadTracksignedSipt[i]);
    tau->setPF_NsigCharged(pat_tau_PF_NsigCharged[i]);
    tau->setPF_isoKlongCandMaxPt(pat_tau_PF_isoKlongCandMaxPt[i]);
    tau->setPF_photonIso05(pat_tau_PF_photonIso05[i]);
    tau->setPF_againstElectron(pat_tau_PF_againstElectron[i]);
    tau->setPF_photonIso03(pat_tau_PF_photonIso03[i]);
    tau->setIsoTracks_n(pat_tau_isoTracks_n[i]);
    tau->setLeadTrack_ntID(pat_tau_leadTrack_ntID[i]);
    tau->setCalo_isoECALEtSum(pat_tau_calo_isoECALEtSum[i]);
    tau->setPF_signalMass(pat_tau_PF_signalMass[i]);
    tau->setGenLepton_pdgID(pat_tau_genLepton_pdgID[i]);
    tau->setPF_isoChargedPtSum(pat_tau_PF_isoChargedPtSum[i]);
    tau->setGenLepton_ntID(pat_tau_genLepton_ntID[i]);
    if(pat_tau_genLepton_ntID[i] >= 0 && pat_tau_genLepton_ntID[i] < (int)m_mcparticles.size()) {
    	tau->setGenLepton(dynamic_cast<SignatureObjectMCPart*>(m_mcparticles[pat_tau_genLepton_ntID[i]]));
    }
    tau->setPF_leadTracksignedSipt(pat_tau_PF_leadTracksignedSipt[i]);
    tau->setPF_isoChargedCandMaxPt(pat_tau_PF_isoChargedCandMaxPt[i]);
    tau->setCaloIso(pat_tau_caloIso[i]);//###
    tau->setPF_isoSumPt(pat_tau_PF_isoSumPt[i]);
    tau->setPF_maxHCALhitEt(pat_tau_PF_maxHCALhitEt[i]);
    tau->setCalo_maxHCALhitEt(pat_tau_calo_maxHCALhitEt[i]);
    tau->setPF_isoGammaCandMaxPt(pat_tau_PF_isoGammaCandMaxPt[i]);
    tau->setCalo_isoChargedPtSum(pat_tau_calo_isoChargedPtSum[i]);
    tau->setTrigger_nfilter(pat_tau_trigger_nfilter[i]);
    tau->setSignalTracks_n(pat_tau_signalTracks_n[i]);
    tau->setSignalTracksInvMass(pat_tau_signalTracksInvMass[i]);
    tau->setPF_signalCharge(pat_tau_PF_signalCharge[i]);
    tau->setPF_chargedHadronIso05(pat_tau_PF_chargedHadronIso05[i]);
    tau->setPF_chargedHadronIso03(pat_tau_PF_chargedHadronIso03[i]);

    tau->setPDGid(-15*tau->getCharge());

    for(int j = 0; j < pat_tau_trigger_nfilter[i] && j < 5; j++){
      tau->addTrigger_objectType(pat_tau_trigger_objectType[i][j]);
      tau->addTrigger_objectID(pat_tau_trigger_objectID[i][j]);
    }

    for(int j = 0; j < 50; j++){
      tau->addPF_Discriminants(pat_tau_PF_Discriminants[i][j]);
    }

    for(int j = 0; j < pat_tau_signalTracks_n[i]; j++){
      tau->addSignalTracks_ntIDs(pat_tau_signalTracks_ntIDs[i][j]);
    }

    for(int j = 0; j < pat_tau_isoTracks_n[i]; j++){
      tau->addIsoTracks_ntIDs(pat_tau_isoTracks_ntIDs[i][j]);
    }
    m_taus.push_back(tau);
    //cout<<"tau "<<i<<" "<<pat_tau_pt[i]<<" "<<pat_tau_eta[i]<<" "<<pat_tau_PF_signalCharge[i]<<" "<<pat_tau_PF_Discriminants[i][29]<<" "<<pat_tau_PF_Discriminants[i][19]<<" "<<pat_tau_PF_Discriminants[i][24]<<" "<<pat_tau_PF_Discriminants[i][26]<<endl;
  }
}

//-----------------------------------------
void SignatureHandler::readMCParticles()
{
  for(int i = 0; i < mc_part_n; i++){
    SignatureObjectMCPart* mcpart = new SignatureObjectMCPart(mc_part_px[i],mc_part_py[i],mc_part_pz[i],mc_part_energy[i]);
    mcpart->setPDGid(mc_part_pdgID[i]);
    mcpart->setVx(mc_part_vx[i]);
    mcpart->setVy(mc_part_vy[i]);
    mcpart->setVz(mc_part_vz[i]);
    mcpart->setCharge(mc_part_charge[i]);
    mcpart->setStatus(mc_part_status[i]);
    mcpart->setBarcode(mc_part_barcode[i]);
    mcpart->setMother_pdgID(mc_part_mother_pdgID[i]);
    mcpart->setMother_ntID(mc_part_mother_ntID[i]);
    if(mc_part_mother_ntID[i] >= 0 && mc_part_mother_ntID[i] < (int)m_mcparticles.size()) {
    	mcpart->setMother(dynamic_cast<SignatureObjectMCPart*>(m_mcparticles[mc_part_mother_ntID[i]]));
    }
    mcpart->setN_children(mc_part_n_children[i]);
    m_mcparticles.push_back(mcpart);
  }
}

//-----------------------------------------
void SignatureHandler::readRecoVertices()
{
  for(int i = 0; i < reco_vertex_n; i++){
    SignatureRecoVertex* recovertex = new SignatureRecoVertex(reco_vertex_x[i],reco_vertex_y[i],reco_vertex_z[i]);
    recovertex->setNtrack(reco_vertex_ntrack[i]);
    recovertex->setEx(reco_vertex_ex[i]);
    recovertex->setEy(reco_vertex_ey[i]);
    recovertex->setEz(reco_vertex_ez[i]);
    recovertex->setNdof(reco_vertex_ndof[i]);
    recovertex->setChi2(reco_vertex_chi2[i]);
    recovertex->setWSumPt(reco_vertex_wSumPt[i]);
    m_recovertices.push_back(recovertex);
  }
}

//-----------------------------------------
void SignatureHandler::readBeamSpots()
{
  m_beamspot = new SignatureBeamSpot(reco_beamSpot_x,reco_beamSpot_y,reco_beamSpot_z);
  m_beamspot->setEx(reco_beamSpot_ex);
  m_beamspot->setEy(reco_beamSpot_ey);
  m_beamspot->setEz(reco_beamSpot_ez);
  m_beamspot->setSigmaz(reco_beamSpot_sigmaz);
  m_beamspot->setDxdz(reco_beamSpot_dxdz);
  m_beamspot->setWidth(reco_beamSpot_width);
}
//-----------------------------------------
void SignatureHandler::readTriggers()
{
  for(int i = 0; i < (int)hlt_triggers_npassed; i++){
    SignatureTrigger* trigger = new SignatureTrigger;
    trigger->setTrigger(hlt_triggers[i]);
    trigger->setId(hlt_triggers_id[i]);
    //trigger->setPrescale(hlt_triggers_prescale_L1[i]*hlt_triggers_prescale_HLT[i]);
    trigger->setPrescale(hlt_triggers_prescale_HLT[i]);
    trigger->setWasrun(hlt_triggers_wasrun[i]);
    m_triggers.push_back(trigger);
  }
}
//---------------------------------------
void SignatureHandler::readGoodRunLumi(TString c){
  ifstream infile(c.Data());
  int rrr,lll;
  while(1){
    infile >> rrr >> lll;
    if(!infile.good())break;
    if(m_goodRunLumi.find(rrr) == m_goodRunLumi.end()){
      vector<int> lvec;
      m_goodRunLumi[rrr] = lvec;
    }
    if(find(m_goodRunLumi[rrr].begin(),m_goodRunLumi[rrr].end(),lll) == m_goodRunLumi[rrr].end())m_goodRunLumi[rrr].push_back(lll);
  }

  if(m_goodRunLumi.size() > 0)m_doRunLumiCheck = true;
}
//-------------------------------------
bool SignatureHandler::checkRunLumi(int r, int l)
{
  if(m_goodRunLumi.find(r) == m_goodRunLumi.end())return false;
  if(find(m_goodRunLumi[r].begin(),m_goodRunLumi[r].end(),l) == m_goodRunLumi[r].end())return false;
  return true;

}
//--------------------------------------
void SignatureHandler::readGoodRunLumiFromJSON(TString JSONFile, bool debug)
{
  ifstream inputfile;
  inputfile.open(JSONFile);
  
  bool beginJson = false;
  bool beginRun = false;
  bool beginLumiSet = false;
  bool beginLumiRange = false;
  
  bool firstLumiNumberEnd = false;
  bool secondLumiNumberEnd = false;
  
  Int_t Run = -999;
  
  std::pair<Int_t, Int_t> LumiRange;
  LumiRange.first = -999;
  LumiRange.second = -999;
  std::vector<std::pair<Int_t, Int_t> > Lumis;
  
  if (!inputfile.is_open()) {
    std::cout << "The JSON file you are using does not exist!!!" << std::endl;
    std::cout << "JSON File: " << JSONFile << std::endl;
  }
  
  else {
    std::cout << "The JSON file you are using is: " << JSONFile << std::endl;
    
    while (!inputfile.eof()) {
      char c = inputfile.get();
      char p = inputfile.peek();
      
      // Find beginning of JSON file
      if (c == '{' && beginJson == false && beginRun == false && beginLumiSet ==false && beginLumiRange == false) {
        beginJson = true;
	
        if (debug == true) {
          std::cout << "Found beginning of JSON file: " << c << std::endl;
        }
      }
      
      // Find beginning of Run and fill it
      if (c == '"' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
        beginRun = true;
	
        inputfile >> Run;
	
        if (debug == true) {
          std::cout << "Found beginning of Run: " << c << Run << std::endl;
        }
      }
      
      // Find ending of Run
      if (c == ':' && beginJson == true && beginRun == true && beginLumiSet == false && beginLumiRange == false) {
        beginRun = false;
	
        if (debug == true) {
          std::cout << "Found ending of Run: " << c << std::endl;
        }
      }
      // Find beginning of Lumi Set
      if (c == '[' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
        beginLumiSet = true;
	
        if (debug == true) {
          std::cout << "Found beginning of LumiSet: " << c << std::endl;
        }
      }
      
      // Find begining of Lumi Range and fill it
      if (p == '[' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == false) {
        beginLumiRange = true;
	
        c = inputfile.get();
	
        inputfile >> LumiRange.first;
        LumiRange.second = -999; // Set to -999 in the case that a second value does not exist for the pair

        if (debug == true) {
          std::cout << "Found beginning of LumiRange: " << c << LumiRange.first << std::endl;
        }
      }
      
      // Find middle of Lumi Range and fill it
      if (c == ',' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == true && 
          firstLumiNumberEnd == false && secondLumiNumberEnd == false) {
        firstLumiNumberEnd = true;
	
        inputfile >> LumiRange.second;
	
        secondLumiNumberEnd = true;
      }
      
      // Find ending of Lumi Range
      if (c == ']' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == true) {
        beginLumiRange = false;
	
        if (debug == true) {
          std::cout << "Found ending of LumiRange: " << c << std::endl;
        }
	
        firstLumiNumberEnd = false;
        secondLumiNumberEnd = false;
	
        Lumis.push_back(LumiRange);
      }
      
      // Find ending of Lumi Set
      if (p == ']' && beginJson == true && beginRun == false && beginLumiSet == true && beginLumiRange == false) {
	beginLumiSet = false;
	
        if (debug == true) {
          std::cout << "Found ending of LumiSet: " << c << std::endl;
        }
      }
      
      // Initialize json multimap
      if (p == ']' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
        m_json.insert(std::pair<Int_t, std::vector<std::pair<Int_t, Int_t> > >(Run, Lumis));
	
	
        Run = -999;
        LumiRange.first = -999;
        LumiRange.second = -999;
        Lumis.clear();        
      }
      
      // Find ending of JSON file
      if (c == '}' && beginJson == true && beginRun == false && beginLumiSet == false && beginLumiRange == false) {
        beginJson = false;
	
        if (debug == true) {
          std::cout << "Found ending of JSON file: " << c << std::endl;
        }
      }
    }
  }
  
  inputfile.close();
  
  if (m_json.size() > 0) {
    m_doRunLumiCheckFromJSON = true;
  }
}
//--------------------------------------
void SignatureHandler::printRunLumiJSON()
{
  std::multimap<Int_t, std::vector<std::pair<Int_t, Int_t> > >::iterator store_iter;
  
  std::cout << "The Run and Lumi numbers stored in memory were: " << std::endl;
  
  std::cout << "{";
  
  for (std::multimap<Int_t, std::vector<std::pair<Int_t, Int_t> > >::iterator json_iter = m_json.begin();
       json_iter != m_json.end(); json_iter++) {
    
    store_iter = json_iter;
    
    std::cout << "\"" << json_iter->first << "\": [";
    
    for (std::vector<std::pair<Int_t, Int_t> >::const_iterator lumi_iter = (json_iter->second).begin(); 
         lumi_iter != (json_iter->second).end(); lumi_iter++) {
      
      // First Run of Json file and Run has only one Lumi Range
      if (json_iter == m_json.begin() &&
          std::distance((json_iter->second).begin(),(json_iter->second).end()) == 1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "]], ";
        }
      }
      
      // First Run of Json file and all Lumi Ranges, except last one, of Run and Run has more than one Lumi Range
      if (json_iter == m_json.begin() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 &&
          lumi_iter != (json_iter->second).end()-1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "], ";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "], ";
        }
      }
      
      // First Run of Json file and last Lumi Range of Run and Run has more than one Lumi Range
      if (json_iter == m_json.begin() && std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 &&
          lumi_iter == (json_iter->second).end()-1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "]]";
        }
      }
      
      // Middle Runs of Json file and if Run has only one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter != m_json.end() &&
          std::distance((json_iter->second).begin(),(json_iter->second).end()) == 1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
          store_iter = json_iter;
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "]], ";
          store_iter = json_iter;
        }
      }
      
      else {
        store_iter = json_iter;
      }
      
      // Middle Runs of Json file and all Lumi Ranges, except last one, of Runs and if Runs have more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter != m_json.end() && 
          std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter != (json_iter->second).end()-1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "], ";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "], ";
        }
      }

      else {
	store_iter = json_iter;
      }
      
      // Middle Runs of Json file and last Lumi Range of Runs and Runs have more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter != m_json.end() && 
          std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && 
	  lumi_iter == (json_iter->second).end()-1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]], ";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "], ";
        }
      }
      
      else {
	store_iter = json_iter;
      }
      
      // Last Run of Json file and Run has only one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter == m_json.end() &&
          std::distance((json_iter->second).begin(),(json_iter->second).end()) == 1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]]";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "]]";
        }
      }
      
      else {
	store_iter = json_iter;
      }
      
      // Last Run of Json file and all Lumi Ranges, except last one, of Run and Run has more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter == m_json.end() &&
          std::distance((json_iter->second).begin(),(json_iter->second).end()) > 1 && lumi_iter != (json_iter->second).end()-1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "], ";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "]], ";
        }
      }
      
      else {
	store_iter = json_iter;
      }
      
      // Last Run of Json file and last Lumi Range of Run and Run has more than one Lumi Range
      if (json_iter != m_json.begin() && ++store_iter == m_json.end() &&
          std::distance((json_iter->second).begin(),(json_iter->second).end()) >
	  1 && lumi_iter == (json_iter->second).end()-1) {
        if (lumi_iter->second != -999) {
          std::cout << "[" << lumi_iter->first << ", " << lumi_iter->second << "]]";
        }
	
        else if (lumi_iter->second == -999) {
          std::cout << "[" << lumi_iter->first << "]], ";
        }
      }
      
      else {
	store_iter = json_iter;
      }
    }
  }
  
  std::cout << "}" << std::endl;
}
//--------------------------------------
bool SignatureHandler::checkRunLumiFromJSON(int RunNumber, int LumiNumber, bool debug)
{
  bool foundRun = false;
  bool foundLumi = false;

  if( m_json.size()==0 )
    {
      return true; //If you didn't specify a JSON file, then just pass everything
    }
  
  std::multimap<int, std::vector<std::pair<int, int> > >::iterator json_iter = m_json.find(RunNumber);
  
  if (debug == true) {
    std::cout << "Run: " << RunNumber << " Lumi: " << LumiNumber << std::endl;
  }
  
  // Check whether Run number is found in JSON file
  if (json_iter != m_json.end()) {
    foundRun = true;
  }
  
  // Check whether Lumi number is found in the list of Lumis for the given Run number in the JSON file
  if (foundRun == true) {
    std::vector<std::pair<int, int> > lumis = json_iter->second;
    
    for (std::vector<std::pair<int, int> >::iterator lumis_iter = lumis.begin();
         lumis_iter != lumis.end(); ++lumis_iter) {
      
      if (debug == true) {
        if (lumis_iter->second != -999) {
          std::cout << "Lumi: [" << lumis_iter->first << ", " << lumis_iter->second << "]" << std::endl;
        }
	
        else if (lumis_iter->second == -999){
          std::cout << "Lumi: [" << lumis_iter->first << "]" << std::endl;
        }
      }
      
      if (LumiNumber >= lumis_iter->first && LumiNumber <= lumis_iter->second) {
        if (debug == true) {
          std::cout << "Run: " << RunNumber << " and Lumi: " << LumiNumber << " was found!" << std::endl;
        }
	
        foundLumi = true;
      }
      
      else if (LumiNumber == lumis_iter->first && lumis_iter->second == -999) {
        if (debug == true) {
          std::cout << "Run: " << RunNumber << " and Lumi: " << LumiNumber << " was found!" << std::endl;
        }
	
        foundLumi = true;
      }
      
      else {
        continue;
      }
    }
  }
  
  else {
    if (debug == true) {
      std::cout << "Did not find Run: " << RunNumber << " and Lumi: " << LumiNumber << std::endl;
    }
  }

  return (foundRun && foundLumi);
}
//--------------------------------------
void SignatureHandler::readFilters()
{
  m_filters["primaryVertexFilter"] = (bool)primaryVertexFilter;
  m_filters["noScrapingFilter"] = (bool)noScrapingFilter;
  m_filters["HBHENoiseFilter"] = (bool)HBHENoiseFilter;
  m_filters["CSCTightHaloFilter"] = (bool)CSCTightHaloFilter;
  m_filters["hcalLaserEventFilter"] = (bool)hcalLaserEventFilter;
  m_filters["EcalDeadCellTriggerPrimitiveFilter"] = (bool)EcalDeadCellTriggerPrimitiveFilter;
  m_filters["trackingFailureFilter"] = (bool)trackingFailureFilter;
  m_filters["eeBadScFilter"] = (bool)eeBadScFilter;

}
//--------------------------------------
bool SignatureHandler::passFilter(TString c)
{
  if(m_filters.find(c) == m_filters.end())return false;
  return m_filters[c];
}
//-------------------------------------
void SignatureHandler::printDebugInfo()
{
  TString line1="DEBUGDEBUG ";
  line1+= run;
  line1+= " ";
  line1+= lumiBlock;
  line1+= " ";
  line1+= event;
  line1+= " ";
  for(int i = 0; i < (int)m_product_names.size(); i++){
    TString name = m_product_names[i];
    line1 += name;
    line1 += ": ";
    line1 += getProduct(name).size();
    line1 += ", ";
  }
  cout<<line1<<endl;

}
//====================================
double SignatureHandler::calculateJetBeta(SignatureObjectJet* jet, SignatureRecoVertex* vertex)
{
  double betaNum = 0;
  double betaDen = 0;
  for(int i = 0; i < jet->getNtracks(); i++){
    int id = jet->getTrkIDsAt(i);
    if(id < 0)continue;
    if(id >= (int)m_recotracks.size()) continue;
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[id];
    double dz = fabs(track->getVz() - vertex->Z());
    if(dz < 0.5)betaNum += pow(track->Pt(),2);
    betaDen += pow(track->Pt(),2);
  }
  if(betaDen == 0)return 0;
  return betaNum/betaDen;
}
