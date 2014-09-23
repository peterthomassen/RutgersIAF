void AIC() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For ZZ
	std::string varexp = "NLEPTONS{2,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODELECTRONS{0,3}:NGOODMUONS{0,3}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLEPTONS{0,400,20}:MLEPTONS*1{6,406,120}:NGOODJETS{0,6}";
	
	// Global cuts, if desired
	//TString selection = "NOTTRILEPTONONZ";
	TString selection = "";
	
	
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
	
	// ZZ control plot
	// selection += "NLEPTONS == 3 && NOSSF == 1 && !ONZ && NGOODTAUS == 0 && NBJETSCSVM == 0 && HT < 200 && MET < 50"; // Richard's
	//	selection += " && NLEPTONS == NGOODMUONS";
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 0, 50, false);
	
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("AIC_MLEPTONS.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_fine.pdf");
	
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_3mu.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_3mu_fine.pdf");
	assembler->setRange("NGOODMUONS");
	
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_2el1mu.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_2el1mu_fine.pdf");
	assembler->setRange("NGOODMUONS");
	
	assembler->setRange("NGOODELECTRONS", 3, 3);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_3el.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_3el_fine.pdf");
	assembler->setRange("NGOODELECTRONS");
	
	assembler->setRange("NGOODELECTRONS", 1, 1);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_1el2mu.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false, true)->SaveAs("AIC_MLEPTONS_1el2mu_fine.pdf");
	assembler->setRange("NGOODELECTRONS");
	
	assembler->setRange();
	
	delete assembler;
}
