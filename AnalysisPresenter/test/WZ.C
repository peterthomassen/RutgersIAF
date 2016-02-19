#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void WZ() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For WZ
	std::string varexp = "NLIGHTLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:MET{0,300,30}:(MET){0,200,4}:MT{0,150,15}:NGOODJETS{0,6}:ST{0,1000,100}";
	varexp += ":NGOODMUONS{0,4}:NGOODELECTRONS{0,4}";
	varexp += ":NGOODMUONS%2{0,2}";
	varexp += ":PTOSSF{0,300,30}";
	//varexp += ":MINJETPT{0,400,40}:MAXJETPT{0,400,40}";
	
	// Global cuts, if desired
	TString selection = "PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10"; // "!(AIC && MET < 50 && HT < 200)";
	//selection += " && NGOODELECTRONS == 3";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	
	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	//assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	assembler->setMode("noWZsystematics");
	
	setupData(assembler);
	setupBackgroundMC(assembler);
	setupBackgroundDD(assembler);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("WZ", 0755);
	chdir("WZ");
	
	// Check for duplicate events
	
//	assembler->project("NLIGHTLEPTONS", true)->getMeta(); // printMeta();
	//assembler->project("NLIGHTLEPTONS", true)->print();
	
	// WZ control plot
	assembler->setRange("NLIGHTLEPTONS", 3, 3);
	//assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1);
	
makeNicePlot(assembler->project("(MET)", true)->plot(true), "MET [GeV]")->SaveAs("../nicePlots/L3DYz1Tau0_MET.pdf");

	//assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("MET", 50, 100, false);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_MT.pdf");
makeNicePlot(assembler->project("MT", true)->plot(false), "MT [GeV]")->SaveAs("../nicePlots/WZ_MET50to100_MT.pdf");
makeNicePlot(assembler->project("PTOSSF", true)->plot(false), "pT(Z) [GeV]")->SaveAs("../nicePlots/WZ_MET50to100_PTOSSF.pdf");
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100_HT.pdf");
	assembler->project("HT", true)->plot(true)->SaveAs("WZ_MET50to100_HT_log.pdf");
	assembler->setRange("NGOODMUONS%2", 0, 0);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_evenMuon_MT.pdf");
	assembler->setRange("NGOODMUONS%2", 1, 1);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_oddMuon_MT.pdf");
	assembler->setRange("NGOODMUONS%2");
	
	assembler->setRange("NGOODMUONS", 0, 0);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu0_MT.pdf");
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu1_MT.pdf");
	assembler->setRange("NGOODMUONS", 2, 2);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu2_MT.pdf");
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100_Mu3_MT.pdf");
	assembler->setRange("NGOODMUONS");
	
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100_HT.pdf");
	assembler->project("HT", true)->plot(true)->SaveAs("WZ_MET50to100_HT_log.pdf");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100_NGOODJETS.pdf");
makeNicePlot(assembler->project("NGOODJETS", true)->plot(false), "nJets")->SaveAs("../nicePlots/WZ_MET50to100_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("NGOODJETS", 0, 0);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS0_HT.pdf");
	assembler->setRange("NGOODJETS", 1, 1);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS1_HT.pdf");
	assembler->setRange("NGOODJETS", 2, 2);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS2_HT.pdf");
	assembler->setRange("NGOODJETS", 3, 3);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET50to100NGOODJETS3_HT.pdf");
	assembler->setRange("NGOODJETS");
	
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_MET50to100HT0to200_MT.pdf");
	assembler->project("MT", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HT0to200_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("HT", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MET50to100HTgt200_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("MET");

	assembler->setRange("MT", 50, 100, false);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_MET.pdf");
makeNicePlot(assembler->project("MET", true)->plot(false), "MET [GeV]")->SaveAs("../nicePlots/WZ_MT50to100HT0to200_MET.pdf");
	assembler->project("MET", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_NGOODJETS.pdf");
	assembler->setRange("HT", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HTgt200_NGOODJETS.pdf");
	
	assembler->setRange("MT");
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MET", true)->plot(false)->SaveAs("WZ_HT0to200_MET.pdf");
	
	assembler->setRange("HT");
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_HT.pdf");
	assembler->project("HT", true)->plot(true)->SaveAs("WZ_HT_log.pdf");
	assembler->setRange("MET", 0, 50, false);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_MET0to50_HT.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
