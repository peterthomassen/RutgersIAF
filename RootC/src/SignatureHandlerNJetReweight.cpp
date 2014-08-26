#include "RutgersIAF/RootC/interface/SignatureHandler.h"
#include <math.h>

std::pair<double,double> SignatureHandler::getNJetReweight(int njet) {
	std::pair<double,double> result;
	result.first=1.0; result.second=0.0;
	
	if(getMCtype() == "WZ" || getMCtype() == "ZZ") {
		//Changed my mind, lets make the systematic equal to the deviation from 1.0
		if(njet < 2) {
			result.first=0.897051;
			result.second=(result.first-1.0);//0.0240056;
		} else {
			result.first=2.0084;
			result.second=(result.first-1.0);//0.235138;
		}
	} else if(getMCtype() == "ttbar") {
		if(njet < 2) //0 or 1
			{
			result.first=1.42;//1.18;
			result.second=-0.42;//-0.18;
		} else if(njet < 3) {
			//2 jet
			result.first=1.18;
			result.second=-0.18;
		} else if(njet < 4)  { //was 2, 3, no just 3
			//3 jet
			result.first=1.04;//0.97;
			result.second=-0.04;//0.03;
		} else if(njet < 6) //4, 5
			{
			result.first=1.0;
			result.second=0.0;
		} else if(njet < 100000) //>5
			{
			result.first=1.0;//0.98;
			result.second=0.0;//0.02;
		}
	}
	
	return result;
}
