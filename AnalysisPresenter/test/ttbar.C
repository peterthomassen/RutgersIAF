#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter.C"

void ttbar() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// for ttbar 2L
	std::string varexp = "NLIGHTLEPTONS{2,5}:HT{0,1500,30}:MET{0,500,10}:ST{0,2000,20}:NGOODJETS{0,10}:NPROMPTNONISOINCLUSIVETRACKS7{0,25}:NGOODTRACKS{0,15}:NGOODINCLUSIVETRACKS{0,15}";
	varexp += ":NBJETSCSVL{0,4}";
	varexp += ":NBJETSCSVM{0,4}";
	
	// Global cuts, if desired
	TString selection = "(NLIGHTLEPTONS == 3 && NOSSF == 0) || (NLIGHTLEPTONS == 2 && NGOODELECTRONS == 1 && NGOODMUONS == 1 && NGOODTAUS == 0 && Sum$(QGOODELECTRONS) + Sum$(QGOODMUONS) == 0)";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	
	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	//assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	assembler->setMode("noTTsystematics");
	
	setupData(assembler, true);
	setupBackgroundMC(assembler, true, true, true);
	setupBackgroundDD(assembler);
	setupFakeRates(assembler);
	assembler->setFakeRate("nTrackFakeElectrons", "0");
	assembler->setFakeRate("nTrackFakeMuons", "0");
	assembler->setFakeRate("nPhotonFakeElectrons", "0");
	assembler->setFakeRate("nPhotonFakeMuons", "0");
//	assembler->setFakeRate("nTauFakeTaus", "0");
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("ttbar", 0755);
	chdir("ttbar");
	
	assembler->setRange("NLIGHTLEPTONS", 2, 2);
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("ST", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbar_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	assembler->project("HT", true)->plot(true)->SaveAs("ttbar_HT.pdf");
	assembler->project("MET", true)->plot(true)->SaveAs("ttbar_MET.pdf");
	assembler->project("ST", true)->plot(true)->SaveAs("ttbar_ST.pdf");
makeNicePlot(assembler->project("ST", true)->plot(false), "ST [GeV]")->SaveAs("../nicePlots/ttbar_ST.pdf");
	assembler->project("NPROMPTNONISOINCLUSIVETRACKS7", true)->plot(true)->SaveAs("ttbar_NPROMPTNONISOINCLUSIVETRACKS7.pdf");
	assembler->project("NGOODINCLUSIVETRACKS", true)->plot(true)->SaveAs("ttbar_NGOODINCLUSIVETRACKS.pdf");
	assembler->project("NGOODTRACKS", true)->plot(true)->SaveAs("ttbar_NGOODTRACKS.pdf");
	assembler->project("NGOODTRACKS", true)->print();
	
	assembler->setRange("ST", 300);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbar_NGOODJETS_STgt300.pdf");
makeNicePlot(assembler->project("NGOODJETS", true)->plot(false), "nJets")->SaveAs("../nicePlots/ttbar_NGOODJETS_STgt300.pdf");
	assembler->project("NGOODJETS", true)->print();
	assembler->project("ST", true)->plot(true)->SaveAs("ttbar_ST_STgt300.pdf");
makeNicePlot(assembler->project("ST", true)->plot(true), "ST [GeV]")->SaveAs("../nicePlots/ttbar_ST_STgt300.pdf");
	assembler->project("HT", true)->plot(true)->SaveAs("ttbar_HT_STgt300.pdf");
makeNicePlot(assembler->project("HT", true)->plot(true), "HT [GeV]")->SaveAs("../nicePlots/ttbar_HT_STgt300.pdf");
	assembler->project("MET", true)->plot(true)->SaveAs("ttbar_MET_STgt300.pdf");
makeNicePlot(assembler->project("MET", true)->plot(true), "MET [GeV]")->SaveAs("../nicePlots/ttbar_MET_STgt300.pdf");
	assembler->project("ST", true)->plot(true)->SaveAs("ttbar_ST_STgt300.pdf");
	assembler->project("NPROMPTNONISOINCLUSIVETRACKS7", true)->plot(true)->SaveAs("ttbar_NPROMPTNONISOINCLUSIVETRACKS7_STgt300.pdf");
makeNicePlot(assembler->project("NPROMPTNONISOINCLUSIVETRACKS7", true)->plot(false), "nPromptNonIsoTracks")->SaveAs("../nicePlots/ttbar_NPROMPTNONISOINCLUSIVETRACKS7_STgt300.pdf");
	assembler->project("NGOODINCLUSIVETRACKS", true)->plot(true)->SaveAs("ttbar_NGOODINCLUSIVETRACKS_STgt300.pdf");
	assembler->project("NGOODTRACKS", true)->plot(true)->SaveAs("ttbar_NGOODTRACKS_STgt300.pdf");
	assembler->project("NGOODTRACKS", true)->print();
	
	assembler->setRange();
	
	
	assembler->setRange("NLIGHTLEPTONS", 3, 3);
	assembler->setRange("ST", 300);
	
	assembler->project("NBJETSCSVL", true)->plot(false)->SaveAs("ttbar_L3STgt300_NBJETSCSVL.pdf");
	assembler->project("NBJETSCSVM", true)->plot(false)->SaveAs("ttbar_L3STgt300_NBJETSCSVM.pdf");
	
	assembler->setRange("ST");
	assembler->setRange("NBJETSCSVM", 1);
	assembler->project("ST", true)->plot(false)->SaveAs("ttbar_L3NBJETSCSVMgt0_ST.pdf");
	
	assembler->setRange();
	
	delete assembler;
}
