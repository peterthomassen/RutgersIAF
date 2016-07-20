#include <iostream>
#include <TH1.h>
#include <boost/algorithm/string.hpp>

#include "RutgersIAF/AnalysisPresenter/interface/Assembler.h"
#include "RutgersIAF/AnalysisPresenter/interface/Bundle.h"
#include "RutgersIAF/AnalysisPresenter/interface/Channel.h"
#include "RutgersIAF/AnalysisPresenter/interface/PhysicsContribution.h"

// muon prompt rate
float muPR( float pt, float eta, float aux ){ 
  //
  if( pt < 20  )  return 0.8245;  
  if( pt < 40  )  return 0.9070;
  if( pt < 80  )  return 0.9514;
  if( pt < 120 )  return 0.9693;
  //
  return 0.9706;
}

// muon fake rate
float muFR( float pt, float eta, float aux, int pu, double ttfrac = 0.5 ){
  //
  float etaFudgeFactor = 1;
  ////if( fabs(eta)<2.5 ) etaFudgeFactor=1.3;
  ////if( fabs(eta)<1.8 ) etaFudgeFactor=1;
  ////if( fabs(eta)<1.2 ) etaFudgeFactor=0.7;
  ////etaFudgeFactor = 1;
  if( fabs(eta)<2.5 ) etaFudgeFactor=1.5;//fixed on exact 3mu selection in TTtoLLNuNu MC
  if( fabs(eta)<1.2 ) etaFudgeFactor=1;//fixed on exact 3mu selection in TTtoLLNuNu MC
  if( fabs(eta)<0.9 ) etaFudgeFactor=0.9;//fixed on exact 3mu selection in TTtoLLNuNu MC
  //if( fabs(eta)<0.9 ) etaFudgeFactor=0.7;
  //
  float puFudgeFactor = 1;
  ////puFudgeFactor=0.045*(pu-16)+1;
  ////if( pu < 13 )   puFudgeFactor=0.06*(pu-12)+1;
  ////puFudgeFactor = 1;
  //puFudgeFactor=0.032*(pu-20)+1;
  //if( pu>20 )  puFudgeFactor=0.044*(pu-20)+1;
  if( pu<17 )  puFudgeFactor=0.039*(pu-17)+1;//fixed on exact 3mu selection in TTtoLLNuNu MC
  if( pu>17 )  puFudgeFactor=0.04*(pu-17)+1;//fixed on exact 3mu selection in TTtoLLNuNu MC
  //
  // -------------------- Low Aux
  double lowAuxDY[5] = { 0.3058, 0.3092, 0.2,    0.2,     0.2    };
  double lowAuxTT[5] = { 0.2265, 0.2603, 0.3244, 0.4244,  0.4324 };
  if( aux<12.5 ){
    if( pt < 20  )  return (lowAuxDY[0]*(1-ttfrac)+lowAuxTT[0]*ttfrac)*etaFudgeFactor*puFudgeFactor;
    if( pt < 40  )  return (lowAuxDY[1]*(1-ttfrac)+lowAuxTT[1]*ttfrac)*etaFudgeFactor*puFudgeFactor;
    if( pt < 80  )  return (lowAuxDY[2]*(1-ttfrac)+lowAuxTT[2]*ttfrac)*etaFudgeFactor*puFudgeFactor;
    if( pt < 120 )  return (lowAuxDY[3]*(1-ttfrac)+lowAuxTT[3]*ttfrac)*etaFudgeFactor*puFudgeFactor;
    if( pt >=120 )  return (lowAuxDY[4]*(1-ttfrac)+lowAuxTT[4]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  }
  // -------------------- High Aux
  double highAuxDY[5] = { 0.1069, 0.1294, 0.0689, 0.0689, 0.0689 };
  double highAuxTT[5] = { 0.0724, 0.0775, 0.1001, 0.1405, 0.1556 };
  if( pt < 20  )  return (highAuxDY[0]*(1-ttfrac)+highAuxTT[0]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 40  )  return (highAuxDY[1]*(1-ttfrac)+highAuxTT[1]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 80  )  return (highAuxDY[2]*(1-ttfrac)+highAuxTT[2]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 120 )  return (highAuxDY[3]*(1-ttfrac)+highAuxTT[3]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt >=120 )  return (highAuxDY[4]*(1-ttfrac)+highAuxTT[4]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  // -------------------- Inclusive
  /*
  double inclDY[5] = { 0.2515, 0.2172, 0.1224, 0.1224, 0.1224 };
  double inclTT[5] = { 0.1599, 0.1465, 0.1493, 0.1826, 0.1699 };
  if( pt < 20  )  return (inclDY[0]*(1-ttfrac)+inclTT[0]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 40  )  return (inclDY[1]*(1-ttfrac)+inclTT[1]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 80  )  return (inclDY[2]*(1-ttfrac)+inclTT[2]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 120 )  return (inclDY[3]*(1-ttfrac)+inclTT[3]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt >=120 )  return (inclDY[4]*(1-ttfrac)+inclTT[4]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  */
  //
  return 0;
}

// electron prompt rate
float elPR( float pt, float eta, float aux ){ 
  //
  if( pt < 20 )  return 0.5736;  
  if( pt < 40 )  return 0.7584;
  if( pt < 60 )  return 0.8586;
  if( pt <120 )  return 0.9030;
  //
  return 0.9186;
}

// electron fake rate
float elFR( float pt, float eta, float aux, int pu, double ttfrac=0 ){ 
  //
  float etaFudgeFactor = 1;
  //if( fabs(eta)<2.5 ) etaFudgeFactor=1.1;
  if( fabs(eta)<1.2 ) etaFudgeFactor=0.7;
  //if( fabs(eta)<0.9 ) etaFudgeFactor=0.9;
  //
  float puFudgeFactor = 1;
  if( pu < 12 ) puFudgeFactor=0.06*(pu-12)+1;
  if( pu > 12 ) puFudgeFactor=0.035*(pu-12)+1;
  //
  double lowAuxDY[5] = { 0.1044, 0.1214, 0.1096, 0.1372, 0.1111 };
  double lowAuxTT[5] = { 0.1154, 0.1033, 0.1047, 0.1190, 0.1327 };
  //
  double highAuxDY[5] = { 0.0459, 0.0150, 0.0085, 0.0215, 0.0111 };
  double highAuxTT[5] = { 0.0569, 0.0239, 0.0162, 0.0177, 0.0117 };
  //
  if( aux<12.5 ){
    if( pt < 20 ) return (lowAuxDY[0]*(1-ttfrac)+lowAuxTT[0]*ttfrac)*etaFudgeFactor*puFudgeFactor;  
    if( pt < 40 ) return (lowAuxDY[1]*(1-ttfrac)+lowAuxTT[1]*ttfrac)*etaFudgeFactor*puFudgeFactor;
    if( pt < 60 ) return (lowAuxDY[2]*(1-ttfrac)+lowAuxTT[2]*ttfrac)*etaFudgeFactor*puFudgeFactor;
    if( pt <120 ) return (lowAuxDY[3]*(1-ttfrac)+lowAuxTT[3]*ttfrac)*etaFudgeFactor*puFudgeFactor;
    if( pt>=120 ) return (lowAuxDY[4]*(1-ttfrac)+lowAuxTT[4]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  }
  //
  if( pt < 20 ) return (highAuxDY[0]*(1-ttfrac)+highAuxTT[0]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 40 ) return (highAuxDY[1]*(1-ttfrac)+highAuxTT[1]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt < 60 ) return (highAuxDY[2]*(1-ttfrac)+highAuxTT[2]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt <120 ) return (highAuxDY[3]*(1-ttfrac)+highAuxTT[3]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  if( pt>=120 ) return (highAuxDY[4]*(1-ttfrac)+highAuxTT[4]*ttfrac)*etaFudgeFactor*puFudgeFactor;
  //
  return 0;
}

// ----------------------------------------------------------------------------------------------------------------------------
// REGULAR USERS SHOULD NOT NEED TO MODIFY LINES BEYOND THIS POINT!
// ----------------------------------------------------------------------------------------------------------------------------

// this calculates and outputs the fakeBckg weight per event
float setMatrixWeights( float p1, float f1, float p2, float f2, float p3, float f3, 
			float nTTT, float nLLT, float nLTL, float nTLL, float nTTL, float nTLT, float nLTT, float nLLL ){        
  //
  float wfff = (f1*f2*f3) * ((-(nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3)) - nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) - nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 - nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 - nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p1 + p2 - p1*p2)*pow(f3 - p3,3)*p3 + nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p1 + p3 - p1*p3) + nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p2 + p3 - p2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  float wffp = (f1*f2*p3) * ((f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  float wfpf = (f1*f3*p2) * ((f2*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  float wpff = (f2*f3*p1) * ((f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + f1*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + f1*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + (-1 + f1)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + f1*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + (-1 + f1)*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  // 
  float wfpp = (f1*p2*p3) * ((-(f2*f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)) - f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  float wpfp = (f2*p1*p3) * ((-(f1*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)) - f1*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - f1*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - f1*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  float wppf = (f3*p1*p2) * ((-(f1*f2*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3)) - (-1 + f1)*(-1 + f2)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) - f1*f2*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - f1*(-1 + f2)*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - (-1 + f1)*f2*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f1 + f2 - f1*f2)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f1 + p3 - f1*p3) + f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f2 + p3 - f2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  float wppp = (p1*p2*p3) * ((f1*f2*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));

  //tripleFakeBckg   = wfff;
  //doubleFakeBckg   = wffp+wfpf+wpff;
  //singleFakeBckg   = wfpp+wpfp+wppf;
  float fakeBckg     = wfff+wffp+wfpf+wpff+wfpp+wpfp+wppf;
  //triplePromptBckg = wppp;
  //
  return fakeBckg;
}

//double LUTvalue( double pt1, double eta1, int aux1, int isTight1, double lepType1,
//		 double pt2, double eta2, int aux2, int isTight2, double lepType2,
//		 double pt3, double eta3, int aux3, int isTight3, double lepType3  ){

//double LUTvalue( double pt1,     int aux1,
//		 double pt2,     int aux2, 
//		 double pt3,     int aux3,  
//		 int    isTight, int lepType  ){ //8

//double LUTvalue( double pt1, double eta1, int aux1, 
//		 double pt2, double eta2, int aux2, 
//		 double pt3, double eta3, int aux3,  
//		 int isTightAndlepType ){ //10

double MMweight( double pt1, double eta1,
		 double pt2, double eta2,
		 double pt3, double eta3,
		 int auxCombined, int pu, 
		 int isTightAndlepType ){ //9

  //
  // std::cout<<"LUTvalue TEST***********"<<std::endl;
  //  double xbin[15]={ pt1, eta1, (double)aux1, (double)isTight1, 
  //		    pt2, eta2, (double)aux2, (double)isTight2,
  //		    pt3, eta3, (double)aux3, (double)isTight3 };

  int aux1=(int)((auxCombined-auxCombined%100)/100)*20;
  int aux2=(int)((auxCombined%100-auxCombined%10)/10)*20;
  int aux3=(int)(auxCombined%10)*20;

  //std::cout<<"auxCombined: "<<auxCombined<<std::endl;
  //std::cout<<"aux1: "<<aux1<<std::endl;
  //std::cout<<"aux2: "<<aux2<<std::endl;
  //std::cout<<"aux3: "<<aux3<<std::endl;

  int lepType = (int)(isTightAndlepType%1000);
  int isTight = (int)((isTightAndlepType-isTightAndlepType%1000)/1000);
  //
  int isTight1=(int)((isTight-isTight%100)/100);
  int isTight2=(int)((isTight%100-isTight%10)/10);
  int isTight3=(int)(isTight%10);

  /*
  double xbin[12]={ pt1, eta1, (double)aux1, (double)isTight1, 
		    pt2, eta2, (double)aux2, (double)isTight2,
		    pt3, eta3, (double)aux3, (double)isTight3  };
  */
  
  /*
  //
  double ele_ptbins[6]     = {  10, 20, 40, 80, 120, 99999 };  TH1D* ElectronPt     = new TH1D("ElectronPt",    "", 5, ele_ptbins     );
  double ele_absetabins[3] = {  0, 1.2, 3.0 };                 TH1D* ElectronAbsEta = new TH1D("ElectronAbsEta","", 2, ele_absetabins ); 
  double ele_auxabins[3]   = { -0.5, 15.5, 200.5 };            TH1D* ElectronAuxA   = new TH1D("ElectronAuxA",  "", 2, ele_auxabins   );
  double ele_auxbbins[3]   = { -0.5, 15.5, 200.5 };            TH1D* ElectronAuxB   = new TH1D("ElectronAuxB",  "", 2, ele_auxbbins   );
  //
  double mu_ptbins[6]      = {  10, 20, 40, 80, 120, 99999 };  TH1D* MuonPt     = new TH1D("MuonPt",    "", 5, mu_ptbins     );
  double mu_absetabins[3]  = {  0, 1.2, 3.0 };                 TH1D* MuonAbsEta = new TH1D("MuonAbsEta","", 2, mu_absetabins ); 
  double mu_auxabins[3]    = { -0.5, 15.5, 200.5 };            TH1D* MuonAuxA   = new TH1D("MuonAuxA",  "", 2, mu_auxabins   );
  double mu_auxbbins[3]    = { -0.5, 15.5, 200.5 };            TH1D* MuonAuxB   = new TH1D("MuonAuxB",  "", 2, mu_auxbbins   );

  int ibin[15]={ 0 };
  // ------------------------------------------------
  if( lepType1==1 ){
    ibin[0]=ElectronPt->FindBin(pt1);
    ibin[1]=ElectronEta->FindBin(eta1);
    ibin[2]=ElectronAuxA->FindBin(auxA1);
    ibin[3]=ElectronAuxB->FindBin(auxB1);
    ibin[4]=(int)(isTight1+1);// 0 1 -> 1 2
  }
  if( lepType2==1 ){
    ibin[5]=ElectronPt->FindBin(pt2);
    ibin[6]=ElectronEta->FindBin(eta2);
    ibin[7]=ElectronAuxA->FindBin(auxA2);
    ibin[8]=ElectronAuxB->FindBin(auxB2);
    ibin[9]=(int)(isTight2+1);// 0 1 -> 1 2
  }
  if( lepType3==1 ){
    ibin[10]=ElectronPt->FindBin(pt3);
    ibin[11]=ElectronEta->FindBin(eta3);
    ibin[12]=ElectronAuxA->FindBin(auxA3);
    ibin[13]=ElectronAuxB->FindBin(auxB3);
    ibin[14]=(int)(isTight3+1);// 0 1 -> 1 2
  }
  // ------------------------------------------------
  if( lepType1==2 ){
    ibin[0]=MuonPt->FindBin(pt1);
    ibin[1]=MuonEta->FindBin(eta1);
    ibin[2]=MuonAuxA->FindBin(auxA1);
    ibin[3]=MuonAuxB->FindBin(auxB1);
    ibin[4]=(int)(isTight1+1);// 0 1 -> 1 2
  }
  if( lepType2==2 ){
    ibin[5]=MuonPt->FindBin(pt2);
    ibin[6]=MuonEta->FindBin(eta2);
    ibin[7]=MuonAuxA->FindBin(auxA2);
    ibin[8]=MuonAuxB->FindBin(auxB2);
    ibin[9]=(int)(isTight2+1);// 0 1 -> 1 2
  }
  if( lepType3==2 ){
    ibin[10]=MuonPt->FindBin(pt3);
    ibin[11]=MuonEta->FindBin(eta3);
    ibin[12]=MuonAuxA->FindBin(auxA3);
    ibin[13]=MuonAuxB->FindBin(auxB3);
    ibin[14]=(int)(isTight3+1);// 0 1 -> 1 2
  }
  // ------------------------------------------------
  */

  TString lutlabel;
  /*
  // e e e
  if(lepType1==1 && lepType2==1 && lepType3==1) lutlabel="ElElElMatrixLUT";
  // 
  // e e mu / e mu e / mu e e
  if(lepType1==1 && lepType2==1 && lepType3==2) lutlabel="ElElMuMatrixLUT";
  if(lepType1==1 && lepType2==2 && lepType3==1) lutlabel="ElMuElMatrixLUT";
  if(lepType1==2 && lepType2==1 && lepType3==1) lutlabel="MuElElMatrixLUT";
  //
  // e mu mu / mu e mu / mu mu e
  if(lepType1==1 && lepType2==2 && lepType3==2) lutlabel="ElMuMuMatrixLUT";
  if(lepType1==2 && lepType2==1 && lepType3==2) lutlabel="MuElMuMatrixLUT";
  if(lepType1==2 && lepType2==2 && lepType3==1) lutlabel="MuMuElMatrixLUT";
*/
  //
  // mu mu mu
  //if(lepType1==2 && lepType2==2 && lepType3==2) lutlabel="MuMuMuMatrixLUT";
  //if( lepType==222 ) lutlabel="Mu3MatrixLUT";

  // Open LUT file
  //TFile* fi = new TFile("MatrixLUT.V0.0.root","READ");
  /*
  TFile* fi = new TFile("/cms/multilepton/hsaka/Workspace/TEST-JUL18/CMSSW_8_0_8_patch2/src/RutgersIAF/AnalysisPresenter/test/MatrixLUTs/Mu3MatrixLUT.root","READ");
  THnSparseF* hLUT = (THnSparseF*)(fi->Get(lutlabel));

  std::cout<<"hLUT->GetBin(xbin): "<<hLUT->GetBin(xbin)<<std::endl;
  //
  return hLUT->GetBin(xbin);
  */

  float e1f = elFR( pt1, eta1, aux1, pu );
  float m1f = muFR( pt1, eta1, aux1, pu );
  float e1p = elPR( pt1, eta1, aux1 );
  float m1p = muPR( pt1, eta1, aux1 );
  //
  float e2f = elFR( pt2, eta2, aux2, pu );
  float m2f = muFR( pt2, eta2, aux2, pu );
  float e2p = elPR( pt2, eta2, aux2 );
  float m2p = muPR( pt2, eta2, aux2 );
  //
  float e3f = elFR( pt3, eta3, aux3, pu );
  float m3f = muFR( pt3, eta3, aux3, pu );
  float e3p = elPR( pt3, eta3, aux3 );
  float m3p = muPR( pt3, eta3, aux3 );

  //cout<<" calculateMatrixEventWeight::debug  e1f: "<<e1f<<endl;
  //cout<<" calculateMatrixEventWeight::debug  e1p: "<<e1p<<endl;
  //
  float f1=0;  float p1=0;  float f2=0;   float p2=0;  float f3=0;   float p3=0;
  //
  if( lepType==111 ){ f1=e1f; f2=e2f; f3=e3f; p1=e1p; p2=e2p; p3=e3p; }
  if( lepType==112 ){ f1=e1f; f2=e2f; f3=m3f; p1=e1p; p2=e2p; p3=m3p; }
  if( lepType==121 ){ f1=e1f; f2=m2f; f3=e3f; p1=e1p; p2=m2p; p3=e3p; }
  if( lepType==211 ){ f1=m1f; f2=e2f; f3=e3f; p1=m1p; p2=e2p; p3=e3p; }
  if( lepType==122 ){ f1=e1f; f2=m2f; f3=m3f; p1=e1p; p2=m2p; p3=m3p; }
  if( lepType==212 ){ f1=m1f; f2=e2f; f3=m3f; p1=m1p; p2=e2p; p3=m3p; }
  if( lepType==221 ){ f1=m1f; f2=m2f; f3=e3f; p1=m1p; p2=m2p; p3=e3p; }
  if( lepType==222 ){ f1=m1f; f2=m2f; f3=m3f; p1=m1p; p2=m2p; p3=m3p; }
  //
  //cout<<" calculateMatrixEventWeight::debug  f1/f2/f3: "<<f1<<"/"<<f2<<"/"<<f3<<endl;
  //cout<<" calculateMatrixEventWeight::debug  p1/p2/p3: "<<p1<<"/"<<p2<<"/"<<p3<<endl;
  //
  float fakeBckg=0;
  float nTTT = 0;
  float nLLT = 0;  float nLTL = 0;  float nTLL = 0;
  float nTTL = 0;  float nTLT = 0;  float nLTT = 0;
  float nLLL = 0;
  //
  if( isTight1==1 && isTight2==1 && isTight3==1 ) nTTT=1;
  if( isTight1==1 && isTight2==1 && isTight3==0 ) nTTL=1;
  if( isTight1==1 && isTight2==0 && isTight3==1 ) nTLT=1;
  if( isTight1==0 && isTight2==1 && isTight3==1 ) nLTT=1;
  if( isTight1==1 && isTight2==0 && isTight3==0 ) nTLL=1;
  if( isTight1==0 && isTight2==1 && isTight3==0 ) nLTL=1;
  if( isTight1==0 && isTight2==0 && isTight3==1 ) nLLT=1;
  if( isTight1==0 && isTight2==0 && isTight3==0 ) nLLL=1;

  fakeBckg = setMatrixWeights( p1, f1, p2, f2, p3, f3, nTTT, nLLT, nLTL, nTLL, nTTL, nTLT, nLTT, nLLL);

  //std::cout<<"fakeBckg: "<<fakeBckg<<endl;
  return fakeBckg;

}

