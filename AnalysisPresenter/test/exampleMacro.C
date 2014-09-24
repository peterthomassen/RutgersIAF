#include <sys/stat.h>
#include <unistd.h>

void exampleMacro(TString ofname = "test.root") {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For inclusive table
	std::string varexp = "NLEPTONS{2,6}:MOSSF{11,131,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,200,1}:MET{0,200,20}:LT{0,500,10}:MLEPTONS{81,101}";
	varexp += ":OSSFMAXMLL{11,131,36}:OSSFMINMLL{11,131,36}";
	
	// Global cuts, if desired
	// Get rid of photon conversions
	TString selection = "(NOSSF != 1 || NOTTRILEPTONONZ)";
	// Cut down charge flips
	// commented out because NPOSGOODMUONS etc. is not available in tcH ntuple
	//selection += " && (NLEPTONS != 3 || (NGOODMUONS == 3 || NGOODELECTRONS == 3 || abs(NPOSGOODMUONS+NPOSGOODELECTRONS-NNEGGOODMUONS-NNEGGOODELECTRONS) != 3))";
	
	
	///////////////////////
	// Signal definition //
	///////////////////////
	PhysicsContribution* signal = new PhysicsContribution("signal", "/users/h2/heindl/simulation/histograms/tcH_zz.simulation.root", (0.01 * 245.8) * 0.0289, "SeesawTo3Lminus_SyncedMC");
	signal->addWeight("WEIGHT");
	//signal->addFlatUncertainty("dummy", 0.2);
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler(ofname, "RECREATE");
	init(assembler);
	setupData(assembler);
	setupBackgroundMC(assembler, false, false);
	setupBackgroundDD(assembler);
	assembler->addContribution(signal); // It is important to add the signal before setting up the rake rates
	setupFakeRates(assembler);
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	assembler->save();
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("exampleMacro", 0755);
	chdir("exampleMacro");
	
	// Inclusive plots: 3L
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 200);
	assembler->setRange("MET", 0, 30, false);
	assembler->project("LT", true)->plot(true, true)->SaveAs("L3DYz1B0HTgt200MET0to30_LT.pdf");
	assembler->project("LT", true)->print();
	
	assembler->setRange();
	
	delete assembler;
}
