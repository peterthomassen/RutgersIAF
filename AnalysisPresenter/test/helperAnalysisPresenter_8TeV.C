#include <iostream>
#include <TH1.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

// Load library, see https://root.cern.ch/phpBB2/viewtopic.php?f=3&t=19471
namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFAnalysisPresenter.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void init(Assembler* assembler) {
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
	
	assembler->addBundle(new Bundle("background", "Fakes"));
	assembler->addBundle(new Bundle("background", "TrackFakes"));
	assembler->addBundle(new Bundle("background", "PhotonFakes"));
	assembler->addBundle(new Bundle("background", "TauFakes"));
	assembler->addBundle(new Bundle("background", "Higgs"));
	assembler->addBundle(new Bundle("background", "Rare MC"));
	
	//assembler->setMinScale(0.1);
}

std::string getDataFileName() {
	return "20150916_data";
}

void prepare(Assembler* assembler) {
	Bundle* fakeBundle = assembler->getBundle("Fakes");
	for(const auto &bundleName : {"TrackFakes", "PhotonFakes", "TauFakes"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			fakeBundle->addComponent(bundle);
		}
	}
	
	Bundle* presentationBundle = new Bundle("background", "presentationBundle");
	for(const auto &bundleName : {"Fakes", "Higgs", "Rare MC"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			presentationBundle->addComponent(bundle);
		}
	}
	assembler->addBundle(presentationBundle);
	
	Bundle* fakePresentationBundle = new Bundle("background", "fakePresentationBundle");
	for(const auto &bundleName : {"TrackFakes", "PhotonFakes", "TauFakes", "Higgs", "Rare MC"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			fakePresentationBundle->addComponent(bundle);
		}
	}
	assembler->addBundle(fakePresentationBundle);
	
	assembler->setDefaultBundle(presentationBundle);
	assembler->getDefaultBundle()->print();
}

void setupData(Assembler* assembler, bool dilep = false, int fakeMode = 0) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string body = getDataFileName();
	std::string suffix = ".root";
	
	PhysicsContribution* data = 0;
	
	if(fakeMode == 0) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 19500, "2012data");
	} else if(fakeMode == 1) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 19500, "2012data", false, "treeRfakeTracks");
	} else if(fakeMode == 2) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 19500, "2012data", false, "treeRfakePhotons");
	} else if(fakeMode == 3) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 19500, "2012data", false, "treeRfakeTaus");
	} else {
		cout << "unsure what to do";
		exit(1);
	}
	
	assembler->addContribution(data);
}

void setupDataSingle(Assembler* assembler, bool fake = false, bool dilep = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".root";
	
	PhysicsContribution* data = fake
		? new PhysicsContribution("data", prefix + "20140827_fakeTracksSingle+Double" + infix + suffix, 19500, "2012trackFakeSeed")
		: new PhysicsContribution("data", prefix + "20140827_dataSingle" + infix + suffix, 19500, "2012data");
	
	assembler->addContribution(data);
}

void setupBackgroundMC(Assembler* assembler, bool dilep = false, bool ttbar = true, bool onlyTTF = false) {
//	ttbar = false;
	
	std::string prefix = "/cms/thomassen/2014/Analysis/simulation/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".simulation.root";
	
	// Richard's numbers
	// Branching ratios
//	Double_t WtoLNu = 0.3203;
//	Double_t Wto2J = (1.0-0.3203);
	// Cross sections [pb]
//	Double_t xsec_ttbar = 225.0;
//	Double_t xsec_ttbar_fullLep = pow(WtoLNu,2)*xsec_ttbar;
//	Double_t xsec_ttbar_semiLep = 2.0*WtoLNu*Wto2J*xsec_ttbar;
//	Double_t xsec_wz = 32.3*(0.3257*0.10095)*1.20;
	Double_t xsec_zz = 0.92*17.7*(0.10095*0.10095)*1.08;
	xsec_zz *= 0.97 * 1.028;
	Double_t xsec_ttw = 0.23;
	Double_t xsec_ttz = 0.208;
	Double_t xsec_tbz_tqz = 0.0114 + 2 * 0.0114; // 0.0114 is tbZ, 2*0.0114 is fudge for missing tqZ
	
	// Peter's numbers
	double xsec_ttbar_fullLep = 23.08;
	double xsec_ttbar_semiLep = 97.97 * 1.32;
	double xsec_wz = 1.2451;
	xsec_wz *= 0.957;
//	double xsec_zz = 0.181;
//	double xsec_ttw = 0.2149;
//	double xsec_ttz = 0.208;
	
	//ttbar = false;
	
	std::vector<PhysicsContribution*> mc;
	std::vector<PhysicsContribution*> mcH;
	std::vector<PhysicsContribution*> mcRare;
	
	Bundle* correlationBundle = new Bundle("background", "correlationBundle");
	assembler->addBundle(correlationBundle);
	
	PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZJetsTo3LNu" + infix + suffix, xsec_wz, "WZ");
	wz->addWeight("exp(-0.005 * PTMCZ[0]/sqrt(MMCZ[0]))", 1.038);
	wz->addWeight("(NGOODJETS[0] == 0) * 1.053 + (NGOODJETS[0] == 1) * 0.85 + (NGOODJETS[0] == 2) * 1.15 + (NGOODJETS[0] > 2) * 1.19");
	wz->addWeight("(NGOODJETS[0] <= 1) + (NGOODJETS[0] > 1) * (Alt$((PTGOODJETS[0] < 70) * 0.65 + (PTGOODJETS[0] >= 70 && PTGOODJETS[0] < 110) * 1.07 + (PTGOODJETS[0] >= 110 && PTGOODJETS[0] < 150) * 1.00 + (PTGOODJETS[0] >= 150) * 1.55, 0))");
	//wz->addWeight("1 + (NBJETSCSVM > 0) * 0.0"); // look with more data whether MC gets number of b's right
	wz->addFlatUncertainty("normalizationWZ", 0.05);
	correlationBundle->addComponent(wz);
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZJetsTo4L" + infix + suffix, xsec_zz, "ZZ");
	zz->addWeight("(NGOODJETS[0] == 0) * 1.084 + (NGOODJETS[0] == 1) * 0.75 + (NGOODJETS[0] == 2) * 0.333 + (NGOODJETS[0] > 2) * 1");
	correlationBundle->addComponent(zz);
	
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWWJets" + infix + suffix, 0.002037, "TTWW"));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWJets" + infix + suffix, xsec_ttw, "TTW"));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTZJets" + infix + suffix, xsec_ttz, "TTZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TBLL" + infix + suffix, xsec_tbz_tqz, "TBZ + TQZ"));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WWWJets" + infix + suffix, 0.08217, "WWW"));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WWZJets" + infix + suffix, 0.0633, "WWZ"));
	mc.push_back(wz);
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WZZJets" + infix + suffix, 0.019, "WZZ"));
	mc.push_back(zz);
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "ZZZNoGstarJets" + infix + suffix, 0.004587, "ZZZ"));
	
	TString nJetWeight = "1 + (NGOODJETS[0] >= 4) * 0.05"; // Peter's numbers
	
	Bundle* bundleTTbar = new Bundle("background", "ttbar");
	assembler->addBundle(bundleTTbar);
	
	if(ttbar) {
		if(dilep) {
			PhysicsContribution* ttbarS = new PhysicsContribution("backgroundMC", prefix + "TTJetsSemiLeptonic" + infix + suffix, xsec_ttbar_semiLep, "TT_SemiL");
			ttbarS->addWeight(nJetWeight);
			mc.push_back(ttbarS);
			bundleTTbar->addComponent(ttbarS);
		}
		
		if(onlyTTF) {
			mc.clear();
		}
		
		//PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + ".3LonZ" + suffix, xsec_ttbar_fullLep, "TT_FullL");
		PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullL", false, "treeR", -1, 0.1);
		ttbarF->addWeight("1.2 - 0.04 * NPROMPTNONISOINCLUSIVETRACKS7[0]");
		ttbarF->addWeight(nJetWeight);
		ttbarF->addWeight("1 + (NLEPTONS[0] - NGOODTAUS[0] >= 3) * 0.66");
//		ttbarF->addFlatUncertainty("xsec", 0.3);
		ttbarF->addFlatUncertainty("fudge", 0.194);
		mc.push_back(ttbarF);
		bundleTTbar->addComponent(ttbarF);
		
		if(!dilep) {
			std::vector<PhysicsContribution*> ttbarFfake;
			
			PhysicsContribution* ttbarFfakeTracks = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullLfakeTracks", true, "treeRfakeTracks", -1, 0.1);
			ttbarFfakeTracks->addWeight("1 + (NLEPTONS[0] - NGOODTAUS[0] >= 3) * 0.66");
			ttbarFfakeTracks->addFlatUncertainty("fudge", 0.194);
			ttbarFfake.push_back(ttbarFfakeTracks);
			assembler->getBundle("TrackFakes")->addComponent(ttbarFfakeTracks);
			
			PhysicsContribution* ttbarFfakePhotons = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullLfakePhotons", true, "treeRfakePhotons", -1, 0.1);
			ttbarFfake.push_back(ttbarFfakePhotons);
			assembler->getBundle("PhotonFakes")->addComponent(ttbarFfakePhotons);
			
			PhysicsContribution* ttbarFfakeTaus = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullLfakeTaus", true, "treeRfakeTaus", -1, 0.1);
			ttbarFfake.push_back(ttbarFfakeTaus);
			assembler->getBundle("TauFakes")->addComponent(ttbarFfakeTaus);
			
			for(auto &contribution : ttbarFfake) {
				contribution->addWeight("1.2 - 0.04 * NPROMPTNONISOINCLUSIVETRACKS7[0]");
				contribution->addWeight(nJetWeight);
				contribution->addWeight("nTrackFakeElectrons + nTrackFakeMuons + nPhotonFakeElectrons + nPhotonFakeMuons + nTauFakeTaus == 1");
				//contribution->addWeight("nTauFakeTaus <= 1");
				//contribution->addWeight("!(abs(MOSSF-90.000000)<15.000000) && !(MOSSF < (90-15))");
	//			contribution->addWeight("!(abs(MOSSF-90.000000)<15.000000)");
	//			contribution->addFlatUncertainty("xsec", 0.3);
				mc.push_back(contribution);
			}
		}
	}
	
	correlationBundle->addComponent(bundleTTbar);
	
	if(dilep) {
//		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-10To50" + infix + suffix, 762.45, "DY10to50"));
//		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50" + infix + suffix, 2950.0, "DYgt50"));
	}
	
	
	for(auto &contribution : mc) {
		contribution->addWeight("WEIGHT[0]");
		assembler->addContribution(contribution);
	}
	
	if(onlyTTF) {
		return;
	}
	
	for(auto &contribution : mcRare) {
		contribution->addWeight("WEIGHT[0]");
		assembler->addContribution(contribution);
		assembler->getBundle("Rare MC")->addComponent(contribution);
	}
	
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToTauTau" + infix + suffix, 1.2466, "GluGluToHToTauTau"));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToWWTo2LAndTau2Nu" + infix + suffix, 0.4437, "GluGluToHToWWTo2LAndTau2Nu"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToZZTo4L" + infix + suffix, 0.0053, "GluGluToHToZZTo4L"));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToTauTau" + infix + suffix, 0.0992, "VBF_HToTauTau"));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToWWTo2LAndTau2Nu" + infix + suffix, 0.0282, "VBF_HToWWTo2LAndTau2Nu"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToZZTo4L" + infix + suffix, 0.000423, "VBF_HToZZTo4L"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToTauTau" + infix + suffix, 0.0778, "WH_ZH_TTH_HToTauTau"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToWW" + infix + suffix, 0.254, "WH_ZH_TTH_HToWW"));
	
	for(auto &contribution : mcH) {
		contribution->addFlatUncertainty("xsecH", 0.5); // TODO correlations?
		contribution->addWeight("WEIGHT[0]");
		assembler->addContribution(contribution);
		assembler->getBundle("Higgs")->addComponent(contribution);
	}
	
	correlationBundle->addComponent(assembler->getBundle("Higgs"));
}

void setupBackgroundDD(Assembler* assembler, TString option = "", bool syst = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string body = getDataFileName();
	std::string suffix = ".root";
	
	////// Tracks
	PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTracks", false, "treeRfakeTracks", (option == "justTracks") ? kWhite : -1);
/*	fakeTracks->addWeight(
		"(Sum$(fakeRoleGOODELECTRONS) + Sum$(fakeRoleGOODMUONS) == 0)"
		" + (Sum$(fakeRoleGOODELECTRONS) > 0)"
			" * 4 * ("
				"(Min$(PTGOODELECTRONS) > 10 && Min$(PTGOODELECTRONS) < 15) * 0.09"
				" + (Min$(PTGOODELECTRONS) > 15 && Min$(PTGOODELECTRONS) < 20) * 0.26"
				" + (Min$(PTGOODELECTRONS) > 20 && Min$(PTGOODELECTRONS) < 25) * 0.58"
				" + (Min$(PTGOODELECTRONS) > 25)"
		")"
		" + (Sum$(fakeRoleGOODMUONS) > 0)"
			" * ("
				"(Min$(PTGOODMUONS) > 10 && Min$(PTGOODMUONS) < 15) * 1.13"
				" + (Min$(PTGOODMUONS) > 15)"
		")"
	);
*/	
	if(syst) {
		fakeTracks->addFlatUncertainty("trackFit", 0.17);
	}
	if(option != "noTracks" && option != "justTaus" && option != "justPhotons" && option != "fakeTaus2L") {
		assembler->getBundle("TrackFakes")->addComponent(fakeTracks);
		assembler->addContribution(fakeTracks);
	}
	
	////// Taus
	PhysicsContribution* fakeTaus = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTaus", false, "treeRfakeTaus");
	//fakeTaus->addWeight("Sum$(fakeRoleGOODTAUS > 0 && abs(TOTALISOGOODTAUS - 10.5) > 4.5) == 0"); // taken care of in the fake rate definition
	if(syst) {
		fakeTaus->addFlatUncertainty("tauFit", 0.05); // for HT > 200 GeV, it is that high
	}
	if(option != "noTaus" && option != "justTracks" && option != "justPhotons" && option != "fakeTaus2L") {
		assembler->getBundle("TauFakes")->addComponent(fakeTaus);
		assembler->addContribution(fakeTaus);
	}
	
	////// Taus (2L)
	PhysicsContribution* fakeTaus2L = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTaus2L", false, "treeRfakeTaus");
	//fakeTaus2L->addWeight("Sum$(fakeRoleGOODTAUS > 0 && abs(TOTALISOGOODTAUS - 10.5) > 4.5) == 0"); // taken care of in the fake rate definition
	if(syst) {
		fakeTaus2L->addFlatUncertainty("tauFit", 0.05); // for HT > 200 GeV, it is that high
	}
	if(option == "fakeTaus2L") {
		assembler->addContribution(fakeTaus2L);
	}
	
	////// Photons
	PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakePhotons", false, "treeRfakePhotons");
	if(syst) {
		fakePhotons->addFlatUncertainty("photonElFake", 0.15);
		//fakePhotons->addFlatUncertainty("photonFudge", 0.25);
		//fakePhotons->setEnsembleFakeRateParam(fakeTracks, "NPROMPTTRACKS7", "0*(x < [0]) + 1*(x > 2*[0]) + (x/[0] - 1)*(x >= [0] && x <= 2*[0])");
	}
	if(option != "noPhotons" && option != "justTracks" && option != "justTaus" && option != "fakeTaus2L") {
		assembler->getBundle("PhotonFakes")->addComponent(fakePhotons);
		assembler->addContribution(fakePhotons);
	}
}

void setupFakeRates(Assembler* assembler) {
	// We found that NGOODJETS and HT binning does not work very well; NPROMPTINCLUSIVETRACK7 binning does a good job at least in 0b regions.
	assembler->setFakeRate("nTrackFakeMuons",
		"(NGOODTAUS[0] == 0) * ("
			"0.0154"
			" * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	assembler->setFakeRate("nTrackFakeElectrons",
		"(NGOODTAUS[0] == 0) * ("
			"((NLEPTONS[0]==3&&NGOODELECTRONS[0]==1)*(0.006771 + 0.005532*NPROMPTNONISOINCLUSIVETRACKS7[0]) + (NLEPTONS[0]==3&&NGOODELECTRONS[0]==3)*(0.009287 + -0.001487*NPROMPTNONISOINCLUSIVETRACKS7[0])"
			"+ (NLEPTONS[0]!=3||!(NGOODELECTRONS[0]%2))*(0.007453 + 0.003052*NPROMPTNONISOINCLUSIVETRACKS7[0]))" // this is not the average of the above, but measured (because of relative fractions)
			" * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
		" * 2.4"
	);
	
	// mZ = 90 \pm 15
	assembler->setFakeRate("nTauFakeTaus",
		"Alt$(fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15, 0) * (" // w/o track/photon subtraction and with 200 binning
		//"Alt$(Sum$(fakeRoleGOODTAUS > 0 && abs(TOTALISOGOODTAUS - 10.5) > 4.5) == 0, 0) * (" // w/o track/photon subtraction and with 200 binning
			"(NBJETSCSVM[0] == 0) * ("
				"(NLEPTONS[0]==3&&NGOODMUONS[0]==0) * (0.2584 - 0.0003302 * HT[0])"
				" + (NLEPTONS[0]==3&&NGOODMUONS[0]==2) * (0.2504 - 0.0002508 * HT[0])"
				" + (NLEPTONS[0]!=3 || NGOODMUONS[0]==1) * (0.2544 - 0.0002905 * HT[0])"
			") + (NBJETSCSVM[0] > 0) * ("
				"(NLEPTONS[0]==3&&NGOODMUONS[0]==0) * (0.2100 - 0.0003165 * HT[0])"
				" + (NLEPTONS[0]==3&&NGOODMUONS[0]==2) * (0.2354 - 0.0002913 * HT[0])"
				" + (NLEPTONS[0]!=3 || NGOODMUONS[0]==1) * (0.2227 - 0.0003039 * HT[0])"
			")"
			//"(HT[0] <= 200) * 0.2275 + (HT[0] > 200) * 0.15"
		")"
		" * (nTauFakeTaus[0] == 1)" // disable multiple fake taus (overprediction for 2l+2tau channels because of double-counting from 2L and from 3L seeds)
	);
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
	// Looking at the AIC control region, we find that we should adjust the fake rate outside MLEPTONS = 75..100.
	assembler->setFakeRate("nPhotonFakeMuons",
		"(NGOODTAUS[0] == 0) * ("
			"0.025 / (1 + ONZ) * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
		" * Alt$(abs(goodMuonsDRgoodLeptons - 0.4) < 0.15 && fakeRoleGOODMUONS > 0, 0)" // only stuff emitted close to leptons
	);
	assembler->setFakeRate("nPhotonFakeElectrons",
		"(NGOODTAUS[0] == 0) * ("
			"0.045 / (1 + ONZ) * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
		" * Alt$(abs(goodElectronsDRgoodLeptons - 0.4) < 0.15 && fakeRoleGOODELECTRONS > 0, 0)" // only stuff emitted close to leptons
	);
}

#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TStyle.h>

TCanvas* makeNicePlot(TCanvas* c, const char* axistitle="")
{
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  c->cd();
  c->SetTopMargin(0.001);
  c->SetRightMargin(0.001);
  c->SetBottomMargin(0.001);
  c->SetLeftMargin(0.001);

  TPad* pad1 = (TPad*)c->GetPrimitive("pad1");
  pad1->SetTopMargin(0.05);
  pad1->SetBottomMargin(0.01);
  TPad* pad2 = (TPad*)c->GetPrimitive("pad2");
  pad2->SetBottomMargin(0.15);
  pad2->SetTopMargin(0.01);

  //pad1->RedrawAxis();
  pad2->RedrawAxis();


  TList* list = pad1->GetListOfPrimitives();
  cout<<"make nice plot "<<list->GetEntries()<<endl;
  for(int i = 0; i < list->GetEntries(); i++){
    TObject* obj = list->At(i);
    TString cname(obj->ClassName());
    if(cname.Contains("TH1")){
      ((TH1*)obj)->SetStats(false);
    }else if(cname == "TLegend"){
      ((TLegend*)obj)->SetFillColor(kWhite);
    }
  }

  TList* list2 = pad2->GetListOfPrimitives();
  for(int i = 0; i < list2->GetEntries(); i++){
    TObject* obj = list2->At(i);
    TString cname(obj->ClassName());
    if(cname.Contains("TH1")){
      float offset = ((TH1*)obj)->GetXaxis()->GetTitleOffset();
      float fontsize = ((TH1*)obj)->GetXaxis()->GetTitleSize();
      ((TH1*)obj)->GetXaxis()->SetTitleOffset(1.1*offset);
      ((TH1*)obj)->GetXaxis()->SetTitleFont(42);
      ((TH1*)obj)->GetXaxis()->SetTitleSize(1.1*fontsize);
      if(TString(axistitle) != "" && TString(((TH1*)obj)->GetXaxis()->GetTitle()) != ""){
        ((TH1*)obj)->GetXaxis()->SetTitle(axistitle);
      }
    }
  }

  c->cd();

  TLatex* latex = new TLatex;
  latex->SetNDC();
  latex->SetTextFont(61);
  latex->SetTextSize(0.04);
  latex->DrawLatex(0.16,0.915,"CMS Simulation");

  latex->SetTextSize(0.03);
  latex->SetTextFont(42);
  latex->DrawLatex(0.75,0.97,"20 fb^{-1} (13 TeV)");

  c->Update();
  pad1->Update();
  pad2->Update();

  return c;

}

void writeUncertainties(AssemblerProjection* projection, TString type) {
	cout << endl << "====== now printing uncertainties for contributions of type " << type << endl;
	if(!projection->has(type)) {
		cerr << "Projection does not have contributions of type " << type << endl;
		return;
	}
	
	auto uncertaintyNames = projection->getUncertaintyNames();
	for(int i = 1; i <= 5; ++i) {
		cout << endl;
		cout << "BIN " << i << endl;
		cout << "TOTAL:";
		cout << " " << projection->getBin(type, i);
		cout << " pm " << projection->getBinStat(type, i) << " pm " << projection->getBinSyst(type, i) << endl;
		for(const auto &uncertaintyName : uncertaintyNames) {
			cout << "uncertainty name: " << uncertaintyName << " " << projection->getBinSyst(type, i, uncertaintyName) << endl;
		}
		cout << endl;
		
		for(const auto &bundleName : projection->getBundleNames(type)) {
			cout << "bundleName: " << bundleName;
			cout << " " << projection->getBin(type, i, bundleName);
			cout << " pm " << projection->getBinStat(type, i, bundleName) << endl;
			for(const auto &uncertaintyName : uncertaintyNames) {
				cout << "uncertainty name: " << uncertaintyName << " " << projection->getBinSyst(type, i, uncertaintyName, bundleName) << endl;
			}
		}
	}
}
