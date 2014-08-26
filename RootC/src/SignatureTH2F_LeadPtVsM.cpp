#include "RutgersIAF/RootC/interface/SignatureTH2F_LeadPtVsM.h"
#include "RutgersIAF/RootC/interface/SignatureObjectRecoTrack.h"

using namespace std;

ClassImp(SignatureTH2F_LeadPtVsM)

Int_t SignatureTH2F_LeadPtVsM::Fill(BaseHandler* handler)
{
  Int_t dummy = -1;

  vector<SignatureObject*> v = handler->getProduct(m_productname);

  if(v.size() < 2)return dummy;

  sort(v.begin(),v.end(),SignatureObjectComparison);
  reverse(v.begin(),v.end());
  double leadpt = v[0]->Pt();

  for(int i = 0; i < (int)v.size() && dummy == -1; i++){
    SignatureObjectRecoTrack* a = dynamic_cast<SignatureObjectRecoTrack*>(v[i]);
    if(a == NULL)break;
    for(int j = 0; j < i && dummy == -1; j++){
      SignatureObjectRecoTrack* b = dynamic_cast<SignatureObjectRecoTrack*>(v[j]);
      TLorentzVector v1(*a);
      TLorentzVector v2(*b);

      if(m_samesign && a->getCharge() * b->getCharge() > 0){
	dummy = TH2F::Fill((v1+v2).M(),leadpt);
      }else if(!m_samesign && a->getCharge() * b->getCharge() < 0){
	dummy = TH2F::Fill((v1+v2).M(),leadpt,handler->getPhysicsWeight());
      }
    }
  }
  return dummy;
}
