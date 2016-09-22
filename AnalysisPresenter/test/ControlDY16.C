#include <sys/stat.h>
#include <unistd.h>
#include "helperAnalysisPresenter_hybrid_13TeV.C"

void ControlDY16() {
	///////////////////////
	// Binning/selection //
	///////////////////////
	
	// Specify axes and bins of multidimensional histogram
	//DY CR
  std::string varexp = "NLIGHTLEPTONS[0]{0,5}:MOSSF[0]{11,131,36}:NGOODELECTRONS[0]{0,3}:NGOODMUONS[0]{0,3}:NBJETSCSVM[0]{0,2}:MET[0]{0,400,16}:HT[0]{0,600,24}:NGOODJETS[0]{0,5}:PTGOODLEPTONS[0]{0,300,30}:PTGOODLEPTONS[1]{0,300,30}:Alt$(ETAGOODMUONS[0],-4){-2.5,2.5,10}:Alt$(ETAGOODMUONS[1],-4){-2.5,2.5,10}::Alt$(ETAGOODELECTRONS[0],-4){-2.5,2.5,10}:Alt$(ETAGOODELECTRONS[1],-4){-2.5,2.5,10}";
  //varexp += ":(Alt$(ETAGOODMUONS[0],-4)){-3,3,20}";
  //varexp += ":(Alt$(ETAGOODMUONS[1],-4)){-3,3,20}";
  //varexp += ":(Alt$(ETAGOODELECTRONS[0],-4)){-3,3,20}";
  //varexp += ":(Alt$(ETAGOODELECTRONS[1],-4)){-3,3,20}";
  //varexp+=":ETAGOODMUONS[0]{-2.5,2.5,50}";/*:ETAGOODMUONS[1]{-2.5,2.5,50}";*/
  //varexp+=":ETAGOODMUONS[1]{-2.5,2.5,50}";
  //varexp+=":ETAGOODELECTRONS[0]{-2.5,2.5,50}";/*:ETAGOODMUONS[1]{-2.5,2.5,50}";*/
  //varexp+=":ETAGOODELECTRONS[1]{-2.5,2.5,50}";
  //varexp+=":ETAGOODELECTRONS[0]{-2.5,2.5,50}";/*:ETAGOODELECTRONS[1]{-2.5,2.5,50}";*/
  varexp+=":NRECOVERTICES[0]{0,50,50}";
	
	//DY CR
	TString selection = "PTGOODLEPTONS[0] > 25 && PTGOODLEPTONS[1] > 15 && NLIGHTLEPTONS[0] == Sum$(ISTIGHTMATRIXMUON) + Sum$(ISTIGHTMATRIXELECTRON)";
	
	
	////////////////////////
	// Initialize and run //
	////////////////////////
	Assembler* assembler = new Assembler();
	init(assembler,"MC");
	assembler->setMode("fullPrecision");
	assembler->setMode("noTTsystematics");
	assembler->setMode("noZZsystematics");
	assembler->setMode("noWZsystematics");
	//assembler->setMode("backgroundModel_");
	setupData(assembler,true);
        setupBackgroundMC(assembler,true);
	//setupBackgroundDD(assembler);
	//setupFakeRates(assembler);
	assembler->setDebug(true);
	prepare(assembler);
	assembler->process(varexp, selection);
	
	mkdir("DY_MC_15.9ifb_22Sep", 0755);
        chdir("DY_MC_15.9ifb_22Sep");
	//DY Mu+Ele CR
	assembler->setRange("NLIGHTLEPTONS[0]", 2, 2);
	//	assembler->setRange("NBJETSCSVM[0]", 0, 0);
	assembler->setRange("MET[0]", 0, 50, false );
	//assembler->setRange("HT[0]", 0, 200, false);
	assembler->setRange("NGOODMUONS[0]", 2, 2);
	assembler->project("MOSSF[0]", true)->plot(false)->SaveAs("DY_MOSSF_2MuMET0TO50.root");
	assembler->project("MOSSF[0]", true)->plot(false)->SaveAs("DY_MOSSF_2MuMET0TO50.png");
	assembler->project("NBJETSCSVM[0]",true)->plot(false)->SaveAs("DY_NBJETSCSVM_2MuMET0TO50.png");
	assembler->project("PTGOODLEPTONS[0]", true)->plot(true)->SaveAs("DY_PT1Mu_2MuMET0TO50.root");
	assembler->project("PTGOODLEPTONS[0]", true)->print();
	assembler->project("PTGOODLEPTONS[0]", true)->plot(true)->SaveAs("DY_PT1Mu_2MuMET0TO50.png");
	assembler->project("Alt$(ETAGOODMUONS[0],-4)", true)->plot(true)->SaveAs("DY_ETA1Mu_2MuMET0TO50.root");
        assembler->project("Alt$(ETAGOODMUONS[0],-4)", true)->plot(true)->SaveAs("DY_ETA1Mu_2MuMET0TO50.png");
	assembler->project("Alt$(ETAGOODMUONS[0],-4)", true)->print();
	assembler->project("PTGOODLEPTONS[1]", true)->print();
	assembler->project("PTGOODLEPTONS[1]", true)->plot(true)->SaveAs("DY_PT2Mu_2MuMET0TO50.root");
	assembler->project("PTGOODLEPTONS[1]", true)->plot(true)->SaveAs("DY_PT2Mu_2MuMET0TO50.png");
	assembler->project("Alt$(ETAGOODMUONS[1],-4)", true)->plot(true)->SaveAs("DY_ETA2Mu_2MuMET0TO50.root");
        assembler->project("Alt$(ETAGOODMUONS[1],-4)", true)->plot(true)->SaveAs("DY_ETA2Mu_2MuMET0TO50.png");
	assembler->project("Alt$(ETAGOODMUONS[1],-4)", true)->print();
	assembler->project("NGOODJETS[0]", true)->plot(true)->SaveAs("DY_nJets_2MuMET0TO50.root");
	assembler->project("NGOODJETS[0]", true)->plot(true)->SaveAs("DY_nJets_2MuMET0TO50.png");
	assembler->project("NRECOVERTICES[0]", true)->plot(false)->SaveAs("DY_nVertices_2MuMET0TO50.root");
	assembler->project("NRECOVERTICES[0]", true)->plot(false)->SaveAs("DY_nVertices_2MuMET0TO50.png");
	assembler->project("NGOODJETS[0]", true)->print();
	assembler->setRange("NGOODMUONS[0]");
	assembler->setRange("NGOODELECTRONS[0]", 2, 2);
	assembler->project("MOSSF[0]", true)->plot(false)->SaveAs("DY_MOSSF_2ElMET0TO50.root");
	assembler->project("MOSSF[0]", true)->print();
	assembler->project("MOSSF[0]", true)->plot(false)->SaveAs("DY_MOSSF_2ElMET0TO50.png");
	assembler->project("PTGOODLEPTONS[0]", true)->plot(true)->SaveAs("DY_PT1El_2ElMET0TO50.root");
	assembler->project("PTGOODLEPTONS[0]", true)->plot(true)->SaveAs("DY_PT1El_2ElMET0TO50.png");
	assembler->project("Alt$(ETAGOODELECTRONS[0],-4)", true)->plot(true)->SaveAs("DY_ETA1El_2ElMET0TO50.root");
        assembler->project("Alt$(ETAGOODELECTRONS[0],-4)", true)->plot(true)->SaveAs("DY_ETA1El_2ElMET0TO50.png");
	assembler->project("PTGOODLEPTONS[1]", true)->plot(true)->SaveAs("DY_PT2El_2ElMET0TO50.root");
	assembler->project("PTGOODLEPTONS[1]", true)->plot(true)->SaveAs("DY_PT2El_2ElMET0TO50.png");
	assembler->project("Alt$(ETAGOODELECTRONS[1],-4)", true)->plot(true)->SaveAs("DY_ETA2El_2ElMET0TO50.root");
        assembler->project("Alt$(ETAGOODELECTRONS[1],-4)", true)->plot(true)->SaveAs("DY_ETA2El_2ElMET0TO50.png");
	assembler->project("NGOODJETS[0]", true)->plot(true)->SaveAs("DY_nJets_2ElMET0TO50.root");
	assembler->project("NGOODJETS[0]", true)->plot(true)->SaveAs("DY_nJets_2ElMET0TO50.png");
	assembler->project("NRECOVERTICES[0]", true)->plot(false)->SaveAs("DY_nVertices_2ElMET0TO50.root");
	assembler->project("NRECOVERTICES[0]", true)->plot(false)->SaveAs("DY_nVertices_2ElMET0TO50.png");
	// Clean up
	delete assembler;
}
