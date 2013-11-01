#ifndef ObjectCutTauGenLepton_h
#define ObjectCutTauGenLepton_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectTau.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class ObjectCutTauGenLepton : public ObjectCut {
 public:
	ObjectCutTauGenLepton(int pdgid = 15, bool keepAntiParticles=true, const char* name="taugenleptonpdgidcut") : ObjectCut(name),m_pdgid(pdgid),m_keepAntiParticles(keepAntiParticles){ /*no-op*/}
		//ObjectCutTauGenLepton(double etamax) : ObjectCutTauGenLepton("etacut",etamax){ /* no-op */ }
		
	virtual ~ObjectCutTauGenLepton(){}
	bool passCut(SignatureObject* sigObj) const {return passCut((SignatureObjectTau*)sigObj);}
	bool operator()(SignatureObject* sigObj)const {return passCut(sigObj);}

	bool passCut(SignatureObjectTau* sigObj) const {
		SignatureObjectMCPart* genLepton = sigObj->getGenLepton();
		if(genLepton == 0) {
			return false;
		}
		int pdgid = genLepton->getPDGid();
		bool res = m_keepAntiParticles
			? (abs(pdgid) == abs(m_pdgid))
			: (pdgid == m_pdgid);
		return res;
	}
	bool operator()(SignatureObjectMCPart*) const;

 private:
	double m_pdgid;
	bool m_keepAntiParticles;

	ClassDef(ObjectCutTauGenLepton,1);

};

inline bool ObjectCutTauGenLepton::operator()(SignatureObjectMCPart* sigobj) const
{
	return passCut(sigobj);
}
#endif
