#include "RutgersIAF/RootC/interface/SignatureCutAllLeptonMass.h"
using namespace std;
ClassImp(SignatureCutAllLeptonMass)

bool SignatureCutAllLeptonMass::passCut(BaseHandler* handler) const
{
  vector<SignatureObject*> electrons = handler->getProduct("goodElectrons");
  vector<SignatureObject*> muons = handler->getProduct("goodMuons");
  TLorentzVector v(0,0,0,0);
  for(int i = 0; i < (int)electrons.size();i++){
    v+=TLorentzVector(*(electrons[i]));
  }
  for(int i = 0; i < (int)muons.size();i++){
    v+=TLorentzVector(*(muons[i]));
  }
  if(m_cutInRange && v.M() > m_massCutLow && v.M() < m_massCutHigh)return false;
  if(!m_cutInRange && v.M() < m_massCutLow) return false;
  if(!m_cutInRange && v.M() > m_massCutHigh)return false;
  return true;
}
