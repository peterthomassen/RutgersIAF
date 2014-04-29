#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH2F_EventVariableVsEventVariable.h"

typedef SignatureTH2F_EventVariableVsEventVariable<double,double> s2_d_d;
ClassImp(s2_d_d)
typedef SignatureTH2F_EventVariableVsEventVariable<int,double> s2_i_d;
ClassImp(s2_i_d)
typedef SignatureTH2F_EventVariableVsEventVariable<double,int> s2_d_i;
ClassImp(s2_d_i)
typedef SignatureTH2F_EventVariableVsEventVariable<int,int> s2_i_i;
ClassImp(s2_i_i)

template class SignatureTH2F_EventVariableVsEventVariable<double,double>;
template class SignatureTH2F_EventVariableVsEventVariable<int,double>;
template class SignatureTH2F_EventVariableVsEventVariable<double,int>;
template class SignatureTH2F_EventVariableVsEventVariable<int,int>;

