#define DelphesTreeBase_cxx
#include "RutgersIAF/RootC/interface/DelphesTreeBase.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

/*
This class is based on a template created by TTree::MakeClass on the 2012 ntuples.

Search for "Rutgers" to find changes.
*/

//Rutgers
#include <vector>
#include <iostream>
#include <sstream> 
using namespace std;
ClassImp(DelphesTreeBase)


DelphesTreeBase::DelphesTreeBase(TTree* anatree)
{
  //assert(anatree->GetEntries() == gentree->GetEntries());
  anaTree_ = anatree;
  //genTree_ = gentree;

  jets_ = 0;
  electrons_ = 0;
  muons_ = 0;
  taus_ = 0;
  photons_ = 0;
  tracks_ = 0;
  towers_ = 0;
  met_ = 0;
  ht_ = 0;
  events_ = 0;
  mcparticles_ = 0;

  nTracks_ = 0;
  nTowers_ = 0;
  nTaus_ = 0;

  anaTree_->SetBranchAddress("Event",&events_);
  anaTree_->SetBranchAddress("Particle",&mcparticles_);
  anaTree_->SetBranchAddress("Particle_size",&nParticles_);

  anaTree_->SetBranchAddress("Jet",&jets_);
  anaTree_->SetBranchAddress("Electron",&electrons_);
  anaTree_->SetBranchAddress("Muon",&muons_);
  anaTree_->SetBranchAddress("Photon",&photons_);
  //anaTree_->SetBranchAddress("EFlowTrack",&tracks_);
  anaTree_->SetBranchAddress("MissingET",&met_);
  anaTree_->SetBranchAddress("ScalarHT",&ht_);

  anaTree_->SetBranchAddress("Jet_size",&nJets_);
  anaTree_->SetBranchAddress("Electron_size",&nElectrons_);
  anaTree_->SetBranchAddress("Muon_size",&nMuons_);
  anaTree_->SetBranchAddress("Photon_size",&nPhotons_);
  //anaTree_->SetBranchAddress("EFlowTrack_size",&nTracks_);
  //anaTree_->SetBranchAddress("EFlowTower_size",&nTowers_);
  //anaTree_->SetBranchAddress("TauJet",&taus_);
  //anaTree_->SetBranchAddress("CaloTower",&towers_);
  //anaTree_->SetBranchAddress("TauJet_size",&nTaus_);



}
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
DelphesTreeBase::~DelphesTreeBase()
{
  /* no op */
}
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
void DelphesTreeBase::Show(Long64_t entry)
{
  if(!anaTree_ )return;
  //genTree_->Show(entry);
  anaTree_->Show(entry);
}
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
Int_t DelphesTreeBase::GetEntry(Long64_t entry)
{
  if(!anaTree_) return 0;
  int a = anaTree_->GetEntry(entry);
  //int g = genTree_-GetEntry(entry);
  return a;
}
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-=-=-

