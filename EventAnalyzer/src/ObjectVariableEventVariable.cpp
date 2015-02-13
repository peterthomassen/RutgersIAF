#include "RutgersIAF/EventAnalyzer/interface/ObjectVariableEventVariable.h"

ClassImp(ObjectVariableEventVariable<int>)
ClassImp(ObjectVariableEventVariable<double>)
ClassImp(ObjectVariableEventVariable<TString>)
ClassImp(ObjectVariableEventVariable<bool>)

template class ObjectVariableEventVariable<int>;
template class ObjectVariableEventVariable<double>;
template class ObjectVariableEventVariable<TString>;
template class ObjectVariableEventVariable<bool>;
