#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

//#include "helperAnalysisPresenter.C"
#include "helperAnalysisPresenter_MConly.C"

void MConly() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
        //std::string varexp = "MOSSF{0,300,60}";
        std::string varexp = "NLEPTONS{0,10,10}";
	//varexp += ":ONZ{0,1}";
	//varexp += ":NBJETSCSVM{0,2}"; 
	varexp += ":HT{0,1000,10}";
	varexp += ":HTLA{0,1000,10}";
	varexp += ":LT{0,1000,10}";
	varexp += ":MET{0,300,30}";
	//varexp += ":MT{0,150,15}";
	varexp += ":NGOODJETS{0,10}";
	//varexp += ":PTGOODLEPTONS{0,200,20}";
	//varexp += ":PTGOODMUONS{0,200,20}";
	//varexp += ":(Alt$(PTGOODMUONS,0)){0,200,20}";
	varexp += ":(Alt$(PTGOODMUONS[0],0)){0,200,40}";
	varexp += ":(Alt$(PTGOODMUONS[1],0)){0,200,40}";
	varexp += ":(Alt$(ISTIGHTMATRIXMUON[0],0)){-1,2}";
	varexp += ":(Alt$(ISTIGHTMATRIXMUON[1],0)){-1,2}";
	varexp += ":(Alt$(PTTIGHTMATRIXMUONS[0],0)){0,200,40}";
	varexp += ":(Alt$(PTTIGHTMATRIXMUONS[1],0)){0,200,40}";
	//
	varexp += ":(Alt$(ISPROMPTMUON[0],0)){-1,2}";
	varexp += ":(Alt$(ISPROMPTMUON[1],0)){-1,2}";
	//
	//varexp += ":ST{0,1000,10}";
	varexp += ":NGOODMUONS{0,10}:NGOODELECTRONS{0,10}:NGOODTAUS{0,10}:NLIGHTLEPTONS{0,10}";
	//varexp += ":NTIGHTMATRIXMUONS{0,10}";
	
	// Global cuts, if desired
	TString selection = "1";
	//selection += "&& PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[20] > 20";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);

	cout<<"MConly debug 1"<<endl;
	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	assembler->setMode("noRatioPlot");
	//assembler->setMode("noWZsystematics");
	
	cout<<"MConly debug 2"<<endl;
	//setupData(assembler);
	setupBackgroundMC(assembler);
	//setupBackgroundDD(assembler);
	//setupFakeRates(assembler);
	//assembler->setDebug(true);
	cout<<"MConly debug 2B"<<endl;
	prepare(assembler);
	cout<<"MConly debug 2C"<<endl;
	assembler->process(varexp, selection, false);
	//assembler->process(varexp, selection, true);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	cout<<"MConly debug 3"<<endl;
	mkdir("MConly", 0755);
	chdir("MConly");
	
	// Check for duplicate events
	

	// WZ control plot
	//assembler->setRange("NLIGHTLEPTONS", 1, 9);
	//assembler->setRange("NGOODTAUS", 0, 0);
	//assembler->setRange("NOSSF", 1, 1);
	//assembler->setRange("ONZ", 1);
	
	//makeNicePlot(assembler->project("(MET)", true)->plot(true), "MET [GeV]")->SaveAs("../nicePlots/L3DYz1Tau0_MET.pdf");

	cout<<"MConly debug 4"<<endl;
	assembler->setRange();


	//all
	/**/
	assembler->project("HT", true )->plot(true)->SaveAs("All_HT.pdf");
	assembler->project("HTLA", true )->plot(true)->SaveAs("All_HTLA.pdf");
	assembler->project("LT", true )->plot(true)->SaveAs("All_LT.pdf");
	assembler->project("MET", true )->plot(true)->SaveAs("All_MET.pdf");
	assembler->project("NLEPTONS", true )->plot(false)->SaveAs("All_NLEPTONS.pdf");
	assembler->project("NGOODMUONS", true )->plot(false)->SaveAs("All_NGOODMUONS.pdf");
	assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("All_NGOODELECTRONS.pdf");
	assembler->project("NGOODTAUS", true )->plot(false)->SaveAs("All_NGOODTAUS.pdf");
	assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS1.pdf");
	assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS2.pdf");
	/**/


	//2Mu
	
	assembler->setRange("NGOODMUONS", 2, 2);
	// -------------------------------------------
	assembler->project("NGOODMUONS", true )->plot(false)->SaveAs("Sel2Mu_NGOODMUONS.pdf");
        assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("Sel2Mu_NGOODELECTRONS.pdf");
        assembler->project("NGOODTAUS", true )->plot(false)->SaveAs("Sel2Mu_NGOODTAUS.pdf");
	//assembler->project("NTIGHTMATRIXMUONS", true )->plot(false)->SaveAs("Sel2Mu_NTIGHTMATRIXMUONS.pdf");
	//assembler->project("PTGOODLEPTONS", true)->plot(false)->SaveAs("Sel2Mu_PTGOODLEPTONS.pdf");
	assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("Sel2Mu_PTGOODMUONS0.pdf");
	assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("Sel2Mu_PTGOODMUONS1.pdf");
	//assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))", true)->plot(true)->SaveAs("Sel2Mu_PTTIGHTMATRIXMUONS0.pdf");
	//assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))", true)->plot(true)->SaveAs("Sel2Mu_PTTIGHTMATRIXMUONS1.pdf");
	//assembler->project("PTGOODMUONS[0]*ISTIGHTMATRIXMUON[0]", true)->plot(true)->SaveAs("Sel2Mu_PTGOODTIGHTMUONS0.pdf");	
	//assembler->project("PTGOODMUONS[1]*2", true)->plot(true)->SaveAs("Sel2Mu_PTGOODTIGHTMUONS1.pdf");
	//assembler->project("HT", true)->plot(true)->SaveAs("HT_log.pdf");
	
	assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
	assembler->setRange("(Alt$(ISPROMPTMUON[0],0))", 1, 1);
	assembler->setRange("(Alt$(ISPROMPTMUON[1],0))", 1, 1);
	// -------------------------------------------
        assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTGOODMUONS0.pdf");
        assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTGOODMUONS1.pdf");
	assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTTIGHTMATRIXMUONS0.pdf");
	assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTTIGHTMATRIXMUONS1.pdf");

	SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true),"LooseMuons.root");
	SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))", true)->plot(true),"TightMuons.root");


	cout<<"MConly debug 5"<<endl;
	assembler->setRange();
	
	delete assembler;
}
