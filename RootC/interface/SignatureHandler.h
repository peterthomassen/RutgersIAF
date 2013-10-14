//////////////////////////////////////////////////////
//
//  This Class Inherits from SkimTreeBase and lets you 
//  Use all of the SkimTree functionality without actually
//  looking through the mass of code
//
//////////////////////////////////////////////////////

#ifndef SignatureHandler_h
#define SignatureHandler_h


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <exception>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TF1.h>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <map>
#include <algorithm>
//#include "EGamma/EGammaAnalysisTools/interface/EGammaMvaEleEstimator.h"
#include "RutgersIAF2012/RootC/interface/SkimTreeBase.h"
#include "RutgersIAF2012/RootC/interface/Signature.h"
//#include "RutgersIAF2012/RootC/interface/SignatureWithBjets.h"
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/VertexCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureBeamSpot.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectPhoton.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureRecoVertex.h"
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureTrigger.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH3F.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"
#include <TLorentzVector.h>

class Signature;
class SignatureWithBjets;

class SignatureHandler: public BaseHandler, public SkimTreeBase {
 public:
  //default constructor
  SignatureHandler(TTree *tree=0,TString ofname="SigHanOutput.root");
  //virtual destructor
  virtual ~SignatureHandler();

  ////////////////    
  //Manage Event//
  ////////////////
  void eventLoop();
  void eventLoop(int runOnly, long int eventOnly);
  int getRun(){ return run;}
  int getLumiBlock(){ return lumiBlock;}
  long int getEvent() {return event;}

  /////////////////////
  //Manage Signatures//
  /////////////////////
  void addSignature(const char*, const char*);
  void addSignature(Signature* sig) {m_Signatures.push_back(sig);}
  void addBjetSignature(SignatureWithBjets* sig){m_bjetSignatures.push_back(sig);}
  void addBjetSignature(Signature* sig, int low, int high);
  void addBjetSignature(const char*, const char*,int,int);
  Signature* getSignature(int i) {return m_Signatures[i];}
  std::vector<Signature*> getSignatures() {return m_Signatures;}

  void addPreCutSignature(const char*, const char*);
  void addPreCutSignature(Signature* sig){m_preHandlerCutSignatures.push_back(sig);}
  Signature* getPreCutSignature(int i){return m_Signatures[i];}
  std::vector<Signature*> getPreCutSignatures(){return m_preHandlerCutSignatures;}


  void setDebugMode(bool c=true){m_debugMode = c;}
  bool getDebugMode(){return m_debugMode;}
  void printDebugInfo();
  void setJetCorrectionMode(int c){m_jetCorrMode = c;}
  void setElectronUncertaintyMode(int c){m_electronUncertaintyMode = c;}
  void setMuonUncertaintyMode(int c){m_muonUncertaintyMode = c;}

  void initSignatures();
  void finishSignatures();
  void setDoPriorityList(bool c=true){m_doPriorityList = c;}
  void addHistogram(SignatureTH1F*);
  void addHistogram(SignatureTH2F*);
  void addHistogram(SignatureTH3F*);
  void addHistogram(SignatureTH1F*, TString signatureRegExp);
  void addHistogram(SignatureTH2F*, TString signatureRegExp);
  void addHistogram(SignatureTH3F*, TString signatureRegExp);
  void addBasicHistograms();
  void addChargeSignHistograms();
  void setIsMC(bool c=true){m_isMC = c;}
  void addPUFile(TString);
  void setBTagForReweight(TString c){m_bTagForReweight = c;}

  void readGoodRunLumi(TString c);
  void readGoodRunLumiFromJSON(TString JSONFile, bool debug = false);
  void printRunLumiJSON();
  bool passFilter(TString c);

  //////////////////////////
  //Manage Physics Objects//
  //////////////////////////
  void addMuonCut(ObjectCut* cut){addProductCut("goodMuons",cut);}
  void addElectronCut(ObjectCut* cut){addProductCut("goodElectrons",cut);}
  void addTauCut(ObjectCut* cut){addProductCut("goodTaus",cut);}
  void addPhotonCut(ObjectCut* cut){addProductCut("goodPhotons",cut);}
  void addJetCut(ObjectCut* cut){addProductCut("goodJets",cut);}
  void addIsotrackCut(ObjectCut* cut){addProductCut("goodIsoTracks",cut);}
  void addMcParticleCut(ObjectCut* cut){addProductCut("goodMcParticles",cut);}

  void addRecoVertexCut(VertexCut* cut){m_recovertexCuts.push_back(cut);}
  void addHandlerCut(SignatureCut* cut){m_handlerCuts.push_back(cut);}

  void readObjectLists();
  void resetObjectLists();
  void applyObjectCuts();
  void applyObjectSeparation();
  bool applyHandlerCuts();

  void setNTupleType(TString c){m_nTuple_type = c;}
  TString getNTupleType(){return m_nTuple_type;}

  double getPhysicsWeight(){return m_physicsWeight;}

  void setMETdataVertHT(float c0,float cv, float ch){m_met_data_sigma0 = c0;m_met_data_vert = cv; m_met_data_ht = ch;}
  void setMETsmearVertHT(float c0,float cv,float ch){m_met_smear_sigma0 = c0;m_met_smear_vert = cv; m_met_smear_ht = ch;}

  /////////////////////////////
  //Access physics quantities//
  /////////////////////////////
  double getLT() {return m_LT;}
  double getST() {return m_ST;}
  double getLJMET() {return m_LJMET;}
  double getHT() {return m_HT;}
  double getPFMET() {return pf_met_pt;}
  double getMT(){return m_MT;}
  double getMLL(){return m_MLL;}
  double getPU(){return pileup_trueNumInteractions >= 0 ? pileup_trueNumInteractions : 0;}

  std::vector<SignatureObject*> getGoodMuons();
  std::vector<SignatureObject*> getGoodElectrons();
  std::vector<SignatureObject*> getGoodTaus();
  std::vector<SignatureObject*> getGoodPhotons();
  std::vector<SignatureObject*> getGoodJets();
  std::vector<SignatureObject*> getGoodRecoTracks();
  std::vector<SignatureObject*> getGoodMCParticles();
  std::vector<SignatureRecoVertex*> getGoodRecoVertices();
  std::vector<SignatureTrigger*> getTriggers();
  SignatureObjectMET* getMET();
  SignatureBeamSpot* getBeamSpot();


  void dumpEventInfo(){SkimTreeBase::dumpEventInfo();}
  void addDumpEvent(int,int,long);

  //////////////////////
  //Product Management//
  //////////////////////
  void addProduct(TString,TString);
  void addProductCut(TString,ObjectCut*);
  std::vector<SignatureObject*> getProduct(TString);
  void createProducts();
  void resetProducts();
  void setSelfSeparate(TString,double);
  void separateProducts();
  void addProductSeparation(TString,TString,double);
  void addProductSeparation(TString,TString,double,double);
  bool isProductPresent(TString);

 private:

  void prepareEvent();

  void printSignature(Signature*);

  TString m_nTuple_type;

  void readMuons();
  void readElectrons();
  void readPhotons();
  void readJets();
  void readMET();
  void readRecoTracks();
  void readTaus();
  void readMCParticles();
  void readRecoVertices();
  void readBeamSpots();
  void readTriggers();
  void readFilters();

  int findTauLeadingTrack(SignatureObjectTau*);

  ///////////////////////////////
  //some stuff for btag weights//
  ///////////////////////////////
  std::vector<int> associateJetsToPartons();
  TString m_bTagForReweight;

  bool isBTagged(SignatureObjectJet*);
  std::vector<float> getLightScaleFactors();
  std::vector<float> getCScaleFactors();
  std::vector<float> getBScaleFactors();
  TF1* GetSFLight(TString,TString,float,float);
  TF1* GetSFB(TString,TString,float,float);
  TF1* GetEffLight(TString,TString,float,float);
  TF1* GetEffC(TString,TString,float,float);
  int getBTagWeight(std::vector<float>,std::vector<int>);

  TF1* m_SFL;
  TF1* m_SFB;
  TF1* m_EFL;
  TF1* m_EFC;

  ////////////////

  void calcLT();
  void calcST();
  void calcLJMET();
  void calcHT();
  void calcMT();

  void calcPhysicsWeight();
  void calcPhysicsWeightWithBjets();

  void smearMET();

  /////////////////

  double getMuonIsolationCorrection(double);
  double getMuonIdentificationCorrection(double);
  double getElectronIsolationCorrection(double);
  double getElectronIdentificationCorrection(double);

  //////////////////

  double calculateJetBeta(SignatureObjectJet*,SignatureRecoVertex*);

  TString m_outFileName;
  TFile* m_outFile;
  int m_lastEntryPrepared;
  int m_currentEntry;
  TH2F* m_signatureCorrelationHisto;
  std::vector<ObjectCut*> m_muonCuts;
  std::vector<ObjectCut*> m_electronCuts;
  std::vector<ObjectCut*> m_photonCuts;
  std::vector<ObjectCut*> m_jetCuts;
  std::vector<ObjectCut*> m_isotrackCuts;
  std::vector<ObjectCut*> m_tauCuts;
  std::vector<ObjectCut*> m_mcparticleCuts;
  std::vector<VertexCut*> m_recovertexCuts;
  std::vector<SignatureCut*> m_handlerCuts;
  double m_LT,m_ST,m_LJMET,m_HT,m_MT,m_MLL;

  TH1F* m_PUweights;
  float m_separation_electron_muon;
  float m_separation_tau_muon;
  float m_separation_tau_electron;
  float m_separation_jet_muon;
  float m_separation_jet_electron;
  float m_separation_jet_tau;
  float m_separation_photon_muon;
  float m_separation_photon_electron;
  float m_separation_photon_tau;
  float m_separation_photon_jet;
  float m_separation_isotrack_muon;
  float m_separation_isotrack_electron;
  float m_met_smear_sigma0;
  float m_met_smear_vert;
  float m_met_smear_ht;
  float m_met_data_sigma0;
  float m_met_data_vert;
  float m_met_data_ht;

  bool m_debugMode;

  std::vector<SignatureObject*> m_muons;
  std::vector<SignatureObject*> m_electrons;
  std::vector<SignatureObject*> m_photons;
  std::vector<SignatureObject*> m_jets;
  SignatureObjectMET* m_met;
  std::vector<SignatureObject*> m_recotracks;
  std::vector<SignatureObject*> m_taus;
  std::vector<SignatureObject*> m_mcparticles;
  std::vector<SignatureRecoVertex*> m_recovertices;
  SignatureBeamSpot* m_beamspot;
  std::vector<SignatureTrigger*> m_triggers;

  std::vector<SignatureObject*> m_good_muons;
  std::vector<SignatureObject*> m_good_electrons;
  std::vector<SignatureObject*> m_good_photons;
  std::vector<SignatureObject*> m_good_jets;
  std::vector<SignatureObject*> m_good_recotracks;
  std::vector<SignatureObject*> m_good_taus;
  std::vector<SignatureObject*> m_good_mcparticles;
  std::vector<SignatureRecoVertex*> m_good_recovertices;

  std::map<TString,bool> m_filters;

  bool m_doPriorityList;

  bool m_isMC;

  double m_physicsWeight;
  double m_btagWeights[3];
  int m_bTagged;

  std::map<int, std::map<int,std::vector<long> > > m_dumpList;

  std::map<int, std::vector<int> > m_goodRunLumi;
  bool m_doRunLumiCheck;
  std::multimap<int, std::vector<std::pair<int, int> > > m_json;
  bool m_doRunLumiCheckFromJSON;
  int m_checkedRun;
  int m_checkedLumi;
  bool m_isRunLumiGood;
  
  bool checkRunLumi(int r, int l);
  bool checkRunLumiFromJSON(int RunNumber, int LumiNumber, bool debug = false);

  /*
  EGammaMvaEleEstimator* myMVANonTrig_;
  EGammaMvaEleEstimator* myMVATrig_;
  */
  
  int m_jetCorrMode;
  int m_electronUncertaintyMode;
  int m_muonUncertaintyMode;
  
  ////////////
  //Products//
  ////////////
  std::vector<TString> m_product_names;
  std::map<TString,TString> m_product_sources;
  std::map<TString,std::vector<SignatureObject*> > m_products;
  std::map<TString,std::vector<ObjectCut*> > m_product_cuts;
  std::map<TString,std::map<TString,std::pair<double,double> > > m_product_separation;
  std::map<TString,double> m_product_selfseparation;

 protected:

  std::vector<Signature*> m_preHandlerCutSignatures;
  std::vector<Signature*> m_Signatures;
  std::vector<SignatureWithBjets*> m_bjetSignatures;
  Signature* m_noCutSignature;

  ClassDef(SignatureHandler,1);

};

#endif //#ifdef SignatureHandler_cxx
