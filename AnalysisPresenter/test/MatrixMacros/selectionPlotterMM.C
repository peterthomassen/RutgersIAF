#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenterMM.C"

void rateMeasurementMC() {
  ///////////////////////
  // Binning/selection //
  ///////////////////////
  
  // Specify axes and bins of multidimensional histogram
  
  std::string varexp = "NLEPTONS{0,10,10}:NGOODMUONS{0,10}:NGOODELECTRONS{0,10}:NGOODTAUS{0,10}:NLIGHTLEPTONS{0,10}";
  varexp += ":HT{0,1000,10}";
  varexp += ":HTLA{0,1000,10}";
  varexp += ":LT{0,1000,10}";
  varexp += ":LTLA{0,1000,10}";
  varexp += ":MET{0,300,30}";
  varexp += ":NGOODJETS{0,10}";
  varexp += ":(Alt$(PTGOODMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODMUONS[1],0)){0,200,40}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[0],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[1],0)){-1,2}";
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[1],0)){0,200,40}";
  varexp += ":(Alt$(ISPROMPTMUON[0],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[1],0)){-1,2}";
  //
  varexp += ":(Alt$(PTGOODELECTRON[0],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODELECTRONS[1],0)){0,200,40}";
  varexp += ":(Alt$(ISTIGHTMATRIXELECTRON[0],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXELECTRON[1],0)){-1,2}";
  varexp += ":(Alt$(PTTIGHTMATRIXELECTRONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTTIGHTMATRIXELECTRONS[1],0)){0,200,40}";
  varexp += ":(Alt$(ISPROMPTELECTRON[0],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTELECTRON[1],0)){-1,2}";

  // Configuration Params
  std::string dirname="rateMeasurementMC";
  bool isTagNprobeLike = false;

  // Global cuts, if desired
  TString selection = "1";
  
  ////////////////////////
  // Initialize and run //
  ////////////////////////
  Assembler* assembler = new Assembler();
  init(assembler);
  
  assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
  assembler->setMode("noRatioPlot");
  

  setupBackgroundMC(assembler);
  prepare(assembler);
  assembler->process(varexp, selection, false);
  //assembler->process(varexp, selection, true);
  
  // At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
  mkdir(dirname, 0755);
  chdir(dirname);
  
  // Check for duplicate events
  // ---  
  

  //all
  assembler->setRange();
  assembler->project("HT",   true )->plot(true)->SaveAs("All_HT.pdf");
  assembler->project("HTLA", true )->plot(true)->SaveAs("All_HTLA.pdf");
  assembler->project("LT",   true )->plot(true)->SaveAs("All_LT.pdf");
  assembler->project("LTLA", true )->plot(true)->SaveAs("All_LTLA.pdf");
  assembler->project("MET",  true )->plot(true)->SaveAs("All_MET.pdf");
  assembler->project("NLEPTONS",       true )->plot(false)->SaveAs("All_NLEPTONS.pdf");
  assembler->project("NLIGHTLEPTONS",  true )->plot(false)->SaveAs("All_NLEPTONS.pdf");
  assembler->project("NGOODMUONS",     true )->plot(false)->SaveAs("All_NGOODMUONS.pdf");
  assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("All_NGOODELECTRONS.pdf");
  assembler->project("NGOODTAUS",      true )->plot(false)->SaveAs("All_NGOODTAUS.pdf");
  assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS1.pdf");
  assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS2.pdf");
  assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_PTGOODELECTRONS1.pdf");
  assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_PTGOODELECTRONS2.pdf");


  if(isTagNprobeLike){
    //2Mu - tag-and-probe like in DY
    assembler->setRange();  
    assembler->setRange("NGOODMUONS", 2, 2);//...................exactly 2 loose muons
    assembler->setRange("QGOODMUONS[0]*QGOODMUONS[1]", -1, -1);//..2 loose muons OS
    // -------------------------------------------
    assembler->project("NGOODMUONS",     true )->plot(false)->SaveAs("Sel2Mu_NGOODMUONS.pdf");
    assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("Sel2Mu_NGOODELECTRONS.pdf");
    assembler->project("NGOODTAUS",      true )->plot(false)->SaveAs("Sel2Mu_NGOODTAUS.pdf");
    //assembler->project("NTIGHTMATRIXMUONS", true )->plot(false)->SaveAs("Sel2Mu_NTIGHTMATRIXMUONS.pdf");
    //assembler->project("PTGOODLEPTONS", true)->plot(false)->SaveAs("Sel2Mu_PTGOODLEPTONS.pdf");
    assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("Sel2Mu_PTGOODMUONS0.pdf");
    assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("Sel2Mu_PTGOODMUONS1.pdf");
    //assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))", true)->plot(true)->SaveAs("Sel2Mu_PTTIGHTMATRIXMUONS0.pdf");
    //assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))", true)->plot(true)->SaveAs("Sel2Mu_PTTIGHTMATRIXMUONS1.pdf");
    //assembler->project("PTGOODMUONS[0]*ISTIGHTMATRIXMUON[0]", true)->plot(true)->SaveAs("Sel2Mu_PTGOODTIGHTMUONS0.pdf");	
    //assembler->project("PTGOODMUONS[1]*2", true)->plot(true)->SaveAs("Sel2Mu_PTGOODTIGHTMUONS1.pdf");
    //assembler->project("HT", true)->plot(true)->SaveAs("HT_log.pdf");
    //
    // Require muons to be prompt, leading muon to be tight, then test subleading muon
    assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
    assembler->setRange("(Alt$(ISPROMPTMUON[1],0))",      1, 1);
    assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
    // -------------------------------------------
    assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("Sel2MuPromptLeadMuTight_PTGOODMUONS0.pdf");
    assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("Sel2MuPromptLeadMuTight_PTGOODMUONS1.pdf");
    assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))", true)->plot(true)->SaveAs("Sel2MuPromptLeadMuTight_PTTIGHTMATRIXMUONS0.pdf");
    assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))", true)->plot(true)->SaveAs("Sel2MuPromptLeadMuTight_PTTIGHTMATRIXMUONS1.pdf");
    // Output histograms
    SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[1],0))",        true)->plot(true),"LooseMuons.root");
    SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))", true)->plot(true),"TightMuons.root");
        
    //2El - tag-and-probe like in DY
    assembler->setRange();  
    assembler->setRange("NGOODELECTRONS", 2, 2);//...................exactly 2 loose electrons
    assembler->setRange("QGOODELECTRONS[0]*QGOODELECTRONS[1]", -1, -1);//..2 loose electrons OS 
    // -------------------------------------------
    assembler->project("NGOODMUONS",     true )->plot(false)->SaveAs("Sel2Ele_NGOODMUONS.pdf");
    assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("Sel2Ele_NGOODELECTRONS.pdf");
    assembler->project("NGOODTAUS",      true )->plot(false)->SaveAs("Sel2Ele_NGOODTAUS.pdf");
    //assembler->project("NTIGHTMATRIXELECTRONS", true )->plot(false)->SaveAs("Sel2Ele_NTIGHTMATRIXELECTRONS.pdf");
    //assembler->project("PTGOODLEPTONS", true)->plot(false)->SaveAs("Sel2Ele_PTGOODLEPTONS.pdf");
    assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2Ele_PTGOODELECTRONS0.pdf");
    assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2Ele_PTGOODELECTRONS1.pdf");
    //assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2Ele_PTTIGHTMATRIXELECTRONS0.pdf");
    //assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2Ele_PTTIGHTMATRIXELECTRONS1.pdf");
    //assembler->project("PTGOODELECTRONS[0]*ISTIGHTMATRIXELECTRON[0]", true)->plot(true)->SaveAs("Sel2Ele_PTGOODTIGHTELECTRONS0.pdf");	
    //assembler->project("PTGOODELECTRONS[1]*2", true)->plot(true)->SaveAs("Sel2Ele_PTGOODTIGHTELECTRONS1.pdf");
    //assembler->project("HT", true)->plot(true)->SaveAs("HT_log.pdf");
    //
    // Require electrons to be prompt, leading electron to be tight, then test subleading electron
    assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
    assembler->setRange("(Alt$(ISPROMPTELECTRON[1],0))",      1, 1);
    assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
    // -------------------------------------------
    assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2ElePromptLeadEleTight_PTGOODELECTRONS0.pdf");
    assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2ElePromptLeadEleTight_PTGOODELECTRONS1.pdf");
    assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel2ElePromptLeadEleTight_PTTIGHTMATRIXELECTRONS0.pdf");
    assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))", true)->plot(true)->SaveAs("Sel2ElePromptLeadEleTight_PTTIGHTMATRIXELECTRONS1.pdf");
    // Output histograms
    SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectrons.root");
    SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))", true)->plot(true),"TightElectrons.root");
  }


  if(!isTagNprobeLike){
    //1Mu 
    assembler->setRange();  
    assembler->setRange("NGOODMUONS", 1, 1);//...................exactly 1 loose muon
    // -------------------------------------------
    assembler->project("NGOODMUONS",     true )->plot(false)->SaveAs("Sel1Mu_NGOODMUONS.pdf");
    assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("Sel1Mu_NGOODELECTRONS.pdf");
    assembler->project("NGOODTAUS",      true )->plot(false)->SaveAs("Sel1Mu_NGOODTAUS.pdf");
    assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("Sel1Mu_PTGOODMUONS0.pdf");
    //
    // Require leading muon to be prompt
    assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
    // -------------------------------------------
    assembler->project("(Alt$(PTGOODMUONS[0],0))",        true)->plot(true)->SaveAs("Sel1MuPrompt_PTGOODMUONS0.pdf");
    assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))", true)->plot(true)->SaveAs("Sel1MuPrompt_PTTIGHTMATRIXMUONS0.pdf");
    // Output histograms
    SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[0],0))",        true)->plot(true),"LooseMuons.root");
    SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))", true)->plot(true),"TightMuons.root");

    //1Ele
    assembler->setRange();  
    assembler->setRange("NGOODELECTRONS", 1, 1);//...................exactly 1 loose electron
    // -------------------------------------------
    assembler->project("NGOODMUONS",     true )->plot(false)->SaveAs("Sel1Ele_NGOODMUONS.pdf");
    assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("Sel1Ele_NGOODELECTRONS.pdf");
    assembler->project("NGOODTAUS",      true )->plot(false)->SaveAs("Sel1Ele_NGOODTAUS.pdf");
    assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel1Ele_PTGOODELECTRONS0.pdf");
    //
    // Require leading electron to be prompt
    assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
    // -------------------------------------------
    assembler->project("(Alt$(PTGOODELECTRONS[0],0))",        true)->plot(true)->SaveAs("Sel1ElePrompt_PTGOODELECTRONS0.pdf");
    assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel1ElePrompt_PTTIGHTMATRIXELECTRONS0.pdf");
    // Output histograms
    SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectrons.root");
    SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))", true)->plot(true),"TightElectrons.root");
  }

  

  assembler->setRange();  
  delete assembler;
}
