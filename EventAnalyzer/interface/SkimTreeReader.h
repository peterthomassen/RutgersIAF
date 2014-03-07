//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

#ifndef SkimTreeReader_h
#define SkimTreeReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>

/*
This class is based on a template created by TTree::MakeClass on the 2012 ntuples.

Search for "Rutgers" to find changes.
*/

//Rutgers
#include <string>
#include <iostream>
#include <sstream>
#include <TLorentzVector.h>
#include <vector>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <map>
#include "TRandom.h"
#include "TRandom3.h"

#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class SkimTreeReader : public BaseTreeReader {
public :
   Int_t           fCurrent; //!current Tree number in a TChain

//Rutgers: increase ElectronMax since we already had 50 in this one
  enum NTMAXSIZE {kNPATMuonMax=200, kNPATElectronMax=200, 
		   kNPATJetMax=100, kNPATMCPartMax=1000, kNRECOTrackMax=1000,
		   kNPATTauMax=100, kNPATJetPartMax=100, kNPATTauPartMax=20,
                   kNPATPhotonMax=40, kNHLTTriggerMax=500, kNPATJetCorrLevelMax=7, kNRECOVertexMax=100, kSUSYSCANMAX=10};//Rutgers: changed kNRECOVertexMax from 30 to 100
//Rutgers
   enum PDG { PDG_muon=13, PDG_munu=14, PDG_b=5, PDG_t=6, 
	      PDG_electron=11, PDG_tau=15, PDG_enu=12, PDG_W=24, 
	      PDG_N2=1000023, PDG_C1=1000024, PDG_C0=1000022};

//Rutgers: Replaced array sizes by enum variables


   // Declaration of leaf types
   Int_t           pat_muon_n;
   Double_t        pat_muon_pt[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_et[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_px[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_py[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_pz[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_eta[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_phi[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_pmag[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isPF[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_PFMatchPdgId[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_PFPAT_dpt[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_PFPAT_dphi[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_PFPAT_deta[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_PFPAT_dq[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_energy[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_charge[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_trackID[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_globalTrackID[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_muonTrackID[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_caloIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_ecaloIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_hcaloIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_trackIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_beta[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_PF_chargedHadronIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_PF_photonIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_PF_neutralHadronIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_allTrackIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_vertTrackIso[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_calEnergyEM[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_calEnergyHad[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_ecalIsoDep[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_hcalIsoDep[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_dRmin[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_dRmin_track_ntID[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_dRmin05[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_dRmin05_track_ntID[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_dRmin10[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_dRmin10_track_ntID[kNPATMuonMax];   //[pat_muon_n]
   Double_t        pat_muon_genLepton_dR[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_genLepton_pdgID[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_genLepton_ntID[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_genLepton_mother_pdgID[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_genLepton_mother_ntID[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isGlobalMuon[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isTrackerMuon[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isStandAloneMuon[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isCaloMuon[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isGlobalMuonPromptTight[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isTMLastStationTight[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isTMLastStationAngTight[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_trigger_nfilter[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_trigger_objectType[kNPATMuonMax][kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_trigger_objectID[kNPATMuonMax][5];   //[pat_muon_n]
   Float_t         pat_muon_segmentCompatibility[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_isCaloCompatibilityValid[kNPATMuonMax];   //[pat_muon_n]
   Float_t         pat_muon_caloCompatibility[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_numberOfMatches[kNPATMuonMax];   //[pat_muon_n]
   Int_t           pat_muon_Direction[kNPATMuonMax];   //[pat_muon_n]
   Float_t         pat_muon_cosmicCompatibility[kNPATMuonMax];   //[pat_muon_n]
   Float_t         pat_muon_timeCompatibility[kNPATMuonMax];   //[pat_muon_n]
   Float_t         pat_muon_backToBackCompatibility[kNPATMuonMax];   //[pat_muon_n]
   Float_t         pat_muon_overlapCompatibility[kNPATMuonMax];   //[pat_muon_n]
   Float_t pat_muon_normalizedChi2[kNPATMuonMax];
   Float_t pat_muon_innerVertDz[kNPATMuonMax];
   Float_t pat_muon_innerVertDxy[kNPATMuonMax];
   Int_t pat_muon_innerNumberOfValidPixelHits[kNPATMuonMax];

   Int_t           pat_electron_n;
   Double_t        pat_electron_pt[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_et[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_px[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_py[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_pz[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_pmag[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_eta[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_phi[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_isPF[kNPATElectronMax];   //[pat_electron_n]
   Double_t           pat_electron_conv_vtxProb[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_classification[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_PFMatchPdgId[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PFPAT_dpt[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PFPAT_dphi[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PFPAT_deta[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PFPAT_dq[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_energy[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_charge[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_trackID[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_caloIso[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_trackIso[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_dRmin[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_dRmin_track_ntID[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_genLepton_pdgID[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_genLepton_ntID[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_GsfCtfScPixChargeConsistent[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_GsfScPixChargeConsistent[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_GsfCtfChargeConsistent[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_eidTight[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_eidLoose[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_eidRobustTight[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_eidRobustLoose[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_eidRobustHighEnergy[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_ecaloIso[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_hcaloIso[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PF_chargedHadronIso[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PF_photonIso[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PF_neutralHadronIso[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PF_chargedHadronIso_04[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PF_photonIso_04[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_PF_neutralHadronIso_04[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_classification_04[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_caloEnergy[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_hadOverEm[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_eOverPin[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_sigmaEtaEta[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_sigmaIetaIeta[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_e1x5[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_e2x5Max[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_e5x5[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_deltaPhi[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_deltaEta[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_status[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_trigger_nfilter[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_trigger_objectType[kNPATElectronMax][5];   //[pat_electron_n]
   Int_t           pat_electron_trigger_objectID[kNPATElectronMax][5];   //[pat_electron_n]
   Double_t        pat_electron_fbrem[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_ecalDriven[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_swissCross[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_eMax[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_IsConversion[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_ConversionDist[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_ConversionDCotTheta[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_NumberOfExpectedInnerHits[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_NumberOfLostInnerHits[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_eSeedClusterOverPout[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_fbrem[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_kfchi2[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_fMVAVar_kfhits[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_gsfchi2[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_deta[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_dphi[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_detacalo[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_dphicalo[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_see[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_spp[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_etawidth[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_phiwidth[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_e1x5e5x5[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_R9[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_electron_fMVAVar_nbrems[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_HoE[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_EoP[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_IoEmIoP[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_eleEoPout[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_PreShowerOverRaw[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_d0[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_dz[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_eta[kNPATElectronMax];   //[pat_electron_n]
   Double_t        pat_electron_fMVAVar_pt[kNPATElectronMax];   //[pat_electron_n]
   Int_t           pat_jet_n;
   Double_t        pat_rho;
   Double_t        pat_rho_neutral;
   Double_t        pat_jet_pt[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_et[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_raw_pt[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_raw_et[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_px[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_py[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_pz[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_pmag[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_uncertainty[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_eta[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_phi[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_energy[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_etaetaMoment[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_etaphiMoment[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_phiphiMoment[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_genParton_pdgID[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_genParton_ntID[kNPATJetMax];   //[pat_jet_n]
/*
pat_jet_bDiscPositive: tags names <-> index correspondence
trackCountingHighEffBJetTags 0
trackCountingHighPurBJetTags 1
simpleSecondaryVertexHighEffBJetTags 2
simpleSecondaryVertexHighPurBJetTags 3
impactParameterTagInfos 4
jetProbabilityBJetTags 5
jetBProbabilityBJetTags 6
secondaryVertexTagInfos 7
ghostTrackVertexTagInfos 8
simpleSecondaryVertexBJetTags 9
combinedSecondaryVertexBJetTags 10
combinedSecondaryVertexMVABJetTags 11
ghostTrackBJetTags 12
btagSoftElectrons 13
softElectronCands 14
softPFElectrons 15
softElectronTagInfos 16
softElectronBJetTags 17
softElectronByIP3dBJetTags 18
softElectronByPtBJetTags 19
softMuonTagInfos 20
softMuonBJetTags 21
softMuonByIP3dBJetTags 22
softMuonByPtBJetTags 23
combinedMVABJetTags 24

pat_jet_bDiscNegative: tags names <-> index correspondence
negativeTrackCountingHighEffJetTags 0
negativeTrackCountingHighPurJetTags 1
simpleSecondaryVertexNegativeHighEffBJetTags 2
simpleSecondaryVertexNegativeHighPurBJetTags 3
*/  
   Double_t        pat_jet_bDiscriminator[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_bDiscriminator_ssVertex[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_bDiscriminator_ssVertexPure[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_bDiscriminator_combined[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_bDiscriminator_trackCount[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_bDiscriminator_trackCountPure[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_sumTrackPt[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_bDiscPositive[kNPATJetMax][50];   //[pat_jet_n]
   Double_t        pat_jet_bDiscNegative[kNPATJetMax][50];   //[pat_jet_n]
   Int_t           pat_jet_ntracks[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_ntracks_max;
   Int_t           pat_jet_trkIDs[kNPATJetMax][50];   //[pat_jet_n]
   Double_t        pat_jet_emf[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_ehf[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_chargedHadronFraction[kNPATJetMax];
   Double_t        pat_jet_neutralHadronFraction[kNPATJetMax];
   Double_t        pat_jet_chargedEMFraction[kNPATJetMax];
   Double_t        pat_jet_neutralEMFraction[kNPATJetMax];
   Int_t           pat_jet_chargedHadronMultiplicity[kNPATJetMax];
   Int_t           pat_jet_numberConstituents[kNPATJetMax];
   Double_t        pat_jet_charge[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_mass[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_vx[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_vy[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_vz[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_isCalo[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_isPF[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_corrLevel[kNPATJetMax];   //[pat_jet_n]
   Double_t        pat_jet_corr_glue[kNPATJetMax][7];   //[pat_jet_n]
   Double_t        pat_jet_corr_uds[kNPATJetMax][7];   //[pat_jet_n]
   Double_t        pat_jet_corr_c[kNPATJetMax][7];   //[pat_jet_n]
   Double_t        pat_jet_corr_b[kNPATJetMax][7];   //[pat_jet_n]
   Int_t           pat_jet_trigger_nfilter[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_trigger_objectType[kNPATJetMax][5];   //[pat_jet_n]
   Int_t           pat_jet_trigger_objectID[kNPATJetMax][5];   //[pat_jet_n]
   Int_t           pat_jet_loose_PFjetID[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_medium_PFjetID[kNPATJetMax];   //[pat_jet_n]
   Int_t           pat_jet_tight_PFjetID[kNPATJetMax];   //[pat_jet_n]
   Int_t           mc_pdfSetA_N;
   Double_t        mc_pdfSetA[1];   //[mc_pdfSetA_N]
   Int_t           mc_pdfSetB_N;
   Double_t        mc_pdfSetB[1];   //[mc_pdfSetB_N]
   Int_t           mc_pdfSetC_N;
   Double_t        mc_pdfSetC[1];   //[mc_pdfSetA_N]
   Int_t           mc_signature_nJets;
   Int_t           mc_signature_nbJets;
   Int_t           mc_signature_nPhotons;
   Int_t           mc_signature_nMuons;
   Double_t        mc_signature_charge_Muons;
   Int_t           mc_signature_nElectrons;
   Double_t        mc_signature_charge_Electrons;
   Int_t           mc_signature_nTaus;
   Double_t        mc_signature_charge_Taus;
   Double_t        mc_signature_met;
   Double_t        mc_susyscan_vars[kSUSYSCANMAX];
   Int_t           mc_part_n;
   Int_t           mc_part_pdgID[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_mass[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_pt[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_et[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_vx[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_vy[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_vz[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_charge[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_px[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_py[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_pz[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_pmag[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_eta[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_phi[kNPATMCPartMax];   //[mc_part_n]
   Double_t        mc_part_energy[kNPATMCPartMax];   //[mc_part_n]
   Int_t           mc_part_status[kNPATMCPartMax];   //[mc_part_n]
   Int_t           mc_part_barcode[kNPATMCPartMax];   //[mc_part_n]
   Int_t           mc_part_mother_pdgID[kNPATMCPartMax];   //[mc_part_n]
   Int_t           mc_part_mother_ntID[kNPATMCPartMax];   //[mc_part_n]
   Int_t           mc_part_n_children[kNPATMCPartMax];   //[mc_part_n]
   Int_t           reco_beamHalo_EventSmellsLikeHalo;
   Int_t           reco_beamHalo_CSCTightHaloId;
   Int_t           reco_beamHalo_CSCLooseHaloId;
   Int_t           reco_beamHalo_nCSChaloTriggers;
   Int_t           reco_beamHalo_nCSChaloTracks;
   Int_t           reco_beamHalo_nCSCoutOfTimeTriggers;
   Double_t        reco_beamSpot_x;
   Double_t        reco_beamSpot_y;
   Double_t        reco_beamSpot_z;
   Double_t        reco_beamSpot_ex;
   Double_t        reco_beamSpot_ey;
   Double_t        reco_beamSpot_ez;
   Double_t        reco_beamSpot_sigmaz;
   Double_t        reco_beamSpot_dxdz;
   Double_t        reco_beamSpot_width;
   Int_t           reco_track_n;
   Double_t        reco_track_genParticle_dR[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_genParticle_pdgID[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_genParticle_ntID[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_genParticle_mother_pdgID[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_genParticle_mother_ntID[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nValidHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_ntrackerLayersWM[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_npixelLayersWM[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nstripLayersWM[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_muonStationsWVH[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_muonStationsWAH[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nBadMuonHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_outermostMuonStationWithValidHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nValidMuonHitsInFirstStation[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nLostMuonHitsInFirstStation[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nBadMuonHitsInFirstStation[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nAnyMuonHitsInFirstStation[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nValidTrackerHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nValidMuonHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nValidPixelHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nLostHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nLostTrackerHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nLostMuonHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_nLostPixelHits[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_isGlobal[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_isMuon[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_track_isTracker[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_pt[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_px[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_py[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_pz[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_vx[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_vy[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_vz[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_chi2[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_ndof[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_charge[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_dxy[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_dsz[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_d0[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_dz[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_vert_dxy[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_vert_dz[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_beam_dxy[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_beam_dsz[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_beam_d0[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_beam_dz[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_phi[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_eta[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_theta[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_dxyError[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_d0Error[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_dzError[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_phiError[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_etaError[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_thetaError[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_lambdaError[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_trackIso[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_caloIso[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_trackIso1[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_caloIso1[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_trackIso2[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_caloIso2[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_trackIso6[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_caloIso6[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_trackIso9[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_caloIso9[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_trackIso12[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_caloIso12[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_ecaloIso[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_hcaloIso[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_vertWeight[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_PF_chargedHadronIso[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_PF_photonIso[kNRECOTrackMax];   //[reco_track_n]
   Double_t        reco_track_PF_neutralHadronIso[kNRECOTrackMax];   //[reco_track_n]
   Int_t           reco_vertex_n;
   Int_t           reco_vertex_ntrack[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_x[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_y[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_z[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_ex[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_ey[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_ez[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_ndof[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_chi2[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        reco_vertex_wSumPt[kNRECOVertexMax];   //[reco_vertex_n]
   Double_t        pat_met_sumEt;
   Double_t        pat_met_mEtSig;
   Double_t        pat_met_gen_sumEt;
   Double_t        pat_met_px;
   Double_t        pat_met_py;
   Double_t        pat_met_pz;
   Double_t        pat_met_pt;
   Double_t        pat_met_eta;
   Double_t        pat_met_phi;
   Int_t           pat_met_trigger_nfilter;
   Int_t           pat_met_trigger_objectType[5];
   Int_t           pat_met_trigger_objectID[5];
   Double_t        pf_met_sumEt;
   Double_t        pf_met_pt;
   Double_t        pf_met_phi;
   Double_t        pf_met_type1_sumEt;
   Double_t        pf_met_type1_pt;
   Double_t        pf_met_type1_phi;
   Double_t        tc_met_sumEt;
   Double_t        tc_met_pt;
   Double_t        tc_met_phi;
   Long64_t        event;
   Int_t           run;
   Int_t           isRealData;
   Int_t           bunchCrossing;
   Int_t           storeNumber;
   Int_t           lumiBlock;
   float pileup_trueNumInteractions;
   int pileup_numInteractions;
   int pileup_bunchCrossing;             
   Int_t           event_mc_processID;
   Double_t        event_mc_sigma_input;
   Double_t        event_mc_sigma_calc;
   Double_t        event_mc_eff_input;
   Int_t           pat_tau_n;
   Double_t        pat_tau_pt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_px[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_py[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_pz[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_pmag[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_eta[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_emFraction[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_phi[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_trackIso[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_caloIso[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_genLepton_pdgID[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_genLepton_ntID[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_signalTracksInvMass[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_isCalo[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_isPF[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_leadTrack_ntID[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_signalTracks_n[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_signalTracks_ntIDs[kNPATTauMax][10];   //[pat_tau_n]
   Int_t           pat_tau_isoTracks_n[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_isoTracks_ntIDs[kNPATTauMax][10];   //[pat_tau_n]
   Double_t        pat_tau_calo_leadTracksignedSipt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_calo_isoChargedPtSum[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_calo_isoECALEtSum[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_calo_maxHCALhitEt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_leadTracksignedSipt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_isoChargedPtSum[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_isoGammaEtSum[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_isoSumPt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_maxHCALhitEt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_chargedHadronIso03[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_neutralHadronIso03[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_photonIso03[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_chargedHadronIso05[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_neutralHadronIso05[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_photonIso05[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_isoChargedCandMaxPt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_isoGammaCandMaxPt[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_isoKlongCandMaxPt[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_PF_NsigCharged[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_PF_NsigGamma[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_signalMass[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_signalCharge[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_againstMuon[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_againstElectron[kNPATTauMax];   //[pat_tau_n]
   Double_t        pat_tau_PF_Discriminants[kNPATTauMax][50];   //[pat_tau_n]
   Int_t           pat_tau_trigger_nfilter[kNPATTauMax];   //[pat_tau_n]
   Int_t           pat_tau_trigger_objectType[kNPATTauMax][5];   //[pat_tau_n]
   Int_t           pat_tau_trigger_objectID[kNPATTauMax][5];   //[pat_tau_n]
   Int_t           pat_photon_n;
   Double_t        pat_photon_pt[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_px[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_py[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_pz[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_eta[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_phi[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_pmag[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_trackIso[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_caloIso[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_genPhoton_pdgID[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_genPhoton_ntID[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_trigger_nfilter[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_trigger_objectType[kNPATPhotonMax][5];   //[pat_photon_n]
   Int_t           pat_photon_trigger_objectID[kNPATPhotonMax][5];   //[pat_photon_n]
   Double_t        pat_photon_hadOverEm[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_hadTowOverEm[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_conversionSafeElectronVeto[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_sigmaIetaIeta[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_endcap[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_barrel[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_scEt[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_isLoose[kNPATPhotonMax];   //[pat_photon_n]
   Int_t           pat_photon_isTight[kNPATPhotonMax];   //[pat_photon_n]
   Double_t        pat_photon_ecalRecHitEtR03[kNPATPhotonMax];
   Double_t        pat_photon_hcalTowerEtR03[kNPATPhotonMax];
   Double_t        pat_photon_hcalDepth1TowerEtR03[kNPATPhotonMax];
   Double_t        pat_photon_hcalDepth2TowerEtR03[kNPATPhotonMax];
   Double_t        pat_photon_ecalRecHitEtR04[kNPATPhotonMax];
   Double_t        pat_photon_hcalTowerEtR04[kNPATPhotonMax];
   Double_t        pat_photon_hcalDepth1TowerEtR04[kNPATPhotonMax];
   Double_t        pat_photon_hcalDepth2TowerEtR04[kNPATPhotonMax];
   Double_t        pat_photon_trackSumPtHollowR03[kNPATPhotonMax];
   Double_t        pat_photon_trackSumPtHollowR04[kNPATPhotonMax];
   Double_t        pat_photon_trackSumPtSolidR03[kNPATPhotonMax];
   Double_t        pat_photon_trackSumPtSolidR04[kNPATPhotonMax];
   Float_t         pat_photon_mustacheEt[kNPATPhotonMax];
   Double_t        pat_photon_MVAGlobalCorrEError[kNPATPhotonMax];
   Float_t         pat_photon_MVAGlobalCorrE[kNPATPhotonMax];
   Double_t        pat_photon_PFPhotonRes[kNPATPhotonMax];
   Double_t        pat_photon_chargedHadronIso[kNPATPhotonMax];
   Double_t        pat_photon_neutralHadronIso[kNPATPhotonMax];
   Double_t        pat_photon_photonIso[kNPATPhotonMax];
   Double_t        pat_photon_r9[kNPATPhotonMax];
   Float_t         pat_photon_EOut[kNPATPhotonMax];
   Int_t           pat_photon_track_nHollowR03[kNPATPhotonMax];
   Int_t           pat_photon_track_nHollowR04[kNPATPhotonMax];
   Int_t           pat_photon_track_nSolidR03[kNPATPhotonMax];
   Int_t           pat_photon_track_nSolidR04[kNPATPhotonMax];
   Int_t           hlt_triggers_npassed;
   Float_t         hlt_triggers[kNHLTTriggerMax];   //[hlt_triggers_npassed]
   Int_t           hlt_triggers_id[kNHLTTriggerMax];   //[hlt_triggers_npassed]
   Int_t           hlt_triggers_prescale[kNHLTTriggerMax];   //[hlt_triggers_npassed]
   Int_t           hlt_triggers_prescale_L1[kNHLTTriggerMax];   //[hlt_triggers_npassed]
   Int_t           hlt_triggers_prescale_HLT[kNHLTTriggerMax];   //[hlt_triggers_npassed]
   Int_t           hlt_triggers_wasrun[kNHLTTriggerMax];   //[hlt_triggers_npassed]

   Int_t primaryVertexFilter;
   Int_t noScrapingFilter;
   Int_t HBHENoiseFilter;
   Int_t CSCTightHaloFilter;
   Int_t hcalLaserEventFilter;
   Int_t EcalDeadCellTriggerPrimitiveFilter;
   Int_t trackingFailureFilter;
   Int_t eeBadScFilter;


   SkimTreeReader(TTree *tree);
   virtual ~SkimTreeReader();
   virtual void     Init(TTree *tree);

 protected:
   void makeProducts();

   void createMuons();
   void createElectrons();
   void createTracks();
   void createTaus();
   void createPhotons();
   void createJets();
   void createMET();
   void createMCParticles();
   void createRecoVertices();
   void createBeamSpots();
   void createTriggers();
   void createVariables();
   double calculateJetBeta(int,int);
   SignatureObject* findTauLeadingTrack(SignatureObject*);

   ClassDef(SkimTreeReader,1);
};

#endif

