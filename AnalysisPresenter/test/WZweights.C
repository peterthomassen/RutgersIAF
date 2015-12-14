#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void WZweights() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For WZ
	std::string varexp = "NLEPTONS[0]{3,6,\"NLEPTONS\"}:MOSSF[0]{6,126,36,\"MOSSF\"}:NOSSF[0]{0,2,\"NOSSF\"}:ONZ{0,2}:NGOODTAUS[0]{0,1,\"NGOODTAUS\"}:NBJETSCSVM[0]{0,2,\"NBJETSCSVM\"}:HT[0]{0,500,50,\"HT\"}:MET[0]{0,300,30,\"MET\"}:MLEPTONS[0]{76,106,9,\"MLIGHTLEPTONS\"}:MT[0]{0,300,30,\"MT\"}:NGOODJETS[0]{0,6,\"NGOODJETS\"}:ST[0]{0,1000,100,\"ST\"}";
	varexp += ":PTGOODJETS[0]{30,430,10,\"PTGOODJETS\"}";
	
	// Global cuts, if desired
	TString selection = ""; // "!(AIC && MET[0] < 50 && HT[0] < 200)";
	//selection += " && NGOODELECTRONS == 3";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	
	//assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	assembler->setMode("noWZsystematics");
	
	setupData(assembler);
	setupBackgroundMC(assembler, false, false);
	//setupBackgroundMC(assembler);
	setupBackgroundDD(assembler, "noTaus", true);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("WZweights", 0755);
	chdir("WZweights");
	
	TF1* f = new TF1("f", "pol1", 0, 500);
	
	// WZ control plot
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("MET", 50, 100, false);
	
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100_PTGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100_NGOODJETS.pdf");
	assembler->setRange("NGOODJETS", 1, 1);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100NGOODJETS1_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	assembler->setRange("NGOODJETS", 2, 2);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100NGOODJETS2_PTGOODJETS.pdf");
	assembler->setRange("NGOODJETS", 3, 3);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100NGOODJETS3_PTGOODJETS.pdf");
	assembler->setRange("NGOODJETS", 2);
	assembler->project("PTGOODJETS", true)->plot(false, f, 0, 0)->SaveAs("WZweights_MET50to100NGOODJETSgt1_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	assembler->setRange("NGOODJETS", 4);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100NGOODJETSgt3_PTGOODJETS.pdf");
	assembler->setRange("NGOODJETS");
	
	assembler->setRange("PTGOODJETS", 30, 70, false);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100PTGOODJETS30to70_PTGOODJETS.pdf");
	assembler->setRange("PTGOODJETS", 70, 110, false);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100PTGOODJETS70to110_PTGOODJETS.pdf");
	assembler->setRange("PTGOODJETS", 110, 150, false);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100PTGOODJETS110to150_PTGOODJETS.pdf");
	assembler->setRange("PTGOODJETS", 150);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100PTGOODJETSgt150_PTGOODJETS.pdf");
	assembler->setRange("PTGOODJETS");
	
	assembler->setRange("HT", 0, 200, false);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100HT0to200_NGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100HT0to200_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	
	assembler->setRange("HT", 200);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100HTgt200_PTGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZweights_MET50to100HTgt200_NGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	
	assembler->setRange("HT");
	assembler->setRange("MET");
	
	assembler->setRange("MT", 50, 100, false);
	
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MT50to100_PTGOODJETS.pdf");

	assembler->setRange("HT", 0, 200, false);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZweights_MT50to100HT0to200_NGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MT50to100HT0to200_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	
	assembler->setRange("HT", 200);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZweights_MT50to100HTgt200_PTGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZweights_MT50to100HTgt200_NGOODJETS.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
