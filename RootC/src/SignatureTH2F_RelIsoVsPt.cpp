#include "RutgersIAF2012/RootC/interface/SignatureTH2F_RelIsoVsPt.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectWithIso.h"

using namespace std;

ClassImp(SignatureTH2F_RelIsoVsPt)

Int_t SignatureTH2F_RelIsoVsPt::Fill(BaseHandler* handler)
{
  double jetpt = -1;
  if(m_jetsource == "HT"){
    jetpt = handler->getHT();
  }else if(m_jetsource == "SUM"){
    jetpt = handler->getGoodRecoVertices()[0]->getWSumPt();
  }else if(m_jetsource == "LEAD" || m_jetsource == "LEADING"){
    vector<SignatureObject*> jetv = handler->getProduct("goodJets");
    if(jetv.size() > 0){
      sort(jetv.begin(),jetv.end());
      reverse(jetv.begin(),jetv.end());
      jetpt = jetv[0]->Pt();
    }
  }else{
    cerr<<"Jet source "<<m_jetsource<<" not recognized"<<endl;
  }

  Int_t dummy = -1;
  if(m_jetmin >= 0 && m_jetmax > 0 && jetpt < 0)return dummy;

  for(int i = 0; i < (int)m_subtractproducts.size(); i++){
    vector<SignatureObject*> product = handler->getProduct(m_subtractproducts[i]);
    for(int j = 0; j < (int)product.size(); j++){
      jetpt -= product[j]->Pt();
    }
  }

  jetpt = max(jetpt,0.0);

  if(m_jetmin >= 0 && jetpt < m_jetmin)return dummy;
  if(m_jetmax > 0 && jetpt > m_jetmax)return dummy;

  vector<SignatureObject*> v = handler->getProduct(m_productname);
  
  for(vector<SignatureObject*>::iterator it = v.begin(); it != v.end(); ++it){
    SignatureObjectWithIso* owi = (SignatureObjectWithIso*)(*it);
    dummy = TH2F::Fill(owi->Pt(),owi->getRelIso(),handler->getPhysicsWeight());
  }

  return dummy;
}
//-------------------------------------
void SignatureTH2F_RelIsoVsPt::addSubtractProduct(TString product)
{
  if(find(m_subtractproducts.begin(),m_subtractproducts.end(),product) != m_subtractproducts.end())return;
  m_subtractproducts.push_back(product);
  return;
}
