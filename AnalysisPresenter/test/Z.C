#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void Z() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For Z peak
	//std::string varexp = "NLIGHTLEPTONS{2,6}:NGOODELECTRONS{0,4}:NGOODMUONS{0,4}:NGOODELECTRONS%2{0,2,\"elFake\"}:NGOODMUONS%2{0,2,\"muFake\"}:MOSSF{11,131,36}:NOSSF{0,2}:ONZ{0,2}:NGOODTAUS{0,2}:NBJETSCSVM{0,2}:HT{-10,440,15}:MET{0,100,10}:MT{0,100,10}:MLIGHTLEPTONS{76,106}";
	std::string varexp = "NLIGHTLEPTONS{2,6}:NGOODELECTRONS{0,4}:NGOODMUONS{0,4}:NGOODELECTRONS%2{0,2,\"elFake\"}:NGOODMUONS%2{0,2,\"muFake\"}:MOSSF{11,131,36}:NOSSF{0,2}:ONZ{0,2}:NGOODTAUS{0,2}:NBJETSCSVM{0,2}:HT{0,510,17}:MET{0,100,10}:MT{0,100,10}:MLIGHTLEPTONS{66,106}";
	varexp += ":NPROMPTTRACKS7{0,100,1}";
	varexp += ":Min$(PTGOODMUONS){0,100,20,\"MINMUONPT\"}:Min$(PTGOODELECTRONS){0,100,20,\"MINELECTRONPT\"}";
	varexp += ":Max$(PTGOODMUONS){0,100,20,\"MAXMUONPT\"}:Max$(PTGOODELECTRONS){0,100,20,\"MAXELECTRONPT\"}";
	varexp += ":AIC{0,2}";
	varexp += ":MOSSF*1{11,131,120,\"MOSSFfine\"}";
//	varexp += ":PTGOODMUONS{-3,3,20}";
//	varexp += ":ETAGOODMUONS{-3,3,20}";
	
	// Global cuts, if desired
	//TString selection = "!AIC";
	TString selection = "PTGOODLEPTONS[0] > 25 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10";
//	selection += " && fakeRoleGOODMUONS > 0";
	//selection += " && !(MLIGHTLEPTONS > 76 && MLIGHTLEPTONS < 106)";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	
	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	//assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	assembler->setMode("noTrackSystematics");
	
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler);
	//setupBackgroundDD(assembler, "noTaus", true);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("Z", 0755);
	chdir("Z");
	
	TF1* f = new TF1("f", "pol0", 81, 101);
	TF1* f1 = new TF1("f", "pol1", 10, 100);
	
//	assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
//	assembler->setRange("NBJETSCSVM", 0, 0);
	
//	assembler->setRange("HT", -10, 200, false);
	assembler->setRange("MET", 0, 50, false);
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("Zloose_MINMUONPT.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("Zloose_MINELECTRONPT.pdf");
	assembler->project("MAXMUONPT", true)->plot(false)->SaveAs("Zloose_MAXMUONPT.pdf");
	assembler->project("MAXELECTRONPT", true)->plot(false)->SaveAs("Zloose_MAXELECTRONPT.pdf");
	assembler->setRange("ONZ");
	
	assembler->setRange("MET", 0, 50, false);
	//assembler->setRange("MT", 0, 50, false);
	
//	assembler->setRange("HT");
	assembler->project("HT", true)->plot(true)->SaveAs("Z_HT.pdf");
makeNicePlot(assembler->project("HT", true)->plot(true), "HT [GeV]")->SaveAs("../nicePlots/Z_L3MET0to50_HT.pdf");
	
	//assembler->setRange("MET", 0, 30, false);
//	assembler->setRange("HT", -10, 200, false);
	
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_MOSSF.pdf");

makeNicePlot(assembler->project("MOSSF", true)->plot(false), "OSSF pair mass [GeV]")->SaveAs("../nicePlots/Z_L3MET0to50_MOSSF.pdf");

	assembler->setRange("MLIGHTLEPTONS", 75, 100);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_MOSSF_3LonZ.pdf");
	assembler->setRange("MLIGHTLEPTONS");

	assembler->project("MOSSFfine", true)->plot(false, f, 81, 101)->SaveAs("Z_MOSSFfine.pdf");
	assembler->setRange("AIC", 0, 0);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_noAIC_MOSSF.pdf");
makeNicePlot(assembler->project("MOSSF", true)->plot(false), "OSSF pair mass [GeV]")->SaveAs("../nicePlots/Z_L3MET0to50_noAIC_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_noAIC_ONZ.pdf");
makeNicePlot(assembler->project("ONZ", true)->plot(false), "OSSF pair on Z?")->SaveAs("../nicePlots/Z_L3MET0to50_noAIC_ONZ.pdf");
	assembler->setRange("AIC", 1, 1);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_AIC_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_AIC_ONZ.pdf");
	assembler->setRange("AIC");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_ONZ.pdf");
makeNicePlot(assembler->project("ONZ", true)->plot(false), "OSSF pair on Z?")->SaveAs("../nicePlots/Z_L3MET0to50_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("Z_MINMUONPT.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("Z_MINELECTRONPT.pdf");
	assembler->project("MAXMUONPT", true)->plot(false)->SaveAs("Z_MAXMUONPT.pdf");
	assembler->project("MAXELECTRONPT", true)->plot(false)->SaveAs("Z_MAXELECTRONPT.pdf");
	assembler->setRange("ONZ");
	
	assembler->setRange("elFake", 1, 1);
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_elFake_MOSSF.pdf");
	assembler->project("MOSSFfine", true)->plot(false, f, 81, 101)->SaveAs("Z_elFake_MOSSFfine.pdf");
	assembler->setRange("AIC", 0, 0);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_elFake_noAIC_MOSSF.pdf");
	assembler->setRange("AIC");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_elFake_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("Z_elFake_MINELECTRONPT.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false, f1, 10, 60)->SaveAs("Z_elFake_MINELECTRONPT_fit.pdf");
	assembler->project("MAXELECTRONPT", true)->plot(false)->SaveAs("Z_elFake_MAXELECTRONPT.pdf");
//	assembler->project("ETAelFake", true)->plot(false)->SaveAs("Z_elFake_ETAelFake.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODELECTRONS", 1, 1);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_1el2mu_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_1el2mu_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("Z_1el2mu_MINELECTRONPT.pdf");
	assembler->project("MAXELECTRONPT", true)->plot(false)->SaveAs("Z_1el2mu_MAXELECTRONPT.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODELECTRONS", 3, 3);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_3el_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_3el_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("Z_3el_MINELECTRONPT.pdf");
	assembler->project("MAXELECTRONPT", true)->plot(false)->SaveAs("Z_3el_MAXELECTRONPT.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODELECTRONS");
	assembler->setRange("elFake");
	
	assembler->setRange("muFake", 1, 1);
	assembler->project("MOSSF", true)->print();
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_muFake_MOSSF.pdf");
	assembler->project("MOSSFfine", true)->plot(false, f, 81, 101)->SaveAs("Z_muFake_MOSSFfine.pdf");
	assembler->setRange("AIC", 0, 0);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_muFake_noAIC_MOSSF.pdf");
	assembler->setRange("AIC");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_muFake_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("Z_muFake_MINMUONPT.pdf");
	assembler->project("MINMUONPT", true)->plot(false, f1, 10, 25)->SaveAs("Z_muFake_MINMUONPT_fit.pdf");
	assembler->project("MAXMUONPT", true)->plot(false)->SaveAs("Z_muFake_MAXMUONPT.pdf");
//	assembler->project("PTGOODMUONS", true)->plot(false)->SaveAs("Z_muFake_fakeRoleGOODMUONS_PTGOODMUONS.pdf");
//	assembler->project("ETAGOODMUONS", true)->plot(false)->SaveAs("Z_muFake_fakeRoleGOODMUONS_ETAGOODMUONS.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_2el1mu_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_2el1mu_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("Z_2el1mu_MINMUONPT.pdf");
	assembler->project("MAXMUONPT", true)->plot(false)->SaveAs("Z_2el1mu_MAXMUONPT.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MOSSF", true)->plot(false, f, 81, 101)->SaveAs("Z_3mu_MOSSF.pdf");
	assembler->project("ONZ", true)->plot(false)->SaveAs("Z_3mu_ONZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("Z_3mu_MINMUONPT.pdf");
	assembler->project("MAXMUONPT", true)->plot(false)->SaveAs("Z_3mu_MAXMUONPT.pdf");
	assembler->setRange("ONZ");
	assembler->setRange("NGOODMUONS");
	assembler->setRange("muFake");
	
	assembler->setRange();
	
	delete assembler;
}
