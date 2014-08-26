#include "RutgersIAF/RootC/interface/SignatureTH1F_TopTagChi2.h"
#include "RutgersIAF/RootC/interface/SignatureObject.h"

using namespace std;

ClassImp(SignatureTH1F_TopTagChi2)

Int_t  SignatureTH1F_TopTagChi2::Fill(BaseHandler* handler)
{

  vector<SignatureObject*> product = handler->getProduct(m_product);

  if(product.size() < 4)return -1;

  int dummy = -1;

  double minChi2 = 9999999.0;

  for(int i = 0 ; i < (int)product.size(); i++){
    TLorentzVector j1,j2,j3,j4;
    j1 = *(product[i]);
    for(int j = i+1; j < (int)product.size(); j++){
      j2 = *(product[j]);
      for(int k = j+1; k < (int)product.size(); k++){
	j3 = *(product[k]);
	for(int l = k+1; l < (int)product.size(); l++){
	  j4 = *(product[l]);
	  double chi2a,chi2b,chi2c;
	  chi2a = pow((j1+j2).M() - m_refMass,2) + pow((j3+j4).M() - m_refMass,2);
	  chi2b = pow((j1+j3).M() - m_refMass,2) + pow((j2+j4).M() - m_refMass,2);
	  chi2c = pow((j1+j4).M() - m_refMass,2) + pow((j3+j2).M() - m_refMass,2);
	  if (chi2a < minChi2)minChi2 = chi2a;
	  if (chi2b < minChi2)minChi2 = chi2b;
	  if (chi2c < minChi2)minChi2 = chi2c;
	}
      }
    }
  }

  dummy = TH1F::Fill(sqrt(minChi2)/2.0,handler->getPhysicsWeight());

  return dummy;

}
