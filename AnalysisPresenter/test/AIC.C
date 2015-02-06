#include <sys/stat.h>
#include <unistd.h>

void AIC() {
	gSystem->Load("libRutgersIAFAnalysisPresenter.so");
	gROOT->ProcessLine(TString::Format(".include %s/src", getenv("CMSSW_BASE")));
	gROOT->ProcessLine(".L helperAnalysisPresenter.C+");
	
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For ZZ
	std::string varexp = "NLEPTONS{2,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:(NGOODELECTRONS%2){0,1}:NGOODELECTRONS{0,3}:NGOODMUONS{0,3}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:MLEPTONS{0,200,8}:MLEPTONS*1{0,200,48}:NGOODJETS{0,6}:NPROMPTINCLUSIVETRACKS{0,15}:MT{0,300,30}";
	varexp += ":Min$(PTGOODMUONS){0,100,20,\"MINMUONPT\"}:Min$(PTGOODELECTRONS){0,100,20,\"MINELECTRONPT\"}";
	varexp += ":Max$(PTGOODMUONS){0,100,20,\"MAXMUONPT\"}:Max$(PTGOODELECTRONS){0,100,20,\"MAXELECTRONPT\"}";
	
	// Global cuts, if desired
	//TString selection = "NOTTRILEPTONONZ";
	TString selection = "MOSSF < 81 && NGOODTAUS == 0";
	//TString selection = "NPROMPTINCLUSIVETRACKS >= 6";
	//TString selection = "!(MLEPTONS > 76 && MLEPTONS < 106)";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	setupData(assembler);
	//setupBackgroundMC(assembler);
	setupBackgroundMC(assembler, false, false);
	setupBackgroundDD(assembler, "noTaus");
	setupFakeRates(assembler);
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("AIC", 0755);
	chdir("AIC");
	
	// ZZ control plot
	// selection += "NLEPTONS == 3 && NOSSF == 1 && !ONZ && NGOODTAUS == 0 && NBJETSCSVM == 0 && HT < 200 && MET < 50"; // Richard's
	//	selection += " && NLEPTONS == NGOODMUONS";
	assembler->setRange("NLEPTONS", 3, 3);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NBJETSCSVM", 0, 0);
	assembler->setRange("HT", 0, 200, false);
	assembler->setRange("MET", 0, 50, false);
	
	assembler->project("MLEPTONS", true)->plot(false)->SaveAs("AIC_MLEPTONS.pdf");
	assembler->project("MT", true)->plot(false)->SaveAs("AIC_MLEPTONS_MT-OFFZ.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLEPTONS_fine.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS-ONZ.pdf");
	assembler->project("MT", true)->plot(false)->SaveAs("AIC_MLEPTONS_MT-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MLEPTONS", true)->plot(false)->SaveAs("AIC_MLEPTONS_3mu.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLEPTONS_3mu_fine.pdf");
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("AIC_MINMUONPT_3mu.pdf");
	assembler->project("MAXMUONPT", true)->plot(false)->SaveAs("AIC_MAXMUONPT_3mu.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3mu-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3mu-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODMUONS");
	
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MLEPTONS", true)->plot(false)->SaveAs("AIC_MLEPTONS_2el1mu.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLEPTONS_2el1mu_fine.pdf");
	assembler->project("MINMUONPT", true)->plot(false)->SaveAs("AIC_MINMUONPT_2el1mu.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_2el1mu-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_2el1mu-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODMUONS");
	
	assembler->setRange("NGOODELECTRONS", 3, 3);
	assembler->project("MLEPTONS", true)->plot(false)->SaveAs("AIC_MLEPTONS_3el.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLEPTONS_3el_fine.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("AIC_MINELECTRONPT_3el.pdf");
	assembler->project("MAXELECTRONPT", true)->plot(false)->SaveAs("AIC_MAXELECTRONPT_3el.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3el-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_3el-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODELECTRONS");
	
	assembler->setRange("NGOODELECTRONS", 1, 1);
	assembler->project("MLEPTONS", true)->plot(false)->SaveAs("AIC_MLEPTONS_1el2mu.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLEPTONS_1el2mu_fine.pdf");
	assembler->project("MINELECTRONPT", true)->plot(false)->SaveAs("AIC_MINELECTRONPT_1el2mu.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_1el2mu-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_1el2mu-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("NGOODELECTRONS");
	
	assembler->setRange("(NGOODELECTRONS%2)", 1, 1);
	assembler->project("MLEPTONS", true)->plot(false)->SaveAs("AIC_MLEPTONS_elFake.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLEPTONS_elFake_fine.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_elFake-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_elFake-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("(NGOODELECTRONS%2)");
	
	assembler->setRange("(NGOODELECTRONS%2)", 0, 0);
	assembler->project("MLEPTONS", true)->plot(false)->SaveAs("AIC_MLEPTONS_muFake.pdf");
	assembler->project("MLEPTONS*1", true)->plot(false)->SaveAs("AIC_MLEPTONS_muFake_fine.pdf");
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_muFake-OFFZ.pdf");
	assembler->setRange("ONZ", 1, 1);
	assembler->project("NPROMPTINCLUSIVETRACKS", true)->plot(false)->SaveAs("AIC_NPROMPTINCLUSIVETRACKS_muFake-ONZ.pdf");
	assembler->setRange("ONZ", 0, 0);
	assembler->setRange("(NGOODELECTRONS%2)");
	
	assembler->setRange();
	
	delete assembler;
}
