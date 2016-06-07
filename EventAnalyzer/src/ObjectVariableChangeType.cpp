#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableChangeType.h"

typedef ObjectVariableChangeType<bool,int> ovct_b_i;
ClassImp(ovct_b_i)
typedef ObjectVariableChangeType<int,bool> ovct_i_b;
ClassImp(ovct_i_b)
typedef ObjectVariableChangeType<double,int> ovct_d_i;
ClassImp(ovct_d_i)
typedef ObjectVariableChangeType<int,double> ovct_i_d;
ClassImp(ovct_i_d)

template class ObjectVariableChangeType<bool,int>;
template class ObjectVariableChangeType<int,bool>;
template class ObjectVariableChangeType<double,int>;
template class ObjectVariableChangeType<int,double>;
