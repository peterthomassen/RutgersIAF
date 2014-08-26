#include "RutgersIAF/EventAnalyzer/interface/SignatureTH2F_EventVariableVsObjectVariable.h"

typedef SignatureTH2F_EventVariableVsObjectVariable<double,double> s2_d_d;
ClassImp(s2_d_d)
typedef SignatureTH2F_EventVariableVsObjectVariable<int,double> s2_i_d;
ClassImp(s2_i_d)
typedef SignatureTH2F_EventVariableVsObjectVariable<double,int> s2_d_i;
ClassImp(s2_d_i)
typedef SignatureTH2F_EventVariableVsObjectVariable<int,int> s2_i_i;
ClassImp(s2_i_i)

template class SignatureTH2F_EventVariableVsObjectVariable<double,double>;
template class SignatureTH2F_EventVariableVsObjectVariable<int,double>;
template class SignatureTH2F_EventVariableVsObjectVariable<double,int>;
template class SignatureTH2F_EventVariableVsObjectVariable<int,int>;
