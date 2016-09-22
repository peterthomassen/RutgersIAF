#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenter_hybrid_13TeV.C"

void ControlWZ16() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	// For WZ
  std::string varexp = "NLIGHTLEPTONS{3,6}:MOSSF{6,126,36}:NOSSF{0,2}:ONZ{0,1}:NGOODTAUS{0,1}:NBJETSCSVM{0,2}:HT{0,500,50}:METraw{0,300,30}:MT{0,150,15}:NGOODJETS{0,6}:ST{0,1000,100}";
	varexp += ":NGOODMUONS{0,4}:NGOODELECTRONS{0,4}";
	varexp += ":NGOODMUONS%2{0,2}";
	varexp += ":PTOSSF{0,300,30}";
	varexp+=":MT1(PTGOODELECTRONS[0],ETAGOODELECTRONS[0],PHIGOODELECTRONS[0],METPXraw[0],METPYraw[0]){0,150,15,\"MT1\"}";
	//if(NGOODMUONS%2==0)
	//varexp += ":MT1(PTGOODELECTRONS[0],ETAGOODELECTRONS[0],PHIGOODELECTRONS[0],METPXraw[0],METPYraw[0]){0,150,15,\"MT1\"}";
	//if(NGOODMUONS%2==1)
	//varexp += ":MT1(PTGOODMUONS[2],ETAGOODMUONS[2],PHIGOODMUONS[2],METPXraw[0],METPYraw[0]){0,150,15,\"MT1\"}";
	//varexp += ":MINJETPT{0,400,40}:MAXJETPT{0,400,40}";
	
	// Global cuts, if desired
	TString selection = "PTGOODLEPTONS[0] > 25 && PTGOODLEPTONS[1] > 15 && PTGOODLEPTONS[2] > 10";// && !(RUN>=275318&&RUN<=275376)"; // "!(AIC && METraw < 50 && HT < 200)";
	//selection += " && NGOODELECTRONS == 3";
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler,"MM");
	
	//assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
	assembler->setDefaultBundle(assembler->getBundle("fakePresentationBundle"));
	//assembler->setMode("noRatioPlot");
	assembler->setMode("noWZsystematics");
	assembler->setMode("noZZsystematics");
	assembler->setMode("noTTsystematics");
	assembler->setMode("fullPrecision");
	setupData(assembler);
	setupBackgroundMC(assembler);
	//	setupBackgroundMC(assembler, true);
	setupBackgroundDD(assembler);
	setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	// At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
	
	mkdir("WZ_MM_15.9ifb_21Sep", 0755);
	chdir("WZ_MM_15.9ifb_21Sep");
	
// Check for duplicate events
	
//	assembler->project("NLIGHTLEPTONS", true)->getMeta(); // printMeta();
	//assembler->project("NLIGHTLEPTONS", true)->print();
	
	// WZ control plot
	assembler->setRange("NLIGHTLEPTONS", 3, 3);
	//	assembler->setRange("NGOODELECTRONS",2);
	//assembler->setRange("NGOODTAUS", 0, 0);
	assembler->setRange("NOSSF", 1, 1);
	assembler->setRange("ONZ", 1);
	
//makeNicePlot(assembler->project("(METraw)", true)->plot(true), "METraw [GeV]")->SaveAs("../nicePlots/L3DYz1Tau0_METraw.png");

	//assembler->setRange("NBJETSCSVM", 0, 0);
	
	assembler->setRange("METraw", 50, 70, false);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70_MT.png");
	//assembler->project("MT1", true)->plot(false)->SaveAs("WZ_METraw50to70_MT1.png");
//makeNicePlot(assembler->project("MT", true)->plot(false), "M_{T}", "GeV")->SaveAs("../nicePlots/WZ_METraw50to70_MT.png");
//makeNicePlot(assembler->project("PTOSSF", true)->plot(false), "p_{T}(Z)", "GeV")->SaveAs("../nicePlots/WZ_METraw50to70_PTOSSF.png");
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw50to70_HT.png");
	assembler->project("HT", true)->plot(true)->SaveAs("WZ_METraw50to70_HT_log.png");
	assembler->setRange("NGOODMUONS%2", 0, 0);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70_evenMuon_MT.png");
	assembler->project("MT1", true)->plot(false)->SaveAs("WZ_METraw50to70_evenMuon_MT1.png");
	assembler->setRange("NGOODMUONS%2", 1, 1);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70_oddMuon_MT.png");
	assembler->project("MT1", true)->plot(false)->SaveAs("WZ_METraw50to70_oddMuon_MT1.png");
	assembler->setRange("NGOODMUONS%2");
	
	assembler->setRange("NGOODMUONS", 0, 0);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70_Mu0_MT.png");
	assembler->setRange("NGOODMUONS", 1, 1);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70_Mu1_MT.png");
	assembler->setRange("NGOODMUONS", 2, 2);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70_Mu2_MT.png");
	assembler->setRange("NGOODMUONS", 3, 3);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70_Mu3_MT.png");
	assembler->setRange("NGOODMUONS");
	
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw50to70_HT.png");
	assembler->project("HT", true)->plot(true)->SaveAs("WZ_METraw50to70_HT_log.png");
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_METraw50to70_NGOODJETS.png");
//makeNicePlot(assembler->project("NGOODJETS", true)->plot(false), "n_{jets}")->SaveAs("../nicePlots/WZ_METraw50to70_NGOODJETS.png");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("NGOODJETS", 0, 0);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw50to70NGOODJETS0_HT.png");
	assembler->setRange("NGOODJETS", 1, 1);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw50to70NGOODJETS1_HT.png");
	assembler->setRange("NGOODJETS", 2, 2);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw50to70NGOODJETS2_HT.png");
	assembler->setRange("NGOODJETS", 3, 3);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw50to70NGOODJETS3_HT.png");
	assembler->setRange("NGOODJETS");
	
	assembler->setRange("HT", 0, 200, false);
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw50to70HT0to200_MT.png");
	assembler->project("MT", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_METraw50to70HT0to200_NGOODJETS.png");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("HT", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_METraw50to70HTgt200_NGOODJETS.png");
	assembler->project("NGOODJETS", true)->print();
	
	assembler->setRange("METraw");
	assembler->setRange("HT");
	//

	assembler->setRange("METraw", 70, 100, false);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100_MT.png");
        //assembler->project("MT1", true)->plot(false)->SaveAs("WZ_METraw70to100_MT1.png");                           
	//makeNicePlot(assembler->project("MT", true)->plot(false), "M_{T}", "GeV")->SaveAs("../nicePlots/WZ_METraw70to100_MT.png");                                                                                                              
	//makeNicePlot(assembler->project("PTOSSF", true)->plot(false), "p_{T}(Z)", "GeV")->SaveAs("../nicePlots/WZ_METraw70to100_PTOSSF.png");                                                                                                   
        assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw70to100_HT.png");
        assembler->project("HT", true)->plot(true)->SaveAs("WZ_METraw70to100_HT_log.png");
        assembler->setRange("NGOODMUONS%2", 0, 0);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100_evenMuon_MT.png");
        assembler->project("MT1", true)->plot(false)->SaveAs("WZ_METraw70to100_evenMuon_MT1.png");
        assembler->setRange("NGOODMUONS%2", 1, 1);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100_oddMuon_MT.png");
        assembler->project("MT1", true)->plot(false)->SaveAs("WZ_METraw70to100_oddMuon_MT1.png");
        assembler->setRange("NGOODMUONS%2");

        assembler->setRange("NGOODMUONS", 0, 0);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100_Mu0_MT.png");
        assembler->setRange("NGOODMUONS", 1, 1);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100_Mu1_MT.png");
        assembler->setRange("NGOODMUONS", 2, 2);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100_Mu2_MT.png");
        assembler->setRange("NGOODMUONS", 3, 3);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100_Mu3_MT.png");
        assembler->setRange("NGOODMUONS");

        assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw70to100_HT.png");
        assembler->project("HT", true)->plot(true)->SaveAs("WZ_METraw70to100_HT_log.png");
        assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_METraw70to100_NGOODJETS.png");
//makeNicePlot(assembler->project("NGOODJETS", true)->plot(false), "n_{jets}")->SaveAs("../nicePlots/WZ_METraw70to100_NGOODJETS.png");                                                                                                    
        assembler->project("NGOODJETS", true)->print();

        assembler->setRange("NGOODJETS", 0, 0);
        assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw70to100NGOODJETS0_HT.png");
        assembler->setRange("NGOODJETS", 1, 1);
        assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw70to100NGOODJETS1_HT.png");
        assembler->setRange("NGOODJETS", 2, 2);
        assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw70to100NGOODJETS2_HT.png");
        assembler->setRange("NGOODJETS", 3, 3);
        assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw70to100NGOODJETS3_HT.png");
        assembler->setRange("NGOODJETS");

        assembler->setRange("HT", 0, 200, false);
        assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw70to100HT0to200_MT.png");
        assembler->project("MT", true)->print();
        assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_METraw70to100HT0to200_NGOODJETS.png");
        assembler->project("NGOODJETS", true)->print();

        assembler->setRange("HT", 200);
        assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_METraw70to100HTgt200_NGOODJETS.png");
        assembler->project("NGOODJETS", true)->print();

	assembler->setRange("METraw");

	///
	assembler->setRange("MT", 50, 100, false);
	assembler->setRange("HT", 0, 200, false);
	assembler->project("METraw", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_METraw.png");
//makeNicePlot(assembler->project("METraw", true)->plot(false), "E_{T}^{miss}", "GeV")->SaveAs("../nicePlots/WZ_MT50to100HT0to200_METraw.png");
	assembler->project("METraw", true)->print();
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HT0to200_NGOODJETS.png");
	assembler->setRange("HT", 200);
	assembler->project("NGOODJETS", true)->plot(false)->SaveAs("WZ_MT50to100HTgt200_NGOODJETS.png");
	
	assembler->setRange("HT");
	assembler->setRange("HT", 0, 200, false);
	assembler->project("METraw", true)->plot(false)->SaveAs("WZ_HT0to200_METraw.png");
	assembler->setRange("METraw");
	assembler->setRange("HT");
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_HT.png");
	assembler->project("HT", true)->plot(true)->SaveAs("WZ_HT_log.png");

	assembler->setRange("METraw", 0, 50, false);
	assembler->project("HT", true)->plot(false)->SaveAs("WZ_METraw0to50_HT.png");
	assembler->project("MT", true)->plot(false)->SaveAs("WZ_METraw0to50_MT.png");
	
	assembler->setRange();
	
	delete assembler;
}

double MT1(double pt, double eta, double phi, double METx, double METy){
  TLorentzVector wl;
  TLorentzVector metv;
  wl.SetPtEtaPhiM(pt,eta,phi,0);
  metv.SetXYZM(METx, METy, 0, 0);
  //
  double MT = sqrt(2*metv.Pt()*wl.Pt()*( 1 - cos(wl.DeltaPhi(metv))));
  return MT;
}
