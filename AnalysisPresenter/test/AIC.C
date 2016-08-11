#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter_hybrid.C"

void AIC() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For ZZ
	std::string varexp = "NLIGHTLEPTONS{2,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,2}:(NGOODELECTRONS%2){0,2}:NGOODELECTRONS{0,4}:NGOODMUONS{0,4}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLIGHTLEPTONS{0,200,8}:MLIGHTLEPTONS*1{0,200,48}:NGOODJETS{0,6}:NPROMPTINCLUSIVETRACKS{0,15}:MT{0,300,30}";
	varexp += ":Min$(PTGOODMUONS){0,100,20,\"MINMUONPT\"}:Min$(PTGOODELECTRONS){0,100,20,\"MINELECTRONPT\"}";
	varexp += ":Max$(PTGOODMUONS){0,100,20,\"MAXMUONPT\"}:Max$(PTGOODELECTRONS){0,100,20,\"MAXELECTRONPT\"}";
	
	// Global cuts, if desired
	//TString selection = "!AIC";
	TString selection = "PTGOODLEPTONS[0] > 25 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10";
	selection += " && MOSSF < 81"; // && NGOODTAUS == 0";
	//TString selection = "NPROMPTINCLUSIVETRACKS >= 6";
	//TString selection = "!(MLIGHTLEPTONS > 76 && MLIGHTLEPTONS < 106)";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	
	//assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	assembler->setMode("noPhotonSystematics");
	
	setupData(assembler);
	setupBackgroundMC(assembler);
	//setupBackgroundMC(assembler, false, false);
	//setupBackgroundDD(assembler, "noTaus");
	setupBackgroundDD(assembler, "", true);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("AIC", 0755);
	chdir("AIC");
	
	// ZZ control plot
	// selection += "NLEPTONS == 3 && NOSSF == 1 && !ONZ && NGOODTAUS == 0 && NBJETSCSVM == 0 && HT < 200 && MET < 50"; // Richard's
	//	selection += " && NLEPTONS == NGOODMUONS";
	assembler->setRange("NLIGHTLEPTONS", 3, 3);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 0, 50, false);
	
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS.pdf");
makeNicePlot(assembler->project("MLIGHTLEPTONS", true)->plot(false), "trilepton mass [GeV]")->SaveAs("../nicePlots/AIC_MLIGHTLEPTONS.pdf");
	assembler->project("MT", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_MT-OFFZ.pdf");
	assembler->project("MLIGHTLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_fine.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS-ONZ.pdf");
	assembler->project("MT", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_MT-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_3mu.pdf");
	assembler->project("MLIGHTLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_3mu_fine.pdf");
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("AIC_MINMUONPT_3mu.pdf");
	assembler->project("MAXMUONPT", true)->plot(false)->SaveAs("AIC_MAXMUONPT_3mu.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3mu-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3mu-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODMUONS");
	
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_2el1mu.pdf");
	assembler->project("MLIGHTLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_2el1mu_fine.pdf");
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("AIC_MINMUONPT_2el1mu.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_2el1mu-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_2el1mu-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODMUONS");
	
	assembler->setRange("NGOODELECTRONS", 3, 3);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_3el.pdf");
	assembler->project("MLIGHTLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_3el_fine.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("AIC_MINELECTRONPT_3el.pdf");
	assembler->project("MAXELECTRONPT", true)->plot(false)->SaveAs("AIC_MAXELECTRONPT_3el.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3el-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3el-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODELECTRONS");
	
	assembler->setRange("NGOODELECTRONS", 1, 1);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_1el2mu.pdf");
	assembler->project("MLIGHTLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_1el2mu_fine.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("AIC_MINELECTRONPT_1el2mu.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_1el2mu-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_1el2mu-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODELECTRONS");
	
	assembler->setRange("(NGOODELECTRONS%2)", 1, 1);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_elFake.pdf");
	assembler->project("MLIGHTLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_elFake_fine.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_elFake-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_elFake-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("(NGOODELECTRONS%2)");
	
	assembler->setRange("(NGOODELECTRONS%2)", 0, 0);
	assembler->project("MLIGHTLEPTONS", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_muFake.pdf");
	assembler->project("MLIGHTLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLIGHTLEPTONS_muFake_fine.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_muFake-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_muFake-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("(NGOODELECTRONS%2)");
	
	assembler->setRange();
	
	delete assembler;
}
