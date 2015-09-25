#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void ZZ() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For ZZ
	std::string varexp = "NLEPTONS{2,6}:MOSSF{6,126,36}:NOSSF{0,3}:ONZ{0,2}:NGOODTAUS{0,2}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLEPTONS{0,400,20,\"MLIGHTLEPTONS\"}:NGOODJETS{0,6}";
	
	// Global cuts, if desired
	TString selection = "";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler);
	//setupBackgroundDD(assembler, "justTracks");
	setupBackgroundDD(assembler);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("ZZ", 0755);
	chdir("ZZ");
	
	// ZZ control plot
	assembler->setRange("NLEPTONS", 4, 4);
	
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_noCuts.pdf");
	
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 0, 50, false);
	
	
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 2, 2);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS.pdf");
//makeNicePlot(assembler->project("MLIGHTLEPTONS", true)->plot(false), "4L mass [GeV]")->SaveAs("../20150730/ZZ_DYz2MET0to50HT0to200_MLIGHTLEPTONS.pdf");
	assembler->project("MLIGHTLEPTONS", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ZZ_NGOODJETS.pdf");
	
	assembler->setRange("NOSSF", 1, 2);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_NOSSF12-0Taus.pdf");
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_NOSSF1-0Taus.pdf");
	
	assembler->setRange("NGOODTAUS", 1, 1);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_NOSSF1-1Tau.pdf");
	
	assembler->setRange("NGOODTAUS", 1);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_NOSSF1-1orMoreTaus.pdf");
	
	assembler->setRange("NGOODTAUS", 2);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_NOSSF1-2orMoreTaus.pdf");
	
	assembler->setRange("NGOODTAUS");
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_NOSSF1-0orMoreTaus.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
