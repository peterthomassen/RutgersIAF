#include <sys/stat.h>
#include <unistd.h>

void WZ() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For WZ
	std::string varexp = "NLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLEPTONS{76,106,9}:MT{0,300,30}:NGOODJETS{0,6}:ST{0,1000,100}";
	//varexp += ":MINJETPT{0,400,40}:MAXJETPT{0,400,40}";
	
	// Global cuts, if desired
	TString selection = "NOTTRILEPTONONZ";
	//selection += " && NGOODELECTRONS == 3";
	
	
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
	
	mkdir("WZ", 0755);
	chdir("WZ");
	
	// WZ control plot
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 50, 100, false);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_MT.pdf");
	assembler->project("MT", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100_NGOODJETS.pdf");
	
	assembler->setRange("HT");
	assembler->setRange("NGOODJETS", 0, 0);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_NGOODJETS0_HT.pdf");
	assembler->setRange("NGOODJETS", 1, 1);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_NGOODJETS1_HT.pdf");
	assembler->setRange("NGOODJETS", 2, 2);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_NGOODJETS2_HT.pdf");
	assembler->setRange("NGOODJETS", 3, 3);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_NGOODJETS3_HT.pdf");
	assembler->setRange("NGOODJETS");
	assembler->setRange("HT", 0, 200, false);
	
	assembler->setRange("MET");
	assembler->setRange("MT", 50, 100, false);
	assembler->project("MET", true)->plot(false)->SaveAs("WZ_MT50to100_MET.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100_NGOODJETS.pdf");
	//assembler->project("NGOODJETS", true)->print();
	assembler->setRange();
	
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("MET", 50, 100, false);
	
/*	cout << "min" << endl;
	assembler->project("MINJETPT", true)->print();
	assembler->project("MINJETPT", true)->plot(false)->SaveAs("WZ_MET50to100_MINJETPT.pdf");
	cout << "max" << endl;
	assembler->project("MAXJETPT", true)->print();
	assembler->project("MAXJETPT", true)->plot(false)->SaveAs("WZ_MET50to100_MAXJETPT.pdf");
	
	assembler->setRange("HT", 0, 200, false);
	cout << "low HT min" << endl;
	assembler->project("MINJETPT", true)->print();
	assembler->project("MINJETPT", true)->plot(false)->SaveAs("WZ_HT0to200MET50to100_MINJETPT.pdf");
	cout << "low HT max" << endl;
	assembler->project("MAXJETPT", true)->print();
	assembler->project("MAXJETPT", true)->plot(false)->SaveAs("WZ_HT0to200MET50to100_MAXJETPT.pdf");
	
	assembler->setRange("HT", 200);
	cout << "high HT min" << endl;
	assembler->project("MINJETPT", true)->print();
	assembler->project("MINJETPT", true)->plot(false)->SaveAs("WZ_HTgt200MET50to100_MINJETPT.pdf");
	cout << "high HT max" << endl;
	assembler->project("MAXJETPT", true)->print();
	assembler->project("MAXJETPT", true)->plot(false)->SaveAs("WZ_HTgt200MET50to100_MAXJETPT.pdf");
*/	
	delete assembler;
}
