#include <iostream>
#include <TH1.h>
#include "RutgersIAF2012/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF2012/AnalysisPresenter/interface/PhysicsContribution.h"

void init(Assembler* assembler) {
	assembler = assembler; // Avoid compiler message about unused variable
	TH1::AddDirectory(false);
}

void setupData(Assembler* assembler) {
	PhysicsContribution* data = new PhysicsContribution("data", "/cms/thomassen/2014/Analysis/data/histograms/20140529_data.3L.root", 19500);
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
	//mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/ZZJetsTo4L.3L.simulation.root", 4804781. / 0.181, "ZZ"));
		std::cout << "Skipping ZZJetsTo4L because it takes quite long ..." << std::endl;
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/ZZZNoGstarJets.3L.simulation.root", 224572. / 0.004587, "ZZZ"));
	mc.push_back(new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTJetsSemiLeptonic.3L.simulation.root", 25365231. / 97.97, "TT_SemiL"));
	
	PhysicsContribution* ttbar = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTJetsFullLeptonic.3L.simulation.root", 12108679. / 23.08, "TT_FullL");
	ttbar->addWeight("1.5");
	mc.push_back(ttbar);
	//mc->addFlatUncertainty("xsec", 0.3);
	
	for(auto &contribution : mc) {
		assembler->addContribution(contribution);
	}
	
	assembler->addWeight("ELIDISOWEIGHT", "backgroundMC");
	assembler->addWeight("MUIDISOWEIGHT", "backgroundMC");
	assembler->addWeight("PUWEIGHT", "backgroundMC");
	assembler->addWeight("TRIGGERWEIGHT", "backgroundMC");
}

void setupBackgroundDD(Assembler* assembler) {
	// Data-driven backgrounds
	PhysicsContribution* dd1 = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140529_dataFake.3L.root", assembler->getLumi(), "emuFake");
	assembler->addContribution(dd1);
}

void setupFakeRates(Assembler* assembler) {
	assembler->setFakeRate("nFakeElectrons", 0.02538);
	assembler->setFakeRate("nFakeMuons", 0.01544);
}
