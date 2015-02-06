#include <unistd.h>

void ttbar() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// for ttbar 2L
	std::string varexp = "NBJETSCSVM{0,2}:HT{0,1000,20}:MET{0,500,10}:ST{0,2000,20}:NGOODJETS{0,6}";
	
	// Global cuts, if desired
	TString selection = "NLEPTONS == 2 && NGOODTAUS == 0 && NPOSGOODELECTRONS == NNEGGOODMUONS && NNEGGOODELECTRONS == NPOSGOODMUONS";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	setupData(assembler, false, true);
	setupBackgroundMC(assembler, true);
	//setupBackgroundDD(assembler);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("ttbar", 0755);
	chdir("ttbar");
	
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("ST", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbar_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	assembler->project("HT", true)->plot(true)->SaveAs("ttbar_HT.pdf");
	assembler->project("MET", true)->plot(true)->SaveAs("ttbar_MET.pdf");
	assembler->project("ST", true)->plot(true)->SaveAs("ttbar_ST.pdf");
	
	assembler->setRange("ST", 300);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbar_NGOODJETS_STgt300.pdf");
	assembler->project("NGOODJETS", true)->print();
	assembler->project("HT", true)->plot(true)->SaveAs("ttbar_HT_STgt300.pdf");
	assembler->project("MET", true)->plot(true)->SaveAs("ttbar_MET_STgt300.pdf");
	assembler->project("ST", true)->plot(true)->SaveAs("ttbar_ST_STgt300.pdf");
	assembler->setRange();
	
	delete assembler;
}
