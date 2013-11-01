#ifndef ObjectCutJetGenParticle_h
#define ObjectCutJetGenParticle_h

#include <string>
#include <iostream>
#include <sstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include "RutgersIAF2012/RootC/interface/ObjectCut.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectJet.h"
#include "RutgersIAF2012/RootC/interface/SignatureObjectMCPart.h"

class ObjectCutJetGenParticle : public ObjectCut {
 public:
	ObjectCutJetGenParticle(int pdgid, bool keepAntiParticles=false, const char* name="jetgenparticlepdgidcut") : ObjectCut(name),m_pdgid(pdgid),m_keepAntiParticles(keepAntiParticles){ /*no-op*/}
		//ObjectCutJetGenParticle(double etamax) : ObjectCutJetGenParticle("etacut",etamax){ /* no-op */ }
		
	virtual ~ObjectCutJetGenParticle(){}
	bool passCut(SignatureObject* sigObj) const {return passCut((SignatureObjectJet*)sigObj);}
	bool operator()(SignatureObject* sigObj)const {return passCut(sigObj);}

	bool passCut(SignatureObjectJet* sigObj) const {
		int pdgid = sigObj->getGenParton_pdgID();
		if(!(abs(pdgid) < 6)) {
			return false;
		}
		SignatureObjectMCPart* mother = sigObj->getGenParton()->getMother();
		if(mother == 0) {
			return false;
		}
		pdgid = mother->getPDGid();
		return m_keepAntiParticles
			? (abs(pdgid) == abs(m_pdgid))
			: (pdgid == m_pdgid);
	}
	bool operator()(SignatureObjectMCPart*) const;

 private:
	double m_pdgid;
	bool m_keepAntiParticles;

	ClassDef(ObjectCutJetGenParticle,1);

};

inline bool ObjectCutJetGenParticle::operator()(SignatureObjectMCPart* sigobj) const
{
	return passCut(sigobj);
}
#endif
