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
	std::string varexp = "NLIGHTLEPTONS{2,6}:MOSSF{6,126,36}:NOSSF{0,3}:ONZ{0,2}:NGOODTAUS{0,2}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLIGHTLEPTONS{20,540,13}:NGOODJETS{0,6}";
	
	// Global cuts, if desired
	TString selection = "PTGOODLEPTONS[0] > 25 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	
	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	//assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	assembler->setMode("noZZsystematics");
	assembler->setMode("fullPrecision");	
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
	assembler->setRange("NLIGHTLEPTONS", 4, 4);
	
	//assembler->setRange("NGOODTAUS", 0, 0);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_noCuts.pdf");
	
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MET", true)->plot(false)->SaveAs("ZZ_onZ_MET.pdf");
	//assembler->setRange("NBJETSCSVM", 0, 0);
	//assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 0, 50, false);
	
	
	//assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 2, 2);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS.pdf");
makeNicePlot(assembler->project("MLIGHTLEPTONS", true)->plot(false), "m_{4l}", "GeV")->SaveAs("../nicePlots/ZZ_DYz2MET0to50HT0to200_MLIGHTLEPTONS.pdf");
	assembler->project("MLIGHTLEPTONS", true)->print();
	assembler->setRange("NBJETSCSVM", 1);
assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("ZZ_MLIGHTLEPTONS_B1.pdf");
assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ZZ_NGOODJETS.pdf");
makeNicePlot(assembler->project("NGOODJETS", true)->plot(false), "n_{jets}")->SaveAs("../nicePlots/ZZ_DYz2MET0to50HT0to200_NGOODJETS.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
