#include "RutgersIAF/RootC/interface/SignatureTH1F_TauIso.h"
#include "RutgersIAF/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF/RootC/interface/SignatureRecoVertex.h"

using namespace std;

ClassImp(SignatureTH1F_TauIso)

Int_t SignatureTH1F_TauIso::Fill(BaseHandler* handler)
{
  double jetpt = -1;
  Int_t dummy = -1;
  if(m_jetsource == "HT"){
    jetpt = handler->getHT();
  }else if(m_jetsource == "SUM"){
	  if(handler->getGoodRecoVertices().size() == 0) {
		  return dummy;
	  }
    jetpt = handler->getGoodRecoVertices()[0]->getWSumPt();
  }else if(m_jetsource == "LEAD" || m_jetsource == "LEADING"){
    vector<SignatureObject*> jetv = handler->getProduct("goodJets");
    if(jetv.size() > 0){
      sort(jetv.begin(),jetv.end(),SignatureObjectComparison);
      reverse(jetv.begin(),jetv.end());
      jetpt = jetv[0]->Pt();
    }
  }else if(m_jetsource ==""){
    jetpt = -1;
    m_jetmin = -1;
    m_jetmax = -1;
  }else{
    cerr<<"Jet source "<<m_jetsource<<" not recognized"<<endl;
  }

  if(m_jetmin >= 0 && m_jetmax > 0 && jetpt < 0)return dummy;

  jetpt = max(jetpt,0.0);

  if(m_jetmin >= 0 && jetpt < m_jetmin)return dummy;
  if(m_jetmax > 0 && jetpt > m_jetmax)return dummy;

  vector<SignatureObject*> v = handler->getProduct(m_productname);

  for(vector<SignatureObject*>::iterator it = v.begin(); it != v.end(); ++it){
    SignatureObjectTau* tau = (SignatureObjectTau*)(*it);
    dummy = TH1F::Fill(tau->getTotalIso(),handler->getPhysicsWeight());
  }

  return dummy;
}
