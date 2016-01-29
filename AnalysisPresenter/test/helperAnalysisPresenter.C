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

void applyUncertainties(Assembler* assembler, PhysicsContribution* contribution) {
	if(!assembler->getMode("fullPrecision")) {
		return;
	}
	
	contribution->addRelativeUncertainty("lepIDTrigger", "0.03");
	if(contribution->isMC() && !assembler->getMode("noSystVariations")) {
		// See https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
		contribution->addVariation("METunc", make_pair("MET", "0.5 * (18.5*sqrt(2)) * sqrt(-log(rndm())) * cos(6.2831853 * rndm()) + _MET"));
	}
}

void init(Assembler* assembler) {
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
	
	assembler->addBundle(new Bundle("background", "Fakes", false, 42));
	assembler->addBundle(new Bundle("background", "presentationBundle"));
	assembler->addBundle(new Bundle("background", "fakePresentationBundle"));
	
	assembler->addBundle(new Bundle("background", "TrackFakes", false, kGreen - 3));
	assembler->addBundle(new Bundle("background", "PhotonFakes", false, kBlue - 7));
	
	assembler->addBundle(new Bundle("background", "WZ", false, 39));
	assembler->addBundle(new Bundle("background", "Higgs", false, 38));
	assembler->addBundle(new Bundle("background", "Rare MC", false, 33));
}

std::string getDataFileName() {
	return "20151203_data";
}

void prepare(Assembler* assembler) {
	Bundle* fakeBundle = assembler->getBundle("Fakes");
	for(const auto &bundleName : {"TrackFakes", "PhotonFakes"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			fakeBundle->addComponent(bundle);
		}
	}
	
	Bundle* presentationBundle = assembler->getBundle("presentationBundle");
	for(const auto &bundleName : {"Fakes", "WZ", "Higgs", "Rare MC"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			presentationBundle->addComponent(bundle);
		}
	}
	
	Bundle* fakePresentationBundle = assembler->getBundle("fakePresentationBundle");
	for(const auto &bundleName : {"TrackFakes", "PhotonFakes", "WZ", "Higgs", "Rare MC"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			fakePresentationBundle->addComponent(bundle);
		}
	}
	
	if(assembler->getDefaultBundle()) {
		assembler->getDefaultBundle()->print();
	}
}

void setupData(Assembler* assembler, bool dilep = false, int fakeMode = 0, bool applyEventVetos = false) {
	std::string prefix = "/cms/thomassen/2015/Analysis/data/results/";
	std::string infix = dilep ? "" : ".3L";
	std::string body = getDataFileName();
	std::string suffix = ".root";
	
	PhysicsContribution* data = 0;
	
	if(fakeMode == 0) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2138, "2.14/fb@13TeV");
	} else if(fakeMode == 1) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2138, "2.14/fb@13TeV", false, "treeRfakeTracks");
	} else if(fakeMode == 2) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2138, "2.14/fb@13TeV", false, "treeRfakePhotons");
	} else if(fakeMode == 3) {
		data = new PhysicsContribution("data", prefix + body + infix + suffix, 2138, "2.14/fb@13TeV", false, "treeRfakeTaus");
	} else {
		cout << "unsure what to do";
		exit(1);
	}
	
	data->addWeight("TRIGGERACCEPT");
	
	std::vector<string> vetoFilenames = {
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/csc2015_Dec01.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/ecalscn1043093_Dec01.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/badResolutionTrack_Jan13.txt",
		"/cms/thomassen/2015/Analysis/CMSSW/src/RutgersIAF/AnalysisPresenter/test/veto/muonBadTrack_Jan13.txt",
	};
	if(!applyEventVetos) {
		vetoFilenames.clear();
	}
	
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
	
	// Pile-up weights
	cout << "Notice: Applying pileup weights" << endl;
	TFile* f = new TFile("/cms/thomassen/2015/Analysis/data/DataPileup_2015-12-18.root");
	if(f->IsZombie()) {
		throw std::runtime_error("couldn't open pileup file");
	}
	TH1D* hPileup = (TH1D*)f->Get("pileup");
	TH1D* hPileupUnc = 0;
	
	if(assembler->getMode("fullPrecision")) {
		TFile* fUnc = new TFile("/cms/thomassen/2015/Analysis/data/DataPileup+5%_2015-12-18.root");
		if(fUnc->IsZombie()) {
			throw std::runtime_error("couldn't open pileup uncertainty file");
		}
		hPileupUnc = (TH1D*)fUnc->Get("pileup");
	} else {
		cout << "Notice: Not applying lepID, MET smearing and pile-up uncertainties. Set fullPrecision mode to do so." << endl;
	}
	assembler->setPileupHistogram(hPileup, hPileupUnc);
}

void setupDataSingle(Assembler* assembler, bool fake = false, bool dilep = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".root";
	
	PhysicsContribution* data = 0;
	
	assembler->addContribution(data);
}

void setupBackgroundMC(Assembler* assembler, bool dilep = false, bool ttbar = true, bool onlyTTF = false) {
	std::string prefix = "/cms/thomassen/2015/Analysis/simulation/results/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".simulation.root";
	
	double xsec_dy10to50 = 18610. * 1.32;
	double xsec_dy50 = 6025.2 * 1.32;
		double dxsec_dy50 = sqrt(pow(39.6, 2) + pow(225, 2));
	// double xsec_ttS = 0; // MCM * BR: 670.3 * 0.322;
	double xsec_ttF = 87.31; // MCM * BR: 670.3 * 0.105;
		double dxsec_ttF = sqrt(pow(3.07, 2) + pow(3.68, 2));
	double xsec_tt = 831.76;
		double dxsec_tt = sqrt(pow(29.20 , 2) + pow(35.06, 2));
	double xsec_WZTo3LNu = 4.42965; // PHYS14: 43.871*(0.3257*0.10095);
	double xsec_WZJets = 5.263;
	double xsec_zz = 1.212; // from MCM; // PHYS14: 1.218;
	double xsec_ttw = 0.2043; // PHYS14: 2.232
	double xsec_ttz = 0.2529; // PHYS14: 1.152
	double xsec_glugluHtoZZto4L = 0.01212;
	double xsec_vbf_HtoZZto4L = 0.001034;
	double xsec_WWZ = 0.1651;
	double xsec_WZZ = 0.05565;
	double xsec_ZZZ = 0.01398;
	
	std::vector<PhysicsContribution*> mc;
	std::vector<PhysicsContribution*> mcH;
	std::vector<PhysicsContribution*> mcRare;
	
	PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZTo3LNu" + infix + suffix, xsec_WZTo3LNu, "WZTo3LNu", false, "treeR", -1, 0);
	wz->setNominalWeight("genEventInfo_weight[0]");
	wz->addWeight("!ONZ");
	wz->addWeight("1.015"); // normalization
	if(!assembler->getMode("noWZsystematics")) {
		wz->addFlatUncertainty("normalizationWZ", 0.015); // size of scale factor (< statistical)
		wz->addFlatUncertainty("trackFakes", -0.0174); // based on 14% variation of fakeTracks in WZ normalization region
		wz->addFlatUncertainty("photonFakes", -0.0082); // based on 52% variation of fakePhotons in WZ normalization region
	}
	assembler->getBundle("WZ")->addComponent(wz);
	mc.push_back(wz);
	
	wz = new PhysicsContribution("backgroundMC", prefix + "WZJets" + infix + suffix, xsec_WZJets, "WZJets", false, "treeR", -1, 0);
	wz->setNominalWeight("genEventInfo_weight[0]");
	wz->addWeight("ONZ");
	if(!assembler->getMode("noWZsystematics")) {
		wz->addFlatUncertainty("normalizationWZ", 0.073); // statistical
		wz->addFlatUncertainty("trackFakes", -0.0174); // based on 14% variation of fakeTracks in WZ normalization region
		wz->addFlatUncertainty("photonFakes", -0.0082); // based on 52% variation of fakePhotons in WZ normalization region
	}
	wz->addWeight("1.372"); // normalization
	assembler->getBundle("WZ")->addComponent(wz);
	mc.push_back(wz);
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZTo4L" + infix + suffix, xsec_zz, "ZZ", false, "treeR", 30, assembler->getMode("fullPrecision") ? 0 : 0.01);
	zz->setNominalWeight("genEventInfo_weight[0]");
	zz->addWeight("1.256"); // normalization
	if(!assembler->getMode("noZZsystematics")) zz->addFlatUncertainty("normalizationZZ", 0.166); // statistical
	mc.push_back(zz);
	
	PhysicsContribution* c = 0;
	
	c = new PhysicsContribution("backgroundMC", prefix + "TTWJetsToLNu" + infix + suffix, xsec_ttw, "TTW", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01);
	c->setNominalWeight("genEventInfo_weight[0]");
	mcRare.push_back(c);
	
	c = new PhysicsContribution("backgroundMC", prefix + "TTZToLLNuNu" + infix + suffix, xsec_ttz, "TTZ", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01);
	c->setNominalWeight("genEventInfo_weight[0]");
	mcRare.push_back(c);
	
//	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TBLL" + infix + suffix, xsec_tbz_tqz, "TBZ + TQZ"));
//	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWWJets" + infix + suffix, 0.002037, "TTWW"));
//	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WWWJets" + infix + suffix, 0.08217, "WWW"));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WWZ" + infix + suffix, xsec_WWZ, "WWZ", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "WZZ" + infix + suffix, xsec_WZZ, "WZZ", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "ZZZ" + infix + suffix, xsec_ZZZ, "ZZZ", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	
	TString nJetWeight = "1 + (NGOODJETS[0] == 1) * 0.01 + (NGOODJETS[0] == 2) * 0.01 + (NGOODJETS[0] == 3) * 0.07 + (NGOODJETS[0] == 4) * -0.07 + (NGOODJETS[0] == 5) * -0.22 + (NGOODJETS[0] > 5) * -0.34";
	TString normalization = "0.805";
//	nJetWeight = "1";
	
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
		
		PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu" + infix + suffix, xsec_ttF, "ttF", false, "treeR", kAzure + 1, assembler->getMode("fullPrecision") ? 0 : 0.01);
		ttbarF->setNominalWeight("genEventInfo_weight[0]");
		ttbarF->addWeight(normalization); // normalization
		ttbarF->addWeight(nJetWeight);
		if(!assembler->getMode("noTTsystematics")) ttbarF->addRelativeUncertainty("ttbarNJet", TString::Format("1 - 1/(%s)", nJetWeight.Data()));
		ttbarF->addWeight("1 + (NLIGHTLEPTONS[0] >= 3) * 0.5");
		//ttbarF->addFlatUncertainty("xsec_ttF", dxsec_ttF / xsec_ttF);
		//if(!assembler->getMode("noTTsystematics")) ttbarF->addFlatUncertainty("xsec_tt", dxsec_tt / xsec_tt);
		if(!assembler->getMode("noTTsystematics")) ttbarF->addFlatUncertainty("ttbarFudge", 0.5);
		mc.push_back(ttbarF);
		bundleTTbar->addComponent(ttbarF);
		
		if(!dilep) {
			std::vector<PhysicsContribution*> ttbarFfake;
			
			PhysicsContribution* ttbarFfakeTracks = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu" + infix + suffix, xsec_ttF, "TT_FullLfakeTracks", true, "treeRfakeTracks", -1, assembler->getMode("fullPrecision") ? 0 : 0.01);
			ttbarFfakeTracks->addWeight("1 + (NLIGHTLEPTONS[0] >= 3) * 0.5");
			if(!assembler->getMode("noTTsystematics")) ttbarFfakeTracks->addFlatUncertainty("ttbarFudge", 0.5);
			ttbarFfake.push_back(ttbarFfakeTracks);
			assembler->getBundle("TrackFakes")->addComponent(ttbarFfakeTracks);
			
			/* 
			 * We don't assume the ttbar MC to model AIC's correctly. We therefore decided to get the estimate from data, and veto leptons from photons in the MC. Thus, we don't need MC subtraction in the data-driven method.
			 * 
			PhysicsContribution* ttbarFfakePhotons = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu" + infix + suffix, xsec_ttF, "TT_FullLfakePhotons", true, "treeRfakePhotons", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
			ttbarFfake.push_back(ttbarFfakePhotons);
			assembler->getBundle("PhotonFakes")->addComponent(ttbarFfakePhotons);
			*/
			
			for(auto &contribution : ttbarFfake) {
				contribution->setNominalWeight("genEventInfo_weight[0]");
				contribution->addWeight(nJetWeight);
				if(!assembler->getMode("noTTsystematics")) contribution->addRelativeUncertainty("ttbarNJet", TString::Format("1 - 1/(%s)", nJetWeight.Data()));
				contribution->addWeight("nTrackFakeElectrons + nTrackFakeMuons + nPhotonFakeElectrons + nPhotonFakeMuons == 1"); // + nTauFakeTaus == 1");
				mc.push_back(contribution);
			}
		}
	}
	
	if(dilep) {
		PhysicsContribution* c = 0;
		
		c = new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-10to50" + infix + suffix, xsec_dy10to50, "DY10to50", false, "treeR", 46, assembler->getMode("fullPrecision") ? 0 : 0.01);
		c->setNominalWeight("genEventInfo_weight[0]");
		c->addWeight("(NGOODJETS[0] == 0) * 1.0 + (NGOODJETS[0] == 1) * 0.93 + (NGOODJETS[0] == 2) * 0.92 + (NGOODJETS[0] == 3) * 0.93 + (NGOODJETS[0] == 4) * 1.09 + (NGOODJETS[0] == 5) * 1.27 + (NGOODJETS[0] == 6) * 1.61 + (NGOODJETS[0] > 6) * 1");
		mc.push_back(c);
		
		c = new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50" + infix + suffix, xsec_dy50, "DY50", false, "treeR", 46, assembler->getMode("fullPrecision") ? 0 : 0.01);
		c->addFlatUncertainty("xsec_dy50", dxsec_dy50 / xsec_dy50);
		c->setNominalWeight("genEventInfo_weight[0]");
		c->addWeight("(NGOODJETS[0] == 0) * 1.0 + (NGOODJETS[0] == 1) * 0.93 + (NGOODJETS[0] == 2) * 0.92 + (NGOODJETS[0] == 3) * 0.93 + (NGOODJETS[0] == 4) * 1.09 + (NGOODJETS[0] == 5) * 1.27 + (NGOODJETS[0] == 6) * 1.61 + (NGOODJETS[0] > 6) * 1");
		mc.push_back(c);
	}
	
	for(auto &contribution : mc) {
		contribution->addWeight("WEIGHT[0]");
//		contribution->addWeight("TRIGGERACCEPT");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		applyUncertainties(assembler, contribution);
		assembler->addContribution(contribution);
	}
	
	if(onlyTTF) {
		return;
	}
	
	for(auto &contribution : mcRare) {
		contribution->addWeight("WEIGHT[0]");
//		contribution->addWeight("TRIGGERACCEPT");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		applyUncertainties(assembler, contribution);
		contribution->addFlatUncertainty("lumi", 0.046); // as of 2015-11-16 https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2544/1/1.html
		contribution->addFlatUncertainty("xsecRare", 0.5);
		assembler->addContribution(contribution);
		assembler->getBundle("Rare MC")->addComponent(contribution);
	}
	
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToTauTau" + infix + suffix, 1.2466, "GluGluToHToTauTau", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToWWTo2LAndTau2Nu" + infix + suffix, 0.4437, "GluGluToHToWWTo2LAndTau2Nu", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluHToZZTo4L_M125" + infix + suffix, xsec_glugluHtoZZto4L, "GluGluHToZZTo4L", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToTauTau" + infix + suffix, 0.0992, "VBF_HToTauTau", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
//	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToWWTo2LAndTau2Nu" + infix + suffix, 0.0282, "VBF_HToWWTo2LAndTau2Nu", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToZZTo4L_M125" + infix + suffix, xsec_vbf_HtoZZto4L, "VBF_HToZZTo4L", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
//?	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToTauTau" + infix + suffix, 0.0778, "WH_ZH_TTH_HToTauTau", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
//?	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToWW" + infix + suffix, 0.254, "WH_ZH_TTH_HToWW", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	
	for(auto &contribution : mcH) {
		//contribution->addFlatUncertainty("xsecH", 0.5); // TODO correlations?
		contribution->addWeight("WEIGHT[0]");
//		contribution->addWeight("TRIGGERACCEPT");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		applyUncertainties(assembler, contribution);
		contribution->addFlatUncertainty("lumi", 0.046); // as of 2015-11-16 https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2544/1/1.html
		contribution->addFlatUncertainty("xsecHiggs", 0.5);
		assembler->addContribution(contribution);
		assembler->getBundle("Higgs")->addComponent(contribution);
	}
}

void setupBackgroundDD(Assembler* assembler, TString option = "", bool syst = true) {
	std::string prefix = "/cms/thomassen/2015/Analysis/data/results/";
	std::string body = getDataFileName();
	std::string suffix = ".3L.root";
	
	TString nVertexWeight = "0.773 + 0.0218 * NVERTICES[0]";
	
	////// Tracks
	PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTracks", false, "treeRfakeTracks", (option == "justTracks") ? kWhite : -1);
	fakeTracks->addWeight("TRIGGERACCEPT");
	fakeTracks->addWeight(
		"(Sum$(fakeRoleGOODELECTRONS) > 0)"
			" * ( (Min$(PTGOODELECTRONS) < 100) * (-0.23 + 0.07 * Min$(PTGOODELECTRONS)) + !(Min$(PTGOODELECTRONS) < 100) )"
		" + (Sum$(fakeRoleGOODMUONS) > 0)"
			" * ( (Min$(PTGOODMUONS) < 25) * (0.00 + 0.07 * Min$(PTGOODMUONS)) + !(Min$(PTGOODMUONS) < 25) )"
	);
	fakeTracks->addWeight(nVertexWeight);
	fakeTracks->addRelativeUncertainty("fakePileupWeight", TString::Format("1 - 1/(%s)", nVertexWeight.Data()));
	applyUncertainties(assembler, fakeTracks);
	if(syst && !assembler->getMode("noTrackSystematics")) {
		//fakeTracks->addFlatUncertainty("trackFakeRateFit", 0.06);
		//fakeTracks->addFlatUncertainty("trackPtFit", 0.10);
		fakeTracks->addFlatUncertainty("trackFakes", 0.14);
		fakeTracks->addFlatUncertainty("photonFakes", -0.080); // based on 52% variation of photon contribution in track fake rate measurement region
		fakeTracks->addFlatUncertainty("normalizationWZ", -0.033); // based on 7.3% variation of WZ in track fake rate measurement region
	}
	if(option != "noTracks" && option != "justTaus" && option != "justPhotons" && option != "fakeTaus2L") {
		assembler->getBundle("TrackFakes")->addComponent(fakeTracks);
		assembler->addContribution(fakeTracks);
	}
	
	////// Photons
	PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakePhotons", false, "treeRfakePhotons");
	fakePhotons->addWeight("TRIGGERACCEPT");
	fakePhotons->addWeight(nVertexWeight);
	fakePhotons->addRelativeUncertainty("fakePileupWeight", TString::Format("1 - 1/(%s)", nVertexWeight.Data()));
	applyUncertainties(assembler, fakePhotons);
	if(syst && !assembler->getMode("noPhotonSystematics")) {
		fakePhotons->addFlatUncertainty("photonFakes", 0.52); // due to photonDR
		fakePhotons->addFlatUncertainty("trackFakes", -0.056); // based on 14% variation of track contribution in photon fake rate measurement region
		fakePhotons->addFlatUncertainty("normalizationWZ", -0.0018); // based on 7.3% variation of WZ in photon fake rate measurement region
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
			"0.0156"
//			" * (1 + 1.9 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	assembler->setFakeRate("nTrackFakeElectrons",
		"(NGOODTAUS[0] == 0) * ("
			"0.0156"
//			" * (1 + 1.9 * (NBJETSCSVM[0] > 0))"
		")"
		" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
	// Looking at the AIC control region, we find that we should adjust the fake rate outside MLEPTONS = 75..100.
	assembler->setFakeRate("nPhotonFakeMuons",
		"(NGOODTAUS[0] == 0) * ("
//			"(NLIGHTLEPTONS[0]==3)*0.0175"
			"((NLIGHTLEPTONS[0]==3&&NGOODMUONS[0]==1)*0.0160"
			" + (NLIGHTLEPTONS[0]==3&&NGOODMUONS[0]==3)*0.0105"
			" + (NLIGHTLEPTONS[0]!=3||!(NGOODMUONS[0]%2))*0.014)" // this is currently a wild guess, but should be measured (because of relative fractions)
			" * (1 + 0.8 * (abs(MLIGHTLEPTONS[0]-87.5) > 12.5))"
//			" * (1 + 1.2 * (NBJETSCSVM[0] > 0))"
		")"
		" * Alt$(Sum$(abs(goodMuonsDRgoodLeptons - 0.45) < 0.15 && fakeRoleGOODMUONS > 0) > 0, 0)" // only stuff emitted close to leptons
		" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
	);
	assembler->setFakeRate("nPhotonFakeElectrons",
		"(NGOODTAUS[0] == 0) * ("
//			"(NLIGHTLEPTONS[0]==3)*0.035"
			"((NLIGHTLEPTONS[0]==3&&NGOODELECTRONS[0]==1)*0.035"
			" + (NLIGHTLEPTONS[0]==3&&NGOODELECTRONS[0]==3)*0.045"
			" + (NLIGHTLEPTONS[0]!=3||!(NGOODELECTRONS[0]%2))*0.040)" // this is currently a wild guess, but should be measured (because of relative fractions)
			" * (1 + 0.8 * (abs(MLIGHTLEPTONS[0]-87.5) > 12.5))"
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

  pad1->cd();
  TList* list = pad1->GetListOfPrimitives();
  cout<<"make nice plot "<<list->GetEntries()<<endl;
  TH1* h = 0;
  TLegend* legend = 0;
  for(int i = 0; i < list->GetEntries(); i++){
    TObject* obj = list->At(i);
    TString cname(obj->ClassName());
    if(cname.Contains("TH1")){
      h = ((TH1*)obj);
      ((TH1*)obj)->SetStats(false);
    } else if(cname == "TLegend") {
      legend = ((TLegend*)obj);
    }
  }
  legend->SetFillColor(kWhite);
  double max = h->GetMaximum();
  double min = h->GetMinimum();
  //legend->SetY1(min + 0.5 * (max - min));
  //legend->SetY2(min + 0.9 * (max - min));
  legend->SetY1(0.5);
  legend->SetY2(2.1);

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
  latex->DrawLatex(0.35,0.885,"CMS Preliminary");

  latex->SetTextSize(0.03);
  latex->SetTextFont(42);
  latex->DrawLatex(0.75,0.96,"2.1 fb^{-1} (13 TeV)");

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


void SaveHistograms(TCanvas* c, TString outfilename)
{
  c->cd();
  TPad* pad1 = (TPad*)c->GetPrimitive("pad1");
  TPad* pad2 = (TPad*)c->GetPrimitive("pad2");
  
  pad1->cd();
  TList* list = pad1->GetListOfPrimitives();
  TH1* h = 0;
  THStack* ths = 0;
  std::vector<TH1*> histVector;
  //
  for(int i = 0; i < list->GetEntries(); i++){
    //
    TObject* obj = list->At(i);
    TString cname(obj->ClassName());
    std::cout<<"cname: "<<cname<<std::endl;
    //
    // MC stack histos
    if(cname.Contains("THStack")){
      ths = ((THStack*)obj);
      TList* hists = ths->GetHists();
      TIterator* iter = new TListIter(hists);
      while(TH1* h = (TH1*)iter->Next()) {
        std::cout<<h->GetName()<<std::endl;
        std::cout<<"new Integral(): "<<h->Integral(0,h->GetNbinsX()+1)<<std::endl;
        for( int ibin=0; ibin<h->GetNbinsX()+1; ibin++){
          std::cout<<"Bin("<<ibin<<"): "<<h->GetBinContent(ibin)<<" +/- "<<h->GetBinError(ibin)<<std::endl;
        }
        histVector.push_back(h);
      }
    }
    //
    // Data
        if(cname.Contains("TH1")){
      h = ((TH1*)obj);
      TString histoname(h->GetName());
      if(histoname.Contains("13TeV")){
        std::cout<<h->GetName()<<std::endl;
        std::cout<<"new Integral(): "<<h->Integral(0,h->GetNbinsX()+1)<<std::endl;
        for( int ibin=0; ibin<h->GetNbinsX()+1; ibin++){
          std::cout<<"Bin("<<ibin<<"): "<<h->GetBinContent(ibin)<<" +/- "<<h->GetBinError(ibin)<<std::endl;
        }
        histVector.push_back(h);
      }
    }
    //
  }
  
  TFile* outfile = new TFile(outfilename,"RECREATE");
  outfile->cd();
  for(std::vector<TH1*>::iterator it = histVector.begin(); it != histVector.end(); ++it) {
    std::cout<<"histVector name: "<<(*it)->GetName()<<std::endl;
    TString histoname((*it)->GetName());
    if(histoname.Contains("13TeV")){//Clean up data histo name and title
      (*it)->SetTitle("Data");
      (*it)->Write("Data");
    }
    else{
      (*it)->SetTitle(histoname);
      (*it)->Write(histoname);
    }
  }
  outfile->ls();
  outfile->Close();
}
