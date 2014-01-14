#include "RutgersIAF2012/RootC/interface/SignatureTH2F_METvsAllMass.h"

ClassImp(SignatureTH2F_METvsAllMass)
using namespace std;

Int_t SignatureTH2F_METvsAllMass::Fill(BaseHandler* handler)
{
  TLorentzVector v(0,0,0,0);
  for(int i = 0; i < (int)m_products.size(); i++){
    vector<SignatureObject*> product = handler->getProduct(m_products[i]);
    for(int j = 0; j < (int)product.size(); j++){
      v += TLorentzVector(*(product[j]));
    }
  }
  return TH2F::Fill(v.M(),handler->getPFMET(),handler->getPhysicsWeight());

}

void SignatureTH2F_METvsAllMass::addProduct(TString c)
{
  if(find(m_products.begin(),m_products.end(),c) == m_products.end())m_products.push_back(c);
  
}
