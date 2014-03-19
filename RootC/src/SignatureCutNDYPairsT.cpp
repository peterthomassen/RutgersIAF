#include "RutgersIAF2012/RootC/interface/SignatureCutNDYPairsT.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(SignatureCutNDYPairsT)

int SignatureCutNDYPairsT::getCandidates(BaseHandler* handler) const
{
  m_dyCandidates.clear();
  /////////////////////////////////
  //only count electons and muons//
  /////////////////////////////////
  vector<SignatureObject*> objects = handler->getProduct(m_productname);
  vector<SignatureObject*> tracks = handler->getGoodRecoTracks();

  int nOp = 0;
  int nOm = 0;
  int nTp = 0;
  int nTm = 0;

  for(int i = 0; i < (int)objects.size(); i++){
    objects[i]->getCharge() > 0 ? nOp++ : nOm++;
  }
  for(int i = 0; i < (int)tracks.size(); i++){
    tracks[i]->getCharge() > 0 ? nTp++ : nTm++;
  }
  for(int i = 0; i < (int)objects.size(); i++){
    for(int j = 0; j < (int)tracks.size(); j++){
      if(objects[i]->getCharge() * tracks[j]->getCharge() > 0) {
        continue;
      }
      m_dyCandidates.push_back(make_pair(objects[i], tracks[j]));
    }
  }
  
  int nPairs = nOp * nTm + nOm * nTp;
  cout << "number of pairs of a track and an object of the given product: " << nPairs << endl;
  
  return nPairs;
}
