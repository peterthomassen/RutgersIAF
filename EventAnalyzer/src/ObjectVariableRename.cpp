#include "RutgersIAF2012/EventAnalyzer/interface/ObjectVariableRename.h"

ClassImp(ObjectVariableRename<int>)
ClassImp(ObjectVariableRename<double>)
ClassImp(ObjectVariableRename<TString>)
ClassImp(ObjectVariableRename<bool>)

template class ObjectVariableRename<int>;
template class ObjectVariableRename<double>;
template class ObjectVariableRename<TString>;
template class ObjectVariableRename<bool>;
