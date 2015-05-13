#ifndef SignatureTH1F_TriggerName_h
#define SignatureTH1F_TriggerName_h

#include <TH1F.h>
#include <TAxis.h>
#include <TString.h>
#include <vector>
#include <algorithm>
#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F.h"
#include "RutgersIAF/EventAnalyzer/interface/SignatureObject.h"

class SignatureTH1F_TriggerName : public SignatureTH1F {
public:
  
  SignatureTH1F_TriggerName(const char* name, TString productName, int maxPrescale = 1, const char* title = "Triggers", int nbins=20, float xmin=-0.5,float xmax=19.5):SignatureTH1F(name,title,nbins,xmin,xmax),m_productName(productName),m_maxPrescale(maxPrescale){}
	
  SignatureTH1F_TriggerName(TH1F h):SignatureTH1F(h){}
  SignatureTH1F_TriggerName():SignatureTH1F(){}

  using TH1F::Fill;
  Int_t Fill(BaseHandler* handler)
  {    
    std::vector<SignatureObject*> triggers = handler->getProduct(m_productName);
    if(triggers.size() < 1)return -1;
    int dummy = -1;
    for(int i = 0; i < (int)triggers.size(); i++){
      bool accept = false;
      if(!triggers[i]->getVariable("ACCEPT",accept) || !accept)continue;
      int prescale = 0;
      if(!triggers[i]->getVariable("PRESCALE",prescale) || prescale > m_maxPrescale)continue;
      TString trigName = "";
      if(!triggers[i]->getVariable("TRIGGERNAME",trigName) || trigName == "")continue;
      std::vector<TString>::iterator iter= std::find(m_triggerNames.begin(),m_triggerNames.end(),trigName);
      if(iter == m_triggerNames.end()){
	m_triggerNames.push_back(trigName);
	if((int)m_triggerNames.size() > GetNbinsX()){
	  float xmin = GetXaxis()->GetXmin();
	  float xmax = GetXaxis()->GetXmax();
	  SetBins(GetNbinsX()+1,xmin,xmax+1);
	}
	GetXaxis()->SetBinLabel(m_triggerNames.size(),trigName.Data());
      }
      dummy = TH1F::Fill((float)(iter-m_triggerNames.begin()),handler->getPhysicsWeight());
    }

    return dummy;
  }

  virtual void Copy(TObject& hnew) const
  {
    TH1F::Copy(hnew);
    ((SignatureTH1F_TriggerName&)hnew).m_productName = m_productName;
    ((SignatureTH1F_TriggerName&)hnew).m_maxPrescale = m_maxPrescale;
    ((SignatureTH1F_TriggerName&)hnew).m_triggerNames = m_triggerNames;
  }

  ClassDef(SignatureTH1F_TriggerName,1);

 protected:
  TString m_productName;
  int m_maxPrescale;
  std::vector<TString> m_triggerNames;
};

#endif
