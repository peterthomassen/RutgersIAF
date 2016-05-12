#include <sys/stat.h>
#include <unistd.h>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/ChannelCollection.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

#include "helperAnalysisPresenterMM.C"

void selectionPlotterMM() {
  ///////////////////////
  // Binning/selection //
  ///////////////////////
  
  // Specify axes and bins of multidimensional histogram
  
  std::string varexp = "NLEPTONS{0,10,10}:NGOODMUONS{0,10}:NGOODELECTRONS{0,10}:NGOODTAUS{0,10}:NLIGHTLEPTONS{0,10}:NGOODJETS{0,10}";
  varexp += ":HT{0,1000,10}";
  varexp += ":HTLA{0,1000,10}";
  varexp += ":LT{0,1000,10}";
  varexp += ":LTLA{0,1000,10}";
  varexp += ":MET{0,300,30}";
  //varexp += ":1mPT{0,200,40}";//test only
  //
  varexp += ":(Alt$(PTGOODMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODMUONS[1],0)){0,200,40}";
  varexp += ":(Alt$(PTGOODMUONS[2],0)){0,200,40}";
  varexp += ":(Alt$(ETAGOODMUONS[0],-3)){-3,3,20}";
  varexp += ":(Alt$(ETAGOODMUONS[1],-3)){-3,3,20}";
  varexp += ":(Alt$(ETAGOODMUONS[2],-3)){-3,3,20}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[0],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[1],0)){-1,2}";
  varexp += ":(Alt$(ISTIGHTMATRIXMUON[2],0)){-1,2}";
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[0],0)){0,200,40}";
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[1],0)){0,200,40}";  
  varexp += ":(Alt$(PTTIGHTMATRIXMUONS[2],0)){0,200,40}";
  varexp += ":(Alt$(ISPROMPTMUON[0],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[1],0)){-1,2}";
  varexp += ":(Alt$(ISPROMPTMUON[2],0)){-1,2}";
  //
  //varexp += ":nTTT{2,0,2}";
  varexp += ":LeptonTypeVal3DLA{0,400}";
  /*
  varexp += ":tripleFakeBckg";
  varexp += ":doubleFakeBckg";
  varexp += ":singleFakeBckg";
  varexp += ":fakeBckg";
  varexp += ":promptBckg";
  */
  //
  /*
  varexp += ":PTGOODMUONS[0]";
  varexp += ":PTGOODMUONS[1]";
  varexp += ":PTGOODMUONS[2]";
  varexp += ":JETCHMULTGOODMUONS[0]";
  varexp += ":JETCHMULTGOODMUONS[1]";
  varexp += ":JETCHMULTGOODMUONS[2]";
  varexp += ":ISTIGHTMATRIXMUON[0]";
  varexp += ":ISTIGHTMATRIXMUON[1]";
  varexp += ":ISTIGHTMATRIXMUON[2]";
  //
  varexp += ":PTGOODELECTRONS[0]";
  varexp += ":PTGOODELECTRONS[1]";
  varexp += ":PTGOODELECTRONS[2]";
  varexp += ":JETCHMULTGOODELECTRONS[0]";
  varexp += ":JETCHMULTGOODELECTRONS[1]";
  varexp += ":JETCHMULTGOODELECTRONS[2]";
  varexp += ":ISTIGHTMATRIXELECTRON[0]";
  varexp += ":ISTIGHTMATRIXELECTRON[1]";
  varexp += ":ISTIGHTMATRIXELECTRON[2]";
*/

  // Configuration Params
  std::string dirname="selectionPlotterMMv5";
  bool isTagNprobeLike = false;

  // Global cuts, if desired
  TString selection = "1";
  //selection +="&&NGOODMUONS>=3";
  //selection +="&&LeptonTypeVal3DLA==222";
  //selection +="&&NGOODJETS>3";
  
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
  mkdir(dirname.c_str(), 0755);
  chdir(dirname.c_str());
  
  // Check for duplicate events
  // ---  
  /*
  // Matrix Weight calculations:
  //-------------------------------------------
  for( int i=1; i<=3; i++){ // Loop over MUONS
    //---------------
    //Pt bins
    treeR->SetAlias(TString::Format("%dmPT0",i),                       TString::Format("(PTGOODMUONS[%d]< 10)"    ,i-1));//not used
    treeR->SetAlias(TString::Format("%dmPT1",i),TString::Format("(PTGOODMUONS[%d]>= 10)*(PTGOODMUONS[%d]< 20)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dmPT2",i),TString::Format("(PTGOODMUONS[%d]>= 20)*(PTGOODMUONS[%d]< 30)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dmPT3",i),TString::Format("(PTGOODMUONS[%d]>= 30)*(PTGOODMUONS[%d]< 50)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dmPT4",i),TString::Format("(PTGOODMUONS[%d]>= 50)*(PTGOODMUONS[%d]< 75)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dmPT5",i),TString::Format("(PTGOODMUONS[%d]>= 75)*(PTGOODMUONS[%d]<100)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dmPT6",i),TString::Format("(PTGOODMUONS[%d]>=100)"                          ,i-1));
    //---------------
    //Aux bins
    treeR->SetAlias(TString::Format("%dmAUX1",i),TString::Format("(JETCHMULTGOODMUONS[%d]<8.5)",i-1));
    treeR->SetAlias(TString::Format("%dmAUX2",i),TString::Format("(JETCHMULTGOODMUONS[%d]>8.5)",i-1));
    //---------------
    //Low CHMULT pt fake rates
    treeR->SetAlias(TString::Format("%dmfPT11",i),TString::Format("%dmPT1*%dmAUX1*0.10",i,i));
    treeR->SetAlias(TString::Format("%dmfPT21",i),TString::Format("%dmPT2*%dmAUX1*0.15",i,i));
    treeR->SetAlias(TString::Format("%dmfPT31",i),TString::Format("%dmPT3*%dmAUX1*0.18",i,i));
    treeR->SetAlias(TString::Format("%dmfPT41",i),TString::Format("%dmPT4*%dmAUX1*0.20",i,i));
    treeR->SetAlias(TString::Format("%dmfPT51",i),TString::Format("%dmPT5*%dmAUX1*0.25",i,i));
    treeR->SetAlias(TString::Format("%dmfPT61",i),TString::Format("%dmPT6*%dmAUX1*0.27",i,i));
    treeR->SetAlias(TString::Format("%dmf1",i),   TString::Format("%dmfPT11+%dmfPT21+%dmfPT31+%dmfPT41+%dmfPT51+%dmfPT61",i,i,i,i,i,i));// imf1
    //---------------
    //High CHMULT pt fake rates
    treeR->SetAlias(TString::Format("%dmfPT12",i),TString::Format("%dmPT1*%dmAUX2*0.012",i,i));
    treeR->SetAlias(TString::Format("%dmfPT22",i),TString::Format("%dmPT2*%dmAUX2*0.012",i,i));
    treeR->SetAlias(TString::Format("%dmfPT32",i),TString::Format("%dmPT3*%dmAUX2*0.022",i,i));
    treeR->SetAlias(TString::Format("%dmfPT42",i),TString::Format("%dmPT4*%dmAUX2*0.028",i,i));
    treeR->SetAlias(TString::Format("%dmfPT52",i),TString::Format("%dmPT5*%dmAUX2*0.032",i,i));
    treeR->SetAlias(TString::Format("%dmfPT62",i),TString::Format("%dmPT6*%dmAUX2*0.065",i,i));
    treeR->SetAlias(TString::Format("%dmf2",i),   TString::Format("%dmfPT12+%dmfPT22+%dmfPT32+%dmfPT42+%dmfPT52+%dmfPT62",i,i,i,i,i,i));// imf2
    //---------------
    //muon fake rate:
    treeR->SetAlias(TString::Format("%dmf",i),TString::Format("%dmf1+%dmf2",i,i));// imf
    //---------------
    //Pt bins - SAME AS FAKES
    //---------------
    //Aux bins - NONE
    //---------------
    //pt prompt rates
    treeR->SetAlias(TString::Format("%dmpPT1",i),TString::Format("%dmPT1*0.85",i));
    treeR->SetAlias(TString::Format("%dmpPT2",i),TString::Format("%dmPT2*0.92",i));
    treeR->SetAlias(TString::Format("%dmpPT3",i),TString::Format("%dmPT3*0.95",i));
    treeR->SetAlias(TString::Format("%dmpPT4",i),TString::Format("%dmPT4*0.97",i));
    treeR->SetAlias(TString::Format("%dmpPT5",i),TString::Format("%dmPT5*0.98",i));
    treeR->SetAlias(TString::Format("%dmpPT6",i),TString::Format("%dmPT6*0.98",i));
    treeR->SetAlias(TString::Format("%dmp",i),   TString::Format("%dmpPT1+%dmpPT2+%dmpPT3+%dmpPT4+%dmpPT5+%dmpPT6",i,i,i,i,i,i));// imp
    //---------------
  }
  //-------------------------------------------
  for( int i=1; i<=3; i++){ // Loop over ELECTRONS
    //---------------
    //Pt bins
    treeR->SetAlias(TString::Format("%dePT0",i),                           TString::Format("(PTGOODELECTRONS[%d]< 10)"    ,i-1));//not used
    treeR->SetAlias(TString::Format("%dePT1",i),TString::Format("(PTGOODELECTRONS[%d]>= 10)*(PTGOODELECTRONS[%d]< 20)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dePT2",i),TString::Format("(PTGOODELECTRONS[%d]>= 20)*(PTGOODELECTRONS[%d]< 30)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dePT3",i),TString::Format("(PTGOODELECTRONS[%d]>= 30)*(PTGOODELECTRONS[%d]< 50)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dePT4",i),TString::Format("(PTGOODELECTRONS[%d]>= 50)*(PTGOODELECTRONS[%d]< 75)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dePT5",i),TString::Format("(PTGOODELECTRONS[%d]>= 75)*(PTGOODELECTRONS[%d]<100)",i-1,i-1));
    treeR->SetAlias(TString::Format("%dePT6",i),TString::Format("(PTGOODELECTRONS[%d]>=100)"                          ,i-1));
    //---------------
    //Aux bins
    treeR->SetAlias(TString::Format("%deAUX1",i),TString::Format("(JETCHMULTGOODELECTRONS[%d]<8.5)",i-1));
    treeR->SetAlias(TString::Format("%deAUX2",i),TString::Format("(JETCHMULTGOODELECTRONS[%d]>8.5)",i-1));
    //---------------
    //Low CHMULT pt fake rates
    treeR->SetAlias(TString::Format("%defPT11",i),TString::Format("%dePT1*%deAUX1*0.10",i,i));
    treeR->SetAlias(TString::Format("%defPT21",i),TString::Format("%dePT2*%deAUX1*0.15",i,i));
    treeR->SetAlias(TString::Format("%defPT31",i),TString::Format("%dePT3*%deAUX1*0.18",i,i));
    treeR->SetAlias(TString::Format("%defPT41",i),TString::Format("%dePT4*%deAUX1*0.20",i,i));
    treeR->SetAlias(TString::Format("%defPT51",i),TString::Format("%dePT5*%deAUX1*0.25",i,i));
    treeR->SetAlias(TString::Format("%defPT61",i),TString::Format("%dePT6*%deAUX1*0.27",i,i));
    treeR->SetAlias(TString::Format("%def1",i),   TString::Format("%defPT11+%defPT21+%defPT31+%defPT41+%defPT51+%defPT61",i,i,i,i,i,i));// ief1
    //---------------
    //High CHMULT pt fake rates
    treeR->SetAlias(TString::Format("%defPT12",i),TString::Format("%dePT1*%deAUX2*0.012",i,i));
    treeR->SetAlias(TString::Format("%defPT22",i),TString::Format("%dePT2*%deAUX2*0.012",i,i));
    treeR->SetAlias(TString::Format("%defPT32",i),TString::Format("%dePT3*%deAUX2*0.022",i,i));
    treeR->SetAlias(TString::Format("%defPT42",i),TString::Format("%dePT4*%deAUX2*0.028",i,i));
    treeR->SetAlias(TString::Format("%defPT52",i),TString::Format("%dePT5*%deAUX2*0.032",i,i));
    treeR->SetAlias(TString::Format("%defPT62",i),TString::Format("%dePT6*%deAUX2*0.065",i,i));
    treeR->SetAlias(TString::Format("%def2",i),   TString::Format("%defPT12+%defPT22+%defPT32+%defPT42+%defPT52+%defPT62",i,i,i,i,i,i));// ief2
    //---------------
    //electron fake rate:
    treeR->SetAlias(TString::Format("%def",i),TString::Format("%def1+%def2",i,i));// imf
    //---------------
    //Pt bins - SAME AS FAKES
    //---------------
    //Aux bins - NONE
    //---------------
    //pt prompt rates
    treeR->SetAlias(TString::Format("%depPT1",i),TString::Format("%dePT1*0.85",i));
    treeR->SetAlias(TString::Format("%depPT2",i),TString::Format("%dePT2*0.92",i));
    treeR->SetAlias(TString::Format("%depPT3",i),TString::Format("%dePT3*0.95",i));
    treeR->SetAlias(TString::Format("%depPT4",i),TString::Format("%dePT4*0.97",i));
    treeR->SetAlias(TString::Format("%depPT5",i),TString::Format("%dePT5*0.98",i));
    treeR->SetAlias(TString::Format("%depPT6",i),TString::Format("%dePT6*0.98",i));
    treeR->SetAlias(TString::Format("%dep",i),   TString::Format("%depPT1+%depPT2+%depPT3+%depPT4+%depPT5+%depPT6",i,i,i,i,i,i));// iep
    //---------------
  }
  //-------------------------------------------
  // Check what the lepton types are: 
  treeR->SetAlias("is1Mu",  "((LeptonTypeVal3DLA-LeptonTypeVal3DLA%100)/100)==2");
  treeR->SetAlias("is2Mu","((LeptonTypeVal3DLA%100-LeptonTypeVal3DLA%10)/10)==2");
  treeR->SetAlias("is3Mu",                           "(LeptonTypeVal3DLA%10)==2");
  treeR->SetAlias("is1El",  "((LeptonTypeVal3DLA-LeptonTypeVal3DLA%100)/100)==1");
  treeR->SetAlias("is2El","((LeptonTypeVal3DLA%100-LeptonTypeVal3DLA%10)/10)==1");
  treeR->SetAlias("is3El",                           "(LeptonTypeVal3DLA%10)==1");
  //-------------------------------------------
  // Set prompt/fake rates:
  treeR->SetAlias("f1","is1Mu*Alt$(1mf,0)+is1El*Alt$(1ef,0)");
  treeR->SetAlias("f2","is2Mu*Alt$(2mf,0)+is2El*Alt$(2ef,0)");
  treeR->SetAlias("f3","is3Mu*Alt$(3mf,0)+is3El*Alt$(3ef,0)");
  treeR->SetAlias("p1","is1Mu*Alt$(1mp,0)+is1El*Alt$(1ep,0)");
  treeR->SetAlias("p2","is2Mu*Alt$(2mp,0)+is2El*Alt$(2ep,0)");
  treeR->SetAlias("p3","is3Mu*Alt$(3mp,0)+is3El*Alt$(3ep,0)");
  //-------------------------------------------
  // Temporary fix: 
  //   waiting for https://gitlab.com/Thomassen/RutgersIAF/commit/a7383de85af3d5582fb8a5e79ebfbc34878519d5
  for( int i=1; i<=3; i++){
    treeR->SetAlias(TString::Format("m%dTight",i),TString::Format("Alt$(ISTIGHTMATRIXMUON[%d],0)",    i-1));
    treeR->SetAlias(TString::Format("e%dTight",i),TString::Format("Alt$(ISTIGHTMATRIXELECTRON[%d],0)",i-1));
  }
  //---------------
  treeR->SetAlias("nTTT","nTTT3DLA");// Name change:
  treeR->SetAlias("nTTL","nTTL3DLA");
  treeR->SetAlias("nTLT","nTLT3DLA");
  treeR->SetAlias("nLTT","nLTT3DLA");
  treeR->SetAlias("nTLL","nTLL3DLA");
  treeR->SetAlias("nLTL","nLTL3DLA");
  treeR->SetAlias("nLLT","nLLT3DLA");
  treeR->SetAlias("nLLL","nLLL3DLA");
  //---------------
  // If first and third matrix leptons are not tight, and the second matrix lepton is tight, manually set nLTL=1
  treeR->SetAlias("nLTL","(m1Tight+e1Tight+m3Tight+e3Tight==0)*(m2Tight+e2Tight>0)");
  //---------------
  // sanity check:
  treeR->SetAlias("nSum","nTTT+nTTL+nTLT+nLTT+nTLL+nLTL+nLLT+nLLL");
  //-------------------------------------------
  // Weights: 
  treeR->SetAlias("wfff","(f1*f2*f3) * ((-(nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3)) - nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) - nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 - nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 - nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p1 + p2 - p1*p2)*pow(f3 - p3,3)*p3 + nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p1 + p3 - p1*p3) + nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p2 + p3 - p2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("wffp","(f1*f2*p3) * ((f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("wfpf","(f1*f3*p2) * ((f2*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("wpff","(f2*f3*p1) * ((f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + f1*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + f1*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + (-1 + f1)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + f1*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + (-1 + f1)*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("wfpp","(f1*p2*p3) * ((-(f2*f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)) - f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("wpfp","(f2*p1*p3) * ((-(f1*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)) - f1*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - f1*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - f1*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("wppf","(f3*p1*p2) * ((-(f1*f2*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3)) - (-1 + f1)*(-1 + f2)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) - f1*f2*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - f1*(-1 + f2)*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - (-1 + f1)*f2*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f1 + f2 - f1*f2)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f1 + p3 - f1*p3) + f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f2 + p3 - f2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("wppp","(p1*p2*p3) * ((f1*f2*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //---------------
  treeR->SetAlias("promptBckg",     "wppp");
  treeR->SetAlias("singleFakeBckg", "wfpp+wpfp+wppf");
  treeR->SetAlias("doubleFakeBckg", "wffp+wfpf+wpff");
  treeR->SetAlias("tripleFakeBckg", "wfff");
  treeR->SetAlias("fakeBckg",       "wfff+wffp+wfpf+wpff+wfpp+wpfp+wppf");
  //-------------------------------------------
  */

  //all
  assembler->setRange();
  assembler->setRange("NGOODMUONS", 3);
  assembler->setRange("LeptonTypeVal3DLA", 222,222);
  //assembler->setRange("nTTT", 1);
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
  //assembler->project("1mPT", true)->plot(true)->SaveAs("All_1mPT.pdf");
  assembler->project("(Alt$(PTGOODMUONS[0],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS1.pdf");
  assembler->project("(Alt$(PTGOODMUONS[1],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS2.pdf");
  assembler->project("(Alt$(PTGOODMUONS[2],0))", true)->plot(true)->SaveAs("All_PTGOODMUONS3.pdf");
  assembler->project("(Alt$(ETAGOODMUONS[0],-3))", true)->plot(true)->SaveAs("All_ETAGOODMUONS1.pdf");
  assembler->project("(Alt$(ETAGOODMUONS[1],-3))", true)->plot(true)->SaveAs("All_ETAGOODMUONS2.pdf");
  assembler->project("(Alt$(ETAGOODMUONS[2],-3))", true)->plot(true)->SaveAs("All_ETAGOODMUONS3.pdf");
  //assembler->project("(Alt$(PTGOODELECTRONS[0],0))", true)->plot(true)->SaveAs("All_PTGOODELECTRONS1.pdf");
  //assembler->project("(Alt$(PTGOODELECTRONS[1],0))", true)->plot(true)->SaveAs("All_PTGOODELECTRONS2.pdf");

  /*
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
  */
  

  assembler->setRange();  
  delete assembler;
}
