#include "RutgersIAF2012/RootC/interface/SignatureCutPairMass.h"

ClassImp(SignatureCutPairMass)

using namespace std;

bool SignatureCutPairMass::passCut(BaseHandler* handler) const
{
  ///chargeMode 
  ///0: OS
  ///1: SS
  ///2: any

  ///mixMode
  ///0: same product
  ///1: different product
  ///2: any
  vector<float> mass;
  TLorentzVector v(0,0,0,0);
  for(int j = 0; j < (int)m_products.size(); j++){
    vector<SignatureObject*> product1 = handler->getProduct(m_products[j]);
    vector<SignatureObject*> product2;
    if(m_mixMode == 0){
      product2 = product1;
    }else if(m_mixMode == 1){
      for(int p = j+1; p < (int)m_products.size(); p++){
        vector<SignatureObject*> product3 = handler->getProduct(m_products[p]);
        product2.insert(product2.end(),product3.begin(),product3.end());
      }
    }else if(m_mixMode == 2){
      for(int p = j; p < (int)m_products.size(); p++){
        vector<SignatureObject*> product3 = handler->getProduct(m_products[p]);
        product2.insert(product2.end(),product3.begin(),product3.end());
      }
    }
    for(int k = 0; k < (int)product1.size(); k++){
      TLorentzVector v1(*(product1[k]));
      for(int l = 0; l < (int)product2.size(); l++){
        if((m_mixMode == 0 || m_mixMode == 2) && l <= k)continue;
        
        if(m_chargeMode < 2) {
			int charge1 = ((SignatureObjectRecoTrack*)product1[k])->getCharge();
			int charge2 = ((SignatureObjectRecoTrack*)product2[l])->getCharge();
			if(m_chargeMode == 0 && fabs(charge1+charge2) > 0.5)continue;
			if(m_chargeMode == 1 && fabs(charge1+charge2) < 1.5)continue;
        }
        TLorentzVector v2(*product2[l]);
		mass.push_back((v1+v2).M());
      }
    }
  }

  bool retval = !m_acceptInRange;

  for(int i = 0; i < (int)mass.size(); i++){
    if(mass[i] < 0)continue;
    if(m_acceptInRange && mass[i] > m_massCutLow && mass[i] < m_massCutHigh)retval = true;
    if(!m_acceptInRange && mass[i] > m_massCutLow && mass[i] < m_massCutHigh)retval = false;
  }

  return retval;

}

void SignatureCutPairMass::addProduct(TString c)
{
  if(find(m_products.begin(),m_products.end(),c)== m_products.end())m_products.push_back(c);
}
