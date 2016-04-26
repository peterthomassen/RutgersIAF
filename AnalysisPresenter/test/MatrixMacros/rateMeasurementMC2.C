#include <sys/stat.h>
#include <string>
#include <unistd.h>
#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"
#include "helperAnalysisPresenter_MConly.C"//

void rateMeasurementMC() {
  ///////////////////////
  // Binning/selection //
  ///////////////////////  
  // Specify axes and bins of multidimensional histogram
  
  std::string varexp = "NLEPTONS{0,10,10}:NGOODMUONS{0,10}:NGOODELECTRONS{0,10}:NGOODTAUS{0,10}:NLIGHTLEPTONS{0,10}";
  varexp +=":MOSSF{0,200,20}";
  varexp += ":HT{0,1000,10}";
  varexp += ":HTLA{0,1000,10}";
  varexp += ":LT{0,1000,10}";
  //varexp += ":LTLA{0,1000,10}";
  varexp += ":MET{0,300,30}";
  varexp += ":NGOODJETS{0,10}";
  varexp += ":NBOSONS{0,10}";
  varexp += ":(Alt$(PTGOODMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODMUONS[1],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODMUONS[2],0)){0,200,40}";

  varexp += ":(Alt$(ETAGOODMUONS[0],0)){-3,3,60}";
  varexp += ":(Alt$(ETAGOODMUONS[1],0)){-3,3,60}";
  varexp += ":(Alt$(ETAGOODMUONS[2],0)){-3,3,60}";

  varexp += ":(Alt$(QGOODMUONS[0],0)){-2,2}";
  varexp += ":(Alt$(QGOODMUONS[1],0)){-2,2}";
  varexp += ":(Alt$(QGOODMUONS[2],0)){-2,2}";


  varexp += ":(Alt$(CONECORRECTEDPTGOODMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(CONECORRECTEDPTGOODMUONS[1],0)){0,200,40}";

  varexp += ":(Alt$(ISTIGHTMATRIXMUON[0],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[1],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[2],0)){-1,2}";
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[1],0)){0,200,40}";
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[2],0)){0,200,40}";
  varexp += ":(Alt$(CONECORRECTEDPTTIGHTMATRIXMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(CONECORRECTEDPTTIGHTMATRIXMUONS[1],0)){0,200,40}";

  varexp += ":(Alt$(ETATIGHTMATRIXMUONS[0],0)){-3,3,60}";
  varexp += ":(Alt$(ETATIGHTMATRIXMUONS[1],0)){-3,3,60}";
  varexp += ":(Alt$(ETATIGHTMATRIXMUONS[2],0)){-3,3,60}";

  varexp += ":(Alt$(ISPROMPTMUON[0],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[1],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[2],0)){-1,2}";

  varexp +=":(Alt$(JETNOOFCONSTGOODMUONS[0],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTGOODMUONS[1],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTGOODMUONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR04TO08GOODMUONS[0],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR04TO08GOODMUONS[1],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR04TO08GOODMUONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONESUMETDR04TO08GOODMUONS[0],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR04TO08GOODMUONS[1],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR04TO08GOODMUONS[2],0)){0,500,100}";

  varexp +=":(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[0],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[1],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[0],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[1],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[0],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[1],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[2],0)){0,500,100}";
  
  //varexp +=":(Alt$(CONENDR04GOODMUONS[0],0)){0,100,100}";
  
  //varexp +=":(Alt$(CONENDR04GOODMUONS[0],0))+(Alt$(CONENDR04GOODMUONS[0],0)){0,100,100,\"test\"}";

  //varexp +=":CONENDR04TIGHTMATRIXMUONS[0]+CONENDR04TO08TIGHTMATRIXMUONS[0]{0,100,100,\"CONENDR0TO08TIGHTMATRIXMUONS\"}";
  // varexp +=":CONENDR04TIGHTMATRIXMUONS[1]+CONENDR04TO08TIGHTMATRIXMUONS[1]{0,100,100,\"CONENDR0TO08TIGHTMATRIXMUONS1\"}";
  // varexp +=":CONENDR04TIGHTMATRIXMUONS[2]+CONENDR04TO08TIGHTMATRIXMUONS[2]{0,100,100,\"CONENDR0TO08TIGHTMATRIXMUONS2\"}";
  varexp +=":(Alt$(CONENDR04GOODMUONS[0],0))+(Alt$(CONENDR04TO08GOODMUONS[0],0)){0,100,100,\"CONENDR0TO08GOODMUONS[0]\"}";
  varexp +=":(Alt$(CONENDR04GOODMUONS[1],0))+(Alt$(CONENDR04TO08GOODMUONS[1],0)){0,100,100,\"CONENDR0TO08GOODMUONS[1]\"}";
  varexp +=":(Alt$(CONENDR04GOODMUONS[2],0))+(Alt$(CONENDR04TO08GOODMUONS[2],0)){0,100,100,\"CONENDR0TO08GOODMUONS[2]\"}";
  //varexp +=":CONENDR04GOODMUONS+CONENDR04TO08GOODMUONS{0,100,100,\"CONENDR0TO08GOODMUONS\"}";
  //varexp +=":CONENDR04GOODMUONS[2]+CONENDR04TO08GOODMUONS[2]{0,100,100,\"CONENDR0TO08GOODMUONSc\"}";    
  varexp +=":(Alt$(PTRELGOODMUONS[0],0)){0,50,500}";
  varexp +=":(Alt$(PTRELGOODMUONS[1],0)){0,50,500}";
  varexp +=":(Alt$(PTRELGOODMUONS[2],0)){0,50,500}";

  
  // varexp +=":(Alt$([0],0)){0,50,50}";
  // varexp +=":(Alt$([0],1)){0,50,50}";


  //electrons

  varexp += ":(Alt$(PTGOODELECTRONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODELECTRONS[1],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODELECTRONS[2],0)){0,200,40}";

  varexp += ":(Alt$(QGOODELECTRONS[0],0)){-2,2}";
  varexp += ":(Alt$(QGOODELECTRONS[1],0)){-2,2}";
  varexp += ":(Alt$(QGOODELECTRONS[2],0)){-2,2}";

  varexp += ":(Alt$(ETAGOODELECTRONS[0],0)){-3,3,60}";
  varexp += ":(Alt$(ETAGOODELECTRONS[1],0)){-3,3,60}";
  varexp += ":(Alt$(ETAGOODELECTRONS[2],0)){-3,3,60}";

  varexp += ":(Alt$(ETATIGHTMATRIXELECTRONS[0],0)){-3,3,60}";
  varexp += ":(Alt$(ETATIGHTMATRIXELECTRONS[1],0)){-3,3,60}";
  varexp += ":(Alt$(ETATIGHTMATRIXELECTRONS[2],0)){-3,3,60}";
  varexp += ":(Alt$(CONECORRECTEDPTGOODELECTRONS[0],0)){0,200,40}";
  varexp += ":(Alt$(CONECORRECTEDPTGOODELECTRONS[1],0)){0,200,40}";
  varexp += ":(Alt$(ISTIGHTMATRIXELECTRON[0],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXELECTRON[1],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXELECTRON[2],0)){-1,2}";
  varexp += ":(Alt$(PTTIGHTMATRIXELECTRONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTTIGHTMATRIXELECTRONS[1],0)){0,200,40}";
  varexp += ":(Alt$(PTTIGHTMATRIXELECTRONS[2],0)){0,200,40}";

  varexp += ":(Alt$(CONECORRECTEDPTTIGHTMATRIXELECTRONS[0],0)){0,200,40}";
  varexp += ":(Alt$(CONECORRECTEDPTTIGHTMATRIXELECTRONS[1],0)){0,200,40}";

  varexp += ":(Alt$(ISPROMPTELECTRON[0],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTELECTRON[1],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTELECTRON[2],0)){-1,2}";


  varexp +=":(Alt$(JETNOOFCONSTGOODELECTRONS[0],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTGOODELECTRONS[1],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTGOODELECTRONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR03TO07GOODELECTRONS[0],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR03TO07GOODELECTRONS[1],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR03TO07GOODELECTRONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONESUMETDR03TO07GOODELECTRONS[0],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR03TO07GOODELECTRONS[1],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR03TO07GOODELECTRONS[2],0)){0,500,100}";

  varexp +=":(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[0],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[1],0)){0,100,100}";
  varexp +=":(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[0],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[1],0)){0,100,100}";
  varexp +=":(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[2],0)){0,100,100}";
  varexp +=":(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[0],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[1],0)){0,500,100}";
  varexp +=":(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[2],0)){0,500,100}";
  
  // varexp +=":CONENDR03TIGHTMATRIXELECTRONS[0]+CONENDR03TO07TIGHTMATRIXELECTRONS[0]{0,100,100,\"CONENDR0TO07TIGHTMATRIXELECTRONS0\"}";
  // varexp +=":CONENDR03TIGHTMATRIXELECTRONS[1]+CONENDR03TO07TIGHTMATRIXELECTRONS[1]{0,100,100,\"CONENDR0TO07TIGHTMATRIXELECTRONS1\"}";
  // varexp +=":CONENDR03TIGHTMATRIXELECTRONS[2]+CONENDR03TO07TIGHTMATRIXELECTRONS[2]{0,100,100,\"CONENDR0TO07TIGHTMATRIXELECTRONS2\"}";
  // varexp +=":CONENDR03GOODELECTRONS[0]+CONENDR03TO07GOODELECTRONS[0]{0,100,100,\"CONENDR0TO07GOODELECTRONS0\"}";
  // varexp +=":CONENDR03GOODELECTRONS[1]+CONENDR03TO07GOODELECTRONS[1]{0,100,100,\"CONENDR0TO07GOODELECTRONS1\"}";
  // varexp +=":CONENDR03GOODELECTRONS[2]+CONENDR03TO07GOODELECTRONS[2]{0,100,100,\"CONENDR0TO07GOODELECTRONS2\"}";

  varexp +=":(Alt$(CONENDR03GOODELECTRONS[0],0))+(Alt$(CONENDR03TO07GOODELECTRONS[0],0)){0,100,100,\"CONENDR0TO07GOODELECTRONS[0]\"}";
  varexp +=":(Alt$(CONENDR03GOODELECTRONS[1],0))+(Alt$(CONENDR03TO07GOODELECTRONS[1],0)){0,100,100,\"CONENDR0TO07GOODELECTRONS[1]\"}";
  varexp +=":(Alt$(CONENDR03GOODELECTRONS[2],0))+(Alt$(CONENDR03TO07GOODELECTRONS[2],0)){0,100,100,\"CONENDR0TO07GOODELECTRONS[2]\"}";

  varexp +=":(Alt$(PTRELGOODELECTRONS[0],0)){0,50,500}";
  varexp +=":(Alt$(PTRELGOODELECTRONS[1],0)){0,50,500}";
  varexp +=":(Alt$(PTRELGOODELECTRONS[2],0)){0,50,500}";




  // Configuration Params
  bool fake = true;
  //bool fake = false;
  //vector<string> slice = {"JETNOOFCONST","CONENDR04TO08","CONESUMETDR04TO08"};
  //vector<string> slice = {"JETNOOFCONST"};
  
  //vector<double> bin_low = {0,5,10,20,60,95};
  //vector<double> bin_high = {5,10,20,60,95,200};

  
  
  //  for(vector<string>::const_iterator s = slice.begin(); s != slice.end(); s++)for(int bin_iter =0;bin_iter<bin_low.size();bin_iter++){      
  //chdir("/home/shchauha/t3store/220316_matrix_method/useConeCorrPt/CMSSW_7_6_3_patch2/src/RutgersIAF/AnalysisPresenter/test/MatrixMacros");
  // char Str[16];
  // sprintf(Str, "%d",bin_iter);
  // std::string str;
  // const char * c = str.c_str();
  // cout<<"char name "<<c<<endl;      
  // TString d=*s+to_string(bin_iter);      
  //TString sample="TTbar/";
  TString sample="DYJets/";	     
  //TString dirname=sample+"Rates"+*s+to_string(bin_low.at(bin_iter))+"_"+to_string(bin_high.at(bin_iter));
  TString dirname=sample+"Rates_new13apr";
  // Global cuts, if desired
  //TString selection = "(ETAGOODMUONS<-1.5||ETAGOODMUONS>1.5)&&(ETATIGHTMATRIXMUONS<-1.5||ETATIGHTMATRIXMUONS>1.5)"; //2.5
  //TString selection = "(ETAGOODMUONS>-1.5&&ETAGOODMUONS<1.5)&&(ETATIGHTMATRIXMUONS>-1.5&&ETATIGHTMATRIXMUONS<1.5)"; //1.5
  //TString selection = "NBOSONS>0";
  TString selection = "NBOSONS>1";

  //TString selection = "(NLEPTONS==3)&&(NGOODMUONS==3||(NGOODMUONS==1&&81<MOSSF<101))";
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
  //assembler->project("LTLA", true )->plot(true)->SaveAs("All_LTLA.pdf");
  assembler->project("MET",  true )->plot(true)->SaveAs("All_MET.pdf");
  assembler->project("NLEPTONS",       true )->plot(false)->SaveAs("All_NLEPTONS.pdf");
  assembler->project("NLIGHTLEPTONS",  true )->plot(false)->SaveAs("All_NLEPTONS.pdf");
  assembler->project("NGOODMUONS",     true )->plot(false)->SaveAs("All_NGOODMUONS.pdf");
  assembler->project("NGOODELECTRONS", true )->plot(false)->SaveAs("All_NGOODELECTRONS.pdf");
  assembler->project("NGOODTAUS",      true )->plot(false)->SaveAs("All_NGOODTAUS.pdf");
  assembler->project("NBOSONS",   true )->plot(true)->SaveAs("All_NBOSONS.pdf");
  assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS0.pdf");
  assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS1.pdf");
  assembler->project("(Alt$(PTGOODMUONS[2],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS2.pdf");

  assembler->project("(Alt$(ETAGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_ETAGOODMUONS0.pdf");
  assembler->project("(Alt$(ETAGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_ETAGOODMUONS1.pdf");
  assembler->project("(Alt$(ETAGOODMUONS[2],0))", true)->plot(true)->SaveAs("All_ETAGOODMUONS2.pdf");

  assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODMUONS0.pdf");
  assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODMUONS1.pdf");
  assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[2],0))", true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODMUONS2.pdf");

  assembler->project("(Alt$(CONENDR04TO08GOODMUONS[0],0))", true)->plot(true)->SaveAs("All_CONENDR04TO08GOODMUONS0.pdf");
  assembler->project("(Alt$(CONENDR04TO08GOODMUONS[1],0))", true)->plot(true)->SaveAs("All_CONENDR04TO08GOODMUONS1.pdf");
  assembler->project("(Alt$(CONENDR04TO08GOODMUONS[2],0))", true)->plot(true)->SaveAs("All_CONENDR04TO08GOODMUONS2.pdf");

  assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[0],0))", true)->plot(true)->SaveAs("All_CONESUMETDR04TO08GOODMUONS0.pdf");
  assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[1],0))", true)->plot(true)->SaveAs("All_CONESUMETDR04TO08GOODMUONS1.pdf");
  assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[2],0))", true)->plot(true)->SaveAs("All_CONESUMETDR04TO08GOODMUONS2.pdf");


  assembler->project("(Alt$(QGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_QGOODMUONS0.pdf");
  assembler->project("(Alt$(QGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_QGOODMUONS1.pdf");
  assembler->project("(Alt$(QGOODMUONS[2],0))", true)->plot(true)->SaveAs("All_QGOODMUONS2.pdf");


  //assembler->project("(Alt$(CONENDR04GOODMUONS[0],0))", true)->plot(true)->SaveAs("All_CONENDR04GOODMUONS0.pdf");



  //
  assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_PTGOODELECTRONS0.pdf");
  assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_PTGOODELECTRONS1.pdf");
  assembler->project("(Alt$(PTGOODELECTRONS[2],0))", true)->plot(true)->SaveAs("All_PTGOODELECTRONS2.pdf");

  assembler->project("(Alt$(ETAGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_ETAGOODELECTRONS0.pdf");
  assembler->project("(Alt$(ETAGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_ETAGOODELECTRONS1.pdf");
  assembler->project("(Alt$(ETAGOODELECTRONS[2],0))", true)->plot(true)->SaveAs("All_ETAGOODELECTRONS2.pdf");

  assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODELECTRONS0.pdf");
  assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODELECTRONS1.pdf");
  assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[2],0))", true)->plot(true)->SaveAs("All_JETNOOFCONSTGOODELECTRONS2.pdf");

  assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_CONENDR03TO07GOODELECTRONS0.pdf");
  assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_CONENDR03TO07GOODELECTRONS1.pdf");
  assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[2],0))", true)->plot(true)->SaveAs("All_CONENDR03TO07GOODELECTRONS2.pdf");

  assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_CONESUMETDR03TO07GOODELECTRONS0.pdf");
  assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_CONESUMETDR03TO07GOODELECTRONS1.pdf");
  assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[2],0))", true)->plot(true)->SaveAs("All_CONESUMETDR03TO07GOODELECTRONS2.pdf");


  assembler->project("(Alt$(QGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_QGOODELECTRONS0.pdf");
  assembler->project("(Alt$(QGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_QGOODELECTRONS1.pdf");
  assembler->project("(Alt$(QGOODELECTRONS[2],0))", true)->plot(true)->SaveAs("All_QGOODELECTRONS2.pdf");



  // assembler->project("(Alt$(CONECORRECTEDPTGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_CONECORRECTEDPTGOODMUONS1.pdf");
  // assembler->project("(Alt$(CONECORRECTEDPTGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_CONECORRECTEDPTGOODMUONS2.pdf");
  // assembler->project("(Alt$(CONECORRECTEDPTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_CONECORRECTEDPTGOODELECTRONS1.pdf");
  // assembler->project("(Alt$(CONECORRECTEDPTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_CONECORRECTEDPTGOODELECTRONS2.pdf");
  //
  
  ////////////////
  ///FAKE RATES///
  ////////////////

  ////////////
  ////Muon////
  ////////////

  // 1L   
  assembler->setRange();    
  assembler->setRange("NBOSONS", 1);
  assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("SelVV_PTGOODMUONS0.pdf");
  assembler->setRange("NLEPTONS", 1,1);
  assembler->setRange("NGOODMUONS", 1, 1);
  //assembler->project("test", true)->plot(true)->SaveAs("All_testGOODMUONS0.pdf");

  assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("Sel1Mu_PTGOODMUONS0.pdf");
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      0, 0);
  assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("Sel1MuPrompt_PTGOODMUONS0.pdf");
      
  // TString va = "(Alt$("+*s+"GOODMUONS[0],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[0]",    true)->plot(true),"LooseMuonsCONENDR0TO0800Fake.root");  
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPTREL00Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPT00Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsETA00Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsJETNOOFCONST00Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08GOODMUONS[0],0))",        true)->plot(true),"LooseMuonsCONENDR04TO0800Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[0],0))",        true)->plot(true),"LooseMuonsCONESUMETDR04TO0800Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPT00Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))", true)->plot(true)->SaveAs("Sel1Mu_PTTIGHTMATRIXMUONS0.pdf");
  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[0]",    true)->plot(true),"TightMuonsCONENDR0TO0800Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[0],0))",        true)->plot(true),"TightMuonsPTREL00Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsPT00Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsETA00Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsJETNOOFCONST00Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsCONENDR04TO0800Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsCONESUMETDR04TO0800Fake.root");

  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsPT00Fake.root");

    
  // ///2L

  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 2,2);
  assembler->setRange("NGOODMUONS", 1, 1);
  assembler->setRange("NGOODELECTRONS", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      0, 0);
  // va = "(Alt$("+*s+"GOODMUONS[0],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);
  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[0]",    true)->plot(true),"LooseMuonsCONENDR0TO0801Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPTREL01Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPT01Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsETA01Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsJETNOOFCONST01Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08GOODMUONS[0],0))",        true)->plot(true),"LooseMuonsCONENDR04TO0801Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[0],0))",        true)->plot(true),"LooseMuonsCONESUMETDR04TO0801Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[0]",    true)->plot(true),"TightMuonsCONENDR0TO0801Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[0],0))",        true)->plot(true),"TightMuonsPTREL01Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsPT01Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsETA01Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsJETNOOFCONST01Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsCONENDR04TO0801Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsCONESUMETDR04TO0801Fake.root");

  
  //
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 2,2);
  assembler->setRange("NGOODMUONS", 2, 2);  
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[1],0))",      0, 0);

  // va = "(Alt$("+*s+"GOODMUONS[1],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[1]",    true)->plot(true),"LooseMuonsCONENDR0TO0811Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsPTREL11Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsPT11Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsETA11Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsJETNOOFCONST11Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08GOODMUONS[1],0))",        true)->plot(true),"LooseMuonsCONENDR04TO0811Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[1],0))",        true)->plot(true),"LooseMuonsCONESUMETDR04TO0811Fake.root");


  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[1],0))", 1, 1);

  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[1]",    true)->plot(true),"TightMuonsCONENDR0TO0811Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[1],0))",        true)->plot(true),"TightMuonsPTREL11Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsPT11Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsETA11Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsJETNOOFCONST11Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsCONENDR04TO0811Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsCONESUMETDR04TO0811Fake.root");

  
  //3L
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 3,3);
  assembler->setRange("NGOODMUONS", 3, 3);
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[1],0))",      1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[2],0))",      0, 0);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[1],0))", 1, 1);  
  // va = "(Alt$("+*s+"GOODMUONS[2],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);
  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[2]",    true)->plot(true),"LooseMuonsCONENDR0TO0822Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[2],0))",        true)->plot(true),"LooseMuonsPTREL22Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[2],0))",        true)->plot(true),"LooseMuonsPT22Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[2],0))",        true)->plot(true),"LooseMuonsETA22Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[2],0))",        true)->plot(true),"LooseMuonsJETNOOFCONST22Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08GOODMUONS[2],0))",        true)->plot(true),"LooseMuonsCONENDR04TO0822Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[2],0))",        true)->plot(true),"LooseMuonsCONESUMETDR04TO0822Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[2],0))",        true)->plot(true),"LooseMuonsPT22Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[2],0))", 1, 1);

  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[2]",    true)->plot(true),"TightMuonsCONENDR0TO0822Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[2],0))",        true)->plot(true),"TightMuonsPTREL22Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[2],0))",        true)->plot(true),"TightMuonsPT22Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXMUONS[2],0))",        true)->plot(true),"TightMuonsETA22Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[2],0))",        true)->plot(true),"TightMuonsJETNOOFCONST22Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[2],0))",        true)->plot(true),"TightMuonsCONENDR04TO0822Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[2],0))",        true)->plot(true),"TightMuonsCONESUMETDR04TO0822Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[2],0))",        true)->plot(true),"TightMuonsPT22Fake.root");

  //
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 3,3);
  assembler->setRange("NGOODMUONS", 2, 2);
  assembler->setRange("NGOODELECTRONS", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[1],0))",      0, 0);

  // va = "(Alt$("+*s+"GOODMUONS[1],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[1]",    true)->plot(true),"LooseMuonsCONENDR0TO0812Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsPTREL12Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsPT12Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsETA12Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsJETNOOFCONST12Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08GOODMUONS[1],0))",        true)->plot(true),"LooseMuonsCONENDR04TO0812Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[1],0))",        true)->plot(true),"LooseMuonsCONESUMETDR04TO0812Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[1],0))",        true)->plot(true),"LooseMuonsPT12Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[1],0))", 1, 1);

  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[1]",    true)->plot(true),"TightMuonsCONENDR0TO0812Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[1],0))",        true)->plot(true),"TightMuonsPTREL12Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsPT12Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsETA12Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsJETNOOFCONST12Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsCONENDR04TO0812Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsCONESUMETDR04TO0812Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[1],0))",        true)->plot(true),"TightMuonsPT12Fake.root");

  //
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 3,3);
  assembler->setRange("NGOODMUONS", 1, 1);
  assembler->setRange("NGOODELECTRONS", 2, 2);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[1],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[1],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      0, 0);

  // va = "(Alt$("+*s+"GOODMUONS[0],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[0]",    true)->plot(true),"LooseMuonsCONENDR0TO0802Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPTREL02Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPT02Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsETA02Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsJETNOOFCONST02Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08GOODMUONS[0],0))",        true)->plot(true),"LooseMuonsCONENDR04TO0802Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08GOODMUONS[0],0))",        true)->plot(true),"LooseMuonsCONESUMETDR04TO0802Fake.root");
  // // SaveHistograms(assembler->project("(Alt$(PTGOODMUONS[0],0))",        true)->plot(true),"LooseMuonsPT02Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  SaveHistograms(assembler->project("CONENDR0TO08GOODMUONS[0]",    true)->plot(true),"TightMuonsCONENDR0TO0802Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODMUONS[0],0))",        true)->plot(true),"TightMuonsPTREL02Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsPT02Fake.root");  
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsETA02Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsJETNOOFCONST02Fake.root");    

  SaveHistograms(assembler->project("(Alt$(CONENDR04TO08TIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsCONENDR04TO0802Fake.root");  
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR04TO08TIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsCONESUMETDR04TO0802Fake.root");  
  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXMUONS[0],0))",        true)->plot(true),"TightMuonsPT02Fake.root");  

  /////////////////////
  ////Electron/////////
  /////////////////////



  // 1L   
  assembler->setRange();    
  assembler->setRange("NBOSONS", 1);
  assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("SelVV_PTGOODELECTRONS0.pdf");
  assembler->setRange("NLEPTONS", 1,1);
  assembler->setRange("NGOODELECTRONS", 1, 1);
  //assembler->project("test", true)->plot(true)->SaveAs("All_testGOODELECTRONS0.pdf");

  assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel1Mu_PTGOODELECTRONS0.pdf");
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      0, 0);
  assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel1MuPrompt_PTGOODELECTRONS0.pdf");
      
  // TString va = "(Alt$("+*s+"GOODELECTRONS[0],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[0]",    true)->plot(true),"LooseElectronsCONENDR0TO0700Fake.root");  
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPTREL00Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPT00Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsETA00Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsJETNOOFCONST00Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsCONENDR03TO0700Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsCONESUMETDR03TO0700Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPT00Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))", true)->plot(true)->SaveAs("Sel1Mu_PTTIGHTMATRIXELECTRONS0.pdf");
  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[0]",    true)->plot(true),"TightElectronsCONENDR0TO0700Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[0],0))",        true)->plot(true),"TightElectronsPTREL00Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsPT00Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsETA00Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsJETNOOFCONST00Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsCONENDR03TO0700Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsCONESUMETDR03TO0700Fake.root");

  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsPT00Fake.root");

    
  // ///2L

  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 2,2);
  assembler->setRange("NGOODELECTRONS", 1, 1);
  assembler->setRange("NGOODMUONS", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      0, 0);
  // va = "(Alt$("+*s+"GOODELECTRONS[0],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);
  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[0]",    true)->plot(true),"LooseElectronsCONENDR0TO0701Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPTREL01Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPT01Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsETA01Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsJETNOOFCONST01Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsCONENDR03TO0701Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsCONESUMETDR03TO0701Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[0]",    true)->plot(true),"TightElectronsCONENDR0TO0701Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[0],0))",        true)->plot(true),"TightElectronsPTREL01Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsPT01Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsETA01Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsJETNOOFCONST01Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsCONENDR03TO0701Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsCONESUMETDR03TO0701Fake.root");

  
  //
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 2,2);
  assembler->setRange("NGOODELECTRONS", 2, 2);  
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[1],0))",      0, 0);

  // va = "(Alt$("+*s+"GOODELECTRONS[1],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[1]",    true)->plot(true),"LooseElectronsCONENDR0TO0711Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsPTREL11Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsPT11Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsETA11Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsJETNOOFCONST11Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsCONENDR03TO0711Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsCONESUMETDR03TO0711Fake.root");


  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[1],0))", 1, 1);

  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[1]",    true)->plot(true),"TightElectronsCONENDR0TO0711Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[1],0))",        true)->plot(true),"TightElectronsPTREL11Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsPT11Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsETA11Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsJETNOOFCONST11Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsCONENDR03TO0711Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsCONESUMETDR03TO0711Fake.root");

  
  //3L
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 3,3);
  assembler->setRange("NGOODELECTRONS", 3, 3);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[1],0))",      1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[2],0))",      0, 0);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[1],0))", 1, 1);  
  // va = "(Alt$("+*s+"GOODELECTRONS[2],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);
  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[2]",    true)->plot(true),"LooseElectronsCONENDR0TO0722Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[2],0))",        true)->plot(true),"LooseElectronsPTREL22Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[2],0))",        true)->plot(true),"LooseElectronsPT22Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODELECTRONS[2],0))",        true)->plot(true),"LooseElectronsETA22Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[2],0))",        true)->plot(true),"LooseElectronsJETNOOFCONST22Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[2],0))",        true)->plot(true),"LooseElectronsCONENDR03TO0722Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[2],0))",        true)->plot(true),"LooseElectronsCONESUMETDR03TO0722Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[2],0))",        true)->plot(true),"LooseElectronsPT22Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[2],0))", 1, 1);

  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[2]",    true)->plot(true),"TightElectronsCONENDR0TO0722Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[2],0))",        true)->plot(true),"TightElectronsPTREL22Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[2],0))",        true)->plot(true),"TightElectronsPT22Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXELECTRONS[2],0))",        true)->plot(true),"TightElectronsETA22Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[2],0))",        true)->plot(true),"TightElectronsJETNOOFCONST22Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[2],0))",        true)->plot(true),"TightElectronsCONENDR03TO0722Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[2],0))",        true)->plot(true),"TightElectronsCONESUMETDR03TO0722Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[2],0))",        true)->plot(true),"TightElectronsPT22Fake.root");

  //
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 3,3);
  assembler->setRange("NGOODELECTRONS", 2, 2);
  assembler->setRange("NGOODMUONS", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[1],0))",      0, 0);

  // va = "(Alt$("+*s+"GOODELECTRONS[1],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[1]",    true)->plot(true),"LooseElectronsCONENDR0TO0712Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsPTREL12Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsPT12Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsETA12Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsJETNOOFCONST12Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsCONENDR03TO0712Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsCONESUMETDR03TO0712Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[1],0))",        true)->plot(true),"LooseElectronsPT12Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[1],0))", 1, 1);

  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[1]",    true)->plot(true),"TightElectronsCONENDR0TO0712Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[1],0))",        true)->plot(true),"TightElectronsPTREL12Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsPT12Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsETA12Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsJETNOOFCONST12Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsCONENDR03TO0712Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsCONESUMETDR03TO0712Fake.root");
  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[1],0))",        true)->plot(true),"TightElectronsPT12Fake.root");

  //
  assembler->setRange();  
  assembler->setRange("NBOSONS", 1);
  assembler->setRange("NLEPTONS", 3,3);
  assembler->setRange("NGOODELECTRONS", 1, 1);
  assembler->setRange("NGOODMUONS", 2, 2);
  assembler->setRange("(Alt$(ISPROMPTMUON[0],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[0],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTMUON[1],0))",      1, 1);
  assembler->setRange("(Alt$(ISTIGHTMATRIXMUON[1],0))", 1, 1);
  assembler->setRange("(Alt$(ISPROMPTELECTRON[0],0))",      0, 0);

  // va = "(Alt$("+*s+"GOODELECTRONS[0],0))";
  // assembler->setRange(va,bin_low.at(bin_iter), bin_high.at(bin_iter),false);

  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[0]",    true)->plot(true),"LooseElectronsCONENDR0TO0702Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPTREL02Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPT02Fake.root");
  SaveHistograms(assembler->project("(Alt$(ETAGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsETA02Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsJETNOOFCONST02Fake.root");

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07GOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsCONENDR03TO0702Fake.root");
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07GOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsCONESUMETDR03TO0702Fake.root");
  // // SaveHistograms(assembler->project("(Alt$(PTGOODELECTRONS[0],0))",        true)->plot(true),"LooseElectronsPT02Fake.root");

  assembler->setRange("(Alt$(ISTIGHTMATRIXELECTRON[0],0))", 1, 1);
  SaveHistograms(assembler->project("CONENDR0TO07GOODELECTRONS[0]",    true)->plot(true),"TightElectronsCONENDR0TO0702Fake.root");
  SaveHistograms(assembler->project("(Alt$(PTRELGOODELECTRONS[0],0))",        true)->plot(true),"TightElectronsPTREL02Fake.root");

  SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsPT02Fake.root");  
  SaveHistograms(assembler->project("(Alt$(ETATIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsETA02Fake.root");
  SaveHistograms(assembler->project("(Alt$(JETNOOFCONSTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsJETNOOFCONST02Fake.root");    

  SaveHistograms(assembler->project("(Alt$(CONENDR03TO07TIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsCONENDR03TO0702Fake.root");  
  SaveHistograms(assembler->project("(Alt$(CONESUMETDR03TO07TIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsCONESUMETDR03TO0702Fake.root");  
  // SaveHistograms(assembler->project("(Alt$(PTTIGHTMATRIXELECTRONS[0],0))",        true)->plot(true),"TightElectronsPT02Fake.root");  


  
  assembler->setRange();  
  delete assembler;
  //    }
}
