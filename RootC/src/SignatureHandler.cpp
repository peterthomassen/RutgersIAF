//--------------------------------------------------------------------
//Written by: 
//Dr. Matthew Walker
//Rutgers University
//Postdoc 
//August 2011
//--------------------------------------------------------------------


#define SignatureHandler_cxx
#include "RutgersIAF2012/RootC/interface/SignatureHandler.h"
#include "RutgersIAF2012/RootC/interface/SignatureWithBjets.h"
#include "TPRegexp.h"
#include "TRandom3.h"
#include <assert.h>

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(SignatureHandler)

  SignatureHandler::SignatureHandler(TTree *tree, TString ofname, const char* option): BaseHandler(),SkimTreeBase(tree)
{
  // Don't add histograms to the directory (bookkeeping is a big performance hit with many histograms)
  TH1::AddDirectory(kFALSE);

  //add default products
  addProduct("goodMuons","allMuons");
  addProduct("goodElectrons","allElectrons");
  addProduct("goodIsoTracks","allRecoTracks");
  addProduct("goodTaus","allTaus");
  addProduct("goodPhotons","allPhotons");
  addProduct("goodJets","allJets");
  addProduct("goodMcParticles","allMCparticles");

  m_doRunLumiCheck = false;
  m_doRunLumiCheckFromJSON = false;
  m_checkedRun = -1;
  m_checkedLumi = -1;
  m_isRunLumiGood = true;

  //product separations
  /*
  setSelfSeparate("goodMuons",0.1);
  setSelfSeparate("goodElectrons",0.1);
  setSelfSeparate("goodTaus",0.15);
  setSelfSeparate("goodIsoTracks",0.005);

  addProductSeparation("goodElectrons","goodMuons",0.1);
  addProductSeparation("goodTaus","goodMuons",0.3);
  addProductSeparation("goodTaus","goodElectrons",0.3);
  addProductSeparation("goodTaus","goodIsoTracks",0.3);
  addProductSeparation("goodJets","goodMuons",0.3);
  addProductSeparation("goodJets","goodElectrons",0.3);
  addProductSeparation("goodJets","goodTaus",0.3);
  addProductSeparation("goodJets","goodIsoTracks",0.3);
  addProductSeparation("goodPhotons","goodMuons",0.1);
  addProductSeparation("goodPhotons","goodElectrons",0.1);
  addProductSeparation("goodPhotons","goodTaus",0.1);
  addProductSeparation("goodPhotons","goodJets",0.3);
  addProductSeparation("goodPhotons","goodIsoTracks",0.1);
  addProductSeparation("goodIsoTracks","goodMuons",0.1);
  addProductSeparation("goodIsoTracks","goodElectrons",0.1);
  */
  m_separation_electron_muon = 0.1;
  m_separation_tau_muon = 0.1;
  m_separation_tau_electron = 0.1;
  m_separation_jet_muon = 0.3;
  m_separation_jet_electron = 0.3;
  m_separation_jet_tau = 0.3;
  m_separation_photon_muon = 0.1;
  m_separation_photon_electron = 0.1;
  m_separation_photon_tau = 0.1;
  m_separation_isotrack_muon = 0.1;
  m_separation_isotrack_electron = 0.1;
  m_separation_photon_jet = 0.3;

  m_isMC = false;
  m_MCtype = "";
  m_PUweights = 0;
  m_bTagForReweight = "CSVM";
  m_physicsWeight = 1.0;

  m_lastEntryPrepared = -1;
  m_currentEntry = -1;
  m_outFileName = ofname;
  m_outFile = new TFile(m_outFileName.Data(),option);
  assert(!(m_outFile->IsZombie()));
  m_noCutSignature = new Signature("noCutSignature","");

  m_doPriorityList = false;

  m_SFL = 0;
  m_SFB = 0;
  m_EFL = 0;
  m_EFC = 0;

  m_met_data_sigma0 = 3.61;
  m_met_data_vert = 3.67;
  m_met_data_ht = 5.85;

  m_met_smear_sigma0 = m_met_data_sigma0;
  m_met_smear_vert = m_met_data_vert;
  m_met_smear_ht = m_met_data_ht;

  m_nTuple_type="";
  /*
  vector<string> myManualCatWeigths;
  myManualCatWeigths.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat1.weights.xml");
  myManualCatWeigths.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat2.weights.xml");
  myManualCatWeigths.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat3.weights.xml");
  myManualCatWeigths.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat4.weights.xml");
  myManualCatWeigths.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat5.weights.xml");
  myManualCatWeigths.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat6.weights.xml");

  Bool_t manualCat = true;
  
  myMVANonTrig_ = new EGammaMvaEleEstimator;
  myMVANonTrig_->initialize("BDT",
			   EGammaMvaEleEstimator::kNonTrig,
			   manualCat, 
			   myManualCatWeigths);
  
  // NOTE: it is better if you copy the MVA weight files locally. See the previous remark

  vector<string> myManualCatWeigthsTrig;
  myManualCatWeigthsTrig.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_TrigV0_Cat1.weights.xml");
  myManualCatWeigthsTrig.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_TrigV0_Cat2.weights.xml");
  myManualCatWeigthsTrig.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_TrigV0_Cat3.weights.xml");
  myManualCatWeigthsTrig.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_TrigV0_Cat4.weights.xml");
  myManualCatWeigthsTrig.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_TrigV0_Cat5.weights.xml");
  myManualCatWeigthsTrig.push_back(string(getenv("CMSSW_BASE"))+"/src/EGamma/EGammaAnalysisTools/data/Electrons_BDTG_TrigV0_Cat6.weights.xml");

  myMVATrig_ = new EGammaMvaEleEstimator();
  myMVATrig_->initialize("BDT",
			EGammaMvaEleEstimator::kTrig,
			manualCat,
			myManualCatWeigthsTrig);
  */
}

//-----------------------------------------
SignatureHandler::~SignatureHandler()
{
  
  m_outFile->Close();
    
}
//-----------------------------------------
int SignatureHandler::getMode(std::string name) {
	std::map<std::string, int>::iterator it = m_mode.find(name);
	return (it != m_mode.end())
		? it->second
		: 0;
}
//-----------------------------------------
void SignatureHandler::setMCtype(TString type) {
	// Make sure that the MCtype hasn't been set to make sure that we don't have any remnant modes from the other MCtype set
	assert(getMCtype() == "");
	
	setIsMC(true);
	
	m_MCtype = type;
	
	if(type == "WZ") {
		setMode("WZKinematicWeight");
		setMode("nJetReweight");
	}
	if(type == "ZZ") {
		setMode("nJetReweight");
	}
	if(type == "ttbar") {
		setMode("nJetReweight");
	}
	
}
//----------------------------------------
void SignatureHandler::printSignature(Signature* sig)
{
  cout<<sig->getName()<<" "<<run<<" "<<event<<" "<<lumiBlock<<" ST: "<<getST()<<" MET: "<<getPFMET()<<" HT: "<<getHT()<<" LT: "<<getLT()<<" njets: "<<m_good_jets.size()<<endl;
  cout<<"agrdl "<<sig->getName()<<" "<<run<<" "<<lumiBlock<<" "<<event<<" leptons "<<m_good_electrons.size()+m_good_muons.size()+m_good_taus.size()<<" muons "<<m_good_muons.size()<<" electrons "<<m_good_electrons.size()<<" taus "<<m_good_taus.size()<<" weight "<<m_physicsWeight;
  if(getMode("debugPhysicsWeights") > 0) {
	  cout<<"(";
	  std::map<TString, double>::iterator iter;
	  double weight = 1.0;
	  for(iter = m_physicsWeights.begin(); iter != m_physicsWeights.end(); ++iter) {
		  cout << iter->first << "=" << iter->second << ",";
		  weight *= iter->second;
	  }
	  cout<<"other="<<(m_physicsWeight/weight)<<")";
  }
  cout<<endl;
}
//-----------------------------------------
Signature* SignatureHandler::addSignature(const char* name, const char* option)
{
  Signature* sig = new Signature(name,option);
  addSignature(sig);
  return sig;
}

//-----------------------------------------
void SignatureHandler::addPreCutSignature(const char* name, const char* option)
{
  Signature* sig = new Signature(name,option);
  addPreCutSignature(sig);
}
//-----------------------------------------
void SignatureHandler::initSignatures()
{
  int nSig = (int)m_Signatures.size()+(int)m_preHandlerCutSignatures.size()+(int)m_bjetSignatures.size();
  m_signatureCorrelationHisto = new TH2F("signatureCorrelationHisto","",nSig,-0.5,(float)nSig-0.5,nSig,-0.5,(float)nSig-0.5);
  m_noCutSignature->init();
  unsigned int s = 0,u=0;
  for(s = 0; s < m_Signatures.size(); s++){
    m_signatureCorrelationHisto->GetXaxis()->SetBinLabel(s+1,m_Signatures[s]->getName());
    m_signatureCorrelationHisto->GetYaxis()->SetBinLabel(s+1,m_Signatures[s]->getName());
    m_Signatures[s]->init();
  }
  for(u = 0; u < m_bjetSignatures.size(); u++){
    m_signatureCorrelationHisto->GetXaxis()->SetBinLabel(s+u+1,m_bjetSignatures[u]->getName());
    m_signatureCorrelationHisto->GetYaxis()->SetBinLabel(s+u+1,m_bjetSignatures[u]->getName());
    m_bjetSignatures[u]->init();
  }
  for(unsigned int t = 0; t < m_preHandlerCutSignatures.size(); t++){
    m_signatureCorrelationHisto->GetXaxis()->SetBinLabel(s+u+t+1,m_preHandlerCutSignatures[t]->getName());
    m_signatureCorrelationHisto->GetYaxis()->SetBinLabel(s+u+t+1,m_preHandlerCutSignatures[t]->getName());
    m_preHandlerCutSignatures[t]->init();
  }

  //init b weighting
  if(m_isMC){
    m_SFL = GetSFLight("mean",m_bTagForReweight,0.0,2.4);
    m_SFB = GetSFB("mean",m_bTagForReweight,0.0,2.4);
    m_EFL = GetEffLight("mean",m_bTagForReweight,0.0,2.4);
    m_EFC = GetEffC("mean",m_bTagForReweight,0.0,2.4);
  }
}

//-----------------------------------------
void SignatureHandler::finishSignatures()
{
  m_outFile->cd();
  m_signatureCorrelationHisto->Write();
  m_noCutSignature->finish();
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    m_Signatures[s]->finish();
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    m_preHandlerCutSignatures[s]->finish();
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    m_bjetSignatures[s]->finish();
  }
}

//-----------------------------------------
int SignatureHandler::setBranchList(std::vector<TString> branchList) {
	if(branchList.size() == 0) {
		UInt_t found = 0;
		fChain->SetBranchStatus("*", 1, &found);
		return found;
	}
	
	fChain->SetBranchStatus("*", 0);
	
	int n = 0;
	for(unsigned int i = 0; i < branchList.size(); ++i) {
		UInt_t found = 0;
		fChain->SetBranchStatus(branchList[i].Data(), 1, &found);
		n += found;
	}
	
	return n;
}

//-----------------------------------------
void SignatureHandler::eventLoop()
{
	eventLoop(-1, 0);
}

void SignatureHandler::eventLoop(int onlyRun, long int onlyEvent)
{
  int nevents = fChain->GetEntries();
  int nEntryLow = getMode("nEntryLow");
  int nEntryHigh = getMode("nEntryHigh");
  if(nEntryHigh == 0) nEntryHigh = nevents;

bool flatNtuple = false;

Double_t weight = 0;
TString* sigName = 0;
TString* flavor1 = 0;
TString* flavor2 = 0;
TString* flavor3 = 0;
Float_t charge1 = 0;
Float_t charge2 = 0;
Float_t charge3 = 0;
Double_t pt1 = 0;
Double_t pt2 = 0;
Double_t pt3 = 0;
Double_t met = 0;
Double_t ht = 0;
Double_t st = 0;
Int_t n_b = 0;
Int_t n_electronsIP = -1;
Int_t n_electronsNIP = -1;
Int_t n_electronsINP = -1;
Int_t n_electronsNINP = -1;
Int_t n_muonsIP = -1;
Int_t n_muonsNIP = -1;
Int_t n_muonsINP = -1;
Int_t n_muonsNINP = -1;
Int_t n_tausIP = -1;
Int_t n_tracksIP = -1;
Int_t n_tracksINP = -1;
Int_t n_tracksNIP = -1;
Int_t n_tracksNINP = -1;

TFile* f1 = 0;
TTree* tree = 0;

if(flatNtuple) {
f1 = new TFile(m_outFileName + TString(".simpleTree.root"), "RECREATE");
tree = new TTree("tree", "a simple tree");

tree->Branch("weight", &weight, "weight/D");
tree->Branch("signature", &sigName);
tree->Branch("flavor1", &flavor1);
tree->Branch("flavor2", &flavor2);
tree->Branch("flavor3", &flavor3);
tree->Branch("charge1", &charge1, "charge1/F");
tree->Branch("charge2", &charge2, "charge2/F");
tree->Branch("charge3", &charge3, "charge3/F");
tree->Branch("pt1", &pt1, "pt1/D");
tree->Branch("pt2", &pt2, "pt2/D");
tree->Branch("pt3", &pt3, "pt3/D");
tree->Branch("met", &met, "met/D");
tree->Branch("ht", &ht, "ht/D");
tree->Branch("st", &st, "st/D");
tree->Branch("n_b", &n_b, "n_b/I");
tree->Branch("n_electronsIP", &n_electronsIP, "n_electronsIP/I");
tree->Branch("n_electronsNIP", &n_electronsNIP, "n_electronsNIP/I");
tree->Branch("n_electronsINP", &n_electronsINP, "n_electronsINP/I");
tree->Branch("n_electronsNINP", &n_electronsNINP, "n_electronsNINP/I");
tree->Branch("n_muonsIP", &n_muonsIP, "n_muonsIP/I");
tree->Branch("n_muonsNIP", &n_muonsNIP, "n_muonsNIP/I");
tree->Branch("n_muonsINP", &n_muonsINP, "n_muonsINP/I");
tree->Branch("n_muonsNINP", &n_muonsNINP, "n_muonsNINP/I");
tree->Branch("n_tausIP", &n_tausIP, "n_tausIP/I");
tree->Branch("n_tracksIP", &n_tracksIP, "n_tracksIP/I");
tree->Branch("n_tracksINP", &n_tracksINP, "n_tracksINP/I");
tree->Branch("n_tracksNIP", &n_tracksNIP, "n_tracksNIP/I");
tree->Branch("n_tracksNINP", &n_tracksNINP, "n_tracksNINP/I");
}

 for(m_currentEntry = nEntryLow; m_currentEntry < nEntryHigh; m_currentEntry++){
    fChain->GetEntry(m_currentEntry);
    if (m_currentEntry % 100000 == 0)cout<<"Processing event "<<m_currentEntry<<" of "<<nevents<<endl;
    if(onlyRun >= 0 && (run != onlyRun || event != onlyEvent)) continue;

    if(m_dumpList.find(run) != m_dumpList.end() && m_dumpList[run].find(lumiBlock) != m_dumpList[run].end() && find(m_dumpList[run][lumiBlock].begin(),m_dumpList[run][lumiBlock].end(),event) != m_dumpList[run][lumiBlock].end())SkimTreeBase::dumpEventInfo();
    if(m_doRunLumiCheck || m_doRunLumiCheckFromJSON){
      if(run != m_checkedRun || lumiBlock != m_checkedLumi){
        m_isRunLumiGood = ((m_doRunLumiCheck && checkRunLumi(run,lumiBlock)) || (m_doRunLumiCheckFromJSON && checkRunLumiFromJSON(run,lumiBlock)));
        m_checkedRun = run;
        m_checkedLumi = lumiBlock;
        
		if(!m_isRunLumiGood) {
			if(getDebugMode()) std::cout << "JSON: Decided against running over run " << run << ", ls " << lumiBlock << std::endl;
		} else {
			if(getDebugMode()) std::cout << "JSON: Will run over run " << run << ", ls " << lumiBlock << std::endl;
		}
      }
      if(!m_isRunLumiGood) {
		  continue;
	  }
    }

    /*
    if(m_currentEntry > 10)break;
    cout<<"================================================"<<endl;
    cout<<"================================================"<<endl;
    cout<<"================================================"<<endl;
    dumpEventInfo();
    */
    //if(run == 167807 && event == 1936020306 && lumiBlock == 1629)dumpEventInfo();
    //if(run == 170876 && event == 178628612 && lumiBlock == 208)dumpEventInfo();
    //if(run == 171578 && event == 314870689 && lumiBlock == 326)dumpEventInfo();
    /*
    if(run == 1 && event == 93 && lumiBlock == 666666)dumpEventInfo();
    if(run == 1 && event == 175 && lumiBlock == 666667)dumpEventInfo();
    if(run == 1 && event == 179 && lumiBlock == 666667)dumpEventInfo();
    if(run == 1 && event == 450 && lumiBlock == 666670)dumpEventInfo();
    if(run == 1 && event == 558 && lumiBlock == 666671)dumpEventInfo();
    if(run == 1 && event == 760 && lumiBlock == 666673)dumpEventInfo();
    if(run == 1 && event == 1124 && lumiBlock == 666677)dumpEventInfo();
    if(run == 1 && event == 1126 && lumiBlock == 666677)dumpEventInfo();
    if(run == 1 && event == 8999 && lumiBlock == 666755)dumpEventInfo();
    if(run == 1 && event == 280  && lumiBlock == 666667)dumpEventInfo();
    if(run == 1 && event == 3283 && lumiBlock == 666682)dumpEventInfo();
    if(run == 1 && event == 4086 && lumiBlock == 666686)dumpEventInfo();
    if(run == 1 && event == 17798 && lumiBlock == 666754)dumpEventInfo();
    */
    ////////////////////////////////////////////////////////////////
    //Get all Physics objects and calculate all Physics quantities//
    ////////////////////////////////////////////////////////////////
    prepareEvent();
    /*
    for(int i = 0; i < (int)m_electrons.size(); i++){
      //cout<<"electron: "<<run<<" "<<lumiBlock<<" "<<event<<" "<<m_electrons[i]->Pt()<<" "<<m_electrons[i]->Eta()<<" "<<m_electrons[i]->Phi()<<" "<<99<<" "<<((SignatureObjectElectron*)m_electrons[i])->getRelIso()<<" "<<getHT()<<" "<<getPFMET()<<" "<<m_good_jets.size()<<" "<<m_good_electrons.size()<<endl;
      cout<<"electron: "<<run<<" "<<lumiBlock<<" "<<event<<" "<<m_electrons[i]->Pt()<<" "<<m_electrons[i]->Eta()<<" "<<m_electrons[i]->Phi()<<" "<<((SignatureObjectElectron*)m_electrons[i])->getRelIso()<<" "<<((SignatureObjectElectron*)m_electrons[i])->getPhotonIso()<<" "<<((SignatureObjectElectron*)m_electrons[i])->getNeutralHadronIso()<<" "<<((SignatureObjectElectron*)m_electrons[i])->getChargedHadronIso()<<" "<<((SignatureObjectElectron*)m_electrons[i])->getRho()<<endl;
    }
    for(int i = 0; i < (int)m_muons.size(); i++){
      cout<<"muon: "<<run<<" "<<lumiBlock<<" "<<event<<" "<<m_muons[i]->Pt()<<" "<<m_muons[i]->Eta()<<" "<<m_muons[i]->Phi()<<" "<<99<<" "<<((SignatureObjectMuon*)m_muons[i])->getRelIso()<<" "<<getHT()<<" "<<getPFMET()<<" "<<m_good_jets.size()<<" "<<m_good_muons.size()<<endl;
    }
    for(int i = 0; i < (int)m_jets.size(); i++){
      cout<<"jet: "<<run<<" "<<lumiBlock<<" "<<event<<" "<<m_jets[i]->Pt()<<" "<<m_jets[i]->Eta()<<" "<<m_jets[i]->Phi()<<" "<<99<<" - "<<getHT()<<" "<<getPFMET()<<" "<<pf_met_type1_pt<<" "<<m_good_jets.size()<<endl;
    }
    */
    m_noCutSignature->setHandler(this);
    m_noCutSignature->fillHistograms();

    if(m_debugMode)printDebugInfo();

    unsigned int nSig = m_Signatures.size();
    unsigned int nBjetSig = m_bjetSignatures.size();
    unsigned int nPreSig = m_preHandlerCutSignatures.size();
    vector<int> isSigVec(nSig + nBjetSig + nPreSig,0);
    for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
      m_preHandlerCutSignatures[s]->setHandler(this);
      if(m_preHandlerCutSignatures[s]->isSignature()){
	printSignature(m_preHandlerCutSignatures[s]);
	m_preHandlerCutSignatures[s]->fillHistograms();
	isSigVec[s+nSig+nBjetSig]=1;
      }
    }
    ////////////////////////////
    //Check handler level cuts//
    ////////////////////////////
    if(applyHandlerCuts()){

    ////////////////////////////////////////////////////////////
    //Check if it is part of the signature and fill histograms//
    ////////////////////////////////////////////////////////////
      for(unsigned int s = 0; s < m_Signatures.size(); s++){
	m_Signatures[s]->setHandler(this);
	if(m_Signatures[s]->isSignature()){
	  //dumpEventInfo();
	  printSignature(m_Signatures[s]);
	  m_Signatures[s]->fillHistograms();
	  isSigVec[s]=1;
	  if(m_doPriorityList)break;
	}
      }
      double baseweight = m_physicsWeight;
      for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
	m_bjetSignatures[s]->setHandler(this);
	if(m_bjetSignatures[s]->isSignature()){
	  //cout<<m_bjetSignatures[s]->getName()<<" m_bTagged "<<m_bTagged<<" low: "<<m_bjetSignatures[s]->getLow()<<" high: "<<m_bjetSignatures[s]->getHigh()<<endl;
	  if(m_bTagged >= m_bjetSignatures[s]->getLow() && m_bTagged <= m_bjetSignatures[s]->getHigh()){
	    isSigVec[s + nSig] = 1;
	    if(!m_isMC){
			printSignature(m_bjetSignatures[s]);
			m_bjetSignatures[s]->fillHistograms();
		}
	  }
	  if(m_isMC){
	    double bweight = 0.0;
	    for(int b = m_bjetSignatures[s]->getLow(); b <= m_bjetSignatures[s]->getHigh() && b < 3; b++){
	      bweight += m_btagWeights[b];
	    }
	    m_physicsWeight = baseweight * bweight;

	    if(m_physicsWeight != 0.0){
			printSignature(m_bjetSignatures[s]);
			m_bjetSignatures[s]->fillHistograms();
		}
	  }
	}

      }
      m_physicsWeight = baseweight;

if(flatNtuple) {
weight = m_physicsWeight;
sigName = new TString("Seed");
for(unsigned int s = 0; s < m_Signatures.size(); s++){
  m_Signatures[s]->setHandler(this);
  if(m_Signatures[s]->getName() != TString("Seed") && m_Signatures[s]->isSignature()) {
	  assert(*sigName == TString("Seed"));
	  sigName = new TString((m_Signatures[s]->getName()).Data());
  }
}
flavor1 = flavor2 = flavor3 = 0;
charge1 = charge2 = charge3 = 0;
pt1 = pt2 = pt3 = 0;

std::map<double, TString> leptonFlavors;
leptonFlavors.insert(make_pair(0, "electron"));
leptonFlavors.insert(make_pair(1, "muon"));
leptonFlavors.insert(make_pair(2, "tau"));
std::vector< std::vector<Double_t> > leptons;
std::vector<SignatureObject*> pr = getProduct("goodElectrons");
for(unsigned int q = 0; q < pr.size(); ++q) {
	std::vector<Double_t> leptonInfo;
	leptonInfo.push_back(0);
	leptonInfo.push_back(pr[q]->Pt());
	leptonInfo.push_back(pr[q]->getCharge());
	leptons.push_back(leptonInfo);
}
pr = getProduct("goodMuons");
for(unsigned int q = 0; q < pr.size(); ++q) {
	std::vector<Double_t> leptonInfo;
	leptonInfo.push_back(1);
	leptonInfo.push_back(pr[q]->Pt());
	leptonInfo.push_back(pr[q]->getCharge());
	leptons.push_back(leptonInfo);
}
pr = getProduct("goodTaus");
for(unsigned int q = 0; q < pr.size(); ++q) {
	std::vector<Double_t> leptonInfo;
	leptonInfo.push_back(2);
	leptonInfo.push_back(pr[q]->Pt());
	leptonInfo.push_back(pr[q]->getCharge());
	leptons.push_back(leptonInfo);
}
for(unsigned int q = 0; q < leptons.size(); ++q) {
	std::cout << *sigName << " lepton: " << leptons[q][0] << " " << leptons[q][1] << " " << leptons[q][2] << " " << std::endl;
}
std::vector< std::vector<Double_t> > leptons2;
if(leptons.size() == 2) {
	if(leptons[0][1] > leptons[1][1]) {
		leptons2.push_back(leptons[0]);
		leptons2.push_back(leptons[1]);
	} else {
		leptons2.push_back(leptons[1]);
		leptons2.push_back(leptons[0]);
	}
}
if(leptons.size() > 2) {
	if(leptons[0][1] > leptons[1][1] && leptons[0][1] > leptons[2][1]) {
		leptons2.push_back(leptons[0]);
		if(leptons[1][1] > leptons[2][1]) {
			leptons2.push_back(leptons[1]);
			leptons2.push_back(leptons[2]);
		} else {
			leptons2.push_back(leptons[2]);
			leptons2.push_back(leptons[1]);
		}
	}
	if(leptons[1][1] > leptons[0][1] && leptons[1][1] > leptons[2][1]) {
		leptons2.push_back(leptons[1]);
		if(leptons[0][1] > leptons[2][1]) {
			leptons2.push_back(leptons[0]);
			leptons2.push_back(leptons[2]);
		} else {
			leptons2.push_back(leptons[2]);
			leptons2.push_back(leptons[0]);
		}
	}
	if(leptons[2][1] > leptons[0][1] && leptons[2][1] > leptons[1][1]) {
		leptons2.push_back(leptons[2]);
		if(leptons[0][1] > leptons[1][1]) {
			leptons2.push_back(leptons[0]);
			leptons2.push_back(leptons[1]);
		} else {
			leptons2.push_back(leptons[1]);
			leptons2.push_back(leptons[0]);
		}
	}
}

flavor1 = new TString(leptonFlavors[leptons2[0][0]].Data());
flavor2 = new TString(leptonFlavors[leptons2[1][0]].Data());
if(leptons2.size() > 2) flavor3 = new TString(leptonFlavors[leptons2[2][0]].Data());

pt1 = leptons2[0][1];
pt2 = leptons2[1][1];
if(leptons2.size() > 2) pt3 = leptons2[2][1];

charge1 = leptons2[0][2];
charge2 = leptons2[1][2];
if(leptons2.size() > 2) charge3 = leptons2[2][2];

met = getPFMET();
ht = getHT();
st = getST();
n_b = getProduct("bJetsCSVM").size();

n_electronsIP = getProduct("electronsIP").size();
n_electronsNIP = getProduct("electronsNIP").size();
n_electronsINP = getProduct("electronsINP").size();
n_electronsNINP = getProduct("electronsNINP").size();
n_muonsIP = getProduct("muonsIP").size();
n_muonsNIP = getProduct("muonsNIP").size();
n_muonsINP = getProduct("muonsINP").size();
n_muonsNINP = getProduct("muonsNINP").size();
n_tausIP = getProduct("goodTaus").size();
n_tracksIP = getProduct("tracksIP").size();
n_tracksINP = getProduct("tracksINP").size();
n_tracksNIP = getProduct("tracksNIP").size();
n_tracksNINP = getProduct("tracksNINP").size();
f1->cd();
tree->Fill();
}
    }
    ////////////////////////////////////
    //Check correlations of signatures//
    ////////////////////////////////////
    for(unsigned int s = 0; s < isSigVec.size(); s++){
      if(isSigVec[s]){
	m_signatureCorrelationHisto->Fill(s,s);
      }
      //dumpEventInfo();
      for(unsigned int t = s+1; t < isSigVec.size();t++){
	if(isSigVec[s] && isSigVec[t]){
	  m_signatureCorrelationHisto->Fill(s,t);
	  m_signatureCorrelationHisto->Fill(t,s);
	}
      }
    }


  }//End of event loop

if(flatNtuple) {
f1->cd();
tree->Write();
f1->Close();

delete tree;
delete f1;
}

}

//-----------------------------------------
void SignatureHandler::addHistogram(SignatureTH1F* h) {
	addHistogram(h, "");
}
//-----------------------------------------
void SignatureHandler::addHistogram(SignatureTH2F* h) {
	addHistogram(h, "");
}
//-----------------------------------------
void SignatureHandler::addHistogram(SignatureTH3F* h) {
	addHistogram(h, "");
}
//-----------------------------------------
void SignatureHandler::addHistogram(SignatureTH1F* h, TString signatureRegExp) {
  TString nname = m_noCutSignature->GetName();
  nname += "_";
  nname += h->GetName();
  SignatureTH1F* nh = (SignatureTH1F*)h->Clone(nname.Data());
  m_noCutSignature->addHistogram(nh);
  
  TPMERegexp re(signatureRegExp);
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    nname = m_Signatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH1F* nh2 = (SignatureTH1F*)h->Clone(nname.Data());
    m_Signatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    nname = m_preHandlerCutSignatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH1F* nh2 = (SignatureTH1F*)h->Clone(nname.Data());
    m_preHandlerCutSignatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    nname = m_bjetSignatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH1F* nh2 = (SignatureTH1F*)h->Clone(nname.Data());
    m_bjetSignatures[s]->addHistogram(nh2);
  }
}
//-----------------------------------------
void SignatureHandler::addHistogram(SignatureTH2F* h, TString signatureRegExp) {
  TString nname = m_noCutSignature->GetName();
  nname += "_";
  nname += h->GetName();
  SignatureTH2F* nh = (SignatureTH2F*)h->Clone(nname.Data());
  m_noCutSignature->addHistogram(nh);
  
  TPMERegexp re(signatureRegExp);
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    nname = m_Signatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH2F* nh2 = (SignatureTH2F*)h->Clone(nname.Data());
    m_Signatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    nname = m_preHandlerCutSignatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH2F* nh2 = (SignatureTH2F*)h->Clone(nname.Data());
    m_preHandlerCutSignatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    nname = m_bjetSignatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH2F* nh2 = (SignatureTH2F*)h->Clone(nname.Data());
    m_bjetSignatures[s]->addHistogram(nh2);
  }
}
//-----------------------------------------
void SignatureHandler::addHistogram(SignatureTH3F* h, TString signatureRegExp) {
  TString nname = m_noCutSignature->GetName();
  nname += "_";
  nname += h->GetName();
  SignatureTH3F* nh = (SignatureTH3F*)h->Clone(nname.Data());
  m_noCutSignature->addHistogram(nh);
  
  TPMERegexp re(signatureRegExp);
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    nname = m_Signatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH3F* nh2 = (SignatureTH3F*)h->Clone(nname.Data());
    m_Signatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    nname = m_preHandlerCutSignatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH3F* nh2 = (SignatureTH3F*)h->Clone(nname.Data());
    m_preHandlerCutSignatures[s]->addHistogram(nh2);
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    nname = m_bjetSignatures[s]->GetName();
    if(!re.Match(nname)) {
		continue;
	}
    nname += "_";
    nname += h->GetName();
    SignatureTH3F* nh2 = (SignatureTH3F*)h->Clone(nname.Data());
    m_bjetSignatures[s]->addHistogram(nh2);
  }
}
//-----------------------------------------
void SignatureHandler::addBasicHistograms()
{
  m_noCutSignature->addBasicHistograms();
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    m_Signatures[s]->addBasicHistograms();
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    m_preHandlerCutSignatures[s]->addBasicHistograms();
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    m_bjetSignatures[s]->addBasicHistograms();
  }
}
//-----------------------------------------
void SignatureHandler::addChargeSignHistograms()
{
  m_noCutSignature->addChargeSignHistograms();
  for(unsigned int s = 0; s < m_Signatures.size(); s++){
    m_Signatures[s]->addChargeSignHistograms();
  }
  for(unsigned int s = 0; s < m_preHandlerCutSignatures.size(); s++){
    m_preHandlerCutSignatures[s]->addChargeSignHistograms();
  }
  for(unsigned int s = 0; s < m_bjetSignatures.size(); s++){
    m_bjetSignatures[s]->addChargeSignHistograms();
  }
}
//-----------------------------------------
bool SignatureHandler::applyHandlerCuts()
{
  for(int i = 0; i < (int)m_handlerCuts.size(); i++){
    if(getDebugMode()) cout<<"handler "<<m_handlerCuts[i]->getName()<<" "<<m_handlerCuts[i]->passCut(this)<<endl;
    if(!m_handlerCuts[i]->passCut(this)){
      return false;
    }
  }
  return true;
}
//-----------------------------------------
void SignatureHandler::resetObjectLists()
{

  m_good_muons.clear();
  m_good_electrons.clear();
  m_good_photons.clear();
  m_good_jets.clear();
  m_good_recotracks.clear();
  m_good_taus.clear();
  m_good_mcparticles.clear();
  m_good_recovertices.clear();

  while(!m_muons.empty()){
    delete m_muons.back();
    m_muons.pop_back();
  }
  while(!m_electrons.empty()){
    delete m_electrons.back();
    m_electrons.pop_back();
  }
  while(!m_photons.empty()){
    delete m_photons.back();
    m_photons.pop_back();
  }
  while(!m_photons.empty()){
    delete m_photons.back();
    m_photons.pop_back();
  }
  while(!m_jets.empty()){
    delete m_jets.back();
    m_jets.pop_back();
  }
  while(!m_recotracks.empty()){
    delete m_recotracks.back();
    m_recotracks.pop_back();
  }
  while(!m_taus.empty()){
    delete m_taus.back();
    m_taus.pop_back();
  }
  while(!m_mcparticles.empty()){
    delete m_mcparticles.back();
    m_mcparticles.pop_back();
  }
  while(!m_recovertices.empty()){
    delete m_recovertices.back();
    m_recovertices.pop_back();
  }
  while(!m_triggers.empty()){
    delete m_triggers.back();
    m_triggers.pop_back();
  }

  m_muons.clear();
  m_electrons.clear();
  m_photons.clear();
  m_jets.clear();
  delete m_met;
  m_recotracks.clear();
  m_taus.clear();
  m_mcparticles.clear();
  m_recovertices.clear();
  delete m_beamspot;

}

//-----------------------------------------
void SignatureHandler::readObjectLists()
{
  // It is CRITICAL to read MC particles first and reco tracks next -- do not change order
  readMCParticles();
  readRecoTracks();
  
  // Now, read everything else
  readRecoVertices();
  readMuons();
  readElectrons();
  readPhotons();
  readJets();
  readMET();
  readTaus();
  readTriggers();
  readFilters();
}
//-----------------------------------------
int SignatureHandler::findTauLeadingTrack(SignatureObjectTau* tau)
{
  int id = -1;
  double maxpt = -99999;
  for(int i = 0; i < (int)m_recotracks.size(); i++){
    SignatureObjectRecoTrack* track = (SignatureObjectRecoTrack*)m_recotracks[i];
    if(fabs(track->Eta()) > 2.4)continue;
    if(track->Pt() < 5.0)continue;
    if(track->getCaloIso() < 0)continue;
    if(track->getCaloIso1() < 0)continue;
    if(track->getIsTracker() != 1)continue;
    if(track->getIsGlobal() == 1)continue;
    if(tau->DeltaR(TLorentzVector(*track)) > 0.075)continue;
    if(track->Pt() < maxpt)continue;
    maxpt = track->Pt();
    id = i;
  }
  return id;
}

//-----------------------------------------
void SignatureHandler::applyObjectCuts()
{
  //////////////////////////
  //Apply reco vertex cuts//
  //////////////////////////

  for(int i = 0; i < (int)m_recovertices.size(); i++){
    int passed = 1;
    for(int j = 0; j < (int)m_recovertexCuts.size(); j++){
      if(!m_recovertexCuts[j]->passCut(m_recovertices[i])){
	passed = 0;
	break;
      }
    }
    if(passed == 1)m_good_recovertices.push_back(m_recovertices[i]);
  }
}

//-----------------------------------------
void SignatureHandler::applyObjectSeparation()
{
  /////////////////////////////////////////
  //Muons are base, then remove electrons//
  /////////////////////////////////////////

  vector<SignatureObject*> d_good_electrons;
  for(int i = 0; i < (int)m_good_electrons.size(); i++){
    int separated = 1;
    for(int j = 0; j < (int)m_good_muons.size() && separated == 1; j++){
      if(m_good_muons[j]->DeltaR(*(m_good_electrons[i])) < m_separation_electron_muon)separated = 0;
    }
    if(separated == 1)d_good_electrons.push_back(m_good_electrons[i]);
  }
  m_good_electrons.clear();
  m_good_electrons = d_good_electrons;
  d_good_electrons.clear();

  //////////////////////////////////////////////////////
  //Now Muons and Electrons are separated, remove taus//
  //////////////////////////////////////////////////////

  vector<SignatureObject*> d_good_taus;

  for(int i = 0; i < (int)m_good_taus.size(); i++){
    int separated = 1;
    for(int j = 0; j < (int)m_good_muons.size() && separated == 1; j++){
      if(m_good_muons[j]->DeltaR(*(m_good_taus[i])) < m_separation_tau_muon)separated = 0;
    }
    for(int j = 0; j < (int)m_good_electrons.size() && separated == 1; j++){
      if(m_good_electrons[j]->DeltaR(*(m_good_taus[i])) < m_separation_tau_electron)separated = 0;
    }
    if(separated == 1)d_good_taus.push_back(m_good_taus[i]);
  }
  m_good_taus.clear();
  m_good_taus = d_good_taus;
  d_good_taus.clear();

  ////////////////////////////////////////////////////
  //Now Muons, Electrons, Taus are good, remove jets//
  ////////////////////////////////////////////////////

  vector<SignatureObject*> d_good_jets;
  for(int i = 0; i < (int)m_good_jets.size(); i++){
    int separated = 1;
    for(int j = 0; j < (int)m_good_muons.size() && separated == 1; j++){
      if(m_good_muons[j]->DeltaR(*(m_good_jets[i])) < m_separation_jet_muon)separated = 0;
    }
    for(int j = 0; j < (int)m_good_electrons.size() && separated == 1; j++){
      if(m_good_electrons[j]->DeltaR(*(m_good_jets[i])) < m_separation_jet_electron)separated = 0;
    }
    for(int j = 0; j < (int)m_good_taus.size() && separated == 1; j++){
      if(m_good_taus[j]->DeltaR(*(m_good_jets[i])) < m_separation_jet_tau)separated = 0;
    }
    if(separated == 1)d_good_jets.push_back(m_good_jets[i]);
  }

  m_good_jets.clear();
  m_good_jets = d_good_jets;
  d_good_jets.clear();

  ////////////////////////////////////////////////////
  //Now Muons, Electrons, Taus are good, remove photons//
  ////////////////////////////////////////////////////

  vector<SignatureObject*> d_good_photons;
  for(int i = 0; i < (int)m_good_photons.size(); i++){
    int separated = 1;
    for(int j = 0; j < (int)m_good_muons.size() && separated == 1; j++){
      if(m_good_muons[j]->DeltaR(*(m_good_photons[i])) < m_separation_photon_muon)separated = 0;
    }
    for(int j = 0; j < (int)m_good_electrons.size() && separated == 1; j++){
      if(m_good_electrons[j]->DeltaR(*(m_good_photons[i])) < m_separation_photon_electron)separated = 0;
    }
    for(int j = 0; j < (int)m_good_taus.size() && separated == 1; j++){
      if(m_good_taus[j]->DeltaR(*(m_good_photons[i])) < m_separation_photon_tau)separated = 0;
    }
    if(separated == 1)d_good_photons.push_back(m_good_photons[i]);
  }

  m_good_photons.clear();
  m_good_photons = d_good_photons;
  d_good_photons.clear();

  ///////////////////////////////////////////////
  //Separate isotracks from electrons and muons//
  ///////////////////////////////////////////////
 
  vector<SignatureObject*> d_good_recotracks;
  for(int i = 0; i < (int)m_good_recotracks.size(); i++){
    int separated = 1;
    for(int j = 0; j < (int)m_good_muons.size() && separated == 1; j++){
      if(m_good_muons[j]->DeltaR(*(m_good_recotracks[i])) < m_separation_isotrack_muon)separated = 0;
    }
    for(int j = 0; j < (int)m_good_electrons.size() && separated == 1; j++){
      if(m_good_electrons[j]->DeltaR(*(m_good_recotracks[i])) < m_separation_isotrack_electron)separated = 0;
    }
    if(separated == 1)d_good_recotracks.push_back(m_good_recotracks[i]);
  }

  m_good_recotracks.clear();
  m_good_recotracks = d_good_recotracks;
  d_good_recotracks.clear();
}

//-----------------------------------------
void SignatureHandler::calcLT()
{
  m_LT = 0;
  for(int i = 0; i < (int)m_good_muons.size();i++){
    m_LT += m_good_muons[i]->Pt();
  }
  for(int i = 0; i < (int)m_good_electrons.size(); i++){
    m_LT += m_good_electrons[i]->Pt();
  }
  for(int i = 0; i < (int)m_good_taus.size(); i++){
    m_LT += m_good_taus[i]->Pt();
  }
  for(int i = 0; i < (int)m_good_photons.size(); i++){
    m_LT += m_good_photons[i]->Pt();
  }
  /*
  for(int i = 0; i < (int)m_good_recotracks.size(); i++){
    m_LT += m_good_recotracks[i]->Pt();
  }
  */
}

//-----------------------------------------
void SignatureHandler::calcHT()
{
  m_HT = 0;
  for(int i = 0; i < (int)m_good_jets.size(); i++){
    m_HT += m_good_jets[i]->Pt();
  }
}

//-----------------------------------------
void SignatureHandler::calcST()
{
  m_ST = m_HT + m_LT + pf_met_pt;
}

//-----------------------------------------
void SignatureHandler::calcLJMET()
{
  m_LJMET = 0;
  TLorentzVector ljmet;
  for(int i = 0; i < (int)m_good_muons.size();i++){
    ljmet += *m_good_muons[i];
  }
  for(int i = 0; i < (int)m_good_electrons.size(); i++){
    ljmet += *m_good_electrons[i];
  }
  for(int i = 0; i < (int)m_good_taus.size(); i++){
    ljmet += *m_good_taus[i];
  }
  for(int i = 0; i < (int)m_good_jets.size(); i++){
    ljmet += *m_good_jets[i];
  }
  for(int i = 0; i < (int)m_good_recotracks.size(); i++){
    ljmet += *m_good_recotracks[i];
  }
  m_LJMET = ljmet.Pt();
}
//-----------------------------------------
void SignatureHandler::smearMET()
{
  TLorentzVector metv;
  metv.SetPtEtaPhiM(pf_met_pt,0,pf_met_phi,0);
  float corrX,corrY;
  TRandom3 random;

  float sigma = pow(m_met_data_sigma0,2) - pow(m_met_smear_sigma0,2) + (pow(m_met_data_vert,2) - pow(m_met_smear_vert,2)) * float(m_good_recovertices.size()) + (pow(m_met_data_ht,2) - pow(m_met_smear_ht,2)) * m_HT / 40.0;

  corrX = random.Gaus(0,sigma);
  corrY = random.Gaus(0,sigma);
  TLorentzVector corrv(corrX,corrY,0,0);
  metv += corrv;
  pf_met_pt = metv.Pt();
  pf_met_phi = metv.Phi();

}
//-----------------------------------------
void SignatureHandler::calcMT()
{
  m_MT = 0;
  m_MLL = 0;

  TLorentzVector vll;
  TLorentzVector wl;
  if(m_good_electrons.size() + m_good_muons.size() + m_good_taus.size() == 3){
    if(m_good_taus.size() == 3)return;
    if(m_good_electrons.size() == 3){
      double bestMll = 919191919;
      int worstIndex = -1;
      for(int i = 0; i < (int)m_good_electrons.size(); i ++){
	for(int j = i+1; j < (int)m_good_electrons.size(); j++){
	  if(((SignatureObjectElectron*)m_good_electrons[i])->getCharge() * ((SignatureObjectElectron*)m_good_electrons[j])->getCharge() > 0)continue;
	  double badMll = (*((TLorentzVector*)m_good_electrons[i])+*((TLorentzVector*)m_good_electrons[j])).M();
	  if(fabs(badMll - 92) < fabs(bestMll - 92)){
	    bestMll = badMll;
	    vll = *((TLorentzVector*)m_good_electrons[i]) + *((TLorentzVector*)m_good_electrons[j]);
	    worstIndex = 3 - i - j;
	    wl = *((TLorentzVector*)m_good_electrons[worstIndex]);
	  }
	}
      }
    }else if(m_good_muons.size() == 3){
      double bestMll = 919191919;
      int worstIndex = -1;
      for(int i = 0; i < (int)m_good_muons.size(); i ++){
	for(int j = i+1; j < (int)m_good_muons.size(); j++){
	  if(((SignatureObjectMuon*)m_good_muons[i])->getCharge() * ((SignatureObjectMuon*)m_good_muons[j])->getCharge() > 0)continue;
	  double badMll = (*((TLorentzVector*)m_good_muons[i])+*((TLorentzVector*)m_good_muons[j])).M();
	  if(fabs(badMll - 92) < fabs(bestMll - 92)){
	  bestMll = badMll;
	  vll = *((TLorentzVector*)m_good_muons[i]) + *((TLorentzVector*)m_good_muons[j]);
	  worstIndex = 3 - i - j;
	  wl = *((TLorentzVector*)m_good_muons[worstIndex]);
	  }
	}
      }
    }else if(m_good_electrons.size() == 2 && m_good_muons.size() == 1){
      if((((SignatureObjectElectron*)m_good_electrons[0])->getCharge()) * (((SignatureObjectElectron*)m_good_electrons[1])->getCharge()) < 0){
	vll = *((TLorentzVector*)m_good_electrons[0]) + *((TLorentzVector*)m_good_electrons[1]);
	wl = *((TLorentzVector*)m_good_muons[0]);
      }else if(((SignatureObjectElectron*)m_good_electrons[0])->getCharge() * ((SignatureObjectMuon*)m_good_muons[0])->getCharge() < 0) {
	double badMll0 = (*((TLorentzVector*)m_good_electrons[0]) + *((TLorentzVector*)m_good_muons[0])).M();
	double badMll1 = (*((TLorentzVector*)m_good_electrons[1]) + *((TLorentzVector*)m_good_muons[0])).M();
	if(fabs(badMll0 - 50) < fabs(badMll1 - 50)){
	  vll = (*((TLorentzVector*)m_good_electrons[0]) + *((TLorentzVector*)m_good_muons[0]));
	  wl = *((TLorentzVector*)m_good_electrons[1]);
	}else{
	  vll = (*((TLorentzVector*)m_good_electrons[1]) + *((TLorentzVector*)m_good_muons[0]));
	  wl = *((TLorentzVector*)m_good_electrons[0]);
	}
      }else{
	return;
      }
    }else if(m_good_electrons.size() == 1 && m_good_muons.size() == 2){
      if((((SignatureObjectMuon*)m_good_muons[0])->getCharge()) * (((SignatureObjectMuon*)m_good_muons[1])->getCharge()) < 0){
	vll = *((TLorentzVector*)m_good_muons[0]) + *((TLorentzVector*)m_good_muons[1]);
	wl = *((TLorentzVector*)m_good_electrons[0]);
      }else  if(((SignatureObjectElectron*)m_good_electrons[0])->getCharge() * ((SignatureObjectMuon*)m_good_muons[0])->getCharge() < 0){
	double badMll0 = (*((TLorentzVector*)m_good_muons[0]) + *((TLorentzVector*)m_good_electrons[0])).M();
	double badMll1 = (*((TLorentzVector*)m_good_muons[1]) + *((TLorentzVector*)m_good_electrons[0])).M();
	if(fabs(badMll0 - 50) < fabs(badMll1 - 50)){
	  vll = (*((TLorentzVector*)m_good_muons[0]) + *((TLorentzVector*)m_good_electrons[0]));
	  wl = *((TLorentzVector*)m_good_muons[1]);
	}else{
	  vll = (*((TLorentzVector*)m_good_muons[1]) + *((TLorentzVector*)m_good_electrons[0]));
	  wl = *((TLorentzVector*)m_good_muons[0]);
	}
      }else{
	return;
      }
    }else if(m_good_electrons.size() == 2 && m_good_taus.size() == 1){
      if((((SignatureObjectElectron*)m_good_electrons[0])->getCharge()) * (((SignatureObjectElectron*)m_good_electrons[1])->getCharge()) < 0){
	vll = *((TLorentzVector*)m_good_electrons[0]) + *((TLorentzVector*)m_good_electrons[1]);
	wl = *((TLorentzVector*)m_good_taus[0]);
      }else if(((SignatureObjectElectron*)m_good_electrons[0])->getCharge() * ((SignatureObjectTau*)m_good_taus[0])->getPF_signalCharge() < 0){
	double badMll0 = (*((TLorentzVector*)m_good_electrons[0]) + *((TLorentzVector*)m_good_taus[0])).M();
	double badMll1 = (*((TLorentzVector*)m_good_electrons[1]) + *((TLorentzVector*)m_good_taus[0])).M();
	if(fabs(badMll0 - 60) < fabs(badMll1 - 60)){
	  vll = (*((TLorentzVector*)m_good_electrons[0]) + *((TLorentzVector*)m_good_taus[0]));
	  wl = *((TLorentzVector*)m_good_electrons[1]);
	}else{
	  vll = (*((TLorentzVector*)m_good_electrons[1]) + *((TLorentzVector*)m_good_taus[0]));
	  wl = *((TLorentzVector*)m_good_electrons[0]);
	}
      }else{
	return;
      }
    }else if(m_good_muons.size() == 2 && m_good_taus.size() == 1){
      if((((SignatureObjectMuon*)m_good_muons[0])->getCharge()) * (((SignatureObjectMuon*)m_good_muons[1])->getCharge()) < 0){
	vll = *((TLorentzVector*)m_good_muons[0]) + *((TLorentzVector*)m_good_muons[1]);
	wl = *((TLorentzVector*)m_good_taus[0]);
      }else if(((SignatureObjectMuon*)m_good_muons[0])->getCharge() * ((SignatureObjectTau*)m_good_taus[0])->getPF_signalCharge() < 0){
	double badMll0 = (*((TLorentzVector*)m_good_muons[0]) + *((TLorentzVector*)m_good_taus[0])).M();
	double badMll1 = (*((TLorentzVector*)m_good_muons[1]) + *((TLorentzVector*)m_good_taus[0])).M();
	if(fabs(badMll0 - 60) < fabs(badMll1 - 60)){
	  vll = (*((TLorentzVector*)m_good_muons[0]) + *((TLorentzVector*)m_good_taus[0]));
	  wl = *((TLorentzVector*)m_good_muons[1]);
	}else{
	  vll = (*((TLorentzVector*)m_good_muons[1]) + *((TLorentzVector*)m_good_taus[0]));
	  wl = *((TLorentzVector*)m_good_muons[0]);
	}
      }else{
	return;
      }
    }else if(m_good_muons.size() == 1 && m_good_electrons.size() ==1 && m_good_taus.size() == 1){
      SignatureObjectElectron* electron = (SignatureObjectElectron*)m_good_electrons[0];
      SignatureObjectMuon* muon = (SignatureObjectMuon*)m_good_muons[0];
      SignatureObjectTau* tau = (SignatureObjectTau*)m_good_taus[0];
      double em = 999999;
      double et = 999999;
      double mt = 999999;
      if(electron->getCharge() * muon->getCharge() < 1){
	em = fabs(TLorentzVector(*electron+*muon).M() - 50);
      }
      if(electron->getCharge() * tau->getPF_signalCharge() < 1){
	et = fabs(TLorentzVector(*electron + *tau).M() - 60);
      }
      if(muon->getCharge() * tau->getPF_signalCharge() < 1){
	mt = fabs(TLorentzVector(*muon + *tau).M() - 60);
      }
      if( em < et && em < mt){
	vll = *electron + *muon;
	wl = *tau;
      }else if(et < em && et < mt){
	vll = *electron+*tau;
	wl = *muon;
    }else if(mt < em && mt < et){
	vll = *tau+*muon;
	wl = *electron;
      }
      
    }else{
      return;
    }
  }else if(m_good_electrons.size() + m_good_muons.size() + m_good_taus.size() == 4){
    if(m_good_taus.size() == 3)return;
    if(m_good_taus.size() == 2 && m_good_electrons.size() == 1 && m_good_muons.size() == 1)return;
    wl.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector best(0,0,0,0);
    for(int i = 0; i < (int)m_good_electrons.size(); i++){
      float charge1 = ((SignatureObjectElectron*)m_good_electrons[i])->getCharge();
      for(int j = i+1; j < (int)m_good_electrons.size(); j++){
	float charge2 = ((SignatureObjectElectron*)m_good_electrons[j])->getCharge();
	if(charge1*charge2 > 0)continue;
	if(fabs(best.M() - 91) < fabs(TLorentzVector(*(m_good_electrons[i])+*(m_good_electrons[j])).M() - 91))continue;
	best = *(m_good_electrons[i]) +*(m_good_electrons[j]);
      }
    }
    for(int i = 0; i < (int)m_good_muons.size(); i++){
      float charge1 = ((SignatureObjectMuon*)m_good_muons[i])->getCharge();
      for(int j = i+1; j < (int)m_good_muons.size(); j++){
	float charge2 = ((SignatureObjectMuon*)m_good_muons[j])->getCharge();
	if(charge1*charge2 > 0)continue;
	if(fabs(best.M() - 91) < fabs(TLorentzVector(*(m_good_muons[i])+*(m_good_muons[j])).M() - 91))continue;
	best = *(m_good_muons[i]) + *(m_good_muons[j]);
      }
    }
    vll = best;
  }
  m_MLL = vll.M();
  TLorentzVector metv;
  metv.SetPtEtaPhiM(pf_met_pt,0,pf_met_phi,0);
  m_MT = sqrt(2*pf_met_pt * wl.Pt() * ( 1 - cos(wl.DeltaPhi(metv))));

}
//-----------------------------------------
vector<SignatureTrigger*> SignatureHandler::getTriggers()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return m_triggers;
}
//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getGoodMuons()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return getProduct("goodMuons");
  //return m_good_muons;
}
//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getGoodElectrons()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return getProduct("goodElectrons");
  //return m_good_electrons;
}

//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getGoodTaus()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return getProduct("goodTaus");
  //return m_good_taus;
}
//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getGoodJets()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return getProduct("goodJets");
  //return m_good_jets;
}
//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getGoodPhotons()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return getProduct("goodPhotons");
  //return m_good_photons;
}
//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getGoodRecoTracks()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return getProduct("goodIsoTracks");
  //return m_good_recotracks;
}
//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getGoodMCParticles()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return getProduct("goodMcParticles");
  //return m_good_mcparticles;
}
//-----------------------------------------
vector<SignatureRecoVertex*> SignatureHandler::getGoodRecoVertices()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return m_good_recovertices;
}
//-----------------------------------------
vector<SignatureRecoVertex*> SignatureHandler::getAllRecoVertices()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return m_recovertices;
}
//----------------------------------------- 
SignatureObjectMET* SignatureHandler::getMET()
{
  //if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return m_met;
}
//-----------------------------------------
SignatureBeamSpot* SignatureHandler::getBeamSpot()
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  return m_beamspot;
}
//-----------------------------------------
void SignatureHandler::addProduct(TString productName,TString productSource)
{
  if(find(m_product_names.begin(),m_product_names.end(),productName) != m_product_names.end()){
    cerr<<"Product with name "<<productName<<" is already in list, skipping"<<endl;
    return;
  }
  m_product_names.push_back(productName);
  m_product_sources[productName] = productSource;
  vector<SignatureObject*> a;
  m_products[productName] = a;
  vector<ObjectCut*> b;
  m_product_cuts[productName] = b;
}
//-----------------------------------------
void SignatureHandler::addProductCut(TString productName, ObjectCut* cut)
{
  if(m_product_cuts.find(productName) == m_product_cuts.end()){
    cerr<<"Product "<<productName<<" not found"<<endl;
    return;
  }
  m_product_cuts[productName].push_back(cut);
}
//-----------------------------------------
void SignatureHandler::addProductSeparation(TString productName,TString sepProduct, double r)
{
  addProductSeparation(productName,sepProduct,r,99999.0);
}
//-----------------------------------------
void SignatureHandler::addProductSeparation(TString productName,TString sepProduct, double r, double ptRatio)
{
  if(m_product_cuts.find(productName) == m_product_cuts.end()){
    cerr<<"Product "<<productName<<" not found"<<endl;
    return;
  }
  if(m_product_cuts.find(sepProduct) == m_product_cuts.end()){
    cerr<<"Product "<<sepProduct<<" not found"<<endl;
    return;
  }
  m_product_separation[productName][sepProduct] = pair<double,double>(r,ptRatio);
}
//-----------------------------------------
vector<SignatureObject*> SignatureHandler::getProduct(TString productName)
{
  if(m_currentEntry != m_lastEntryPrepared)prepareEvent();
  vector<SignatureObject*> retvec;
  if(m_products.find(productName) == m_products.end()){
    cerr<<"Product "<<productName<<" not found"<<endl;
    return retvec;
  }

  retvec = m_products[productName];
  return retvec;
}
//-----------------------------------------
bool SignatureHandler::isProductPresent(TString prodName)
{
  if(m_products.find(prodName) == m_products.end())return false;
  return true;
}
//-----------------------------------------
void SignatureHandler::createProducts()
{
  for(int i = 0; i < (int)m_product_names.size(); i++){
    TString pname = m_product_names[i];
    TString sname = m_product_sources[pname];
    vector<SignatureObject*> source;
    vector<SignatureObject*> product;

    if(m_products.find(sname) != m_products.end()){
      source = m_products[sname];
    }else if(sname == "allMuons"){
      source = m_muons;
    }else if(sname == "allElectrons"){
      source = m_electrons;
    }else if(sname == "allPhotons"){
      source = m_photons;
    }else if(sname == "allJets"){
      source = m_jets;
    }else if(sname == "allRecoTracks"){
      source = m_recotracks;
    }else if(sname == "allTaus"){
      source = m_taus;
    }else if(sname == "allMCparticles"){
      source = m_mcparticles;
    }

    //////////////////////////////////////////////////////
    //First apply cuts on source to create base products//
    //////////////////////////////////////////////////////
    //cout<<pname<<" "<<sname<<" "<<source.size()<<endl;

    for(int k = 0; k < (int)source.size(); k++){
      int passed = 1;
      for(int j = 0; j < (int)m_product_cuts[pname].size(); j++){
	/*
	if(pname == "goodElectrons"){
	  cout<<m_product_cuts[pname][j]->getName()<<" "<<k<<endl;
	}
	*/
	if(!m_product_cuts[pname][j]->passCut(source[k])){
	  if(m_debugMode)cout<<pname<<" "<<sname<<" "<<k<<" "<<m_product_cuts[pname][j]->getName()<<endl;
	  //if(pname == "goodElectrons")
	  //cout<<pname<<" "<<k<<" "<<m_product_cuts[pname][j]->getName()<<endl;
	  passed = 0;
	  break;
	}
      }
      if(passed == 1)product.push_back(source[k]);
    }
    m_products[pname] = product;

    ///////////////////////////////////////////////////////
    ////////////////apply self separation//////////////////
    ///////////////////////////////////////////////////////
    map<TString,double>::const_iterator selfIter = m_product_selfseparation.find(pname);
    if(selfIter != m_product_selfseparation.end()){
      vector<SignatureObject*> i_product = m_products[pname];
      vector<SignatureObject*> f_product;
      double sep = (*selfIter).second;
      for(int k = 0; k < (int)i_product.size(); k++){
	int passed = 1;
	for(int j = 0; j < k && passed == 1; j++){
	  double dr = i_product[k]->DeltaR(TLorentzVector(*(i_product[j])));
	  if((pname == "goodIsoTracks" || pname == "goodTracks" || sname == "goodTracks") && ((SignatureObjectRecoTrack*)i_product[k])->getNValidTrackerHits() == ((SignatureObjectRecoTrack*)i_product[j])->getNValidTrackerHits() && ((SignatureObjectRecoTrack*)i_product[k])->getNValidPixelHits() == ((SignatureObjectRecoTrack*)i_product[j])->getNValidPixelHits() && dr < sep)passed = 0;
	  else if((pname == "goodElectrons" || sname == "goodElectrons" || sname == "allElectrons") && fabs(((SignatureObjectElectron*)i_product[k])->getFMVAVar_eta() - ((SignatureObjectElectron*)i_product[j])->getFMVAVar_eta()) < 0.0001 && fabs(((SignatureObjectElectron*)i_product[k])->getFMVAVar_deta() - ((SignatureObjectElectron*)i_product[j])->getFMVAVar_deta()) < 0.0001 && fabs(((SignatureObjectElectron*)i_product[k])->getFMVAVar_dz() - ((SignatureObjectElectron*)i_product[j])->getFMVAVar_dz()) < 0.0001 && fabs(((SignatureObjectElectron*)i_product[k])->getSigmaIetaIeta() - ((SignatureObjectElectron*)i_product[j])->getSigmaIetaIeta()) < 0.0001)passed = 0;
	  else if(pname != "goodIsoTracks" && dr < sep && i_product[k]->getCharge() == i_product[j]->getCharge())passed = 0;
	}
	if(passed == 1)f_product.push_back(i_product[k]);
      }
      m_products[pname] = f_product;
      i_product.clear();
      f_product.clear();
    }

    ///////////////////////////////////////////////////////
    //////////apply separation to other objects////////////
    ///////////////////////////////////////////////////////

    map<TString,pair<double,double> >::iterator iter;
    for(iter = m_product_separation[pname].begin(); iter != m_product_separation[pname].end(); iter++){
      vector<SignatureObject*> i_product = m_products[pname];
      vector<SignatureObject*> comp_product;
      pair<double,double> RandPt = (*iter).second;
      double dR = RandPt.first;
      double ptRatio = RandPt.second;
      //cout<<pname<<" "<<(*iter).first<<" "<<dR<<" "<<ptRatio<<endl;
      if(m_products.find((*iter).first) != m_products.end()) comp_product = m_products[(*iter).first];
      vector<SignatureObject*> f_product;
      for(int j = 0; j < (int)i_product.size(); j++){
        int separated = 1;
        for(int k = 0; k < (int)comp_product.size() && separated == 1; k++){
          double compPt = comp_product[k]->Pt();
          if(comp_product[k]->DeltaR(*(i_product[j])) < dR && fabs(i_product[j]->Pt() - compPt) < ptRatio*compPt)separated = 0;
	  //cout<<pname<<" "<<(*iter).first<<" "<<j<<" "<<k<<" "<<separated<<endl;
        }
        if(separated == 1)f_product.push_back(i_product[j]);
      }
      i_product.clear();
      m_products[pname] = f_product;
      f_product.clear();
    }
  }
}
//-----------------------------------------
void SignatureHandler::setSelfSeparate(TString productname, double separation)
{
  if(find(m_product_names.begin(),m_product_names.end(),productname) != m_product_names.end())m_product_selfseparation[productname] = separation;
}
//-----------------------------------------
void SignatureHandler::separateProducts()
{
  map<TString,double>::iterator Iter;
  for(Iter = m_product_selfseparation.begin(); Iter != m_product_selfseparation.end(); ++Iter){
    vector<SignatureObject*> i_product = m_products[(*Iter).first];
    //sort(i_product.begin(),i_product.end());
    //reverse(i_product.begin(),i_product.end());
    double sep = (*Iter).second;
    vector<SignatureObject*> f_product;
    for(int i = 0; i < (int)i_product.size(); i++){
      int passed = 1;
      for(int j = 0; j < i && passed == 1; j++){
	double dr = i_product[i]->DeltaR(TLorentzVector(*(i_product[j])));
	if((*Iter).first == "goodIsoTracks" && ((SignatureObjectRecoTrack*)i_product[i])->getNValidTrackerHits() == ((SignatureObjectRecoTrack*)i_product[j])->getNValidTrackerHits() && ((SignatureObjectRecoTrack*)i_product[i])->getNValidPixelHits() == ((SignatureObjectRecoTrack*)i_product[j])->getNValidPixelHits() && dr < sep)passed = 0;
	else if((*Iter).first != "goodIsoTracks" && dr < sep)passed = 0;
      }
      if(passed == 1)f_product.push_back(i_product[i]);
    }
    //cout<<"self separating "<<(*Iter).first<<" for r < "<<(*Iter).second<<" before "<<i_product.size()<<" after "<<f_product.size()<<endl;
    i_product.clear();
    m_products[(*Iter).first] = f_product;
    f_product.clear();
  }

  for(int i = 0; i < (int)m_product_names.size(); i++){
    TString pname = m_product_names[i];
    map<TString,pair<double,double> >::iterator iter;
    for(iter = m_product_separation[pname].begin(); iter != m_product_separation[pname].end(); iter++){
      vector<SignatureObject*> i_product = m_products[pname];
      vector<SignatureObject*> comp_product;
      pair<double,double> RandPt = (*iter).second;
      double dR = RandPt.first;
      double ptRatio = RandPt.second;
      //cout<<pname<<" "<<(*iter).first<<" "<<dR<<" "<<ptRatio<<endl;
      if(m_products.find((*iter).first) != m_products.end()) comp_product = m_products[(*iter).first];
      vector<SignatureObject*> f_product;
      for(int j = 0; j < (int)i_product.size(); j++){
        int separated = 1;
        for(int k = 0; k < (int)comp_product.size() && separated == 1; k++){
          double compPt = comp_product[k]->Pt();
          if(comp_product[k]->DeltaR(*(i_product[j])) < dR && fabs(i_product[j]->Pt() - compPt) < ptRatio*compPt)separated = 0;
	  //cout<<pname<<" "<<(*iter).first<<" "<<j<<" "<<k<<" "<<separated<<endl;
        }
        if(separated == 1)f_product.push_back(i_product[j]);
      }
      i_product.clear();
      m_products[pname] = f_product;
      f_product.clear();
    }
  }
}
//-----------------------------------------
void SignatureHandler::resetProducts()
{
  for(int i = 0; i < (int)m_product_names.size(); i++){
    m_products[m_product_names[i]].clear();
  }
}
//-----------------------------------------
void SignatureHandler::calcPhysicsWeight()
{
  m_physicsWeight = 1.0;
  m_physicsWeights.clear();
  

  //////////////////////
  /////Btag weights/////
  //////////////////////
  calcPhysicsWeightWithBjets();//calculates n bTags for data

  if(!m_isMC)return;

  //DO NOT DO ANYTHING ELSE WITH BTAG WEIGHTS
  //IT IS TAKEN CARE OF IN EVENTLOOP

  ///////////////////
  //pileup reweight//
  ///////////////////
  if(!m_PUweights){
    cerr<<"No PILEUP weights included, please add them and run again"<<endl;
    assert(0);
  }
  double puweight = 1.0;
  int pubin = m_PUweights->FindBin(pileup_trueNumInteractions);
  puweight = m_PUweights->GetBinContent(pubin);

  m_physicsWeight *= puweight;
  if(getMode("debugPhysicsWeights") > 0) {
	  m_physicsWeights["PU"] = puweight;
  }

  //////////////
  //Trigger SF//
  //////////////

  double triggerWeight = calcTriggerWeight();
  m_physicsWeight *= triggerWeight;
  if(getMode("debugPhysicsWeights") > 0) {
	  m_physicsWeights["trigger"] = triggerWeight;
  }

  //////////////////////
  //Isolation reweight//
  //////////////////////

  double leptonCorrections = 1.0;
  for(int i = 0; i < (int)m_good_electrons.size(); i++){
    leptonCorrections *= getElectronIdentificationCorrection(m_good_electrons[i]->Pt());
    leptonCorrections *= getElectronIsolationCorrection(m_good_electrons[i]->Pt());
  }
  for(int i = 0; i < (int)m_good_muons.size(); i++){
    leptonCorrections *= getMuonIdentificationCorrection(m_good_muons[i]->Pt());
    leptonCorrections *= getMuonIsolationCorrection(m_good_muons[i]->Pt());
  }

  m_physicsWeight *= leptonCorrections;
  if(getMode("debugPhysicsWeights") > 0) {
	  m_physicsWeights["leptonCorrections"] = leptonCorrections;
  }

  if(getMode("WZKinematicWeight") > 0) {
	  std::pair<double,double> WZKinematicWeight = getWZKinematicWeight();
	  m_physicsWeight *= WZKinematicWeight.first;
	  if(getMode("debugPhysicsWeights") > 0) {
		  m_physicsWeights["WZKinematicWeight"] = WZKinematicWeight.first;
	  }
  }
  
  if(getMode("nJetReweight") > 0) {
	  if(getProduct("goodJetsFromW").size() > 0) {
		  std::cout << "goodJetsFromW: " << getProduct("goodJetsFromW").size() << ", goodAndTauFakeJets " << getProduct("goodAndTauFakeJets").size() << std::endl;
	  }
	  int njet = (int)(getProduct("goodAndTauFakeJets").size());
	  std::pair<double,double> nJetReweight = getNJetReweight(njet);
	  m_physicsWeight *= nJetReweight.first;
	  if(getMode("debugPhysicsWeights") > 0) {
		  m_physicsWeights["nJetReweight"] = nJetReweight.first;
	  }
  }
}
//-----------------------------------------
void SignatureHandler::prepareEvent()
{
  if(m_currentEntry == m_lastEntryPrepared)return;

  m_physicsWeight = 1.0;

  resetProducts();
  resetObjectLists();
  readObjectLists();

  applyObjectCuts();
  //applyObjectSeparation();

  createProducts();
  //separateProducts();

  /*
  if(m_good_muons.size() != m_products["goodMuons"].size()){
    cout<<"Muons don't match: "<<m_good_muons.size()<<" "<<m_products["goodMuons"].size()<<" from "<<m_muons.size()<<endl;
  }
  if(m_good_electrons.size() != m_products["goodElectrons"].size()){
    cout<<"Electrons don't match: "<<m_good_electrons.size()<<" "<<m_products["goodElectrons"].size()<<" from "<<m_electrons.size()<<endl;
    vector<SignatureObject*> electronProduct = getProduct("goodElectrons");
    for(int i = 0; i < (int)m_good_electrons.size(); i++){
      SignatureObjectElectron* e = (SignatureObjectElectron*)m_good_electrons[i];
      cout<<e->Pt()<<" "<<e->Eta()<<" "<<e->Phi()<<endl;
    }
    cout<<"product electrons"<<endl;
    for(int i = 0; i < (int)electronProduct.size(); i++){
      SignatureObjectElectron* e = (SignatureObjectElectron*)electronProduct[i];
      cout<<e->Pt()<<" "<<e->Eta()<<" "<<e->Phi()<<endl;
    }
    cout<<"all electrons"<<endl;
    for(int i = 0; i < (int)m_electrons.size(); i++){
      SignatureObjectElectron* e = (SignatureObjectElectron*)m_electrons[i];
      cout<<e->Pt()<<" "<<e->Eta()<<" "<<e->Phi()<<endl;
    }
  }
  */
  /*
  for(int i = 0; i < (int)m_taus.size(); i++){
    SignatureObjectTau* t = (SignatureObjectTau*)m_taus[i];
    cout<<t->Pt()<<" "<<t->Eta()<<" "<<t->getPF_DiscriminantsAt(19)<<" "<<t->getPF_DiscriminantsAt(24)<<" "<<t->getPF_DiscriminantsAt(26)<<" "<<t->getPF_DiscriminantsAt(29)<<endl;
  }
  */
  m_lastEntryPrepared = m_currentEntry;
  m_good_jets = getProduct("goodJets");
  m_good_muons = getProduct("goodMuons");
  m_good_electrons = getProduct("goodElectrons");
  m_good_taus = getProduct("goodTaus");
  m_good_recotracks = getProduct("goodIsoTracks");
  m_good_photons = getProduct("goodPhotons");
  m_good_mcparticles = getProduct("goodMcParticles");

  if(m_isMC)smearMET();

  calcLT();
  calcHT();
  calcST();
  calcLJMET();
  calcMT();

  calcPhysicsWeight();

  //cout<<m_electrons.size()<<" "<<m_good_electrons.size()<<endl;
  //cout<<m_taus.size()<<" "<<m_good_taus.size()<<endl;
  //cout<<m_jets.size()<<" "<<m_good_jets.size()<<endl;

  //if(m_good_electrons.size() + m_good_muons.size() >= 3)
  //cout << run<<" "<<event<<" "<<lumiBlock<< " " << getST() << " " << getPFMET() << " " << getHT() <<" "<<getLT()<<" "<<m_good_jets.size()<<" "<<m_good_electrons.size()<<" "<<m_good_muons.size()<<" "<<m_good_taus.size()<<" "<<m_good_photons.size()<<" "<<m_good_recotracks.size()<<endl;

  /*
  if(run == 171091 && event == 80295363 && lumiBlock == 73){
    for(int i = 0; i < (int)m_good_photons.size(); i++){
      cout<<i<<" photon pt: "<<m_good_photons[i]->Pt()<<" eta: "<<m_good_photons[i]->Eta()<<" phi: "<<m_good_photons[i]->Phi()<<" cIso: "<<((SignatureObjectWithIso*)(m_good_photons[i]))->getEcaloIso()<<endl;
    }
    for(int i = 0; i < (int)m_good_jets.size(); i++){
      cout<<i<<" jet pt: "<<m_good_jets[i]->Pt()<<" eta: "<<m_good_jets[i]->Eta()<<" phi: "<<m_good_jets[i]->Phi()<<endl;
    }
  }
  */
  return;
}
//------------------------------------------
//------------------------------------------
void SignatureHandler::addPUFile(TString fname){
  TFile pufile(fname);
  m_PUweights = (TH1F*)pufile.Get("puweights");
  m_PUweights->SetDirectory(0);
  pufile.Close();
}
//------------------------------------------
//------------------------------------------
void SignatureHandler::addDumpEvent(int run, int lumi, long event)
{
  if(m_dumpList.find(run) == m_dumpList.end()){
    map<int,vector<long> > amap;
    m_dumpList[run] = amap;
  }
  if(m_dumpList[run].find(lumi) == m_dumpList[run].end()){
    vector<long> avec;
    m_dumpList[run][lumi] = avec;
  }
  m_dumpList[run][lumi].push_back(event);
}
