void exampleMacro(TString ofname = "test.root") {
	gSystem->Load("libRutgersIAF2012AnalysisPresenter.so");
	TH1::AddDirectory(false);
	
	PhysicsContribution* contributionData = new PhysicsContribution("/cms/thomassen/2014/Analysis/data/histograms/20140522_data.3L.root", 19500);
	PhysicsContribution* contributionMC1 = new PhysicsContribution("/cms/thomassen/2014/Analysis/simulation/histograms/WZJetsTo3LNu.3L.simulation.root", 2016678. / 1.1735);
	PhysicsContribution* contributionMC2 = new PhysicsContribution("/cms/thomassen/2014/Analysis/simulation/histograms/ZZJetsTo4L.3L.simulation.root", 4804781. / 0.181);
	
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,150,3}";
	std::string selection = "!(NLEPTONS == 3 && MLEPTONS > 76 && MLEPTONS < 106)";
	//std::string selection = "!(MLEPTONS > 76 && MLEPTONS < 106)";
	selection += " && nFakeMuons + nFakeElectrons == 0";
//	selection += " && (LOWDYOSMINMLL > 12)";
	
	Assembler* assembler = new Assembler(ofname);
	assembler->addData(contributionData);
	assembler->addBackground(contributionMC1);
	assembler->addBackground(contributionMC2);
	
	assembler->process(varexp, selection);
//	cout << hn->GetEntries() << endl;
	
	// So far, now taus and no b-jets
	assembler->setRange("NLEPTONS", 3, 4);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	for(int i = 0; i <= 1; ++i) {
		if(i == 0) {
			assembler->setRange("HT", 0, 200, false);
			cout << "\n==== HT 0-200" << endl;
		} else if(i == 1) {
			assembler->setRange("HT", 200);
			cout << "\n==== HT 200-inf" << endl;
		}
		
		// In general, make no assumption on the OSSF mass (think of DY0)
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
	delete contributionData;
}
