#include <sys/stat.h>
#include <unistd.h>

void ZZ() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For ZZ
	std::string varexp = "NLEPTONS{2,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLEPTONS{0,400,20}:NGOODJETS{0,6}";
	
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
	
	mkdir("ZZ", 0755);
	chdir("ZZ");
	
	// ZZ control plot
	assembler->setRange("NLEPTONS", 4, 4);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 0, 50, false);
	
	
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 2, 2);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("ZZ_MLEPTONS.pdf");
	assembler->project("NGOODJETS", true)->plot(false, true)->SaveAs("ZZ_NGOODJETS.pdf");
	
	assembler->project("MLEPTONS", true)->print();
	
	assembler->setRange("NOSSF", 1, 2);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("ZZ_MLEPTONS_NOSSF12-0Taus.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("ZZ_MLEPTONS_NOSSF1-0Taus.pdf");
	
	assembler->setRange("NGOODTAUS", 1);
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("ZZ_MLEPTONS_NOSSF1-1orMoreTaus.pdf");
	
	assembler->setRange("NGOODTAUS");
	assembler->project("MLEPTONS", true)->plot(false, true)->SaveAs("ZZ_MLEPTONS_NOSSF1-0orMoreTaus.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
