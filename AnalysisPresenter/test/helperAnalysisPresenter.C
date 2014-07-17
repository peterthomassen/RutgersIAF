#include <iostream>
#include <TH1.h>
#include "RutgersIAF2012/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

void init(Assembler* assembler) {
	assembler = assembler; // Avoid compiler message about unused variable
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
}

void setupData(Assembler* assembler, bool fake = false, bool dilep = false) {
	std::string prefix = "/cms/thomassen/2014/Analysis/data/histograms/";
	std::string infix = dilep ? "" : ".3L";
	std::string suffix = ".root";
	
	PhysicsContribution* data = fake
		? new PhysicsContribution("data", prefix + "20140715_fakeTracks" + infix + suffix, 19500, "2012trackFakeSeed")
		: new PhysicsContribution("data", prefix + "20140627_data" + infix + suffix, 19500, "2012data");
	
	assembler->addContribution(data);
}

void setupBackgroundMC(Assembler* assembler, bool dilep = false) {
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
	Double_t xsec_ttw = 0.23;
	Double_t xsec_ttz = 0.208;
	
	// Peter's numbers
	double xsec_ttbar_fullLep = 23.08;
	double xsec_ttbar_semiLep = 97.97;
	double xsec_wz = 1.2451;
//	double xsec_zz = 0.181;
//	double xsec_ttw = 0.2149;
//	double xsec_ttz = 0.208;
	
	std::vector<PhysicsContribution*> mc;
	
	//PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZJetsTo3LNu" + infix + suffix, 2016678. / 1.2030, "WZ");
	PhysicsContribution* wz = new PhysicsContribution("backgroundMC", prefix + "WZJetsTo3LNu" + infix + suffix, 2016678. / xsec_wz, "WZ");
	//wz->addWeight("(NGOODJETS < 2) * 0.897051 + (NGOODJETS >= 2) * 2.0084"); // Richard's numbers
	wz->addWeight("(NGOODJETS == 0) * 1.10596 + (NGOODJETS == 1) * 0.78 + (NGOODJETS > 1) * 1");
	
	PhysicsContribution* zz = new PhysicsContribution("backgroundMC", prefix + "ZZJetsTo4L" + infix + suffix, 4804781. / xsec_zz, "ZZ");
	zz->addWeight("(NGOODJETS == 0) * 1.067 + (NGOODJETS == 1) * 0.83 + (NGOODJETS == 2) * 0.333 + (NGOODJETS > 2) * 1");
	
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWWJets" + infix + suffix, 217213. / 0.002037, "TTWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTWJets" + infix + suffix, 195555. / xsec_ttw, "TTW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTZJets" + infix + suffix, 209677. / xsec_ttz, "TTZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WWWJets" + infix + suffix, 220170. / 0.08217, "WWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WWZJets" + infix + suffix, 221805. / 0.0633, "WWZ"));
	mc.push_back(wz);
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "WZZJets" + infix + suffix, 219428. / 0.019, "WZZ"));
	mc.push_back(zz);
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "ZZZNoGstarJets" + infix + suffix, 224572. / 0.004587, "ZZZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", prefix + "TTJetsSemiLeptonic" + infix + suffix, 25365231. / xsec_ttbar_semiLep, "TT_SemiL"));
	
	PhysicsContribution* ttbar = new PhysicsContribution("backgroundMC", prefix + "TTJetsFullLeptonic" + infix + suffix, 12108679. / xsec_ttbar_fullLep, "TT_FullL");
	ttbar->addWeight("(NLEPTONS >= 3) * 1.5 + !(NLEPTONS >= 3) * 1");
	//ttbar->addWeight("(NGOODJETS < 2) * 1.42 + (NGOODJETS == 2) * 1.18 + (NGOODJETS == 3) * 1.04 + (NGOODJETS > 3) * 1"); // Richard's numbers
	ttbar->addWeight("(NGOODJETS < 2) * 1.50 + (NGOODJETS == 2) * 1.17 + (NGOODJETS == 3) * 1.11 + (NGOODJETS == 4) * 1.076 + (NGOODJETS > 4) * 1"); // Peter's numbers, regular bkgs + DY MC
	ttbar->addWeight("nTrackFakeElectrons + nTrackFakeMuons == 0");
//	ttbar->addFlatUncertainty("xsec", 0.3);
	mc.push_back(ttbar);
	
	if(dilep) {
		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-10To50" + infix + suffix, 7131530. / 762.45, "DY10to50"));
		mc.push_back(new PhysicsContribution("backgroundMC", prefix + "DYJetsToLL_M-50" + infix + suffix, 25095812. / 2950.0, "DYgt50"));
	}
	
	for(auto &contribution : mc) {
		assembler->addContribution(contribution);
	}
	
	assembler->addWeight("WEIGHT", "backgroundMC");
}

void setupBackgroundDD(Assembler* assembler) {
	std::vector<PhysicsContribution*> dd;
	dd.push_back(new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140715_fakeTracks.3L.root", assembler->getLumi(), "fakeTracks"));
	//dd.push_back(new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140618_fakePhotons.root", assembler->getLumi(), "fakePhotons"));
	//dd.push_back(new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140618_fakeMixed.root", assembler->getLumi(), "fakeMixed"));
	
	for(auto &contribution : dd) {
		contribution->addFlatUncertainty("fakeTracks", 0.25);
		assembler->addContribution(contribution);
	}
}

void setupFakeRates(Assembler* assembler) {
	// [PT] These numbers were obtained from the MOSSF plots on Z
	//assembler->setFakeRate("nTrackFakeElectrons", "(NLEPTONS > 2) * 0.02538");
	//assembler->setFakeRate("nTrackFakeMuons", "(NLEPTONS > 2) * 0.01544");
	
	// Matt's numbers
	//assembler->setFakeRate("nTrackFakeElectrons", "(NBJETSCSVM == 0) * ( (HT < 200) * 0.028 + (HT > 200) * 0.05 ) + (NBJETSCSVM >= 1) * 0.11");
	//assembler->setFakeRate("nTrackFakeMuons", "(NBJETSCSVM == 0) * 0.018 + (NBJETSCSVM >= 1) * 0.13");
	
	// Peter's numbers based on Matt's method
	assembler->setFakeRate("nTrackFakeElectrons", "(NBJETSCSVM == 0) * ( (HT < 200) * 0.0227594 + (HT > 200) * 0.0491398 ) + (NBJETSCSVM >= 1 && ONZ) * 0.0491398");
	assembler->setFakeRate("nTrackFakeMuons",     "(NBJETSCSVM == 0) * ( (HT < 200) * 0.0134250 + (HT > 200) * 0.0324227 ) + (NBJETSCSVM >= 1 && ONZ) * 0.0324227");
	
	// Turning off photon fakes for now
	assembler->setFakeRate("nPhotonFakeElectrons", "0");
	assembler->setFakeRate("nPhotonFakeMuons", "0");
}
