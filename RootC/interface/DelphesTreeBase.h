//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun  6 06:54:13 2012 by ROOT version 5.32/00
// from TTree SkimTree/PAT information from CMS MC
// found on file: results_35_1_TFd.root
//////////////////////////////////////////////////////////

#ifndef DelphesTreeBase_h
#define DelphesTreeBase_h

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
#include "RutgersIAF/RootC/interface/DelphesClasses.h"
#include <TClonesArray.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class DelphesTreeBase : virtual public TObject {
 public :
  TTree* anaTree_;
  //TTree* genTree_;

  DelphesTreeBase(TTree* anaTree);
  virtual ~DelphesTreeBase();
  virtual Int_t GetEntry(Long64_t entry);
  virtual void Show(Long64_t entry = -1);
  
  TClonesArray* jets_;
  TClonesArray* electrons_;
  TClonesArray* muons_;
  TClonesArray* taus_;
  TClonesArray* photons_;
  TClonesArray* tracks_;
  TClonesArray* towers_;
  TClonesArray* met_;
  TClonesArray* ht_;
  
  TClonesArray* events_;
  TClonesArray* mcparticles_;
  
  long event;

  int nJets_;
  int nElectrons_;
  int nMuons_;
  int nTaus_;
  int nPhotons_;
  int nTracks_;
  int nTowers_;
  int nParticles_;
  
  
  //Rutgers
  enum PDG { PDG_muon=13, PDG_munu=14, PDG_b=5, PDG_t=6, 
	     PDG_electron=11, PDG_tau=15, PDG_enu=12, PDG_W=24, 
	     PDG_N2=1000023, PDG_C1=1000024, PDG_C0=1000022};
  
  ClassDef(DelphesTreeBase,1);
};

#endif

