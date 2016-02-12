#include <sys/stat.h>
#include <unistd.h>
#include "helperAnalysisSkeleton.C"

void AnalysisSkeleton() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	std::string varexp = "NLEPTONS{2,6}";
	
	// Global cuts, if desired
	TString selection = "PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[1] > 15 && Alt$(PTGOODLEPTONS[2] > 10, 1)";
	
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
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("skeleton", 0755);
	chdir("skeleton");
	
	// Check for duplicate events
	//assembler->project("NLEPTONS", true)->getMeta(); // printMeta();
	
	// Go ahead and make some plots!
	assembler->project("NLEPTONS", true)->print();
	
	// Clean up
	delete assembler;
}
