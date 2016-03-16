#include "RutgersIAF/EventAnalyzer/interface/EventVariableMatrixWeights2D.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableMatrixWeights2D)

void EventVariableMatrixWeights2D::addProduct(TString pname) {
	if(find(m_productnames.begin(), m_productnames.end(), pname) == m_productnames.end()) {
		m_productnames.push_back(pname);
	}
}

bool EventVariableMatrixWeights2D::calculate(BaseHandler* handler) {

  // This calculates and stores matrix method weights (Nff, Nfp, ..., Nll, Nlt, ...)
  // Also stores IsMatrixLep flags

  bool isdebug=false;

  //debugging
  if(isdebug){
    std::cout<<std::endl;
    std::cout<<"-----------"<<std::endl;
    for(int i = 0; i < (int)m_productnames.size(); i++) {//loop over all product names added
      vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);// get all objects of a given product name
      for(int j = 0; j < (int)v.size(); j++){//loop over all objects of a given product name
	std::cout<<"m_productname: "<<m_productnames[i]<<"   pT: "<<v[j]->Pt()<<std::endl;
      }
    }
  }//end-debugging


  //need m_loosename, m_tightname

  // Store Tight Leptons
  vector<float> PtVectorTight;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find(m_loosename) != std::string::npos ) continue;//skip loose lepton collections
    for(int j = 0; j < (int)v.size(); j++){
      PtVectorTight.push_back( (float)(v[j]->Pt()) );
    }
  }

  // Get Loose Leptons
  vector<int>    maxPtIndexVector;
  vector<int>    maxPtPNindexVector;//product name index
  vector<float> maxPtVector;
  vector<pair<float,int>> maxPtPairVector;
  //
  int ctr=0;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find(m_tightname) != std::string::npos ) continue;//skip tight lepton collections
    for(int j = 0; j < (int)v.size(); j++){
      v[j]->setVariable(TString::Format("IsMatrixLep%s",m_suffix.Data()), (int)(0));
      //
      maxPtPairVector.push_back( pair<float,int>((float)(v[j]->Pt()),ctr) );//ctr is the total number of matrix lepton objects
      ctr++;
      maxPtVector.push_back( (float)(v[j]->Pt()) );
      maxPtIndexVector.push_back( j );
      maxPtPNindexVector.push_back( i );
    }
  }

  // Sort Loose Leptons by pT, highest pt first
  std::sort(maxPtPairVector.rbegin(), maxPtPairVector.rend());


  // Define 2 Matrix Lepton vectors
  TLorentzVector v1;
  TLorentzVector v2;


  // Define Matrix lepton type
  int LeptonType[2]={0};//1-ele, 2-mu, 3-tau.


  // If event has at least 2 loose matrix leptons, for/using the leading pt 2 leptons do the following:
  // - Store loose lepton types
  // - Mark loose leptons 
  // - Calculate Fake/Prompt rates
  // - Calculate event type 
  if( maxPtVector.size()>=2 ){
    int LeptonCtr=0;
    for(std::vector< pair<float,int> >::iterator it = maxPtPairVector.begin(); it != maxPtPairVector.end(); ++it){
      LeptonCtr++;
      vector<SignatureObject*> lepvec = handler->getProduct(m_productnames[maxPtPNindexVector.at(it->second)]);
      lepvec[maxPtIndexVector.at(it->second)]->setVariable(TString::Format("IsMatrixLep%s",m_suffix.Data()), (int)(1));//set flags for matrix leptons
      //
      string prodname = (string)(m_productnames[maxPtPNindexVector.at(it->second)]);
      if( prodname.find("Electron") != std::string::npos ) LeptonType[LeptonCtr-1]=1; 
      if( prodname.find("Muon")     != std::string::npos ) LeptonType[LeptonCtr-1]=2; 
      if( prodname.find("Tau")      != std::string::npos ) LeptonType[LeptonCtr-1]=3; 
      //
      float lepvecpt  = (float)(lepvec[maxPtIndexVector.at(it->second)]->Pt());
      float lepveceta = (float)(lepvec[maxPtIndexVector.at(it->second)]->Eta());
      float lepvecphi = (float)(lepvec[maxPtIndexVector.at(it->second)]->Phi());
      if( LeptonCtr==1 ){ v1.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==2 ){ v2.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==2 ) break;
    }
    //
    //check if 2 vector objects are tight:
    int LTint=0;
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), (float)(v1.Pt())) != PtVectorTight.end()) LTint += 10;// Is 1st lepton tight?
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), (float)(v2.Pt())) != PtVectorTight.end()) LTint +=  1;// Is 2nd lepton tight?
    //
    //
    if(isdebug){
      for(unsigned int k=0; k<PtVectorTight.size(); k++){ cout<<"PtVectorTight.at("<<k<<"): "<<PtVectorTight.at(k)<<endl; }
      if(std::find(PtVectorTight.begin(), PtVectorTight.end(), (float)(v1.Pt())) != PtVectorTight.end()) cout<<"v1.Pt(): "<<v1.Pt()<<"  found!"<<endl;
      if(std::find(PtVectorTight.begin(), PtVectorTight.end(), (float)(v2.Pt())) != PtVectorTight.end()) cout<<"v2.Pt(): "<<v2.Pt()<<"  found!"<<endl;
      cout<<"LTint: "<<LTint<<endl;
      cout<<"v1.Pt(): "<<v1.Pt()<<endl;
      cout<<"v2.Pt(): "<<v2.Pt()<<endl;
    }
    //
    //
    //  bit1, bit0  -  Rightmost digit is 2nd lepton
    ResetLooseTight();
    if( LTint==11 ) nTT=1;
    if( LTint==10 ) nTL=1;
    if( LTint== 1 ) nLT=1;
    if( LTint== 0 ) nLL=1;
    //
    // Store event type variables:
    handler->setVariable( TString::Format("nLL%s", m_suffix.Data()), nLL );//    no T
    handler->setVariable( TString::Format("nLT%s", m_suffix.Data()), nLT );//single T
    handler->setVariable( TString::Format("nTL%s", m_suffix.Data()), nTL );//single T
    handler->setVariable( TString::Format("nTT%s", m_suffix.Data()), nTT );//triple T
    //
    //
    // Store central weights (both components and the final fake-bckg weight)
    SetFakePromptRates( v1, v2, LeptonType, "CENTRAL" );
    handler->setVariable( TString::Format("Wff%s",       m_suffix.Data()), Wff()       );// double fake
    handler->setVariable( TString::Format("Wfp%s",       m_suffix.Data()), Wfp()       );// single fake
    handler->setVariable( TString::Format("Wpf%s",       m_suffix.Data()), Wpf()       );// single fake
    handler->setVariable( TString::Format("Wpp%s",       m_suffix.Data()), Wpp()       );//     no fake
    handler->setVariable( TString::Format("WfakeBckg%s", m_suffix.Data()), WfakeBckg() );//  total fake
    //
    // Store variation weights (just the final fake-bckg weights)
    //  We need p/f systematics as well (12 new WfakeBckg values, one for each muon,electron,tau P/F rate variation):
    SetFakePromptRates( v1, v2, LeptonType, "PEU" );
    handler->setVariable( TString::Format("WfakeBckgPEU%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Ele Up
    SetFakePromptRates( v1, v2, LeptonType, "FEU" );
    handler->setVariable( TString::Format("WfakeBckgFEU%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake Ele Up
    SetFakePromptRates( v1, v2, LeptonType, "PMU" );
    handler->setVariable( TString::Format("WfakeBckgPMU%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt  Mu Up
    SetFakePromptRates( v1, v2, LeptonType, "FMU" );
    handler->setVariable( TString::Format("WfakeBckgFMU%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake  Mu Up
    SetFakePromptRates( v1, v2, LeptonType, "PTU" );
    handler->setVariable( TString::Format("WfakeBckgPTU%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Tau Up
    SetFakePromptRates( v1, v2, LeptonType, "FTU" );
    handler->setVariable( TString::Format("WfakeBckgFTU%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake Tau Up
    SetFakePromptRates( v1, v2, LeptonType, "PED" );
    handler->setVariable( TString::Format("WfakeBckgPED%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Ele Down
    SetFakePromptRates( v1, v2, LeptonType, "FED" );
    handler->setVariable( TString::Format("WfakeBckgFED%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake Ele Down
    SetFakePromptRates( v1, v2, LeptonType, "PMD" );
    handler->setVariable( TString::Format("WfakeBckgPMD%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt  Mu Down
    SetFakePromptRates( v1, v2, LeptonType, "FMD" );
    handler->setVariable( TString::Format("WfakeBckgFMD%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake  Mu Down
    SetFakePromptRates( v1, v2, LeptonType, "PTD" );
    handler->setVariable( TString::Format("WfakeBckgPTD%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Tau Down
    SetFakePromptRates( v1, v2, LeptonType, "FTD" );
    handler->setVariable( TString::Format("WfakeBckgFTD%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake Tau Down
    //
  } else setVariablesToZero(handler);


  //debugging
  if(isdebug){
    for(std::vector< pair<float,int> >::iterator it = maxPtPairVector.begin(); it != maxPtPairVector.end(); ++it){
      vector<SignatureObject*> lepvec = handler->getProduct(m_productnames[maxPtPNindexVector.at(it->second)]);
      //
      std::cout<<"      Pt1: "<< lepvec[maxPtIndexVector.at(it->second)]->Pt();
      //std::cout<<"      Pt2: "<< maxPtVector.at(it->second);
      std::cout<<" prodName: "<< m_productnames[maxPtPNindexVector.at(it->second)] <<std::endl; 
    }
    std::cout<<std::endl;	
    //
    if( maxPtVector.size()>=2 ){
      SetFakePromptRates( v1, v2, LeptonType, "CENTRAL" );
      std::cout<<"Prompt1: "<< p1<<std::endl;
      std::cout<<"Prompt2: "<< p2<<std::endl;
      std::cout<<"  Fake1: "<< f1<<std::endl;
      std::cout<<"  Fake2: "<< f2<<std::endl;
      std::cout<<"Vec1 Pt: "<<v1.Pt()<<std::endl;
      std::cout<<"Vec2 Pt: "<<v2.Pt()<<std::endl;
      std::cout<<"LeptonType[0]: "<<LeptonType[0]<<std::endl;
      std::cout<<"LeptonType[1]: "<<LeptonType[1]<<std::endl;
      std::cout<<"nLL: "<<nLL<<std::endl;
      std::cout<<"nLT: "<<nLT<<std::endl;
      std::cout<<"nTL: "<<nTL<<std::endl;
      std::cout<<"nTT: "<<nTT<<std::endl;
      std::cout<<" -- -- "<<std::endl;
      std::cout<<"Wff: "<< Wff()<<std::endl;
      std::cout<<"Wfp: "<< Wfp()<<std::endl;
      std::cout<<"Wpf: "<< Wpf()<<std::endl;
      std::cout<<"Wpp: "<< Wpp()<<std::endl;
      std::cout<<"WfakeBckg: "<<WfakeBckg()<<std::endl;
    }
  }//end-debugging
  
  return true;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights2D::SetFakePromptRates( TLorentzVector v1, TLorentzVector v2, int LeptonType[2], TString var ){
  //
  ResetFakePromptRates();
  //
  float pt1=(float)(v1.Pt()); float eta1=(float)(v1.Eta()); 
  float pt2=(float)(v2.Pt()); float eta2=(float)(v2.Eta());  
  //
  TString varPE, varFE, varPM, varFM, varPT, varFT;// These are PromptEle variation, FakeEle variation, PromptMuon variation, etc.
  //
  if(     var=="CENTRAL"){ varPE="central"; varFE="central"; varPM="central"; varFM="central"; varPT="central"; varFT="central"; }// Central
  else if(var=="PEU"    ){ varPE="up";      varFE="central"; varPM="central"; varFM="central"; varPT="central"; varFT="central"; }// Ups
  else if(var=="FEU"    ){ varPE="central"; varFE="up";      varPM="central"; varFM="central"; varPT="central"; varFT="central"; } 
  else if(var=="PMU"    ){ varPE="central"; varFE="central"; varPM="up";      varFM="central"; varPT="central"; varFT="central"; }
  else if(var=="FMU"    ){ varPE="central"; varFE="central"; varPM="central"; varFM="up";      varPT="central"; varFT="central"; }
  else if(var=="PTU"    ){ varPE="central"; varFE="central"; varPM="central"; varFM="central"; varPT="up";      varFT="central"; }
  else if(var=="FTU"    ){ varPE="central"; varFE="central"; varPM="central"; varFM="central"; varPT="central"; varFT="up";      }
  else if(var=="PED"    ){ varPE="down";    varFE="central"; varPM="central"; varFM="central"; varPT="central"; varFT="central"; }// Downs
  else if(var=="FED"    ){ varPE="central"; varFE="down";    varPM="central"; varFM="central"; varPT="central"; varFT="central"; }
  else if(var=="PMD"    ){ varPE="central"; varFE="central"; varPM="down";    varFM="central"; varPT="central"; varFT="central"; }
  else if(var=="FMD"    ){ varPE="central"; varFE="central"; varPM="central"; varFM="down";    varPT="central"; varFT="central"; }
  else if(var=="PTD"    ){ varPE="central"; varFE="central"; varPM="central"; varFM="central"; varPT="down";    varFT="central"; }
  else if(var=="FTD"    ){ varPE="central"; varFE="central"; varPM="central"; varFM="central"; varPT="central"; varFT="down";    }
  else{ 
    cout<<"\nWARNING: Invalid *var* value is provided in EventVariableMatrixWeights2D::SetFakePromptRates, switching to *CENTRAL* values!\n"<<endl;
    varPE="central"; varFE="central"; varPM="central"; varFM="central"; varPT="central"; varFT="central"; 
  }

  //
  if( LeptonType[0]==1 ){ p1=eP(pt1,eta1,0,varPE); f1=eF(pt1,eta1,0,varFE); }//1st lepton
  if( LeptonType[0]==2 ){ p1=mP(pt1,eta1,0,varPM); f1=mF(pt1,eta1,0,varFM); }
  if( LeptonType[0]==3 ){ p1=tP(pt1,eta1,0,varPT); f1=tF(pt1,eta1,0,varFT); }
  //
  if( LeptonType[1]==1 ){ p2=eP(pt2,eta2,0,varPE); f2=eF(pt2,eta2,0,varFE); }//2nd lepton
  if( LeptonType[1]==2 ){ p2=mP(pt2,eta2,0,varPM); f2=mF(pt2,eta2,0,varFM); }
  if( LeptonType[1]==3 ){ p2=tP(pt2,eta2,0,varPT); f2=tF(pt2,eta2,0,varFT); }
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights2D::ResetFakePromptRates(){
  p1=0;  p2=0; 
  f1=0;  f2=0;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights2D::ResetLooseTight(){
  nLL=0;
  nLT=0;
  nTL=0;
  nTT=0;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

float EventVariableMatrixWeights2D::mF( float pt, float eta, float njet, TString var ){
  float uncU=0;
  float uncD=0;
  if(      pt < 10 ){ uncU = 0;      uncD = 0;     }
  else if( pt < 20 ){ uncU = 0.002;  uncD = 0.002; }
  else if( pt < 40 ){ uncU = 0.003;  uncD = 0.004; }
  else if( pt < 70 ){ uncU = 0.007;  uncD = 0.007; }
  else if( pt <100 ){ uncU = 0.020;  uncD = 0.020; }
  else if( pt <150 ){ uncU = 0.050;  uncD = 0.050; }
  else{               uncU = 0.100;  uncD = 0.100; }
  //
  float central=0;
  if(      pt < 10 ) central = 0;
  else if( pt < 20 ) central = 0.014;
  else if( pt < 40 ) central = 0.008;
  else if( pt < 70 ) central = 0.014;
  else if( pt <100 ) central = 0.040;
  else               central = 0.100;
  //
  float unc=0;
  if(var=="up"     ) unc = uncU;
  if(var=="down"   ) unc = uncD;
  if(var=="central") unc = 0;
  //
  return central+unc;
}

float EventVariableMatrixWeights2D::mP( float pt, float eta, float njet, TString var ){
  float uncU=0;
  float uncD=0;
  if(      pt < 10 ){ uncU = 0;     uncD = 0;    }
  else if( pt < 15 ){ uncU = 0.08;  uncD = 0.08; }
  else if( pt < 20 ){ uncU = 0.05;  uncD = 0.05; }
  else if( pt < 30 ){ uncU = 0.04;  uncD = 0.04; }
  else if( pt < 40 ){ uncU = 0.03;  uncD = 0.03; }
  else if( pt < 50 ){ uncU = 0.01;  uncD = 0.01; }
  else{               uncU = 0.00;  uncD = 0.01; }
  //
  float central=0;
  if(      pt < 10 ) central = 0;
  else if( pt < 15 ) central = 0.83;
  else if( pt < 20 ) central = 0.90;
  else if( pt < 30 ) central = 0.94;
  else if( pt < 40 ) central = 0.97;
  else if( pt < 50 ) central = 0.99;
  else               central = 1.00;
  //
  float unc=0;
  if(var=="up"     ) unc = uncU;
  if(var=="down"   ) unc = uncD;
  if(var=="central") unc = 0;
  //
  return central+unc;
}

float EventVariableMatrixWeights2D::eF( float pt, float eta, float njet, TString var ){
  float uncU=0;
  float uncD=0;
  if(      pt < 10 ){ uncU = 0;     uncD = 0;    }
  else if( pt < 30 ){ uncU = 0.03;  uncD = 0.03; }
  else if( pt <150 ){ uncU = 0.08;  uncD = 0.05; }
  else{               uncU = 0.05;  uncD = 0.05; }
  //
  float central=0;
  if(      pt < 10 ) central = 0;
  else if( pt < 30 ) central = 0.07;
  else if( pt <150 ) central = 0.12;
  else               central = 0.25;
  //
  float unc=0;
  if(var=="up"     ) unc = uncU;
  if(var=="down"   ) unc = uncD;
  if(var=="central") unc = 0;
  //
  return central+unc;
}

float EventVariableMatrixWeights2D::eP( float pt, float eta, float njet, TString var ){
  float uncU=0;
  float uncD=0;
  if(      pt < 10 ){ uncU = 0;     uncD = 0;    }
  else if( pt < 15 ){ uncU = 0.10;  uncD = 0.10; }
  else if( pt < 20 ){ uncU = 0.07;  uncD = 0.07; }
  else if( pt < 30 ){ uncU = 0.05;  uncD = 0.05; }
  else if( pt < 40 ){ uncU = 0.03;  uncD = 0.03; }
  else if( pt < 50 ){ uncU = 0.03;  uncD = 0.03; }
  else if( pt < 70 ){ uncU = 0.03;  uncD = 0.03; }
  else{               uncU = 0.00;  uncD = 0.05; }
  //
  float central=0;
  if(      pt < 10 ) central = 0;
  else if( pt < 15 ) central = 0.65;
  else if( pt < 20 ) central = 0.75;
  else if( pt < 30 ) central = 0.82;
  else if( pt < 40 ) central = 0.87;
  else if( pt < 50 ) central = 0.90;
  else if( pt < 70 ) central = 0.95;
  else               central = 1.00;
  //
  float unc=0;
  if(var=="up"     ) unc = uncU;
  if(var=="down"   ) unc = uncD;
  if(var=="central") unc = 0;
  //
  return central+unc;
}

float EventVariableMatrixWeights2D::tF( float pt, float eta, float njet, TString var ){
  float uncU=0;
  float uncD=0;
  if(      pt < 20 ){ uncU = 0;     uncD = 0;    }
  else if( pt < 40 ){ uncU = 0.05;  uncD = 0.05; }
  else if( pt <150 ){ uncU = 0.05;  uncD = 0.05; }
  else{               uncU = 0.05;  uncD = 0.05; }
  //
  float central=0;
  if(      pt < 20 ) central = 0;
  else if( pt < 40 ) central = 0.25;
  else if( pt <150 ) central = 0.20;
  else               central = 0.30;
  //
  float unc=0;
  if(var=="up"     ) unc = uncU;
  if(var=="down"   ) unc = uncD;
  if(var=="central") unc = 0;
  //
  return central+unc;
}

float EventVariableMatrixWeights2D::tP( float pt, float eta, float njet, TString var ){
  float uncU=0;
  float uncD=0;
  if(      pt < 20 ){ uncU = 0;     uncD = 0;    }
  else if( pt < 25 ){ uncU = 0.05;  uncD = 0.05; }
  else if( pt < 50 ){ uncU = 0.05;  uncD = 0.05; }
  else{               uncU = 0.05;  uncD = 0.05; }
  //
  float central=0;
  if(      pt < 20 ) central = 0;
  else if( pt < 25 ) central = 0.75;
  else if( pt < 50 ) central = 0.85;
  else               central = 0.95;
  //
  float unc=0;
  if(var=="up"     ) unc = uncU;
  if(var=="down"   ) unc = uncD;
  if(var=="central") unc = 0;
  //
  return central+unc;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

float EventVariableMatrixWeights2D::WfakeBckg( ){
  float fakeBckg = Wff()+Wfp()+Wpf();
  return fakeBckg;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

float EventVariableMatrixWeights2D::Wff( ){
  float wff_ = (f1*f2)*(
                         nLL*( p1*p2        )+
                         nLT*(-p1*(1-p2)    )+
                         nTL*(-(1-p1)*p2    )+
                         nTT*( (1-p1)*(1-p2))
                         )/((p1-f1)*(p2-f2));
  //
  return wff_;
}

float EventVariableMatrixWeights2D::Wfp( ){
  float wfp_ = (f1*p2)*(
                         nLL*(-p1*f2        )+
                         nLT*( p1*(1-f2)    )+
                         nTL*( (1-p1)*f2    )+
                         nTT*(-(1-p1)*(1-f2))
                         )/((p1-f1)*(p2-f2));
  //
  return wfp_;
}

float EventVariableMatrixWeights2D::Wpf( ){
  float wpf_ = (p1*f2)*(
                         nLL*(-f1*p2        )+
                         nLT*( f1*(1-p2)    )+
                         nTL*( (1-f1)*p2    )+
                         nTT*(-(1-f1)*(1-p2))
                         )/((p1-f1)*(p2-f2));
  //
  return wpf_;
}

float EventVariableMatrixWeights2D::Wpp( ){
  float wpp_ = (p1*p2)*(
                         nLL*( f1*f2        )+
                         nLT*(-f1*(1-f2)    )+
                         nTL*(-(1-f1)*f2    )+
                         nTT*( (1-f1)*(1-f2))
                         )/((p1-f1)*(p2-f2));
  //
  return wpp_;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights2D::setVariablesToZero(BaseHandler* handler){ 
  handler->setVariable( TString::Format("nLL%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nLT%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nTL%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nTT%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wff%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wfp%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wpf%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wpp%s",           m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckg%s",     m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgPEU%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgFEU%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgPMU%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgFMU%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgPTU%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgFTU%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgPED%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgFED%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgPMD%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgFMD%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgPTD%s",  m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("WfakeBckgFTD%s",  m_suffix.Data()), (float)(0) );
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

