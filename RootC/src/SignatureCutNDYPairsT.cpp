#include "RutgersIAF2012/RootC/interface/SignatureCutNDYPairsT.h"

#include "RutgersIAF2012/RootC/interface/debug.h"

using namespace std;

ClassImp(SignatureCutNDYPairsT)

int SignatureCutNDYPairsT::getCandidates(BaseHandler* handler) const
{
  m_dyCandidates.clear();

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
  
  int nPairs = min(nOp,nTm) + min(nOm,nTp);
/*  cout << "number of pairs of a track and an object of product " << m_productname << ": " << nPairs << " (nOp=" << nOp << ",nOm=" << nOm << ",nTp=" << nTp << ",nTm=" << nTm << ")" << endl;
  for(int i = 0; i < (int)m_dyCandidates.size(); ++i) {
    cout << "mass: " << (*(m_dyCandidates[i].first) + *(m_dyCandidates[i].second)).M() << endl;
  }
*/  
  return nPairs;
}

bool SignatureCutNDYPairsT::passCut(BaseHandler* handler) const
{
	// Make sure the number of DY pairs is within the desired range
	int nDY = getCandidates(handler);
//std::cout << m_productname << ":" << nDY << " m_ndypairlow=" << m_ndypairlow << ", m_ndypairhigh=" << m_ndypairhigh << ", m_onZ=" << m_onZ << ", m_ZmassCutOffLow=" << m_ZMassCutOffLow << ", m_ZmassCutOffHigh=" << m_ZMassCutOffHigh << ", m_lowMassCutOff=" << m_lowMassCutOff << std::endl;
	if(m_ndypairlow >= 0 && (double)nDY < m_ndypairlow) {
		return false;
	}
	if(m_ndypairhigh >= 0 && (double)nDY > m_ndypairhigh) {
		return false;
	}
	
	// Ok, it is. If 0 is included in the desired range, we don't have to look at on/off Z, so just return true
	if(nDY == 0) {
		return true;
	}
	
	// Otherwise, look at on/off Z properties
	int nZ = 0;
	for(int i = 0; i < (int)m_dyCandidates.size(); i++) {
		TLorentzVector v1(*((m_dyCandidates[i]).first));
		TLorentzVector v2(*((m_dyCandidates[i]).second));
		if((v1+v2).M() < m_lowMassCutOff) {
			return false;
		}
		if((v1+v2).M() > m_ZMassCutOffLow && (v1+v2).M() < m_ZMassCutOffHigh) {
			nZ++;
		}
	}
	if(m_onZ && !nZ) {
		return false;
	}
	if(!m_onZ && nZ) {
		return false;
	}
	return true;
}
