//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun  6 06:54:13 2012 by ROOT version 5.32/00
// from TTree SkimTree/PAT information from CMS MC
// found on file: results_35_1_TFd.root
//////////////////////////////////////////////////////////

#ifndef SkimTreeBase_h
#define SkimTreeBase_h

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


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class SkimTreeBase : virtual public TObject {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
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

   // List of branches
   TBranch        *b_pat_muon_n;   //!
   TBranch        *b_pat_muon_pt;   //!
   TBranch        *b_pat_muon_et;   //!
   TBranch        *b_pat_muon_px;   //!
   TBranch        *b_pat_muon_py;   //!
   TBranch        *b_pat_muon_pz;   //!
   TBranch        *b_pat_muon_eta;   //!
   TBranch        *b_pat_muon_phi;   //!
   TBranch        *b_pat_muon_pmag;   //!
   TBranch        *b_pat_muon_isPF;   //!
   TBranch        *b_pat_muon_PFMatchPdgId;   //!
   TBranch        *b_pat_muon_PFPAT_dpt;   //!
   TBranch        *b_pat_muon_PFPAT_dphi;   //!
   TBranch        *b_pat_muon_PFPAT_deta;   //!
   TBranch        *b_pat_muon_PFPAT_dq;   //!
   TBranch        *b_pat_muon_energy;   //!
   TBranch        *b_pat_muon_charge;   //!
   TBranch        *b_pat_muon_trackID;   //!
   TBranch        *b_pat_muon_globalTrackID;   //!
   TBranch        *b_pat_muon_muonTrackID;   //!
   TBranch        *b_pat_muon_caloIso;   //!
   TBranch        *b_pat_muon_ecaloIso;   //!
   TBranch        *b_pat_muon_hcaloIso;   //!
   TBranch        *b_pat_muon_trackIso;   //!
   TBranch        *b_pat_muon_beta;   //!
   TBranch        *b_pat_muon_PF_chargedHadronIso;   //!
   TBranch        *b_pat_muon_PF_photonIso;   //!
   TBranch        *b_pat_muon_PF_neutralHadronIso;   //!
   TBranch        *b_pat_muon_allTrackIso;   //!
   TBranch        *b_pat_muon_vertTrackIso;   //!
   TBranch        *b_pat_muon_calEnergyEM;   //!
   TBranch        *b_pat_muon_calEnergyHad;   //!
   TBranch        *b_pat_muon_ecalIsoDep;   //!
   TBranch        *b_pat_muon_hcalIsoDep;   //!
   TBranch        *b_pat_muon_dRmin;   //!
   TBranch        *b_pat_muon_dRmin_track_ntID;   //!
   TBranch        *b_pat_muon_dRmin05;   //!
   TBranch        *b_pat_muon_dRmin05_track_ntID;   //!
   TBranch        *b_pat_muon_dRmin10;   //!
   TBranch        *b_pat_muon_dRmin10_track_ntID;   //!
   TBranch        *b_pat_muon_genLepton_dR;   //!
   TBranch        *b_pat_muon_genLepton_pdgID;   //!
   TBranch        *b_pat_muon_genLepton_ntID;   //!
   TBranch        *b_pat_muon_genLepton_mother_pdgID;   //!
   TBranch        *b_pat_muon_genLepton_mother_ntID;   //!
   TBranch        *b_pat_muon_isGlobalMuon;   //!
   TBranch        *b_pat_muon_isTrackerMuon;   //!
   TBranch        *b_pat_muon_isStandAloneMuon;   //!
   TBranch        *b_pat_muon_isCaloMuon;   //!
   TBranch        *b_pat_muon_isGlobalMuonPromptTight;   //!
   TBranch        *b_pat_muon_isTMLastStationTight;   //!
   TBranch        *b_pat_muon_isTMLastStationAngTight;   //!
   TBranch        *b_pat_muon_trigger_nfilter;   //!
   TBranch        *b_pat_muon_trigger_objectType;   //!
   TBranch        *b_pat_muon_trigger_objectID;   //!
   TBranch        *b_pat_muon_segmentCompatibility;   //!
   TBranch        *b_pat_muon_isCaloCompatibilityValid;   //!
   TBranch        *b_pat_muon_caloCompatibility;   //!
   TBranch        *b_pat_muon_numberOfMatches;   //!
   TBranch        *b_pat_muon_Direction;   //!
   TBranch        *b_pat_muon_cosmicCompatibility;   //!
   TBranch        *b_pat_muon_timeCompatibility;   //!
   TBranch        *b_pat_muon_backToBackCompatibility;   //!
   TBranch        *b_pat_muon_overlapCompatibility;   //!
   TBranch        *b_pat_muon_normalizedChi2;
   TBranch         *b_pat_muon_innerVertDz;
   TBranch         *b_pat_muon_innerVertDxy;
   TBranch         *b_pat_muon_innerNumberOfValidPixelHits;
   TBranch        *b_pat_electron_n;   //!
   TBranch        *b_pat_electron_pt;   //!
   TBranch        *b_pat_electron_et;   //!
   TBranch        *b_pat_electron_px;   //!
   TBranch        *b_pat_electron_py;   //!
   TBranch        *b_pat_electron_pz;   //!
   TBranch        *b_pat_electron_pmag;   //!
   TBranch        *b_pat_electron_eta;   //!
   TBranch        *b_pat_electron_phi;   //!
   TBranch        *b_pat_electron_isPF;   //!
   TBranch        *b_pat_electron_conv_vtxProb;   //!
   TBranch        *b_pat_electron_classification;   //!
   TBranch        *b_pat_electron_PFMatchPdgId;   //!
   TBranch        *b_pat_electron_PFPAT_dpt;   //!
   TBranch        *b_pat_electron_PFPAT_dphi;   //!
   TBranch        *b_pat_electron_PFPAT_deta;   //!
   TBranch        *b_pat_electron_PFPAT_dq;   //!
   TBranch        *b_pat_electron_energy;   //!
   TBranch        *b_pat_electron_charge;   //!
   TBranch        *b_pat_electron_trackID;   //!
   TBranch        *b_pat_electron_caloIso;   //!
   TBranch        *b_pat_electron_trackIso;   //!
   TBranch        *b_pat_electron_dRmin;   //!
   TBranch        *b_pat_electron_dRmin_track_ntID;   //!
   TBranch        *b_pat_electron_genLepton_pdgID;   //!
   TBranch        *b_pat_electron_genLepton_ntID;   //!
   TBranch        *b_pat_electron_GsfCtfScPixChargeConsistent;   //!
   TBranch        *b_pat_electron_GsfScPixChargeConsistent;   //!
   TBranch        *b_pat_electron_GsfCtfChargeConsistent;   //!
   TBranch        *b_pat_electron_eidTight;   //!
   TBranch        *b_pat_electron_eidLoose;   //!
   TBranch        *b_pat_electron_eidRobustTight;   //!
   TBranch        *b_pat_electron_eidRobustLoose;   //!
   TBranch        *b_pat_electron_eidRobustHighEnergy;   //!
   TBranch        *b_pat_electron_ecaloIso;   //!
   TBranch        *b_pat_electron_hcaloIso;   //!
   TBranch        *b_pat_electron_PF_chargedHadronIso;   //!
   TBranch        *b_pat_electron_PF_photonIso;   //!
   TBranch        *b_pat_electron_PF_neutralHadronIso;   //!
   TBranch        *b_pat_electron_PF_chargedHadronIso_04;   //!
   TBranch        *b_pat_electron_PF_photonIso_04;   //!
   TBranch        *b_pat_electron_PF_neutralHadronIso_04;   //!
   TBranch        *b_pat_electron_classification_04;   //!
   TBranch        *b_pat_electron_caloEnergy;   //!
   TBranch        *b_pat_electron_hadOverEm;   //!
   TBranch        *b_pat_electron_eOverPin;   //!
   TBranch        *b_pat_electron_sigmaEtaEta;   //!
   TBranch        *b_pat_electron_sigmaIetaIeta;   //!
   TBranch        *b_pat_electron_e1x5;   //!
   TBranch        *b_pat_electron_e2x5Max;   //!
   TBranch        *b_pat_electron_e5x5;   //!
   TBranch        *b_pat_electron_deltaPhi;   //!
   TBranch        *b_pat_electron_deltaEta;   //!
   TBranch        *b_pat_electron_status;   //!
   TBranch        *b_pat_electron_trigger_nfilter;   //!
   TBranch        *b_pat_electron_trigger_objectType;   //!
   TBranch        *b_pat_electron_trigger_objectID;   //!
   TBranch        *b_pat_electron_fbrem;   //!
   TBranch        *b_pat_electron_ecalDriven;   //!
   TBranch        *b_pat_electron_swissCross;   //!
   TBranch        *b_pat_electron_eMax;   //!
   TBranch        *b_pat_electron_IsConversion;   //!
   TBranch        *b_pat_electron_ConversionDist;   //!
   TBranch        *b_pat_electron_ConversionDCotTheta;   //!
   TBranch        *b_pat_electron_NumberOfExpectedInnerHits;   //!
   TBranch        *b_pat_electron_NumberOfLostInnerHits;   //!
   TBranch        *b_pat_electron_eSeedClusterOverPout;   //!
   TBranch        *b_pat_electron_fMVAVar_fbrem;   //!
   TBranch        *b_pat_electron_fMVAVar_kfchi2;   //!
   TBranch        *b_pat_electron_fMVAVar_kfhits;   //!
   TBranch        *b_pat_electron_fMVAVar_gsfchi2;   //!
   TBranch        *b_pat_electron_fMVAVar_deta;   //!
   TBranch        *b_pat_electron_fMVAVar_dphi;   //!
   TBranch        *b_pat_electron_fMVAVar_detacalo;   //!
   TBranch        *b_pat_electron_fMVAVar_dphicalo;   //!
   TBranch        *b_pat_electron_fMVAVar_see;   //!
   TBranch        *b_pat_electron_fMVAVar_spp;   //!
   TBranch        *b_pat_electron_fMVAVar_etawidth;   //!
   TBranch        *b_pat_electron_fMVAVar_phiwidth;   //!
   TBranch        *b_pat_electron_fMVAVar_e1x5e5x5;   //!
   TBranch        *b_pat_electron_fMVAVar_R9;   //!
   TBranch        *b_pat_electron_fMVAVar_nbrems;   //!
   TBranch        *b_pat_electron_fMVAVar_HoE;   //!
   TBranch        *b_pat_electron_fMVAVar_EoP;   //!
   TBranch        *b_pat_electron_fMVAVar_IoEmIoP;   //!
   TBranch        *b_pat_electron_fMVAVar_eleEoPout;   //!
   TBranch        *b_pat_electron_fMVAVar_PreShowerOverRaw;   //!
   TBranch        *b_pat_electron_fMVAVar_d0;   //!
   TBranch        *b_pat_electron_fMVAVar_dz;   //!
   TBranch        *b_pat_electron_fMVAVar_eta;   //!
   TBranch        *b_pat_electron_fMVAVar_pt;   //!
   TBranch        *b_pat_jet_n;   //!
   TBranch        *b_pat_rho;   //!
   TBranch        *b_pat_rho_neutral;   //!
   TBranch        *b_pat_jet_pt;   //!
   TBranch        *b_pat_jet_et;   //!
   TBranch        *b_pat_jet_raw_pt;   //!
   TBranch        *b_pat_jet_raw_et;   //!
   TBranch        *b_pat_jet_px;   //!
   TBranch        *b_pat_jet_py;   //!
   TBranch        *b_pat_jet_pz;   //!
   TBranch        *b_pat_jet_pmag;   //!
   TBranch        *b_pat_jet_uncertainty;   //!
   TBranch        *b_pat_jet_eta;   //!
   TBranch        *b_pat_jet_phi;   //!
   TBranch        *b_pat_jet_energy;   //!
   TBranch        *b_pat_jet_etaetaMoment;   //!
   TBranch        *b_pat_jet_etaphiMoment;   //!
   TBranch        *b_pat_jet_phiphiMoment;   //!
   TBranch        *b_pat_jet_genParton_pdgID;   //!
   TBranch        *b_pat_jet_genParton_ntID;   //!
   TBranch        *b_pat_jet_bDiscriminator;   //!
   TBranch        *b_pat_jet_bDiscriminator_ssVertex;   //!
   TBranch        *b_pat_jet_bDiscriminator_ssVertexPure;   //!
   TBranch        *b_pat_jet_bDiscriminator_combined;   //!
   TBranch        *b_pat_jet_bDiscriminator_trackCount;   //!
   TBranch        *b_pat_jet_bDiscriminator_trackCountPure;   //!
   TBranch        *b_pat_jet_sumTrackPt;   //!
   TBranch        *b_pat_jet_bDiscPositive;   //!
   TBranch        *b_pat_jet_bDiscNegative;   //!
   TBranch        *b_pat_jet_ntracks;   //!
   TBranch        *b_pat_jet_ntracks_max;   //!
   TBranch        *b_pat_jet_trkIDs;   //!
   TBranch        *b_pat_jet_emf;   //!
   TBranch        *b_pat_jet_ehf;   //!
   TBranch        *b_pat_jet_chargedHadronFraction;   //!
   TBranch        *b_pat_jet_neutralHadronFraction;   //!
   TBranch        *b_pat_jet_chargedEMFraction;   //!
   TBranch        *b_pat_jet_neutralEMFraction;   //!
   TBranch        *b_pat_jet_chargedHadronMultiplicity;   //!
   TBranch        *b_pat_jet_numberConstituents;   //!
   TBranch        *b_pat_jet_charge;   //!
   TBranch        *b_pat_jet_mass;   //!
   TBranch        *b_pat_jet_vx;   //!
   TBranch        *b_pat_jet_vy;   //!
   TBranch        *b_pat_jet_vz;   //!
   TBranch        *b_pat_jet_isCalo;   //!
   TBranch        *b_pat_jet_isPF;   //!
   TBranch        *b_pat_jet_corrLevel;   //!
   TBranch        *b_pat_jet_corr_glue;   //!
   TBranch        *b_pat_jet_corr_uds;   //!
   TBranch        *b_pat_jet_corr_c;   //!
   TBranch        *b_pat_jet_corr_b;   //!
   TBranch        *b_pat_jet_trigger_nfilter;   //!
   TBranch        *b_pat_jet_trigger_objectType;   //!
   TBranch        *b_pat_jet_trigger_objectID;   //!
   TBranch        *b_pat_jet_loose_PFjetID;   //!
   TBranch        *b_pat_jet_medium_PFjetID;   //!
   TBranch        *b_pat_jet_tight_PFjetID;   //!
   TBranch        *b_mc_pdfSetA_N;   //!
   TBranch        *b_mc_pdfSetA;   //!
   TBranch        *b_mc_pdfSetB_N;   //!
   TBranch        *b_mc_pdfSetB;   //!
   TBranch        *b_mc_pdfSetC_N;   //!
   TBranch        *b_mc_pdfSetC;   //!
   TBranch        *b_mc_signature_nJets;   //!
   TBranch        *b_mc_signature_nbJets;   //!
   TBranch        *b_mc_signature_nPhotons;   //!
   TBranch        *b_mc_signature_nMuons;   //!
   TBranch        *b_mc_signature_charge_Muons;   //!
   TBranch        *b_mc_signature_nElectrons;   //!
   TBranch        *b_mc_signature_Electrons;   //!
   TBranch        *b_mc_signature_nTaus;   //!
   TBranch        *b_mc_signature_charge_Taus;   //!
   TBranch        *b_mc_signature_met;   //!
   TBranch        *b_mc_susyscan_vars;   //!
   TBranch        *b_mc_part_n;   //!
   TBranch        *b_mc_part_pdgID;   //!
   TBranch        *b_mc_part_mass;   //!
   TBranch        *b_mc_part_pt;   //!
   TBranch        *b_mc_part_et;   //!
   TBranch        *b_mc_part_vx;   //!
   TBranch        *b_mc_part_vy;   //!
   TBranch        *b_mc_part_vz;   //!
   TBranch        *b_mc_part_charge;   //!
   TBranch        *b_mc_part_px;   //!
   TBranch        *b_mc_part_py;   //!
   TBranch        *b_mc_part_pz;   //!
   TBranch        *b_mc_part_pmag;   //!
   TBranch        *b_mc_part_eta;   //!
   TBranch        *b_mc_part_phi;   //!
   TBranch        *b_mc_part_energy;   //!
   TBranch        *b_mc_part_status;   //!
   TBranch        *b_mc_part_barcode;   //!
   TBranch        *b_mc_part_mother_pdgID;   //!
   TBranch        *b_mc_part_mother_ntID;   //!
   TBranch        *b_mc_part_n_children;   //!
   TBranch        *b_reco_beamHalo_EventSmellsLikeHalo;   //!
   TBranch        *b_reco_beamHalo_CSCTightHaloId;   //!
   TBranch        *b_reco_beamHalo_CSCLooseHaloId;   //!
   TBranch        *b_reco_beamHalo_nCSChaloTriggers;   //!
   TBranch        *b_reco_beamHalo_nCSChaloTracks;   //!
   TBranch        *b_reco_beamHalo_nCSCoutOfTimeTriggers;   //!
   TBranch        *b_reco_beamSpot_x;   //!
   TBranch        *b_reco_beamSpot_y;   //!
   TBranch        *b_reco_beamSpot_z;   //!
   TBranch        *b_reco_beamSpot_ex;   //!
   TBranch        *b_reco_beamSpot_ey;   //!
   TBranch        *b_reco_beamSpot_ez;   //!
   TBranch        *b_reco_beamSpot_sigmaz;   //!
   TBranch        *b_reco_beamSpot_dxdz;   //!
   TBranch        *b_reco_beamSpot_width;   //!
   TBranch        *b_reco_track_n;   //!
   TBranch        *b_reco_track_genParticle_dR;   //!
   TBranch        *b_reco_track_genParticle_pdgID;   //!
   TBranch        *b_reco_track_genParticle_ntID;   //!
   TBranch        *b_reco_track_genParticle_mother_pdgID;   //!
   TBranch        *b_reco_track_genParticle_mother_ntID;   //!
   TBranch        *b_reco_track_nValidHits;   //!
   TBranch        *b_reco_track_ntrackerLayersWM;   //!
   TBranch        *b_reco_track_npixelLayersWM;   //!
   TBranch        *b_reco_track_nstripLayersWM;   //!
   TBranch        *b_reco_track_muonStationsWVH;   //!
   TBranch        *b_reco_track_muonStationsWAH;   //!
   TBranch        *b_reco_track_nBadMuonHits;   //!
   TBranch        *b_reco_track_outermostMuonStationWithValidHits;   //!
   TBranch        *b_reco_track_nValidMuonHitsInFirstStation;   //!
   TBranch        *b_reco_track_nLostMuonHitsInFirstStation;   //!
   TBranch        *b_reco_track_nBadMuonHitsInFirstStation;   //!
   TBranch        *b_reco_track_nAnyMuonHitsInFirstStation;   //!
   TBranch        *b_reco_track_nValidTrackerHits;   //!
   TBranch        *b_reco_track_nValidMuonHits;   //!
   TBranch        *b_reco_track_nValidPixelHits;   //!
   TBranch        *b_reco_track_nLostHits;   //!
   TBranch        *b_reco_track_nLostTrackerHits;   //!
   TBranch        *b_reco_track_nLostMuonHits;   //!
   TBranch        *b_reco_track_nLostPixelHits;   //!
   TBranch        *b_reco_track_isGlobal;   //!
   TBranch        *b_reco_track_isMuon;   //!
   TBranch        *b_reco_track_isTracker;   //!
   TBranch        *b_reco_track_pt;   //!
   TBranch        *b_reco_track_px;   //!
   TBranch        *b_reco_track_py;   //!
   TBranch        *b_reco_track_pz;   //!
   TBranch        *b_reco_track_vx;   //!
   TBranch        *b_reco_track_vy;   //!
   TBranch        *b_reco_track_vz;   //!
   TBranch        *b_reco_track_chi2;   //!
   TBranch        *b_reco_track_ndof;   //!
   TBranch        *b_reco_track_charge;   //!
   TBranch        *b_reco_track_dxy;   //!
   TBranch        *b_reco_track_dsz;   //!
   TBranch        *b_reco_track_d0;   //!
   TBranch        *b_reco_track_dz;   //!
   TBranch        *b_reco_track_vert_dxy;   //!
   TBranch        *b_reco_track_vert_dz;   //!
   TBranch        *b_reco_track_beam_dxy;   //!
   TBranch        *b_reco_track_beam_dsz;   //!
   TBranch        *b_reco_track_beam_d0;   //!
   TBranch        *b_reco_track_beam_dz;   //!
   TBranch        *b_reco_track_phi;   //!
   TBranch        *b_reco_track_eta;   //!
   TBranch        *b_reco_track_theta;   //!
   TBranch        *b_reco_track_dxyError;   //!
   TBranch        *b_reco_track_d0Error;   //!
   TBranch        *b_reco_track_dzError;   //!
   TBranch        *b_reco_track_phiError;   //!
   TBranch        *b_reco_track_etaError;   //!
   TBranch        *b_reco_track_thetaError;   //!
   TBranch        *b_reco_track_lambdaError;   //!
   TBranch        *b_reco_track_trackIso;   //!
   TBranch        *b_reco_track_caloIso;   //!
   TBranch        *b_reco_track_trackIso1;   //!
   TBranch        *b_reco_track_caloIso1;   //!
   TBranch        *b_reco_track_trackIso2;   //!
   TBranch        *b_reco_track_caloIso2;   //!
   TBranch        *b_reco_track_trackIso6;   //!
   TBranch        *b_reco_track_caloIso6;   //!
   TBranch        *b_reco_track_trackIso9;   //!
   TBranch        *b_reco_track_caloIso9;   //!
   TBranch        *b_reco_track_trackIso12;   //!
   TBranch        *b_reco_track_caloIso12;   //!
   TBranch        *b_reco_track_ecaloIso;   //!
   TBranch        *b_reco_track_hcaloIso;   //!
   TBranch        *b_reco_track_vertWeight;   //!
   TBranch        *b_reco_track_PF_chargedHadronIso;   //!
   TBranch        *b_reco_track_PF_photonIso;   //!
   TBranch        *b_reco_track_PF_neutralHadronIso;   //!
   TBranch        *b_reco_vertex_n;   //!
   TBranch        *b_reco_vertex_ntrack;   //!
   TBranch        *b_reco_vertex_x;   //!
   TBranch        *b_reco_vertex_y;   //!
   TBranch        *b_reco_vertex_z;   //!
   TBranch        *b_reco_vertex_ex;   //!
   TBranch        *b_reco_vertex_ey;   //!
   TBranch        *b_reco_vertex_ez;   //!
   TBranch        *b_reco_vertex_ndof;   //!
   TBranch        *b_reco_vertex_chi2;   //!
   TBranch        *b_reco_vertex_wSumPt;   //!
   TBranch        *b_pat_met_sumEt;   //!
   TBranch        *b_pat_met_mEtSig;   //!
   TBranch        *b_pat_met_gen_sumEt;   //!
   TBranch        *b_pat_met_px;   //!
   TBranch        *b_pat_met_py;   //!
   TBranch        *b_pat_met_pz;   //!
   TBranch        *b_pat_met_pt;   //!
   TBranch        *b_pat_met_eta;   //!
   TBranch        *b_pat_met_phi;   //!
   TBranch        *b_pat_met_trigger_nfilter;   //!
   TBranch        *b_pat_met_trigger_objectType;   //!
   TBranch        *b_pat_met_trigger_objectID;   //!
   TBranch        *b_pf_met_sumEt;   //!
   TBranch        *b_pf_met_pt;   //!
   TBranch        *b_pf_met_phi;   //!
   TBranch        *b_pf_met_type1_sumEt;   //!
   TBranch        *b_pf_met_type1_pt;   //!
   TBranch        *b_pf_met_type1_phi;   //!
   TBranch        *b_tc_met_sumEt;   //!
   TBranch        *b_tc_met_pt;   //!
   TBranch        *b_tc_met_phi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_run;   //!
   TBranch        *b_isRealData;   //!
   TBranch        *b_bunchCrossing;   //!
   TBranch        *b_storeNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_pileup_trueNumInteractions;   //!
   TBranch        *b_pileup_numInteractions;   //!
   TBranch        *b_pileup_bunchCrossing;   //!
   TBranch        *b_event_mc_processID;   //!
   TBranch        *b_event_mc_sigma_input;   //!
   TBranch        *b_event_mc_sigma_calc;   //!
   TBranch        *b_event_mc_eff_input;   //!
   TBranch        *b_pat_tau_n;   //!
   TBranch        *b_pat_tau_pt;   //!
   TBranch        *b_pat_tau_px;   //!
   TBranch        *b_pat_tau_py;   //!
   TBranch        *b_pat_tau_pz;   //!
   TBranch        *b_pat_tau_pmag;   //!
   TBranch        *b_pat_tau_eta;   //!
   TBranch        *b_pat_tau_emFraction;   //!
   TBranch        *b_pat_tau_phi;   //!
   TBranch        *b_pat_tau_trackIso;   //!
   TBranch        *b_pat_tau_caloIso;   //!
   TBranch        *b_pat_tau_genLepton_pdgID;   //!
   TBranch        *b_pat_tau_genLepton_ntID;   //!
   TBranch        *b_pat_tau_signalTracksInvMass;   //!
   TBranch        *b_pat_tau_isCalo;   //!
   TBranch        *b_pat_tau_isPF;   //!
   TBranch        *b_pat_tau_leadTrack_ntID;   //!
   TBranch        *b_pat_tau_signalTracks_n;   //!
   TBranch        *b_pat_tau_signalTracks_ntIDs;   //!
   TBranch        *b_pat_tau_isoTracks_n;   //!
   TBranch        *b_pat_tau_isoTracks_ntIDs;   //!
   TBranch        *b_pat_tau_calo_leadTracksignedSipt;   //!
   TBranch        *b_pat_tau_calo_isoChargedPtSum;   //!
   TBranch        *b_pat_tau_calo_isoECALEtSum;   //!
   TBranch        *b_pat_tau_calo_maxHCALhitEt;   //!
   TBranch        *b_pat_tau_PF_leadTracksignedSipt;   //!
   TBranch        *b_pat_tau_PF_isoChargedPtSum;   //!
   TBranch        *b_pat_tau_PF_isoGammaEtSum;   //!
   TBranch        *b_pat_tau_PF_isoSumPt;   //!
   TBranch        *b_pat_tau_PF_maxHCALhitEt;   //!
   TBranch        *b_pat_tau_PF_chargedHadronIso03;   //!
   TBranch        *b_pat_tau_PF_neutralHadronIso03;   //!
   TBranch        *b_pat_tau_PF_photonIso03;   //!
   TBranch        *b_pat_tau_PF_chargedHadronIso05;   //!
   TBranch        *b_pat_tau_PF_neutralHadronIso05;   //!
   TBranch        *b_pat_tau_PF_photonIso05;   //!
   TBranch        *b_pat_tau_PF_isoChargedCandMaxPt;   //!
   TBranch        *b_pat_tau_PF_isoGammaCandMaxPt;   //!
   TBranch        *b_pat_tau_PF_isoKlongCandMaxPt;   //!
   TBranch        *b_pat_tau_PF_NsigCharged;   //!
   TBranch        *b_pat_tau_PF_NsigGamma;   //!
   TBranch        *b_pat_tau_PF_signalMass;   //!
   TBranch        *b_pat_tau_PF_signalCharge;   //!
   TBranch        *b_pat_tau_PF_againstMuon;   //!
   TBranch        *b_pat_tau_PF_againstElectron;   //!
   TBranch        *b_pat_tau_PF_Discriminants;   //!
   TBranch        *b_pat_tau_trigger_nfilter;   //!
   TBranch        *b_pat_tau_trigger_objectType;   //!
   TBranch        *b_pat_tau_trigger_objectID;   //!
   TBranch        *b_pat_photon_n;   //!
   TBranch        *b_pat_photon_pt;   //!
   TBranch        *b_pat_photon_px;   //!
   TBranch        *b_pat_photon_py;   //!
   TBranch        *b_pat_photon_pz;   //!
   TBranch        *b_pat_photon_eta;   //!
   TBranch        *b_pat_photon_phi;   //!
   TBranch        *b_pat_photon_pmag;   //!
   TBranch        *b_pat_photon_trackIso;   //!
   TBranch        *b_pat_photon_caloIso;   //!
   TBranch        *b_pat_photon_genPhoton_pdgID;   //!
   TBranch        *b_pat_photon_genPhoton_ntID;   //!
   TBranch        *b_pat_photon_trigger_nfilter;   //!
   TBranch        *b_pat_photon_trigger_objectType;   //!
   TBranch        *b_pat_photon_trigger_objectID;   //!
   TBranch        *b_pat_photon_hadOverEm;   //!
   TBranch        *b_pat_photon_hadTowOverEm;   //!
   TBranch        *b_pat_photon_conversionSafeElectronVeto;   //!
   TBranch        *b_pat_photon_sigmaIetaIeta;   //!
   TBranch        *b_pat_photon_endcap;   //!
   TBranch        *b_pat_photon_barrel;   //!
   TBranch        *b_pat_photon_scEt;   //!
   TBranch        *b_pat_photon_isLoose;   //!
   TBranch        *b_pat_photon_isTight;   //!
   TBranch        *b_pat_photon_ecalRecHitEtR03;   //!
   TBranch        *b_pat_photon_hcalTowerEtR03;   //!
   TBranch        *b_pat_photon_hcalDepth1TowerEtR03;   //!
   TBranch        *b_pat_photon_hcalDepth2TowerEtR03;   //!
   TBranch        *b_pat_photon_ecalRecHitEtR04;   //!
   TBranch        *b_pat_photon_hcalTowerEtR04;   //!
   TBranch        *b_pat_photon_hcalDepth1TowerEtR04;   //!
   TBranch        *b_pat_photon_hcalDepth2TowerEtR04;   //!
   TBranch        *b_pat_photon_trackSumPtHollowR03;   //!
   TBranch        *b_pat_photon_trackSumPtHollowR04;   //!
   TBranch        *b_pat_photon_trackSumPtSolidR03;   //!
   TBranch        *b_pat_photon_trackSumPtSolidR04;   //!
   TBranch        *b_pat_photon_mustacheEt;   //!
   TBranch        *b_pat_photon_MVAGlobalCorrEError;   //!
   TBranch        *b_pat_photon_MVAGlobalCorrE;   //!
   TBranch        *b_pat_photon_PFPhotonRes;   //!
   TBranch        *b_pat_photon_chargedHadronIso;   //!
   TBranch        *b_pat_photon_neutralHadronIso;   //!
   TBranch        *b_pat_photon_photonIso;   //!
   TBranch        *b_pat_photon_r9;   //!
   TBranch        *b_pat_photon_EOut;   //!
   TBranch        *b_pat_photon_track_nHollowR03;   //!
   TBranch        *b_pat_photon_track_nHollowR04;   //!
   TBranch        *b_pat_photon_track_nSolidR03;   //!
   TBranch        *b_pat_photon_track_nSolidR04;   //!
   TBranch        *b_hlt_triggers_npassed;   //!
   TBranch        *b_hlt_triggers;   //!
   TBranch        *b_hlt_triggers_id;   //!
   TBranch        *b_hlt_triggers_prescale;   //!
   TBranch        *b_hlt_triggers_prescale_L1;   //!
   TBranch        *b_hlt_triggers_prescale_HLT;   //!
   TBranch        *b_hlt_triggers_wasrun;   //!

   TBranch        *b_primaryVertexFilter;
   TBranch        *b_noScrapingFilter;
   TBranch        *b_HBHENoiseFilter;
   TBranch        *b_CSCTightHaloFilter;
   TBranch        *b_hcalLaserEventFilter;
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;
   TBranch        *b_trackingFailureFilter;
   TBranch        *b_eeBadScFilter;

   TRandom *m_randomGenerator; //Rutgers
   Int_t m_enforce_mass_charge; //Rutgers

   SkimTreeBase(TTree *tree=0);
   virtual ~SkimTreeBase();
   //virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   //Rutgers added functions
   virtual void InitializeData(); //Defined in SkimTreeBase.h. The rest are in SkimTreeBase.C
   virtual void setEnforceMassCharge(Int_t myval);
   virtual void MyLoop();
   virtual void MakeSignatureReport(Int_t inc_jet, Int_t inc_met);
   virtual void PrintDecayTree(Int_t ientry, Int_t levelMax);
   virtual void PrintDecayTree(Int_t levelMax);
   virtual void PrintMCPartOfType(Int_t PDGID);
   virtual void PrintParentChain(Int_t ntID);
   virtual void getVectorOfChildren( int parent_ntID, std::vector<int> &children_ntID);
   virtual void getVectorOfAllChildren( int parent_ntID, std::vector<int> &children_ntID);
   virtual void getVectorOfStableDescendants(int parent_ntID, std::vector<int> &stable_descendants_ntID);
   virtual void getVectorOfSignatureParts(int parent_ntID, std::vector<int> &stable_descendants_ntID);
   virtual void PrintSignatureParts(int parent_idx);
   virtual void PrintStableDescendants(int i_event, int parent_idx);
   virtual void PrintStableDescendants(int parent_idx);
   virtual void PrintChildren( int i_event, int parent_idx);
   virtual void PrintChildren( int parent_idx);
   virtual void getListOfPDG(int pdgID, std::vector<int> &nt_pdg_list);
   virtual void getListOfPDG_Parents(int pdgID, std::vector<int> &nt_pdg_list);
   virtual void getListOfPDG_abs(int pdgID, std::vector<int> &nt_pdg_list);
   virtual void getChainOfParents( int part_ntID, std::vector<int> &nt_parent_chain);
   virtual int getDirectParent( int ntID);
   virtual int isMCPartFromPDGID_abs(int mc_ntID, int PDGID);
   virtual int isMCPartFromPDGID(int mc_ntID, int PDGID);

   virtual int testMCParentChain(Int_t ntID, std::vector<Int_t> parent_chain);
   virtual int testMCAncestor(Int_t ntID, Int_t parent);
   virtual Double_t getDeltaPhi(Double_t x1, Double_t y1, Double_t x2, Double_t y2);
   virtual Double_t getDeltaPhi(std::pair<TString,Int_t> part1, std::pair<TString,Int_t> part2);
   virtual void getVectorOfDeltaPhi(TString type1, std::vector<Int_t> list1,
					TString type2, std::vector<Int_t> list2,
					std::vector<Double_t> &deltaPhi);
   virtual void getVectorOfDuplicateTracks(std::vector<int> &list);
   
      //Get mass and sum pt of a collection of particles
   virtual std::pair<Double_t,Double_t> getMass(std::vector< std::pair<TString,Int_t> > particles);
   //Get vector of pair diMass and sumPT 
   virtual std::pair<Double_t,Double_t> getWConstrainedMETZ(TLorentzVector lep4V, Double_t my_met, Double_t my_phi);
   virtual void getVectorOfDiMass( TString type1, std::vector<Int_t> list1,
				   TString type2, std::vector<Int_t> list2,
				   std::vector< std::pair<Double_t,Double_t> > &diMasses);
   virtual TLorentzVector get4Vector(TString type1, Int_t id);
   //get vector of pair TriMass and sumPT
   virtual void getVectorOfTriMass( TString type1, std::vector<Int_t> list1,
				    TString type2, std::vector<Int_t> list2,
				    TString type3, std::vector<Int_t> list3,
				    std::vector< std::pair<Double_t,Double_t> > &TriMasses);
   virtual void fillLeadAndNoLead(TString Type,std::vector<int> all, std::vector<int> &lead, std::vector<int> &nolead);
   virtual Int_t getClosestObject(TString type, Int_t id, TString test_type, std::vector<Int_t> test_ids, Double_t dR_max);
   virtual Int_t eidCut(TString cutType, Int_t ntID);
   virtual Double_t getJetDropHCalPt(Int_t ntID);
   virtual Double_t getJetDropECalPt(Int_t ntID);
   virtual Double_t getJetDropECalPtV02(Int_t ntID);
   virtual Double_t getJetPlusMuPt(Int_t ntID); 
   virtual Double_t getJetTestPt(Int_t ntID);
   virtual Double_t getJetLeadTrack(Int_t ntID);
   virtual Double_t getJetLeadTrackbyN(Int_t ntID);
   virtual Double_t getPiEcalResponseFrac(Double_t pt); 
   virtual Double_t getPiHcalResponseFrac(Double_t pt); 
   virtual Double_t getJetECalPlusMuPt(Int_t ntID);
   virtual Double_t getJetHCalPlusMuPt(Int_t ntID);
   virtual Int_t EIDRobustTight(Int_t ntID);
   virtual Int_t EIDWP80(Int_t ntID);
   virtual Int_t EIDWP90(Int_t ntID);
   virtual Int_t EIDWP90_NoPhoConv(Int_t ntID); 
   virtual Int_t EIDLoose(Int_t ntID);
   virtual Int_t PhotonID2012(Int_t ntID); //Photon 2012 Selection
   virtual Int_t EIDVeto2012(Int_t ntID); //2012 Electron Selection
   virtual Int_t EIDTight2012(Int_t ntID); //2012 Electron Selection
   virtual Int_t EIDMedium2012(Int_t ntID); //2012 Electron Selection
   virtual Int_t EIDLoose2012(Int_t ntID); //2012 Electron Selection    
   virtual Int_t MuIDTight2012(Int_t ntID); //2012 Muon Selection    
   virtual Int_t getElectronPhotonMatch(Int_t eID);
   virtual void dumpEventInfo();
   virtual Double_t getConversion_Dist(Int_t tid1, Int_t tid2);
   virtual Double_t getConversion_DCot(Int_t tid1, Int_t tid2);
   virtual void getConversion_Info(Int_t tid1, Int_t tid2, std::vector<Double_t> &answers);
   virtual void getMuonConversionInfo(Int_t muID, std::vector<Double_t> &answers);
   virtual void getElectronConversionInfo(Int_t muID, std::vector<Double_t> &answers);
   virtual void getTrackConversionInfo(Int_t muID, std::vector<Double_t> &answers);
   
   virtual void getWZCandidates(std::vector<std::pair<TString,Int_t> > leptons, std::vector<std::vector<std::pair<TString,Int_t> > > &zcand, std::vector<std::pair<TString,Int_t> > &wcand, std::vector<Double_t> &dymass,std::vector<Double_t> &wmass);
   //End of Rutgers added functions
   ClassDef(SkimTreeBase,1);
};

#endif

#ifdef SkimTreeBase_cxx

SkimTreeBase::SkimTreeBase(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("results_35_1_TFd.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("results_35_1_TFd.root");
      }
      f->GetObject("SkimTree",tree);

   }
   Init(tree);
}

SkimTreeBase::~SkimTreeBase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SkimTreeBase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SkimTreeBase::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SkimTreeBase::Init(TTree *tree)
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
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("pat_muon_n", &pat_muon_n, &b_pat_muon_n);
   fChain->SetBranchAddress("pat_muon_pt", pat_muon_pt, &b_pat_muon_pt);
   fChain->SetBranchAddress("pat_muon_et", pat_muon_et, &b_pat_muon_et);
   fChain->SetBranchAddress("pat_muon_px", pat_muon_px, &b_pat_muon_px);
   fChain->SetBranchAddress("pat_muon_py", pat_muon_py, &b_pat_muon_py);
   fChain->SetBranchAddress("pat_muon_pz", pat_muon_pz, &b_pat_muon_pz);
   fChain->SetBranchAddress("pat_muon_eta", pat_muon_eta, &b_pat_muon_eta);
   fChain->SetBranchAddress("pat_muon_phi", pat_muon_phi, &b_pat_muon_phi);
   fChain->SetBranchAddress("pat_muon_pmag", pat_muon_pmag, &b_pat_muon_pmag);
   fChain->SetBranchAddress("pat_muon_isPF", pat_muon_isPF, &b_pat_muon_isPF);
   fChain->SetBranchAddress("pat_muon_PFMatchPdgId", pat_muon_PFMatchPdgId, &b_pat_muon_PFMatchPdgId);
   fChain->SetBranchAddress("pat_muon_PFPAT_dpt", pat_muon_PFPAT_dpt, &b_pat_muon_PFPAT_dpt);
   fChain->SetBranchAddress("pat_muon_PFPAT_dphi", pat_muon_PFPAT_dphi, &b_pat_muon_PFPAT_dphi);
   fChain->SetBranchAddress("pat_muon_PFPAT_deta", pat_muon_PFPAT_deta, &b_pat_muon_PFPAT_deta);
   fChain->SetBranchAddress("pat_muon_PFPAT_dq", pat_muon_PFPAT_dq, &b_pat_muon_PFPAT_dq);
   fChain->SetBranchAddress("pat_muon_energy", pat_muon_energy, &b_pat_muon_energy);
   fChain->SetBranchAddress("pat_muon_charge", pat_muon_charge, &b_pat_muon_charge);
   fChain->SetBranchAddress("pat_muon_trackID", pat_muon_trackID, &b_pat_muon_trackID);
   fChain->SetBranchAddress("pat_muon_globalTrackID", pat_muon_globalTrackID, &b_pat_muon_globalTrackID);
   fChain->SetBranchAddress("pat_muon_muonTrackID", pat_muon_muonTrackID, &b_pat_muon_muonTrackID);
   fChain->SetBranchAddress("pat_muon_caloIso", pat_muon_caloIso, &b_pat_muon_caloIso);
   fChain->SetBranchAddress("pat_muon_ecaloIso", pat_muon_ecaloIso, &b_pat_muon_ecaloIso);
   fChain->SetBranchAddress("pat_muon_hcaloIso", pat_muon_hcaloIso, &b_pat_muon_hcaloIso);
   fChain->SetBranchAddress("pat_muon_trackIso", pat_muon_trackIso, &b_pat_muon_trackIso);
   fChain->SetBranchAddress("pat_muon_beta", pat_muon_beta, &b_pat_muon_beta);
   fChain->SetBranchAddress("pat_muon_PF_chargedHadronIso", pat_muon_PF_chargedHadronIso, &b_pat_muon_PF_chargedHadronIso);
   fChain->SetBranchAddress("pat_muon_PF_photonIso", pat_muon_PF_photonIso, &b_pat_muon_PF_photonIso);
   fChain->SetBranchAddress("pat_muon_PF_neutralHadronIso", pat_muon_PF_neutralHadronIso, &b_pat_muon_PF_neutralHadronIso);
   fChain->SetBranchAddress("pat_muon_allTrackIso", pat_muon_allTrackIso, &b_pat_muon_allTrackIso);
   fChain->SetBranchAddress("pat_muon_vertTrackIso", pat_muon_vertTrackIso, &b_pat_muon_vertTrackIso);
   fChain->SetBranchAddress("pat_muon_calEnergyEM", pat_muon_calEnergyEM, &b_pat_muon_calEnergyEM);
   fChain->SetBranchAddress("pat_muon_calEnergyHad", pat_muon_calEnergyHad, &b_pat_muon_calEnergyHad);
   fChain->SetBranchAddress("pat_muon_ecalIsoDep", pat_muon_ecalIsoDep, &b_pat_muon_ecalIsoDep);
   fChain->SetBranchAddress("pat_muon_hcalIsoDep", pat_muon_hcalIsoDep, &b_pat_muon_hcalIsoDep);
   fChain->SetBranchAddress("pat_muon_dRmin", pat_muon_dRmin, &b_pat_muon_dRmin);
   fChain->SetBranchAddress("pat_muon_dRmin_track_ntID", pat_muon_dRmin_track_ntID, &b_pat_muon_dRmin_track_ntID);
   fChain->SetBranchAddress("pat_muon_dRmin05", pat_muon_dRmin05, &b_pat_muon_dRmin05);
   fChain->SetBranchAddress("pat_muon_dRmin05_track_ntID", pat_muon_dRmin05_track_ntID, &b_pat_muon_dRmin05_track_ntID);
   fChain->SetBranchAddress("pat_muon_dRmin10", pat_muon_dRmin10, &b_pat_muon_dRmin10);
   fChain->SetBranchAddress("pat_muon_dRmin10_track_ntID", pat_muon_dRmin10_track_ntID, &b_pat_muon_dRmin10_track_ntID);
   fChain->SetBranchAddress("pat_muon_genLepton_dR", pat_muon_genLepton_dR, &b_pat_muon_genLepton_dR);
   fChain->SetBranchAddress("pat_muon_genLepton_pdgID", pat_muon_genLepton_pdgID, &b_pat_muon_genLepton_pdgID);
   fChain->SetBranchAddress("pat_muon_genLepton_ntID", pat_muon_genLepton_ntID, &b_pat_muon_genLepton_ntID);
   fChain->SetBranchAddress("pat_muon_genLepton_mother_pdgID", pat_muon_genLepton_mother_pdgID, &b_pat_muon_genLepton_mother_pdgID);
   fChain->SetBranchAddress("pat_muon_genLepton_mother_ntID", pat_muon_genLepton_mother_ntID, &b_pat_muon_genLepton_mother_ntID);
   fChain->SetBranchAddress("pat_muon_isGlobalMuon", pat_muon_isGlobalMuon, &b_pat_muon_isGlobalMuon);
   fChain->SetBranchAddress("pat_muon_isTrackerMuon", pat_muon_isTrackerMuon, &b_pat_muon_isTrackerMuon);
   fChain->SetBranchAddress("pat_muon_isStandAloneMuon", pat_muon_isStandAloneMuon, &b_pat_muon_isStandAloneMuon);
   fChain->SetBranchAddress("pat_muon_isCaloMuon", pat_muon_isCaloMuon, &b_pat_muon_isCaloMuon);
   fChain->SetBranchAddress("pat_muon_isGlobalMuonPromptTight", pat_muon_isGlobalMuonPromptTight, &b_pat_muon_isGlobalMuonPromptTight);
   fChain->SetBranchAddress("pat_muon_isTMLastStationTight", pat_muon_isTMLastStationTight, &b_pat_muon_isTMLastStationTight);
   fChain->SetBranchAddress("pat_muon_isTMLastStationAngTight", pat_muon_isTMLastStationAngTight, &b_pat_muon_isTMLastStationAngTight);
   fChain->SetBranchAddress("pat_muon_trigger_nfilter", pat_muon_trigger_nfilter, &b_pat_muon_trigger_nfilter);
   fChain->SetBranchAddress("pat_muon_trigger_objectType", pat_muon_trigger_objectType, &b_pat_muon_trigger_objectType);
   fChain->SetBranchAddress("pat_muon_trigger_objectID", pat_muon_trigger_objectID, &b_pat_muon_trigger_objectID);
   fChain->SetBranchAddress("pat_muon_segmentCompatibility", pat_muon_segmentCompatibility, &b_pat_muon_segmentCompatibility);
   fChain->SetBranchAddress("pat_muon_isCaloCompatibilityValid", pat_muon_isCaloCompatibilityValid, &b_pat_muon_isCaloCompatibilityValid);
   fChain->SetBranchAddress("pat_muon_caloCompatibility", pat_muon_caloCompatibility, &b_pat_muon_caloCompatibility);
   fChain->SetBranchAddress("pat_muon_numberOfMatches", pat_muon_numberOfMatches, &b_pat_muon_numberOfMatches);
   fChain->SetBranchAddress("pat_muon_Direction", pat_muon_Direction, &b_pat_muon_Direction);
   fChain->SetBranchAddress("pat_muon_cosmicCompatibility", pat_muon_cosmicCompatibility, &b_pat_muon_cosmicCompatibility);
   fChain->SetBranchAddress("pat_muon_timeCompatibility", pat_muon_timeCompatibility, &b_pat_muon_timeCompatibility);
   fChain->SetBranchAddress("pat_muon_backToBackCompatibility", pat_muon_backToBackCompatibility, &b_pat_muon_backToBackCompatibility);
   fChain->SetBranchAddress("pat_muon_overlapCompatibility", pat_muon_overlapCompatibility, &b_pat_muon_overlapCompatibility);
   fChain->SetBranchAddress("pat_muon_normalizedChi2", pat_muon_normalizedChi2, &b_pat_muon_normalizedChi2);
   fChain->SetBranchAddress("pat_muon_innerVertDz", pat_muon_innerVertDz, &b_pat_muon_innerVertDz);
   fChain->SetBranchAddress("pat_muon_innerVertDxy", pat_muon_innerVertDxy, &b_pat_muon_innerVertDxy);
   fChain->SetBranchAddress("pat_muon_innerNumberOfValidPixelHits", pat_muon_innerNumberOfValidPixelHits, &b_pat_muon_innerNumberOfValidPixelHits);


   fChain->SetBranchAddress("pat_electron_n", &pat_electron_n, &b_pat_electron_n);
   fChain->SetBranchAddress("pat_electron_pt", pat_electron_pt, &b_pat_electron_pt);
   fChain->SetBranchAddress("pat_electron_et", pat_electron_et, &b_pat_electron_et);
   fChain->SetBranchAddress("pat_electron_px", pat_electron_px, &b_pat_electron_px);
   fChain->SetBranchAddress("pat_electron_py", pat_electron_py, &b_pat_electron_py);
   fChain->SetBranchAddress("pat_electron_pz", pat_electron_pz, &b_pat_electron_pz);
   fChain->SetBranchAddress("pat_electron_pmag", pat_electron_pmag, &b_pat_electron_pmag);
   fChain->SetBranchAddress("pat_electron_eta", pat_electron_eta, &b_pat_electron_eta);
   fChain->SetBranchAddress("pat_electron_phi", pat_electron_phi, &b_pat_electron_phi);
   fChain->SetBranchAddress("pat_electron_isPF", pat_electron_isPF, &b_pat_electron_isPF);
   fChain->SetBranchAddress("pat_electron_conv_vtxProb", pat_electron_conv_vtxProb, &b_pat_electron_conv_vtxProb);
   fChain->SetBranchAddress("pat_electron_classification", pat_electron_classification, &b_pat_electron_classification);
   fChain->SetBranchAddress("pat_electron_PFMatchPdgId", pat_electron_PFMatchPdgId, &b_pat_electron_PFMatchPdgId);
   fChain->SetBranchAddress("pat_electron_PFPAT_dpt", pat_electron_PFPAT_dpt, &b_pat_electron_PFPAT_dpt);
   fChain->SetBranchAddress("pat_electron_PFPAT_dphi", pat_electron_PFPAT_dphi, &b_pat_electron_PFPAT_dphi);
   fChain->SetBranchAddress("pat_electron_PFPAT_deta", pat_electron_PFPAT_deta, &b_pat_electron_PFPAT_deta);
   fChain->SetBranchAddress("pat_electron_PFPAT_dq", pat_electron_PFPAT_dq, &b_pat_electron_PFPAT_dq);
   fChain->SetBranchAddress("pat_electron_energy", pat_electron_energy, &b_pat_electron_energy);
   fChain->SetBranchAddress("pat_electron_charge", pat_electron_charge, &b_pat_electron_charge);
   fChain->SetBranchAddress("pat_electron_trackID", pat_electron_trackID, &b_pat_electron_trackID);
   fChain->SetBranchAddress("pat_electron_caloIso", pat_electron_caloIso, &b_pat_electron_caloIso);
   fChain->SetBranchAddress("pat_electron_trackIso", pat_electron_trackIso, &b_pat_electron_trackIso);
   fChain->SetBranchAddress("pat_electron_dRmin", pat_electron_dRmin, &b_pat_electron_dRmin);
   fChain->SetBranchAddress("pat_electron_dRmin_track_ntID", pat_electron_dRmin_track_ntID, &b_pat_electron_dRmin_track_ntID);
   fChain->SetBranchAddress("pat_electron_genLepton_pdgID", pat_electron_genLepton_pdgID, &b_pat_electron_genLepton_pdgID);
   fChain->SetBranchAddress("pat_electron_genLepton_ntID", pat_electron_genLepton_ntID, &b_pat_electron_genLepton_ntID);
   fChain->SetBranchAddress("pat_electron_GsfCtfScPixChargeConsistent", pat_electron_GsfCtfScPixChargeConsistent, &b_pat_electron_GsfCtfScPixChargeConsistent);
   fChain->SetBranchAddress("pat_electron_GsfScPixChargeConsistent", pat_electron_GsfScPixChargeConsistent, &b_pat_electron_GsfScPixChargeConsistent);
   fChain->SetBranchAddress("pat_electron_GsfCtfChargeConsistent", pat_electron_GsfCtfChargeConsistent, &b_pat_electron_GsfCtfChargeConsistent);
   fChain->SetBranchAddress("pat_electron_eidTight", pat_electron_eidTight, &b_pat_electron_eidTight);
   fChain->SetBranchAddress("pat_electron_eidLoose", pat_electron_eidLoose, &b_pat_electron_eidLoose);
   fChain->SetBranchAddress("pat_electron_eidRobustTight", pat_electron_eidRobustTight, &b_pat_electron_eidRobustTight);
   fChain->SetBranchAddress("pat_electron_eidRobustLoose", pat_electron_eidRobustLoose, &b_pat_electron_eidRobustLoose);
   fChain->SetBranchAddress("pat_electron_eidRobustHighEnergy", pat_electron_eidRobustHighEnergy, &b_pat_electron_eidRobustHighEnergy);
   fChain->SetBranchAddress("pat_electron_ecaloIso", pat_electron_ecaloIso, &b_pat_electron_ecaloIso);
   fChain->SetBranchAddress("pat_electron_hcaloIso", pat_electron_hcaloIso, &b_pat_electron_hcaloIso);
   fChain->SetBranchAddress("pat_electron_PF_chargedHadronIso", pat_electron_PF_chargedHadronIso, &b_pat_electron_PF_chargedHadronIso);
   fChain->SetBranchAddress("pat_electron_PF_photonIso", pat_electron_PF_photonIso, &b_pat_electron_PF_photonIso);
   fChain->SetBranchAddress("pat_electron_PF_neutralHadronIso", pat_electron_PF_neutralHadronIso, &b_pat_electron_PF_neutralHadronIso);
   fChain->SetBranchAddress("pat_electron_PF_chargedHadronIso_04", pat_electron_PF_chargedHadronIso_04, &b_pat_electron_PF_chargedHadronIso_04);
   fChain->SetBranchAddress("pat_electron_PF_photonIso_04", pat_electron_PF_photonIso_04, &b_pat_electron_PF_photonIso_04);
   fChain->SetBranchAddress("pat_electron_PF_neutralHadronIso_04", pat_electron_PF_neutralHadronIso_04, &b_pat_electron_PF_neutralHadronIso_04);
   fChain->SetBranchAddress("pat_electron_classification_04", pat_electron_classification_04, &b_pat_electron_classification_04);
   fChain->SetBranchAddress("pat_electron_caloEnergy", pat_electron_caloEnergy, &b_pat_electron_caloEnergy);
   fChain->SetBranchAddress("pat_electron_hadOverEm", pat_electron_hadOverEm, &b_pat_electron_hadOverEm);
   fChain->SetBranchAddress("pat_electron_eOverPin", pat_electron_eOverPin, &b_pat_electron_eOverPin);
   fChain->SetBranchAddress("pat_electron_sigmaEtaEta", pat_electron_sigmaEtaEta, &b_pat_electron_sigmaEtaEta);
   fChain->SetBranchAddress("pat_electron_sigmaIetaIeta", pat_electron_sigmaIetaIeta, &b_pat_electron_sigmaIetaIeta);
   fChain->SetBranchAddress("pat_electron_e1x5", pat_electron_e1x5, &b_pat_electron_e1x5);
   fChain->SetBranchAddress("pat_electron_e2x5Max", pat_electron_e2x5Max, &b_pat_electron_e2x5Max);
   fChain->SetBranchAddress("pat_electron_e5x5", pat_electron_e5x5, &b_pat_electron_e5x5);
   fChain->SetBranchAddress("pat_electron_deltaPhi", pat_electron_deltaPhi, &b_pat_electron_deltaPhi);
   fChain->SetBranchAddress("pat_electron_deltaEta", pat_electron_deltaEta, &b_pat_electron_deltaEta);
   fChain->SetBranchAddress("pat_electron_status", pat_electron_status, &b_pat_electron_status);
   fChain->SetBranchAddress("pat_electron_trigger_nfilter", pat_electron_trigger_nfilter, &b_pat_electron_trigger_nfilter);
   fChain->SetBranchAddress("pat_electron_trigger_objectType", pat_electron_trigger_objectType, &b_pat_electron_trigger_objectType);
   fChain->SetBranchAddress("pat_electron_trigger_objectID", pat_electron_trigger_objectID, &b_pat_electron_trigger_objectID);
   fChain->SetBranchAddress("pat_electron_fbrem", pat_electron_fbrem, &b_pat_electron_fbrem);
   fChain->SetBranchAddress("pat_electron_ecalDriven", pat_electron_ecalDriven, &b_pat_electron_ecalDriven);
   fChain->SetBranchAddress("pat_electron_swissCross", pat_electron_swissCross, &b_pat_electron_swissCross);
   fChain->SetBranchAddress("pat_electron_eMax", pat_electron_eMax, &b_pat_electron_eMax);
   fChain->SetBranchAddress("pat_electron_IsConversion", pat_electron_IsConversion, &b_pat_electron_IsConversion);
   fChain->SetBranchAddress("pat_electron_ConversionDist", pat_electron_ConversionDist, &b_pat_electron_ConversionDist);
   fChain->SetBranchAddress("pat_electron_ConversionDCotTheta", pat_electron_ConversionDCotTheta, &b_pat_electron_ConversionDCotTheta);
   fChain->SetBranchAddress("pat_electron_NumberOfExpectedInnerHits", pat_electron_NumberOfExpectedInnerHits, &b_pat_electron_NumberOfExpectedInnerHits);
   fChain->SetBranchAddress("pat_electron_NumberOfLostInnerHits", pat_electron_NumberOfLostInnerHits, &b_pat_electron_NumberOfLostInnerHits);
   fChain->SetBranchAddress("pat_electron_eSeedClusterOverPout", pat_electron_eSeedClusterOverPout, &b_pat_electron_eSeedClusterOverPout);
   fChain->SetBranchAddress("pat_electron_fMVAVar_fbrem", pat_electron_fMVAVar_fbrem, &b_pat_electron_fMVAVar_fbrem);
   fChain->SetBranchAddress("pat_electron_fMVAVar_kfchi2", pat_electron_fMVAVar_kfchi2, &b_pat_electron_fMVAVar_kfchi2);
   fChain->SetBranchAddress("pat_electron_fMVAVar_kfhits", pat_electron_fMVAVar_kfhits, &b_pat_electron_fMVAVar_kfhits);
   fChain->SetBranchAddress("pat_electron_fMVAVar_gsfchi2", pat_electron_fMVAVar_gsfchi2, &b_pat_electron_fMVAVar_gsfchi2);
   fChain->SetBranchAddress("pat_electron_fMVAVar_deta", pat_electron_fMVAVar_deta, &b_pat_electron_fMVAVar_deta);
   fChain->SetBranchAddress("pat_electron_fMVAVar_dphi", pat_electron_fMVAVar_dphi, &b_pat_electron_fMVAVar_dphi);
   fChain->SetBranchAddress("pat_electron_fMVAVar_detacalo", pat_electron_fMVAVar_detacalo, &b_pat_electron_fMVAVar_detacalo);
   fChain->SetBranchAddress("pat_electron_fMVAVar_dphicalo", pat_electron_fMVAVar_dphicalo, &b_pat_electron_fMVAVar_dphicalo);
   fChain->SetBranchAddress("pat_electron_fMVAVar_see", pat_electron_fMVAVar_see, &b_pat_electron_fMVAVar_see);
   fChain->SetBranchAddress("pat_electron_fMVAVar_spp", pat_electron_fMVAVar_spp, &b_pat_electron_fMVAVar_spp);
   fChain->SetBranchAddress("pat_electron_fMVAVar_etawidth", pat_electron_fMVAVar_etawidth, &b_pat_electron_fMVAVar_etawidth);
   fChain->SetBranchAddress("pat_electron_fMVAVar_phiwidth", pat_electron_fMVAVar_phiwidth, &b_pat_electron_fMVAVar_phiwidth);
   fChain->SetBranchAddress("pat_electron_fMVAVar_e1x5e5x5", pat_electron_fMVAVar_e1x5e5x5, &b_pat_electron_fMVAVar_e1x5e5x5);
   fChain->SetBranchAddress("pat_electron_fMVAVar_R9", pat_electron_fMVAVar_R9, &b_pat_electron_fMVAVar_R9);
   fChain->SetBranchAddress("pat_electron_fMVAVar_nbrems", pat_electron_fMVAVar_nbrems, &b_pat_electron_fMVAVar_nbrems);
   fChain->SetBranchAddress("pat_electron_fMVAVar_HoE", pat_electron_fMVAVar_HoE, &b_pat_electron_fMVAVar_HoE);
   fChain->SetBranchAddress("pat_electron_fMVAVar_EoP", pat_electron_fMVAVar_EoP, &b_pat_electron_fMVAVar_EoP);
   fChain->SetBranchAddress("pat_electron_fMVAVar_IoEmIoP", pat_electron_fMVAVar_IoEmIoP, &b_pat_electron_fMVAVar_IoEmIoP);
   fChain->SetBranchAddress("pat_electron_fMVAVar_eleEoPout", pat_electron_fMVAVar_eleEoPout, &b_pat_electron_fMVAVar_eleEoPout);
   fChain->SetBranchAddress("pat_electron_fMVAVar_PreShowerOverRaw", pat_electron_fMVAVar_PreShowerOverRaw, &b_pat_electron_fMVAVar_PreShowerOverRaw);
   fChain->SetBranchAddress("pat_electron_fMVAVar_d0", pat_electron_fMVAVar_d0, &b_pat_electron_fMVAVar_d0);
   fChain->SetBranchAddress("pat_electron_fMVAVar_dz", pat_electron_fMVAVar_dz, &b_pat_electron_fMVAVar_dz);
   fChain->SetBranchAddress("pat_electron_fMVAVar_eta", pat_electron_fMVAVar_eta, &b_pat_electron_fMVAVar_eta);
   fChain->SetBranchAddress("pat_electron_fMVAVar_pt", pat_electron_fMVAVar_pt, &b_pat_electron_fMVAVar_pt);
   fChain->SetBranchAddress("pat_jet_n", &pat_jet_n, &b_pat_jet_n);
   fChain->SetBranchAddress("pat_rho", &pat_rho, &b_pat_rho);
   fChain->SetBranchAddress("pat_rho_neutral", &pat_rho_neutral, &b_pat_rho_neutral);
   fChain->SetBranchAddress("pat_jet_pt", pat_jet_pt, &b_pat_jet_pt);
   fChain->SetBranchAddress("pat_jet_et", pat_jet_et, &b_pat_jet_et);
   fChain->SetBranchAddress("pat_jet_raw_pt", pat_jet_raw_pt, &b_pat_jet_raw_pt);
   fChain->SetBranchAddress("pat_jet_raw_et", pat_jet_raw_et, &b_pat_jet_raw_et);
   fChain->SetBranchAddress("pat_jet_px", pat_jet_px, &b_pat_jet_px);
   fChain->SetBranchAddress("pat_jet_py", pat_jet_py, &b_pat_jet_py);
   fChain->SetBranchAddress("pat_jet_pz", pat_jet_pz, &b_pat_jet_pz);
   fChain->SetBranchAddress("pat_jet_pmag", pat_jet_pmag, &b_pat_jet_pmag);
   fChain->SetBranchAddress("pat_jet_uncertainty", pat_jet_uncertainty, &b_pat_jet_uncertainty);
   fChain->SetBranchAddress("pat_jet_eta", pat_jet_eta, &b_pat_jet_eta);
   fChain->SetBranchAddress("pat_jet_phi", pat_jet_phi, &b_pat_jet_phi);
   fChain->SetBranchAddress("pat_jet_energy", pat_jet_energy, &b_pat_jet_energy);
   fChain->SetBranchAddress("pat_jet_etaetaMoment", pat_jet_etaetaMoment, &b_pat_jet_etaetaMoment);
   fChain->SetBranchAddress("pat_jet_etaphiMoment", pat_jet_etaphiMoment, &b_pat_jet_etaphiMoment);
   fChain->SetBranchAddress("pat_jet_phiphiMoment", pat_jet_phiphiMoment, &b_pat_jet_phiphiMoment);
   fChain->SetBranchAddress("pat_jet_genParton_pdgID", pat_jet_genParton_pdgID, &b_pat_jet_genParton_pdgID);
   fChain->SetBranchAddress("pat_jet_genParton_ntID", pat_jet_genParton_ntID, &b_pat_jet_genParton_ntID);
   fChain->SetBranchAddress("pat_jet_bDiscriminator", pat_jet_bDiscriminator, &b_pat_jet_bDiscriminator);
   fChain->SetBranchAddress("pat_jet_bDiscriminator_ssVertex", pat_jet_bDiscriminator_ssVertex, &b_pat_jet_bDiscriminator_ssVertex);
   fChain->SetBranchAddress("pat_jet_bDiscriminator_ssVertexPure", pat_jet_bDiscriminator_ssVertexPure, &b_pat_jet_bDiscriminator_ssVertexPure);
   fChain->SetBranchAddress("pat_jet_bDiscriminator_combined", pat_jet_bDiscriminator_combined, &b_pat_jet_bDiscriminator_combined);
   fChain->SetBranchAddress("pat_jet_bDiscriminator_trackCount", pat_jet_bDiscriminator_trackCount, &b_pat_jet_bDiscriminator_trackCount);
   fChain->SetBranchAddress("pat_jet_bDiscriminator_trackCountPure", pat_jet_bDiscriminator_trackCountPure, &b_pat_jet_bDiscriminator_trackCountPure);
   fChain->SetBranchAddress("pat_jet_sumTrackPt", pat_jet_sumTrackPt, &b_pat_jet_sumTrackPt);
   fChain->SetBranchAddress("pat_jet_bDiscPositive", pat_jet_bDiscPositive, &b_pat_jet_bDiscPositive);
   fChain->SetBranchAddress("pat_jet_bDiscNegative", pat_jet_bDiscNegative, &b_pat_jet_bDiscNegative);
   fChain->SetBranchAddress("pat_jet_ntracks", pat_jet_ntracks, &b_pat_jet_ntracks);
   fChain->SetBranchAddress("pat_jet_ntracks_max", &pat_jet_ntracks_max, &b_pat_jet_ntracks_max);
   fChain->SetBranchAddress("pat_jet_trkIDs", pat_jet_trkIDs, &b_pat_jet_trkIDs);
   fChain->SetBranchAddress("pat_jet_emf", pat_jet_emf, &b_pat_jet_emf);
   fChain->SetBranchAddress("pat_jet_ehf", pat_jet_ehf, &b_pat_jet_ehf);
   fChain->SetBranchAddress("pat_jet_chargedHadronFraction", pat_jet_chargedHadronFraction, &b_pat_jet_chargedHadronFraction);
   fChain->SetBranchAddress("pat_jet_neutralHadronFraction", pat_jet_neutralHadronFraction, &b_pat_jet_neutralHadronFraction);
   fChain->SetBranchAddress("pat_jet_chargedEMFraction", pat_jet_chargedEMFraction, &b_pat_jet_chargedEMFraction);
   fChain->SetBranchAddress("pat_jet_neutralEMFraction", pat_jet_neutralEMFraction, &b_pat_jet_neutralEMFraction);
   fChain->SetBranchAddress("pat_jet_chargedHadronMultiplicity", pat_jet_chargedHadronMultiplicity, &b_pat_jet_chargedHadronMultiplicity);
   fChain->SetBranchAddress("pat_jet_numberConstituents", pat_jet_numberConstituents, &b_pat_jet_numberConstituents);

   fChain->SetBranchAddress("pat_jet_charge", pat_jet_charge, &b_pat_jet_charge);
   fChain->SetBranchAddress("pat_jet_mass", pat_jet_mass, &b_pat_jet_mass);
   fChain->SetBranchAddress("pat_jet_vx", pat_jet_vx, &b_pat_jet_vx);
   fChain->SetBranchAddress("pat_jet_vy", pat_jet_vy, &b_pat_jet_vy);
   fChain->SetBranchAddress("pat_jet_vz", pat_jet_vz, &b_pat_jet_vz);
   fChain->SetBranchAddress("pat_jet_isCalo", pat_jet_isCalo, &b_pat_jet_isCalo);
   fChain->SetBranchAddress("pat_jet_isPF", pat_jet_isPF, &b_pat_jet_isPF);
   fChain->SetBranchAddress("pat_jet_corrLevel", pat_jet_corrLevel, &b_pat_jet_corrLevel);
   fChain->SetBranchAddress("pat_jet_corr_glue", pat_jet_corr_glue, &b_pat_jet_corr_glue);
   fChain->SetBranchAddress("pat_jet_corr_uds", pat_jet_corr_uds, &b_pat_jet_corr_uds);
   fChain->SetBranchAddress("pat_jet_corr_c", pat_jet_corr_c, &b_pat_jet_corr_c);
   fChain->SetBranchAddress("pat_jet_corr_b", pat_jet_corr_b, &b_pat_jet_corr_b);
   fChain->SetBranchAddress("pat_jet_trigger_nfilter", pat_jet_trigger_nfilter, &b_pat_jet_trigger_nfilter);
   fChain->SetBranchAddress("pat_jet_trigger_objectType", pat_jet_trigger_objectType, &b_pat_jet_trigger_objectType);
   fChain->SetBranchAddress("pat_jet_trigger_objectID", pat_jet_trigger_objectID, &b_pat_jet_trigger_objectID);
   fChain->SetBranchAddress("pat_jet_loose_PFjetID", pat_jet_loose_PFjetID, &b_pat_jet_loose_PFjetID);
   fChain->SetBranchAddress("pat_jet_medium_PFjetID", pat_jet_medium_PFjetID, &b_pat_jet_medium_PFjetID);
   fChain->SetBranchAddress("pat_jet_tight_PFjetID", pat_jet_tight_PFjetID, &b_pat_jet_tight_PFjetID);
   fChain->SetBranchAddress("mc_pdfSetA_N", &mc_pdfSetA_N, &b_mc_pdfSetA_N);
   fChain->SetBranchAddress("mc_pdfSetA", mc_pdfSetA, &b_mc_pdfSetA);
   fChain->SetBranchAddress("mc_pdfSetB_N", &mc_pdfSetB_N, &b_mc_pdfSetB_N);
   fChain->SetBranchAddress("mc_pdfSetB", mc_pdfSetB, &b_mc_pdfSetB);
   fChain->SetBranchAddress("mc_pdfSetC_N", &mc_pdfSetC_N, &b_mc_pdfSetC_N);
   fChain->SetBranchAddress("mc_pdfSetC", mc_pdfSetC, &b_mc_pdfSetC);
   fChain->SetBranchAddress("mc_signature_nJets", &mc_signature_nJets, &b_mc_signature_nJets);
   fChain->SetBranchAddress("mc_signature_nbJets", &mc_signature_nbJets, &b_mc_signature_nbJets);
   fChain->SetBranchAddress("mc_signature_nPhotons", &mc_signature_nPhotons, &b_mc_signature_nPhotons);
   fChain->SetBranchAddress("mc_signature_nMuons", &mc_signature_nMuons, &b_mc_signature_nMuons);
   fChain->SetBranchAddress("mc_signature_charge_Muons", &mc_signature_charge_Muons, &b_mc_signature_charge_Muons);
   fChain->SetBranchAddress("mc_signature_nElectrons", &mc_signature_nElectrons, &b_mc_signature_nElectrons);
   fChain->SetBranchAddress("mc_signature_charge_Electrons", &mc_signature_charge_Electrons, &b_mc_signature_Electrons);
   fChain->SetBranchAddress("mc_signature_nTaus", &mc_signature_nTaus, &b_mc_signature_nTaus);
   fChain->SetBranchAddress("mc_signature_charge_Taus", &mc_signature_charge_Taus, &b_mc_signature_charge_Taus);
   fChain->SetBranchAddress("mc_signature_met", &mc_signature_met, &b_mc_signature_met);
   fChain->SetBranchAddress("mc_susyscan_vars", mc_susyscan_vars, &b_mc_susyscan_vars);
   fChain->SetBranchAddress("mc_part_n", &mc_part_n, &b_mc_part_n);
   fChain->SetBranchAddress("mc_part_pdgID", &mc_part_pdgID, &b_mc_part_pdgID);
   fChain->SetBranchAddress("mc_part_mass", &mc_part_mass, &b_mc_part_mass);
   fChain->SetBranchAddress("mc_part_pt", &mc_part_pt, &b_mc_part_pt);
   fChain->SetBranchAddress("mc_part_et", &mc_part_et, &b_mc_part_et);
   fChain->SetBranchAddress("mc_part_vx", &mc_part_vx, &b_mc_part_vx);
   fChain->SetBranchAddress("mc_part_vy", &mc_part_vy, &b_mc_part_vy);
   fChain->SetBranchAddress("mc_part_vz", &mc_part_vz, &b_mc_part_vz);
   fChain->SetBranchAddress("mc_part_charge", &mc_part_charge, &b_mc_part_charge);
   fChain->SetBranchAddress("mc_part_px", &mc_part_px, &b_mc_part_px);
   fChain->SetBranchAddress("mc_part_py", &mc_part_py, &b_mc_part_py);
   fChain->SetBranchAddress("mc_part_pz", &mc_part_pz, &b_mc_part_pz);
   fChain->SetBranchAddress("mc_part_pmag", &mc_part_pmag, &b_mc_part_pmag);
   fChain->SetBranchAddress("mc_part_eta", &mc_part_eta, &b_mc_part_eta);
   fChain->SetBranchAddress("mc_part_phi", &mc_part_phi, &b_mc_part_phi);
   fChain->SetBranchAddress("mc_part_energy", &mc_part_energy, &b_mc_part_energy);
   fChain->SetBranchAddress("mc_part_status", &mc_part_status, &b_mc_part_status);
   fChain->SetBranchAddress("mc_part_barcode", &mc_part_barcode, &b_mc_part_barcode);
   fChain->SetBranchAddress("mc_part_mother_pdgID", &mc_part_mother_pdgID, &b_mc_part_mother_pdgID);
   fChain->SetBranchAddress("mc_part_mother_ntID", &mc_part_mother_ntID, &b_mc_part_mother_ntID);
   fChain->SetBranchAddress("mc_part_n_children", &mc_part_n_children, &b_mc_part_n_children);
   fChain->SetBranchAddress("reco_beamHalo_EventSmellsLikeHalo", &reco_beamHalo_EventSmellsLikeHalo, &b_reco_beamHalo_EventSmellsLikeHalo);
   fChain->SetBranchAddress("reco_beamHalo_CSCTightHaloId", &reco_beamHalo_CSCTightHaloId, &b_reco_beamHalo_CSCTightHaloId);
   fChain->SetBranchAddress("reco_beamHalo_CSCLooseHaloId", &reco_beamHalo_CSCLooseHaloId, &b_reco_beamHalo_CSCLooseHaloId);
   fChain->SetBranchAddress("reco_beamHalo_nCSChaloTriggers", &reco_beamHalo_nCSChaloTriggers, &b_reco_beamHalo_nCSChaloTriggers);
   fChain->SetBranchAddress("reco_beamHalo_nCSChaloTracks", &reco_beamHalo_nCSChaloTracks, &b_reco_beamHalo_nCSChaloTracks);
   fChain->SetBranchAddress("reco_beamHalo_nCSCoutOfTimeTriggers", &reco_beamHalo_nCSCoutOfTimeTriggers, &b_reco_beamHalo_nCSCoutOfTimeTriggers);
   fChain->SetBranchAddress("reco_beamSpot_x", &reco_beamSpot_x, &b_reco_beamSpot_x);
   fChain->SetBranchAddress("reco_beamSpot_y", &reco_beamSpot_y, &b_reco_beamSpot_y);
   fChain->SetBranchAddress("reco_beamSpot_z", &reco_beamSpot_z, &b_reco_beamSpot_z);
   fChain->SetBranchAddress("reco_beamSpot_ex", &reco_beamSpot_ex, &b_reco_beamSpot_ex);
   fChain->SetBranchAddress("reco_beamSpot_ey", &reco_beamSpot_ey, &b_reco_beamSpot_ey);
   fChain->SetBranchAddress("reco_beamSpot_ez", &reco_beamSpot_ez, &b_reco_beamSpot_ez);
   fChain->SetBranchAddress("reco_beamSpot_sigmaz", &reco_beamSpot_sigmaz, &b_reco_beamSpot_sigmaz);
   fChain->SetBranchAddress("reco_beamSpot_dxdz", &reco_beamSpot_dxdz, &b_reco_beamSpot_dxdz);
   fChain->SetBranchAddress("reco_beamSpot_width", &reco_beamSpot_width, &b_reco_beamSpot_width);
   fChain->SetBranchAddress("reco_track_n", &reco_track_n, &b_reco_track_n);
   fChain->SetBranchAddress("reco_track_genParticle_dR", reco_track_genParticle_dR, &b_reco_track_genParticle_dR);
   fChain->SetBranchAddress("reco_track_genParticle_pdgID", reco_track_genParticle_pdgID, &b_reco_track_genParticle_pdgID);
   fChain->SetBranchAddress("reco_track_genParticle_ntID", reco_track_genParticle_ntID, &b_reco_track_genParticle_ntID);
   fChain->SetBranchAddress("reco_track_genParticle_mother_pdgID", reco_track_genParticle_mother_pdgID, &b_reco_track_genParticle_mother_pdgID);
   fChain->SetBranchAddress("reco_track_genParticle_mother_ntID", reco_track_genParticle_mother_ntID, &b_reco_track_genParticle_mother_ntID);
   fChain->SetBranchAddress("reco_track_nValidHits", reco_track_nValidHits, &b_reco_track_nValidHits);
   fChain->SetBranchAddress("reco_track_ntrackerLayersWM", reco_track_ntrackerLayersWM, &b_reco_track_ntrackerLayersWM);
   fChain->SetBranchAddress("reco_track_npixelLayersWM", reco_track_npixelLayersWM, &b_reco_track_npixelLayersWM);
   fChain->SetBranchAddress("reco_track_nstripLayersWM", reco_track_nstripLayersWM, &b_reco_track_nstripLayersWM);
   fChain->SetBranchAddress("reco_track_muonStationsWVH", reco_track_muonStationsWVH, &b_reco_track_muonStationsWVH);
   fChain->SetBranchAddress("reco_track_muonStationsWAH", reco_track_muonStationsWAH, &b_reco_track_muonStationsWAH);
   fChain->SetBranchAddress("reco_track_nBadMuonHits", reco_track_nBadMuonHits, &b_reco_track_nBadMuonHits);
   fChain->SetBranchAddress("reco_track_outermostMuonStationWithValidHits", reco_track_outermostMuonStationWithValidHits, &b_reco_track_outermostMuonStationWithValidHits);
   fChain->SetBranchAddress("reco_track_nValidMuonHitsInFirstStation", reco_track_nValidMuonHitsInFirstStation, &b_reco_track_nValidMuonHitsInFirstStation);
   fChain->SetBranchAddress("reco_track_nLostMuonHitsInFirstStation", reco_track_nLostMuonHitsInFirstStation, &b_reco_track_nLostMuonHitsInFirstStation);
   fChain->SetBranchAddress("reco_track_nBadMuonHitsInFirstStation", reco_track_nBadMuonHitsInFirstStation, &b_reco_track_nBadMuonHitsInFirstStation);
   fChain->SetBranchAddress("reco_track_nAnyMuonHitsInFirstStation", reco_track_nAnyMuonHitsInFirstStation, &b_reco_track_nAnyMuonHitsInFirstStation);
   fChain->SetBranchAddress("reco_track_nValidTrackerHits", reco_track_nValidTrackerHits, &b_reco_track_nValidTrackerHits);
   fChain->SetBranchAddress("reco_track_nValidMuonHits", reco_track_nValidMuonHits, &b_reco_track_nValidMuonHits);
   fChain->SetBranchAddress("reco_track_nValidPixelHits", reco_track_nValidPixelHits, &b_reco_track_nValidPixelHits);
   fChain->SetBranchAddress("reco_track_nLostHits", reco_track_nLostHits, &b_reco_track_nLostHits);
   fChain->SetBranchAddress("reco_track_nLostTrackerHits", reco_track_nLostTrackerHits, &b_reco_track_nLostTrackerHits);
   fChain->SetBranchAddress("reco_track_nLostMuonHits", reco_track_nLostMuonHits, &b_reco_track_nLostMuonHits);
   fChain->SetBranchAddress("reco_track_nLostPixelHits", reco_track_nLostPixelHits, &b_reco_track_nLostPixelHits);
   fChain->SetBranchAddress("reco_track_isGlobal", reco_track_isGlobal, &b_reco_track_isGlobal);
   fChain->SetBranchAddress("reco_track_isMuon", reco_track_isMuon, &b_reco_track_isMuon);
   fChain->SetBranchAddress("reco_track_isTracker", reco_track_isTracker, &b_reco_track_isTracker);
   fChain->SetBranchAddress("reco_track_pt", reco_track_pt, &b_reco_track_pt);
   fChain->SetBranchAddress("reco_track_px", reco_track_px, &b_reco_track_px);
   fChain->SetBranchAddress("reco_track_py", reco_track_py, &b_reco_track_py);
   fChain->SetBranchAddress("reco_track_pz", reco_track_pz, &b_reco_track_pz);
   fChain->SetBranchAddress("reco_track_vx", reco_track_vx, &b_reco_track_vx);
   fChain->SetBranchAddress("reco_track_vy", reco_track_vy, &b_reco_track_vy);
   fChain->SetBranchAddress("reco_track_vz", reco_track_vz, &b_reco_track_vz);
   fChain->SetBranchAddress("reco_track_chi2", reco_track_chi2, &b_reco_track_chi2);
   fChain->SetBranchAddress("reco_track_ndof", reco_track_ndof, &b_reco_track_ndof);
   fChain->SetBranchAddress("reco_track_charge", reco_track_charge, &b_reco_track_charge);
   fChain->SetBranchAddress("reco_track_dxy", reco_track_dxy, &b_reco_track_dxy);
   fChain->SetBranchAddress("reco_track_dsz", reco_track_dsz, &b_reco_track_dsz);
   fChain->SetBranchAddress("reco_track_d0", reco_track_d0, &b_reco_track_d0);
   fChain->SetBranchAddress("reco_track_dz", reco_track_dz, &b_reco_track_dz);
   fChain->SetBranchAddress("reco_track_vert_dxy", reco_track_vert_dxy, &b_reco_track_vert_dxy);
   fChain->SetBranchAddress("reco_track_vert_dz", reco_track_vert_dz, &b_reco_track_vert_dz);
   fChain->SetBranchAddress("reco_track_beam_dxy", reco_track_beam_dxy, &b_reco_track_beam_dxy);
   fChain->SetBranchAddress("reco_track_beam_dsz", reco_track_beam_dsz, &b_reco_track_beam_dsz);
   fChain->SetBranchAddress("reco_track_beam_d0", reco_track_beam_d0, &b_reco_track_beam_d0);
   fChain->SetBranchAddress("reco_track_beam_dz", reco_track_beam_dz, &b_reco_track_beam_dz);
   fChain->SetBranchAddress("reco_track_phi", reco_track_phi, &b_reco_track_phi);
   fChain->SetBranchAddress("reco_track_eta", reco_track_eta, &b_reco_track_eta);
   fChain->SetBranchAddress("reco_track_theta", reco_track_theta, &b_reco_track_theta);
   fChain->SetBranchAddress("reco_track_dxyError", reco_track_dxyError, &b_reco_track_dxyError);
   fChain->SetBranchAddress("reco_track_d0Error", reco_track_d0Error, &b_reco_track_d0Error);
   fChain->SetBranchAddress("reco_track_dzError", reco_track_dzError, &b_reco_track_dzError);
   fChain->SetBranchAddress("reco_track_phiError", reco_track_phiError, &b_reco_track_phiError);
   fChain->SetBranchAddress("reco_track_etaError", reco_track_etaError, &b_reco_track_etaError);
   fChain->SetBranchAddress("reco_track_thetaError", reco_track_thetaError, &b_reco_track_thetaError);
   fChain->SetBranchAddress("reco_track_lambdaError", reco_track_lambdaError, &b_reco_track_lambdaError);
   fChain->SetBranchAddress("reco_track_trackIso", reco_track_trackIso, &b_reco_track_trackIso);
   fChain->SetBranchAddress("reco_track_caloIso", reco_track_caloIso, &b_reco_track_caloIso);
   fChain->SetBranchAddress("reco_track_trackIso1", reco_track_trackIso1, &b_reco_track_trackIso1);
   fChain->SetBranchAddress("reco_track_caloIso1", reco_track_caloIso1, &b_reco_track_caloIso1);
   fChain->SetBranchAddress("reco_track_trackIso2", reco_track_trackIso2, &b_reco_track_trackIso2);
   fChain->SetBranchAddress("reco_track_caloIso2", reco_track_caloIso2, &b_reco_track_caloIso2);
   fChain->SetBranchAddress("reco_track_trackIso6", reco_track_trackIso6, &b_reco_track_trackIso6);
   fChain->SetBranchAddress("reco_track_caloIso6", reco_track_caloIso6, &b_reco_track_caloIso6);
   fChain->SetBranchAddress("reco_track_trackIso9", reco_track_trackIso9, &b_reco_track_trackIso9);
   fChain->SetBranchAddress("reco_track_caloIso9", reco_track_caloIso9, &b_reco_track_caloIso9);
   fChain->SetBranchAddress("reco_track_trackIso12", reco_track_trackIso12, &b_reco_track_trackIso12);
   fChain->SetBranchAddress("reco_track_caloIso12", reco_track_caloIso12, &b_reco_track_caloIso12);
   fChain->SetBranchAddress("reco_track_ecaloIso", reco_track_ecaloIso, &b_reco_track_ecaloIso);
   fChain->SetBranchAddress("reco_track_hcaloIso", reco_track_hcaloIso, &b_reco_track_hcaloIso);
   fChain->SetBranchAddress("reco_track_vertWeight", reco_track_vertWeight, &b_reco_track_vertWeight);
   fChain->SetBranchAddress("reco_track_PF_chargedHadronIso", reco_track_PF_chargedHadronIso, &b_reco_track_PF_chargedHadronIso);
   fChain->SetBranchAddress("reco_track_PF_photonIso", reco_track_PF_photonIso, &b_reco_track_PF_photonIso);
   fChain->SetBranchAddress("reco_track_PF_neutralHadronIso", reco_track_PF_neutralHadronIso, &b_reco_track_PF_neutralHadronIso);
   fChain->SetBranchAddress("reco_vertex_n", &reco_vertex_n, &b_reco_vertex_n);
   fChain->SetBranchAddress("reco_vertex_ntrack", reco_vertex_ntrack, &b_reco_vertex_ntrack);
   fChain->SetBranchAddress("reco_vertex_x", reco_vertex_x, &b_reco_vertex_x);
   fChain->SetBranchAddress("reco_vertex_y", reco_vertex_y, &b_reco_vertex_y);
   fChain->SetBranchAddress("reco_vertex_z", reco_vertex_z, &b_reco_vertex_z);
   fChain->SetBranchAddress("reco_vertex_ex", reco_vertex_ex, &b_reco_vertex_ex);
   fChain->SetBranchAddress("reco_vertex_ey", reco_vertex_ey, &b_reco_vertex_ey);
   fChain->SetBranchAddress("reco_vertex_ez", reco_vertex_ez, &b_reco_vertex_ez);
   fChain->SetBranchAddress("reco_vertex_ndof", reco_vertex_ndof, &b_reco_vertex_ndof);
   fChain->SetBranchAddress("reco_vertex_chi2", reco_vertex_chi2, &b_reco_vertex_chi2);
   fChain->SetBranchAddress("reco_vertex_wSumPt", reco_vertex_wSumPt, &b_reco_vertex_wSumPt);
   fChain->SetBranchAddress("pat_met_sumEt", &pat_met_sumEt, &b_pat_met_sumEt);
   fChain->SetBranchAddress("pat_met_mEtSig", &pat_met_mEtSig, &b_pat_met_mEtSig);
   fChain->SetBranchAddress("pat_met_gen_sumEt", &pat_met_gen_sumEt, &b_pat_met_gen_sumEt);
   fChain->SetBranchAddress("pat_met_px", &pat_met_px, &b_pat_met_px);
   fChain->SetBranchAddress("pat_met_py", &pat_met_py, &b_pat_met_py);
   fChain->SetBranchAddress("pat_met_pz", &pat_met_pz, &b_pat_met_pz);
   fChain->SetBranchAddress("pat_met_pt", &pat_met_pt, &b_pat_met_pt);
   fChain->SetBranchAddress("pat_met_eta", &pat_met_eta, &b_pat_met_eta);
   fChain->SetBranchAddress("pat_met_phi", &pat_met_phi, &b_pat_met_phi);
   fChain->SetBranchAddress("pat_met_trigger_nfilter", &pat_met_trigger_nfilter, &b_pat_met_trigger_nfilter);
   fChain->SetBranchAddress("pat_met_trigger_objectType", pat_met_trigger_objectType, &b_pat_met_trigger_objectType);
   fChain->SetBranchAddress("pat_met_trigger_objectID", pat_met_trigger_objectID, &b_pat_met_trigger_objectID);
   fChain->SetBranchAddress("pf_met_sumEt", &pf_met_sumEt, &b_pf_met_sumEt);
   fChain->SetBranchAddress("pf_met_pt", &pf_met_pt, &b_pf_met_pt);
   fChain->SetBranchAddress("pf_met_phi", &pf_met_phi, &b_pf_met_phi);
   fChain->SetBranchAddress("pf_met_type1_sumEt", &pf_met_type1_sumEt, &b_pf_met_type1_sumEt);
   fChain->SetBranchAddress("pf_met_type1_pt", &pf_met_type1_pt, &b_pf_met_type1_pt);
   fChain->SetBranchAddress("pf_met_type1_phi", &pf_met_type1_phi, &b_pf_met_type1_phi);
   fChain->SetBranchAddress("tc_met_sumEt", &tc_met_sumEt, &b_tc_met_sumEt);
   fChain->SetBranchAddress("tc_met_pt", &tc_met_pt, &b_tc_met_pt);
   fChain->SetBranchAddress("tc_met_phi", &tc_met_phi, &b_tc_met_phi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("isRealData", &isRealData, &b_isRealData);
   fChain->SetBranchAddress("bunchCrossing", &bunchCrossing, &b_bunchCrossing);
   fChain->SetBranchAddress("storeNumber", &storeNumber, &b_storeNumber);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain->SetBranchAddress("pileup_trueNumInteractions", &pileup_trueNumInteractions, &b_pileup_trueNumInteractions);
   fChain->SetBranchAddress("pileup_numInteractions", &pileup_numInteractions, &b_pileup_numInteractions);
   fChain->SetBranchAddress("pileup_bunchCrossing", &pileup_bunchCrossing, &b_pileup_bunchCrossing);
   fChain->SetBranchAddress("event_mc_processID", &event_mc_processID, &b_event_mc_processID);
   fChain->SetBranchAddress("event_mc_sigma_input", &event_mc_sigma_input, &b_event_mc_sigma_input);
   fChain->SetBranchAddress("event_mc_sigma_calc", &event_mc_sigma_calc, &b_event_mc_sigma_calc);
   fChain->SetBranchAddress("event_mc_eff_input", &event_mc_eff_input, &b_event_mc_eff_input);
   fChain->SetBranchAddress("pat_tau_n", &pat_tau_n, &b_pat_tau_n);
   fChain->SetBranchAddress("pat_tau_pt", pat_tau_pt, &b_pat_tau_pt);
   fChain->SetBranchAddress("pat_tau_px", pat_tau_px, &b_pat_tau_px);
   fChain->SetBranchAddress("pat_tau_py", pat_tau_py, &b_pat_tau_py);
   fChain->SetBranchAddress("pat_tau_pz", pat_tau_pz, &b_pat_tau_pz);
   fChain->SetBranchAddress("pat_tau_pmag", pat_tau_pmag, &b_pat_tau_pmag);
   fChain->SetBranchAddress("pat_tau_eta", pat_tau_eta, &b_pat_tau_eta);
   fChain->SetBranchAddress("pat_tau_emFraction", pat_tau_emFraction, &b_pat_tau_emFraction);
   fChain->SetBranchAddress("pat_tau_phi", pat_tau_phi, &b_pat_tau_phi);
   fChain->SetBranchAddress("pat_tau_trackIso", pat_tau_trackIso, &b_pat_tau_trackIso);
   fChain->SetBranchAddress("pat_tau_caloIso", pat_tau_caloIso, &b_pat_tau_caloIso);
   fChain->SetBranchAddress("pat_tau_genLepton_pdgID", pat_tau_genLepton_pdgID, &b_pat_tau_genLepton_pdgID);
   fChain->SetBranchAddress("pat_tau_genLepton_ntID", pat_tau_genLepton_ntID, &b_pat_tau_genLepton_ntID);
   fChain->SetBranchAddress("pat_tau_signalTracksInvMass", pat_tau_signalTracksInvMass, &b_pat_tau_signalTracksInvMass);
   fChain->SetBranchAddress("pat_tau_isCalo", pat_tau_isCalo, &b_pat_tau_isCalo);
   fChain->SetBranchAddress("pat_tau_isPF", pat_tau_isPF, &b_pat_tau_isPF);
   fChain->SetBranchAddress("pat_tau_leadTrack_ntID", pat_tau_leadTrack_ntID, &b_pat_tau_leadTrack_ntID);
   fChain->SetBranchAddress("pat_tau_signalTracks_n", pat_tau_signalTracks_n, &b_pat_tau_signalTracks_n);
   fChain->SetBranchAddress("pat_tau_signalTracks_ntIDs", pat_tau_signalTracks_ntIDs, &b_pat_tau_signalTracks_ntIDs);
   fChain->SetBranchAddress("pat_tau_isoTracks_n", pat_tau_isoTracks_n, &b_pat_tau_isoTracks_n);
   fChain->SetBranchAddress("pat_tau_isoTracks_ntIDs", pat_tau_isoTracks_ntIDs, &b_pat_tau_isoTracks_ntIDs);
   fChain->SetBranchAddress("pat_tau_calo_leadTracksignedSipt", pat_tau_calo_leadTracksignedSipt, &b_pat_tau_calo_leadTracksignedSipt);
   fChain->SetBranchAddress("pat_tau_calo_isoChargedPtSum", pat_tau_calo_isoChargedPtSum, &b_pat_tau_calo_isoChargedPtSum);
   fChain->SetBranchAddress("pat_tau_calo_isoECALEtSum", pat_tau_calo_isoECALEtSum, &b_pat_tau_calo_isoECALEtSum);
   fChain->SetBranchAddress("pat_tau_calo_maxHCALhitEt", pat_tau_calo_maxHCALhitEt, &b_pat_tau_calo_maxHCALhitEt);
   fChain->SetBranchAddress("pat_tau_PF_leadTracksignedSipt", pat_tau_PF_leadTracksignedSipt, &b_pat_tau_PF_leadTracksignedSipt);
   fChain->SetBranchAddress("pat_tau_PF_isoChargedPtSum", pat_tau_PF_isoChargedPtSum, &b_pat_tau_PF_isoChargedPtSum);
   fChain->SetBranchAddress("pat_tau_PF_isoGammaEtSum", pat_tau_PF_isoGammaEtSum, &b_pat_tau_PF_isoGammaEtSum);
   fChain->SetBranchAddress("pat_tau_PF_isoSumPt", pat_tau_PF_isoSumPt, &b_pat_tau_PF_isoSumPt);
   fChain->SetBranchAddress("pat_tau_PF_maxHCALhitEt", pat_tau_PF_maxHCALhitEt, &b_pat_tau_PF_maxHCALhitEt);
   fChain->SetBranchAddress("pat_tau_PF_chargedHadronIso03", pat_tau_PF_chargedHadronIso03, &b_pat_tau_PF_chargedHadronIso03);
   fChain->SetBranchAddress("pat_tau_PF_neutralHadronIso03", pat_tau_PF_neutralHadronIso03, &b_pat_tau_PF_neutralHadronIso03);
   fChain->SetBranchAddress("pat_tau_PF_photonIso03", pat_tau_PF_photonIso03, &b_pat_tau_PF_photonIso03);
   fChain->SetBranchAddress("pat_tau_PF_chargedHadronIso05", pat_tau_PF_chargedHadronIso05, &b_pat_tau_PF_chargedHadronIso05);
   fChain->SetBranchAddress("pat_tau_PF_neutralHadronIso05", pat_tau_PF_neutralHadronIso05, &b_pat_tau_PF_neutralHadronIso05);
   fChain->SetBranchAddress("pat_tau_PF_photonIso05", pat_tau_PF_photonIso05, &b_pat_tau_PF_photonIso05);
   fChain->SetBranchAddress("pat_tau_PF_isoChargedCandMaxPt", pat_tau_PF_isoChargedCandMaxPt, &b_pat_tau_PF_isoChargedCandMaxPt);
   fChain->SetBranchAddress("pat_tau_PF_isoGammaCandMaxPt", pat_tau_PF_isoGammaCandMaxPt, &b_pat_tau_PF_isoGammaCandMaxPt);
   fChain->SetBranchAddress("pat_tau_PF_isoKlongCandMaxPt", pat_tau_PF_isoKlongCandMaxPt, &b_pat_tau_PF_isoKlongCandMaxPt);
   fChain->SetBranchAddress("pat_tau_PF_NsigCharged", pat_tau_PF_NsigCharged, &b_pat_tau_PF_NsigCharged);
   fChain->SetBranchAddress("pat_tau_PF_NsigGamma", pat_tau_PF_NsigGamma, &b_pat_tau_PF_NsigGamma);
   fChain->SetBranchAddress("pat_tau_PF_signalMass", pat_tau_PF_signalMass, &b_pat_tau_PF_signalMass);
   fChain->SetBranchAddress("pat_tau_PF_signalCharge", pat_tau_PF_signalCharge, &b_pat_tau_PF_signalCharge);
   fChain->SetBranchAddress("pat_tau_PF_againstMuon", pat_tau_PF_againstMuon, &b_pat_tau_PF_againstMuon);
   fChain->SetBranchAddress("pat_tau_PF_againstElectron", pat_tau_PF_againstElectron, &b_pat_tau_PF_againstElectron);
   fChain->SetBranchAddress("pat_tau_PF_Discriminants", pat_tau_PF_Discriminants, &b_pat_tau_PF_Discriminants);
   fChain->SetBranchAddress("pat_tau_trigger_nfilter", pat_tau_trigger_nfilter, &b_pat_tau_trigger_nfilter);
   fChain->SetBranchAddress("pat_tau_trigger_objectType", pat_tau_trigger_objectType, &b_pat_tau_trigger_objectType);
   fChain->SetBranchAddress("pat_tau_trigger_objectID", pat_tau_trigger_objectID, &b_pat_tau_trigger_objectID);
   fChain->SetBranchAddress("pat_photon_n", &pat_photon_n, &b_pat_photon_n);
   fChain->SetBranchAddress("pat_photon_pt", pat_photon_pt, &b_pat_photon_pt);
   fChain->SetBranchAddress("pat_photon_px", pat_photon_px, &b_pat_photon_px);
   fChain->SetBranchAddress("pat_photon_py", pat_photon_py, &b_pat_photon_py);
   fChain->SetBranchAddress("pat_photon_pz", pat_photon_pz, &b_pat_photon_pz);
   fChain->SetBranchAddress("pat_photon_eta", pat_photon_eta, &b_pat_photon_eta);
   fChain->SetBranchAddress("pat_photon_phi", pat_photon_phi, &b_pat_photon_phi);
   fChain->SetBranchAddress("pat_photon_pmag", pat_photon_pmag, &b_pat_photon_pmag);
   fChain->SetBranchAddress("pat_photon_trackIso", pat_photon_trackIso, &b_pat_photon_trackIso);
   fChain->SetBranchAddress("pat_photon_caloIso", pat_photon_caloIso, &b_pat_photon_caloIso);
   fChain->SetBranchAddress("pat_photon_genPhoton_pdgID", pat_photon_genPhoton_pdgID, &b_pat_photon_genPhoton_pdgID);
   fChain->SetBranchAddress("pat_photon_genPhoton_ntID", pat_photon_genPhoton_ntID, &b_pat_photon_genPhoton_ntID);
   fChain->SetBranchAddress("pat_photon_trigger_nfilter", pat_photon_trigger_nfilter, &b_pat_photon_trigger_nfilter);
   fChain->SetBranchAddress("pat_photon_trigger_objectType", pat_photon_trigger_objectType, &b_pat_photon_trigger_objectType);
   fChain->SetBranchAddress("pat_photon_trigger_objectID", pat_photon_trigger_objectID, &b_pat_photon_trigger_objectID);
   fChain->SetBranchAddress("pat_photon_hadOverEm", pat_photon_hadOverEm, &b_pat_photon_hadOverEm);
   fChain->SetBranchAddress("pat_photon_hadTowOverEm", pat_photon_hadTowOverEm, &b_pat_photon_hadTowOverEm);
   fChain->SetBranchAddress("pat_photon_conversionSafeElectronVeto", pat_photon_conversionSafeElectronVeto, &b_pat_photon_conversionSafeElectronVeto);
   fChain->SetBranchAddress("pat_photon_sigmaIetaIeta", pat_photon_sigmaIetaIeta, &b_pat_photon_sigmaIetaIeta);
   fChain->SetBranchAddress("pat_photon_endcap", pat_photon_endcap, &b_pat_photon_endcap);
   fChain->SetBranchAddress("pat_photon_barrel", pat_photon_barrel, &b_pat_photon_barrel);
   fChain->SetBranchAddress("pat_photon_scEt", pat_photon_scEt, &b_pat_photon_scEt);
   fChain->SetBranchAddress("pat_photon_isLoose", pat_photon_isLoose, &b_pat_photon_isLoose);
   fChain->SetBranchAddress("pat_photon_isTight", pat_photon_isTight, &b_pat_photon_isTight);
   fChain->SetBranchAddress("pat_photon_ecalRecHitEtR03", pat_photon_ecalRecHitEtR03, &b_pat_photon_ecalRecHitEtR03);
   fChain->SetBranchAddress("pat_photon_hcalTowerEtR03", pat_photon_hcalTowerEtR03, &b_pat_photon_hcalTowerEtR03);
   fChain->SetBranchAddress("pat_photon_hcalDepth1TowerEtR03", pat_photon_hcalDepth1TowerEtR03, &b_pat_photon_hcalDepth1TowerEtR03);
   fChain->SetBranchAddress("pat_photon_hcalDepth2TowerEtR03", pat_photon_hcalDepth2TowerEtR03, &b_pat_photon_hcalDepth2TowerEtR03);
   fChain->SetBranchAddress("pat_photon_ecalRecHitEtR04", pat_photon_ecalRecHitEtR04, &b_pat_photon_ecalRecHitEtR04);
   fChain->SetBranchAddress("pat_photon_hcalTowerEtR04", pat_photon_hcalTowerEtR04, &b_pat_photon_hcalTowerEtR04);
   fChain->SetBranchAddress("pat_photon_hcalDepth1TowerEtR04", pat_photon_hcalDepth1TowerEtR04, &b_pat_photon_hcalDepth1TowerEtR04);
   fChain->SetBranchAddress("pat_photon_hcalDepth2TowerEtR04", pat_photon_hcalDepth2TowerEtR04, &b_pat_photon_hcalDepth2TowerEtR04);
   fChain->SetBranchAddress("pat_photon_trackSumPtHollowR03", pat_photon_trackSumPtHollowR03, &b_pat_photon_trackSumPtHollowR03);
   fChain->SetBranchAddress("pat_photon_trackSumPtHollowR04", pat_photon_trackSumPtHollowR04, &b_pat_photon_trackSumPtHollowR04);
   fChain->SetBranchAddress("pat_photon_trackSumPtSolidR03", pat_photon_trackSumPtSolidR03, &b_pat_photon_trackSumPtSolidR03);
   fChain->SetBranchAddress("pat_photon_trackSumPtSolidR04", pat_photon_trackSumPtSolidR04, &b_pat_photon_trackSumPtSolidR04);
   fChain->SetBranchAddress("pat_photon_mustacheEt", pat_photon_mustacheEt, &b_pat_photon_mustacheEt);
   fChain->SetBranchAddress("pat_photon_MVAGlobalCorrEError", pat_photon_MVAGlobalCorrEError, &b_pat_photon_MVAGlobalCorrEError);
   fChain->SetBranchAddress("pat_photon_MVAGlobalCorrE", pat_photon_MVAGlobalCorrE, &b_pat_photon_MVAGlobalCorrE);
   fChain->SetBranchAddress("pat_photon_PFPhotonRes", pat_photon_PFPhotonRes, &b_pat_photon_PFPhotonRes);
   fChain->SetBranchAddress("pat_photon_chargedHadronIso", pat_photon_chargedHadronIso, &b_pat_photon_chargedHadronIso);
   fChain->SetBranchAddress("pat_photon_neutralHadronIso", pat_photon_neutralHadronIso, &b_pat_photon_neutralHadronIso);
   fChain->SetBranchAddress("pat_photon_photonIso", pat_photon_photonIso, &b_pat_photon_photonIso);
   fChain->SetBranchAddress("pat_photon_r9", pat_photon_r9, &b_pat_photon_r9);
   fChain->SetBranchAddress("pat_photon_EOut", pat_photon_EOut, &b_pat_photon_EOut);
   fChain->SetBranchAddress("pat_photon_track_nHollowR03", pat_photon_track_nHollowR03, &b_pat_photon_track_nHollowR03);
   fChain->SetBranchAddress("pat_photon_track_nHollowR04", pat_photon_track_nHollowR04, &b_pat_photon_track_nHollowR04);
   fChain->SetBranchAddress("pat_photon_track_nSolidR03", pat_photon_track_nSolidR03, &b_pat_photon_track_nSolidR03);
   fChain->SetBranchAddress("pat_photon_track_nSolidR04", pat_photon_track_nSolidR04, &b_pat_photon_track_nSolidR04);
   fChain->SetBranchAddress("hlt_triggers_npassed", &hlt_triggers_npassed, &b_hlt_triggers_npassed);
   fChain->SetBranchAddress("hlt_triggers", hlt_triggers, &b_hlt_triggers);
   fChain->SetBranchAddress("hlt_triggers_id", hlt_triggers_id, &b_hlt_triggers_id);
   fChain->SetBranchAddress("hlt_triggers_prescale", hlt_triggers_prescale, &b_hlt_triggers_prescale);
   fChain->SetBranchAddress("hlt_triggers_prescale_L1", hlt_triggers_prescale_L1, &b_hlt_triggers_prescale_L1);
   fChain->SetBranchAddress("hlt_triggers_prescale_HLT", hlt_triggers_prescale_HLT, &b_hlt_triggers_prescale_HLT);
   fChain->SetBranchAddress("hlt_triggers_wasrun", hlt_triggers_wasrun, &b_hlt_triggers_wasrun);
   fChain->SetBranchAddress("primaryVertexFilter", &primaryVertexFilter,&b_primaryVertexFilter);
   fChain->SetBranchAddress("noScrapingFilter", &noScrapingFilter,&b_noScrapingFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter,&b_HBHENoiseFilter);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter,&b_CSCTightHaloFilter);
   fChain->SetBranchAddress("hcalLaserEventFilter", &hcalLaserEventFilter,&b_hcalLaserEventFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter,&b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("trackingFailureFilter", &trackingFailureFilter,&b_trackingFailureFilter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter,&b_eeBadScFilter);


   Notify();
}

Bool_t SkimTreeBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SkimTreeBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
//Int_t SkimTreeBase::Cut(Long64_t entry)
//{
//// This function may be called from Loop.
//// returns  1 if entry is accepted.
//// returns -1 otherwise.
//   return 1;
//}

//==================Some Rutgers Functions=========================================
void SkimTreeBase::InitializeData()
{
  m_enforce_mass_charge=1;
  m_randomGenerator = new TRandom3(65539);
}
//==================End of Some Rutgers Functions=================================

#endif // #ifdef SkimTreeBase_cxx
