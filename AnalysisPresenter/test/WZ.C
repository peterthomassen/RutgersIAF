void WZ() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For WZ
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLEPTONS{76,106,9}:MT{0,300,30}:NGOODJETS{0,6}";
	
	// Global cuts, if desired
	TString selection = "NOTTRILEPTONONZ";
	
	
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
	
	// WZ control plot
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 50, 100, false);
	assembler->project("MT", true)->plot(false, true)->SaveAs("WZ_MT.pdf");
	assembler->project("NGOODJETS", true)->plot(false, true)->SaveAs("WZ_MET50to100_NGOODJETS.pdf");
	assembler->setRange("MET");
	assembler->setRange("MT", 50, 100, false);
	assembler->project("MET", true)->plot(false, true)->SaveAs("WZ_MET.pdf");
	assembler->project("NGOODJETS", true)->plot(false, true)->SaveAs("WZ_MT50to100_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	assembler->setRange();
	
	delete assembler;
}
