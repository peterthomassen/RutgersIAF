void exampleMacro(TString ofname = "test.root") {
	gSystem->Load("libRutgersIAF2012AnalysisPresenter.so");
	TH1::AddDirectory(false);
	
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,150,3}";
	TString selection = "";
	
	PhysicsContribution* data = new PhysicsContribution("data", "/cms/thomassen/2014/Analysis/data/histograms/20140529_data.3L.root", 19500);
	
	PhysicsContribution* mc1 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTWWJets.3L.simulation.root", 217213. / 0.002037, "TTWW");
	PhysicsContribution* mc2 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTWJets.3L.simulation.root", 195555. / 0.2149, "TTW");
	PhysicsContribution* mc3 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTZJets.3L.simulation.root", 209677. / 0.208, "TTZ");
	PhysicsContribution* mc4 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WWWJets.3L.simulation.root", 220170. / 0.08217, "WWW");
	PhysicsContribution* mc5 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WWZJets.3L.simulation.root", 221805. / 0.0633, "WWZ");
	PhysicsContribution* mc6 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WZJetsTo3LNu.3L.simulation.root", 2016678. / 1.2030, "WZ");
	PhysicsContribution* mc7 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/WZZJets.3L.simulation.root", 219428. / 0.019, "WZZ");
	PhysicsContribution* mc8 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/ZZJetsTo4L.3L.simulation.root", 4804781. / 0.181, "ZZ");
	PhysicsContribution* mc9 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/ZZZNoGstarJets.3L.simulation.root", 224572. / 0.004587, "ZZZ");
	PhysicsContribution* mc10 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTJetsSemiLeptonic.3L.simulation.root", 25365231. / 97.97, "TT_SemiL");
	PhysicsContribution* mc11 = new PhysicsContribution("backgroundMC", "/cms/thomassen/2014/Analysis/simulation/histograms/TTJetsFullLeptonic.3L.simulation.root", 12108679. / 23.08, "TT_FullL");
	mc11->addWeight("1.5");
	
	PhysicsContribution* dd1 = new PhysicsContribution("backgroundDD", "/cms/thomassen/2014/Analysis/data/histograms/20140529_dataFake.3L.root", data->getLumi(), "emuFake");
	
	//mc->addFlatUncertainty("xsec", 0.3);
	
	Assembler* assembler = new Assembler(ofname);
	assembler->addContribution(data);
	assembler->addContribution(mc1);
	assembler->addContribution(mc2);
	assembler->addContribution(mc3);
	assembler->addContribution(mc4);
	assembler->addContribution(mc5);
	assembler->addContribution(mc6);
	assembler->addContribution(mc7);
	assembler->addContribution(mc8);
	assembler->addContribution(mc9);
	assembler->addContribution(mc10);
	assembler->addContribution(mc11);
	assembler->addContribution(dd1);
	assembler->setFakeRate("nFakeElectrons", 0.02538);
	assembler->setFakeRate("nFakeMuons", 0.01544);
	assembler->addWeight("ELIDISOWEIGHT", "backgroundMC");
	assembler->addWeight("MUIDISOWEIGHT", "backgroundMC");
	assembler->addWeight("PUWEIGHT", "backgroundMC");
	assembler->addWeight("TRIGGERWEIGHT", "backgroundMC");
	
	// Assemble everything
	assembler->process(varexp, selection);
	
	// So far, now taus and no b-jets
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	// HT loop
	for(int i = 0; i <= 0; i += 200) {
		if(i == 0) {
			assembler->setRange("HT", 0, 200, false);
			cout << "\n==== HT 0-200" << endl;
		} else {
			assembler->setRange("HT", 200);
			cout << "\n==== HT 200-inf" << endl;
		}
		
		// Reset any OSSF mass cuts from previous loop iteration
		assembler->setRange("MOSSF");
		
		// DY0, no requirements on ONZ
		cout << "DY0" << endl;
		assembler->setRange("NOSSF", 0, 0);
		assembler->setRange("ONZ");
		assembler->write("MET");
		
		// DYz1
		cout << endl;
		cout << "DYz1" << endl;
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 1, 1);
		assembler->write("MET");
		
		// DYl1
		cout << endl;
		cout << "DYl1" << endl;
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 0, 0);
		assembler->setRange("MOSSF", 0, 76, false);
		assembler->write("MET");
		
		// DYh1
		cout << endl;
		cout << "DYh1" << endl;
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 0, 0);
		assembler->setRange("MOSSF", 106);
		assembler->write("MET");
		
		continue;
		
		// DYo1
		cout << endl;
		cout << "DYo1" << endl;
		assembler->setRange("NOSSF", 1, 1);
		assembler->setRange("ONZ", 0, 0);
		assembler->setRange("MOSSF");
		assembler->write("MET");
	}
	
	delete assembler;
	delete data;
	delete mc1;
	delete dd1;
}
