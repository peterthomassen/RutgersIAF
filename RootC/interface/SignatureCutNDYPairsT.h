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
#include "RutgersIAF/RootC/interface/SignatureObject.h"
#include "RutgersIAF/RootC/interface/SignatureObjectElectron.h"
#include "RutgersIAF/RootC/interface/SignatureObjectMuon.h"
#include "RutgersIAF/RootC/interface/SignatureCut.h"
#include "RutgersIAF/RootC/interface/BaseHandler.h"

class SignatureCutNDYPairsT : public SignatureCut {
 public:
	SignatureCutNDYPairsT(const char* productname, double ndypairlow = 1, double ndypairhigh=1,bool onZ=true, double ZmassCutLow = 75, double ZmassCutHigh=105, double lowMassCut = 12, const char* name="sigcutndypairst") : SignatureCut(name),m_productname(productname),m_ndypairhigh(ndypairhigh),m_ndypairlow(ndypairlow),m_onZ(onZ),m_ZMassCutOffLow(ZmassCutLow), m_ZMassCutOffHigh(ZmassCutHigh),m_lowMassCutOff(lowMassCut){ /* no-op */}
		//SignatureCutNDYPairsT(double dypairlow = 0, double dypairhigh=-1):SignatureCutNDYPairsT("sigcutndypair",ndypairlow,ndypairhigh) { /*no-op */ }
	virtual ~SignatureCutNDYPairsT(){ /* no-op */ }

	int getCandidates(BaseHandler*) const;
	virtual bool passCut(BaseHandler*) const;
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
