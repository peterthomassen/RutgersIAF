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
float muFR( float pt, float eta, float aux, int pu, double ttfrac = 0.5 ){// aux is JETNOODCONST
  //
  float puFudgeFactorDY = 0.6537+0.01887*pu;
  float puFudgeFactorTT = 0.5807+0.02425*pu;
  float puFudgeFactor   = puFudgeFactorDY*(1-ttfrac)+puFudgeFactorTT*ttfrac;
  //
  double dy_pt1aux1[4] = {0.278928,  0.293323,  0.351441,  0.373284};
  double tt_pt1aux1[4] = {0.196746,  0.232648,  0.301672,  0.328507};
  double dy_pt1aux2[4] = {0.0947098, 0.107661,  0.15737,   0.203869};
  double tt_pt1aux2[4] = {0.0686246, 0.0909286, 0.118021,  0.116879};
  double dy_pt2aux1[4] = {0.27297,   0.339212,  0.381945,  0.381719};
  double tt_pt2aux1[4] = {0.220477,  0.29339,   0.383246,  0.369223};
  double dy_pt2aux2[4] = {0.0819678, 0.115186,  0.17209,   0.126654};
  double tt_pt2aux2[4] = {0.0550719, 0.0827279, 0.115189,  0.124113};
  double dy_pt3aux1[4] = {0.181835,  0.29535,   0.417729,  0.227695};
  double tt_pt3aux1[4] = {0.343549,  0.433043,  0.493151,  0.482818};
  double dy_pt3aux2[4] = {0.0910248, 0.0915931, 0.0870385, 0.214689};
  double tt_pt3aux2[4] = {0.0821324, 0.114872,  0.15649,   0.194138};
  //
  // ------
  if( pt<15 ){
    if( aux<11.5 ){
      if(      TMath::abs(eta)>1.6 ) return (dy_pt1aux1[3]*(1-ttfrac)+tt_pt1aux1[3]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>1.2 ) return (dy_pt1aux1[2]*(1-ttfrac)+tt_pt1aux1[2]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>0.8 ) return (dy_pt1aux1[1]*(1-ttfrac)+tt_pt1aux1[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt1aux1[0]*(1-ttfrac)+tt_pt1aux1[0]*ttfrac)*puFudgeFactor;
    }
    //
    else{
      if(      TMath::abs(eta)>1.6 ) return (dy_pt1aux2[3]*(1-ttfrac)+tt_pt1aux2[3]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>1.2 ) return (dy_pt1aux2[2]*(1-ttfrac)+tt_pt1aux2[2]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>0.8 ) return (dy_pt1aux2[1]*(1-ttfrac)+tt_pt1aux2[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt1aux2[0]*(1-ttfrac)+tt_pt1aux2[0]*ttfrac)*puFudgeFactor;
    }
  }
  // ------
  else if( pt<40 ){
    if( aux<11.5 ){
      if(      TMath::abs(eta)>1.6 ) return (dy_pt2aux1[3]*(1-ttfrac)+tt_pt2aux1[3]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>1.2 ) return (dy_pt2aux1[2]*(1-ttfrac)+tt_pt2aux1[2]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>0.8 ) return (dy_pt2aux1[1]*(1-ttfrac)+tt_pt2aux1[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt2aux1[0]*(1-ttfrac)+tt_pt2aux1[0]*ttfrac)*puFudgeFactor;
    }
    //
    else{
      if(      TMath::abs(eta)>1.6 ) return (dy_pt2aux2[3]*(1-ttfrac)+tt_pt2aux2[3]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>1.2 ) return (dy_pt2aux2[2]*(1-ttfrac)+tt_pt2aux2[2]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>0.8 ) return (dy_pt2aux2[1]*(1-ttfrac)+tt_pt2aux2[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt2aux2[0]*(1-ttfrac)+tt_pt2aux2[0]*ttfrac)*puFudgeFactor;
    }
  }
  // ------
  else{
    if( aux<11.5 ){
      if(      TMath::abs(eta)>1.6 ) return (dy_pt3aux1[3]*(1-ttfrac)+tt_pt3aux1[3]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>1.2 ) return (dy_pt3aux1[2]*(1-ttfrac)+tt_pt3aux1[2]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>0.8 ) return (dy_pt3aux1[1]*(1-ttfrac)+tt_pt3aux1[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt3aux1[0]*(1-ttfrac)+tt_pt3aux1[0]*ttfrac)*puFudgeFactor;
    }
    //
    else{
      if(      TMath::abs(eta)>1.6 ) return (dy_pt3aux2[3]*(1-ttfrac)+tt_pt3aux2[3]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>1.2 ) return (dy_pt3aux2[2]*(1-ttfrac)+tt_pt3aux2[2]*ttfrac)*puFudgeFactor;
      else if( TMath::abs(eta)>0.8 ) return (dy_pt3aux2[1]*(1-ttfrac)+tt_pt3aux2[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt3aux2[0]*(1-ttfrac)+tt_pt3aux2[0]*ttfrac)*puFudgeFactor;
    }
  }
  // ------
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
float elFR( float pt, float eta, float aux, int pu, double ttfrac=0.5 ){// aux is CONENDR03TO07
  //
  float puFudgeFactorDY = 0.783+0.0121*pu;
  float puFudgeFactorTT = 0.622+0.0219*pu;
  float puFudgeFactor   = puFudgeFactorDY*(1-ttfrac)+puFudgeFactorTT*ttfrac;
  //
  double dy_pt1aux1[4] = {0.0846258, 0.067997,  0.0964844, 0.0935314};
  double tt_pt1aux1[4] = {0.102297,  0.109783,  0.118133,  0.110278 };
  double dy_pt1aux2[4] = {0.0858718, 0.0957084, 0.0960298, 0.0680214};
  double tt_pt1aux2[4] = {0.0984432, 0.0957944, 0.110951,  0.0822723};
  double dy_pt2aux1[4] = {0.0488455, 0.0533243, 0.058976,  0.0912755};
  double tt_pt2aux1[4] = {0.0580961, 0.0574215, 0.0813953, 0.0985414};
  double dy_pt2aux2[4] = {0.0549532, 0.0553764, 0.062472,  0.0587218};
  double tt_pt2aux2[4] = {0.0586517, 0.0647359, 0.0718603, 0.0904184};
  double dy_pt3aux1[4] = {0.024817,  0.0265909, 0.0348484, 0.0750026};
  double tt_pt3aux1[4] = {0.0270479, 0.0361861, 0.0480769, 0.0803736};
  double dy_pt3aux2[4] = {0.0199044, 0.0263238, 0.0267278, 0.0635343};
  double tt_pt3aux2[4] = {0.0291502, 0.0321577, 0.0444685, 0.0567752};
  //
  // ------
  if( pt<15 ){
    if( aux<5.5 ){
      if(      TMath::Abs(eta)>1.6 ) return (dy_pt1aux1[3]*(1-ttfrac)+tt_pt1aux1[3]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>1.2 ) return (dy_pt1aux1[2]*(1-ttfrac)+tt_pt1aux1[2]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>0.8 ) return (dy_pt1aux1[1]*(1-ttfrac)+tt_pt1aux1[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt1aux1[0]*(1-ttfrac)+tt_pt1aux1[0]*ttfrac)*puFudgeFactor;
    }
    //
    else{
      if(      TMath::Abs(eta)>1.6 ) return (dy_pt1aux2[3]*(1-ttfrac)+tt_pt1aux2[3]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>1.2 ) return (dy_pt1aux2[2]*(1-ttfrac)+tt_pt1aux2[2]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>0.8 ) return (dy_pt1aux2[1]*(1-ttfrac)+tt_pt1aux2[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt1aux2[0]*(1-ttfrac)+tt_pt1aux2[0]*ttfrac)*puFudgeFactor;
    }
  }
  // ------
  else if( pt<40 ){
    if( aux<5.5 ){
      if(      TMath::Abs(eta)>1.6 ) return (dy_pt2aux1[3]*(1-ttfrac)+tt_pt2aux1[3]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>1.2 ) return (dy_pt2aux1[2]*(1-ttfrac)+tt_pt2aux1[2]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>0.8 ) return (dy_pt2aux1[1]*(1-ttfrac)+tt_pt2aux1[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt2aux1[0]*(1-ttfrac)+tt_pt2aux1[0]*ttfrac)*puFudgeFactor;
    }
    //
    else{
      if(      TMath::Abs(eta)>1.6 ) return (dy_pt2aux2[3]*(1-ttfrac)+tt_pt2aux2[3]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>1.2 ) return (dy_pt2aux2[2]*(1-ttfrac)+tt_pt2aux2[2]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>0.8 ) return (dy_pt2aux2[1]*(1-ttfrac)+tt_pt2aux2[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt2aux2[0]*(1-ttfrac)+tt_pt2aux2[0]*ttfrac)*puFudgeFactor;
    }
  }
  // ------
  else{
    if( aux<5.5 ){
      if(      TMath::Abs(eta)>1.6 ) return (dy_pt3aux1[3]*(1-ttfrac)+tt_pt3aux1[3]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>1.2 ) return (dy_pt3aux1[2]*(1-ttfrac)+tt_pt3aux1[2]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>0.8 ) return (dy_pt3aux1[1]*(1-ttfrac)+tt_pt3aux1[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt3aux1[0]*(1-ttfrac)+tt_pt3aux1[0]*ttfrac)*puFudgeFactor;
    }
    //
    else{
      if(      TMath::Abs(eta)>1.6 ) return (dy_pt3aux2[3]*(1-ttfrac)+tt_pt3aux2[3]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>1.2 ) return (dy_pt3aux2[2]*(1-ttfrac)+tt_pt3aux2[2]*ttfrac)*puFudgeFactor;
      else if( TMath::Abs(eta)>0.8 ) return (dy_pt3aux2[1]*(1-ttfrac)+tt_pt3aux2[1]*ttfrac)*puFudgeFactor;
      else                           return (dy_pt3aux2[0]*(1-ttfrac)+tt_pt3aux2[0]*ttfrac)*puFudgeFactor;
    }
  }
  // ------
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

