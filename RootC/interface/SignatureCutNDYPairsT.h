#ifndef SignatureCutNDYPairsT_h
#define SignatureCutNDYPairsT_h

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

class SignatureCutNDYPairsT : public SignatureCut {
 public:
	SignatureCutNDYPairsT(const char* productname, double ndypairlow = 1, double ndypairhigh=1,bool onZ=true, double ZmassCutLow = 75, double ZmassCutHigh=105, double lowMassCut = 12, const char* name="sigcutndypairst") : SignatureCut(name),m_productname(productname),m_ndypairhigh(ndypairhigh),m_ndypairlow(ndypairlow),m_onZ(onZ),m_ZMassCutOffLow(ZmassCutLow), m_ZMassCutOffHigh(ZmassCutHigh),m_lowMassCutOff(lowMassCut){ /* no-op */}
		//SignatureCutNDYPairsT(double dypairlow = 0, double dypairhigh=-1):SignatureCutNDYPairsT("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
	virtual ~SignatureCutNDYPairsT(){ /* no-op */ }

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
	virtual bool operator()(BaseHandler*) const;

 private:
	TString m_productname;
	double m_ndypairhigh;
	double m_ndypairlow;
	bool m_onZ;
	double m_ZMassCutOffLow;
	double m_ZMassCutOffHigh;
	double m_lowMassCutOff;
	mutable std::vector< std::pair<SignatureObject*,SignatureObject*> > m_dyCandidates;

	ClassDef(SignatureCutNDYPairsT,1);

};

inline bool SignatureCutNDYPairsT::operator()(BaseHandler* handler) const
{
	return passCut(handler);
}
#endif
