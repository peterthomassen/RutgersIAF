#include "RutgersIAF2012/EventAnalyzer/interface/EventVariableTriggerWeight.h"
#include <algorithm>
#include "RutgersIAF2012/EventAnalyzer/interface/SignatureObject.h"

ClassImp(EventVariableTriggerWeight)

using namespace std;

bool EventVariableTriggerWeight::calculate(BaseHandler* handler) {
	std::vector<SignatureObject*> goodElectrons = handler->getProduct("goodElectrons");
	std::vector<SignatureObject*> goodMuons     = handler->getProduct("goodMuons");
	
	vector<double> weights;
	for(int i = 0; i < (int)goodElectrons.size(); i++){
		double pt1 = goodElectrons[i]->Pt();
		if(pt1 > 85.0){
			weights.push_back(1.0-0.937);
		}
		if(pt1 < 10)continue;
		for(int j = 0; j < (int)goodMuons.size(); j++){
			double pt2 = goodMuons[j]->Pt();
			if(pt2 < 10)continue;
			if(pt1 > 20 && pt2 > 20){
				weights.push_back(1.0-0.93);
			}else if(pt1 > 20 || pt2 > 20){
				weights.push_back(1.0-0.88);
			}
		}
		if(pt1 < 20)continue;
		for(int j = i+1; j < (int)goodElectrons.size(); j++){
			double pt2 = goodElectrons[j]->Pt();
			if(pt2 < 10)break;
			if(pt1 > 20 && pt2 > 20){
				weights.push_back(1.0-0.96);
			}else{
				weights.push_back(1.0-0.89);
			}
		}
	}
	for(int i = 0; i < (int)goodMuons.size(); i++){
		double pt1 = goodMuons[i]->Pt();
		if(pt1 > 30.0){
			weights.push_back(1.0-0.81);
		}
		if(pt1 < 20)continue;
		for(int j = i+1; j < (int)goodMuons.size(); j++){
			double pt2 = goodMuons[j]->Pt();
			if(pt2 < 10)break;
			if(pt1 > 20 && pt2 > 20){
				weights.push_back(1.0-0.88);
			}else{
				weights.push_back(1.0-0.86);
			}
		}
	}
	
	double p = (weights.size() > 0)
		? 1.0
		: 0;
	
	for(int i = 0; i < (int)weights.size(); i++){
		p *= weights[i];
	}
	
	double weight = 1 - p;
	handler->setVariable(getName(), weight);
	return true;
}
