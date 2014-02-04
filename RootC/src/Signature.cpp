#include "RutgersIAF2012/RootC/interface/Signature.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_HT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_LJMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_LT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_N.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_PFMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_PT.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_ST.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH1F_TCMET.h"
#include "RutgersIAF2012/RootC/interface/SignatureTH2F_LeadPtVsM.h"

using namespace std;

ClassImp(Signature)

Signature::Signature(const char* name,const char* options)
{
  m_name = name;
  m_options = options;
  m_isInit = 0;
  m_isFinish = 0;
  parseOptions();
  m_doEventDump = false;

}
//-----------------------------------------
Signature::Signature(const Signature& sig)
{
  m_name = TString(sig.getName());
  m_options = "";
  m_isInit = 0;
  m_isFinish = 0;
  m_doEventDump = false;
  m_Cuts = sig.getCuts();
}
//-----------------------------------------
Signature::~Signature()
{

}
//-----------------------------------------
void Signature::addFakeStudyHistograms()
{

}
//-----------------------------------------
void Signature::addChargeSignHistograms()
{
  addHistogram(new SignatureTH2F_LeadPtVsM(TString(m_name+"_2El_OSSF_LeadPtVsM").Data(),"goodElectrons",false));
  addHistogram(new SignatureTH2F_LeadPtVsM(TString(m_name+"_2El_SSSF_LeadPtVsM").Data(),"goodElectrons",true));
  addHistogram(new SignatureTH2F_LeadPtVsM(TString(m_name+"_2Mu_OSSF_LeadPtVsM").Data(),"goodMuons",false));
  addHistogram(new SignatureTH2F_LeadPtVsM(TString(m_name+"_2Mu_SSSF_LeadPtVsM").Data(),"goodMuons",true));
}
//-----------------------------------------
void Signature::addBasicHistograms()
{
  addHistogram(new SignatureTH1F_ST(TString(m_name+"_ST").Data()));
  addHistogram(new SignatureTH1F_LT(TString(m_name+"_LT").Data()));
  addHistogram(new SignatureTH1F_HT(TString(m_name+"_HT").Data()));
  addHistogram(new SignatureTH1F_PFMET(TString(m_name+"_PFMET").Data()));
  addHistogram(new SignatureTH1F_LJMET(TString(m_name+"_LJMET").Data()));
  addHistogram(new SignatureTH1F_N(TString(m_name+"_nmuons").Data(),"goodMuons"));
  addHistogram(new SignatureTH1F_N(TString(m_name+"_nelectrons").Data(),"goodElectrons"));
  addHistogram(new SignatureTH1F_N(TString(m_name+"_ntaus").Data(),"goodTaus"));
  addHistogram(new SignatureTH1F_N(TString(m_name+"_nphotons").Data(),"goodPhotons"));
  addHistogram(new SignatureTH1F_N(TString(m_name+"_ntracks").Data(),"goodIsoTracks"));
  addHistogram(new SignatureTH1F_N(TString(m_name+"_njets").Data(),"goodJets"));
}

bool Signature::isSignature(BaseHandler* sigHandler)
{
  setHandler(sigHandler);
  return isSignature();
}
//-----------------------------------------
bool Signature::isSignature()
{
  for(int i = 0; i < (int)m_Cuts.size(); i++){
    if(m_handler->getDebugMode())cout<<getName()<<" "<<m_Cuts[i]->getName()<<endl;
    if(!m_Cuts[i]->passCut(m_handler)){
      //cout<<getName()<<" "<<m_Cuts[i]->getName()<<endl;
      return false;
    }
  }
  if(m_doEventDump)m_handler->dumpEventInfo();
  return true;
}
//-----------------------------------------
void Signature::init()
{
  if(m_isInit) return;
  cout<<"Initializing Signature "<<m_name<<endl;

  //Set dimensions of histograms

  m_isInit = 1;
}
//-----------------------------------------
void Signature::finish()
{
  if(m_isFinish) return;

  for(int i = 0; i < (int)m_1dhistograms.size(); i++){
    TH1F h = *(dynamic_cast<TH1F *>(m_1dhistograms[i]));
    h.Write();
  }
  for(int i = 0; i < (int)m_2dhistograms.size(); i++){
    TH2F h = *(dynamic_cast<TH2F *>(m_2dhistograms[i]));
    h.Write();
  }
  for(int i = 0; i < (int)m_3dhistograms.size(); i++){
    TH3F h = *(dynamic_cast<TH3F *>(m_3dhistograms[i]));
    h.Write();
  }
  m_isFinish = 1;
}
//-----------------------------------------
void Signature::fillHistograms()
{
  if(!m_isInit)init();

  for(int i = 0; i < (int)m_1dhistograms.size(); i++){
    m_1dhistograms[i]->Fill(m_handler);
  }
  for(int i = 0; i < (int)m_2dhistograms.size(); i++){
    m_2dhistograms[i]->Fill(m_handler);
  }
  for(int i = 0; i < (int)m_3dhistograms.size(); i++){
    m_3dhistograms[i]->Fill(m_handler);
  }
}
//-----------------------------------------
void Signature::parseOptions()
{


}
