#include "RutgersIAF/EventAnalyzer/interface/EventVariableMatrixWeights3D.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableMatrixWeights3D)

void EventVariableMatrixWeights3D::addProduct(TString pname) {
	if(find(m_productnames.begin(), m_productnames.end(), pname) == m_productnames.end()) {
		m_productnames.push_back(pname);
	}
}

bool EventVariableMatrixWeights3D::calculate(BaseHandler* handler) {

  // This calculates and stores matrix method weights (Nfff, Nffp, ..., Nlll, Nllt, ...)
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
    if( prodname.find(m_loosename) != std::string::npos ) continue;
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


  // Define 3 Matrix Lepton vectors
  TLorentzVector v1;
  TLorentzVector v2;
  TLorentzVector v3;


  // Define Matrix lepton type
  int LeptonType[3]={0};//1-ele, 2-mu, 3-tau.


  // If event has at least 3 loose matrix leptons, for/using the leading pt 3 leptons do the following:
  // - Store loose lepton types
  // - Mark loose leptons 
  // - Calculate Fake/Prompt rates
  // - Calculate event type 
  if( maxPtVector.size()>=3 ){
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
      if( LeptonCtr==3 ){ v3.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==3 ) break;
    }
    //
    //check if 3 vector objects are tight:
    int LTint=0;
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), (float)(v1.Pt())) != PtVectorTight.end()) LTint += 100;// Is 1st lepton tight?
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), (float)(v2.Pt())) != PtVectorTight.end()) LTint +=  10;// Is 2nd lepton tight?
    if(std::find(PtVectorTight.begin(), PtVectorTight.end(), (float)(v3.Pt())) != PtVectorTight.end()) LTint +=   1;// Is 3rd lepton tight?
    //
    //  bit2, bit1, bit0  -  Rightmost digit is 3rd lepton
    ResetLooseTight();
    if( LTint==111 ) nTTT=1;
    if( LTint==110 ) nTTL=1;
    if( LTint==101 ) nTLT=1;
    if( LTint== 11 ) nLTT=1;
    if( LTint==100 ) nTLL=1;
    if( LTint==010 ) nLTL=1;
    if( LTint==  1 ) nLLT=1;
    if( LTint==  0 ) nLLL=1;
    //
    // Store event type variables:
    handler->setVariable( TString::Format("nLLL%s", m_suffix.Data()), nLLL );//    no T
    handler->setVariable( TString::Format("nLLT%s", m_suffix.Data()), nLLT );//single T
    handler->setVariable( TString::Format("nLTL%s", m_suffix.Data()), nLTL );//single T
    handler->setVariable( TString::Format("nTLL%s", m_suffix.Data()), nTLL );//single T
    handler->setVariable( TString::Format("nLTT%s", m_suffix.Data()), nLTT );//double T
    handler->setVariable( TString::Format("nTLT%s", m_suffix.Data()), nTLT );//double T
    handler->setVariable( TString::Format("nTTL%s", m_suffix.Data()), nTTL );//double T
    handler->setVariable( TString::Format("nTTT%s", m_suffix.Data()), nTTT );//triple T
    //
    //
    //
    // Store central weights (both components and the final fake-bckg weight)
    SetFakePromptRates( v1, v2, v3, LeptonType, "CENTRAL" );
    handler->setVariable( TString::Format("Wfff%s",      m_suffix.Data()), Wfff()      );//triple fake
    handler->setVariable( TString::Format("Wffp%s",      m_suffix.Data()), Wffp()      );//double fake
    handler->setVariable( TString::Format("Wfpf%s",      m_suffix.Data()), Wfpf()      );//double fake
    handler->setVariable( TString::Format("Wpff%s",      m_suffix.Data()), Wpff()      );//double fake
    handler->setVariable( TString::Format("Wfpp%s",      m_suffix.Data()), Wfpp()      );//single fake
    handler->setVariable( TString::Format("Wpfp%s",      m_suffix.Data()), Wpfp()      );//single fake
    handler->setVariable( TString::Format("Wppf%s",      m_suffix.Data()), Wppf()      );//single fake
    handler->setVariable( TString::Format("Wppp%s",      m_suffix.Data()), Wppp()      );//    no fake
    handler->setVariable( TString::Format("WfakeBckg%s", m_suffix.Data()), WfakeBckg() );// total fake
    //
    // Store variation weights (just the final fake-bckg weights)
    //  We need p/f systematics as well (12 new WfakeBckg values, one for each muon,electron,tau P/F rate variation):
    SetFakePromptRates( v1, v2, v3, LeptonType, "PEU" );
    handler->setVariable( TString::Format("WfakeBckgPEU%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Ele Up
    SetFakePromptRates( v1, v2, v3, LeptonType, "FEU" );
    handler->setVariable( TString::Format("WfakeBckgFEU%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake Ele Up
    SetFakePromptRates( v1, v2, v3, LeptonType, "PMU" );
    handler->setVariable( TString::Format("WfakeBckgPMU%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt  Mu Up
    SetFakePromptRates( v1, v2, v3, LeptonType, "FMU" );
    handler->setVariable( TString::Format("WfakeBckgFMU%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake  Mu Up
    SetFakePromptRates( v1, v2, v3, LeptonType, "PTU" );
    handler->setVariable( TString::Format("WfakeBckgPTU%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Tau Up
    SetFakePromptRates( v1, v2, v3, LeptonType, "FTU" );
    handler->setVariable( TString::Format("WfakeBckgFTU%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake Tau Up
    SetFakePromptRates( v1, v2, v3, LeptonType, "PED" );
    handler->setVariable( TString::Format("WfakeBckgPED%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Ele Down
    SetFakePromptRates( v1, v2, v3, LeptonType, "FED" );
    handler->setVariable( TString::Format("WfakeBckgFED%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake Ele Down
    SetFakePromptRates( v1, v2, v3, LeptonType, "PMD" );
    handler->setVariable( TString::Format("WfakeBckgPMD%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt  Mu Down
    SetFakePromptRates( v1, v2, v3, LeptonType, "FMD" );
    handler->setVariable( TString::Format("WfakeBckgFMD%s",  m_suffix.Data()), WfakeBckg() );// total fake    Fake  Mu Down
    SetFakePromptRates( v1, v2, v3, LeptonType, "PTD" );
    handler->setVariable( TString::Format("WfakeBckgPTD%s",  m_suffix.Data()), WfakeBckg() );// total fake  Prompt Tau Down
    SetFakePromptRates( v1, v2, v3, LeptonType, "FTD" );
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
    if( maxPtVector.size()>=3 ){
      SetFakePromptRates( v1, v2, v3, LeptonType, "CENTRAL" );
      std::cout<<"Prompt1: "<< p1<<std::endl;
      std::cout<<"Prompt2: "<< p2<<std::endl;
      std::cout<<"Prompt3: "<< p3<<std::endl;
      std::cout<<"  Fake1: "<< f1<<std::endl;
      std::cout<<"  Fake2: "<< f2<<std::endl;
      std::cout<<"  Fake3: "<< f3<<std::endl;
      std::cout<<"Vec1 Pt: "<<v1.Pt()<<std::endl;
      std::cout<<"Vec2 Pt: "<<v2.Pt()<<std::endl;
      std::cout<<"Vec3 Pt: "<<v3.Pt()<<std::endl;
      std::cout<<"LeptonType[0]: "<<LeptonType[0]<<std::endl;
      std::cout<<"LeptonType[1]: "<<LeptonType[1]<<std::endl;
      std::cout<<"LeptonType[2]: "<<LeptonType[2]<<std::endl;
      std::cout<<"nLLL: "<<nLLL<<std::endl;
      std::cout<<"nLLT: "<<nLLT<<std::endl;
      std::cout<<"nLTL: "<<nLTL<<std::endl;
      std::cout<<"nTLL: "<<nTLL<<std::endl;
      std::cout<<"nLTT: "<<nLTT<<std::endl;
      std::cout<<"nTLT: "<<nTLT<<std::endl;
      std::cout<<"nTTL: "<<nTTL<<std::endl;
      std::cout<<"nTTT: "<<nTTT<<std::endl;
      std::cout<<" -- -- "<<std::endl;
      std::cout<<"Wfff: "<< Wfff()<<std::endl;
      std::cout<<"Wffp: "<< Wffp()<<std::endl;
      std::cout<<"Wfpf: "<< Wfpf()<<std::endl;
      std::cout<<"Wpff: "<< Wpff()<<std::endl;
      std::cout<<"Wfpp: "<< Wfpp()<<std::endl;
      std::cout<<"Wpfp: "<< Wpfp()<<std::endl;
      std::cout<<"Wppf: "<< Wppf()<<std::endl;
      std::cout<<"Wppp: "<< Wppp()<<std::endl;
      std::cout<<"WfakeBckg: "<<WfakeBckg()<<std::endl;
    }
  }//end-debugging
  
  return true;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights3D::SetFakePromptRates( TLorentzVector v1, TLorentzVector v2, TLorentzVector v3, int LeptonType[3], TString var ){
  //
  ResetFakePromptRates();
  //
  float pt1=(float)(v1.Pt()); float eta1=(float)(v1.Eta()); 
  float pt2=(float)(v2.Pt()); float eta2=(float)(v2.Eta());  
  float pt3=(float)(v3.Pt()); float eta3=(float)(v3.Eta());  
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
    cout<<"\nWARNING: Invalid *var* value is provided in EventVariableMatrixWeights3D::SetFakePromptRates, switching to *CENTRAL* values!\n"<<endl;
    varPE="central"; varFE="central"; varPM="central"; varFM="central"; varPT="central"; varFT="central"; 
  }

  //
  if( LeptonType[0]==1 ){ p1=eP(pt1,eta1,0,varPE); f1=eF(pt1,eta1,0,varFE); }
  if( LeptonType[0]==2 ){ p1=mP(pt1,eta1,0,varPM); f1=mF(pt1,eta1,0,varFM); }
  if( LeptonType[0]==3 ){ p1=tP(pt1,eta1,0,varPT); f1=tF(pt1,eta1,0,varFT); }
  //
  if( LeptonType[1]==1 ){ p2=eP(pt2,eta2,0,varPE); f2=eF(pt2,eta2,0,varFE); }
  if( LeptonType[1]==2 ){ p2=mP(pt2,eta2,0,varPM); f2=mF(pt2,eta2,0,varFM); }
  if( LeptonType[1]==3 ){ p2=tP(pt2,eta2,0,varPT); f2=tF(pt2,eta2,0,varFT); }
  //
  if( LeptonType[2]==1 ){ p3=eP(pt3,eta3,0,varPE); f3=eF(pt3,eta3,0,varFE); }
  if( LeptonType[2]==2 ){ p3=mP(pt3,eta3,0,varPM); f3=mF(pt3,eta3,0,varFM); }
  if( LeptonType[2]==3 ){ p3=tP(pt3,eta3,0,varPT); f3=tF(pt3,eta3,0,varFT); }
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights3D::ResetFakePromptRates(){
  p1=0;  p2=0;  p3=0;
  f1=0;  f2=0;  f3=0;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights3D::ResetLooseTight(){
  nLLL=0;
  nLLT=0, nLTL=0, nTLL=0;
  nLTT=0, nTLT=0, nTTL=0;
  nTTT=0;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

float EventVariableMatrixWeights3D::mF( float pt, float eta, float njet, TString var ){
  float unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.1+unc;  
}

float EventVariableMatrixWeights3D::mP( float pt, float eta, float njet, TString var ){
  float unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.95+unc;  
}

float EventVariableMatrixWeights3D::eF( float pt, float eta, float njet, TString var ){
  float unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.2+unc;  
}

float EventVariableMatrixWeights3D::eP( float pt, float eta, float njet, TString var ){
  float unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.90+unc;  
}

float EventVariableMatrixWeights3D::tF( float pt, float eta, float njet, TString var ){
  float unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.25+unc;
}

float EventVariableMatrixWeights3D::tP( float pt, float eta, float njet, TString var ){
  float unc=0;
  if(var=="up"     ) unc=0;
  if(var=="down"   ) unc=0;
  if(var=="central") unc=0;
  //
  return 0.85+unc;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

float EventVariableMatrixWeights3D::WfakeBckg( ){
  float fakeBckg = Wfff()+Wffp()+Wfpf()+Wpff()+Wfpp()+Wpfp()+Wppf();
  return fakeBckg;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

float EventVariableMatrixWeights3D::Wfff( ){
  float wfff_ = (f1*f2*f3) * ((-(nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3)) - nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) - nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 - nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 - nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p1 + p2 - p1*p2)*pow(f3 - p3,3)*p3 + nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p1 + p3 - p1*p3) + nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p2 + p3 - p2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wfff_;
}

float EventVariableMatrixWeights3D::Wffp( ){
  float wffp_ = (f1*f2*p3) * ((f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wffp_;
}

float EventVariableMatrixWeights3D::Wfpf( ){
  float wfpf_ = (f1*f3*p2) * ((f2*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wfpf_;
}

float EventVariableMatrixWeights3D::Wpff( ){
  float wpff_ = (f2*f3*p1) * ((f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + f1*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + f1*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + (-1 + f1)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + f1*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + (-1 + f1)*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wpff_;
}

float EventVariableMatrixWeights3D::Wfpp( ){
  float wfpp_ = (f1*p2*p3) * ((-(f2*f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)) - f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wfpp_;
}

float EventVariableMatrixWeights3D::Wpfp( ){
  float wpfp_ = (f2*p1*p3) * ((-(f1*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)) - f1*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - f1*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - f1*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wpfp_;
}

float EventVariableMatrixWeights3D::Wppf( ){
  float wppf_ = (f3*p1*p2) * ((-(f1*f2*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3)) - (-1 + f1)*(-1 + f2)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) - f1*f2*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - f1*(-1 + f2)*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - (-1 + f1)*f2*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f1 + f2 - f1*f2)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f1 + p3 - f1*p3) + f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f2 + p3 - f2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wppf_;
}

float EventVariableMatrixWeights3D::Wppp( ){
  float wppp_ = (p1*p2*p3) * ((f1*f2*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wppp_;
}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void EventVariableMatrixWeights3D::setVariablesToZero(BaseHandler* handler){ 
  handler->setVariable( TString::Format("nLLL%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nLLT%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nLTL%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nTLL%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nLTT%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nTLT%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nTTL%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("nTTT%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wfff%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wffp%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wfpf%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wpff%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wfpp%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wpfp%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wppf%s",          m_suffix.Data()), (float)(0) );
  handler->setVariable( TString::Format("Wppp%s",          m_suffix.Data()), (float)(0) );
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
