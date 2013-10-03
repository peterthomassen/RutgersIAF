#ifndef SignatureCutNDYPairs_h
#define SignatureCutNDYPairs_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <algorithm>
#include <map>
#include "RutgersIAF2012/RootC/interface/SignatureObject.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF2012/RootC/interface/SignatureCut.h"
#include "RutgersIAF2012/RootC/interface/BaseHandler.h"

class SignatureCutNDYPairs : public SignatureCut {
 public:
	SignatureCutNDYPairs(double ndypairlow = 1, double ndypairhigh=1,bool onZ=true, double ZmassCutLow = 75, double ZmassCutHigh=105, bool removeLowM = true, double lowMassCut = 12, const char* name="sigcutndypairs") : SignatureCut(name),m_ndypairhigh(ndypairhigh),m_ndypairlow(ndypairlow),m_onZ(onZ),m_ZMassCutOffLow(ZmassCutLow), m_ZMassCutOffHigh(ZmassCutHigh),m_removeLowM(removeLowM),m_lowMassCutOff(lowMassCut){ /* no-op */}
		//SignatureCutNDYPairs(double dypairlow = 0, double dypairhigh=-1):SignatureCutNDYPairs("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
	virtual ~SignatureCutNDYPairs(){ /* no-op */ }

	int getCandidates(BaseHandler*) const;
	virtual bool passCut(BaseHandler* handler) const
	{
		// Make sure the number of DY pairs is within the desired range
		int nDY = getCandidates(handler);
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
			if(m_removeLowM && (v1+v2).M() < m_lowMassCutOff) {
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
	virtual bool operator()(BaseHandler*) const;

 private:
	double m_ndypairhigh;
	double m_ndypairlow;
	bool m_onZ;
	double m_ZMassCutOffLow;
	double m_ZMassCutOffHigh;
	bool m_removeLowM;
	double m_lowMassCutOff;
	mutable std::vector< std::pair<SignatureObject*,SignatureObject*> > m_dyCandidates;

	ClassDef(SignatureCutNDYPairs,1);

};

inline bool SignatureCutNDYPairs::operator()(BaseHandler* handler) const
{
	return passCut(handler);
}
#endif
