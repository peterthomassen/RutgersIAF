#include <iostream>
#include <TH1.h>
#include "RutgersIAF2012/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

void init(Assembler* assembler) {
	assembler = assembler; // Avoid compiler message about unused variable
	TH1::AddDirectory(false);
	TH1::SetDefaultSumw2(true);
}

void setupData(Assembler* assembler) {
	PhysicsContribution* data = new PhysicsContribution("data", "/cms/thomassen/2014/Analysis/data/histograms/20140618_data.3L.root", 19500, "2012data");
	assembler->addContribution(data);
}

void setupBackgroundMC(Assembler* assembler) {
	std::vector<PhysicsContribution*> mc;
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTWWJets.3L.simulation.root", 217213. / 0.002037, "TTWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTWJets.3L.simulation.root", 195555. / 0.2149, "TTW"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTZJets.3L.simulation.root", 209677. / 0.208, "TTZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WWWJets.3L.simulation.root", 220170. / 0.08217, "WWW"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WWZJets.3L.simulation.root", 221805. / 0.0633, "WWZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WZJetsTo3LNu.3L.simulation.root", 2016678. / 1.2030, "WZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WZZJets.3L.simulation.root", 219428. / 0.019, "WZZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/ZZJetsTo4L.3L.simulation.root", 4804781. / 0.181, "ZZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/ZZZNoGstarJets.3L.simulation.root", 224572. / 0.004587, "ZZZ"));
//	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTJetsSemiLeptonic.3L.simulation.root", 25365231. / 97.97, "TT_SemiL"));
	
	PhysicsContribution* ttbar = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTJetsFullLeptonic.3L.simulation.root", 12108679. / 23.08, "TT_FullL");
	ttbar->addWeight("1.5");
	ttbar->addFlatUncertainty("xsec", 0.3);
//	mc.push_back(ttbar);
	
	for(auto &contribution : mc) {
		assembler->addContribution(contribution);
	}
	
	assembler->addWeight("WEIGHT", "backgroundMC");
}

void setupBackgroundDD(Assembler* assembler) {
	std::vector<PhysicsContribution*> dd;
	dd.push_back(new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140618_fakeTracks.root", assembler->getLumi(), "fakeTracks"));
	//dd.push_back(new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140618_fakePhotons.root", assembler->getLumi(), "fakePhotons"));
	//dd.push_back(new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140618_fakeMixed.root", assembler->getLumi(), "fakeMixed"));
	
	for(auto &contribution : dd) {
		//contribution->addFlatUncertainty("test", 0.5);
		assembler->addContribution(contribution);
	}
}

void setupFakeRates(Assembler* assembler) {
	//assembler->setFakeRate("nTrackFakeElectrons", "0.02538");
	//assembler->setFakeRate("nTrackFakeMuons", "0.01544");
	
	// Matt's numbers
	assembler->setFakeRate("nTrackFakeElectrons", "(NBJETSCSVM == 0) * ( (HT < 200) * 0.028 + (HT > 200) * 0.05 ) + (NBJETSCSVM > 1) * 0.11");
	assembler->setFakeRate("nTrackFakeMuons", "(NBJETSCSVM == 0) * 0.018 + (NBJETSCSVM > 1) * 0.13");
	
	assembler->setFakeRate("nPhotonFakeElectrons", "0");
	assembler->setFakeRate("nPhotonFakeMuons", "0");
}
