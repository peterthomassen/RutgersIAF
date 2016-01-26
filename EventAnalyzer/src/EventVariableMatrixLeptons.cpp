#include "RutgersIAF/EventAnalyzer/interface/EventVariableMatrixLeptons.h"
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

using namespace std;

ClassImp(EventVariableMatrixLeptons)

void EventVariableMatrixLeptons::addProduct(TString pname) {
	if(find(m_productnames.begin(), m_productnames.end(), pname) == m_productnames.end()) {
		m_productnames.push_back(pname);
	}
}

bool EventVariableMatrixLeptons::calculate(BaseHandler* handler) {

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



  // Store Tight Leptons
  vector<double> PtVectorTight;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find("loose") != std::string::npos ) continue;
    for(int j = 0; j < (int)v.size(); j++){
      PtVectorTight.push_back( v[j]->Pt() );
    }
  }

  // Get Loose Leptons
  vector<int>    maxPtIndexVector;
  vector<int>    maxPtPNindexVector;
  vector<double> maxPtVector;
  vector<pair<double,int>> maxPtPairVector;
  //
  int ctr=0;
  for(int i = 0; i < (int)m_productnames.size(); i++) {
    vector<SignatureObject*> v = handler->getProduct(m_productnames[i]);
    string prodname = (string)(m_productnames[i]);
    if( prodname.find("good") != std::string::npos ) continue;
    for(int j = 0; j < (int)v.size(); j++){
      v[j]->setVariable("IsMatrixLep", (int)(0));
      //
      maxPtPairVector.push_back( pair<double,int>(v[j]->Pt(),ctr) );
      ctr++;
      maxPtVector.push_back( v[j]->Pt() );
      maxPtIndexVector.push_back( j );
      maxPtPNindexVector.push_back( i );
    }
  }

  // Sort Loose Leptons by pT
  std::sort(maxPtPairVector.rbegin(), maxPtPairVector.rend());


  // Define 3 Matrix Lepton vectors
  TLorentzVector v1;
  TLorentzVector v2;
  TLorentzVector v3;

  // Define Matrix lepton type
  int LeptonType[3]={0};//1-ele, 2-mu, 3-tau.


  // If event has 3 loose matrix leptons:
  // - Store loose lepton types
  // - Mark loose leptons
  // - Calculate Fake/Prompt rates
  // - Calculate event type 
  if( maxPtVector.size()>=3 ){
    int LeptonCtr=0;
    for(std::vector< pair<double,int> >::iterator it = maxPtPairVector.begin(); it != maxPtPairVector.end(); ++it){
      LeptonCtr++;
      vector<SignatureObject*> lepvec = handler->getProduct(m_productnames[maxPtPNindexVector.at(it->second)]);
      lepvec[maxPtIndexVector.at(it->second)]->setVariable("IsMatrixLep", (int)(1));//set flags for matrix leptons

      string prodname = (string)(m_productnames[maxPtPNindexVector.at(it->second)]);
      if( prodname.find("Electron") != std::string::npos ) LeptonType[LeptonCtr-1]=1; 
      if( prodname.find("Muon")     != std::string::npos ) LeptonType[LeptonCtr-1]=2; 
      if( prodname.find("Tau")      != std::string::npos ) LeptonType[LeptonCtr-1]=3; 

      double lepvecpt  = lepvec[maxPtIndexVector.at(it->second)]->Pt();
      double lepveceta = lepvec[maxPtIndexVector.at(it->second)]->Eta();
      double lepvecphi = lepvec[maxPtIndexVector.at(it->second)]->Phi();
      if( LeptonCtr==1 ){ v1.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==2 ){ v2.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==3 ){ v3.SetPtEtaPhiM( lepvecpt, lepveceta, lepvecphi, 0 ); }
      if( LeptonCtr==3 ) break;
    }
    //
    ResetLooseTight();
    ResetFakePromptRates();
    SetFakePromptRates( v1.Pt(), v2.Pt(), v3.Pt(), LeptonType );

    //check if 3 vector objects are tight:
    int LTint=0;
    if (std::find(PtVectorTight.begin(), PtVectorTight.end(), v1.Pt()) != PtVectorTight.end()) LTint |= 1 << 0;//set bit0
    if (std::find(PtVectorTight.begin(), PtVectorTight.end(), v2.Pt()) != PtVectorTight.end()) LTint |= 1 << 1;//set bit1
    if (std::find(PtVectorTight.begin(), PtVectorTight.end(), v3.Pt()) != PtVectorTight.end()) LTint |= 1 << 2;//set bit2

    // ....................// bit2, bit1, bit0 -  Rightmost label is 0th bit.
    if( LTint==7 ) nTTT=1; // 111
    if( LTint==6 ) nTTL=1; // 110
    if( LTint==5 ) nTLT=1; // 101
    if( LTint==3 ) nLTT=1; // 011
    if( LTint==4 ) nTLL=1; // 100
    if( LTint==2 ) nLTL=1; // 010
    if( LTint==1 ) nLLT=1; // 001 
    if( LTint==0 ) nLLL=1; // 000
  }
 
  handler->setVariable("Wfff",Wfff());//triple fake
  handler->setVariable("Wffp",Wffp());//double fake
  handler->setVariable("Wfpf",Wfpf());//double fake
  handler->setVariable("Wpff",Wpff());//double fake
  handler->setVariable("Wfpp",Wfpp());//single fake
  handler->setVariable("Wpfp",Wpfp());//single fake
  handler->setVariable("Wppf",Wppf());//single fake
  handler->setVariable("Wppp",Wppp());//no fake
  handler->setVariable("WfakeBckg",WfakeBckg());//total fake
  //
  // We need p/f systematics as well (12 new WfakeBckg values):
  //  p1Up, p1Down,  p2Up, p2Down,  p3Up, p3Down, 
  //  f1Up, f1Down,  f2Up, f2Down,  f3Up, f3Down, 
  //
  handler->setVariable("nLLL",nLLL);//no T
  handler->setVariable("nLLT",nLLT);//single T
  handler->setVariable("nLTL",nLTL);//single T
  handler->setVariable("nTLL",nTLL);//single T
  handler->setVariable("nLTT",nLTT);//double T
  handler->setVariable("nTLT",nTLT);//double T
  handler->setVariable("nTTL",nTTL);//double T
  handler->setVariable("nTTT",nTTT);//triple T


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
    if( maxPtVector.size()>=3 ){
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

void EventVariableMatrixLeptons::SetFakePromptRates( double pt1, double pt2, double pt3, int LeptonType[3] ){
  if( LeptonType[0]==1 ){ p1=eP(pt1,0); f1=eF(pt1,0); }
  if( LeptonType[0]==2 ){ p1=mP(pt1,0); f1=mF(pt1,0); }
  if( LeptonType[1]==1 ){ p2=eP(pt2,0); f2=eF(pt2,0); }
  if( LeptonType[1]==2 ){ p2=mP(pt2,0); f2=mF(pt2,0); }
  if( LeptonType[2]==1 ){ p3=eP(pt3,0); f3=eF(pt3,0); }
  if( LeptonType[2]==2 ){ p3=mP(pt3,0); f3=mF(pt3,0); }
}

void EventVariableMatrixLeptons::ResetFakePromptRates(){
  p1=0;  p2=0;  p3=0;
  f1=0;  f2=0;  f3=0;
}

void EventVariableMatrixLeptons::ResetLooseTight(){
  nLLL=0;
  nLLT=0, nLTL=0, nTLL=0;
  nLTT=0, nTLT=0, nTTL=0;
  nTTT=0;
}

double EventVariableMatrixLeptons::mF( double pt, double njet ){
  return 0.1;  
}

double EventVariableMatrixLeptons::mP( double pt, double njet ){
  return 0.95;  
}

double EventVariableMatrixLeptons::eF( double pt, double njet ){
  return 0.2;  
}

double EventVariableMatrixLeptons::eP( double pt, double njet ){
  return 0.90;  
}

double EventVariableMatrixLeptons::Wfff( ){
  double wfff_ = (f1*f2*f3) * ((-(nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3)) - nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) - nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 - nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 - nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p1 + p2 - p1*p2)*pow(f3 - p3,3)*p3 + nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p1 + p3 - p1*p3) + nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p2 + p3 - p2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wfff_;
}

double EventVariableMatrixLeptons::Wffp( ){
  double wffp_ = (f1*f2*p3) * ((f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + (-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) + f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3) + (-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wffp_;
}

double EventVariableMatrixLeptons::Wfpf( ){
  double wfpf_ = (f1*f3*p2) * ((f2*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f2)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) + f2*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f2)*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wfpf_;
}

double EventVariableMatrixLeptons::Wpff( ){
  double wpff_ = (f2*f3*p1) * ((f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*(-1 + p3) + f1*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + (-1 + f1)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*(-1 + p3) + f1*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + (-1 + f1)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)*p3 + f1*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3 + (-1 + f1)*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3)*p3)/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wpff_;
}

double EventVariableMatrixLeptons::Wfpp( ){
  double wfpp_ = (f1*p2*p3) * ((-(f2*f3*nTLL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3)) - f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nTTL*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*(-1 + p1)*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*f3*nLLL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*f3*nLTL*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3) - (-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*p1*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wfpp_;
}

double EventVariableMatrixLeptons::Wpfp( ){
  double wpfp_ = (f2*p1*p3) * ((-(f1*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3)) - f1*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*(-1 + p2)*pow(f3 - p3,3) - f1*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - f1*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3) - (-1 + f1)*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*p2*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wpfp_;
}

double EventVariableMatrixLeptons::Wppf( ){
  double wppf_ = (f3*p1*p2) * ((-(f1*f2*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3)) - (-1 + f1)*(-1 + f2)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + p3) - f1*f2*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - f1*(-1 + f2)*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 - (-1 + f1)*f2*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + (-1 + f1 + f2 - f1*f2)*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*p3 + f2*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f1 + p3 - f1*p3) + f1*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3)*(-1 + f2 + p3 - f2*p3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wppf_;
}

double EventVariableMatrixLeptons::Wppp( ){
  double wppp_ = (p1*p2*p3) * ((f1*f2*f3*nLLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*f2*(-1 + f3)*nLLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*f3*nLTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + f1*(-1 + f2)*(-1 + f3)*nLTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*f3*nTLL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*f2*(-1 + f3)*nTLT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*f3*nTTL*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3) + (-1 + f1)*(-1 + f2)*(-1 + f3)*nTTT*pow(f1 - p1,3)*pow(f2 - p2,3)*pow(f3 - p3,3))/(pow(f1 - p1,4)*pow(f2 - p2,4)*pow(f3 - p3,4)));
  //
  return wppp_;
}

double EventVariableMatrixLeptons::WfakeBckg( ){
  double fakeBckg = Wfff()+Wffp()+Wfpf()+Wpff()+Wfpp()+Wpfp()+Wppf();
  return fakeBckg;
}


  /*
	handler->setVariable(TString::Format("%sNOSSF",m_prefix.Data()),nOSSF);
	handler->setVariable(TString::Format("%sONZ",m_prefix.Data()),onZ);
	
	// Always set these variables to avoid skipping of NOSSF == 0 events, 
	// e.g. when selecting from the ntuple with MOSSF dimension
	handler->setVariable(TString::Format("%sOSSFMINMLL",m_prefix.Data()),minMass);
	handler->setVariable(TString::Format("%sOSSFCLOSEMLL",m_prefix.Data()),closeMass);
	handler->setVariable(TString::Format("%sOSSFMAXMLL",m_prefix.Data()),maxMass);
	handler->setVariable(TString::Format("%sMOSSF",m_prefix.Data()),bestMass);
	handler->setVariable(TString::Format("%sPTOSSF",m_prefix.Data()),zPT);
	
	// TODO add vector of all OSSF pair masses
		
	return true;
  */