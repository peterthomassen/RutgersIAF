#include "RutgersIAF/RootC/interface/SignatureHandler.h"

using namespace std;

///////----0-0-0-0-0-0-0-0-0-0--0--0-0--0-0-0---0
double SignatureHandler::calcTriggerWeight()
{
  vector<double> weights;
  for(int i = 0; i < (int)m_good_electrons.size(); i++){
    double pt1 = m_good_electrons[i]->Pt();
    if(pt1 > 85.0){
      weights.push_back(1.0-0.937);
    }
    if(pt1 < 10)continue;
    for(int j = 0; j < (int)m_good_muons.size(); j++){
      double pt2 = m_good_muons[j]->Pt();
      if(pt2 < 10)continue;
      if(pt1 > 20 && pt2 > 20){
	weights.push_back(1.0-0.93);
      }else if(pt1 > 20 || pt2 > 20){
	weights.push_back(1.0-0.88);
      }
    }
    if(pt1 < 20)continue;
    for(int j = i+1; j < (int)m_good_electrons.size(); j++){
      double pt2 = m_good_electrons[j]->Pt();
      if(pt2 < 10)break;
      if(pt1 > 20 && pt2 > 20){
	weights.push_back(1.0-0.96);
      }else{
	weights.push_back(1.0-0.89);
      }
    }
  }
  for(int i = 0; i < (int)m_good_muons.size(); i++){
    double pt1 = m_good_muons[i]->Pt();
    if(pt1 > 30.0){
      weights.push_back(1.0-0.81);
    }
    if(pt1 < 20)continue;
    for(int j = i+1; j < (int)m_good_muons.size(); j++){
      double pt2 = m_good_muons[j]->Pt();
      if(pt2 < 10)break;
      if(pt1 > 20 && pt2 > 20){
	weights.push_back(1.0-0.88);
      }else{
	weights.push_back(1.0-0.86);
      }
    }
  }
  if(weights.size() == 0) {
	  return 1.0;
  }
  double p = 1.0;
  for(int i = 0; i < (int)weights.size(); i++){
    p *= weights[i];
  }

  return 1.0 - p;
}
