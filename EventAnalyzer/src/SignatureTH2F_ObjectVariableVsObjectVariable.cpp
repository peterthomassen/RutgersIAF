#include "RutgersIAF2012/EventAnalyzer/interface/SignatureTH2F_ObjectVariableVsObjectVariable.h"

typedef SignatureTH2F_ObjectVariableVsObjectVariable<double,double> s2_d_d;
ClassImp(s2_d_d)
typedef SignatureTH2F_ObjectVariableVsObjectVariable<int,double> s2_i_d;
ClassImp(s2_i_d)
typedef SignatureTH2F_ObjectVariableVsObjectVariable<double,int> s2_d_i;
ClassImp(s2_d_i)
typedef SignatureTH2F_ObjectVariableVsObjectVariable<int,int> s2_i_i;
ClassImp(s2_i_i)

template class SignatureTH2F_ObjectVariableVsObjectVariable<double,double>;
template class SignatureTH2F_ObjectVariableVsObjectVariable<int,double>;
template class SignatureTH2F_ObjectVariableVsObjectVariable<double,int>;
template class SignatureTH2F_ObjectVariableVsObjectVariable<int,int>;
