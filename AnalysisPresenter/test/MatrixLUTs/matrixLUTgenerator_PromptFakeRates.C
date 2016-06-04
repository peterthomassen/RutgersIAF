
// ----------------------------------------------------------------------------------------------------------------------------
// PROMPT AND FAKE RATES ARE DEFINED HERE. 
// **WARNING**: THE BIN BOUNDARIES OF THE FAKE AND PROMPT RATES SHOULD BE IN SYNC WITH THE 
//              THn BIN BOUNDARIES DESCRIBED IN matrixLUTgenerator.C
// ----------------------------------------------------------------------------------------------------------------------------

// muon prompt rate
float muPR( float pt, float eta, float aux ){ 
  //
  if( pt < 20 )  return 0.85;  
  if( pt < 30 )  return 0.92;
  if( pt < 50 )  return 0.95;
  if( pt < 75 )  return 0.97;
  if( pt <100 )  return 0.98;
  return 0.98;
  //
}

// muon fake rate
float muFR( float pt, float eta, float aux ){
  //
  float etaFudgeFactor = 1;
  if(                   fabs(eta)<1.1 ) etaFudgeFactor=0.9;
  if( fabs(eta)>=1.1 && fabs(eta)<1.4 ) etaFudgeFactor=1.0;
  if( fabs(eta)>=1.4 && fabs(eta)<2.5 ) etaFudgeFactor=1.2;
  //
  if( aux<8.5 ){
    if( pt < 20 )  return etaFudgeFactor*0.06;
    if( pt < 30 )  return etaFudgeFactor*0.075;
    if( pt < 50 )  return etaFudgeFactor*0.10;
    if( pt < 75 )  return etaFudgeFactor*0.15;
    if( pt <100 )  return etaFudgeFactor*0.20;
    return etaFudgeFactor*0.23;
  }
  //
  if( pt < 20 )  return etaFudgeFactor*0.006;
  if( pt < 30 )  return etaFudgeFactor*0.008;
  if( pt < 50 )  return etaFudgeFactor*0.018;
  if( pt < 75 )  return etaFudgeFactor*0.030;
  if( pt <100 )  return etaFudgeFactor*0.043;
  return etaFudgeFactor*0.050;
  //
}

// electron prompt rate
float elPR( float pt, float eta, float aux ){ 
  //
  if( pt < 20 )  return 0.50;  
  if( pt < 40 )  return 0.725;
  if( pt < 60 )  return 0.83;
  if( pt <100 )  return 0.88;
  return 0.91;
  //
}

// electron fake rate
float elFR( float pt, float eta, float aux ){ 
  //
  if( aux<8.5 ){
    if( pt < 20 )  return 0.07;  
    if( pt < 40 )  return 0.10;
    if( pt < 60 )  return 0.10;
    if( pt <100 )  return 0.12;
    return 0.15;
  }
  //
  if( aux<15.5 ){
    if( pt < 20 )  return 0.010; 
    if( pt < 40 )  return 0.016;
    if( pt < 60 )  return 0.028;
    if( pt <100 )  return 0.048;
    return 0.075;
  }
  //
  if( pt < 20 )  return 0.0027;
  if( pt < 40 )  return 0.0006;
  if( pt < 60 )  return 0.0017;
  if( pt <100 )  return 0.0030;
  return 0.0080;
  //
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

// ----------------------------------------------------------------------------------------------------------------------------

float calculateMatrixEventWeight( int leptonType, 
				  float pt1, float eta1, int aux1, int isTight1, 
				  float pt2, float eta2, int aux2, int isTight2, 
				  float pt3, float eta3, int aux3, int isTight3  ){
  float e1f = elFR( pt1, eta1, aux1 );
  float m1f = muFR( pt1, eta1, aux1 );
  float e1p = elPR( pt1, eta1, aux1 );
  float m1p = muPR( pt1, eta1, aux1 );
  //
  float e2f = elFR( pt2, eta2, aux2 );
  float m2f = muFR( pt2, eta2, aux2 );
  float e2p = elPR( pt2, eta2, aux2 );
  float m2p = muPR( pt2, eta2, aux2 );
  //
  float e3f = elFR( pt3, eta3, aux3 );
  float m3f = muFR( pt3, eta3, aux3 );
  float e3p = elPR( pt3, eta3, aux3 );
  float m3p = muPR( pt3, eta3, aux3 );

  //cout<<" calculateMatrixEventWeight::debug  e1f: "<<e1f<<endl;
  //cout<<" calculateMatrixEventWeight::debug  e1p: "<<e1p<<endl;
  //
  float f1=0;  float p1=0;  float f2=0;   float p2=0;  float f3=0;   float p3=0;
  //
  if( leptonType==111 ){ f1=e1f; f2=e2f; f3=e3f; p1=e1p; p2=e2p; p3=e3p; }
  if( leptonType==112 ){ f1=e1f; f2=e2f; f3=m3f; p1=e1p; p2=e2p; p3=m3p; }
  if( leptonType==121 ){ f1=e1f; f2=m2f; f3=e3f; p1=e1p; p2=m2p; p3=e3p; }
  if( leptonType==211 ){ f1=m1f; f2=e2f; f3=e3f; p1=m1p; p2=e2p; p3=e3p; }
  if( leptonType==122 ){ f1=e1f; f2=m2f; f3=m3f; p1=e1p; p2=m2p; p3=m3p; }
  if( leptonType==212 ){ f1=m1f; f2=e2f; f3=m3f; p1=m1p; p2=e2p; p3=m3p; }
  if( leptonType==221 ){ f1=m1f; f2=m2f; f3=e3f; p1=m1p; p2=m2p; p3=e3p; }
  if( leptonType==222 ){ f1=m1f; f2=m2f; f3=m3f; p1=m1p; p2=m2p; p3=m3p; }
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
  //
  fakeBckg = setMatrixWeights( p1, f1, p2, f2, p3, f3, nTTT, nLLT, nLTL, nTLL, nTTL, nTLT, nLTT, nLLL);
  //
  return fakeBckg;
}

// ----------------------------------------------------------------------------------------------------------------------------

void printTHnEntry(THnSparseF* h, int ibin[12]){
  cout<<" Bin (Pt/Eta/Aux/isTight) Lep1  / Lep2 /  Lep3  : ";
  for( int i=0; i<12; i++){
    if( (i+1)%4==0 && i>0 && i<11 ) cout<<h->GetAxis(i)->GetBinCenter(ibin[i])<<" / ";
    else if(i<11) cout<<h->GetAxis(i)->GetBinCenter(ibin[i])<<"/";
    else cout<<h->GetAxis(i)->GetBinCenter(ibin[i])<<" ---  fakeBckg: "<<h->GetBinContent(ibin)<<endl;
  }
}

void fillTHn( THnSparseF* h, int leptonType, bool isDebug){
  //loop over all bins in all axes:
  cout<<"Filling in "<<h->GetTitle()<<endl;
  for(unsigned int ibin11=1; ibin11<=h->GetAxis(0)->GetNbins(); ibin11++){// 1st lepton
    for(unsigned int ibin21=1; ibin21<=h->GetAxis(1)->GetNbins(); ibin21++){
      for(unsigned int ibin31=1; ibin31<=h->GetAxis(2)->GetNbins(); ibin31++){
	for(unsigned int ibin41=1; ibin41<=h->GetAxis(3)->GetNbins(); ibin41++){
	  //
	  for(unsigned int ibin12=1; ibin12<=h->GetAxis(4)->GetNbins(); ibin12++){// 2nd lepton
	    for(unsigned int ibin22=1; ibin22<=h->GetAxis(5)->GetNbins(); ibin22++){
	      for(unsigned int ibin32=1; ibin32<=h->GetAxis(6)->GetNbins(); ibin32++){
		for(unsigned int ibin42=1; ibin42<=h->GetAxis(7)->GetNbins(); ibin42++){
		  //
		  for(unsigned int ibin13=1; ibin13<=h->GetAxis(8)->GetNbins(); ibin13++){// 3rd lepton
		    for(unsigned int ibin23=1; ibin23<=h->GetAxis(9)->GetNbins(); ibin23++){
		      for(unsigned int ibin33=1; ibin33<=h->GetAxis(10)->GetNbins(); ibin33++){
			for(unsigned int ibin43=1; ibin43<=h->GetAxis(11)->GetNbins(); ibin43++){
			  //
			  int ibin[12]={ (int)ibin11, (int)ibin21, (int)ibin31, (int)ibin41,
					 (int)ibin12, (int)ibin22, (int)ibin32, (int)ibin42,
					 (int)ibin13, (int)ibin23, (int)ibin33, (int)ibin43  };
			  float fakeBckg;
                          fakeBckg = calculateMatrixEventWeight( (int)leptonType,
                                                                 h->GetAxis( 0)->GetBinCenter(ibin11),  h->GetAxis( 1)->GetBinCenter(ibin21),
                                                                 h->GetAxis( 2)->GetBinCenter(ibin31),  h->GetAxis( 3)->GetBinCenter(ibin41),
                                                                 //
                                                                 h->GetAxis( 4)->GetBinCenter(ibin12),  h->GetAxis( 5)->GetBinCenter(ibin22),
                                                                 h->GetAxis( 6)->GetBinCenter(ibin32),  h->GetAxis( 7)->GetBinCenter(ibin42),
                                                                 //
                                                                 h->GetAxis( 8)->GetBinCenter(ibin13),  h->GetAxis( 9)->GetBinCenter(ibin23),
                                                                 h->GetAxis(10)->GetBinCenter(ibin33),  h->GetAxis(11)->GetBinCenter(ibin43)
                                                                 );
                          h->SetBinContent( ibin, fakeBckg );
                          // debugging >>
                          if(isDebug) printTHnEntry(h,ibin);
                          // debugging <<
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  // done
}

// ----------------------------------------------------------------------------------------------------------------------------

