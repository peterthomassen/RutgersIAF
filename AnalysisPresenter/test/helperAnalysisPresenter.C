#include <iostream>
#include <TH1.h>
#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

void init(Assembler* assembler) {
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
	
	Bundle* fakeBundle = new Bundle("background", "Fakes");
	assembler->addBundle(fakeBundle);
	
	Bundle* bundleHiggs = new Bundle("background", "Higgs");
	assembler->addBundle(bundleHiggs);
	
	Bundle* rareBundle = new Bundle("background", "Rare MC");
	assembler->addBundle(rareBundle);
	
	//assembler->setMinScale(0.1);
}

void prepare(Assembler* assembler) {
	Bundle* presentationBundle = new Bundle("background", "presentationBundle");
	presentationBundle->addComponent(assembler->getBundle("Fakes"));
	presentationBundle->addComponent(assembler->getBundle("Higgs"));
	presentationBundle->addComponent(assembler->getBundle("Rare MC"));
	
	assembler->setDefaultBundle(presentationBundle);
	
	assembler->getDefaultBundle()->print();
}

void setupData(Assembler* assembler, bool fake = false, bool dilep = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".root";
	
	PhysicsContribution* data = fake
		? new PhysicsContribution("data", prefix + "20150518_data" + infix + suffix, 19500, "2012data", false, "treeRfakeTracks")
		: new PhysicsContribution("data", prefix + "20150518_data" + infix + suffix, 19500, "2012data");
	
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
	wz->addWeight("(NGOODJETS[0] == 0) * 1.06 + (NGOODJETS[0] == 1) * 0.89 + (NGOODJETS[0] == 2) * 1.18 + (NGOODJETS[0] > 2) * 1.32");
	wz->addWeight("!(NGOODJETS > 1) + (NGOODJETS > 1) * Alt$((PTGOODJETS[0] < 70) * 0.75 + (PTGOODJETS[0] >= 70 && PTGOODJETS[0] < 110) * 1.16 + (PTGOODJETS[0] >= 110 && PTGOODJETS[0] < 150) * 0.88 + (PTGOODJETS[0] >= 150) * 1.26, 0)");
	//wz->addWeight("1 + (NBJETSCSVM > 0) * 0.0"); // look with more data whether MC gets number of b's right
	wz->addFlatUncertainty("normalizationWZ", 0.05);
	correlationBundle->addComponent(wz);
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZJetsTo4L" + infix + suffix, xsec_zz, "ZZ");
	zz->addWeight("(NGOODJETS[0] == 0) * 1.084 + (NGOODJETS[0] == 1) * 0.75 + (NGOODJETS[0] == 2) * 0.333 + (NGOODJETS[0] > 2) * 1");
	correlationBundle->addComponent(zz);
	
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWWJets" + infix + suffix, 0.002037, "TTWW"));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWJets" + infix + suffix, xsec_ttw, "TTW"));
	mcRare.push_back(new PhysicsContribution("backgroundMC", prefix + "TTZJets" + infix + suffix, xsec_ttz, "TTZ"));
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
		if(dilep && !onlyTTF) {
			PhysicsContribution* ttbarS = new PhysicsContribution("backgroundMC", prefix + "TTJetsSemiLeptonic" + infix + suffix, xsec_ttbar_semiLep, "TT_SemiL");
			ttbarS->addWeight(nJetWeight);
			mc.push_back(ttbarS);
			bundleTTbar->addComponent(ttbarS);
		}
		
		//PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + ".3LonZ" + suffix, xsec_ttbar_fullLep, "TT_FullL");
		PhysicsContribution* ttbarF = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullL");
		ttbarF->addWeight("1.2 - 0.04 * NPROMPTNONISOINCLUSIVETRACKS7[0]");
		ttbarF->addWeight(nJetWeight);
		//ttbarF->addWeight("nTrackFakeElectrons + nTrackFakeMuons == 0");
		ttbarF->addWeight("1 + (NLEPTONS[0] >= 3) * 0.66");
//		ttbarF->addFlatUncertainty("xsec", 0.3);
		ttbarF->addFlatUncertainty("fudge", 0.194);
		mc.push_back(ttbarF);
		bundleTTbar->addComponent(ttbarF);
		
		std::vector<PhysicsContribution*> ttbarFfake;
		ttbarFfake.push_back(new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullLfake", true, "treeRfakeTracks"));
		ttbarFfake.push_back(new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullLfake", true, "treeRfakePhotons"));
		ttbarFfake.push_back(new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, xsec_ttbar_fullLep, "TT_FullLfake", true, "treeRfakeTaus"));
		for(auto &contribution : ttbarFfake) {
			contribution->addWeight("1.2 - 0.04 * NPROMPTNONISOINCLUSIVETRACKS7[0]");
			contribution->addWeight(nJetWeight);
			//ttbarFfake->addWeight("nTrackFakeElectrons + nTrackFakeMuons == 0");
			contribution->addWeight("1 + (NLEPTONS[0] >= 3) * 0.66");
//			ttbarFfake->addFlatUncertainty("xsec", 0.3);
			contribution->addFlatUncertainty("fudge", 0.194);
			mc.push_back(contribution);
			assembler->getBundle("Fakes")->addComponent(contribution);
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
	
	for(auto &contribution : mcRare) {
		contribution->addWeight("WEIGHT[0]");
		assembler->addContribution(contribution);
		assembler->getBundle("Rare MC")->addComponent(contribution);
	}
	
	if(onlyTTF) {
		return;
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
	Bundle* fakeBundle = assembler->getBundle("Fakes");
	
	////// Tracks
	PhysicsContribution* fakeTracks = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20150518_data.3L.root", assembler->getLumi(), "fakeTracks", false, "treeRfakeTracks", (option == "justTracks") ? kWhite : -1);
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
		fakeBundle->addComponent(fakeTracks);
		assembler->addContribution(fakeTracks);
	}
	
	////// Taus
	PhysicsContribution* fakeTaus = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20150518_data.3L.root", assembler->getLumi(), "fakeTaus", false, "treeRfakeTaus");
	fakeTaus->addWeight("fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15");
	if(syst) {
		fakeTaus->addFlatUncertainty("tauFit", 0.11); // for HT > 200 GeV, it is that high
	}
	if(option != "noTaus" && option != "justTracks" && option != "justPhotons" && option != "fakeTaus2L") {
		fakeBundle->addComponent(fakeTaus);
		assembler->addContribution(fakeTaus);
	}
	
	////// Taus (2L)
	PhysicsContribution* fakeTaus2L = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20150518_data.root", assembler->getLumi(), "fakeTaus2L", false, "treeRfakeTaus");
	fakeTaus2L->addWeight("fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15");
	if(syst) {
		fakeTaus2L->addFlatUncertainty("tauFit", 0.11); // for HT > 200 GeV, it is that high
	}
	if(option == "fakeTaus2L") {
		assembler->addContribution(fakeTaus2L);
	}
	
	////// Photons
	PhysicsContribution* fakePhotons = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20150518_data.3L.root", assembler->getLumi(), "fakePhotons", false, "treeRfakePhotons");
	if(syst) {
		fakePhotons->addFlatUncertainty("photonElFake", 0.15);
		//fakePhotons->addFlatUncertainty("photonFudge", 0.25);
		//fakePhotons->setEnsembleFakeRateParam(fakeTracks, "NPROMPTTRACKS7", "0*(x < [0]) + 1*(x > 2*[0]) + (x/[0] - 1)*(x >= [0] && x <= 2*[0])");
	}
	if(option != "noPhotons" && option != "justTracks" && option != "justTaus" && option != "fakeTaus2L") {
		fakeBundle->addComponent(fakePhotons);
		assembler->addContribution(fakePhotons);
	}
}

void setupFakeRates(Assembler* assembler) {
	// We found that NGOODJETS and HT binning does not work very well; NPROMPTINCLUSIVETRACK7 binning does a good job at least in 0b regions.
	assembler->setFakeRate("nTrackFakeMuons",
		"(NGOODTAUS == 0) * ("
			"0.0154" // "(NGOODMUONS[0]==1)*(0.01384 + -0.0003956*NPROMPTNONISOINCLUSIVETRACKS7[0]) + (NGOODMUONS[0]==3)*(0.01697 + -0.0001669*NPROMPTNONISOINCLUSIVETRACKS7[0])"
			" * (1 + 1.4 * (NBJETSCSVM[0] > 0))"
		")"
	);
	assembler->setFakeRate("nTrackFakeElectrons",
		"(NGOODTAUS == 0) * ("
			"((NLEPTONS[0]==3&&NGOODELECTRONS[0]==1)*(0.006771 + 0.005532*NPROMPTNONISOINCLUSIVETRACKS7[0]) + (NLEPTONS[0]==3&&NGOODELECTRONS[0]==3)*(0.009287 + -0.001487*NPROMPTNONISOINCLUSIVETRACKS7[0])"
			"+ (NLEPTONS[0]!=3||!(NGOODELECTRONS[0]%2))*(0.007453 + 0.003052*NPROMPTNONISOINCLUSIVETRACKS7[0]))" // this is not the average of the above, but measured (because of relative fractions)
			" * (1 + 1.4 * (NBJETSCSVM[0] > 0))"
		")"
	);
	
/*	assembler->setFakeRate("nTauFakeTaus", 
		"(fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15) * ("
			"(NLEPTONS[0] == 3 && NGOODELECTRONS[0] == 2) * ( (NPROMPTNONISOINCLUSIVETRACKS7[0] == 0) * 0.0090"
				" + (NPROMPTNONISOINCLUSIVETRACKS7[0] >= 1 && NPROMPTNONISOINCLUSIVETRACKS7[0] <= 3) * (0.0198891 + 0.00652005 * NPROMPTNONISOINCLUSIVETRACKS7[0]) "
				" + (NPROMPTNONISOINCLUSIVETRACKS7[0] > 3) * (0.0424706 - 0.00225938 * NPROMPTNONISOINCLUSIVETRACKS7[0]) "
			") * 1.2"
			"+ (NLEPTONS[0] == 3 && NGOODMUONS[0] == 2) * ( (NPROMPTNONISOINCLUSIVETRACKS7[0] == 0) * 0.0093"
				" + (NPROMPTNONISOINCLUSIVETRACKS7[0] >= 1 && NPROMPTNONISOINCLUSIVETRACKS7[0] <= 3) * (0.0255488 + 0.00560732 * NPROMPTNONISOINCLUSIVETRACKS7[0]) "
				" + (NPROMPTNONISOINCLUSIVETRACKS7[0] > 3) * (0.0471066 - 0.00269566 * NPROMPTNONISOINCLUSIVETRACKS7[0]) "
			") * 1.2"
			// Now el-mu-tau and 4L with both light flavors. el-el-el-tau and mu-mu-mu-tau missing!
			" + (NGOODELECTRONS[0] > 0 && NGOODMUONS[0] > 0) * ( (HT[0] < 200) * 0.022 + !(HT[0] < 200) * 0.019 )"
		")"
	);*/
	
/*
	// mZ = 91 \pm 10
	assembler->setFakeRate("nTauFakeTaus",
		//"Alt$(fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15, 0) * (0.2395 - 0.0004384 * HT[0])" // w/o track/photon subtraction and with 30 binning
		"Alt$(fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15, 0) * (" // w/o track/photon subtraction and with 200 binning
			"(NBJETSCSVM == 0) * ("
				"(NLEPTONS[0]==3&&NGOODMUONS[0]==0) * (0.2562 - 0.0003139 * HT[0])"
				" + (NLEPTONS[0]==3&&NGOODMUONS[0]==2) * (0.2503 - 0.0002499 * HT[0])"
				" + (NLEPTONS[0]!=3 || NGOODMUONS[0]==1) * (0.25325 - 0.0002819 * HT[0])"
			") + (NBJETSCSVM > 0) * ("
				"(NLEPTONS[0]==3&&NGOODMUONS[0]==0) * (0.2129 - 0.0003078 * HT[0])"
				" + (NLEPTONS[0]==3&&NGOODMUONS[0]==2) * (0.2339 - 0.0002751 * HT[0])"
				" + (NLEPTONS[0]!=3 || NGOODMUONS[0]==1) * (0.2234 - 0.00029145 * HT[0])"
			")"
		")"
	);
*/
	
	// mZ = 90 \pm 15
	assembler->setFakeRate("nTauFakeTaus",
		//"Alt$(fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15, 0) * (0.2395 - 0.0004384 * HT[0])" // w/o track/photon subtraction and with 30 binning
		"Alt$(fakeRoleGOODTAUS > 0 && TOTALISOGOODTAUS > 6 && TOTALISOGOODTAUS < 15, 0) * (" // w/o track/photon subtraction and with 200 binning
			"(NBJETSCSVM == 0) * ("
				"(NLEPTONS[0]==3&&NGOODMUONS[0]==0) * (0.2584 - 0.0003302 * HT[0])"
				" + (NLEPTONS[0]==3&&NGOODMUONS[0]==2) * (0.2504 - 0.0002508 * HT[0])"
				" + (NLEPTONS[0]!=3 || NGOODMUONS[0]==1) * (0.2544 - 0.0002905 * HT[0])"
			") + (NBJETSCSVM > 0) * ("
				"(NLEPTONS[0]==3&&NGOODMUONS[0]==0) * (0.2100 - 0.0003165 * HT[0])"
				" + (NLEPTONS[0]==3&&NGOODMUONS[0]==2) * (0.2354 - 0.0002913 * HT[0])"
				" + (NLEPTONS[0]!=3 || NGOODMUONS[0]==1) * (0.2227 - 0.0003039 * HT[0])"
			")"
		")"
	);
	
	// Photon fake rates for Asymmetric Internal Conversions (AIC)
	// AIC reduces the pt of the emitting lepton, and can push on-Z pairs below the Z peak. This causes migration between on-Z/off-Z etc.
	// Looking at the AIC control region, we find that we should adjust the fake rate outside MLEPTONS = 75..100.
	assembler->setFakeRate("nPhotonFakeMuons",
		"(NGOODTAUS == 0) * ("
			"(NOSSF == 1 && !ONZ && MOSSF < 91) * 0.00295 / ( (1 + 0.5 * (MLEPTONS[0] < 75 || MLEPTONS[0] > 100) ) * (1 + ONZ) ) * (1 + 1.4 * (NBJETSCSVM[0] > 0))"
		")"
	);
	assembler->setFakeRate("nPhotonFakeElectrons",
		"(NGOODTAUS == 0) * ("
			"0.0088 / ( (1 + 0.5 * (MLEPTONS[0] < 75 || MLEPTONS[0] > 100) ) * (1 + ONZ) ) * (1 + 1.4 * (NBJETSCSVM[0] > 0))"
		")"
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

std::vector<double> getFirst(std::vector<std::pair<double, double> > list) {
	std::vector<double> list2;
	for(size_t i = 0; i < list.size(); ++i) {
		list2.push_back(list[i].first);
	}
	return list2;
}

std::vector<double> getSecond(std::vector<std::pair<double, double> > list) {
	std::vector<double> list2;
	for(size_t i = 0; i < list.size(); ++i) {
		list2.push_back(list[i].second);
	}
	return list2;
}

void writeUncertainties(AssemblerProjection* projection) {
	cout << endl << "====== now printing uncertainties" << endl;
	
	auto uncertaintyNames = projection->getUncertaintyNames();
	for(int i = 1; i <= 5; ++i) {
		cout << endl;
		cout << "BIN " << i << endl;
		cout << "TOTAL:";
		cout << " " << projection->getBin("background", i);
		cout << " pm " << projection->getBinStat("background", i) << " pm " << projection->getBinSyst("background", i) << endl;
		for(const auto &uncertaintyName : uncertaintyNames) {
			cout << "uncertainty name: " << uncertaintyName << " " << projection->getBinSyst("background", i, uncertaintyName) << endl;
		}
		cout << endl;
		
		for(const auto &bundleName : projection->getBundleNames("background")) {
			cout << "bundleName: " << bundleName;
			cout << " " << projection->getBin("background", i, bundleName);
			cout << " pm " << projection->getBinStat("background", i, bundleName) << endl;
			for(const auto &uncertaintyName : uncertaintyNames) {
				cout << "uncertainty name: " << uncertaintyName << " " << projection->getBinSyst("background", i, uncertaintyName, bundleName) << endl;
			}
		}
	}
}
