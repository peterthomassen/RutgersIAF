void exampleMacro(TString ofname = "test.root") {
	gSystem->Load("libRutgersIAF2012AnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	//std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,100,2}:MLEPTONS{76,106}";
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,20}:MET{0,200,4}:MLEPTONS{76,106}";
	// Global cuts, if desired
	TString selection = "NOTTRILEPTONONZ";
	
	
	///////////////////////
	// Signal definition //
	///////////////////////
	PhysicsContribution* signal = new PhysicsContribution("signal", "/cms/data25/maritader/sim/Seesaw_Full_M-140_FDS_TuneZ2_8TeV.root", 126612. / 0.0669, "SeesawTo3Lminus_SyncedMC");
	// For now, the signal weights need to be applied here (maybe simplify this in the future?)
	signal->addWeight("ELIDISOWEIGHT");
	signal->addWeight("MUIDISOWEIGHT");
//	signal->addWeight("PUWEIGHT");
	signal->addWeight("TRIGGERWEIGHT");
	signal->addFlatUncertainty("dummy", 0.2);
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler(ofname, "RECREATE");
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler);
	//assembler->addContribution(signal); // It is important to add the signal before setting up the rake rates
	setupFakeRates(assembler);
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	assembler->save();
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	// Make some proof-of-concept plots
	
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 0, 0);
	assembler->project("MET", true)->plot()->SaveAs("L3DY0_MET.pdf");
	assembler->project("HT", true)->plot()->SaveAs("L3DY0_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MET", true)->plot()->SaveAs("L3DYz1_MET.pdf");
	assembler->project("HT", true)->plot()->SaveAs("L3DYz1_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 0, 76, false);
	assembler->project("MET", true)->plot()->SaveAs("L3DYl1_MET.pdf");
	assembler->project("HT", true)->plot()->SaveAs("L3DYl1_HT.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ"); // reset ONZ requirement (i.e. all on and off Z)
	assembler->setRange("MOSSF", 106);
	assembler->project("MET", true)->plot()->SaveAs("L3DYh1_MET.pdf");
	assembler->project("HT", true)->plot()->SaveAs("L3DYh1_HT.pdf");
	
	
	/////////////////
	// Make tables //
	/////////////////
	
	// Reset all cuts
	assembler->setRange();
	
	// So far, no taus
	assembler->setRange("NGOODTAUS", 0, 0);
	
	cout << endl;
	cout << "3L DYz1 with trileptons on Z" << endl;
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("MLEPTONS", 76, 106, false);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->print();
	assembler->setRange("MLEPTONS");
	
	// nLeptons loop
	for(int nLeptons = 3; nLeptons <= 4; nLeptons += 1) {
		if(nLeptons == 3) {
			assembler->setRange("NLEPTONS", 3, 3);
			cout << "\n==== 3L" << endl;
		} else {
			assembler->setRange("NLEPTONS", 4);
			cout << "\n==== >=4L" << endl;
		}
		
		// HT loop
		for(int i = 0; i <= 200; i += 200) {
			if(i == 0) {
				assembler->setRange("HT", 0, 200, false);
				cout << "\n==== HT 0-200" << endl;
			} else {
				assembler->setRange("HT", 200);
				cout << "\n==== HT 200-inf" << endl;
			}
			
			// b-tag loop
			for(int j = 0; j <= 1; ++j) {
				if(j == 0) {
					assembler->setRange("NBJETSCSVM", 0, 0);
					cout << "\n==== 0b" << endl;
				} else {
					delete assembler;
					return;
					assembler->setRange("NBJETSCSVM", 1);
					cout << "\n==== >=1b" << endl;
				}
				
				// Reset any OSSF mass cuts from previous loop iteration
				assembler->setRange("MOSSF");
				
				if(nLeptons == 3) {
					// DY0, no requirements on ONZ
					cout << "DY0" << endl;
					assembler->setRange("NOSSF", 0, 0);
					assembler->setRange("ONZ");
					assembler->project("MET", true)->print();
					
					// DYz1
					cout << endl;
					cout << "DYz1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 1, 1);
					assembler->project("MET", true)->print();
					assembler->save("MET");
					//assembler->save("MET", "L3Tau0DYz1B0HT0to200");
					
					// DYl1
					cout << endl;
					cout << "DYl1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 0, 0);
					assembler->setRange("MOSSF", 0, 76, false);
					assembler->project("MET", true)->print();
					
					// DYh1
					cout << endl;
					cout << "DYh1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 0, 0);
					assembler->setRange("MOSSF", 106);
					assembler->project("MET", true)->print();
				}
				
				if(nLeptons == 4) {
					// DY0, no requirements on ONZ
					cout << "DY0" << endl;
					assembler->setRange("NOSSF", 0, 0);
					assembler->setRange("ONZ");
					assembler->project("MET", true)->print();
					
					// DYz1
					cout << endl;
					cout << "DYz1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 1, 1);
					assembler->project("MET", true)->print();
					
					// DYn1
					cout << endl;
					cout << "DYn1" << endl;
					assembler->setRange("NOSSF", 1, 1);
					assembler->setRange("ONZ", 0, 0);
					assembler->project("MET", true)->print();
					
					// DYz2
					cout << endl;
					cout << "DYz2" << endl;
					assembler->setRange("NOSSF", 2, 2);
					assembler->setRange("ONZ", 1, 1);
					assembler->project("MET", true)->print();
					
					// DYn2
					cout << endl;
					cout << "DYn2" << endl;
					assembler->setRange("NOSSF", 2, 2);
					assembler->setRange("ONZ", 0, 0);
					assembler->project("MET", true)->print();
				}
			}
		}
	}
	
	delete assembler;
}
