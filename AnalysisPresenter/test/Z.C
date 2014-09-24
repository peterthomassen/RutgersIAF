#include <sys/stat.h>
#include <unistd.h>

void Z() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For Z peak
	std::string varexp = "NLEPTONS{2,6}:NGOODELECTRONS{0,3}:NGOODMUONS{0,3}:NGOODELECTRONS%2{0,1,\"elFake\"}:NGOODMUONS%2{0,1,\"muFake\"}:MOSSF{11,131,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,200,2}:MET{0,100,10}:MT{0,100,10}:MLEPTONS{76,106}";
	varexp += ":NPROMPTTRACKS7{0,100,1}";
	varexp += ":Min$(PTGOODMUONS){0,200,100,\"MINMUONPT\"}:Min$(PTGOODELECTRONS){0,200,100,\"MINELECTRONPT\"}";
	
	// Global cuts, if desired
	//TString selection = "NOTTRILEPTONONZ";
	TString selection = "1";
	//selection += " && !(MLEPTONS > 81 && MLEPTONS < 101)";
	// for Zpeak
	selection += " && NLEPTONS == 3";
	//selection += " && !(MLEPTONS > 76 && MLEPTONS < 106)";
	
	
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
	
	mkdir("Z", 0755);
	chdir("Z");
	
	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 0, 50, false);
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false, true)->SaveAs("Zloose_MINMUONPT.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false, true)->SaveAs("Zloose_MINELECTRONPT.pdf");
	assembler->setRange("ONZ");
	
	assembler->setRange("HT", 0, 100, false);
	assembler->setRange("MET", 0, 30, false);
	assembler->setRange("MT", 0, 50, false);
	
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, true, 81, 101)->SaveAs("Z_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false, true)->SaveAs("Z_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false, true)->SaveAs("Z_MINMUONPT.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false, true)->SaveAs("Z_MINELECTRONPT.pdf");
	assembler->setRange("ONZ");
	
	assembler->setRange("elFake", 1, 1);
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, true, 81, 101)->SaveAs("Z_elFake_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false, true)->SaveAs("Z_elFake_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINELECTRONPT", true)->plot(false, true)->SaveAs("Z_elFake_MINELECTRONPT.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODELECTRONS", 1, 1);
	assembler->project("MOSSF", true)->plot(false, true, 81, 101)->SaveAs("Z_1el2mu_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false, true)->SaveAs("Z_1el2mu_ONZ.pdf");
	assembler->setRange("NGOODELECTRONS", 3, 3);
	assembler->project("MOSSF", true)->plot(false, true, 81, 101)->SaveAs("Z_3el_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false, true)->SaveAs("Z_3el_ONZ.pdf");
	assembler->setRange("NGOODELECTRONS");
	assembler->setRange("elFake");
	
	assembler->setRange("muFake", 1, 1);
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, true, 81, 101)->SaveAs("Z_muFake_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false, true)->SaveAs("Z_muFake_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false, true)->SaveAs("Z_muFake_MINMUONPT.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MOSSF", true)->plot(false, true, 81, 101)->SaveAs("Z_2el1mu_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false, true)->SaveAs("Z_2el1mu_ONZ.pdf");
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MOSSF", true)->plot(false, true, 81, 101)->SaveAs("Z_3mu_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false, true)->SaveAs("Z_3mu_ONZ.pdf");
	assembler->setRange("NGOODMUONS");
	assembler->setRange("muFake");
	
	assembler->setRange();
	
	delete assembler;
}
