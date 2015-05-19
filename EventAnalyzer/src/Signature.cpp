#include <TString.h>
#include "RutgersIAF/EventAnalyzer/interface/Signature.h"
#include "RutgersIAF/EventAnalyzer/interface/BaseHandler.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH3F.h"

using namespace std;

ClassImp(Signature)

Signature::Signature(TString name,TString options)
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
Signature* Signature::addCut(TString cutname)
{
  vector<TString>::const_iterator iter = find(m_Cuts.begin(),m_Cuts.end(),cutname);
  if(iter == m_Cuts.end())m_Cuts.push_back(cutname);

  return this;
}
//-----------------------------------------
bool Signature::isSignature()
{
  for(int i = 0; i < (int)m_Cuts.size(); i++){
    bool pass = m_handler->passCut(m_Cuts[i]);
    if(m_handler->getDebugMode())cout<<getName()<<" "<<m_Cuts[i]<<"="<<pass<<endl;
    if(!pass){
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
    TH1F h;
    m_1dhistograms[i]->TH1F::Copy(h);
    h.Write();
  }
  for(int i = 0; i < (int)m_2dhistograms.size(); i++){
    TH2F h;
    m_2dhistograms[i]->TH2F::Copy(h);
    h.Write();
  }
  for(int i = 0; i < (int)m_3dhistograms.size(); i++){
    TH3F h;
    m_3dhistograms[i]->TH3F::Copy(h);
    h.Write();
  }
  m_isFinish = 1;
}
//-----------------------------------------
void Signature::parseOptions()
{


}
//-------------------------------------------
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
