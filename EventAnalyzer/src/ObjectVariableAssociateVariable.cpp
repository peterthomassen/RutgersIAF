#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableAssociateVariable.h"

ClassImp(ObjectVariableAssociateVariable<int>)
ClassImp(ObjectVariableAssociateVariable<double>)
ClassImp(ObjectVariableAssociateVariable<bool>)
ClassImp(ObjectVariableAssociateVariable<TString>)

template class ObjectVariableAssociateVariable<int>;
template class ObjectVariableAssociateVariable<double>;
template class ObjectVariableAssociateVariable<TString>;
template class ObjectVariableAssociateVariable<bool>;
