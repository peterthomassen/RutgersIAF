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
	std::string varexp = "NBJETSCSVM{0,2}:HT{0,1000,20}:MET{0,500,10}:ST{0,2000,20}:NGOODJETS{0,6}:NPROMPTNONISOINCLUSIVETRACKS7{0,15}:NGOODTRACKS{0,15}";
	
	// Global cuts, if desired
	TString selection = "NLEPTONS == 2 && NGOODTAUS == 0 && NPOSGOODELECTRONS == NNEGGOODMUONS && NNEGGOODELECTRONS == NPOSGOODMUONS";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);
	setupData(assembler, false, true);
	setupBackgroundMC(assembler, true);
	//setupBackgroundDD(assembler);
	//setupFakeRates(assembler);
	assembler->setFakeRate("nTrackFakeElectrons", "0");
	assembler->setFakeRate("nTrackFakeMuons", "0");
	assembler->setFakeRate("nPhotonFakeElectrons", "0");
	assembler->setFakeRate("nPhotonFakeMuons", "0");
	assembler->setFakeRate("nTauFakeTaus", "0");
	assembler->setDebug(true);
	assembler->process(varexp, selection);
	
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("ttbar", 0755);
	chdir("ttbar");
	
	assembler->setRange("NBJETSCSVM", 1);
	assembler->setRange("ST", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbar_NGOODJETS.pdf");
	assembler->project("NGOODJETS", true)->print();
	assembler->project("HT", true)->plot(true)->SaveAs("ttbar_HT.pdf");
	assembler->project("MET", true)->plot(true)->SaveAs("ttbar_MET.pdf");
	assembler->project("ST", true)->plot(true)->SaveAs("ttbar_ST.pdf");
	assembler->project("NPROMPTNONISOINCLUSIVETRACKS7", true)->plot(true)->SaveAs("ttbar_NPROMPTNONISOINCLUSIVETRACKS7.pdf");
	assembler->project("NGOODTRACKS", true)->plot(true)->SaveAs("ttbar_NGOODTRACKS.pdf");
	assembler->project("NGOODTRACKS", true)->print();
	
	assembler->setRange("ST", 300);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("ttbar_NGOODJETS_STgt300.pdf");
	assembler->project("NGOODJETS", true)->print();
	assembler->project("HT", true)->plot(true)->SaveAs("ttbar_HT_STgt300.pdf");
	assembler->project("MET", true)->plot(true)->SaveAs("ttbar_MET_STgt300.pdf");
	assembler->project("ST", true)->plot(true)->SaveAs("ttbar_ST_STgt300.pdf");
	assembler->project("NPROMPTNONISOINCLUSIVETRACKS7", true)->plot(true)->SaveAs("ttbar_NPROMPTNONISOINCLUSIVETRACKS7_STgt300.pdf");
	assembler->project("NGOODTRACKS", true)->plot(true)->SaveAs("ttbar_NGOODTRACKS_STgt300.pdf");
	assembler->project("NGOODTRACKS", true)->print();
	
	assembler->setRange();
	
	delete assembler;
}
