#include "RutgersIAF2012/RootC/interface/SignatureTH1F_ZpT.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"

using namespace std;

ClassImp(SignatureTH1F_ZpT)

Int_t SignatureTH1F_ZpT::Fill(BaseHandler* handler)
{
  int dummy = -1;

  for(int i = 0; i < (int)m_products.size(); i++){
    vector<SignatureObject*> product = handler->getProduct(m_products[i]);
    TLorentzVector p1,p2;
    for(int j = 0; j < (int)product.size();j++){
      double charge1 = ((SignatureObjectRecoTrack*)product[j])->getCharge();
      p1 = *(product[j]);
      for(int k = j+1; k < (int)product.size();k++){
	if(charge1 * ((SignatureObjectRecoTrack*)product[k])->getCharge() > 0)continue;
	p2 = *(product[k]);
	dummy = TH1F::Fill((p1+p2).Pt(),handler->getPhysicsWeight());
      }
    }
  }

  return dummy;
}
void SignatureTH1F_ZpT::addProduct(TString c)
{
  if(find(m_products.begin(),m_products.end(),c)== m_products.end())m_products.push_back(c);
}
