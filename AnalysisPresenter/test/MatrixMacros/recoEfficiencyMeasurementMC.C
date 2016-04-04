#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter_MConly.C"

void recoEfficiencyMeasurementMC() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
        //std::string varexp = "NLEPTONS{0,10,10}";
        std::string varexp = "NMCMUONSFROMBOSON[0]{0,10,10}";
	varexp += ":NMCELECTRONSFROMBOSON[0]{0,10,10}";
	varexp += ":NMCTAUSFROMBOSON[0]{0,10,10}";
	varexp += ":NGOODMUONS[0]{0,10,10}";
	//varexp += ":HT{0,1000,10}";
	//varexp += ":HTLA{0,1000,10}";
	//varexp += ":LT{0,1000,10}";
	//varexp += ":MET{0,300,30}";
	//varexp += ":MT{0,150,15}";
	//varexp += ":NGOODJETS{0,10}";
	//varexp += ":(Alt$(PTGOODMUONS[0],0)){0,200,40}";
	varexp += ":(Alt$(PTMCMUONSFROMBOSON[0],0)){0,200,40}";
	varexp += ":(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0)){0,200,40}";
	//varexp += ":(Alt$(ETAMCMUONSFROMBOSON[0],-10)){-6,6,40}";
	varexp += ":ETAMCMUONSFROMBOSON[0]{-6,6,40}";
	varexp += ":abs(ETAMCMUONSFROMBOSON[0]){-6,6,40}";
	//varexp += ":abs(Alt$(ETAMCMUONSFROMBOSON[0],10)){0,10,100}";
	//varexp += ":abs(ETAMCMUONSFROMBOSON[0]){0,10,100}";
	varexp += ":(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10)){-6,6,40}";
	//varexp += ":ETAMCMUONSFROMBOSONMATCHED[0]{-3,3,20}";
	//varexp += ":(Alt$(PTGOODTAUS[1],0)){0,200,40}";
	//varexp += ":(Alt$(ISTIGHTMATRIXTAU[0],0)){-1,2}";
	//varexp += ":(Alt$(ISTIGHTMATRIXTAU[1],0)){-1,2}";
	//varexp += ":(Alt$(PTTIGHTMATRIXTAUS[0],0)){0,200,40}";
	//varexp += ":(Alt$(PTTIGHTMATRIXTAUS[1],0)){0,200,40}";
	//
	//varexp += ":(Alt$(ISPROMPTTAU[0],0)){-1,2}";
	//varexp += ":(Alt$(ISFAKETAUFROMELE[0],0)){-1,2}";
	//varexp += ":(Alt$(ISFAKETAUFROMMU[0],0)){-1,2}";
	//varexp += ":(Alt$(ISPROMPTTAU[1],0)){-1,2}";
	//
	//varexp += ":NGOODMUONS{0,10}:NGOODELECTRONS{0,10}:NGOODTAUS{0,10}:NLIGHTLEPTONS{0,10}";
	
	// Global cuts, if desired
	TString selection = "1";
	//selection += "&& PTGOODLEPTONS[0] > 20 && PTGOODLEPTONS[20] > 20";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler);

	assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	assembler->setMode("noRatioPlot");
	//assembler->setMode("noWZsystematics");
	
	//setupData(assembler);
	setupBackgroundMC(assembler);
	//setupBackgroundDD(assembler);
	//setupFakeRates(assembler);
	//assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection, false);
	//assembler->process(varexp, selection, true);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	mkdir("RecoEfficiencyMuon", 0755);
	chdir("RecoEfficiencyMuon");
	
	// Check for duplicate events
	

	// WZ control plot
	//assembler->setRange("NLIGHTLEPTONS", 1, 9);
	//assembler->setRange("NGOODTAUS", 0, 0);
	//assembler->setRange("NOSSF", 1, 1);
	//assembler->setRange("ONZ", 1);
	
	//makeNicePlot(assembler->project("(MET)", true)->plot(true), "MET [GeV]")->SaveAs("../nicePlots/L3DYz1Tau0_MET.pdf");

	assembler->setRange();
        assembler->project("NMCELECTRONSFROMBOSON[0]", true )->plot(true)->SaveAs("All_NMCELECTRONSFROMBOSON.pdf");
        assembler->project("NMCMUONSFROMBOSON[0]",     true )->plot(true)->SaveAs("All_NMCMUONSFROMBOSON.pdf");
        assembler->project("NMCTAUSFROMBOSON[0]",      true )->plot(true)->SaveAs("All_NMCTAUSFROMBOSON.pdf");

        assembler->setRange();
	assembler->setRange("NMCELECTRONSFROMBOSON[0]",0,0);
	assembler->setRange("NMCMUONSFROMBOSON[0]",1,1);
	assembler->setRange("NMCTAUSFROMBOSON[0]",0,0);
	//-----------------------------------------------------------------------------
        assembler->project("NMCELECTRONSFROMBOSON[0]", true )->plot(true)->SaveAs("Sel1genMu_NMCELECTRONSFROMBOSON.pdf");
        assembler->project("NMCMUONSFROMBOSON[0]",     true )->plot(true)->SaveAs("Sel1genMu_NMCMUONSFROMBOSON.pdf");
        assembler->project("NMCTAUSFROMBOSON[0]",      true )->plot(true)->SaveAs("Sel1genMu_NMCTAUSFROMBOSON.pdf");
        assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true )->plot(true)->SaveAs("Sel1genMu_PTMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true )->plot(true)->SaveAs("Sel1genMu_PTMCMUONSFROMBOSONMATCHED0.pdf");
        assembler->project("ETAMCMUONSFROMBOSON[0]",                    true )->plot(true)->SaveAs("Sel1genMu_ETAMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true )->plot(true)->SaveAs("Sel1genMu_ETAMCMUONSFROMBOSONMATCHED0.pdf");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true)->plot(true),"GenMuonsPT.root");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true)->plot(true),"GenMuonsMatchedPT.root");
        SaveHistograms(assembler->project("ETAMCMUONSFROMBOSON[0]",                    true)->plot(true),"GenMuonsETA.root");
        SaveHistograms(assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true)->plot(true),"GenMuonsMatchedETA.root");

        assembler->setRange();
        assembler->setRange("NMCELECTRONSFROMBOSON[0]",0,0);
        assembler->setRange("NMCMUONSFROMBOSON[0]",1,1);
        assembler->setRange("NMCTAUSFROMBOSON[0]",0,0);
        assembler->setRange("ETAMCMUONSFROMBOSON[0]",-2.4,2.3999999);
	//-----------------------------------------------------------------------------
        assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true )->plot(true)->SaveAs("Sel1genMuEta2p4_PTMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true )->plot(true)->SaveAs("Sel1genMuEta2p4_PTMCMUONSFROMBOSONMATCHED0.pdf");
        assembler->project("ETAMCMUONSFROMBOSON[0]",                    true )->plot(true)->SaveAs("Sel1genMuEta2p4_ETAMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true )->plot(true)->SaveAs("Sel1genMuEta2p4_ETAMCMUONSFROMBOSONMATCHED0.pdf");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true)->plot(true),"GenMuonsEta2p4PT.root");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true)->plot(true),"GenMuonsEta2p4MatchedPT.root");
        SaveHistograms(assembler->project("ETAMCMUONSFROMBOSON[0]",                    true)->plot(true),"GenMuonsEta2p4ETA.root");
        SaveHistograms(assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true)->plot(true),"GenMuonsEta2p4MatchedETA.root");

	assembler->setRange();
        assembler->setRange("NMCELECTRONSFROMBOSON[0]",0,0);
        assembler->setRange("NMCMUONSFROMBOSON[0]",1,1);
        assembler->setRange("NMCTAUSFROMBOSON[0]",0,0);
        assembler->setRange("ETAMCMUONSFROMBOSON[0]",-1.2,1.1999999);
	//-----------------------------------------------------------------------------
        assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true )->plot(true)->SaveAs("Sel1genMuEtaBar_PTMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true )->plot(true)->SaveAs("Sel1genMuEtaBar_PTMCMUONSFROMBOSONMATCHED0.pdf");
        assembler->project("ETAMCMUONSFROMBOSON[0]",                    true )->plot(true)->SaveAs("Sel1genMuEtaBar_ETAMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true )->plot(true)->SaveAs("Sel1genMuEtaBar_ETAMCMUONSFROMBOSONMATCHED0.pdf");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true)->plot(true),"GenMuonsBarrelPT.root");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true)->plot(true),"GenMuonsBarrelMatchedPT.root");
        SaveHistograms(assembler->project("ETAMCMUONSFROMBOSON[0]",                    true)->plot(true),"GenMuonsBarrelETA.root");
        SaveHistograms(assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true)->plot(true),"GenMuonsBarrelMatchedETA.root");
	
        assembler->setRange();
        assembler->setRange("NMCELECTRONSFROMBOSON[0]",0,0);
        assembler->setRange("NMCMUONSFROMBOSON[0]",1,1);
        assembler->setRange("NMCTAUSFROMBOSON[0]",0,0);
	assembler->setRange("abs(ETAMCMUONSFROMBOSON[0])",1.2,2.3999999);
        //-----------------------------------------------------------------------------
        assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true )->plot(true)->SaveAs("Sel1genMuEtaEnd_PTMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true )->plot(true)->SaveAs("Sel1genMuEtaEnd_PTMCMUONSFROMBOSONMATCHED0.pdf");
        assembler->project("ETAMCMUONSFROMBOSON[0]",                    true )->plot(true)->SaveAs("Sel1genMuEtaEnd_ETAMCMUONSFROMBOSON0.pdf");
        assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true )->plot(true)->SaveAs("Sel1genMuEtaEnd_ETAMCMUONSFROMBOSONMATCHED0.pdf");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSON[0],0))",           true)->plot(true),"GenMuonsEndcapPT.root");
        SaveHistograms(assembler->project("(Alt$(PTMCMUONSFROMBOSONMATCHED[0],0))",    true)->plot(true),"GenMuonsEndcapMatchedPT.root");
        SaveHistograms(assembler->project("ETAMCMUONSFROMBOSON[0]",                    true)->plot(true),"GenMuonsEndcapETA.root");
        SaveHistograms(assembler->project("(Alt$(ETAMCMUONSFROMBOSONMATCHED[0],-10))", true)->plot(true),"GenMuonsEndcapMatchedETA.root");


	//all
	/*
	assembler->project("HT", true )->plot(true)->SaveAs("All_HT.pdf");
	assembler->project("HTLA", true )->plot(true)->SaveAs("All_HTLA.pdf");
	assembler->project("LT", true )->plot(true)->SaveAs("All_LT.pdf");
	assembler->project("MET", true )->plot(true)->SaveAs("All_MET.pdf");
	assembler->project("NLEPTONS", true )->plot(false)->SaveAs("All_NLEPTONS.pdf");
	assembler->project("NGOODMUONS", true )->plot(false)->SaveAs("All_NGOODMUONS.pdf");
	assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("All_NGOODELECTRONS.pdf");
	assembler->project("NGOODTAUS", true )->plot(false)->SaveAs("All_NGOODTAUS.pdf");
	//assembler->project("(Alt$(ISPROMPTTAU[0],0))", true )->plot(false)->SaveAs("All_ISPROMPTTAU0.pdf");
	//assembler->project("(Alt$(ISFAKETAUFROMELE[0],0))", true )->plot(false)->SaveAs("All_ISFAKETAUFROMELE0.pdf");
	//assembler->project("(Alt$(ISFAKETAUFROMMU[0],0))", true )->plot(false)->SaveAs("All_ISFAKETAUFROMMU0.pdf");
	assembler->project("(Alt$(PTGOODTAUS[0],0))", true)->plot(true)->SaveAs("All_PTGOODTAUS1.pdf");
	//assembler->project("(Alt$(PTGOODTAUS[1],0))", true)->plot(true)->SaveAs("All_PTGOODTAUS2.pdf");
	*/


	//1 lep
	/*
	assembler->setRange("NGOODTAUS", 1, 1);
	// -------------------------------------------
	assembler->project("NGOODMUONS", true )->plot(false)->SaveAs("Sel1Tau_NGOODMUONS.pdf");
        assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("Sel1Tau_NGOODELECTRONS.pdf");
        assembler->project("NGOODTAUS", true )->plot(false)->SaveAs("Sel1Tau_NGOODTAUS.pdf");
        assembler->project("(Alt$(ISPROMPTTAU[0],0))", true )->plot(true)->SaveAs("Sel1Tau_ISPROMPTTAU0.pdf");
        assembler->project("(Alt$(ISFAKETAUFROMELE[0],0))", true )->plot(true)->SaveAs("Sel1Tau_ISFAKETAUFROMELE0.pdf");
        assembler->project("(Alt$(ISFAKETAUFROMMU[0],0))", true )->plot(true)->SaveAs("Sel1Tau_ISFAKETAUFROMMU0.pdf");
	assembler->project("(Alt$(PTGOODTAUS[0],0))", true)->plot(true)->SaveAs("Sel1Tau_PTGOODTAUS0.pdf");
	assembler->setRange("(Alt$(ISPROMPTTAU[0],0))", 0, 0);
	assembler->setRange("(Alt$(ISFAKETAUFROMELE[0],0))", 0, 0);
	assembler->setRange("(Alt$(ISFAKETAUFROMMU[0],0))", 0, 0);
	// -------------------------------------------
        assembler->project("(Alt$(ISPROMPTTAU[0],0))", true )->plot(true)->SaveAs("Sel1TauLeadTauJetFake_ISPROMPTTAU0.pdf");
        assembler->project("(Alt$(ISFAKETAUFROMELE[0],0))", true )->plot(true)->SaveAs("Sel1TauLeadTauJetFake_ISFAKETAUFROMELE0.pdf");
        assembler->project("(Alt$(ISFAKETAUFROMMU[0],0))", true )->plot(true)->SaveAs("Sel1TauLeadTauJetFake_ISFAKETAUFROMMU0.pdf");
        assembler->project("(Alt$(PTGOODTAUS[0],0))", true)->plot(true)->SaveAs("Sel1TauLeadTauJetFake_PTGOODTAUS0.pdf");
	assembler->project("(Alt$(PTTIGHTMATRIXTAUS[0],0))", true)->plot(true)->SaveAs("Sel1TauLeadTauJetFake_PTTIGHTMATRIXTAUS0.pdf");
	//
	SaveHistograms(assembler->project("(Alt$(PTGOODTAUS[0],0))", true)->plot(true),"LooseTaus.root");
	SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXTAUS[0],0))", true)->plot(true),"TightTaus.root");
	*/

	//2 lep	
	/*
	assembler->setRange("NGOODELECTRONS", 2, 2);
	// -------------------------------------------
	assembler->project("NGOODMUONS", true )->plot(false)->SaveAs("Sel2Mu_NGOODMUONS.pdf");
        assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("Sel2Mu_NGOODELECTRONS.pdf");
        assembler->project("NGOODTAUS", true )->plot(false)->SaveAs("Sel2Mu_NGOODTAUS.pdf");
	//assembler->project("NTIGHTMATRIXELECTRONS", true )->plot(false)->SaveAs("Sel2Mu_NTIGHTMATRIXELECTRONS.pdf");
	//assembler->project("PTGOODLEPTONS", true)->plot(false)->SaveAs("Sel2Mu_PTGOODLEPTONS.pdf");
	assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2Mu_PTGOODELECTRONS0.pdf");
	assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2Mu_PTGOODELECTRONS1.pdf");
	//assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2Mu_PTTIGHTMATRIXELECTRONS0.pdf");
	//assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2Mu_PTTIGHTMATRIXELECTRONS1.pdf");
	//assembler->project("PTGOODELECTRONS[0]*ISTIGHTMATRIXELECTRON[0]", true)->plot(true)->SaveAs("Sel2Mu_PTGOODTIGHTELECTRONS0.pdf");	
	//assembler->project("PTGOODELECTRONS[1]*2", true)->plot(true)->SaveAs("Sel2Mu_PTGOODTIGHTELECTRONS1.pdf");
	//assembler->project("HT", true)->plot(true)->SaveAs("HT_log.pdf");
	assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
	assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))", 1, 1);
	assembler->setRange("(Alt$(ISPROMPTELECTRON[1],0))", 1, 1);
	// -------------------------------------------
        assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTGOODELECTRONS0.pdf");
        assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTGOODELECTRONS1.pdf");
	assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTTIGHTMATRIXELECTRONS0.pdf");
	assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2MuLeadMuTight_PTTIGHTMATRIXELECTRONS1.pdf");
	//
	SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true),"LooseElectrons.root");
	SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))", true)->plot(true),"TightElectrons.root");
	*/

	assembler->setRange();
	
	delete assembler;
}
