#include "RutgersIAF2012/RootC/interface/SignatureCutTauZ.h"

ClassImp(SignatureCutTauZ)

using namespace std;

bool SignatureCutTauZ::passCut(BaseHandler* handler) const
{
  vector<SignatureObject*> taus = handler->getProduct(m_tauProduct);
  vector<SignatureObject*> muons = handler->getProduct(m_muonProduct);
  vector<SignatureObject*> electrons = handler->getProduct(m_electronProduct);

  int nInRange = 0;
  for(int i = 0; i < (int)taus.size(); i++){
    SignatureObjectTau* tau = (SignatureObjectTau*)taus[i];
    double tauCharge = tau->getCharge();
    TLorentzVector tauVec(*tau);
    for(int j = 0; j < (int)muons.size();j++){
      SignatureObjectMuon* muon = (SignatureObjectMuon*)muons[j];
      if(muon->getCharge()*tauCharge > 0.0)continue;
      TLorentzVector muonVec(*muon);
      double mass = (muonVec+tauVec).M();
      if(mass < m_massCutLow)continue;
      if(mass > m_massCutHigh)continue;
      nInRange++;
    }
    for(int j = 0; j < (int)electrons.size();j++){
      SignatureObjectElectron* electron = (SignatureObjectElectron*)electrons[j];
      if(electron->getCharge()*tauCharge > 0.0)continue;
      TLorentzVector electronVec(*electron);
      double mass = (electronVec+tauVec).M();
      if(mass < m_massCutLow)continue;
      if(mass > m_massCutHigh)continue;
      nInRange++;
    }
  }
  if(m_acceptInRange && nInRange > 0)return true;
  if(!m_acceptInRange && nInRange == 0)return true;
  return false;
}
