#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenterMMdynamic.C"

void selectionPlotterMMwLUT() {
  ///////////////////////
  // Binning/selection //
  ///////////////////////
  
  // Specify axes and bins of multidimensional histogram
  
  std::string varexp = "NLEPTONS{0,10,10}:NGOODMUONS{0,10}:NGOODELECTRONS{0,10}:NGOODTAUS{0,10}:NLIGHTLEPTONS{0,10}:NGOODJETS{0,10}:NGOODBJETSCSVM{0,10}";
  varexp += ":NMATRIXJETSLA{0,10}";
  varexp += ":HT{0,1000,20}";
  varexp += ":HTLA{0,1000,20}";
  varexp += ":LT{0,1000,20}";
  varexp += ":LTLA{0,1000,20}";
  varexp += ":LTLA3{0,1000,20}";
  varexp += ":MET{0,300,30}";
  varexp += ":MT{0,500,50}";
  varexp += ":NRECOVERTICES{-0.5,50.5,51}";
  varexp += ":(Alt$(MOSSF,0)){0,200}";
  //
  varexp += ":(Alt$(PTGOODMUONS[0],0)){0,200,40}"; // Muon Params 1
  varexp += ":PTGOODMUONS[0]{0,200,20}"; 
  varexp += ":(Alt$(ETAGOODMUONS[0],-3)){-3,3,20}";
  varexp += ":(abs(ETAGOODMUONS[0])){-3,3,20}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[0],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[0],0)){-1,2}";
  varexp += ":JETNOOFCONSTGOODMUONS[0]{-0.5,50.5}";
  //
  varexp += ":(Alt$(PTGOODMUONS[1],0)){0,200,40}"; // Muon Params 2
  varexp += ":PTGOODMUONS[1]{0,200,20}"; 
  varexp += ":(Alt$(ETAGOODMUONS[1],-3)){-3,3,20}";
  varexp += ":(abs(ETAGOODMUONS[1])){-3,3,20}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[1],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[1],0)){-1,2}";
  varexp += ":JETNOOFCONSTGOODMUONS[1]{-0.5,50.5}";
  //
  varexp += ":(Alt$(PTGOODMUONS[2],0)){0,200,40}"; // Muon Params 3
  varexp += ":PTGOODMUONS[2]{0,200,20}"; 
  varexp += ":(Alt$(ETAGOODMUONS[2],-3)){-3,3,20}";
  varexp += ":(abs(ETAGOODMUONS[2])){-3,3,20}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[2],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[2],0)){-1,2}";
  varexp += ":JETNOOFCONSTGOODMUONS[2]{-0.5,50.5}";
  //
  varexp += ":LeptonTypeVal3DLA{0,400}";

  // Configuration Params
  std::string dirname="selectionPlotterMM_MuMuMu";

  // Global cuts, if desired
  TString selection = "1";
  
  ////////////////////////
  // Initialize and run //
  ////////////////////////
  Assembler* assembler = new Assembler();
  init(assembler);
  
  assembler->setDefaultBundle(assembler->getBundle("presentationBundle"));
  //assembler->setMode("noRatioPlot");
  //assembler->setMode("ZscorePlot");

  setupBackgroundMC(assembler);
  prepare(assembler);
  assembler->process(varexp, selection, false);
  //assembler->process(varexp, selection, true);
  
  // At this point, we have the multidimensional histogram in memory and can start taking projections (tables, 1d histograms, ...)
  mkdir(dirname.c_str(), 0755);
  chdir(dirname.c_str());
  
  // Check for duplicate events
  // ---  

  //all
  assembler->setRange();
  // ------------------------------------------
  assembler->setRange("NGOODMUONS", 3);//...................// triple Mu Selection
  assembler->setRange("LeptonTypeVal3DLA", 222,222);//......// triple Mu Selection
  //assembler->setRange("(abs(ETAGOODMUONS[0]))",0,0.9);
  //assembler->setRange("(abs(ETAGOODMUONS[1]))",0,0.9);
  //assembler->setRange("(abs(ETAGOODMUONS[2]))",0,1.2);
  assembler->setRange("(Alt$(PTGOODMUONS[0],0))",25);//trig cuts
  assembler->setRange("(Alt$(PTGOODMUONS[1],0))",15);//trig cuts
  assembler->setRange("(Alt$(PTGOODMUONS[2],0))",10);//trig cuts
  assembler->setRange("(Alt$(MOSSF,0))",89,93);
  // ------------------------------------------
  //
  assembler->project("(Alt$(MOSSF,0))",   true )->plot(true)->SaveAs("All_MOSSF.pdf");
  //SaveHistograms(assembler->project("(Alt$(MOSSF,0))",   true )->plot(true),"All_MOSSF.root");
  assembler->project("HT",   true )->plot(true)->SaveAs("All_HT.pdf");
  //SaveHistograms(assembler->project("HT",   true )->plot(true),"All_HT.root");
  assembler->project("HTLA", true )->plot(true)->SaveAs("All_HTLA.pdf");
  //SaveHistograms(assembler->project("HTLA", true )->plot(true),"All_HTLA.root");
  assembler->project("LT",   true )->plot(true)->SaveAs("All_LT.pdf");
  //SaveHistograms(assembler->project("LT",   true )->plot(true),"All_LT.root");
  assembler->project("LTLA", true )->plot(true)->SaveAs("All_LTLA.pdf");
  //SaveHistograms(assembler->project("LTLA", true )->plot(true),"All_LTLA.root");
  assembler->project("LTLA3", true )->plot(true)->SaveAs("All_LTLA3.pdf");
  //SaveHistograms(assembler->project("LTLA3", true )->plot(true),"All_LTLA3.root");
  assembler->project("MET",  true )->plot(true)->SaveAs("All_MET.pdf");
  //SaveHistograms(assembler->project("MET",  true )->plot(true),"All_MET.root");
  assembler->project("LeptonTypeVal3DLA",  true )->plot(true)->SaveAs("All_LeptonTypeVal3DLA.pdf");
  //SaveHistograms(assembler->project("LeptonTypeVal3DLA",  true )->plot(true),"All_LeptonTypeVal3DLA.root");
  assembler->project("NLEPTONS",       true )->plot(true)->SaveAs("All_NLEPTONS.pdf");
  //SaveHistograms(assembler->project("NLEPTONS",       true )->plot(true),"All_NLEPTONS.root");
  assembler->project("NLIGHTLEPTONS",  true )->plot(true)->SaveAs("All_NLIGHTLEPTONS.pdf");
  //SaveHistograms(assembler->project("NLIGHTLEPTONS",  true )->plot(true),"All_NLIGHTLEPTONS.root");
  assembler->project("NGOODMUONS",     true )->plot(true)->SaveAs("All_NGOODMUONS.pdf");
  //SaveHistograms(assembler->project("NGOODMUONS",     true )->plot(true),"All_NGOODMUONS.root");
  assembler->project("NGOODELECTRONS", true )->plot(true)->SaveAs("All_NGOODELECTRONS.pdf");
  //SaveHistograms(assembler->project("NGOODELECTRONS", true )->plot(true),"All_NGOODELECTRONS.root");
  assembler->project("NGOODTAUS",      true )->plot(true)->SaveAs("All_NGOODTAUS.pdf");
  //SaveHistograms(assembler->project("NGOODTAUS",      true )->plot(true),"All_NGOODTAUS.root");
  assembler->project("NGOODJETS",      true )->plot(true)->SaveAs("All_NGOODJETS.pdf");
  //SaveHistograms(assembler->project("NGOODJETS",      true )->plot(true),"All_NGOODJETS.root");
  assembler->project("NMATRIXJETSLA",      true )->plot(true)->SaveAs("All_NMATRIXJETSLA.pdf");
  //SaveHistograms(assembler->project("NMATRIXJETSLA",      true )->plot(true),"All_NMATRIXJETSLA.root");
  assembler->project("NGOODBJETSCSVM", true )->plot(true)->SaveAs("All_NGOODBJETSCSVM.pdf");
  //SaveHistograms(assembler->project("NGOODBJETSCSVM", true )->plot(true),"All_NGOODBJETSCSVM.root");
  assembler->project("NRECOVERTICES",  true )->plot(true)->SaveAs("All_NRECOVERTICES.pdf");
  //SaveHistograms(assembler->project("NRECOVERTICES",  true )->plot(true),"All_NRECOVERTICES.root");
  //
  //

  assembler->project("PTGOODMUONS[0]",   true)->plot(true)->SaveAs("All_PTGOODMUONS1.pdf"); //  Mu Parameters 1
  //SaveHistograms(assembler->project("PTGOODMUONS[0]",   true)->plot(true),"All_PTGOODMUONS1.root");
  assembler->project("(Alt$(ETAGOODMUONS[0],-3))", true)->plot(true)->SaveAs("All_ETAGOODMUONS1.pdf");
  //SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[0],-3))", true)->plot(true),"All_ETAGOODMUONS1.root");
  assembler->project("(Alt$(ISPROMPTMUON[0],0))",   true)->plot(true)->SaveAs("All_ISPROMPTMUON1.pdf"); 
  //SaveHistograms(assembler->project("(Alt$(ISPROMPTMUON[0],0))",   true)->plot(true),"All_ISPROMPTMUON1.root");
  assembler->project("JETNOOFCONSTGOODMUONS[0]",   true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODMUONS1.pdf");
  //SaveHistograms(assembler->project("JETNOOFCONSTGOODMUONS[0]",   true)->plot(true),"All_JETNOOFCONSTGOODMUONS1.root");
  //
  assembler->project("PTGOODMUONS[1]",   true)->plot(true)->SaveAs("All_PTGOODMUONS2.pdf"); //  Mu Parameters 2
  //SaveHistograms(assembler->project("PTGOODMUONS[1]",   true)->plot(true),"All_PTGOODMUONS2.root");
  assembler->project("(Alt$(ETAGOODMUONS[1],-3))", true)->plot(true)->SaveAs("All_ETAGOODMUONS2.pdf");
  //SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[1],-3))", true)->plot(true),"All_ETAGOODMUONS2.root");
  assembler->project("(Alt$(ISPROMPTMUON[1],0))",   true)->plot(true)->SaveAs("All_ISPROMPTMUON2.pdf"); 
  //SaveHistograms(assembler->project("(Alt$(ISPROMPTMUON[1],0))",   true)->plot(true),"All_ISPROMPTMUON2.root");
  assembler->project("JETNOOFCONSTGOODMUONS[1]",   true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODMUONS2.pdf");
  //SaveHistograms(assembler->project("JETNOOFCONSTGOODMUONS[1]",   true)->plot(true),"All_JETNOOFCONSTGOODMUONS2.root");
  //
  assembler->project("PTGOODMUONS[2]",   true)->plot(true)->SaveAs("All_PTGOODMUONS3.pdf"); //  Mu Parameters 3
  //SaveHistograms(assembler->project("PTGOODMUONS[2]",   true)->plot(true),"All_PTGOODMUONS3.root");
  assembler->project("(Alt$(ETAGOODMUONS[2],-3))", true)->plot(true)->SaveAs("All_ETAGOODMUONS3.pdf");
  //SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[2],-3))", true)->plot(true),"All_ETAGOODMUONS3.root");
  assembler->project("(Alt$(ISPROMPTMUON[2],0))",   true)->plot(true)->SaveAs("All_ISPROMPTMUON3.pdf");
  //SaveHistograms(assembler->project("(Alt$(ISPROMPTMUON[2],0))",   true)->plot(true),"All_ISPROMPTMUON3.root");
  assembler->project("JETNOOFCONSTGOODMUONS[2]",   true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODMUONS3.pdf");
  //SaveHistograms(assembler->project("JETNOOFCONSTGOODMUONS[2]",   true)->plot(true),"All_JETNOOFCONSTGOODMUONS3.root");

  //
  
  assembler->setRange();  
  delete assembler;
}
