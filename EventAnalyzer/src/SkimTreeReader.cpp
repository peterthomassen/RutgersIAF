#include "RutgersIAF2012/EventAnalyzer/interface/SkimTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

ClassImp(SkimTreeReader)

using namespace std;

SkimTreeReader::SkimTreeReader(TTree *tree) : BaseTreeReader(tree)
{
   Init(tree);
}

SkimTreeReader::~SkimTreeReader()
{
   if (!m_tree) return;
   delete m_tree->GetCurrentFile();
}

void SkimTreeReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   m_tree = tree;
   fCurrent = -1;
   m_tree->SetMakeClass(1);

   m_tree->SetBranchAddress("pat_muon_n", &pat_muon_n);
   m_tree->SetBranchAddress("pat_muon_pt", pat_muon_pt);
   m_tree->SetBranchAddress("pat_muon_et", pat_muon_et);
   m_tree->SetBranchAddress("pat_muon_px", pat_muon_px);
   m_tree->SetBranchAddress("pat_muon_py", pat_muon_py);
   m_tree->SetBranchAddress("pat_muon_pz", pat_muon_pz);
   m_tree->SetBranchAddress("pat_muon_eta", pat_muon_eta);
   m_tree->SetBranchAddress("pat_muon_phi", pat_muon_phi);
   m_tree->SetBranchAddress("pat_muon_pmag", pat_muon_pmag);
   m_tree->SetBranchAddress("pat_muon_isPF", pat_muon_isPF);
   m_tree->SetBranchAddress("pat_muon_PFMatchPdgId", pat_muon_PFMatchPdgId);
   m_tree->SetBranchAddress("pat_muon_PFPAT_dpt", pat_muon_PFPAT_dpt);
   m_tree->SetBranchAddress("pat_muon_PFPAT_dphi", pat_muon_PFPAT_dphi);
   m_tree->SetBranchAddress("pat_muon_PFPAT_deta", pat_muon_PFPAT_deta);
   m_tree->SetBranchAddress("pat_muon_PFPAT_dq", pat_muon_PFPAT_dq);
   m_tree->SetBranchAddress("pat_muon_energy", pat_muon_energy);
   m_tree->SetBranchAddress("pat_muon_charge", pat_muon_charge);
   m_tree->SetBranchAddress("pat_muon_trackID", pat_muon_trackID);
   m_tree->SetBranchAddress("pat_muon_globalTrackID", pat_muon_globalTrackID);
   m_tree->SetBranchAddress("pat_muon_muonTrackID", pat_muon_muonTrackID);
   m_tree->SetBranchAddress("pat_muon_caloIso", pat_muon_caloIso);
   m_tree->SetBranchAddress("pat_muon_ecaloIso", pat_muon_ecaloIso);
   m_tree->SetBranchAddress("pat_muon_hcaloIso", pat_muon_hcaloIso);
   m_tree->SetBranchAddress("pat_muon_trackIso", pat_muon_trackIso);
   m_tree->SetBranchAddress("pat_muon_beta", pat_muon_beta);
   m_tree->SetBranchAddress("pat_muon_PF_chargedHadronIso", pat_muon_PF_chargedHadronIso);
   m_tree->SetBranchAddress("pat_muon_PF_photonIso", pat_muon_PF_photonIso);
   m_tree->SetBranchAddress("pat_muon_PF_neutralHadronIso", pat_muon_PF_neutralHadronIso);
   m_tree->SetBranchAddress("pat_muon_allTrackIso", pat_muon_allTrackIso);
   m_tree->SetBranchAddress("pat_muon_vertTrackIso", pat_muon_vertTrackIso);
   m_tree->SetBranchAddress("pat_muon_calEnergyEM", pat_muon_calEnergyEM);
   m_tree->SetBranchAddress("pat_muon_calEnergyHad", pat_muon_calEnergyHad);
   m_tree->SetBranchAddress("pat_muon_ecalIsoDep", pat_muon_ecalIsoDep);
   m_tree->SetBranchAddress("pat_muon_hcalIsoDep", pat_muon_hcalIsoDep);
   m_tree->SetBranchAddress("pat_muon_dRmin", pat_muon_dRmin);
   m_tree->SetBranchAddress("pat_muon_dRmin_track_ntID", pat_muon_dRmin_track_ntID);
   m_tree->SetBranchAddress("pat_muon_dRmin05", pat_muon_dRmin05);
   m_tree->SetBranchAddress("pat_muon_dRmin05_track_ntID", pat_muon_dRmin05_track_ntID);
   m_tree->SetBranchAddress("pat_muon_dRmin10", pat_muon_dRmin10);
   m_tree->SetBranchAddress("pat_muon_dRmin10_track_ntID", pat_muon_dRmin10_track_ntID);
   m_tree->SetBranchAddress("pat_muon_genLepton_dR", pat_muon_genLepton_dR);
   m_tree->SetBranchAddress("pat_muon_genLepton_pdgID", pat_muon_genLepton_pdgID);
   m_tree->SetBranchAddress("pat_muon_genLepton_ntID", pat_muon_genLepton_ntID);
   m_tree->SetBranchAddress("pat_muon_genLepton_mother_pdgID", pat_muon_genLepton_mother_pdgID);
   m_tree->SetBranchAddress("pat_muon_genLepton_mother_ntID", pat_muon_genLepton_mother_ntID);
   m_tree->SetBranchAddress("pat_muon_isGlobalMuon", pat_muon_isGlobalMuon);
   m_tree->SetBranchAddress("pat_muon_isTrackerMuon", pat_muon_isTrackerMuon);
   m_tree->SetBranchAddress("pat_muon_isStandAloneMuon", pat_muon_isStandAloneMuon);
   m_tree->SetBranchAddress("pat_muon_isCaloMuon", pat_muon_isCaloMuon);
   m_tree->SetBranchAddress("pat_muon_isGlobalMuonPromptTight", pat_muon_isGlobalMuonPromptTight);
   m_tree->SetBranchAddress("pat_muon_isTMLastStationTight", pat_muon_isTMLastStationTight);
   m_tree->SetBranchAddress("pat_muon_isTMLastStationAngTight", pat_muon_isTMLastStationAngTight);
   m_tree->SetBranchAddress("pat_muon_trigger_nfilter", pat_muon_trigger_nfilter);
   m_tree->SetBranchAddress("pat_muon_trigger_objectType", pat_muon_trigger_objectType);
   m_tree->SetBranchAddress("pat_muon_trigger_objectID", pat_muon_trigger_objectID);
   m_tree->SetBranchAddress("pat_muon_segmentCompatibility", pat_muon_segmentCompatibility);
   m_tree->SetBranchAddress("pat_muon_isCaloCompatibilityValid", pat_muon_isCaloCompatibilityValid);
   m_tree->SetBranchAddress("pat_muon_caloCompatibility", pat_muon_caloCompatibility);
   m_tree->SetBranchAddress("pat_muon_numberOfMatches", pat_muon_numberOfMatches);
   m_tree->SetBranchAddress("pat_muon_Direction", pat_muon_Direction);
   m_tree->SetBranchAddress("pat_muon_cosmicCompatibility", pat_muon_cosmicCompatibility);
   m_tree->SetBranchAddress("pat_muon_timeCompatibility", pat_muon_timeCompatibility);
   m_tree->SetBranchAddress("pat_muon_backToBackCompatibility", pat_muon_backToBackCompatibility);
   m_tree->SetBranchAddress("pat_muon_overlapCompatibility", pat_muon_overlapCompatibility);
   m_tree->SetBranchAddress("pat_muon_normalizedChi2", pat_muon_normalizedChi2);
   m_tree->SetBranchAddress("pat_muon_innerVertDz", pat_muon_innerVertDz);
   m_tree->SetBranchAddress("pat_muon_innerVertDxy", pat_muon_innerVertDxy);
   m_tree->SetBranchAddress("pat_muon_innerNumberOfValidPixelHits", pat_muon_innerNumberOfValidPixelHits);


   m_tree->SetBranchAddress("pat_electron_n", &pat_electron_n);
   m_tree->SetBranchAddress("pat_electron_pt", pat_electron_pt);
   m_tree->SetBranchAddress("pat_electron_et", pat_electron_et);
   m_tree->SetBranchAddress("pat_electron_px", pat_electron_px);
   m_tree->SetBranchAddress("pat_electron_py", pat_electron_py);
   m_tree->SetBranchAddress("pat_electron_pz", pat_electron_pz);
   m_tree->SetBranchAddress("pat_electron_pmag", pat_electron_pmag);
   m_tree->SetBranchAddress("pat_electron_eta", pat_electron_eta);
   m_tree->SetBranchAddress("pat_electron_phi", pat_electron_phi);
   m_tree->SetBranchAddress("pat_electron_isPF", pat_electron_isPF);
   m_tree->SetBranchAddress("pat_electron_conv_vtxProb", pat_electron_conv_vtxProb);
   m_tree->SetBranchAddress("pat_electron_classification", pat_electron_classification);
   m_tree->SetBranchAddress("pat_electron_PFMatchPdgId", pat_electron_PFMatchPdgId);
   m_tree->SetBranchAddress("pat_electron_PFPAT_dpt", pat_electron_PFPAT_dpt);
   m_tree->SetBranchAddress("pat_electron_PFPAT_dphi", pat_electron_PFPAT_dphi);
   m_tree->SetBranchAddress("pat_electron_PFPAT_deta", pat_electron_PFPAT_deta);
   m_tree->SetBranchAddress("pat_electron_PFPAT_dq", pat_electron_PFPAT_dq);
   m_tree->SetBranchAddress("pat_electron_energy", pat_electron_energy);
   m_tree->SetBranchAddress("pat_electron_charge", pat_electron_charge);
   m_tree->SetBranchAddress("pat_electron_trackID", pat_electron_trackID);
   m_tree->SetBranchAddress("pat_electron_caloIso", pat_electron_caloIso);
   m_tree->SetBranchAddress("pat_electron_trackIso", pat_electron_trackIso);
   m_tree->SetBranchAddress("pat_electron_dRmin", pat_electron_dRmin);
   m_tree->SetBranchAddress("pat_electron_dRmin_track_ntID", pat_electron_dRmin_track_ntID);
   m_tree->SetBranchAddress("pat_electron_genLepton_pdgID", pat_electron_genLepton_pdgID);
   m_tree->SetBranchAddress("pat_electron_genLepton_ntID", pat_electron_genLepton_ntID);
   m_tree->SetBranchAddress("pat_electron_GsfCtfScPixChargeConsistent", pat_electron_GsfCtfScPixChargeConsistent);
   m_tree->SetBranchAddress("pat_electron_GsfScPixChargeConsistent", pat_electron_GsfScPixChargeConsistent);
   m_tree->SetBranchAddress("pat_electron_GsfCtfChargeConsistent", pat_electron_GsfCtfChargeConsistent);
   m_tree->SetBranchAddress("pat_electron_eidTight", pat_electron_eidTight);
   m_tree->SetBranchAddress("pat_electron_eidLoose", pat_electron_eidLoose);
   m_tree->SetBranchAddress("pat_electron_eidRobustTight", pat_electron_eidRobustTight);
   m_tree->SetBranchAddress("pat_electron_eidRobustLoose", pat_electron_eidRobustLoose);
   m_tree->SetBranchAddress("pat_electron_eidRobustHighEnergy", pat_electron_eidRobustHighEnergy);
   m_tree->SetBranchAddress("pat_electron_ecaloIso", pat_electron_ecaloIso);
   m_tree->SetBranchAddress("pat_electron_hcaloIso", pat_electron_hcaloIso);
   m_tree->SetBranchAddress("pat_electron_PF_chargedHadronIso", pat_electron_PF_chargedHadronIso);
   m_tree->SetBranchAddress("pat_electron_PF_photonIso", pat_electron_PF_photonIso);
   m_tree->SetBranchAddress("pat_electron_PF_neutralHadronIso", pat_electron_PF_neutralHadronIso);
   m_tree->SetBranchAddress("pat_electron_PF_chargedHadronIso_04", pat_electron_PF_chargedHadronIso_04);
   m_tree->SetBranchAddress("pat_electron_PF_photonIso_04", pat_electron_PF_photonIso_04);
   m_tree->SetBranchAddress("pat_electron_PF_neutralHadronIso_04", pat_electron_PF_neutralHadronIso_04);
   m_tree->SetBranchAddress("pat_electron_classification_04", pat_electron_classification_04);
   m_tree->SetBranchAddress("pat_electron_caloEnergy", pat_electron_caloEnergy);
   m_tree->SetBranchAddress("pat_electron_hadOverEm", pat_electron_hadOverEm);
   m_tree->SetBranchAddress("pat_electron_eOverPin", pat_electron_eOverPin);
   m_tree->SetBranchAddress("pat_electron_sigmaEtaEta", pat_electron_sigmaEtaEta);
   m_tree->SetBranchAddress("pat_electron_sigmaIetaIeta", pat_electron_sigmaIetaIeta);
   m_tree->SetBranchAddress("pat_electron_e1x5", pat_electron_e1x5);
   m_tree->SetBranchAddress("pat_electron_e2x5Max", pat_electron_e2x5Max);
   m_tree->SetBranchAddress("pat_electron_e5x5", pat_electron_e5x5);
   m_tree->SetBranchAddress("pat_electron_deltaPhi", pat_electron_deltaPhi);
   m_tree->SetBranchAddress("pat_electron_deltaEta", pat_electron_deltaEta);
   m_tree->SetBranchAddress("pat_electron_status", pat_electron_status);
   m_tree->SetBranchAddress("pat_electron_trigger_nfilter", pat_electron_trigger_nfilter);
   m_tree->SetBranchAddress("pat_electron_trigger_objectType", pat_electron_trigger_objectType);
   m_tree->SetBranchAddress("pat_electron_trigger_objectID", pat_electron_trigger_objectID);
   m_tree->SetBranchAddress("pat_electron_fbrem", pat_electron_fbrem);
   m_tree->SetBranchAddress("pat_electron_ecalDriven", pat_electron_ecalDriven);
   m_tree->SetBranchAddress("pat_electron_swissCross", pat_electron_swissCross);
   m_tree->SetBranchAddress("pat_electron_eMax", pat_electron_eMax);
   m_tree->SetBranchAddress("pat_electron_IsConversion", pat_electron_IsConversion);
   m_tree->SetBranchAddress("pat_electron_ConversionDist", pat_electron_ConversionDist);
   m_tree->SetBranchAddress("pat_electron_ConversionDCotTheta", pat_electron_ConversionDCotTheta);
   m_tree->SetBranchAddress("pat_electron_NumberOfExpectedInnerHits", pat_electron_NumberOfExpectedInnerHits);
   m_tree->SetBranchAddress("pat_electron_NumberOfLostInnerHits", pat_electron_NumberOfLostInnerHits);
   m_tree->SetBranchAddress("pat_electron_eSeedClusterOverPout", pat_electron_eSeedClusterOverPout);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_fbrem", pat_electron_fMVAVar_fbrem);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_kfchi2", pat_electron_fMVAVar_kfchi2);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_kfhits", pat_electron_fMVAVar_kfhits);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_gsfchi2", pat_electron_fMVAVar_gsfchi2);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_deta", pat_electron_fMVAVar_deta);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_dphi", pat_electron_fMVAVar_dphi);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_detacalo", pat_electron_fMVAVar_detacalo);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_dphicalo", pat_electron_fMVAVar_dphicalo);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_see", pat_electron_fMVAVar_see);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_spp", pat_electron_fMVAVar_spp);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_etawidth", pat_electron_fMVAVar_etawidth);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_phiwidth", pat_electron_fMVAVar_phiwidth);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_e1x5e5x5", pat_electron_fMVAVar_e1x5e5x5);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_R9", pat_electron_fMVAVar_R9);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_nbrems", pat_electron_fMVAVar_nbrems);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_HoE", pat_electron_fMVAVar_HoE);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_EoP", pat_electron_fMVAVar_EoP);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_IoEmIoP", pat_electron_fMVAVar_IoEmIoP);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_eleEoPout", pat_electron_fMVAVar_eleEoPout);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_PreShowerOverRaw", pat_electron_fMVAVar_PreShowerOverRaw);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_d0", pat_electron_fMVAVar_d0);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_dz", pat_electron_fMVAVar_dz);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_eta", pat_electron_fMVAVar_eta);
   m_tree->SetBranchAddress("pat_electron_fMVAVar_pt", pat_electron_fMVAVar_pt);
   m_tree->SetBranchAddress("pat_jet_n", &pat_jet_n);
   m_tree->SetBranchAddress("pat_rho", &pat_rho);
   m_tree->SetBranchAddress("pat_rho_neutral", &pat_rho_neutral);
   m_tree->SetBranchAddress("pat_jet_pt", pat_jet_pt);
   m_tree->SetBranchAddress("pat_jet_et", pat_jet_et);
   m_tree->SetBranchAddress("pat_jet_raw_pt", pat_jet_raw_pt);
   m_tree->SetBranchAddress("pat_jet_raw_et", pat_jet_raw_et);
   m_tree->SetBranchAddress("pat_jet_px", pat_jet_px);
   m_tree->SetBranchAddress("pat_jet_py", pat_jet_py);
   m_tree->SetBranchAddress("pat_jet_pz", pat_jet_pz);
   m_tree->SetBranchAddress("pat_jet_pmag", pat_jet_pmag);
   m_tree->SetBranchAddress("pat_jet_uncertainty", pat_jet_uncertainty);
   m_tree->SetBranchAddress("pat_jet_eta", pat_jet_eta);
   m_tree->SetBranchAddress("pat_jet_phi", pat_jet_phi);
   m_tree->SetBranchAddress("pat_jet_energy", pat_jet_energy);
   m_tree->SetBranchAddress("pat_jet_etaetaMoment", pat_jet_etaetaMoment);
   m_tree->SetBranchAddress("pat_jet_etaphiMoment", pat_jet_etaphiMoment);
   m_tree->SetBranchAddress("pat_jet_phiphiMoment", pat_jet_phiphiMoment);
   m_tree->SetBranchAddress("pat_jet_genParton_pdgID", pat_jet_genParton_pdgID);
   m_tree->SetBranchAddress("pat_jet_genParton_ntID", pat_jet_genParton_ntID);
   m_tree->SetBranchAddress("pat_jet_bDiscriminator", pat_jet_bDiscriminator);
   m_tree->SetBranchAddress("pat_jet_bDiscriminator_ssVertex", pat_jet_bDiscriminator_ssVertex);
   m_tree->SetBranchAddress("pat_jet_bDiscriminator_ssVertexPure", pat_jet_bDiscriminator_ssVertexPure);
   m_tree->SetBranchAddress("pat_jet_bDiscriminator_combined", pat_jet_bDiscriminator_combined);
   m_tree->SetBranchAddress("pat_jet_bDiscriminator_trackCount", pat_jet_bDiscriminator_trackCount);
   m_tree->SetBranchAddress("pat_jet_bDiscriminator_trackCountPure", pat_jet_bDiscriminator_trackCountPure);
   m_tree->SetBranchAddress("pat_jet_sumTrackPt", pat_jet_sumTrackPt);
   m_tree->SetBranchAddress("pat_jet_bDiscPositive", pat_jet_bDiscPositive);
   m_tree->SetBranchAddress("pat_jet_bDiscNegative", pat_jet_bDiscNegative);
   m_tree->SetBranchAddress("pat_jet_ntracks", pat_jet_ntracks);
   m_tree->SetBranchAddress("pat_jet_ntracks_max", &pat_jet_ntracks_max);
   m_tree->SetBranchAddress("pat_jet_trkIDs", pat_jet_trkIDs);
   m_tree->SetBranchAddress("pat_jet_emf", pat_jet_emf);
   m_tree->SetBranchAddress("pat_jet_ehf", pat_jet_ehf);
   m_tree->SetBranchAddress("pat_jet_chargedHadronFraction", pat_jet_chargedHadronFraction);
   m_tree->SetBranchAddress("pat_jet_neutralHadronFraction", pat_jet_neutralHadronFraction);
   m_tree->SetBranchAddress("pat_jet_chargedEMFraction", pat_jet_chargedEMFraction);
   m_tree->SetBranchAddress("pat_jet_neutralEMFraction", pat_jet_neutralEMFraction);
   m_tree->SetBranchAddress("pat_jet_chargedHadronMultiplicity", pat_jet_chargedHadronMultiplicity);
   m_tree->SetBranchAddress("pat_jet_numberConstituents", pat_jet_numberConstituents);

   m_tree->SetBranchAddress("pat_jet_charge", pat_jet_charge);
   m_tree->SetBranchAddress("pat_jet_mass", pat_jet_mass);
   m_tree->SetBranchAddress("pat_jet_vx", pat_jet_vx);
   m_tree->SetBranchAddress("pat_jet_vy", pat_jet_vy);
   m_tree->SetBranchAddress("pat_jet_vz", pat_jet_vz);
   m_tree->SetBranchAddress("pat_jet_isCalo", pat_jet_isCalo);
   m_tree->SetBranchAddress("pat_jet_isPF", pat_jet_isPF);
   m_tree->SetBranchAddress("pat_jet_corrLevel", pat_jet_corrLevel);
   m_tree->SetBranchAddress("pat_jet_corr_glue", pat_jet_corr_glue);
   m_tree->SetBranchAddress("pat_jet_corr_uds", pat_jet_corr_uds);
   m_tree->SetBranchAddress("pat_jet_corr_c", pat_jet_corr_c);
   m_tree->SetBranchAddress("pat_jet_corr_b", pat_jet_corr_b);
   m_tree->SetBranchAddress("pat_jet_trigger_nfilter", pat_jet_trigger_nfilter);
   m_tree->SetBranchAddress("pat_jet_trigger_objectType", pat_jet_trigger_objectType);
   m_tree->SetBranchAddress("pat_jet_trigger_objectID", pat_jet_trigger_objectID);
   m_tree->SetBranchAddress("pat_jet_loose_PFjetID", pat_jet_loose_PFjetID);
   m_tree->SetBranchAddress("pat_jet_medium_PFjetID", pat_jet_medium_PFjetID);
   m_tree->SetBranchAddress("pat_jet_tight_PFjetID", pat_jet_tight_PFjetID);
   m_tree->SetBranchAddress("mc_pdfSetA_N", &mc_pdfSetA_N);
   m_tree->SetBranchAddress("mc_pdfSetA", mc_pdfSetA);
   m_tree->SetBranchAddress("mc_pdfSetB_N", &mc_pdfSetB_N);
   m_tree->SetBranchAddress("mc_pdfSetB", mc_pdfSetB);
   m_tree->SetBranchAddress("mc_pdfSetC_N", &mc_pdfSetC_N);
   m_tree->SetBranchAddress("mc_pdfSetC", mc_pdfSetC);
   m_tree->SetBranchAddress("mc_signature_nJets", &mc_signature_nJets);
   m_tree->SetBranchAddress("mc_signature_nbJets", &mc_signature_nbJets);
   m_tree->SetBranchAddress("mc_signature_nPhotons", &mc_signature_nPhotons);
   m_tree->SetBranchAddress("mc_signature_nMuons", &mc_signature_nMuons);
   m_tree->SetBranchAddress("mc_signature_charge_Muons", &mc_signature_charge_Muons);
   m_tree->SetBranchAddress("mc_signature_nElectrons", &mc_signature_nElectrons);
   m_tree->SetBranchAddress("mc_signature_charge_Electrons", &mc_signature_charge_Electrons);
   m_tree->SetBranchAddress("mc_signature_nTaus", &mc_signature_nTaus);
   m_tree->SetBranchAddress("mc_signature_charge_Taus", &mc_signature_charge_Taus);
   m_tree->SetBranchAddress("mc_signature_met", &mc_signature_met);
   m_tree->SetBranchAddress("mc_susyscan_vars", mc_susyscan_vars);
   m_tree->SetBranchAddress("mc_part_n", &mc_part_n);
   m_tree->SetBranchAddress("mc_part_pdgID", &mc_part_pdgID);
   m_tree->SetBranchAddress("mc_part_mass", &mc_part_mass);
   m_tree->SetBranchAddress("mc_part_pt", &mc_part_pt);
   m_tree->SetBranchAddress("mc_part_et", &mc_part_et);
   m_tree->SetBranchAddress("mc_part_vx", &mc_part_vx);
   m_tree->SetBranchAddress("mc_part_vy", &mc_part_vy);
   m_tree->SetBranchAddress("mc_part_vz", &mc_part_vz);
   m_tree->SetBranchAddress("mc_part_charge", &mc_part_charge);
   m_tree->SetBranchAddress("mc_part_px", &mc_part_px);
   m_tree->SetBranchAddress("mc_part_py", &mc_part_py);
   m_tree->SetBranchAddress("mc_part_pz", &mc_part_pz);
   m_tree->SetBranchAddress("mc_part_pmag", &mc_part_pmag);
   m_tree->SetBranchAddress("mc_part_eta", &mc_part_eta);
   m_tree->SetBranchAddress("mc_part_phi", &mc_part_phi);
   m_tree->SetBranchAddress("mc_part_energy", &mc_part_energy);
   m_tree->SetBranchAddress("mc_part_status", &mc_part_status);
   m_tree->SetBranchAddress("mc_part_barcode", &mc_part_barcode);
   m_tree->SetBranchAddress("mc_part_mother_pdgID", &mc_part_mother_pdgID);
   m_tree->SetBranchAddress("mc_part_mother_ntID", &mc_part_mother_ntID);
   m_tree->SetBranchAddress("mc_part_n_children", &mc_part_n_children);
   m_tree->SetBranchAddress("reco_beamHalo_EventSmellsLikeHalo", &reco_beamHalo_EventSmellsLikeHalo);
   m_tree->SetBranchAddress("reco_beamHalo_CSCTightHaloId", &reco_beamHalo_CSCTightHaloId);
   m_tree->SetBranchAddress("reco_beamHalo_CSCLooseHaloId", &reco_beamHalo_CSCLooseHaloId);
   m_tree->SetBranchAddress("reco_beamHalo_nCSChaloTriggers", &reco_beamHalo_nCSChaloTriggers);
   m_tree->SetBranchAddress("reco_beamHalo_nCSChaloTracks", &reco_beamHalo_nCSChaloTracks);
   m_tree->SetBranchAddress("reco_beamHalo_nCSCoutOfTimeTriggers", &reco_beamHalo_nCSCoutOfTimeTriggers);
   m_tree->SetBranchAddress("reco_beamSpot_x", &reco_beamSpot_x);
   m_tree->SetBranchAddress("reco_beamSpot_y", &reco_beamSpot_y);
   m_tree->SetBranchAddress("reco_beamSpot_z", &reco_beamSpot_z);
   m_tree->SetBranchAddress("reco_beamSpot_ex", &reco_beamSpot_ex);
   m_tree->SetBranchAddress("reco_beamSpot_ey", &reco_beamSpot_ey);
   m_tree->SetBranchAddress("reco_beamSpot_ez", &reco_beamSpot_ez);
   m_tree->SetBranchAddress("reco_beamSpot_sigmaz", &reco_beamSpot_sigmaz);
   m_tree->SetBranchAddress("reco_beamSpot_dxdz", &reco_beamSpot_dxdz);
   m_tree->SetBranchAddress("reco_beamSpot_width", &reco_beamSpot_width);
   m_tree->SetBranchAddress("reco_track_n", &reco_track_n);
   m_tree->SetBranchAddress("reco_track_genParticle_dR", reco_track_genParticle_dR);
   m_tree->SetBranchAddress("reco_track_genParticle_pdgID", reco_track_genParticle_pdgID);
   m_tree->SetBranchAddress("reco_track_genParticle_ntID", reco_track_genParticle_ntID);
   m_tree->SetBranchAddress("reco_track_genParticle_mother_pdgID", reco_track_genParticle_mother_pdgID);
   m_tree->SetBranchAddress("reco_track_genParticle_mother_ntID", reco_track_genParticle_mother_ntID);
   m_tree->SetBranchAddress("reco_track_nValidHits", reco_track_nValidHits);
   m_tree->SetBranchAddress("reco_track_ntrackerLayersWM", reco_track_ntrackerLayersWM);
   m_tree->SetBranchAddress("reco_track_npixelLayersWM", reco_track_npixelLayersWM);
   m_tree->SetBranchAddress("reco_track_nstripLayersWM", reco_track_nstripLayersWM);
   m_tree->SetBranchAddress("reco_track_muonStationsWVH", reco_track_muonStationsWVH);
   m_tree->SetBranchAddress("reco_track_muonStationsWAH", reco_track_muonStationsWAH);
   m_tree->SetBranchAddress("reco_track_nBadMuonHits", reco_track_nBadMuonHits);
   m_tree->SetBranchAddress("reco_track_outermostMuonStationWithValidHits", reco_track_outermostMuonStationWithValidHits);
   m_tree->SetBranchAddress("reco_track_nValidMuonHitsInFirstStation", reco_track_nValidMuonHitsInFirstStation);
   m_tree->SetBranchAddress("reco_track_nLostMuonHitsInFirstStation", reco_track_nLostMuonHitsInFirstStation);
   m_tree->SetBranchAddress("reco_track_nBadMuonHitsInFirstStation", reco_track_nBadMuonHitsInFirstStation);
   m_tree->SetBranchAddress("reco_track_nAnyMuonHitsInFirstStation", reco_track_nAnyMuonHitsInFirstStation);
   m_tree->SetBranchAddress("reco_track_nValidTrackerHits", reco_track_nValidTrackerHits);
   m_tree->SetBranchAddress("reco_track_nValidMuonHits", reco_track_nValidMuonHits);
   m_tree->SetBranchAddress("reco_track_nValidPixelHits", reco_track_nValidPixelHits);
   m_tree->SetBranchAddress("reco_track_nLostHits", reco_track_nLostHits);
   m_tree->SetBranchAddress("reco_track_nLostTrackerHits", reco_track_nLostTrackerHits);
   m_tree->SetBranchAddress("reco_track_nLostMuonHits", reco_track_nLostMuonHits);
   m_tree->SetBranchAddress("reco_track_nLostPixelHits", reco_track_nLostPixelHits);
   m_tree->SetBranchAddress("reco_track_isGlobal", reco_track_isGlobal);
   m_tree->SetBranchAddress("reco_track_isMuon", reco_track_isMuon);
   m_tree->SetBranchAddress("reco_track_isTracker", reco_track_isTracker);
   m_tree->SetBranchAddress("reco_track_pt", reco_track_pt);
   m_tree->SetBranchAddress("reco_track_px", reco_track_px);
   m_tree->SetBranchAddress("reco_track_py", reco_track_py);
   m_tree->SetBranchAddress("reco_track_pz", reco_track_pz);
   m_tree->SetBranchAddress("reco_track_vx", reco_track_vx);
   m_tree->SetBranchAddress("reco_track_vy", reco_track_vy);
   m_tree->SetBranchAddress("reco_track_vz", reco_track_vz);
   m_tree->SetBranchAddress("reco_track_chi2", reco_track_chi2);
   m_tree->SetBranchAddress("reco_track_ndof", reco_track_ndof);
   m_tree->SetBranchAddress("reco_track_charge", reco_track_charge);
   m_tree->SetBranchAddress("reco_track_dxy", reco_track_dxy);
   m_tree->SetBranchAddress("reco_track_dsz", reco_track_dsz);
   m_tree->SetBranchAddress("reco_track_d0", reco_track_d0);
   m_tree->SetBranchAddress("reco_track_dz", reco_track_dz);
   m_tree->SetBranchAddress("reco_track_vert_dxy", reco_track_vert_dxy);
   m_tree->SetBranchAddress("reco_track_vert_dz", reco_track_vert_dz);
   m_tree->SetBranchAddress("reco_track_beam_dxy", reco_track_beam_dxy);
   m_tree->SetBranchAddress("reco_track_beam_dsz", reco_track_beam_dsz);
   m_tree->SetBranchAddress("reco_track_beam_d0", reco_track_beam_d0);
   m_tree->SetBranchAddress("reco_track_beam_dz", reco_track_beam_dz);
   m_tree->SetBranchAddress("reco_track_phi", reco_track_phi);
   m_tree->SetBranchAddress("reco_track_eta", reco_track_eta);
   m_tree->SetBranchAddress("reco_track_theta", reco_track_theta);
   m_tree->SetBranchAddress("reco_track_dxyError", reco_track_dxyError);
   m_tree->SetBranchAddress("reco_track_d0Error", reco_track_d0Error);
   m_tree->SetBranchAddress("reco_track_dzError", reco_track_dzError);
   m_tree->SetBranchAddress("reco_track_phiError", reco_track_phiError);
   m_tree->SetBranchAddress("reco_track_etaError", reco_track_etaError);
   m_tree->SetBranchAddress("reco_track_thetaError", reco_track_thetaError);
   m_tree->SetBranchAddress("reco_track_lambdaError", reco_track_lambdaError);
   m_tree->SetBranchAddress("reco_track_trackIso", reco_track_trackIso);
   m_tree->SetBranchAddress("reco_track_caloIso", reco_track_caloIso);
   m_tree->SetBranchAddress("reco_track_trackIso1", reco_track_trackIso1);
   m_tree->SetBranchAddress("reco_track_caloIso1", reco_track_caloIso1);
   m_tree->SetBranchAddress("reco_track_trackIso2", reco_track_trackIso2);
   m_tree->SetBranchAddress("reco_track_caloIso2", reco_track_caloIso2);
   m_tree->SetBranchAddress("reco_track_trackIso6", reco_track_trackIso6);
   m_tree->SetBranchAddress("reco_track_caloIso6", reco_track_caloIso6);
   m_tree->SetBranchAddress("reco_track_trackIso9", reco_track_trackIso9);
   m_tree->SetBranchAddress("reco_track_caloIso9", reco_track_caloIso9);
   m_tree->SetBranchAddress("reco_track_trackIso12", reco_track_trackIso12);
   m_tree->SetBranchAddress("reco_track_caloIso12", reco_track_caloIso12);
   m_tree->SetBranchAddress("reco_track_ecaloIso", reco_track_ecaloIso);
   m_tree->SetBranchAddress("reco_track_hcaloIso", reco_track_hcaloIso);
   m_tree->SetBranchAddress("reco_track_vertWeight", reco_track_vertWeight);
   m_tree->SetBranchAddress("reco_track_PF_chargedHadronIso", reco_track_PF_chargedHadronIso);
   m_tree->SetBranchAddress("reco_track_PF_photonIso", reco_track_PF_photonIso);
   m_tree->SetBranchAddress("reco_track_PF_neutralHadronIso", reco_track_PF_neutralHadronIso);
   m_tree->SetBranchAddress("reco_vertex_n", &reco_vertex_n);
   m_tree->SetBranchAddress("reco_vertex_ntrack", reco_vertex_ntrack);
   m_tree->SetBranchAddress("reco_vertex_x", reco_vertex_x);
   m_tree->SetBranchAddress("reco_vertex_y", reco_vertex_y);
   m_tree->SetBranchAddress("reco_vertex_z", reco_vertex_z);
   m_tree->SetBranchAddress("reco_vertex_ex", reco_vertex_ex);
   m_tree->SetBranchAddress("reco_vertex_ey", reco_vertex_ey);
   m_tree->SetBranchAddress("reco_vertex_ez", reco_vertex_ez);
   m_tree->SetBranchAddress("reco_vertex_ndof", reco_vertex_ndof);
   m_tree->SetBranchAddress("reco_vertex_chi2", reco_vertex_chi2);
   m_tree->SetBranchAddress("reco_vertex_wSumPt", reco_vertex_wSumPt);
   m_tree->SetBranchAddress("pat_met_sumEt", &pat_met_sumEt);
   m_tree->SetBranchAddress("pat_met_mEtSig", &pat_met_mEtSig);
   m_tree->SetBranchAddress("pat_met_gen_sumEt", &pat_met_gen_sumEt);
   m_tree->SetBranchAddress("pat_met_px", &pat_met_px);
   m_tree->SetBranchAddress("pat_met_py", &pat_met_py);
   m_tree->SetBranchAddress("pat_met_pz", &pat_met_pz);
   m_tree->SetBranchAddress("pat_met_pt", &pat_met_pt);
   m_tree->SetBranchAddress("pat_met_eta", &pat_met_eta);
   m_tree->SetBranchAddress("pat_met_phi", &pat_met_phi);
   m_tree->SetBranchAddress("pat_met_trigger_nfilter", &pat_met_trigger_nfilter);
   m_tree->SetBranchAddress("pat_met_trigger_objectType", pat_met_trigger_objectType);
   m_tree->SetBranchAddress("pat_met_trigger_objectID", pat_met_trigger_objectID);
   m_tree->SetBranchAddress("pf_met_sumEt", &pf_met_sumEt);
   m_tree->SetBranchAddress("pf_met_pt", &pf_met_pt);
   m_tree->SetBranchAddress("pf_met_phi", &pf_met_phi);
   m_tree->SetBranchAddress("pf_met_type1_sumEt", &pf_met_type1_sumEt);
   m_tree->SetBranchAddress("pf_met_type1_pt", &pf_met_type1_pt);
   m_tree->SetBranchAddress("pf_met_type1_phi", &pf_met_type1_phi);
   m_tree->SetBranchAddress("tc_met_sumEt", &tc_met_sumEt);
   m_tree->SetBranchAddress("tc_met_pt", &tc_met_pt);
   m_tree->SetBranchAddress("tc_met_phi", &tc_met_phi);
   m_tree->SetBranchAddress("event", &event);
   m_tree->SetBranchAddress("run", &run);
   m_tree->SetBranchAddress("isRealData", &isRealData);
   m_tree->SetBranchAddress("bunchCrossing", &bunchCrossing);
   m_tree->SetBranchAddress("storeNumber", &storeNumber);
   m_tree->SetBranchAddress("lumiBlock", &lumiBlock);
   m_tree->SetBranchAddress("pileup_trueNumInteractions", &pileup_trueNumInteractions);
   m_tree->SetBranchAddress("pileup_numInteractions", &pileup_numInteractions);
   m_tree->SetBranchAddress("pileup_bunchCrossing", &pileup_bunchCrossing);
   m_tree->SetBranchAddress("event_mc_processID", &event_mc_processID);
   m_tree->SetBranchAddress("event_mc_sigma_input", &event_mc_sigma_input);
   m_tree->SetBranchAddress("event_mc_sigma_calc", &event_mc_sigma_calc);
   m_tree->SetBranchAddress("event_mc_eff_input", &event_mc_eff_input);
   m_tree->SetBranchAddress("pat_tau_n", &pat_tau_n);
   m_tree->SetBranchAddress("pat_tau_pt", pat_tau_pt);
   m_tree->SetBranchAddress("pat_tau_px", pat_tau_px);
   m_tree->SetBranchAddress("pat_tau_py", pat_tau_py);
   m_tree->SetBranchAddress("pat_tau_pz", pat_tau_pz);
   m_tree->SetBranchAddress("pat_tau_pmag", pat_tau_pmag);
   m_tree->SetBranchAddress("pat_tau_eta", pat_tau_eta);
   m_tree->SetBranchAddress("pat_tau_emFraction", pat_tau_emFraction);
   m_tree->SetBranchAddress("pat_tau_phi", pat_tau_phi);
   m_tree->SetBranchAddress("pat_tau_trackIso", pat_tau_trackIso);
   m_tree->SetBranchAddress("pat_tau_caloIso", pat_tau_caloIso);
   m_tree->SetBranchAddress("pat_tau_genLepton_pdgID", pat_tau_genLepton_pdgID);
   m_tree->SetBranchAddress("pat_tau_genLepton_ntID", pat_tau_genLepton_ntID);
   m_tree->SetBranchAddress("pat_tau_signalTracksInvMass", pat_tau_signalTracksInvMass);
   m_tree->SetBranchAddress("pat_tau_isCalo", pat_tau_isCalo);
   m_tree->SetBranchAddress("pat_tau_isPF", pat_tau_isPF);
   m_tree->SetBranchAddress("pat_tau_leadTrack_ntID", pat_tau_leadTrack_ntID);
   m_tree->SetBranchAddress("pat_tau_signalTracks_n", pat_tau_signalTracks_n);
   m_tree->SetBranchAddress("pat_tau_signalTracks_ntIDs", pat_tau_signalTracks_ntIDs);
   m_tree->SetBranchAddress("pat_tau_isoTracks_n", pat_tau_isoTracks_n);
   m_tree->SetBranchAddress("pat_tau_isoTracks_ntIDs", pat_tau_isoTracks_ntIDs);
   m_tree->SetBranchAddress("pat_tau_calo_leadTracksignedSipt", pat_tau_calo_leadTracksignedSipt);
   m_tree->SetBranchAddress("pat_tau_calo_isoChargedPtSum", pat_tau_calo_isoChargedPtSum);
   m_tree->SetBranchAddress("pat_tau_calo_isoECALEtSum", pat_tau_calo_isoECALEtSum);
   m_tree->SetBranchAddress("pat_tau_calo_maxHCALhitEt", pat_tau_calo_maxHCALhitEt);
   m_tree->SetBranchAddress("pat_tau_PF_leadTracksignedSipt", pat_tau_PF_leadTracksignedSipt);
   m_tree->SetBranchAddress("pat_tau_PF_isoChargedPtSum", pat_tau_PF_isoChargedPtSum);
   m_tree->SetBranchAddress("pat_tau_PF_isoGammaEtSum", pat_tau_PF_isoGammaEtSum);
   m_tree->SetBranchAddress("pat_tau_PF_isoSumPt", pat_tau_PF_isoSumPt);
   m_tree->SetBranchAddress("pat_tau_PF_maxHCALhitEt", pat_tau_PF_maxHCALhitEt);
   m_tree->SetBranchAddress("pat_tau_PF_chargedHadronIso03", pat_tau_PF_chargedHadronIso03);
   m_tree->SetBranchAddress("pat_tau_PF_neutralHadronIso03", pat_tau_PF_neutralHadronIso03);
   m_tree->SetBranchAddress("pat_tau_PF_photonIso03", pat_tau_PF_photonIso03);
   m_tree->SetBranchAddress("pat_tau_PF_chargedHadronIso05", pat_tau_PF_chargedHadronIso05);
   m_tree->SetBranchAddress("pat_tau_PF_neutralHadronIso05", pat_tau_PF_neutralHadronIso05);
   m_tree->SetBranchAddress("pat_tau_PF_photonIso05", pat_tau_PF_photonIso05);
   m_tree->SetBranchAddress("pat_tau_PF_isoChargedCandMaxPt", pat_tau_PF_isoChargedCandMaxPt);
   m_tree->SetBranchAddress("pat_tau_PF_isoGammaCandMaxPt", pat_tau_PF_isoGammaCandMaxPt);
   m_tree->SetBranchAddress("pat_tau_PF_isoKlongCandMaxPt", pat_tau_PF_isoKlongCandMaxPt);
   m_tree->SetBranchAddress("pat_tau_PF_NsigCharged", pat_tau_PF_NsigCharged);
   m_tree->SetBranchAddress("pat_tau_PF_NsigGamma", pat_tau_PF_NsigGamma);
   m_tree->SetBranchAddress("pat_tau_PF_signalMass", pat_tau_PF_signalMass);
   m_tree->SetBranchAddress("pat_tau_PF_signalCharge", pat_tau_PF_signalCharge);
   m_tree->SetBranchAddress("pat_tau_PF_againstMuon", pat_tau_PF_againstMuon);
   m_tree->SetBranchAddress("pat_tau_PF_againstElectron", pat_tau_PF_againstElectron);
   m_tree->SetBranchAddress("pat_tau_PF_Discriminants", pat_tau_PF_Discriminants);
   m_tree->SetBranchAddress("pat_tau_trigger_nfilter", pat_tau_trigger_nfilter);
   m_tree->SetBranchAddress("pat_tau_trigger_objectType", pat_tau_trigger_objectType);
   m_tree->SetBranchAddress("pat_tau_trigger_objectID", pat_tau_trigger_objectID);
   m_tree->SetBranchAddress("pat_photon_n", &pat_photon_n);
   m_tree->SetBranchAddress("pat_photon_pt", pat_photon_pt);
   m_tree->SetBranchAddress("pat_photon_px", pat_photon_px);
   m_tree->SetBranchAddress("pat_photon_py", pat_photon_py);
   m_tree->SetBranchAddress("pat_photon_pz", pat_photon_pz);
   m_tree->SetBranchAddress("pat_photon_eta", pat_photon_eta);
   m_tree->SetBranchAddress("pat_photon_phi", pat_photon_phi);
   m_tree->SetBranchAddress("pat_photon_pmag", pat_photon_pmag);
   m_tree->SetBranchAddress("pat_photon_trackIso", pat_photon_trackIso);
   m_tree->SetBranchAddress("pat_photon_caloIso", pat_photon_caloIso);
   m_tree->SetBranchAddress("pat_photon_genPhoton_pdgID", pat_photon_genPhoton_pdgID);
   m_tree->SetBranchAddress("pat_photon_genPhoton_ntID", pat_photon_genPhoton_ntID);
   m_tree->SetBranchAddress("pat_photon_trigger_nfilter", pat_photon_trigger_nfilter);
   m_tree->SetBranchAddress("pat_photon_trigger_objectType", pat_photon_trigger_objectType);
   m_tree->SetBranchAddress("pat_photon_trigger_objectID", pat_photon_trigger_objectID);
   m_tree->SetBranchAddress("pat_photon_hadOverEm", pat_photon_hadOverEm);
   m_tree->SetBranchAddress("pat_photon_hadTowOverEm", pat_photon_hadTowOverEm);
   m_tree->SetBranchAddress("pat_photon_conversionSafeElectronVeto", pat_photon_conversionSafeElectronVeto);
   m_tree->SetBranchAddress("pat_photon_sigmaIetaIeta", pat_photon_sigmaIetaIeta);
   m_tree->SetBranchAddress("pat_photon_endcap", pat_photon_endcap);
   m_tree->SetBranchAddress("pat_photon_barrel", pat_photon_barrel);
   m_tree->SetBranchAddress("pat_photon_scEt", pat_photon_scEt);
   m_tree->SetBranchAddress("pat_photon_isLoose", pat_photon_isLoose);
   m_tree->SetBranchAddress("pat_photon_isTight", pat_photon_isTight);
   m_tree->SetBranchAddress("pat_photon_ecalRecHitEtR03", pat_photon_ecalRecHitEtR03);
   m_tree->SetBranchAddress("pat_photon_hcalTowerEtR03", pat_photon_hcalTowerEtR03);
   m_tree->SetBranchAddress("pat_photon_hcalDepth1TowerEtR03", pat_photon_hcalDepth1TowerEtR03);
   m_tree->SetBranchAddress("pat_photon_hcalDepth2TowerEtR03", pat_photon_hcalDepth2TowerEtR03);
   m_tree->SetBranchAddress("pat_photon_ecalRecHitEtR04", pat_photon_ecalRecHitEtR04);
   m_tree->SetBranchAddress("pat_photon_hcalTowerEtR04", pat_photon_hcalTowerEtR04);
   m_tree->SetBranchAddress("pat_photon_hcalDepth1TowerEtR04", pat_photon_hcalDepth1TowerEtR04);
   m_tree->SetBranchAddress("pat_photon_hcalDepth2TowerEtR04", pat_photon_hcalDepth2TowerEtR04);
   m_tree->SetBranchAddress("pat_photon_trackSumPtHollowR03", pat_photon_trackSumPtHollowR03);
   m_tree->SetBranchAddress("pat_photon_trackSumPtHollowR04", pat_photon_trackSumPtHollowR04);
   m_tree->SetBranchAddress("pat_photon_trackSumPtSolidR03", pat_photon_trackSumPtSolidR03);
   m_tree->SetBranchAddress("pat_photon_trackSumPtSolidR04", pat_photon_trackSumPtSolidR04);
   m_tree->SetBranchAddress("pat_photon_mustacheEt", pat_photon_mustacheEt);
   m_tree->SetBranchAddress("pat_photon_MVAGlobalCorrEError", pat_photon_MVAGlobalCorrEError);
   m_tree->SetBranchAddress("pat_photon_MVAGlobalCorrE", pat_photon_MVAGlobalCorrE);
   m_tree->SetBranchAddress("pat_photon_PFPhotonRes", pat_photon_PFPhotonRes);
   m_tree->SetBranchAddress("pat_photon_chargedHadronIso", pat_photon_chargedHadronIso);
   m_tree->SetBranchAddress("pat_photon_neutralHadronIso", pat_photon_neutralHadronIso);
   m_tree->SetBranchAddress("pat_photon_photonIso", pat_photon_photonIso);
   m_tree->SetBranchAddress("pat_photon_r9", pat_photon_r9);
   m_tree->SetBranchAddress("pat_photon_EOut", pat_photon_EOut);
   m_tree->SetBranchAddress("pat_photon_track_nHollowR03", pat_photon_track_nHollowR03);
   m_tree->SetBranchAddress("pat_photon_track_nHollowR04", pat_photon_track_nHollowR04);
   m_tree->SetBranchAddress("pat_photon_track_nSolidR03", pat_photon_track_nSolidR03);
   m_tree->SetBranchAddress("pat_photon_track_nSolidR04", pat_photon_track_nSolidR04);
   m_tree->SetBranchAddress("hlt_triggers_npassed", &hlt_triggers_npassed);
   m_tree->SetBranchAddress("hlt_triggers", hlt_triggers);
   m_tree->SetBranchAddress("hlt_triggers_id", hlt_triggers_id);
   m_tree->SetBranchAddress("hlt_triggers_prescale", hlt_triggers_prescale);
   m_tree->SetBranchAddress("hlt_triggers_prescale_L1", hlt_triggers_prescale_L1);
   m_tree->SetBranchAddress("hlt_triggers_prescale_HLT", hlt_triggers_prescale_HLT);
   m_tree->SetBranchAddress("hlt_triggers_wasrun", hlt_triggers_wasrun);
   m_tree->SetBranchAddress("primaryVertexFilter", &primaryVertexFilter);
   m_tree->SetBranchAddress("noScrapingFilter", &noScrapingFilter);
   m_tree->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter);
   m_tree->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter);
   m_tree->SetBranchAddress("hcalLaserEventFilter", &hcalLaserEventFilter);
   m_tree->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
   m_tree->SetBranchAddress("trackingFailureFilter", &trackingFailureFilter);
   m_tree->SetBranchAddress("eeBadScFilter", &eeBadScFilter);

}


void SkimTreeReader::createProducts()
{
  createMCParticles();
  createTracks();
  createRecoVertices();
  createMuons();
  createElectrons();
  createPhotons();
  createJets();
  createMET();
  createTaus();
  createTriggers();
  createVariables();
}

void SkimTreeReader::createMCParticles()
{
  vector<SignatureObject*> mcparticles;
  for(int i = 0; i < mc_part_n; i++){
    SignatureObject* mcpart = new SignatureObject(mc_part_px[i],mc_part_py[i],mc_part_pz[i],mc_part_energy[i]);
    mcpart->setVariable("PDGID",mc_part_pdgID[i]);
    mcpart->setVariable("VX",mc_part_vx[i]);
    mcpart->setVariable("VY",mc_part_vy[i]);
    mcpart->setVariable("VZ",mc_part_vz[i]);
    mcpart->setVariable("CHARGE",mc_part_charge[i]);
    mcpart->setVariable("STATUS",mc_part_status[i]);
    mcpart->setVariable("BARCODE",mc_part_barcode[i]);
    mcpart->setVariable("MOTHER_PDGID",mc_part_mother_pdgID[i]);
    mcpart->setVariable("MOTHER_NTID",mc_part_mother_ntID[i]);
    if(mc_part_mother_ntID[i] >= 0 && mc_part_mother_ntID[i] < (int)mcparticles.size()) {
      mcpart->setAssociate("MOTHER",mcparticles[mc_part_mother_ntID[i]]);
    }
    mcpart->setVariable("N_CHILDREN",mc_part_n_children[i]);
    mcparticles.push_back(mcpart);
  }
  m_products["ALLMCPARTICLES"] = mcparticles;
}

void SkimTreeReader::createTracks()
{
  vector<SignatureObject*> recotracks;
  vector<SignatureObject*> mcparticles = getProduct("ALLMCPARTICLES");
  for(int i = 0; i < reco_track_n; i++){
    SignatureObject* recotrack = new SignatureObject(0,0,0,0);
    recotrack->SetPtEtaPhiM(reco_track_pt[i],reco_track_eta[i],reco_track_phi[i],0);
    if(reco_track_genParticle_ntID[i] >= 0 && reco_track_genParticle_ntID[i] < (int)mcparticles.size()) {
      recotrack->setAssociate("GENPARTICLE",mcparticles[reco_track_genParticle_ntID[i]]);
    }
    recotrack->setVariable("RHO",pat_rho);
    recotrack->setVariable("CHARGEDHADRONISO",reco_track_PF_chargedHadronIso[i]);
    recotrack->setVariable("NEUTRALHADRONISO",reco_track_PF_neutralHadronIso[i]);
    recotrack->setVariable("PHOTONISO",reco_track_PF_photonIso[i]);
    recotrack->setVariable("DZ",reco_track_dz[i]);
    recotrack->setVariable("ECALOISO",reco_track_ecaloIso[i]);
    recotrack->setVariable("CALOISO9",reco_track_caloIso9[i]);
    recotrack->setVariable("DXY",reco_track_dxy[i]);
    recotrack->setVariable("NVALIDMUONHITS",reco_track_nValidMuonHits[i]);
    recotrack->setVariable("CALOISO2",reco_track_caloIso2[i]);
    recotrack->setVariable("VERT_DXY",reco_track_vert_dxy[i]);
    recotrack->setVariable("CHARGE",reco_track_charge[i]);
    recotrack->setVariable("CALOISO1",reco_track_caloIso1[i]);
    recotrack->setVariable("TRACKISO",reco_track_trackIso[i]);
    recotrack->setVariable("ISGLOBAL",reco_track_isGlobal[i]);
    recotrack->setVariable("BEAM_DSZ",reco_track_beam_dsz[i]);
    recotrack->setVariable("NLOSTPIXELHITS",reco_track_nLostPixelHits[i]);
    recotrack->setVariable("NPIXELLAYERSWM",reco_track_npixelLayersWM[i]);
    recotrack->setVariable("VX",reco_track_vx[i]);
    recotrack->setVariable("VY",reco_track_vy[i]);
    recotrack->setVariable("LAMBDAERROR",reco_track_lambdaError[i]);
    recotrack->setVariable("PF_CHARGEDHADRONISO",reco_track_PF_chargedHadronIso[i]);
    recotrack->setVariable("NVALIDPIXELHITS",reco_track_nValidPixelHits[i]);
    recotrack->setVariable("VZ",reco_track_vz[i]);
    recotrack->setVariable("D0",reco_track_d0[i]);
    recotrack->setVariable("DSZ",reco_track_dsz[i]);
    recotrack->setVariable("NVALIDTRACKERHITS",reco_track_nValidTrackerHits[i]);
    recotrack->setVariable("NBADMUONHITSINFIRSTSTATION",reco_track_nBadMuonHitsInFirstStation[i]);
    recotrack->setVariable("THETAERROR",reco_track_thetaError[i]);
    recotrack->setVariable("VERT_DZ",reco_track_vert_dz[i]);
    recotrack->setVariable("PF_PHOTONISO",reco_track_PF_photonIso[i]);
    recotrack->setVariable("OUTERMOSTMUONSTATIONWITHVALIDHITS",reco_track_outermostMuonStationWithValidHits[i]);
    recotrack->setVariable("PHIERROR",reco_track_phiError[i]);
    recotrack->setVariable("NANYMUONHITSINFIRSTSTATION",reco_track_nAnyMuonHitsInFirstStation[i]);
    recotrack->setVariable("TRACKISO6",reco_track_trackIso6[i]);
    recotrack->setVariable("NTRACKERLAYERSWM",reco_track_ntrackerLayersWM[i]);
    recotrack->setVariable("TRACKISO2",reco_track_trackIso2[i]);
    recotrack->setVariable("THETA",reco_track_theta[i]);
    recotrack->setVariable("NLOSTTRACKERHITS",reco_track_nLostTrackerHits[i]);
    recotrack->setVariable("ISMUON",reco_track_isMuon[i]);
    recotrack->setVariable("TRACKISO9",reco_track_trackIso9[i]);
    recotrack->setVariable("D0ERROR",reco_track_d0Error[i]);
    recotrack->setVariable("TRACKISO1",reco_track_trackIso1[i]);
    recotrack->setVariable("NBADMUONHITS",reco_track_nBadMuonHits[i]);
    recotrack->setVariable("CHI2",reco_track_chi2[i]);
    recotrack->setVariable("CALOISO6",reco_track_caloIso6[i]);
    recotrack->setVariable("ETAERROR",reco_track_etaError[i]);
    recotrack->setVariable("TRACKISO12",reco_track_trackIso12[i]);
    recotrack->setVariable("NDOF",reco_track_ndof[i]);
    recotrack->setVariable("NSTRIPLAYERSWM",reco_track_nstripLayersWM[i]);
    recotrack->setVariable("BEAM_DZ",reco_track_beam_dz[i]);
    recotrack->setVariable("ISTRACKER",reco_track_isTracker[i]);
    recotrack->setVariable("HCALOISO",reco_track_hcaloIso[i]);
    recotrack->setVariable("NVALIDHITS",reco_track_nValidHits[i]);
    recotrack->setVariable("DZERROR",reco_track_dzError[i]);
    recotrack->setVariable("NVALIDMUONHITSINFIRSTSTATION",reco_track_nValidMuonHitsInFirstStation[i]);
    recotrack->setVariable("DXYERROR",reco_track_dxyError[i]);
    recotrack->setVariable("CALOISO",reco_track_caloIso[i]);
    recotrack->setVariable("PF_NEUTRALHADRONISO",reco_track_PF_neutralHadronIso[i]);
    recotrack->setVariable("NLOSTMUONHITSINFIRSTSTATION",reco_track_nLostMuonHitsInFirstStation[i]);
    recotrack->setVariable("BEAM_DXY",reco_track_beam_dxy[i]);
    recotrack->setVariable("CALOISO12",reco_track_caloIso12[i]);
    recotrack->setVariable("MUONSTATIONSWAH",reco_track_muonStationsWAH[i]);
    recotrack->setVariable("NLOSTMUONHITS",reco_track_nLostMuonHits[i]);
    recotrack->setVariable("NLOSTHITS",reco_track_nLostHits[i]);
    recotrack->setVariable("MUONSTATIONSWVH",reco_track_muonStationsWVH[i]);
    recotrack->setVariable("BEAM_D0",reco_track_beam_d0[i]);
    recotrack->setVariable("VERTWEIGHT",reco_track_vertWeight[i]);

    recotracks.push_back(recotrack);
  }
  m_products["ALLRECOTRACKS"] = recotracks;

}

void SkimTreeReader::createMuons()
{
  vector<SignatureObject*> mcparticles = getProduct("ALLMCPARTICLES");
  vector<SignatureObject*> alltracks = getProduct("ALLRECOTRACKS");
  vector<SignatureObject*> muons;
  for(int i = 0; i < pat_muon_n; i++){
    int gtID = pat_muon_globalTrackID[i];
    if(gtID < 0)continue;
    SignatureObject* muon = new SignatureObject(pat_muon_px[i],pat_muon_py[i],pat_muon_pz[i],pat_muon_energy[i]);
    if(gtID < (int)alltracks.size())
      muon->setAssociate("RECOTRACK",alltracks[gtID]);
    if(pat_muon_genLepton_ntID[i] >= 0 && pat_muon_genLepton_ntID[i] < (int)mcparticles.size()) {
      muon->setAssociate("GENPARTICLE",mcparticles[pat_muon_genLepton_ntID[i]]);
    }
    muon->setVariable("RHO",pat_rho);
    muon->setVariable("CHARGEDHADRONISO",pat_muon_PF_chargedHadronIso[i]);
    muon->setVariable("NEUTRALHADRONISO",pat_muon_PF_neutralHadronIso[i]);
    muon->setVariable("PHOTONISO",pat_muon_PF_photonIso[i]);
    muon->setVariable("VERT_DXY",pat_muon_innerVertDxy[i]);
    muon->setVariable("ISGLOBALMUON",pat_muon_isGlobalMuon[i]);
    muon->setVariable("ECALOISO",pat_muon_ecaloIso[i]);
    muon->setVariable("GLOBALTRACKID",pat_muon_globalTrackID[i]);
    muon->setVariable("DRMIN10",pat_muon_dRmin10[i]);
    muon->setVariable("TRACKID",pat_muon_trackID[i]);
    muon->setVariable("TRACKISO",pat_muon_trackIso[i]);
    muon->setVariable("PFMATCHPDGID",pat_muon_PFMatchPdgId[i]);
    muon->setVariable("ISTMLASTSTATIONANGTIGHT",pat_muon_isTMLastStationAngTight[i]);
    muon->setVariable("PFPAT_DQ",pat_muon_PFPAT_dq[i]);
    muon->setVariable("ISPF",pat_muon_isPF[i]);
    muon->setVariable("HCALISODEP",pat_muon_hcalIsoDep[i]);
    muon->setVariable("PFPAT_DETA",pat_muon_PFPAT_deta[i]);
    muon->setVariable("DIRECTION",pat_muon_Direction[i]);
    muon->setVariable("VERTTRACKISO",pat_muon_vertTrackIso[i]);
    muon->setVariable("PF_CHARGEDHADRONISO",pat_muon_PF_chargedHadronIso[i]);
    muon->setVariable("ISGLOBALMUONPROMPTTIGHT",pat_muon_isGlobalMuonPromptTight[i]);
    muon->setVariable("PF_PHOTONISO",pat_muon_PF_photonIso[i]);
    muon->setVariable("DRMIN",pat_muon_dRmin[i]);
    muon->setVariable("CHARGE",pat_muon_charge[i]);
    muon->setVariable("CALENERGYHAD",pat_muon_calEnergyHad[i]);
    muon->setVariable("CALOCOMPATIBILITY",pat_muon_caloCompatibility[i]);
    muon->setVariable("DRMIN_TRACK_NTID",pat_muon_dRmin_track_ntID[i]);
    muon->setVariable("SEGMENTCOMPATIBILITY",pat_muon_segmentCompatibility[i]);
    muon->setVariable("OVERLAPCOMPATIBILITY",pat_muon_overlapCompatibility[i]);
    muon->setVariable("ISCALOMUON",pat_muon_isCaloMuon[i]);
    muon->setVariable("COSMICCOMPATIBILITY",pat_muon_cosmicCompatibility[i]);
    muon->setVariable("PF_NEUTRALHADRONISO",pat_muon_PF_neutralHadronIso[i]);
    muon->setVariable("ISTMLASTSTATIONTIGHT",pat_muon_isTMLastStationTight[i]);
    muon->setVariable("ISCALOCOMPATIBILITYVALID",pat_muon_isCaloCompatibilityValid[i]);
    muon->setVariable("NUMBEROFMATCHES",pat_muon_numberOfMatches[i]);
    muon->setVariable("PFPAT_DPT",pat_muon_PFPAT_dpt[i]);
    muon->setVariable("GENLEPTON_PDGID",pat_muon_genLepton_pdgID[i]);
    muon->setVariable("CALENERGYEM",pat_muon_calEnergyEM[i]);
    muon->setVariable("DRMIN05_TRACK_NTID",pat_muon_dRmin05_track_ntID[i]);
    muon->setVariable("HCALOISO",pat_muon_hcaloIso[i]);
    muon->setVariable("DRMIN05",pat_muon_dRmin05[i]);
    muon->setVariable("GENLEPTON_DR",pat_muon_genLepton_dR[i]);
    muon->setVariable("MUONTRACKID",pat_muon_muonTrackID[i]);
    muon->setVariable("ISTRACKERMUON",pat_muon_isTrackerMuon[i]);
    muon->setVariable("BACKTOBACKCOMPATIBILITY",pat_muon_backToBackCompatibility[i]);
    muon->setVariable("ECALISODEP",pat_muon_ecalIsoDep[i]);
    muon->setVariable("CALOISO",pat_muon_caloIso[i]);
    muon->setVariable("ALLTRACKISO",pat_muon_allTrackIso[i]);
    muon->setVariable("PFPAT_DPHI",pat_muon_PFPAT_dphi[i]);
    muon->setVariable("ISSTANDALONEMUON",pat_muon_isStandAloneMuon[i]);
    muon->setVariable("DRMIN10_TRACK_NTID",pat_muon_dRmin10_track_ntID[i]);
    muon->setVariable("GENLEPTON_MOTHER_NTID",pat_muon_genLepton_mother_ntID[i]);
    muon->setVariable("TRIGGER_NFILTER",pat_muon_trigger_nfilter[i]);
    muon->setVariable("TIMECOMPATIBILITY",pat_muon_timeCompatibility[i]);
    muon->setVariable("GENLEPTON_MOTHER_PDGID",pat_muon_genLepton_mother_pdgID[i]);
    muon->setVariable("GENLEPTON_NTID",pat_muon_genLepton_ntID[i]);
    muon->setVariable("BETA",pat_muon_beta[i]);
    muon->setVariable("INNERVERTDXY",pat_muon_innerVertDxy[i]);
    muon->setVariable("INNERNUMBEROFVALIDPIXELHITS",pat_muon_innerNumberOfValidPixelHits[i]);
    muon->setVariable("INNERVERTDZ",pat_muon_innerVertDz[i]);
    muon->setVariable("NORMALIZEDCHI2",pat_muon_normalizedChi2[i]);
    muon->setVariable("PDGID",13*-1*pat_muon_charge[i]);

    muons.push_back(muon);
  }
  sort(muons.begin(),muons.end(),SignatureObjectComparison);
  reverse(muons.begin(),muons.end());

  m_products["ALLMUONS"] = muons;
}

void SkimTreeReader::createElectrons()
{
  vector<SignatureObject*> mcparticles = getProduct("ALLMCPARTICLES");
  vector<SignatureObject*> alltracks = getProduct("ALLRECOTRACKS");
  vector<SignatureObject*> electrons;
  for(int i = 0; i < pat_electron_n; i++){
    int gtID = pat_electron_trackID[i];
    if(gtID < 0)continue;
    SignatureObject* electron = new SignatureObject(pat_electron_px[i],pat_electron_py[i],pat_electron_pz[i],pat_electron_energy[i]);
    if(gtID < (int)alltracks.size())
      electron->setAssociate("RECOTRACK",alltracks[gtID]);
    if(pat_electron_genLepton_ntID[i] >= 0 && pat_electron_genLepton_ntID[i] < (int)mcparticles.size()) {
      electron->setAssociate("GENPARTICLE",mcparticles[pat_electron_genLepton_ntID[i]]);
    }
    electron->setVariable("RHO",pat_rho);
    electron->setVariable("RHONEUTRAL",pat_rho_neutral);
    electron->setVariable("CHARGEDHADRONISO",pat_electron_PF_chargedHadronIso[i]);
    electron->setVariable("NEUTRALHADRONISO",pat_electron_PF_neutralHadronIso[i]);
    electron->setVariable("PHOTONISO",pat_electron_PF_photonIso[i]);
    electron->setVariable("VERT_DXY",pat_electron_fMVAVar_d0[i]);
    electron->setVariable("FBREM",pat_electron_fbrem[i]);
    electron->setVariable("TRACKID",pat_electron_trackID[i]);
    electron->setVariable("PF_CHARGEDHADRONISO_04",pat_electron_PF_chargedHadronIso_04[i]);
    electron->setVariable("CONVERSIONDCOTTHETA",pat_electron_ConversionDCotTheta[i]);
    electron->setVariable("FMVAVAR_DETACALO",pat_electron_fMVAVar_detacalo[i]);
    electron->setVariable("PF_NEUTRALHADRONISO",pat_electron_PF_neutralHadronIso[i]);
    electron->setVariable("FMVAVAR_ETA",pat_electron_fMVAVar_eta[i]);
    electron->setVariable("FMVAVAR_DPHICALO",pat_electron_fMVAVar_dphicalo[i]);
    electron->setVariable("SWISSCROSS",pat_electron_swissCross[i]);
    electron->setVariable("PF_PHOTONISO",pat_electron_PF_photonIso[i]);
    electron->setVariable("CHARGE",pat_electron_charge[i]);
    electron->setVariable("FMVAVAR_PRESHOWEROVERRAW",pat_electron_fMVAVar_PreShowerOverRaw[i]);
    electron->setVariable("FMVAVAR_KFHITS",pat_electron_fMVAVar_kfhits[i]);
    electron->setVariable("EIDTIGHT",pat_electron_eidTight[i]);
    electron->setVariable("GENLEPTON_NTID",pat_electron_genLepton_ntID[i]);
    electron->setVariable("HCALOISO",pat_electron_hcaloIso[i]);
    electron->setVariable("FMVAVAR_KFCHI2",pat_electron_fMVAVar_kfchi2[i]);
    electron->setVariable("HADOVEREM",pat_electron_hadOverEm[i]);
    electron->setVariable("FMVAVAR_IOEMIOP",pat_electron_fMVAVar_IoEmIoP[i]);
    electron->setVariable("FMVAVAR_PT",pat_electron_fMVAVar_pt[i]);
    electron->setVariable("TRIGGER_NFILTER",pat_electron_trigger_nfilter[i]);
    electron->setVariable("FMVAVAR_PHIWIDTH",pat_electron_fMVAVar_phiwidth[i]);
    electron->setVariable("FMVAVAR_EOP",pat_electron_fMVAVar_EoP[i]);
    electron->setVariable("ECALOISO",pat_electron_ecaloIso[i]);
    electron->setVariable("PFPAT_DPHI",pat_electron_PFPAT_dphi[i]);
    electron->setVariable("GSFSCPIXCHARGECONSISTENT",pat_electron_GsfScPixChargeConsistent[i]);
    electron->setVariable("FMVAVAR_ELEEOPOUT",pat_electron_fMVAVar_eleEoPout[i]);
    electron->setVariable("TRACKISO",pat_electron_trackIso[i]);
    electron->setVariable("PFMATCHPDGID",pat_electron_PFMatchPdgId[i]);
    electron->setVariable("PF_NEUTRALHADRONISO_04",pat_electron_PF_neutralHadronIso_04[i]);
    electron->setVariable("EIDROBUSTLOOSE",pat_electron_eidRobustLoose[i]);
    electron->setVariable("ISPF",pat_electron_isPF[i]);
    electron->setVariable("FMVAVAR_ETAWIDTH",pat_electron_fMVAVar_etawidth[i]);
    electron->setVariable("PF_CHARGEDHADRONISO",pat_electron_PF_chargedHadronIso[i]);
    electron->setVariable("DELTAETA",pat_electron_deltaEta[i]);
    electron->setVariable("DRMIN",pat_electron_dRmin[i]);
    electron->setVariable("ESEEDCLUSTEROVERPOUT",pat_electron_eSeedClusterOverPout[i]);
    electron->setVariable("DRMIN_TRACK_NTID",pat_electron_dRmin_track_ntID[i]);
    electron->setVariable("SIGMAIETAIETA",pat_electron_sigmaIetaIeta[i]);
    electron->setVariable("FMVAVAR_D0",pat_electron_fMVAVar_d0[i]);
    electron->setVariable("FMVAVAR_DZ",pat_electron_fMVAVar_dz[i]);
    electron->setVariable("FMVAVAR_NBREMS",pat_electron_fMVAVar_nbrems[i]);
    electron->setVariable("FMVAVAR_SEE",pat_electron_fMVAVar_see[i]);
    electron->setVariable("CALOENERGY",pat_electron_caloEnergy[i]);
    electron->setVariable("FMVAVAR_FBREM",pat_electron_fMVAVar_fbrem[i]);
    electron->setVariable("CLASSIFICATION",pat_electron_classification[i]);
    electron->setVariable("E2X5MAX",pat_electron_e2x5Max[i]);
    electron->setVariable("PFPAT_DQ",pat_electron_PFPAT_dq[i]);
    electron->setVariable("PFPAT_DETA",pat_electron_PFPAT_deta[i]);
    electron->setVariable("DELTAPHI",pat_electron_deltaPhi[i]);
    electron->setVariable("NUMBEROFLOSTINNERHITS",pat_electron_NumberOfLostInnerHits[i]);
    electron->setVariable("CONVERSIONDIST",pat_electron_ConversionDist[i]);
    electron->setVariable("PFPAT_DPT",pat_electron_PFPAT_dpt[i]);
    electron->setVariable("GENLEPTON_PDGID",pat_electron_genLepton_pdgID[i]);
    electron->setVariable("FMVAVAR_GSFCHI2",pat_electron_fMVAVar_gsfchi2[i]);
    electron->setVariable("EOVERPIN",pat_electron_eOverPin[i]);
    electron->setVariable("FMVAVAR_HOE",pat_electron_fMVAVar_HoE[i]);
    electron->setVariable("ISCONVERSION",pat_electron_IsConversion[i]);
    electron->setVariable("ECALDRIVEN",pat_electron_ecalDriven[i]);
    electron->setVariable("GSFCTFCHARGECONSISTENT",pat_electron_GsfCtfChargeConsistent[i]);
    electron->setVariable("FMVAVAR_SPP",pat_electron_fMVAVar_spp[i]);
    electron->setVariable("FMVAVAR_DPHI",pat_electron_fMVAVar_dphi[i]);
    electron->setVariable("FMVAVAR_E1X5E5X5",pat_electron_fMVAVar_e1x5e5x5[i]);
    electron->setVariable("E1X5",pat_electron_e1x5[i]);
    electron->setVariable("EIDROBUSTHIGHENERGY",pat_electron_eidRobustHighEnergy[i]);
    electron->setVariable("EMAX",pat_electron_eMax[i]);
    electron->setVariable("SIGMAETAETA",pat_electron_sigmaEtaEta[i]);
    electron->setVariable("CONV_VTXPROB",pat_electron_conv_vtxProb[i]);
    electron->setVariable("STATUS",pat_electron_status[i]);
    electron->setVariable("E5X5",pat_electron_e5x5[i]);
    electron->setVariable("FMVAVAR_R9",pat_electron_fMVAVar_R9[i]);
    electron->setVariable("CALOISO",pat_electron_caloIso[i]);
    electron->setVariable("EIDROBUSTTIGHT",pat_electron_eidRobustTight[i]);
    electron->setVariable("FMVAVAR_DETA",pat_electron_fMVAVar_deta[i]);
    electron->setVariable("PF_PHOTONISO_04",pat_electron_PF_photonIso_04[i]);
    electron->setVariable("EIDLOOSE",pat_electron_eidLoose[i]);
    electron->setVariable("GSFCTFSCPIXCHARGECONSISTENT",pat_electron_GsfCtfScPixChargeConsistent[i]);
    electron->setVariable("NUMBEROFEXPECTEDINNERHITS",pat_electron_NumberOfExpectedInnerHits[i]);
    electron->setVariable("PDGID",11*-1*pat_electron_charge[i]);
    electrons.push_back(electron);
  }
  sort(electrons.begin(),electrons.end(),SignatureObjectComparison);
  reverse(electrons.begin(),electrons.end());
  m_products["ALLELECTRONS"] = electrons;
}



void SkimTreeReader::createPhotons()
{
  vector<SignatureObject*> mcparticles = getProduct("ALLMCPARTICLES");
  vector<SignatureObject*> alltracks = getProduct("ALLRECOTRACKS");
  vector<SignatureObject*> photons;
  for(int i = 0; i < pat_photon_n; i++){
    SignatureObject* photon = new SignatureObject(pat_photon_px[i],pat_photon_py[i],pat_photon_pz[i],pat_photon_pmag[i]);
    if(pat_photon_genPhoton_ntID[i] >= 0 && pat_photon_genPhoton_ntID[i] < (int)mcparticles.size()) {
      photon->setAssociate("GENPARTICLE",mcparticles[pat_photon_genPhoton_ntID[i]]);
    }
    photon->setVariable("RHO",pat_rho);
    photon->setVariable("RHONEUTRAL",pat_rho_neutral);
    photon->setVariable("PHOTONISO",pat_photon_photonIso[i]);
    photon->setVariable("TRACKISO",pat_photon_trackIso[i]);
    photon->setVariable("GENPHOTON_PDGID",pat_photon_genPhoton_pdgID[i]);
    photon->setVariable("ENDCAP",pat_photon_endcap[i]);
    photon->setVariable("TRACK_NSOLIDR03",pat_photon_track_nSolidR03[i]);
    photon->setVariable("NEUTRALHADRONISO",pat_photon_neutralHadronIso[i]);
    photon->setVariable("ISLOOSE",pat_photon_isLoose[i]);
    photon->setVariable("HCALDEPTH2TOWERETR04",pat_photon_hcalDepth2TowerEtR04[i]);
    photon->setVariable("CHARGEDHADRONISO",pat_photon_chargedHadronIso[i]);
    photon->setVariable("EOUT",pat_photon_EOut[i]);
    photon->setVariable("SCET",pat_photon_scEt[i]);
    photon->setVariable("ECALRECHITETR04",pat_photon_ecalRecHitEtR04[i]);
    photon->setVariable("ECALRECHITETR03",pat_photon_ecalRecHitEtR03[i]);
    photon->setVariable("CONVERSIONSAFEELECTRONVETO",pat_photon_conversionSafeElectronVeto[i]);
    photon->setVariable("GENPHOTON_NTID",pat_photon_genPhoton_ntID[i]);
    photon->setVariable("TRACKSUMPTSOLIDR04",pat_photon_trackSumPtSolidR04[i]);
    photon->setVariable("HADTOWOVEREM",pat_photon_hadTowOverEm[i]);
    photon->setVariable("SIGMAIETAIETA",pat_photon_sigmaIetaIeta[i]);
    photon->setVariable("PFPHOTONRES",pat_photon_PFPhotonRes[i]);
    photon->setVariable("MVAGLOBALCORREERROR",pat_photon_MVAGlobalCorrEError[i]);
    photon->setVariable("HCALTOWERETR04",pat_photon_hcalTowerEtR04[i]);
    photon->setVariable("HCALDEPTH1TOWERETR03",pat_photon_hcalDepth1TowerEtR03[i]);
    photon->setVariable("MUSTACHEET",pat_photon_mustacheEt[i]);
    photon->setVariable("HCALDEPTH1TOWERETR04",pat_photon_hcalDepth1TowerEtR04[i]);
    photon->setVariable("HCALTOWERETR03",pat_photon_hcalTowerEtR03[i]);
    photon->setVariable("TRACK_NHOLLOWR03",pat_photon_track_nHollowR03[i]);
    photon->setVariable("TRACK_NHOLLOWR04",pat_photon_track_nHollowR04[i]);
    photon->setVariable("TRACK_NSOLIDR04",pat_photon_track_nSolidR04[i]);
    photon->setVariable("ISTIGHT",pat_photon_isTight[i]);
    photon->setVariable("MVAGLOBALCORRE",pat_photon_MVAGlobalCorrE[i]);
    photon->setVariable("CALOISO",pat_photon_caloIso[i]);
    photon->setVariable("HADOVEREM",pat_photon_hadOverEm[i]);
    photon->setVariable("R9",pat_photon_r9[i]);
    photon->setVariable("TRIGGER_NFILTER",pat_photon_trigger_nfilter[i]);
    photon->setVariable("TRACKSUMPTHOLLOWR04",pat_photon_trackSumPtHollowR04[i]);
    photon->setVariable("BARREL",pat_photon_barrel[i]);
    photon->setVariable("TRACKSUMPTSOLIDR03",pat_photon_trackSumPtSolidR03[i]);
    photon->setVariable("HCALDEPTH2TOWERETR03",pat_photon_hcalDepth2TowerEtR03[i]);
    photon->setVariable("TRACKSUMPTHOLLOWR03",pat_photon_trackSumPtHollowR03[i]);
    photons.push_back(photon);
  }
  m_products["ALLPHOTONS"] = photons;

}

void SkimTreeReader::createJets()
{
  vector<SignatureObject*> mcparticles = getProduct("ALLMCPARTICLES");
  vector<SignatureObject*> jets;
  for(int i = 0; i < pat_jet_n; i++){
    SignatureObject* jet = new SignatureObject(pat_jet_px[i],pat_jet_py[i],pat_jet_pz[i],pat_jet_energy[i]);
    jet->setVariable("CORRLEVEL",pat_jet_corrLevel[i]);
    jet->setVariable("BDISCRIMINATOR_COMBINED",pat_jet_bDiscriminator_combined[i]);
    jet->setVariable("CHARGEDHADRONFRACTION",pat_jet_chargedHadronFraction[i]);
    jet->setVariable("GENPARTON_NTID",pat_jet_genParton_ntID[i]);
    if(pat_jet_genParton_ntID[i] >= 0 && pat_jet_genParton_ntID[i] < (int)mcparticles.size()) {
      jet->setAssociate("GENPARTICLE",mcparticles[pat_jet_genParton_ntID[i]]);
    }
    jet->setVariable("ETAETAMOMENT",pat_jet_etaetaMoment[i]);
    jet->setVariable("RAW_PT",pat_jet_raw_pt[i]);
    //jet->setVariable("VY",pat_jet_vy[i]);
    //jet->setVariable("VX",pat_jet_vx[i]);
    jet->setVariable("BDISCRIMINATOR_TRACKCOUNT",pat_jet_bDiscriminator_trackCount[i]);
    jet->setVariable("NEUTRALEMFRACTION",pat_jet_neutralEMFraction[i]);
    jet->setVariable("CHARGEDEMFRACTION",pat_jet_chargedEMFraction[i]);
    jet->setVariable("TRIGGER_NFILTER",pat_jet_trigger_nfilter[i]);
    jet->setVariable("NEUTRALHADRONFRACTION",pat_jet_neutralHadronFraction[i]);
    jet->setVariable("ISCALO",pat_jet_isCalo[i]);
    jet->setVariable("EHF",pat_jet_ehf[i]);
    //jet->setVariable("CHARGE",pat_jet_charge[i]);
    jet->setVariable("BDISCRIMINATOR_SSVERTEXPURE",pat_jet_bDiscriminator_ssVertexPure[i]);
    jet->setVariable("BDISCRIMINATOR",pat_jet_bDiscriminator[i]);
    jet->setVariable("PHIPHIMOMENT",pat_jet_phiphiMoment[i]);
    //jet->setVariable("VZ",pat_jet_vz[i]);
    jet->setVariable("GENPARTON_PDGID",pat_jet_genParton_pdgID[i]);
    jet->setVariable("SUMTRACKPT",pat_jet_sumTrackPt[i]);
    jet->setVariable("TIGHT_PFJETID",pat_jet_tight_PFjetID[i]);
    jet->setVariable("CHARGEDHADRONMULTIPLICITY",pat_jet_chargedHadronMultiplicity[i]);
    jet->setVariable("BDISCRIMINATOR_TRACKCOUNTPURE",pat_jet_bDiscriminator_trackCountPure[i]);
    jet->setVariable("ISPF",pat_jet_isPF[i]);
    jet->setVariable("EMF",pat_jet_emf[i]);
    jet->setVariable("UNCERTAINTY",pat_jet_uncertainty[i]);
    jet->setVariable("NTRACKS",pat_jet_ntracks[i]);
    jet->setVariable("RAW_ET",pat_jet_raw_et[i]);
    jet->setVariable("ETAPHIMOMENT",pat_jet_etaphiMoment[i]);
    jet->setVariable("MASS",pat_jet_mass[i]);
    jet->setVariable("LOOSE_PFJETID",pat_jet_loose_PFjetID[i]);
    jet->setVariable("MEDIUM_PFJETID",pat_jet_medium_PFjetID[i]);
    jet->setVariable("NUMBERCONSTITUENTS",pat_jet_numberConstituents[i]);
    jet->setVariable("BDISCRIMINATOR_SSVERTEX",pat_jet_bDiscriminator_ssVertex[i]);

    jet->setVariable("BETA",calculateJetBeta(i,0));
    
    jets.push_back(jet);
  }
  m_products["ALLJETS"] = jets;
}

void SkimTreeReader::createRecoVertices()
{
  vector<SignatureObject*> recovertices;
  for(int i = 0; i < reco_vertex_n; i++){
    SignatureObject* recovertex = new SignatureObject(0,0,0,0);
    recovertex->setVariable("X",reco_vertex_x[i]);
    recovertex->setVariable("Y",reco_vertex_y[i]);
    recovertex->setVariable("Z",reco_vertex_z[i]);
    recovertex->setVariable("NTRACK",reco_vertex_ntrack[i]);
    recovertex->setVariable("EX",reco_vertex_ex[i]);
    recovertex->setVariable("EY",reco_vertex_ey[i]);
    recovertex->setVariable("EZ",reco_vertex_ez[i]);
    recovertex->setVariable("NDOF",reco_vertex_ndof[i]);
    recovertex->setVariable("CHI2",reco_vertex_chi2[i]);
    recovertex->setVariable("WSUMPT",reco_vertex_wSumPt[i]);
    recovertices.push_back(recovertex);
  }
  m_products["ALLRECOVERTICES"] = recovertices;
}

void SkimTreeReader::createTaus()
{
  vector<SignatureObject*> mcparticles = getProduct("ALLMCPARTICLES");
  vector<SignatureObject*> taus;
  for(int i = 0; i < pat_tau_n; i++){
    SignatureObject* tau = new SignatureObject(0,0,0,0);
    tau->SetPtEtaPhiM(pat_tau_pt[i],pat_tau_eta[i],pat_tau_phi[i],1.777);
    SignatureObject* leadtrack = findTauLeadingTrack(tau);
    if(leadtrack)tau->setAssociate("LEADTRACK",leadtrack);
    if(pat_tau_genLepton_ntID[i] >= 0 && pat_tau_genLepton_ntID[i] < (int)mcparticles.size()) {
      tau->setAssociate("GENPARTICLE",mcparticles[pat_tau_genLepton_ntID[i]]);
    }
    tau->setVariable("RHO",pat_rho);
    tau->setVariable("CHARGEDHADRONISO",pat_tau_PF_chargedHadronIso03[i]);
    tau->setVariable("NEUTRALHADRONISO",pat_tau_PF_neutralHadronIso03[i]);
    tau->setVariable("PHOTONISO",pat_tau_PF_photonIso03[i]);
    tau->setVariable("CHARGE",pat_tau_PF_signalCharge[i]);
    tau->setVariable("PF_NEUTRALHADRONISO05",pat_tau_PF_neutralHadronIso05[i]);
    tau->setVariable("TRACKISO",pat_tau_trackIso[i]);
    tau->setVariable("PF_ISOGAMMAETSUM",pat_tau_PF_isoGammaEtSum[i]);
    tau->setVariable("PF_NSIGGAMMA",pat_tau_PF_NsigGamma[i]);
    tau->setVariable("ISPF",pat_tau_isPF[i]);
    tau->setVariable("ISCALO",pat_tau_isCalo[i]);
    tau->setVariable("EMFRACTION",pat_tau_emFraction[i]);
    tau->setVariable("PF_AGAINSTMUON",pat_tau_PF_againstMuon[i]);
    tau->setVariable("PF_NEUTRALHADRONISO03",pat_tau_PF_neutralHadronIso03[i]);
    tau->setVariable("CALO_LEADTRACKSIGNEDSIPT",pat_tau_calo_leadTracksignedSipt[i]);
    tau->setVariable("PF_NSIGCHARGED",pat_tau_PF_NsigCharged[i]);
    tau->setVariable("PF_ISOKLONGCANDMAXPT",pat_tau_PF_isoKlongCandMaxPt[i]);
    tau->setVariable("PF_PHOTONISO05",pat_tau_PF_photonIso05[i]);
    tau->setVariable("PF_AGAINSTELECTRON",pat_tau_PF_againstElectron[i]);
    tau->setVariable("PF_PHOTONISO03",pat_tau_PF_photonIso03[i]);
    tau->setVariable("ISOTRACKS_N",pat_tau_isoTracks_n[i]);
    tau->setVariable("LEADTRACK_NTID",pat_tau_leadTrack_ntID[i]);
    tau->setVariable("CALO_ISOECALETSUM",pat_tau_calo_isoECALEtSum[i]);
    tau->setVariable("PF_SIGNALMASS",pat_tau_PF_signalMass[i]);
    tau->setVariable("GENLEPTON_PDGID",pat_tau_genLepton_pdgID[i]);
    tau->setVariable("PF_ISOCHARGEDPTSUM",pat_tau_PF_isoChargedPtSum[i]);
    tau->setVariable("GENLEPTON_NTID",pat_tau_genLepton_ntID[i]);
    tau->setVariable("PF_LEADTRACKSIGNEDSIPT",pat_tau_PF_leadTracksignedSipt[i]);
    tau->setVariable("PF_ISOCHARGEDCANDMAXPT",pat_tau_PF_isoChargedCandMaxPt[i]);
    tau->setVariable("CALOISO",pat_tau_caloIso[i]);
    tau->setVariable("PF_ISOSUMPT",pat_tau_PF_isoSumPt[i]);
    tau->setVariable("PF_MAXHCALHITET",pat_tau_PF_maxHCALhitEt[i]);
    tau->setVariable("CALO_MAXHCALHITET",pat_tau_calo_maxHCALhitEt[i]);
    tau->setVariable("PF_ISOGAMMACANDMAXPT",pat_tau_PF_isoGammaCandMaxPt[i]);
    tau->setVariable("CALO_ISOCHARGEDPTSUM",pat_tau_calo_isoChargedPtSum[i]);
    tau->setVariable("TRIGGER_NFILTER",pat_tau_trigger_nfilter[i]);
    tau->setVariable("SIGNALTRACKS_N",pat_tau_signalTracks_n[i]);
    tau->setVariable("SIGNALTRACKSINVMASS",pat_tau_signalTracksInvMass[i]);
    tau->setVariable("PF_SIGNALCHARGE",pat_tau_PF_signalCharge[i]);
    tau->setVariable("PF_CHARGEDHADRONISO05",pat_tau_PF_chargedHadronIso05[i]);
    tau->setVariable("PF_CHARGEDHADRONISO03",pat_tau_PF_chargedHadronIso03[i]);
    tau->setVariable("PDGID",-15*pat_tau_PF_signalCharge[i]);

    taus.push_back(tau);
  }
  m_products["ALLTAUS"] = taus;
}

void SkimTreeReader::createMET()
{
  vector<SignatureObject*> mets;
  SignatureObject* met = new SignatureObject(0,0,0,0);
  met->SetPtEtaPhiM(pf_met_pt,0,pf_met_phi,0);
  met->setVariable("PAT_SUMET",pat_met_sumEt);
  met->setVariable("PF_PT",pf_met_pt);
  //m_met->setVariable("PF_ETA",pf_met_eta);
  met->setVariable("PAT_PHI",pat_met_phi);
  met->setVariable("PAT_ETA",pat_met_eta);
  met->setVariable("PF_PHI",pf_met_phi);
  met->setVariable("PAT_PX",pat_met_px);
  met->setVariable("PAT_PY",pat_met_py);
  met->setVariable("PAT_PZ",pat_met_pz);
  met->setVariable("PAT_PT",pat_met_pt);
  met->setVariable("PF_SUMET",pf_met_sumEt);
  met->setVariable("PAT_GEN_SUMET",pat_met_gen_sumEt);
  met->setVariable("PAT_METSIG",pat_met_mEtSig);
  met->setVariable("TC_SUMET",tc_met_sumEt);
  met->setVariable("TC_PT",tc_met_pt);
  met->setVariable("TC_PHI",tc_met_phi);
  mets.push_back(met);
  m_products["MET"] = mets;

}

void SkimTreeReader::createTriggers()
{
  vector<SignatureObject*> triggers;
  for(int i = 0; i < (int)hlt_triggers_npassed; i++){
    SignatureObject* trigger = new SignatureObject(0,0,0,0);
    trigger->setVariable("TRIGGER",hlt_triggers[i]);
    trigger->setVariable("ID",hlt_triggers_id[i]);
    trigger->setVariable("PRESCALE",hlt_triggers_prescale_HLT[i]);
    trigger->setVariable("WASRUN",hlt_triggers_wasrun[i]);
    triggers.push_back(trigger);
  }
  m_products["TRIGGERS"] = triggers;
}

double SkimTreeReader::calculateJetBeta(int jetid, int vertexid = 0)
{
  double betaNum = 0;
  double betaDen = 0;
  vector<SignatureObject*> recotracks = getProduct("ALLRECOTRACKS");
  for(int i = 0; i < pat_jet_ntracks[jetid]; i++){
    int id = pat_jet_trkIDs[jetid][i];
    if(id < 0)continue;
    if(id >= (int)recotracks.size()) continue;
    SignatureObject* track = recotracks[id];
    double vertexZ = reco_vertex_z[vertexid];
    double trackZ;
    bool isset = track->getVariable("VZ",trackZ);
    if(!isset)continue;
    double dz = fabs(trackZ - vertexZ);
    if(dz < 0.5)betaNum += pow(track->Pt(),2);
    betaDen += pow(track->Pt(),2);
  }
  if(betaDen == 0)return 0;
  return betaNum/betaDen;
}

SignatureObject* SkimTreeReader::findTauLeadingTrack(SignatureObject* tau)
{
  vector<SignatureObject*> recotracks = getProduct("ALLRECOTRACKS");
  SignatureObject* leadtrack = 0;
  double maxpt = -99999;
  for(int i = 0; i < (int)recotracks.size(); i++){
    SignatureObject* track = recotracks[i];
    if(fabs(track->Eta()) > 2.4)continue;
    if(track->Pt() < 5.0)continue;
    double valueD;
    int valueI;
    if(!track->getVariable("CALOISO",valueD) || valueD < 0)continue;
    if(!track->getVariable("CALOISO1",valueD) || valueD < 0)continue;
    if(!track->getVariable("ISTRACKER",valueI) || valueI != 1)continue;
    if(!track->getVariable("ISGLOBAL",valueI) || valueI == 1)continue;
    if(tau->DeltaR(TLorentzVector(*track)) > 0.075)continue;
    if(track->Pt() < maxpt)continue;
    maxpt = track->Pt();
    leadtrack = track;
  }
  return leadtrack;
}
void SkimTreeReader::createVariables()
{

  setVariable("PRIMARYVERTEXFILTER",(bool)primaryVertexFilter);
  setVariable("NOSCRAPINGFILTER",(bool)noScrapingFilter);
  setVariable("HBHENOISEFILTER",(bool)HBHENoiseFilter);
  setVariable("CSCTIGHTHALOFILTER",(bool)CSCTightHaloFilter);
  setVariable("HCALLASEREVENTFILTER",(bool)hcalLaserEventFilter);
  setVariable("ECALDEADCELLTRIGGERPRIMITIVEFILTER",(bool)EcalDeadCellTriggerPrimitiveFilter);
  setVariable("TRACKINGFAILUREFILTER",(bool)trackingFailureFilter);
  setVariable("EEBADSCFILTER",(bool)eeBadScFilter);
  setVariable("RUN",run);
  setVariable("LUMI",lumiBlock);
  setVariable("EVENT",(long)event);
  setVariable("PROCESSID",event_mc_processID);
  setVariable("TRUENUMINTERACTIONS",pileup_trueNumInteractions);
  setVariable("NUMINTERACTIONS",pileup_numInteractions);
  setVariable("BUNCHCROSSING",pileup_bunchCrossing);

}
