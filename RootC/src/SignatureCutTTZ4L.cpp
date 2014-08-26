#include "RutgersIAF/RootC/interface/SignatureCutTTZ4L.h"
#include <algorithm>

using namespace std;

ClassImp(SignatureCutTTZ4L)

bool SignatureCutTTZ4L::passCut(BaseHandler* handler) const
{
  int nZ = 0;
  for(int i = 0; i < (int)m_products.size(); i++){
    vector<SignatureObject*> objects = handler->getProduct(m_products[i]);
    //cout<<m_products[i]<<" "<<objects.size()<<endl;
    if(objects.size() < 2)continue;
    map<double,pair<int,int> > onZpairs;
    map<double,pair<int,int> >::const_iterator pairIter;
    for(int j = 0; j < (int)objects.size(); j++){
      for(int k = j+1; k < (int)objects.size(); k++){
	SignatureObjectRecoTrack* obj1 = (SignatureObjectRecoTrack*)objects[j];
	SignatureObjectRecoTrack* obj2 = (SignatureObjectRecoTrack*)objects[k];
	//cout<<m_products[i]<<" "<<j<<" "<<k<<" "<<obj1->getCharge()<<" "<<obj2->getCharge()<<endl;
	if(obj1->getCharge() * obj2->getCharge() > 0)continue;
	TLorentzVector o1(*objects[j]);
	TLorentzVector o2(*objects[k]);
	double nzmass = (o1+o2).M();
	//cout<<m_products[i]<<" "<<j<<" "<<k<<" "<<nzmass<<endl;
	if(nzmass > m_ZMassCutOffLow && nzmass < m_ZMassCutOffHigh){
	  onZpairs[fabs(nzmass-91)] = make_pair(j,k);
	}
      }
    }
    vector<int> used;
    for(pairIter = onZpairs.begin(); pairIter != onZpairs.end(); pairIter++){
      if(find(used.begin(),used.end(),(*pairIter).second.first) == used.end() && find(used.begin(),used.end(),(*pairIter).second.second) == used.end()){
	used.push_back((*pairIter).second.first);
	used.push_back((*pairIter).second.second);
      }
    }
      nZ += (int)used.size() / 2;
  }
  //cout<<"num Z"<<" "<<nZ<<endl;
  if(nZ != 1)return false;
  return true;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void SignatureCutTTZ4L::addProduct(TString pname)
{
  if(find(m_products.begin(),m_products.end(),pname) != m_products.end())return;
  m_products.push_back(pname);
}
