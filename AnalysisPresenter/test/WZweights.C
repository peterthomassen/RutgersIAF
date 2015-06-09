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
	std::string varexp = "NLEPTONS[0]{3,6,\"NLEPTONS\"}:MOSSF[0]{6,126,36,\"MOSSF\"}:NOSSF[0]{0,2,\"NOSSF\"}:ONZ{0,1}:NGOODTAUS[0]{0,1,\"NGOODTAUS\"}:NBJETSCSVM[0]{0,2,\"NBJETSCSVM\"}:HT[0]{0,500,50,\"HT\"}:MET[0]{0,300,30,\"MET\"}:MLEPTONS[0]{76,106,9,\"MLEPTONS\"}:MT[0]{0,300,30,\"MT\"}:NGOODJETS[0]{0,6,\"NGOODJETS\"}:ST[0]{0,1000,100,\"ST\"}";
	varexp += ":PTGOODJETS[0]{30,430,10,\"PTGOODJETS\"}";
	
	// Global cuts, if desired
	TString selection = "NOTTRILEPTONONZ";
	//selection += " && NGOODELECTRONS == 3";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler, false, false);
	//setupBackgroundMC(assembler);
	setupBackgroundDD(assembler);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("WZweights", 0755);
	chdir("WZweights");
	
	// WZ control plot
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("MET", 50, 100, false);
	
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100_PTGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100_NGOODJETS.pdf");
	assembler->setRange("NGOODJETS", 1, 1);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS1_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	assembler->setRange("NGOODJETS", 2, 2);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS2_PTGOODJETS.pdf");
	assembler->setRange("NGOODJETS", 3, 3);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS3_PTGOODJETS.pdf");
	assembler->setRange("NGOODJETS", 2);
	assembler->project("PTGOODJETS", true)->plot(false, 0, 0, "pol1")->SaveAs("WZ_MET50to100NGOODJETSgt1_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	
	assembler->setRange("NGOODJETS", 4);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETSgt3_PTGOODJETS.pdf");
	assembler->setRange("NGOODJETS");
	
	assembler->setRange("HT", 0, 200, false);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HT0to200_NGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HT0to200_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	
	assembler->setRange("HT", 200);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HTgt200_PTGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HTgt200_NGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	
	assembler->setRange("HT");
	assembler->setRange("MET");
	
	assembler->setRange("MT", 50, 100, false);
	
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100_PTGOODJETS.pdf");

	assembler->setRange("HT", 0, 200, false);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_NGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_PTGOODJETS.pdf");
	assembler->project("PTGOODJETS", true)->print();
	
	assembler->setRange("HT", 200);
	assembler->project("PTGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HTgt200_PTGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HTgt200_NGOODJETS.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
