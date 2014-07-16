void Z() {
	gSystem->Load("libRutgersIAF2012AnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For Z peak
	std::string varexp = "NLEPTONS{2,6}:NGOODELECTRONS{0,3}:NGOODMUONS{0,3}:NGOODELECTRONS%2{0,1}:NGOODMUONS%2{0,1}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,200,2}:MET{0,100,2}:MLEPTONS{76,106}";
	
	// Global cuts, if desired
	TString selection = "NOTTRILEPTONONZ";
	// for Zpeak
	selection += " && NLEPTONS == 3 && !(MLEPTONS > 76 && MLEPTONS < 106) && MET < 30 && MT < 50";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 100, false);
	
	assembler->setRange("NGOODELECTRONS%2", 1, 1);
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, true, 76, 106)->SaveAs("Z_elFake_MOSSF.pdf");
	assembler->setRange("NGOODELECTRONS", 1, 1);
	assembler->project("MOSSF", true)->plot(false, true, 76, 106)->SaveAs("Z_1el2mu_MOSSF.pdf");
	assembler->setRange("NGOODELECTRONS", 3, 3);
	assembler->project("MOSSF", true)->plot(false, true, 76, 106)->SaveAs("Z_3el_MOSSF.pdf");
	assembler->setRange("NGOODELECTRONS");
	assembler->setRange("NGOODELECTRONS%2");
	
	assembler->setRange("NGOODMUONS%2", 1, 1);
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, true, 76, 106)->SaveAs("Z_muFake_MOSSF.pdf");
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MOSSF", true)->plot(false, true, 76, 106)->SaveAs("Z_2el1mu_MOSSF.pdf");
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MOSSF", true)->plot(false, true, 76, 106)->SaveAs("Z_3mu_MOSSF.pdf");
	assembler->setRange("NGOODMUONS");
	assembler->setRange("NGOODMUONS%2");
	
	assembler->setRange();
	
	delete assembler;
}
