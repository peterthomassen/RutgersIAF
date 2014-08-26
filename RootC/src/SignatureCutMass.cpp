#include "RutgersIAF/RootC/interface/SignatureCutMass.h"

using namespace std;

ClassImp(SignatureCutMass)

bool SignatureCutMass::passCut(BaseHandler* handler) const
{
  TLorentzVector v(0,0,0,0);
  for(int i = 0; i < (int)m_products.size(); i++){
    vector<SignatureObject*> product = handler->getProduct(m_products[i]);
    for(int j = 0; j < (int)product.size(); j++){
      v += TLorentzVector(*(product[j]));
    }
  }
  if(m_cutInRange && v.M() > m_massCutLow && v.M() < m_massCutHigh)return false;
  if(!m_cutInRange && v.M() < m_massCutLow) return false;
  if(!m_cutInRange && v.M() > m_massCutHigh) return false;
  return true;
  
}

void SignatureCutMass::addProduct(TString c)
{
  if(find(m_products.begin(),m_products.end(),c) == m_products.end())m_products.push_back(c);
  
}

