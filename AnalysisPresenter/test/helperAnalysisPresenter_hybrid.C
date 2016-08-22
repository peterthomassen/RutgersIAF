#include <iostream>
#include <TH1.h>
#include <boost/algorithm/string.hpp>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "MatrixMacros/helperAnalysisPresenterMM_WeightFunctions.C"

// Load library, see https://root.cern.ch/phpBB2/viewtopic.php?f=3&t=19471
namespace {
  int loadMyLibraryTriggerFunc() {
    gSystem->Load("libRutgersIAFAnalysisPresenter.so");
    return 0;
  }
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void applyUncertaintiesAndScaleFactors(Assembler* assembler, PhysicsContribution* contribution) {
	if(!contribution->isMC()) {
		return;
	}
	
	// do some stuff
}

void init(Assembler* assembler, std::string backgroundModel = "proxy") {
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
	//gStyle->SetErrorX(0);
	
	assembler->addBundle(new Bundle("background", "Misidentified", false, 42));
	assembler->addBundle(new Bundle("background", "presentationBundle"));
	assembler->addBundle(new Bundle("background", "fakePresentationBundle"));
	
	assembler->addBundle(new Bundle("background", "TrackFakes", false, kGreen - 3));
	assembler->addBundle(new Bundle("background", "PhotonFakes", false, kBlue - 7));
	
	assembler->addBundle(new Bundle("background", "WZ", false, 39));
	assembler->addBundle(new Bundle("background", "Higgs", false, 38));
	assembler->addBundle(new Bundle("background", "Rare MC", false, 33));
	
	if(backgroundModel == "proxy") {
		assembler->setMode("backgroundModel_proxy");
	} else if(backgroundModel == "MC") {
		assembler->setMode("backgroundModel_MC");
	} else if(backgroundModel == "MM") {
		assembler->setMode("backgroundModel_MM");
	} else {
		cout << "background model: " << backgroundModel << endl;
		throw std::runtime_error("unknown background model");
	}
}

void prepare(Assembler* assembler) {
	Bundle* fakeBundle = assembler->getBundle("Misidentified");
	for(const auto &bundleName : {"TrackFakes", "PhotonFakes"}) {
		Bundle* bundle = assembler->getBundle(bundleName);
		if(bundle->getComponents().size() > 0) {
			fakeBundle->addComponent(bundle);
		}
	}
	
	Bundle* presentationBundle = assembler->getBundle("presentationBundle");
	for(const auto &bundleName : {"Misidentified", "WZ", "Higgs", "Rare MC"}) {
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
	std::string infix = dilep ? ".2L" : ".3L";
	std::string suffix = ".data.root";
	
	PhysicsContribution* dataElEl_B = 0;
	PhysicsContribution* dataMuEl_B = 0;
	PhysicsContribution* dataMuMu_B = 0;
	PhysicsContribution* dataMuMu_D = 0;
	std::string TREE="treeR";
	  if(fakeMode == 0) {
	      TREE = "treeR";
	  }
	  if(fakeMode == 1) {
	    TREE = "treeRfakeTracks";
	  }
	  if(fakeMode == 2) {
            TREE = "treeRfakePhotons";
          }
	  if(!(fakeMode == 0||fakeMode == 1||fakeMode == 3)){
	    cout << "unsure what to do";                                                                                                                            
	    exit(1); 
	  }
	  std::vector<PhysicsContribution*> data;
		
		
	  dataMuMu_B = new PhysicsContribution("data", "/cms/multilepton/mheindl/2016/AnalysisTrees/Data/output/DoubleMuon_2016B" + infix + suffix, 5892, "10.2/fb@13TeV",false,TREE);
	  data.push_back(dataMuMu_B);
	  
	  dataMuMu_D = new PhysicsContribution("data", "/cms/multilepton/mheindl/2016/Data/DoubleMuon/Run2016D-PromptReco-v2_MINIAOD/160730_063738/0000/DoubleMuon_2016D" + infix + suffix, 4353, "10.2/fb@13TeV",false,TREE);
	  data.push_back(dataMuMu_D);
	  

	for(auto &contribution : data) {
		contribution->addWeight("TRIGGERACCEPT");
		contribution->addWeight("NLIGHTLEPTONS[0] == Sum$(ISTIGHTMATRIXMUON) + Sum$(ISTIGHTMATRIXELECTRON) + Sum$(fakeRoleGOODMUONS > 0) + Sum$(fakeRoleGOODELECTRONS > 0)");
		
		std::vector<string> vetoFilenames = { };
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
			
				if(!contribution->addVetoEvent(line)) {
					++nDuplicates;
				}
			}
			ifile.close();
			cout << " (" << nDuplicates << " duplicates)" << endl;
		}
		
		assembler->addContribution(contribution);
	}
	
	// Pile-up weights
	cout << "Notice: Applying pileup weights" << endl;
	TFile* f = new TFile("/users/h2/schauhan/PileUpHist/12.9fb_PileupHistogram_xsec69200.root");
	if(f->IsZombie()) {
		throw std::runtime_error("couldn't open pileup file");
	}
	TH1D* hPileup = (TH1D*)f->Get("pileup");
	TH1D* hPileupUnc = 0;
	
	if(assembler->getMode("fullPrecision")) {
		TFile* fUnc = new TFile("/users/h2/schauhan/PileUpHist/12.9fb_Pileup+5%Histogram_xsec69200.root");
		if(fUnc->IsZombie()) {
			throw std::runtime_error("couldn't open pileup uncertainty file");
		}
		hPileupUnc = (TH1D*)fUnc->Get("pileup");
	} else {
		cout << "Notice: Not applying MET smearing and pile-up. Set fullPrecision mode to do so." << endl;
	}
	assembler->setPileupHistogram(hPileup, hPileupUnc);
}

void setupBackgroundMC(Assembler* assembler, bool dilep = false, bool ttbar = true) {
	std::string prefix = "/cms/heindl/2016/AnalysisTrees/MCData/output/";
	std::string infix = dilep ? ".2L" : ".3L";
	std::string suffix = ".simulation.root";
	
	double xsec_dy10to50 = 18610.;
	double xsec_dy50 = 6025.2;
		double dxsec_dy50 = sqrt(pow(39.6, 2) + pow(225, 2));
	double xsec_ttF = 87.31; // MCM * BR: 670.3 * 0.105;
		double dxsec_ttF = sqrt(pow(3.07, 2) + pow(3.68, 2));
	double xsec_WZTo3LNu = 4.42965;
	double xsec_zz = 1.212; // from MCM; // PHYS14: 1.218;
	
	/*double xsec_ttw = 0.2043;
	double xsec_ttz = 0.2529;
	double xsec_glugluHtoZZto4L = 0.01212;
	double xsec_vbf_HtoZZto4L = 0.001034;
	double xsec_WWZ = 0.1651;
	double xsec_WZZ = 0.05565;
	double xsec_ZZZ = 0.01398;*/
	
	std::vector<PhysicsContribution*> mc;
	std::vector<PhysicsContribution*> mcH;
	std::vector<PhysicsContribution*> mcRare;
	
	PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZTo3LNu__062116_083202/WZTo3LNu" + infix + suffix, xsec_WZTo3LNu, "WZTo3LNu", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01);
	//wz->setNominalWeight("genEventInfo_weight[0]");
	//wz->addWeight("0.815"); // normalization
	if(!assembler->getMode("noWZsystematics")) {
		wz->addFlatUncertainty("normalizationWZ", 1./sqrt(219)); // size of scale factor (< statistical)
	//	wz->addFlatUncertainty("trackFakes", -0.0174); // based on 14% variation of fakeTracks in WZ normalization region
	//	wz->addFlatUncertainty("photonFakes", -0.0082); // based on 52% variation of fakePhotons in WZ normalization region
	}
	assembler->getBundle("WZ")->addComponent(wz);
	mc.push_back(wz);
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZTo4L__062116_083236/ZZTo4L" + infix + suffix, xsec_zz, "ZZ", false, "treeR", 30, assembler->getMode("fullPrecision") ? 0 : 0.01);
	//zz->setNominalWeight("genEventInfo_weight[0]");
	//zz->addWeight("1.64");  // normalization
	if(!assembler->getMode("noZZsystematics")) {
		zz->addFlatUncertainty("normalizationZZ", 1./sqrt(65)); // statistical
	}
	mc.push_back(zz);
	
	PhysicsContribution* c = 0;
	
	TString nJetWeight = "1";
	TString normalization = "1";
	
	Bundle* bundleTTbar = new Bundle("background", "ttbar");
	assembler->addBundle(bundleTTbar);
	
	if(ttbar && !assembler->getMode("backgroundModel_MM")) {
		PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu_2__061616_090554/TTTo2L2Nu" + infix + suffix, xsec_ttF, "ttbar", false, "treeR", kAzure + 1, assembler->getMode("fullPrecision") ? 0 : 0.01);
		//ttbarF->setNominalWeight("genEventInfo_weight[0]");
		ttbarF->addWeight(normalization); // normalization
		ttbarF->addWeight(nJetWeight);
		if(!assembler->getMode("noTTsystematics")) {
			//ttbarF->addRelativeUncertainty("ttbarNJet", TString::Format("1 - 1/(%s)", nJetWeight.Data()));
		}
		ttbarF->addWeight("1 + (NLIGHTLEPTONS[0] >= 3) * 0.5");
		//ttbarF->addFlatUncertainty("xsec_ttF", dxsec_ttF / xsec_ttF);
		//if(!assembler->getMode("noTTsystematics")) ttbarF->addFlatUncertainty("xsec_tt", dxsec_tt / xsec_tt);
		if(!assembler->getMode("noTTsystematics")) {
		//	ttbarF->addFlatUncertainty("ttbarFakeRate", 0.5);
		}
		mc.push_back(ttbarF);
		bundleTTbar->addComponent(ttbarF);
		
		if(!dilep && assembler->getMode("backgroundModel_proxy")) {
			std::vector<PhysicsContribution*> ttbarFfake;
			
			PhysicsContribution* ttbarFfakeTracks = new PhysicsContribution("backgroundMC", prefix + "TTTo2L2Nu_2__061616_090554/TTTo2L2Nu" + infix + suffix, xsec_ttF, "TT_FullLfakeTracks", true, "treeRfakeTracks", -1, assembler->getMode("fullPrecision") ? 0 : 0.01);
			ttbarFfakeTracks->addWeight("1 + (NLIGHTLEPTONS[0] >= 3) * 0.5");
			if(!assembler->getMode("noTTsystematics")) {
				ttbarFfakeTracks->addFlatUncertainty("ttbarFudge", 0.5);
			}
			ttbarFfake.push_back(ttbarFfakeTracks);
			assembler->getBundle("TrackFakes")->addComponent(ttbarFfakeTracks);
			
			/* 
			 * We don't assume the ttbar MC to model AIC's correctly. We therefore decided to get the estimate from data, and veto leptons from photons in the MC. Thus, we don't need MC subtraction in the data-driven method.
			*/
			
			for(auto &contribution : ttbarFfake) {
				//contribution->setNominalWeight("genEventInfo_weight[0]");
				contribution->addWeight(nJetWeight);
				if(!assembler->getMode("noTTsystematics")) {
					contribution->addRelativeUncertainty("ttbarNJet", TString::Format("1 - 1/(%s)", nJetWeight.Data()));
				}
				contribution->addWeight("nTrackFakeElectrons + nTrackFakeMuons + nPhotonFakeElectrons + nPhotonFakeMuons == 1"); // + nTauFakeTaus == 1");
				mc.push_back(contribution);
			}
		}
	}
	
	if(assembler->getMode("backgroundModel_MC")) {
		PhysicsContribution* dy10to50 = new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-10to50__061616_090315/DYJetsToLL_M-10to50" + infix + suffix, xsec_dy10to50, "DY10to50", false, "treeR", 46, assembler->getMode("fullPrecision") ? 0 : 0.01);
		//dy10to50->setNominalWeight("genEventInfo_weight[0]");
		mc.push_back(dy10to50);
		
		PhysicsContribution* dy50 = new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50_1__061616_090231/DYJetsToLL_M-50" + infix + suffix, xsec_dy50, "DY50", false, "treeR", 46, assembler->getMode("fullPrecision") ? 0 : 0.01);
		//dy50->addFlatUncertainty("xsec_dy50", dxsec_dy50 / xsec_dy50);
		//c->setNominalWeight("genEventInfo_weight[0]");
		mc.push_back(dy50);
	}
	
	for(auto &contribution : mc) {
		contribution->addWeight("WEIGHT[0]");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		contribution->addWeight("NLIGHTLEPTONS[0] == Sum$(ISTIGHTMATRIXMUON) + Sum$(ISTIGHTMATRIXELECTRON) + Sum$(fakeRoleGOODMUONS > 0) + Sum$(fakeRoleGOODELECTRONS > 0)");
		//ElectronScaleFactors                                                                                                                                                                                                       
                contribution->addWeight("elSF(Alt$(PTGOODELECTRONS[0],-1),Alt$(ETAGOODELECTRONS[0],543))*elSF(Alt$(PTGOODELECTRONS[1],-1),Alt$(ETAGOODELECTRONS[1],543))*elSF(Alt$(PTGOODELECTRONS[2],-1),Alt$(ETAGOODELECTRONS[2],543))**elSF(Alt$(PTGOODELECTRONS[3],-1),Alt$(ETAGOODELECTRONS[3],543))");
                //MuonScaleFactors                                                                                                                                                                                                           
                contribution->addWeight("muSF(Alt$(PTGOODMUONS[0],-1),Alt$(ETAGOODMUONS[0],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[1],-1),Alt$(ETAGOODMUONS[1],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[2],-1),Alt$(ETAGOODMUONS[2],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[3],-1),Alt$(ETAGOODMUONS[3],543),NRECOVERTICES[0])");
		applyUncertaintiesAndScaleFactors(assembler, contribution);
		assembler->addContribution(contribution);
	}
	
	for(auto &contribution : mcRare) {
		contribution->addWeight("WEIGHT[0]");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		contribution->addWeight("NLIGHTLEPTONS[0] == Sum$(ISTIGHTMATRIXMUON) + Sum$(ISTIGHTMATRIXELECTRON) + Sum$(fakeRoleGOODMUONS > 0) + Sum$(fakeRoleGOODELECTRONS > 0)");
		//ElectronScaleFactors                                                                                                                                                                                                       
                contribution->addWeight("elSF(Alt$(PTGOODELECTRONS[0],-1),Alt$(ETAGOODELECTRONS[0],543))*elSF(Alt$(PTGOODELECTRONS[1],-1),Alt$(ETAGOODELECTRONS[1],543))*elSF(Alt$(PTGOODELECTRONS[2],-1),Alt$(ETAGOODELECTRONS[2],543))**elSF(Alt$(PTGOODELECTRONS[3],-1),Alt$(ETAGOODELECTRONS[3],543))");
                //MuonScaleFactors                                                                                                                                                                                                           
                contribution->addWeight("muSF(Alt$(PTGOODMUONS[0],-1),Alt$(ETAGOODMUONS[0],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[1],-1),Alt$(ETAGOODMUONS[1],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[2],-1),Alt$(ETAGOODMUONS[2],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[3],-1),Alt$(ETAGOODMUONS[3],543),NRECOVERTICES[0])");
		applyUncertaintiesAndScaleFactors(assembler, contribution);
		//contribution->addFlatUncertainty("lumi", 0.027); // as of 2016-02-22 https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/563.html
		//contribution->addFlatUncertainty("xsecRare", 0.5);
		assembler->addContribution(contribution);
		assembler->getBundle("Rare MC")->addComponent(contribution);
	}
	
	return;
	
/*	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToTauTau" + infix + suffix, 1.2466, "GluGluToHToTauTau", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluToHToWWTo2LAndTau2Nu" + infix + suffix, 0.4437, "GluGluToHToWWTo2LAndTau2Nu", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "GluGluHToZZTo4L_M125" + infix + suffix, xsec_glugluHtoZZto4L, "GluGluHToZZTo4L", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToTauTau" + infix + suffix, 0.0992, "VBF_HToTauTau", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToWWTo2LAndTau2Nu" + infix + suffix, 0.0282, "VBF_HToWWTo2LAndTau2Nu", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "VBF_HToZZTo4L_M125" + infix + suffix, xsec_vbf_HtoZZto4L, "VBF_HToZZTo4L", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
//?	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToTauTau" + infix + suffix, 0.0778, "WH_ZH_TTH_HToTauTau", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
//?	mcH.push_back(new PhysicsContribution("backgroundMC", prefix + "WH_ZH_TTH_HToWW" + infix + suffix, 0.254, "WH_ZH_TTH_HToWW", false, "treeR", -1, assembler->getMode("fullPrecision") ? 0 : 0.01));
*/
	
	for(auto &contribution : mcH) {
		//contribution->addFlatUncertainty("xsecH", 0.5); // TODO correlations?
		contribution->addWeight("WEIGHT[0]");
		contribution->addWeight("DIMUTRIGTHRESHOLD || DIELTRIGTHRESHOLD || MUEGCOMBINEDTHRESHOLD");
		contribution->addWeight("NLIGHTLEPTONS[0] == Sum$(ISTIGHTMATRIXMUON) + Sum$(ISTIGHTMATRIXELECTRON) + Sum$(fakeRoleGOODMUONS > 0) + Sum$(fakeRoleGOODELECTRONS > 0)");
		//ElectronScaleFactors                                                                                                                                                                                                       
                contribution->addWeight("elSF(Alt$(PTGOODELECTRONS[0],-1),Alt$(ETAGOODELECTRONS[0],543))*elSF(Alt$(PTGOODELECTRONS[1],-1),Alt$(ETAGOODELECTRONS[1],543))*elSF(Alt$(PTGOODELECTRONS[2],-1),Alt$(ETAGOODELECTRONS[2],543))**elSF(Alt$(PTGOODELECTRONS[3],-1),Alt$(ETAGOODELECTRONS[3],543))");
                //MuonScaleFactors                                                                                                                                                                                                           
                contribution->addWeight("muSF(Alt$(PTGOODMUONS[0],-1),Alt$(ETAGOODMUONS[0],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[1],-1),Alt$(ETAGOODMUONS[1],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[2],-1),Alt$(ETAGOODMUONS[2],543),NRECOVERTICES[0])*muSF(Alt$(PTGOODMUONS[3],-1),Alt$(ETAGOODMUONS[3],543),NRECOVERTICES[0])");

		applyUncertaintiesAndScaleFactors(assembler, contribution);
		//contribution->addFlatUncertainty("lumi", 0.027); // as of 2016-02-22 https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/563.html
		//contribution->addFlatUncertainty("xsecHiggs", 0.5);
		assembler->addContribution(contribution);
		assembler->getBundle("Higgs")->addComponent(contribution);
	}
}

void setupBackgroundDD(Assembler* assembler, TString option = "", bool syst = true) {
	std::string prefix = "/cms/multilepton/mheindl/2016/AnalysisTrees/Data/output/";
	std::string body = "DiLeptonData_2016B_273000-275125";
	std::string suffix = ".3L.data.root";
	
	TString nVertexWeight = "1"; // "0.773 + 0.0218 * NVERTICES[0]";
	
	////// Tracks
	if(assembler->getMode("backgroundModel_proxy")) {
		PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakeTracks", false, "treeRfakeTracks", (option == "justTracks") ? kWhite : -1);
		fakeTracks->addWeight("TRIGGERACCEPT");
		fakeTracks->addWeight("NLIGHTLEPTONS[0] == Sum$(ISTIGHTMATRIXMUON) + Sum$(ISTIGHTMATRIXELECTRON) + Sum$(fakeRoleGOODMUONS > 0) + Sum$(fakeRoleGOODELECTRONS > 0)");
		fakeTracks->addWeight(
			"(Sum$(fakeRoleGOODELECTRONS) > 0)"
				" * ("
					"(NGOODELECTRONS[0] == 1) * ( (Min$(PTGOODELECTRONS) < 15) * 0.45 + !(Min$(PTGOODELECTRONS) < 15) * 1.75 )"
					" + (NGOODELECTRONS[0] == 3) * ((Min$(PTGOODELECTRONS) < 15) * 0.4 + !(Min$(PTGOODELECTRONS) < 15) )"
					" + (NGOODELECTRONS[0] != 1 && NGOODELECTRONS[0] != 3)"
				")"
			" + (Sum$(fakeRoleGOODMUONS) > 0)"
				" * ("
					"(NGOODMUONS[0] == 1) * ( (Min$(PTGOODMUONS) < 15) * 0.64 + !(Min$(PTGOODMUONS) < 15) )"
					" + (NGOODMUONS[0] == 3) * (1.7 -  0.02 * Min$(PTGOODMUONS))"
					" + (NGOODMUONS[0] != 1 && NGOODMUONS[0] != 3)"
				")"
		);
		fakeTracks->addWeight(nVertexWeight);
		fakeTracks->addRelativeUncertainty("fakePileupWeight", TString::Format("1 - 1/(%s)", nVertexWeight.Data()));
		applyUncertaintiesAndScaleFactors(assembler, fakeTracks);
		if(syst && !assembler->getMode("noTrackSystematics")) {
			//fakeTracks->addFlatUncertainty("trackFakeRateFit", 0.06);
			//fakeTracks->addFlatUncertainty("trackPtFit", 0.10);
			//fakeTracks->addFlatUncertainty("trackFakes", 0.14);
			//fakeTracks->addFlatUncertainty("photonFakes", -0.080); // based on 52% variation of photon contribution in track fake rate measurement region
			//fakeTracks->addFlatUncertainty("normalizationWZ", -0.033); // based on 7.3% variation of WZ in track fake rate measurement region
		}
		if(option != "noTracks" && option != "justTaus" && option != "justPhotons" && option != "fakeTaus2L") {
			assembler->getBundle("TrackFakes")->addComponent(fakeTracks);
			assembler->addContribution(fakeTracks);
		}
	}
	
	
	////// Photons
	if(assembler->getMode("backgroundModel_proxy") || assembler->getMode("backgroundModel_MM")) {
		PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", prefix + body + suffix, assembler->getLumi(), "fakePhotons", false, "treeRfakePhotons");
		fakePhotons->addWeight("TRIGGERACCEPT");
		fakePhotons->addWeight("NLIGHTLEPTONS[0] == Sum$(ISTIGHTMATRIXMUON) + Sum$(ISTIGHTMATRIXELECTRON) + Sum$(fakeRoleGOODMUONS > 0) + Sum$(fakeRoleGOODELECTRONS > 0)");
		fakePhotons->addWeight(nVertexWeight);
		fakePhotons->addRelativeUncertainty("fakePileupWeight", TString::Format("1 - 1/(%s)", nVertexWeight.Data()));
		applyUncertaintiesAndScaleFactors(assembler, fakePhotons);
		if(syst && !assembler->getMode("noPhotonSystematics")) {
			//fakePhotons->addFlatUncertainty("photonFakes", 0.52); // due to photonDR
			//fakePhotons->addFlatUncertainty("trackFakes", -0.056); // based on 14% variation of track contribution in photon fake rate measurement region
			//fakePhotons->addFlatUncertainty("normalizationWZ", -0.0018); // based on 7.3% variation of WZ in photon fake rate measurement region
		}
		if(option != "noPhotons" && option != "justTracks" && option != "justTaus" && option != "fakeTaus2L") {
			assembler->getBundle("PhotonFakes")->addComponent(fakePhotons);
			assembler->addContribution(fakePhotons);
		}
	}
	
	
	////// Matrix Method
	if(assembler->getMode("backgroundModel_MM")) {
		PhysicsContribution* mm = new PhysicsContribution("backgroundMM", prefix + body + suffix, assembler->getLumi(), "MM", false, "treeR");
		mm->addWeight("TRIGGERACCEPT");
		mm->addWeight("MMweight(PTGOODMUONS[0],ETAGOODMUONS[0],PTGOODMUONS[1],ETAGOODMUONS[1],PTGOODMUONS[2],ETAGOODMUONS[2],((JETNOOFCONSTGOODMUONS[0]>12.5)*100+(JETNOOFCONSTGOODMUONS[1]>12.5)*10+(JETNOOFCONSTGOODMUONS[2]>12.5)),NRECOVERTICES[0],(ISTIGHTMATRIXMUON[0]*100000+ISTIGHTMATRIXMUON[1]*10000+ISTIGHTMATRIXMUON[2]*1000+222))");
		//mm->addWeight("MMweight(PTGOODELECTRONS[0],ETAGOODELECTRONS[0],PTGOODELECTRONS[1],ETAGOODELECTRONS[1],PTGOODELECTRONS[2],ETAGOODELECTRONS[2],((JETNOOFCONSTGOODELECTRONS[0]>12.5)*100+(JETNOOFCONSTGOODELECTRONS[1]>12.5)*10+(JETNOOFCONSTGOODELECTRONS[2]>12.5)),NRECOVERTICES[0],(ISTIGHTMATRIXELECTRON[0]*100000+ISTIGHTMATRIXELECTRON[1]*10000+ISTIGHTMATRIXELECTRON[2]*1000+111))");
		assembler->getBundle("Misidentified")->addComponent(mm);
		assembler->addContribution(mm);
	}
}

void setupFakeRates(Assembler* assembler) {
	if(assembler->getMode("backgroundModel_proxy")) {
		// In 2012, we found that NGOODJETS and HT binning does not work very well; NPROMPTINCLUSIVETRACK7 binning does a good job at least in 0b regions.
		assembler->setFakeRate("nTrackFakeMuons",
			"("
				"(NGOODMUONS[0] == 1) * 0.0158 + (NGOODMUONS[0] == 3) * 0.017" // measurement done here
				" + (NGOODMUONS[0] == 2 || NGOODMUONS[0] == 4) * 0.0164" // use average for the other cases
			")"
			" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
		);
		assembler->setFakeRate("nTrackFakeElectrons",
			"("
				"(NGOODELECTRONS[0] == 1) * 0.019 + (NGOODELECTRONS[0] == 3) * 0.019" // measurement done here
				" + (NGOODELECTRONS[0] == 2 || NGOODELECTRONS[0] == 4) * 0.019" // use average for the other cases
			")"
			" * (nTrackFakeElectrons[0] + nTrackFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
		);
	}
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	if(assembler->getMode("backgroundModel_proxy") || assembler->getMode("backgroundModel_MM")) {
		// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
		// Looking at the AIC control region, we find that we should adjust the fake rate outside MLEPTONS = 75..100.
		assembler->setFakeRate("nPhotonFakeMuons",
			"("
				"(NGOODMUONS[0] == 1) * 0.0105 + (NGOODMUONS[0] == 3) * 0.0115" // measurement done here
				" + (NGOODMUONS[0] == 2 || NGOODMUONS[0] == 4) * 0.0110" // use average for the other cases
			")"
			" * Alt$(Sum$(abs(goodMuonsDRgoodLeptons - 0.5) < 0.1 && fakeRoleGOODMUONS > 0) > 0, 0)" // only stuff emitted close to leptons
			" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
		);
		assembler->setFakeRate("nPhotonFakeElectrons",
			"("
				"(NGOODELECTRONS[0] == 1) * 0.0435 + (NGOODELECTRONS[0] == 3) * 0.024" // measurement done here
				" + (NGOODELECTRONS[0] == 2 || NGOODELECTRONS[0] == 4) * 0.03375" // use average for the other cases
			")"
			" * Alt$(Sum$(abs(goodElectronsDRgoodLeptons - 0.5) < 0.1 && fakeRoleGOODELECTRONS > 0) > 0, 0)" // only stuff emitted close to leptons
			" * (nPhotonFakeElectrons[0] + nPhotonFakeMuons[0] == 1)" // disable multiple proxies (precaution to avoid problems like with taus)
		);
	}
}

#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TStyle.h>

TCanvas* makeNicePlot(TCanvas* c, TString axistitle = "", TString unit = "", TString preliminary = "Preliminary", bool noRatio = false) {
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	c->cd();
	c->SetTopMargin(0.001);
	c->SetRightMargin(0.001);
	c->SetBottomMargin(0.001);
	c->SetLeftMargin(0.001);

	TPad* pad1 = (TPad*)c->GetPrimitive("pad1");
	pad1->SetRightMargin(0.03);
	//pad1->SetBottomMargin(0.01);
	pad1->SetTopMargin(0.07);
	TPad* pad2 = (TPad*)c->GetPrimitive("pad2");
	pad2->SetTopMargin(0.01);
	pad2->SetRightMargin(0.03);
	pad2->SetBottomMargin(0.25);

	//pad1->RedrawAxis();
	pad2->RedrawAxis();

	pad1->cd();
	TList* list = pad1->GetListOfPrimitives();
	cout<<"make nice plot "<<list->GetEntries()<<endl;
	TH1* h = 0;
	TLegend* legend = 0;
	for(int i = 0; i < list->GetEntries(); i++) {
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
	pad1->Range(0, 0, 1, 1);
	legend->SetX1(0.63); legend->SetX2(1.0);
	legend->SetY1(0.51); legend->SetY2(0.9);

	for(auto pad : {pad1, pad2}) {
		TList* list2 = pad->GetListOfPrimitives();
		for(int i = 0; i < list2->GetEntries(); i++){
			TObject* obj = list2->At(i);
			TString cname(obj->ClassName());
			if(cname.Contains("TH1")) {
				if(pad == pad1) {
					if(!noRatio) {
						((TH1*)obj)->GetXaxis()->SetTitle("");
					}
					if(unit != "") {
						float offsetY = ((TH1*)obj)->GetYaxis()->GetTitleOffset();
						float fontsizeY = ((TH1*)obj)->GetYaxis()->GetTitleSize();
						((TH1*)obj)->GetYaxis()->SetTitleOffset(1*offsetY);
						((TH1*)obj)->GetYaxis()->SetTitleSize(1.3*fontsizeY);
						//TString axisTitleY = TString::Format("Events / %d %s", (int)(((TH1*)obj)->GetBinWidth(1)), unit.Data());
						TString axisTitleY = TString::Format("Events / %.2f %s", (double)(((TH1*)obj)->GetBinWidth(1)), unit.Data());
						((TH1*)obj)->GetYaxis()->SetTitle(axisTitleY);
					}
				}
				if(pad == pad2 || noRatio) {
					float offsetX = ((TH1*)obj)->GetXaxis()->GetTitleOffset();
					float fontsizeX = ((TH1*)obj)->GetXaxis()->GetTitleSize();
					((TH1*)obj)->GetXaxis()->SetTitleOffset(1*offsetX);
					((TH1*)obj)->GetXaxis()->SetTitleFont(42);
					if(noRatio) {
						((TH1*)obj)->GetXaxis()->SetTitleSize(1.25*fontsizeX);
						((TH1*)obj)->GetXaxis()->SetLabelSize(0.05);
					} else {
						((TH1*)obj)->GetXaxis()->SetTitleSize(1.75*fontsizeX);
					}
					if(axistitle != "" && TString(((TH1*)obj)->GetXaxis()->GetTitle()) != ""){
						TString axisTitleX = axistitle;
						if(unit != "") {
							axisTitleX += TString::Format(" [%s]", unit.Data());
						}
						((TH1*)obj)->GetXaxis()->SetTitle(axisTitleX);
					}
				}
				if(pad == pad2) {
					((TH1*)obj)->GetYaxis()->SetNdivisions(50206);
					float offsetY = ((TH1*)obj)->GetYaxis()->GetTitleOffset();
					float fontsizeY = ((TH1*)obj)->GetYaxis()->GetTitleSize();
					((TH1*)obj)->GetYaxis()->SetTitleOffset(0.65*offsetY);
					((TH1*)obj)->GetYaxis()->SetTitleSize(1.75*fontsizeY);
				}
			}
		}
	}
	
	c->cd();
	
	TLatex* latex = new TLatex;
	latex->SetNDC();
	latex->SetTextFont(61);
	latex->SetTextSize(0.04);
	latex->DrawLatex(0.13, noRatio ? 0.86 : 0.89, "CMS");
	latex->SetTextFont(52);
	latex->DrawLatex(0.13, noRatio ? 0.81 : 0.84, preliminary);
	
	latex->SetTextSize(0.035);
	latex->SetTextFont(42);
	if(!preliminary.Contains("Simulation", TString::kIgnoreCase)) {
		latex->DrawLatex(0.76, 0.96, "2.8 fb^{-1} (13 TeV)");
	}
	
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
  bool isdebug=false;
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
    if(isdebug) std::cout<<"cname: "<<cname<<std::endl;
    //
    // MC stack histos
    if(cname.Contains("THStack")){
      ths = ((THStack*)obj);
      TList* hists = ths->GetHists();
      TIterator* iter = new TListIter(hists);
      while(TH1* h = (TH1*)iter->Next()) {
        if(isdebug){ 
            std::cout<<h->GetName()<<std::endl;
            std::cout<<"new Integral(): "<<h->Integral(0,h->GetNbinsX()+1)<<std::endl;
            for( int ibin=0; ibin<h->GetNbinsX()+1; ibin++){
              std::cout<<"Bin("<<ibin<<"): "<<h->GetBinContent(ibin)<<" +/- "<<h->GetBinError(ibin)<<std::endl;
            }
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
        if(isdebug){ 
            std::cout<<h->GetName()<<std::endl;
            std::cout<<"new Integral(): "<<h->Integral(0,h->GetNbinsX()+1)<<std::endl;
            for( int ibin=0; ibin<h->GetNbinsX()+1; ibin++){
                std::cout<<"Bin("<<ibin<<"): "<<h->GetBinContent(ibin)<<" +/- "<<h->GetBinError(ibin)<<std::endl;
            }
        }
        histVector.push_back(h);
      }
    }
    //
  }
  
  TFile* outfile = new TFile(outfilename,"RECREATE");
  outfile->cd();
  for(std::vector<TH1*>::iterator it = histVector.begin(); it != histVector.end(); ++it) {
    if(isdebug) std::cout<<"histVector name: "<<(*it)->GetName()<<std::endl;
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

//The below function returns electron scale factor. Electron Scale Fcator = Gsf_Tracking Scale factor x Medium ID scale factor
double elSF(double Pt, double Eta)
{ 
  if(Pt==-1&&Eta==543)return 1;
  double SFWeight=1;
  static TFile *feSF1=0;
  static TFile *feSF2=0;
  if(!feSF1)feSF1= new TFile("./ScaleFactors/egammaEffi.txt_SF2D_Gsf_12p9ifb.root");
  if(!feSF2)feSF2= new TFile("./ScaleFactors/egammaEffi.txt_SF2D_Med_12p9ifb.root");
  //TH2F *heSF;  
  //TFile *feSF;
  for(int p=0;p<=1;p++){
    TH2F *heSF;
    if(p==0)
      heSF = (TH2F*)feSF1->Get("EGamma_SF2D");
    if(p==1)
      heSF = (TH2F*)feSF2->Get("EGamma_SF2D");
    //////////////////////////////////////Finding the Bin
    Int_t binEta = heSF->GetXaxis()->FindBin(Eta);
    Int_t binPt = heSF->GetYaxis()->FindBin(Pt);
    if(Eta<(heSF->GetXaxis()->GetXmin()))
      binEta = heSF->GetXaxis()->FindBin(heSF->GetXaxis()->GetXmin());//This is needed since FinBin returns zero if value is less than axis min.
    if(Pt<(heSF->GetYaxis()->GetXmin()))
      binPt= heSF->GetYaxis()->FindBin(heSF->GetYaxis()->GetXmin());//This is needed since FinBin returns zero if value is less than axis min.
    if(Eta>=(heSF->GetXaxis()->GetXmax()))
      binEta = (heSF->GetXaxis()->FindBin(heSF->GetXaxis()->GetXmax()))-1;
    if(Pt>=(heSF->GetYaxis()->GetXmax()))
      binPt= (heSF->GetYaxis()->FindBin(heSF->GetYaxis()->GetXmax()))-1;

    /////////////////////////////////////////
       SFWeight=SFWeight*(heSF->GetBinContent(binEta,binPt));//Multiply the scale factor with the one from previous file
       delete heSF;
  }
  return SFWeight;
}
//The below function returns muon scale factor. Muon Scale Factor = ID factor x Vertex factor x Tracking POG
double muSF(double Pt,double Eta, int NVertices, bool VertexWeight=true)
{
  if(Pt==-1&&Eta==543)return 1;
  double SFWeight=1;
  //PT_Eta_weights_for_medium_ID
  static TFile *fmSF1=0;
  static TDirectory *dmSF1=0;
  if(!fmSF1)fmSF1= new TFile("ScaleFactors/MuonID_Z_RunBCD_prompt80X_7p65ifb.root");
  if(!dmSF1)dmSF1= (TDirectoryFile*)fmSF1->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_spliteta_bin1");
  //  TH2F *hmSF;
  for(int p=0;p<=0;p++){ //Only one file right now hence p<=0. We can add more files when needed. See how its done in elSF.
    TH2F *hmSF;
    hmSF = (TH2F*)dmSF1->Get("abseta_pt_ratio");
    Int_t binEta = hmSF->GetXaxis()->FindBin(abs(Eta));
    Int_t binPt = hmSF->GetYaxis()->FindBin(Pt);
    if(abs(Eta)<(hmSF->GetXaxis()->GetXmin()))
      binEta = hmSF->GetXaxis()->FindBin(hmSF->GetXaxis()->GetXmin());//This is needed since FinBin returns zero if value is less than axis min.
    if(Pt<(hmSF->GetYaxis()->GetXmin()))
      binPt= hmSF->GetYaxis()->FindBin(hmSF->GetYaxis()->GetXmin());//This is needed since FinBin returns zero if value is less than axis min. 
    if(abs(Eta)>=(hmSF->GetXaxis()->GetXmax()))
      binEta = (hmSF->GetXaxis()->FindBin(hmSF->GetXaxis()->GetXmax()))-1;
    if(Pt>=(hmSF->GetYaxis()->GetXmax()))
      binPt= (hmSF->GetYaxis()->FindBin(hmSF->GetYaxis()->GetXmax()))-1;
    SFWeight=SFWeight*(hmSF->GetBinContent(binEta,binPt));//Multiply the scale factor with the one from previous file                                               
    delete hmSF;
  }
  //Vertex Weights for Medium ID
  static TDirectory *dmVSF1=0;
  if(!dmVSF1)dmVSF1= (TDirectoryFile*)fmSF1->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_vtx");
  if(VertexWeight){
    TH1F *hVSF=(TH1F*)dmVSF1->Get("tag_nVertices_ratio");
    Int_t Vbin=hVSF->GetXaxis()->FindBin(NVertices);
    if(NVertices<(hVSF->GetXaxis()->GetXmin()))
      Vbin= hVSF->GetXaxis()->FindBin(hVSF->GetXaxis()->GetXmin());
    if(NVertices>=(hVSF->GetXaxis()->GetXmax()))
      Vbin= (hVSF->GetXaxis()->FindBin(hVSF->GetXaxis()->GetXmax()))-1;
    SFWeight=SFWeight*(hVSF->GetBinContent(Vbin)/hVSF->GetBinContent(hVSF->GetXaxis()->FindBin(15)));
    delete hVSF;
  }
  //TrackingPOG_Eta_Based_Weights
  static TFile *TrPOG_SF1=0;
  if(!TrPOG_SF1)TrPOG_SF1=new TFile("./ScaleFactors/ratios_Tracking_efficiency_12p9ifb.root");
  TGraphAsymmErrors *etaRatio=(TGraphAsymmErrors*) TrPOG_SF1->Get("ratio_eta");
  Double_t xp,yp;
  //  etaRatio->GetPoint(i,xp,yp);
  for(int i=0;i<etaRatio->GetN();i++){
    etaRatio->GetPoint(i,xp,yp); 
    //    cout<<xp-etaRatio->GetErrorXlow(i)<<" "<<xp+etaRatio->GetErrorXhigh(i)<<" "<<yp<<endl;}
    if(Eta<=xp+etaRatio->GetErrorXhigh(i)&&Eta>xp-etaRatio->GetErrorXlow(i)){
      SFWeight=SFWeight*yp;break;}
    if(Eta>xp+etaRatio->GetErrorXhigh(i)&&i==(etaRatio->GetN()-1)){
      SFWeight=SFWeight*yp;break;}
    if(Eta<=xp-etaRatio->GetErrorXlow(i)&&i==0){
      SFWeight=SFWeight*yp;break;}
  }
  delete etaRatio;
  return SFWeight;
}
