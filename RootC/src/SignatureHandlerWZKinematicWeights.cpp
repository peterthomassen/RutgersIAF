#include "RutgersIAF/RootC/interface/SignatureHandler.h"
#include <math.h>

std::pair<double,double> SignatureHandler::getWZKinematicWeight() {
	// Only do this if this is WZ MC. Must have a status 3 W and Z in the first 12 MC particles
	
	std::pair<double,double> result;
	result.first=1.0; result.second=0.0;
	
	int w_id = -1;
	int z_id = -1;
	bool has_top = false;
	
	for(size_t i = 0; i < 12 && i < m_mcparticles.size(); ++i){
		int pdgid = ((SignatureObjectMCPart*)m_mcparticles[i])->getPDGid();
		int status = ((SignatureObjectMCPart*)m_mcparticles[i])->getStatus();
		
		if(status == 3) {
			if(abs(pdgid) == 23) { // Z
				z_id = i;
			} else if(abs(pdgid) == 24) { // W
				w_id = i;
			} else if(abs(pdgid) == 6) { // top
				has_top = true;
			}
		}
	}
	
	if(z_id < 0 || w_id < 0 || has_top) {
		return result;
	}
	
	double mz = m_mcparticles[z_id]->M();
	double zpt = m_mcparticles[z_id]->Pt();
	if(mz < 10.0) {
		return result;
	}

	double gz = zpt / sqrt(mz);

	double kin_nom_param = -0.005;
	double kin_syst_param = 0.012; // Syst exponentially increases with zpt/sqrt(mz)
	
	result.first = exp(kin_nom_param * gz);
	result.second = exp((kin_nom_param + kin_syst_param) * gz) - result.first;

	//std::cout<<"WZ Systematic: "<<result.first<<" +/- "<<result.second<<" for zpt="<<zpt<<" mz="<<mz<<" and gz="<<gz<<std::endl;
	return result;
}
