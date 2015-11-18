#include <iostream>
#include <TH1.h>
#include <boost/algorithm/string.hpp>

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
	
	assembler->addBundle(new Bundle("background", "Fakes", false, 42));
	assembler->addBundle(new Bundle("background", "TrackFakes", false, kGreen - 3));
	assembler->addBundle(new Bundle("background", "PhotonFakes", false, kBlue - 7));
	assembler->addBundle(new Bundle("background", "TauFakes"));
	assembler->addBundle(new Bundle("background", "Higgs", false, 38));
	assembler->addBundle(new Bundle("background", "Rare MC", false, 33));
}

std::string getDataFileName() {
	return "20151116_data";
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
	
//	assembler->setDefaultBundle(presentationBundle);
//	assembler->getDefaultBundle()->print();
}

void setupData(Assembler* assembler, bool dilep = false, int fakeMode = 0) {
	dilep = true;
	std::string prefix = "/cms/thomassen/2015/Analysis/data/results/";
	std::string infix = dilep ? "" : ".3L";
	std::string body = getDataFileName();
	std::string suffix = ".root";
	
	PhysicsContribution* data = 0;
	
	if(fakeMode == 0) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2090, "2.09/fb@13TeV");
	} else if(fakeMode == 1) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2090, "2.09/fb@13TeV", false, "treeRfakeTracks");
	} else if(fakeMode == 2) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2090, "2.09/fb@13TeV", false, "treeRfakePhotons");
	} else if(fakeMode == 3) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2090, "2.09/fb@13TeV", false, "treeRfakeTaus");
	} else {
		cout << "unsure what to do";
		exit(1);
	}
	
	data->addWeight("TRIGGERACCEPT");
	
	std::vector<string> vetoFilenames = {
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/eventlist_DoubleEG_csc2015.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/eventlist_DoubleMuon_csc2015.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/eventlist_MuonEG_csc2015.txt",
	};
	
	for(auto vetoFilename : vetoFilenames) {
		cout << "adding vetos from " << vetoFilename << " ..." << flush;
		int nDuplicates = 0;
		ifstream ifile(vetoFilename);
		std::string line;
		while(getline(ifile, line)) {
			if(line.size() == 0 || line.at(0) == '#') {
				continue;
			}
			
			if(!data->addVetoEvent(line)) {
				++nDuplicates;
			}
		}
		ifile.close();
		cout << " (" << nDuplicates << " duplicates)" << endl;
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
//	dilep = true;
	std::string prefix = "/cms/thomassen/2015/Analysis/simulation/results/";
	std::string infix = ""; // dilep ? "" : ".3L";
	std::string suffix = ".simulation.root";
	
	double xsec_dy10to50 = 18610.;
	double xsec_dy50 = 6025.2;
		double dxsec_dy50 = sqrt(pow(39.6, 2) + pow(225, 2));
	// double xsec_ttS = 0; // MCM * BR: 670.3 * 0.322;
	double xsec_ttF = 87.31; // MCM * BR: 670.3 * 0.105;
		double dxsec_ttF = sqrt(pow(3.07, 2) + pow(3.68, 2));
		xsec_ttF *= 0.821; // normalization
		double xsec_ttF_fudge = 1;
	double xsec_tt = 831.76;
		double dxsec_tt = sqrt(pow(29.20 , 2) + pow(35.06, 2));
	double xsec_wz = 4.42965; // PHYS14: 43.871*(0.3257*0.10095);
	double xsec_zz = 1.212; // from MCM; // PHYS14: 1.218;
	double xsec_ttw = 0.2043; // PHYS14: 2.232
	double xsec_ttz = 0.2529; // PHYS14: 1.152
	double xsec_glugluHtoZZto4L = 0.01212;
	double xsec_vbf_HtoZZto4L = 0.001034;
	
	std::vector<PhysicsContribution*> mc;
	std::vector<PhysicsContribution*> mcH;
	std::vector<PhysicsContribution*> mcRare;
	
	Bundle* correlationBundle = new Bundle("background", "correlationBundle");
	assembler->addBundle(correlationBundle);
	
	PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZTo3LNu" + infix + suffix, xsec_wz, "WZ", false, "treeR", 39);
	//wz->addWeight("exp(-0.005 * PTMCZ[0]/sqrt(MMCZ[0]))", 1.038);
	//wz->addWeight("(NGOODJETS[0] == 0) * 1.053 + (NGOODJETS[0] == 1) * 0.85 + (NGOODJETS[0] == 2) * 1.15 + (NGOODJETS[0] > 2) * 1.19");
	//wz->addWeight("(NGOODJETS[0] <= 1) + (NGOODJETS[0] > 1) * (Alt$((PTGOODJETS[0] < 70) * 0.65 + (PTGOODJETS[0] >= 70 && PTGOODJETS[0] < 110) * 1.07 + (PTGOODJETS[0] >= 110 && PTGOODJETS[0] < 150) * 1.00 + (PTGOODJETS[0] >= 150) * 1.55, 0))");
	//wz->addWeight("1 + (NBJETSCSVM > 0) * 0.0"); // look with more data whether MC gets number of b's right
	//wz->addFlatUncertainty("normalizationWZ", 0.05);
	wz->setNominalWeight("genEventInfo_weight[0]");
	wz->addWeight("1.10"); // normalization
	correlationBundle->addComponent(wz);
	mc.push_back(wz);
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZTo4L" + infix + suffix, xsec_zz, "ZZ", false, "treeR", 30);
	//zz->addWeight("(NGOODJETS[0] == 0) * 1.084 + (NGOODJETS[0] == 1) * 0.75 + (NGOODJETS[0] == 2) * 0.333 + (NGOODJETS[0] > 2) * 1");
	zz->setNominalWeight("genEventInfo_weight[0]");
	zz->addWeight("1.35"); // normalization
	correlationBundle->addComponent(zz);
	mc.push_back(zz);
	
//	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "QCD_HT-100To250" + infix + suffix, 28730000*0.1178, "QCD_HT-100To250"));
//	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "QCD_HT-250To500" + infix + suffix, 670500*0.1685, "QCD_HT-250To500"));
//	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "QCD_HT-500To1000" + infix + suffix, 26740*0.2103, "QCD_HT-500To1000"));
//	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "QCD_HT-1000ToInf" + infix + suffix, 769.7*0.2358, "QCD_HT-1000ToInf"));
	
	PhysicsContribution* c = 0;
	
	c = new PhysicsContribution("backgroundMC", prefix + "TTWJetsToLNu" + infix + suffix, xsec_ttw, "TTW");
	c->setNominalWeight("genEventInfo_weight[0]");
	mcRare.push_back(c);
	
	c = new PhysicsContribution("backgroundMC", prefix + "TTZToLLNuNu" + infix + suffix, xsec_ttz, "TTZ");
	c->setNominalWeight("genEventInfo_weight[0]");
	mcRare.push_back(c);
	
//	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TBLL" + infix + suffix, xsec_tbz_tqz, "TBZ + TQZ"));
//	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWWJets" + infix + suffix, 0.002037, "TTWW"));
//	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WWWJets" + infix + suffix, 0.08217, "WWW"));
//	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WWZJets" + infix + suffix, 0.0633, "WWZ"));
//	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WZZJets" + infix + suffix, 0.019, "WZZ"));
//	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "ZZZNoGstarJets" + infix + suffix, 0.004587, "ZZZ"));
	
	//TString nJetWeight = "1 + (NGOODJETS[0] >= 4) * 0.05"; // Peter's numbers
	TString nJetWeight = "1";
	
	Bundle* bundleTTbar = new Bundle("background", "ttbar");
	assembler->addBundle(bundleTTbar);
	
	if(ttbar) {
/*		if(dilep) {
			PhysicsContribution* ttbarS = new PhysicsContribution("backgroundMC", prefix + "TTJetsSemiLeptonic" + infix + suffix, xsec_ttbar_semiLep, "TT_SemiL");
			ttbarS->addWeight(nJetWeight);
			mc.push_back(ttbarS);
			bundleTTbar->addComponent(ttbarS);
		}*/
		
		if(onlyTTF) {
			mc.clear();
		}
		
		//PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJets" + infix + suffix, xsec_tt, "TT", false, "treeR", -1, 0.01);
		PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu" + infix + suffix, xsec_ttF * xsec_ttF_fudge, "ttF", false, "treeR", kAzure + 1);
		ttbarF->setNominalWeight("genEventInfo_weight[0]");
//		ttbarF->addWeight("1.2 - 0.04 * NPROMPTNONISOINCLUSIVETRACKS7[0]");
//		ttbarF->addWeight(nJetWeight);
		ttbarF->addWeight("1 + (NLIGHTLEPTONS[0] >= 3) * 1.0");
		ttbarF->addFlatUncertainty("xsec_ttF", dxsec_ttF / xsec_ttF);
		//ttbarF->addFlatUncertainty("xsec_tt", dxsec_tt / xsec_tt);
//		ttbarF->addFlatUncertainty("fudge", 0.194);
		mc.push_back(ttbarF);
		bundleTTbar->addComponent(ttbarF);
		
		if(!dilep) {
			std::vector<PhysicsContribution*> ttbarFfake;
			
			PhysicsContribution* ttbarFfakeTracks = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu" + infix + suffix, xsec_ttF * xsec_ttF_fudge, "TT_FullLfakeTracks", true, "treeRfakeTracks", -1, 0.01);
			ttbarFfakeTracks->addWeight("1 + (NLIGHTLEPTONS[0] >= 3) * 1.0");
			//ttbarFfakeTracks->addFlatUncertainty("fudge", 0.194);
			ttbarFfake.push_back(ttbarFfakeTracks);
			assembler->getBundle("TrackFakes")->addComponent(ttbarFfakeTracks);
			
			PhysicsContribution* ttbarFfakePhotons = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu" + infix + suffix, xsec_ttF * xsec_ttF_fudge, "TT_FullLfakePhotons", true, "treeRfakePhotons", -1, 0.01);
			ttbarFfake.push_back(ttbarFfakePhotons);
			assembler->getBundle("PhotonFakes")->addComponent(ttbarFfakePhotons);
			
			//PhysicsContribution* ttbarFfakeTaus = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu" + infix + suffix, xsec_ttF * xsec_ttF_fudge, "TT_FullLfakeTaus", true, "treeRfakeTaus", -1, 0.01);
			//ttbarFfake.push_back(ttbarFfakeTaus);
			//assembler->getBundle("TauFakes")->addComponent(ttbarFfakeTaus);
			
			for(auto &contribution : ttbarFfake) {
				contribution->setNominalWeight("genEventInfo_weight[0]");
				//contribution->addWeight("1.2 - 0.04 * NPROMPTNONISOINCLUSIVETRACKS7[0]");
				//contribution->addWeight(nJetWeight);
				contribution->addWeight("nTrackFakeElectrons + nTrackFakeMuons + nPhotonFakeElectrons + nPhotonFakeMuons == 1"); // + nTauFakeTaus == 1");
				mc.push_back(contribution);
			}
		}
	}
	
	correlationBundle->addComponent(bundleTTbar);
	
	if(dilep) {
		PhysicsContribution* c = 0;
		
		c = new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-10to50" + infix + suffix, xsec_dy10to50, "DY10to50", false, "treeR", 46);
		c->setNominalWeight("genEventInfo_weight[0]");
		c->addWeight("(NGOODJETS[0] == 0) * 1.4 + (NGOODJETS[0] == 1) * 1.3 + (NGOODJETS[0] == 2) * 1.3 + (NGOODJETS[0] == 3) * 1.3 + (NGOODJETS[0] == 4) * 1.38 + (NGOODJETS[0] == 5) * 1.6 + (NGOODJETS[0] > 4) * 1.45");
		mc.push_back(c);
		
		c = new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50" + infix + suffix, xsec_dy50, "DY50", false, "treeR", 46);
		c->addFlatUncertainty("xsec_dy50", dxsec_dy50 / xsec_dy50);
		c->setNominalWeight("genEventInfo_weight[0]");
		c->addWeight("(NGOODJETS[0] == 0) * 1.4 + (NGOODJETS[0] == 1) * 1.3 + (NGOODJETS[0] == 2) * 1.3 + (NGOODJETS[0] == 3) * 1.3 + (NGOODJETS[0] == 4) * 1.38 + (NGOODJETS[0] == 5) * 1.6 + (NGOODJETS[0] > 5) * 1.45");
		mc.push_back(c);
	}
	
	
	for(auto &contribution : mc) {
		contribution->addWeight("WEIGHT[0]");
//		contribution->addWeight("TRIGGERACCEPT");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		assembler->addContribution(contribution);
	}
	
	if(onlyTTF) {
		return;
	}
	
	for(auto &contribution : mcRare) {
		contribution->addWeight("WEIGHT[0]");
//		contribution->addWeight("TRIGGERACCEPT");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		contribution->addFlatUncertainty("lumi", 0.12); // as of 2015-11-16 https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2544/1/1.html
		assembler->addContribution(contribution);
		assembler->getBundle("Rare MC")->addComponent(contribution);
	}
	
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToTauTau" + infix + suffix, 1.2466, "GluGluToHToTauTau"));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToWWTo2LAndTau2Nu" + infix + suffix, 0.4437, "GluGluToHToWWTo2LAndTau2Nu"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluHToZZTo4L_M125" + infix + suffix, xsec_glugluHtoZZto4L, "GluGluHToZZTo4L"));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToTauTau" + infix + suffix, 0.0992, "VBF_HToTauTau"));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToWWTo2LAndTau2Nu" + infix + suffix, 0.0282, "VBF_HToWWTo2LAndTau2Nu"));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToZZTo4L_M125" + infix + suffix, xsec_vbf_HtoZZto4L, "VBF_HToZZTo4L"));
//?	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToTauTau" + infix + suffix, 0.0778, "WH_ZH_TTH_HToTauTau"));
//?	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToWW" + infix + suffix, 0.254, "WH_ZH_TTH_HToWW"));
	
	for(auto &contribution : mcH) {
		//contribution->addFlatUncertainty("xsecH", 0.5); // TODO correlations?
		contribution->addWeight("WEIGHT[0]");
//		contribution->addWeight("TRIGGERACCEPT");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		contribution->addFlatUncertainty("lumi", 0.12); // as of 2015-11-16 https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2544/1/1.html
		assembler->addContribution(contribution);
		assembler->getBundle("Higgs")->addComponent(contribution);
	}
	
	correlationBundle->addComponent(assembler->getBundle("Higgs"));
}

void setupBackgroundDD(Assembler* assembler, TString option = "", bool syst = false) {
	std::string prefix = "/cms/thomassen/2015/Analysis/data/results/";
	std::string body = getDataFileName();
	std::string suffix = ".root";
	
	////// Tracks
	PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTracks", false, "treeRfakeTracks", (option == "justTracks") ? kWhite : -1);
	fakeTracks->addWeight("TRIGGERACCEPT");
	fakeTracks->addWeight(
		"(Sum$(fakeRoleGOODELECTRONS) > 0)"
			" * ( (Min$(PTGOODELECTRONS) < 100) * (-0.23 + 0.07 * Min$(PTGOODELECTRONS)) + !(Min$(PTGOODELECTRONS) < 100) )"
		" + (Sum$(fakeRoleGOODMUONS) > 0)"
			" * ( (Min$(PTGOODMUONS) < 25) * (0.00 + 0.07 * Min$(PTGOODMUONS)) + !(Min$(PTGOODMUONS) < 25) )"
	);
	if(syst) {
		fakeTracks->addFlatUncertainty("trackFit", 0.21);
	}
	if(option != "noTracks" && option != "justTaus" && option != "justPhotons" && option != "fakeTaus2L") {
		assembler->getBundle("TrackFakes")->addComponent(fakeTracks);
		assembler->addContribution(fakeTracks);
	}
	
/*	////// Taus
	PhysicsContribution* fakeTaus = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTaus", false, "treeRfakeTaus");
	fakeTaus->addWeight("TRIGGERACCEPT");
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
	fakeTaus2L->addWeight("TRIGGERACCEPT");
	//fakeTaus2L->addWeight("Sum$(fakeRoleGOODTAUS > 0 && abs(TOTALISOGOODTAUS - 10.5) > 4.5) == 0"); // taken care of in the fake rate definition
	if(syst) {
		fakeTaus2L->addFlatUncertainty("tauFit", 0.05); // for HT > 200 GeV, it is that high
	}
	if(option == "fakeTaus2L") {
		assembler->addContribution(fakeTaus2L);
	}*/
	
	////// Photons
	PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakePhotons", false, "treeRfakePhotons");
	fakePhotons->addWeight("TRIGGERACCEPT");
	if(syst) {
		//fakePhotons->addFlatUncertainty("photonElFake", 0.15);
		//fakePhotons->addFlatUncertainty("photonFudge", 0.25);
	}
	//fakePhotons->addFlatUncertainty("photonDR", 0.33);
	if(option != "noPhotons" && option != "justTracks" && option != "justTaus" && option != "fakeTaus2L") {
		assembler->getBundle("PhotonFakes")->addComponent(fakePhotons);
		assembler->addContribution(fakePhotons);
	}
}

void setupFakeRates(Assembler* assembler) {
	// We found that NGOODJETS and HT binning does not work very well; NPROMPTINCLUSIVETRACK7 binning does a good job at least in 0b regions.
	assembler->setFakeRate("nTrackFakeMuons",
		"(NGOODTAUS[0] == 0) * ("
			"((NLEPTONS[0]==3&&NGOODMUONS[0]==1)*(0.02257 + -0.004068*NPROMPTNONISOINCLUSIVETRACKS7[0])*0.764"
			" + (NLEPTONS[0]==3&&NGOODMUONS[0]==3)*(0.01265 + 0.0004019*NPROMPTNONISOINCLUSIVETRACKS7[0])*0.96"
			" + (NLEPTONS[0]!=3||!(NGOODMUONS[0]%2))*(0.01761 + -0.00183305*NPROMPTNONISOINCLUSIVETRACKS7[0]))" // this is currently the average of the above, but should be measured (because of relative fractions)
			" * (1 + 1.9 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	assembler->setFakeRate("nTrackFakeElectrons",
		"(NGOODTAUS[0] == 0) * ("
			"((NLEPTONS[0]==3&&NGOODELECTRONS[0]==1)*(0.01901 + -0.0006741*NPROMPTNONISOINCLUSIVETRACKS7[0])*0.82"
			" + (NLEPTONS[0]==3&&NGOODELECTRONS[0]==3)*(0.0193 + -0.002522*NPROMPTNONISOINCLUSIVETRACKS7[0])*0.99"
			" + (NLEPTONS[0]!=3||!(NGOODELECTRONS[0]%2))*(0.019155 + -0.00159805*NPROMPTNONISOINCLUSIVETRACKS7[0]))" // this is currently the average of the above, but should be measured (because of relative fractions)
			" * (1 + 1.9 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	
	// mZ = 90 \pm 15
/*	assembler->setFakeRate("nTauFakeTaus",
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
	);*/
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
	// Looking at the AIC control region, we find that we should adjust the fake rate outside MLEPTONS = 75..100.
	assembler->setFakeRate("nPhotonFakeMuons",
		"(NGOODTAUS[0] == 0) * ("
//			"(NLEPTONS[0]==3)*0.0175"
			"((NLEPTONS[0]==3&&NGOODMUONS[0]==1)*0.0160"
			" + (NLEPTONS[0]==3&&NGOODMUONS[0]==3)*0.0105"
			" + (NLEPTONS[0]!=3||!(NGOODMUONS[0]%2))*0.014)" // this is currently a wild guess, but should be measured (because of relative fractions)
//			" * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		")"
		" * Alt$(Sum$(abs(goodMuonsDRgoodLeptons - 0.45) < 0.15 && fakeRoleGOODMUONS > 0) > 0, 0)" // only stuff emitted close to leptons
		" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	assembler->setFakeRate("nPhotonFakeElectrons",
		"(NGOODTAUS[0] == 0) * ("
//			"(NLEPTONS[0]==3)*0.035"
			"((NLEPTONS[0]==3&&NGOODELECTRONS[0]==1)*0.035"
			" + (NLEPTONS[0]==3&&NGOODELECTRONS[0]==3)*0.045"
			" + (NLEPTONS[0]!=3||!(NGOODELECTRONS[0]%2))*0.040)" // this is currently a wild guess, but should be measured (because of relative fractions)
//			" * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		")"
		" * Alt$(Sum$(abs(goodElectronsDRgoodLeptons - 0.45) < 0.15 && fakeRoleGOODELECTRONS > 0) > 0, 0)" // only stuff emitted close to leptons
		" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
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
  pad1->SetTopMargin(0.06);
  //pad1->SetBottomMargin(0.01);
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

  for(auto pad : {pad1, pad2}) {
	  TList* list2 = pad->GetListOfPrimitives();
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
  }

  c->cd();

  TLatex* latex = new TLatex;
  latex->SetNDC();
  latex->SetTextFont(61);
  latex->SetTextSize(0.04);	
  latex->DrawLatex(0.16,0.885,"CMS Preliminary");

  latex->SetTextSize(0.03);
  latex->SetTextFont(42);
  latex->DrawLatex(0.75,0.96,"1.56 fb^{-1} (13 TeV)");

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
