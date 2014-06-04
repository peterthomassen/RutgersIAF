//////////////////////////////////////////////////////
//                                                  //
// This Class produces a theory mini TTree          //
//                                                  //
// Written by: Emmanuel Contreras-Campana and       //
//             Christian Contreras-Campana          //
//                                                  //
// Date: 05-26-2014                                 //
//                                                  //
//////////////////////////////////////////////////////

#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TLorentzVector.h>

#include "RutgersIAF2012/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF2012/EventAnalyzer/interface/BaseTreeReader.h"
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"
#include "RutgersIAF2012/EventAnalyzer/interface/TheoryTreeWriter.h"

using namespace std;

ClassImp(TheoryTreeWriter)

TheoryTreeWriter::TheoryTreeWriter(BaseHandler* handler, TString treename)
: BaseTreeWriter(handler, treename)
{
  // Initialize the ID Codes for the theory Ntuple
  m_theoryID_photon = 0.0;
  m_theoryID_electron = 1.0;
  m_theoryID_muon = 2.0;
  m_theoryID_tau_isotrack = 3.0;
  m_theoryID_tau_1prongpi0s = 3.1;
  m_theoryID_jet = 4.0;
  m_theoryID_pfmet = 6.0;
  m_theoryID_tcmet = 6.2;
  m_theoryID_calomet = 6.1;
  m_theoryID_st = 7.0;
  m_theoryID_lt = 8.0;
  m_theoryID_ht = 9.0;
  m_theoryID_dymass = 10.0;
  m_theoryID_wtmass = 11.0;

  // Initialize any variables that you want to. This is your constructor
  m_debug = 0;

  nobject = 0;
  weight = 1.0;

  m_object = new TClonesArray("TLorentzVector");

  m_object_type = new vector<double>;
  m_object_btag = new vector<double>;
  m_object_dum1 = new vector<double>;
  m_object_dum2 = new vector<double>;
  m_object_dum3 = new vector<double>;
  m_object_dum4 = new vector<double>;
  m_object_dum5 = new vector<double>;
  m_object_dum6 = new vector<double>;
  m_object_dum7 = new vector<double>;
  m_object_dum8 = new vector<double>;
  m_object_scalar = new vector<double>;
  m_evtnum = new vector<double>;

  m_tree->Branch("weight", &weight,"weight/D");
  m_tree->Branch("object", "TClonesArray",&m_object, 32000, 0);
  m_tree->Branch("nobject",&nobject,"nobject/I");
  m_tree->Branch("object_type", "vector<double>",&m_object_type);
  m_tree->Branch("object_btag","vector<double>",&m_object_btag);
  m_tree->Branch("object_dum1","vector<double>",&m_object_dum1);
  m_tree->Branch("object_dum2","vector<double>",&m_object_dum2);
  m_tree->Branch("object_dum3","vector<double>",&m_object_dum3);
  m_tree->Branch("object_dum4","vector<double>",&m_object_dum4);
  m_tree->Branch("object_dum5","vector<double>",&m_object_dum5);
  m_tree->Branch("object_dum6","vector<double>",&m_object_dum6);
  m_tree->Branch("object_dum7","vector<double>",&m_object_dum7);
  m_tree->Branch("object_dum8","vector<double>",&m_object_dum8);
  m_tree->Branch("object_scalar","vector<double>",&m_object_scalar);
  m_tree->Branch("eventnum","vector<double>",&m_evtnum);
}

TheoryTreeWriter::~TheoryTreeWriter()
{
  delete m_object;
  delete m_object_type;
  delete m_object_btag;
  delete m_object_dum1;
  delete m_object_dum2;
  delete m_object_dum3;
  delete m_object_dum4;
  delete m_object_dum5;
  delete m_object_dum6;
  delete m_object_dum7;
  delete m_object_dum8;
  delete m_object_scalar;
  delete m_evtnum;
}

void TheoryTreeWriter::addEvtNum(double run, double evt, double lumi)
{
  m_evtnum->push_back(run);
  m_evtnum->push_back(evt);
  m_evtnum->push_back(lumi);

  if (m_debug==1) {
    std::cout<<"EvtNum added successfully"<<std::endl;
  }
}

void TheoryTreeWriter::addMET(double type, double pt, double phi)
{
  double e = pt;
  double px = pt*cos(phi);
  double py = pt*sin(phi);
  double pz = 0;

  Double_t btag = 0;
  Double_t dum = 0;
  Double_t scalar = 0;

  TLorentzVector fourvec(px,py,pz,e);

  addObject(fourvec,type,btag,dum,dum,dum,dum,dum,dum,dum,dum,scalar);

  if (m_debug==1) {
    std::cout<<"MET added successfully"<<std::endl;
  }
}

void TheoryTreeWriter::addScalar(double type, double value)
{
  Double_t dum = -999.0;

  addObject(TLorentzVector(0,0,0,0),type,0,dum,dum,dum,dum,dum,dum,dum,dum,value);
}

void TheoryTreeWriter::addObject(TLorentzVector fourvec, double type, double btag)
{
  Double_t dum = -999.0;

  addObject(fourvec,type,btag,dum,dum,dum,dum,dum,dum,dum,dum);
}

void TheoryTreeWriter::addObject(TLorentzVector fourvec, double type, double btag, double dum1, double dum2, double dum3, double dum4, double dum5, double dum6, double dum7, double dum8)
{
  addObject(fourvec,type,btag,dum1,dum2,dum3,dum4,dum5,dum6,dum7,dum8,-999);
}

void TheoryTreeWriter::addObject(TLorentzVector fourvec, double type, double btag, double dum1, double dum2, double dum3, double dum4, double dum5, double dum6, double dum7, double dum8, double scalar)
{
  m_object_type->push_back(type);
  m_object_btag->push_back(btag);
  m_object_dum1->push_back(dum1);
  m_object_dum2->push_back(dum2);
  m_object_dum3->push_back(dum3);
  m_object_dum4->push_back(dum4);
  m_object_dum5->push_back(dum5);
  m_object_dum6->push_back(dum6);
  m_object_dum7->push_back(dum7);
  m_object_dum8->push_back(dum8);
  m_object_scalar->push_back(scalar);

  new ((*m_object)[nobject]) TLorentzVector(fourvec);

  ++nobject;
  
  if (m_debug==1) {
    std::cout<<"Object added successfully"<<std::endl;
  }
}

void TheoryTreeWriter::fillTree()
{
  Int_t run = 0, lumiBlock = 0;
  long event = 0;

  Double_t pf_met_pt = 0.0, pf_met_phi = 0.0;
  Double_t tc_met_pt = 0.0, tc_met_phi = 0.0;
  Double_t pat_met_pt = 0.0, pat_met_phi = 0.0;

  Double_t st = 0.0, lt = 0.0, ht = 0.0;

  bool hasRun = m_handler->getVariable("RUN",run);
  bool hasLumi = m_handler->getVariable("LUMI",lumiBlock);
  bool hasEvent = m_handler->getVariable("EVENT",event);

  bool hasPFMET =  m_handler->getVariable("PF_PT",pf_met_pt);
  bool hasPFMETPhi =  m_handler->getVariable("PF_PHI",pf_met_phi);

  bool hasTCMET =  m_handler->getVariable("TC_PT",tc_met_pt);
  bool hasTCMETPhi =  m_handler->getVariable("TC_PT",tc_met_phi);

  bool hasCaloMET =  m_handler->getVariable("PAT_PT",pat_met_pt);
  bool hasCaloMETPhi =  m_handler->getVariable("PAT_PT",pat_met_phi);

  bool hasST =  m_handler->getVariable("ST",st);
  bool hasLT =  m_handler->getVariable("LT",lt);
  bool hasHT =  m_handler->getVariable("HT",ht);

  weight = m_handler->getPhysicsWeight();

  // Add run, event, and lumi number
  if (hasRun && hasLumi && hasEvent) {
    addEvtNum(run,event,lumiBlock);
  }

  // Add PF MET
  if (hasPFMET && hasPFMETPhi) {
    addMET(m_theoryID_pfmet,pf_met_pt,pf_met_phi);
  }

  // Add TC MET
  if (hasTCMET && hasTCMETPhi) {
    addMET(m_theoryID_tcmet,tc_met_pt,tc_met_phi);
  }

  // Add Calo MET
  if (hasCaloMET && hasCaloMETPhi) {
    addMET(m_theoryID_calomet,pat_met_pt,pat_met_phi);
  }

  // Add ST
  if (hasST) {
    addScalar(m_theoryID_st,st);
  }

  // Add LT
  if (hasLT) {
    addScalar(m_theoryID_lt,lt);
  }

  // Add HT
  if (hasHT) {
    addScalar(m_theoryID_ht,ht);
  }

  // Add DY and W transverse mass
  Double_t mll = 0.0, mt = 0.0;

  bool hasMLL = m_handler->getVariable("MLL",mll);
  bool hasMT = m_handler->getVariable("MT",mt);

  if (hasMLL) {
     addScalar(m_theoryID_dymass, mll);
  }

  if (hasMT) {
    addScalar(m_theoryID_wtmass, mt);
  }

  // Add Muons
  vector<SignatureObject*> goodMuons = m_handler->getProduct("goodMuons");

  for (Int_t i = 0; i < (Int_t)goodMuons.size(); ++i) {
    double type = -999.0;
    double btag = -999.0;
    double muon_charge = -999.0;

    TLorentzVector muon = TLorentzVector(*goodMuons[i]);

    bool hasCharge = goodMuons[i]->getVariable("CHARGE",muon_charge);

    if (hasCharge) {
      type = -m_theoryID_muon*muon_charge;
    }

    addObject(muon,type,btag);
  }

  // Add Electrons
  vector<SignatureObject*> goodElectrons = m_handler->getProduct("goodElectrons");

  for (Int_t i = 0; i < (Int_t)goodElectrons.size(); ++i) {
    double type = -999.0;
    double btag = -999.0;
    double electron_charge = -999.0;

    TLorentzVector electron = TLorentzVector(*goodElectrons[i]);

    bool hasCharge = goodElectrons[i]->getVariable("CHARGE",electron_charge);

    if (hasCharge) {
      type = -m_theoryID_electron*electron_charge;
    }

    addObject(electron,type,btag);
  }

  // Add PF Taus
  vector<SignatureObject*> goodTaus = m_handler->getProduct("goodTaus");

  for (Int_t i = 0; i < (Int_t)goodTaus.size(); ++i) {
    double type = m_theoryID_tau_1prongpi0s;
    double btag = -999.0;

    Double_t tau_energy = sqrt((goodTaus[i]->Px(),2)+(goodTaus[i]->Py(),2)+(goodTaus[i]->Pz(),2)+pow(1.777,2)); // M_tau = 1.777 GeV

    TLorentzVector tau(goodTaus[i]->Px(),goodTaus[i]->Py(),goodTaus[i]->Pz(),tau_energy);

    addObject(tau,type,btag);
  }

  // Add Isolated Tracks
  vector<SignatureObject*> goodTracks = m_handler->getProduct("goodTracks");

  for (Int_t i = 0; i < (Int_t)goodTracks.size(); ++i) {
    double type = -999.0;
    double btag = -999.0;
    double track_charge = -999.0;

    Double_t track_energy = sqrt(pow(goodTracks[i]->Pt(),2)+pow(goodTracks[i]->Pz(),2)+pow(0.14,2));  // M_pion = 0.140 GeV

    TLorentzVector track(goodTracks[i]->Px(),goodTracks[i]->Py(),goodTracks[i]->Pz(),track_energy);

    bool hasCharge = goodTracks[i]->getVariable("CHARGE",track_charge);

    if (hasCharge) {
      type = -m_theoryID_tau_isotrack*track_charge;
    }

    addObject(track,type,btag);
  }

  // Add Photons
  vector<SignatureObject*> goodPhotons = m_handler->getProduct("goodPhotons");

  for (Int_t i = 0; i < (Int_t)goodPhotons.size(); ++i) {
    double type = m_theoryID_photon;
    double btag = -999.0;

    TLorentzVector photon = TLorentzVector(*goodPhotons[i]);

    addObject(photon,type,btag);
  }

  // Add Jets
  vector<SignatureObject*> goodJets = m_handler->getProduct("goodJets");

  for (Int_t i = 0; i < (Int_t)goodJets.size(); ++i) {
    double type = m_theoryID_jet;
    double btag = -999.0;

    TLorentzVector jet = TLorentzVector(*goodJets[i]);

    bool check_btag = false;

    goodJets[i]->getVariable("BJET_CSVM",check_btag);

    if (check_btag) {
       btag = 1.0;
    }

    else if (!check_btag) {
       btag = 0.0;
    }

    addObject(jet,type,btag);
  }

  m_tree->Fill();

  if (m_debug==1) {
    std::cout << "Event " << event << " Filled" <<std::endl;
  }

  nobject = 0;

  m_object_type->clear();
  m_object_btag->clear();
  m_object_dum1->clear();
  m_object_dum2->clear();
  m_object_dum3->clear();
  m_object_dum4->clear();
  m_object_dum5->clear();
  m_object_dum6->clear();
  m_object_dum7->clear();
  m_object_dum8->clear();
  m_object_scalar->clear();
  m_evtnum->clear();

  m_object->Clear();
}

void TheoryTreeWriter::finish()
{
  m_tree->Print();

  std::cout<<"About to write theory ntuple to file"<<std::endl;
  m_handler->getOutFile()->cd();
  m_tree->Write();
}
