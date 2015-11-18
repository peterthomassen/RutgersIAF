#include "RutgersIAF/EventAnalyzer/interface/SignatureTH1F_EventVariable.h"

ClassImp(SignatureTH1F_EventVariable<int>)
ClassImp(SignatureTH1F_EventVariable<double>)

template class SignatureTH1F_EventVariable<int>;
template class SignatureTH1F_EventVariable<double>;

using namespace std;

template <typename T>
Int_t SignatureTH1F_EventVariable<T>::Fill(BaseHandler* handler) {
	T value;
	bool isSet = handler->getVariable(m_varname,value);
	if(!isSet)return -1;
	
	double weight;
	if(m_weightName.Length() > 0) {
		bool hasWeight = handler->getVariable(m_weightName, weight);
		if(!hasWeight) {
			return -1;
		}
	} else {
		weight = handler->getPhysicsWeight();
	}
	
	return TH1F::Fill(value, weight);
}
