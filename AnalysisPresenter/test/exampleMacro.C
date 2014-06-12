void exampleMacro(TString ofname = "test.root") {
	gSystem->Load("libRutgersIAF2012AnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,150,3}";
	// Global cuts, if desired
	TString selection = "";
	
	
	///////////////////////
	// Signal definition //
	///////////////////////
	PhysicsContribution* signal = new PhysicsContribution("signal", "/cms/data25/maritader/sim/Seesaw_Full_M-140_FDS_TuneZ2_8TeV.root", 126612 / 0.0669, "SeesawTo3Lminus_SyncedMC");
	// For now, the signal weights need to be applied here (this will change shortly)
	signal->addWeight("ELIDISOWEIGHT");
	signal->addWeight("MUIDISOWEIGHT");
	//signal->addWeight("PUWEIGHT");
	signal->addWeight("TRIGGERWEIGHT");
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler(ofname);
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler);
	assembler->addContribution(signal); // It is important to add the signal before setting up the rake rates
	setupFakeRates(assembler);
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	
	
	/////////////////
	// Make tables //
	/////////////////
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	// So far, exactly 3L, no taus and no b-jets
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
}
