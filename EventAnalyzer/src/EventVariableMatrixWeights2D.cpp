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

  // This calculates and stores matrix method weights (Nfff, Nffp, ..., Nlll, Nllt, ...)
  // Also stores IsMatrixLep flags

  bool isdebug=true;

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
  vector<double> PtVectorTight;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find(m_loosename) != std::string::npos ) continue;
    for(int j = 0; j < (int)v.size(); j++){
      PtVectorTight.push_back( v[j]->Pt() );
    }
  }

  // Get Loose Leptons
  vector<int>    maxPtIndexVector;
  vector<int>    maxPtPNindexVector;//product name index
  vector<double> maxPtVector;
  vector<pair<double,int>> maxPtPairVector;
  //
  int ctr=0;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find(m_tightname) != std::string::npos ) continue;//skip tight lepton collections
    for(int j = 0; j < (int)v.size(); j++){
      v[j]->setVariable(TString::Format("IsMatrixLep%s",m_suffix.Data()), (int)(0));
      //
      maxPtPairVector.push_back( pair<double,int>(v[j]->Pt(),ctr) );//ctr is the total number of matrix lepton objects
      ctr++;
      maxPtVector.push_back( v[j]->Pt() );
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


  setVariablesToZero(handler);
  // If event has at least 2 loose matrix leptons, for/using the leading pt 2 leptons do the following:
  // - Store loose lepton types
  // - Mark loose leptons 
  // - Calculate Fake/Prompt rates
  // - Calculate event type 
  if( maxPtVector.size()>=2 ){
    int LeptonCtr=0;
    for(std::vector< pair<double,int> >::iterator it = maxPtPairVector.begin(); it != maxPtPairVector.end(); ++it){
      LeptonCtr++;
      vector<SignatureObject*> lepvec = handler->getProduct(m_productnames[maxPtPNindexVector.at(it->second)]);
      lepvec[maxPtIndexVector.at(it->second)]->setVariable(TString::Format("IsMatrixLep%s",m_suffix.Data()), (int)(1));//set flags for matrix leptons
      //
      string prodname = (string)(m_productnames[maxPtPNindexVector.at(it->second)]);
      if( prodname.find("Electron") != std::string::npos ) LeptonType[LeptonCtr-1]=1; 
      if( prodname.find("Muon")     != std::string::npos ) LeptonType[LeptonCtr-1]=2; 
      if( prodname.find("Tau")      != std::string::npos ) LeptonType[LeptonCtr-1]=3; 
      //
      double lepvecpt  = lepvec[maxPtIndexVector.at(it->second)]->Pt();
      double lepveceta = lepvec[maxPtIndexVector.at(it->second)]->Eta();
      double lepvecphi = lepvec[maxPtIndexVector.at(it->second)]->Phi();
      if( LeptonCtr==1 ){ v1.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==2 ){ v2.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==2 ) break;
    }
    //
    //check if 2 vector objects are tight:
    int LTint=0;
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), v1.Pt()) != PtVectorTight.end()) LTint += 10;// Is 1st lepton tight?
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), v2.Pt()) != PtVectorTight.end()) LTint +=  1;// Is 2nd lepton tight?
    //
    //  bit1, bit0  -  Rightmost digit is 2nd lepton
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
    ResetLooseTight();
    ResetFakePromptRates();
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
  }


  //debugging
  if(isdebug){
    for(std::vector< pair<double,int> >::iterator it = maxPtPairVector.begin(); it != maxPtPairVector.end(); ++it){
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
  double pt1=v1.Pt(); double eta1=v1.Eta(); 
  double pt2=v2.Pt(); double eta2=v2.Eta();  
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

double EventVariableMatrixWeights2D::mF( double pt, double eta, double njet, TString var ){
  double unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.1+unc;  
}

double EventVariableMatrixWeights2D::mP( double pt, double eta, double njet, TString var ){
  double unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.95+unc;  
}

double EventVariableMatrixWeights2D::eF( double pt, double eta, double njet, TString var ){
  double unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.2+unc;  
}

double EventVariableMatrixWeights2D::eP( double pt, double eta, double njet, TString var ){
  double unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.90+unc;  
}

double EventVariableMatrixWeights2D::tF( double pt, double eta, double njet, TString var ){
  double unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.25+unc;
}

double EventVariableMatrixWeights2D::tP( double pt, double eta, double njet, TString var ){
  double unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.85+unc;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

double EventVariableMatrixWeights2D::WfakeBckg( ){
  double fakeBckg = Wff()+Wfp()+Wpf();
  return fakeBckg;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

double EventVariableMatrixWeights2D::Wff( ){
  double wff_ = (f1*f2)*(
                         nLL*( p1*p2        )+
                         nLT*(-p1*(1-p2)    )+
                         nTL*(-(1-p1)*p2    )+
                         nTT*( (1-p1)*(1-p2))
                         )/((p1-f1)*(p2-f2));
  //
  return wff_;
}

double EventVariableMatrixWeights2D::Wfp( ){
  double wfp_ = (f1*p2)*(
                         nLL*(-p1*f2        )+
                         nLT*( p1*(1-f2)    )+
                         nTL*( (1-p1)*f2    )+
                         nTT*(-(1-p1)*(1-f2))
                         )/((p1-f1)*(p2-f2));
  //
  return wfp_;
}

double EventVariableMatrixWeights2D::Wpf( ){
  double wpf_ = (p1*f2)*(
                         nLL*(-f1*p2        )+
                         nLT*( f1*(1-p2)    )+
                         nTL*( (1-f1)*p2    )+
                         nTT*(-(1-f1)*(1-p2))
                         )/((p1-f1)*(p2-f2));
  //
  return wpf_;
}

double EventVariableMatrixWeights2D::Wpp( ){
  double wpp_ = (p1*p2)*(
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
  handler->setVariable( TString::Format("Wff%s",           m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("Wfp%s",           m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("Wpf%s",           m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("Wpp%s",           m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckg%s",     m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgPEU%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgFEU%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgPMU%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgFMU%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgPTU%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgFTU%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgPED%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgFED%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgPMD%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgFMD%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgPTD%s",  m_suffix.Data()), 0 );
  handler->setVariable( TString::Format("WfakeBckgFTD%s",  m_suffix.Data()), 0 );
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

