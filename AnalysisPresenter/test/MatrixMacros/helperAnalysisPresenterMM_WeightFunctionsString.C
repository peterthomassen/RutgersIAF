#include <iostream>
#include <TH1.h>
#include <boost/algorithm/string.hpp>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"


void addMatrix(PhysicsContribution* contribution) {


  // Check what the lepton types are:
  contribution->setAlias("is1Mu","((LeptonTypeVal3DLA-LeptonTypeVal3DLA%100)/100)==2");
  contribution->setAlias("is2Mu","((LeptonTypeVal3DLA%100-LeptonTypeVal3DLA%10)/10)==2");
  contribution->setAlias("is3Mu","(LeptonTypeVal3DLA%10)==2");
  contribution->setAlias("is1El","((LeptonTypeVal3DLA-LeptonTypeVal3DLA%100)/100)==1");
  contribution->setAlias("is2El","((LeptonTypeVal3DLA%100-LeptonTypeVal3DLA%10)/10)==1");
  contribution->setAlias("is3El","(LeptonTypeVal3DLA%10)==1");

  // Count number of GOODMUONS and GOODELECTRONS to be read in:
  contribution->setAlias("nMuMM","is1Mu+is2Mu+is3Mu");
  contribution->setAlias("nElMM","is1El+is2El+is3El");

  for( int i=1; i<=3; i++){
    //Lepton = Muon - Valid for RutgersIAF 76X_v2.1 or higher.
    //Pt bins
    contribution->setAlias(TString::Format("%dmPT0",i),                       TString::Format("(PTGOODMUONS[%d]< 10)"    ,i-1));//not used
    contribution->setAlias(TString::Format("%dmPT1",i),TString::Format("(PTGOODMUONS[%d]>= 10)*(PTGOODMUONS[%d]< 20)",i-1,i-1));
    contribution->setAlias(TString::Format("%dmPT2",i),TString::Format("(PTGOODMUONS[%d]>= 20)*(PTGOODMUONS[%d]< 30)",i-1,i-1));
    contribution->setAlias(TString::Format("%dmPT3",i),TString::Format("(PTGOODMUONS[%d]>= 30)*(PTGOODMUONS[%d]< 50)",i-1,i-1));
    contribution->setAlias(TString::Format("%dmPT4",i),TString::Format("(PTGOODMUONS[%d]>= 50)*(PTGOODMUONS[%d]< 75)",i-1,i-1));
    contribution->setAlias(TString::Format("%dmPT5",i),TString::Format("(PTGOODMUONS[%d]>=75)*(PTGOODMUONS[%d]<100)",i-1,i-1));
    contribution->setAlias(TString::Format("%dmPT6",i),TString::Format("(PTGOODMUONS[%d]>=100)",i-1));
    //---------------
    //Aux bins
    contribution->setAlias(TString::Format("%dmAUX1",i),TString::Format("(JETCHMULTGOODMUONS[%d]<8.5)",i-1));
    contribution->setAlias(TString::Format("%dmAUX2",i),TString::Format("(JETCHMULTGOODMUONS[%d]>8.5)",i-1));
    //---------------
    //Low CHMULT pt fake rates
    //contribution->setAlias(TString::Format("%dmfPT11",i),TString::Format("%dmPT1*%dmAUX1*0.10",i,i)); // mean rates
    //contribution->setAlias(TString::Format("%dmfPT21",i),TString::Format("%dmPT2*%dmAUX1*0.15",i,i));
    //contribution->setAlias(TString::Format("%dmfPT31",i),TString::Format("%dmPT3*%dmAUX1*0.18",i,i));
    //contribution->setAlias(TString::Format("%dmfPT41",i),TString::Format("%dmPT4*%dmAUX1*0.20",i,i));
    //contribution->setAlias(TString::Format("%dmfPT51",i),TString::Format("%dmPT5*%dmAUX1*0.25",i,i));
    //contribution->setAlias(TString::Format("%dmfPT61",i),TString::Format("%dmPT6*%dmAUX1*0.27",i,i));
    contribution->setAlias(TString::Format("%dmfPT11",i),TString::Format("%dmPT1*%dmAUX1*0.06",i,i)); // ttbar rates
    contribution->setAlias(TString::Format("%dmfPT21",i),TString::Format("%dmPT2*%dmAUX1*0.075",i,i));
    contribution->setAlias(TString::Format("%dmfPT31",i),TString::Format("%dmPT3*%dmAUX1*0.10",i,i));
    contribution->setAlias(TString::Format("%dmfPT41",i),TString::Format("%dmPT4*%dmAUX1*0.15",i,i));
    contribution->setAlias(TString::Format("%dmfPT51",i),TString::Format("%dmPT5*%dmAUX1*0.20",i,i));
    contribution->setAlias(TString::Format("%dmfPT61",i),TString::Format("%dmPT6*%dmAUX1*0.23",i,i));
    contribution->setAlias(TString::Format("%dmf1",   i),TString::Format("%dmfPT11+%dmfPT21+%dmfPT31+%dmfPT41+%dmfPT51+%dmfPT61",i,i,i,i,i,i));
    //---------------
    //High CHMULT pt fake rates
    //contribution->setAlias(TString::Format("%dmfPT12",i),TString::Format("%dmPT1*%dmAUX2*0.012",i,i)); // mean rates
    //contribution->setAlias(TString::Format("%dmfPT22",i),TString::Format("%dmPT2*%dmAUX2*0.012",i,i));
    //contribution->setAlias(TString::Format("%dmfPT32",i),TString::Format("%dmPT3*%dmAUX2*0.022",i,i));
    //contribution->setAlias(TString::Format("%dmfPT42",i),TString::Format("%dmPT4*%dmAUX2*0.028",i,i));
    //contribution->setAlias(TString::Format("%dmfPT52",i),TString::Format("%dmPT5*%dmAUX2*0.032",i,i));
    //contribution->setAlias(TString::Format("%dmfPT62",i),TString::Format("%dmPT6*%dmAUX2*0.065",i,i));
    contribution->setAlias(TString::Format("%dmfPT12",i),TString::Format("%dmPT1*%dmAUX2*0.006",i,i)); // ttbar rates
    contribution->setAlias(TString::Format("%dmfPT22",i),TString::Format("%dmPT2*%dmAUX2*0.008",i,i));
    contribution->setAlias(TString::Format("%dmfPT32",i),TString::Format("%dmPT3*%dmAUX2*0.018",i,i));
    contribution->setAlias(TString::Format("%dmfPT42",i),TString::Format("%dmPT4*%dmAUX2*0.030",i,i));
    contribution->setAlias(TString::Format("%dmfPT52",i),TString::Format("%dmPT5*%dmAUX2*0.043",i,i));
    contribution->setAlias(TString::Format("%dmfPT62",i),TString::Format("%dmPT6*%dmAUX2*0.050",i,i));
    contribution->setAlias(TString::Format("%dmf2",i),   TString::Format("%dmfPT12+%dmfPT22+%dmfPT32+%dmfPT42+%dmfPT52+%dmfPT62",i,i,i,i,i,i));
    //---------------
    //Eta bin corrections (fudge factors)
    contribution->setAlias(TString::Format("%dmETA1",i),TString::Format("(abs(ETAGOODMUONS[%d])<=1.1)*0.9"                                ,i-1));//barrel
    contribution->setAlias(TString::Format("%dmETA2",i),TString::Format("(abs(ETAGOODMUONS[%d])<=1.4)*(abs(ETAGOODMUONS[%d])>1.1)*1.0",i-1,i-1));//transition
    contribution->setAlias(TString::Format("%dmETA3",i),TString::Format("(abs(ETAGOODMUONS[%d])<=2.5)*(abs(ETAGOODMUONS[%d])>1.4)*1.2",i-1,i-1));//endcap
    //---------------
    //Muon fake rate:
    //contribution->setAlias(TString::Format("%dmf",i),TString::Format("%dmf1+%dmf2",i,i));
    contribution->setAlias(TString::Format("%dmf",i),TString::Format("((%dmf1+%dmf2)*%dmETA1)+((%dmf1+%dmf2)*%dmETA2)+((%dmf1+%dmf2)*%dmETA3)",i,i,i,i,i,i,i,i,i));
    //---------------
    //Pt bins - SAME AS FAKES
    //---------------
    //Aux bins - NONE
    //---------------
    //pt prompt rates
    contribution->setAlias(TString::Format("%dmpPT1",i),TString::Format("%dmPT1*0.85",i));
    contribution->setAlias(TString::Format("%dmpPT2",i),TString::Format("%dmPT2*0.92",i));
    contribution->setAlias(TString::Format("%dmpPT3",i),TString::Format("%dmPT3*0.95",i));
    contribution->setAlias(TString::Format("%dmpPT4",i),TString::Format("%dmPT4*0.97",i));
    contribution->setAlias(TString::Format("%dmpPT5",i),TString::Format("%dmPT5*0.98",i));
    contribution->setAlias(TString::Format("%dmpPT6",i),TString::Format("%dmPT6*0.98",i));
    //---------------
    //muon1 prompt rate:
    contribution->setAlias(TString::Format("%dmp",i),TString::Format("%dmpPT1+%dmpPT2+%dmpPT3+%dmpPT4+%dmpPT5+%dmpPT6",i,i,i,i,i,i));
    //---------------
    }

  for( int i=1; i<=3; i++){
    //Lepton = Electron - Valid for RutgersIAF 76X_v3.1 or higher (new electron IDs, Loose = Cut Veto ID w/out isolation, Tight = Cut Medium ID w isolation)
    //Pt bins
    contribution->setAlias(TString::Format("%dePT0",i),TString::Format(                           "(PTGOODELECTRONS[%d]< 10)",i-1    ));//not used
    contribution->setAlias(TString::Format("%dePT1",i),TString::Format("(PTGOODELECTRONS[%d]>= 10)*(PTGOODELECTRONS[%d]< 20)",i-1,i-1));
    contribution->setAlias(TString::Format("%dePT2",i),TString::Format("(PTGOODELECTRONS[%d]>= 20)*(PTGOODELECTRONS[%d]< 40)",i-1,i-1));
    contribution->setAlias(TString::Format("%dePT3",i),TString::Format("(PTGOODELECTRONS[%d]>= 40)*(PTGOODELECTRONS[%d]< 60)",i-1,i-1));
    contribution->setAlias(TString::Format("%dePT4",i),TString::Format("(PTGOODELECTRONS[%d]>= 60)*(PTGOODELECTRONS[%d]<100)",i-1,i-1));
    contribution->setAlias(TString::Format("%dePT5",i),TString::Format("(PTGOODELECTRONS[%d]>=100)",                          i-1    ));
    //---------------
    //Aux bins
    contribution->setAlias(TString::Format("%deAUX1",i),TString::Format("(JETNOOFCONSTGOODELECTRONS[%d]< 8.5)",                                     i-1    ));
    contribution->setAlias(TString::Format("%deAUX2",i),TString::Format("(JETNOOFCONSTGOODELECTRONS[%d]> 8.5)*(JETNOOFCONSTGOODELECTRONS[%d]<15.5)",i-1,i-1));
    contribution->setAlias(TString::Format("%deAUX3",i),TString::Format("(JETNOOFCONSTGOODELECTRONS[%d]>15.5)",                                     i-1    ));
    //---------------
    //Low NOOFCONST pt fake rates
    contribution->setAlias(TString::Format("%defPT11",i),TString::Format("%dePT1*%deAUX1*0.07",i,i));// ttbar rates
    contribution->setAlias(TString::Format("%defPT21",i),TString::Format("%dePT2*%deAUX1*0.10",i,i));
    contribution->setAlias(TString::Format("%defPT31",i),TString::Format("%dePT3*%deAUX1*0.10",i,i));
    contribution->setAlias(TString::Format("%defPT41",i),TString::Format("%dePT4*%deAUX1*0.12",i,i));
    contribution->setAlias(TString::Format("%defPT51",i),TString::Format("%dePT5*%deAUX1*0.15",i,i));
    contribution->setAlias(TString::Format("%def1",   i),TString::Format("%defPT11+%defPT21+%defPT31+%defPT41+%defPT51",i,i,i,i,i));
    //---------------
    //Medium NOOFCONST pt fake rates
    contribution->setAlias(TString::Format("%defPT12",i),TString::Format("%dePT1*%deAUX2*0.010",i,i));// ttbar rates
    contribution->setAlias(TString::Format("%defPT22",i),TString::Format("%dePT2*%deAUX2*0.016",i,i));
    contribution->setAlias(TString::Format("%defPT32",i),TString::Format("%dePT3*%deAUX2*0.028",i,i));
    contribution->setAlias(TString::Format("%defPT42",i),TString::Format("%dePT4*%deAUX2*0.048",i,i));
    contribution->setAlias(TString::Format("%defPT52",i),TString::Format("%dePT5*%deAUX2*0.075",i,i));
    contribution->setAlias(TString::Format("%def2",   i),TString::Format("%defPT12+%defPT22+%defPT32+%defPT42+%defPT52",i,i,i,i,i));
    //---------------
    //High NOOFCONST pt fake rates
    contribution->setAlias(TString::Format("%defPT13",i),TString::Format("%dePT1*%deAUX3*0.0027",i,i));// ttbar rates
    contribution->setAlias(TString::Format("%defPT23",i),TString::Format("%dePT2*%deAUX3*0.0006",i,i));
    contribution->setAlias(TString::Format("%defPT33",i),TString::Format("%dePT3*%deAUX3*0.0017",i,i));
    contribution->setAlias(TString::Format("%defPT43",i),TString::Format("%dePT4*%deAUX3*0.0030",i,i));
    contribution->setAlias(TString::Format("%defPT53",i),TString::Format("%dePT5*%deAUX3*0.0080",i,i));
    contribution->setAlias(TString::Format("%def3",   i),TString::Format("%defPT13+%defPT23+%defPT33+%defPT43+%defPT53",i,i,i,i,i));
    //---------------
    //electron1 fake rate:
    contribution->setAlias(TString::Format("%def",i),TString::Format("%def1+%def2+%def3",i,i,i));
    //---------------
    //Pt bins - SAME AS FAKES
    //---------------
    //Aux bins - NONE
    //---------------
    //pt prompt rates
    contribution->setAlias(TString::Format("%depPT1",i),TString::Format("%dePT1*0.50", i)); // mean values
    contribution->setAlias(TString::Format("%depPT2",i),TString::Format("%dePT2*0.725",i));
    contribution->setAlias(TString::Format("%depPT3",i),TString::Format("%dePT3*0.83", i));
    contribution->setAlias(TString::Format("%depPT4",i),TString::Format("%dePT4*0.88", i));
    contribution->setAlias(TString::Format("%depPT5",i),TString::Format("%dePT5*0.91", i));
    //---------------
    //electron1 prompt rate:
    contribution->setAlias(TString::Format("%dep",i),TString::Format("%depPT1+%depPT2+%depPT3+%depPT4+%depPT5",i,i,i,i,i));
    //---------------
  }

  
  // Set prompt/fake rates:
  //----------------------------------------------------------------------------------------
  contribution->setAlias("f1","Alt$(1mf,0)*(LeptonTypeVal3DLA==221)+Alt$(1mf,0)*(LeptonTypeVal3DLA==212)+Alt$(1ef,0)*(LeptonTypeVal3DLA==122)+Alt$(1ef,0)*(LeptonTypeVal3DLA==112)+Alt$(1ef,0)*(LeptonTypeVal3DLA==121)+Alt$(1mf,0)*(LeptonTypeVal3DLA==211)+Alt$(1mf,0)*(LeptonTypeVal3DLA==222)+Alt$(1ef,0)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("f2","Alt$(2mf,0)*(LeptonTypeVal3DLA==221)+Alt$(1ef,0)*(LeptonTypeVal3DLA==212)+Alt$(1mf,0)*(LeptonTypeVal3DLA==122)+Alt$(2ef,0)*(LeptonTypeVal3DLA==112)+Alt$(1mf,0)*(LeptonTypeVal3DLA==121)+Alt$(1ef,0)*(LeptonTypeVal3DLA==211)+Alt$(2mf,0)*(LeptonTypeVal3DLA==222)+Alt$(2ef,0)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("f3","Alt$(1ef,0)*(LeptonTypeVal3DLA==221)+Alt$(2mf,0)*(LeptonTypeVal3DLA==212)+Alt$(2mf,0)*(LeptonTypeVal3DLA==122)+Alt$(1mf,0)*(LeptonTypeVal3DLA==112)+Alt$(2ef,0)*(LeptonTypeVal3DLA==121)+Alt$(2ef,0)*(LeptonTypeVal3DLA==211)+Alt$(3mf,0)*(LeptonTypeVal3DLA==222)+Alt$(3ef,0)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("p1","Alt$(1mp,1)*(LeptonTypeVal3DLA==221)+Alt$(1mp,1)*(LeptonTypeVal3DLA==212)+Alt$(1ep,1)*(LeptonTypeVal3DLA==122)+Alt$(1ep,1)*(LeptonTypeVal3DLA==112)+Alt$(1ep,1)*(LeptonTypeVal3DLA==121)+Alt$(1mp,1)*(LeptonTypeVal3DLA==211)+Alt$(1mp,1)*(LeptonTypeVal3DLA==222)+Alt$(1ep,1)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("p2","Alt$(2mp,1)*(LeptonTypeVal3DLA==221)+Alt$(1ep,1)*(LeptonTypeVal3DLA==212)+Alt$(1mp,1)*(LeptonTypeVal3DLA==122)+Alt$(2ep,1)*(LeptonTypeVal3DLA==112)+Alt$(1mp,1)*(LeptonTypeVal3DLA==121)+Alt$(1ep,1)*(LeptonTypeVal3DLA==211)+Alt$(2mp,1)*(LeptonTypeVal3DLA==222)+Alt$(2ep,1)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("p3","Alt$(1ep,1)*(LeptonTypeVal3DLA==221)+Alt$(2mp,1)*(LeptonTypeVal3DLA==212)+Alt$(2mp,1)*(LeptonTypeVal3DLA==122)+Alt$(1mp,1)*(LeptonTypeVal3DLA==112)+Alt$(2ep,1)*(LeptonTypeVal3DLA==121)+Alt$(2ep,1)*(LeptonTypeVal3DLA==211)+Alt$(3mp,1)*(LeptonTypeVal3DLA==222)+Alt$(3ep,1)*(LeptonTypeVal3DLA==111)");
  //----------------------------------------------------------------------------------------
  // 3Mu or 3El
  /*  
  contribution->setAlias("f1","Alt$(1mf,0)*(LeptonTypeVal3DLA==222)+Alt$(1ef,0)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("f2","Alt$(2mf,0)*(LeptonTypeVal3DLA==222)+Alt$(2ef,0)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("f3","Alt$(3mf,0)*(LeptonTypeVal3DLA==222)+Alt$(3ef,0)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("p1","Alt$(1mp,1)*(LeptonTypeVal3DLA==222)+Alt$(1ep,1)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("p2","Alt$(2mp,1)*(LeptonTypeVal3DLA==222)+Alt$(2ep,1)*(LeptonTypeVal3DLA==111)");
  contribution->setAlias("p3","Alt$(3mp,1)*(LeptonTypeVal3DLA==222)+Alt$(3ep,1)*(LeptonTypeVal3DLA==111)");
  */
  //--------
  // El + 2Mu
  /*
  contribution->setAlias("f1","Alt$(1mf,0)*(LeptonTypeVal3DLA==221)+Alt$(1mf,0)*(LeptonTypeVal3DLA==212)+Alt$(1ef,0)*(LeptonTypeVal3DLA==122)");
  contribution->setAlias("f2","Alt$(2mf,0)*(LeptonTypeVal3DLA==221)+Alt$(1ef,0)*(LeptonTypeVal3DLA==212)+Alt$(1mf,0)*(LeptonTypeVal3DLA==122)");
  contribution->setAlias("f3","Alt$(1ef,0)*(LeptonTypeVal3DLA==221)+Alt$(2mf,0)*(LeptonTypeVal3DLA==212)+Alt$(2mf,0)*(LeptonTypeVal3DLA==122)");
  contribution->setAlias("p1","Alt$(1mp,1)*(LeptonTypeVal3DLA==221)+Alt$(1mp,1)*(LeptonTypeVal3DLA==212)+Alt$(1ep,1)*(LeptonTypeVal3DLA==122)");
  contribution->setAlias("p2","Alt$(2mp,1)*(LeptonTypeVal3DLA==221)+Alt$(1ep,1)*(LeptonTypeVal3DLA==212)+Alt$(1mp,1)*(LeptonTypeVal3DLA==122)");
  contribution->setAlias("p3","Alt$(1ep,1)*(LeptonTypeVal3DLA==221)+Alt$(2mp,1)*(LeptonTypeVal3DLA==212)+Alt$(2mp,1)*(LeptonTypeVal3DLA==122)");
  */
  // -------
  // 2El + Mu
  /*
  contribution->setAlias("f1","Alt$(1ef,0)*(LeptonTypeVal3DLA==112)+Alt$(1ef,0)*(LeptonTypeVal3DLA==121)+Alt$(1mf,0)*(LeptonTypeVal3DLA==211)");
  contribution->setAlias("f2","Alt$(2ef,0)*(LeptonTypeVal3DLA==112)+Alt$(1mf,0)*(LeptonTypeVal3DLA==121)+Alt$(1ef,0)*(LeptonTypeVal3DLA==211)");
  contribution->setAlias("f3","Alt$(1mf,0)*(LeptonTypeVal3DLA==112)+Alt$(2ef,0)*(LeptonTypeVal3DLA==121)+Alt$(2ef,0)*(LeptonTypeVal3DLA==211)");
  contribution->setAlias("p1","Alt$(1ep,1)*(LeptonTypeVal3DLA==112)+Alt$(1ep,1)*(LeptonTypeVal3DLA==121)+Alt$(1mp,1)*(LeptonTypeVal3DLA==211)");
  contribution->setAlias("p2","Alt$(2ep,1)*(LeptonTypeVal3DLA==112)+Alt$(1mp,1)*(LeptonTypeVal3DLA==121)+Alt$(1ep,1)*(LeptonTypeVal3DLA==211)");
  contribution->setAlias("p3","Alt$(1mp,1)*(LeptonTypeVal3DLA==112)+Alt$(2ep,1)*(LeptonTypeVal3DLA==121)+Alt$(2ep,1)*(LeptonTypeVal3DLA==211)");
  */
  //----------------------------------------------------------------------------------------

  // Name change:
  contribution->setAlias("nTTT","nTTT3DLA");
  contribution->setAlias("nTTL","nTTL3DLA");
  contribution->setAlias("nTLT","nTLT3DLA");
  contribution->setAlias("nLTT","nLTT3DLA");
  contribution->setAlias("nTLL","nTLL3DLA");
  contribution->setAlias("nLTL","nLTL3DLA");
  contribution->setAlias("nLLT","nLLT3DLA");
  contribution->setAlias("nLLL","nLLL3DLA");

  // -------------------------------------------------------------------------------------------------------------------- //
  // temporary fix: waiting for https://gitlab.com/Thomassen/RutgersIAF/commit/a7383de85af3d5582fb8a5e79ebfbc34878519d5
  // If first and third matrix leptons are not tight, and the second matrix lepton is tight, manually set nLTL=1
  //for( int i=1; i<=3; i++){
  //contribution->setAlias(TString::Format("m%dTight",i),TString::Format("Alt$(ISTIGHTMATRIXMUON[%d],0)",    i-1));
  //contribution->setAlias(TString::Format("e%dTight",i),TString::Format("Alt$(ISTIGHTMATRIXELECTRON[%d],0)",i-1));
  //}
  //contribution->setAlias("nLTL","(m1Tight+e1Tight+m3Tight+e3Tight==0)*(m2Tight+e2Tight>0)"); //possibly doesnt work for e-mu mixed case!
  // -------------------------------------------------------------------------------------------------------------------- //
  
  // for sanity check:
  contribution->setAlias("nSum","nTTT+nTTL+nTLT+nLTT+nTLL+nLTL+nLLT+nLLL");


  // 3D MM weight functions:
  contribution->setAlias("wfff","(f1*f2*f3) * ((-(nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3)) - nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) - nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 - nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 - nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p1 + p2 - p1*p2)*pow(f3 - p3,3)*p3 + nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p1 + p3 - p1*p3) + nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p2 + p3 - p2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wffp","(f1*f2*p3) * ((f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wfpf","(f1*f3*p2) * ((f2*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wpff","(f2*f3*p1) * ((f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + f1*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + f1*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + (-1 + f1)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + f1*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + (-1 + f1)*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wfpp","(f1*p2*p3) * ((-(f2*f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)) - f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wfpp","(f1*p2*p3) * ((-(f2*f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)) - f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wpfp","(f2*p1*p3) * ((-(f1*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)) - f1*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - f1*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - f1*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wppf","(f3*p1*p2) * ((-(f1*f2*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3)) - (-1 + f1)*(-1 + f2)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) - f1*f2*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - f1*(-1 + f2)*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - (-1 + f1)*f2*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f1 + f2 - f1*f2)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f1 + p3 - f1*p3) + f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f2 + p3 - f2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //
  contribution->setAlias("wppp","(p1*p2*p3) * ((f1*f2*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)))");
  //

  // MM predictions:
  contribution->setAlias("tripleFakeBckg","wfff");
  contribution->setAlias("doubleFakeBckg","wffp+wfpf+wpff");
  contribution->setAlias("singleFakeBckg","+wfpp+wpfp+wppf");
  contribution->setAlias("fakeBckg","wfff+wffp+wfpf+wpff+wfpp+wpfp+wppf");
  contribution->setAlias("promptBckg","wppp");

  // Systematic Uncertainties on MM predictions:
  // Pending..

}

