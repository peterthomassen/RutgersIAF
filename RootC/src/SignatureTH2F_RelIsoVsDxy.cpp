#include "RutgersIAF2012/RootC/interface/SignatureTH2F_RelIsoVsDxy.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectRecoTrack.h"

using namespace std;

ClassImp(SignatureTH2F_RelIsoVsDxy)

Int_t SignatureTH2F_RelIsoVsDxy::Fill(BaseHandler* handler)
{
	TString sigName = TString(this->GetName());
	bool debug = sigName.Contains("SeedEl2B0onZMET0to50_RelIsoVsDxy_electrons");
//	if(debug) cout << "[PT] debug!" << endl;
  double jetpt = -1;
  if(m_jetsource == "HT"){
    jetpt = handler->getHT();
  }else if(m_jetsource == "SUM"){
    jetpt = handler->getGoodRecoVertices()[0]->getWSumPt();
  }else if(m_jetsource == "LEAD" || m_jetsource == "LEADING"){
    vector<SignatureObject*> jetv = handler->getProduct("goodJets");
    if(jetv.size() > 0){
      sort(jetv.begin(),jetv.end(),SignatureObjectComparison);
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
  
  unsigned int nIP = 0;
  for(vector<SignatureObject*>::iterator it = v.begin(); it != v.end(); ++it){
    SignatureObjectRecoTrack* owi = (SignatureObjectRecoTrack*)(*it);
    dummy = TH2F::Fill(owi->getVert_dxy(),owi->getRelIso(),handler->getPhysicsWeight());
    int binX = GetXaxis()->FindFixBin(owi->getVert_dxy());
    int binY = GetYaxis()->FindFixBin(owi->getRelIso());
    if(debug && binX >= 37 && binX <= 44 && binY >= 1 && binY <= 3) {
		nIP++;
	} else if(debug) {
		cout << "[PT] " << binX << "," << binY << endl;
	}
  }
  if(debug && nIP < handler->getProduct("goodElectrons").size()) {
	  cout << "[PT] " << nIP << " < " << handler->getProduct("goodElectrons").size() << endl;
  }
  if(debug && nIP < 2) {
	  cout << "[PT]2 " << nIP << " < 2" << endl;
  }

  return dummy;
}
//-------------------------------------
void SignatureTH2F_RelIsoVsDxy::addSubtractProduct(TString product)
{
  if(find(m_subtractproducts.begin(),m_subtractproducts.end(),product) != m_subtractproducts.end())return;
  m_subtractproducts.push_back(product);
  return;
}
